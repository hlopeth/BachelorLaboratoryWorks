using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Data;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Data.SQLite;
using RabbitMQ.Client;
using System.Security.Cryptography;

namespace Server
{
    class Program
    {
        static void Main(string[] args)
        {
            DataSet dataSet = ReadFromDB("sqlite.db");
            dataSet = NormalizeData(dataSet);
           
            SendDataViaSocket(dataSet);
            //SendDataViaMQ(dataSet);
        }

        public static byte[] RSAEncrypt(byte[] DataToEncrypt, RSAParameters RSAKeyInfo, bool DoOAEPPadding)
        {
            try
            {
                byte[] encryptedData;
                using (RSACryptoServiceProvider RSA = new RSACryptoServiceProvider())
                {
                    RSA.ImportParameters(RSAKeyInfo);
                    encryptedData = RSA.Encrypt(DataToEncrypt, DoOAEPPadding);
                }
                return encryptedData;
            }
            catch (CryptographicException e)
            {
                Console.WriteLine(e.Message);
                return null;
            }

        }

        public static byte[] RSADecrypt(byte[] DataToDecrypt, RSAParameters RSAKeyInfo, bool DoOAEPPadding)
        {
            try
            {
                byte[] decryptedData;
                using (RSACryptoServiceProvider RSA = new RSACryptoServiceProvider())
                {
                    RSA.ImportParameters(RSAKeyInfo);
                    decryptedData = RSA.Decrypt(DataToDecrypt, DoOAEPPadding);
                }
                return decryptedData;
            }
            catch (CryptographicException e)
            {
                Console.WriteLine(e.ToString());
                return null;
            }

        }

        private static byte[] DecryptTextFromMemory(byte[] data, byte[] key, byte[] iV)
        {
            try
            {
                MemoryStream msDecrypt = new MemoryStream(data);

                DES DESalg = DES.Create();

                CryptoStream csDecrypt = new CryptoStream(msDecrypt,
                    DESalg.CreateDecryptor(key, iV),
                    CryptoStreamMode.Read);

                byte[] fromEncrypt = new byte[data.Length];

                csDecrypt.Read(fromEncrypt, 0, fromEncrypt.Length);

                return fromEncrypt;
            }
            catch (CryptographicException e)
            {
                Console.WriteLine("A Cryptographic error occurred: {0}", e.Message);
                return null;
            }
        }

        private static byte[] EncryptTextToMemory(byte[] dataSet, byte[] key, byte[] iV)
        {
            MemoryStream mStream = new MemoryStream();
            DES DESalg = DES.Create();

            CryptoStream cStream = new CryptoStream(mStream,
                DESalg.CreateEncryptor(key, iV),
                CryptoStreamMode.Write);

            cStream.Write(dataSet, 0, dataSet.Length);
            cStream.FlushFinalBlock();

            byte[] ret = mStream.ToArray();

            cStream.Close();
            mStream.Close();

            return ret;
        }

        static void PrintDs(DataSet ds)
        {
            foreach (DataTable dt in ds.Tables)
            {
                Console.WriteLine(dt.TableName);
                foreach (DataColumn c in dt.Columns)
                    Console.Write("\t{0}", c.ColumnName);
                Console.WriteLine();
                foreach (DataRow r in dt.Rows)
                {
                    foreach (var cell in r.ItemArray)
                        Console.Write("\t{0}", cell);
                    Console.WriteLine();
                }
                Console.WriteLine();
            }
        }

        private static void SendDataViaMQ(DataSet dataSet)
        {
            var factory = new ConnectionFactory() { HostName = "localhost" };
            using (var connection = factory.CreateConnection())
            {
                using (var channel = connection.CreateModel())
                {
                    channel.ExchangeDeclare(exchange: "logs", type: "fanout");

                    string input = "";
                    do
                    {
                        input = Console.ReadLine();
                        var body = DataSetToBytes(dataSet);
                        channel.BasicPublish(exchange: "logs", routingKey: "", basicProperties: null, body: body);
                        Console.WriteLine(" [x] Sent");
                    }
                    while (input.ToUpper() != "Q");
                }

            }


            Console.WriteLine(" Press [enter] to exit.");
            Console.ReadLine();
        }

        private static void SendDataViaSocket(DataSet dataSet, int port = 11000)
        {
            /*IPHostEntry ipHost = Dns.GetHostEntry("localhost");
            IPAddress ipAddr = ipHost.AddressList[0];*/
            IPEndPoint ipEndPoint = new IPEndPoint(IPAddress.Any, port);
            
            Socket sListener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                sListener.Bind(ipEndPoint);
                sListener.Listen(10);

                while (true)
                {
                    Console.WriteLine("Ожидаем соединение через порт {0}", ipEndPoint);

                    Socket handler = sListener.Accept();
                    string data = null;


                    RSACryptoServiceProvider RSA = new RSACryptoServiceProvider();
                    byte[] bytes = new byte[256];
                    int bytesRec = handler.Receive(bytes);
                    RSA.ImportParameters(BytesToRSAParams(bytes));

                    data += Encoding.UTF8.GetString(bytes, 0, bytesRec);

                    
                    var des = DES.Create();
                    byte[] encDataSet = EncryptTextToMemory(DataSetToBytes(dataSet), des.Key, des.IV);
                    handler.Send(RSA.Encrypt(des.Key,false));
                    handler.Send(des.IV);
                    handler.Send(ToBytes<int>(encDataSet.Length));
                    int bytesSend = handler.Send(encDataSet);
                    if (data.IndexOf("<TheEnd>") > -1)
                    {
                        Console.WriteLine("Сервер завершил соединение с клиентом.");
                        break;
                    }

                    handler.Shutdown(SocketShutdown.Both);
                    handler.Close();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
            finally
            {
                Console.ReadLine();
            }
        }

        private static DataSet NormalizeData(DataSet dataSet)
        {
            DataSet _dataSet = new DataSet();


            DataTable Towns = new DataTable("Towns");
            DataColumn TownIdCol = new DataColumn("Id", Type.GetType("System.Int32"))
            {
                Unique = true,
                AllowDBNull = false,
                AutoIncrement = true,
                AutoIncrementSeed = 1,
                AutoIncrementStep = 1
            };
            DataColumn TownNameCol = new DataColumn("Name", Type.GetType("System.String"))
            {
                Unique = true
            };
            DataColumn TownPopulationCol = new DataColumn("Population", Type.GetType("System.Int32"));
            Towns.Columns.AddRange(new DataColumn[] { TownIdCol, TownNameCol, TownPopulationCol });
            Towns.PrimaryKey = new DataColumn[] { Towns.Columns["Name"] };


            DataTable Companies = new DataTable("Companies");
            DataColumn CompanyIdCol = new DataColumn("Id", Type.GetType("System.Int32"))
            {
                Unique = true,
                AllowDBNull = false,
                AutoIncrement = true,
                AutoIncrementSeed = 1,
                AutoIncrementStep = 1
            };
            DataColumn CompanyNameCol = new DataColumn("Name", Type.GetType("System.String"))
            {
                Unique = true
            };
            DataColumn CompanyDiscountCol = new DataColumn("Discount", Type.GetType("System.Int32"));
            Companies.Columns.AddRange(new DataColumn[] { CompanyIdCol, CompanyNameCol, CompanyDiscountCol });
            Companies.PrimaryKey = new DataColumn[] { Companies.Columns["Name"] };


            DataTable Shops = new DataTable("Shops");
            DataColumn ShopIdCol = new DataColumn("Id", Type.GetType("System.Int32"))
            {
                Unique = true,
                AllowDBNull = false,
                AutoIncrement = true,
                AutoIncrementSeed = 1,
                AutoIncrementStep = 1
            };
            DataColumn ShopNameCol = new DataColumn("Name", Type.GetType("System.String"))
            {
                Unique = true
            };
            DataColumn ShopPhoneCol = new DataColumn("Phone", Type.GetType("System.String"));
            DataColumn ShopTownIdCol = new DataColumn("TownId", Type.GetType("System.Int32"));
            Shops.Columns.AddRange(new DataColumn[] { ShopIdCol, ShopNameCol, ShopPhoneCol, ShopTownIdCol });
            Shops.PrimaryKey = new DataColumn[] { Shops.Columns["Name"] };


            DataTable Models = new DataTable("Model");
            DataColumn ModelIdCol = new DataColumn("Id", Type.GetType("System.Int32"))
            {
                Unique = true,
                AllowDBNull = false,
                AutoIncrement = true,
                AutoIncrementSeed = 1,
                AutoIncrementStep = 1
            };
            DataColumn ModelNameCol = new DataColumn("Name", Type.GetType("System.String"))
            {
                Unique = true
            };
            DataColumn ModelPriceCol = new DataColumn("Price", Type.GetType("System.Int32"));
            DataColumn ModelCompanyIdCol = new DataColumn("CompanyId", Type.GetType("System.Int32"));
            Models.Columns.AddRange(new DataColumn[] { ModelIdCol, ModelNameCol, ModelPriceCol, ModelCompanyIdCol });
            Models.PrimaryKey = new DataColumn[] { Models.Columns["Name"] };


            DataTable CompanyShop = new DataTable("CompanyShop");
            DataColumn CompanyShop_CompanyIdCol = new DataColumn("CompanyId", Type.GetType("System.Int32"));
            DataColumn CompanyShop_ShopIdCol = new DataColumn("ShopId", Type.GetType("System.Int32"));
            CompanyShop.Columns.AddRange(new DataColumn[] { CompanyShop_CompanyIdCol, CompanyShop_ShopIdCol });
            CompanyShop.PrimaryKey = new DataColumn[] { CompanyShop.Columns["CompanyId"], CompanyShop.Columns["ShopId"] };

            foreach (DataTable table in dataSet.Tables)
                foreach (DataRow row in table.Rows)
                {
                    int n = row.ItemArray.Length;
                    var items = row.ItemArray;

                    string modelName = (string)items[0];
                    string companyName = (string)items[1];
                    int price = Convert.ToInt32(items[2]);
                    int discount = Convert.ToInt32(items[3]);
                    string shopName = (string)items[4];
                    string phone = (string)items[5];
                    string townName = (string)items[6];
                    int population = Convert.ToInt32(items[7]);

                    if (!Towns.Rows.Contains(townName))
                    {
                        Towns.Rows.Add(new object[] {null, townName, population });
                    }

                    if(!Companies.Rows.Contains(companyName))
                    {
                        Companies.Rows.Add(new object[] { null, companyName, discount});
                    }

                    if(!Shops.Rows.Contains(shopName))
                    {
                        int townId = Convert.ToInt32(Towns.Rows.Find(townName)["Id"]);
                        Shops.Rows.Add(null, shopName, phone, townId);
                    }

                    if(!Models.Rows.Contains(modelName))
                    {
                        int companyId = Convert.ToInt32(Companies.Rows.Find(companyName)["Id"]);
                        Models.Rows.Add(new object[] { null, modelName, price, companyId });
                    }

                    
                    {
                        int companyId = Convert.ToInt32(Companies.Rows.Find(companyName)["Id"]);
                        int shopId = Convert.ToInt32(Shops.Rows.Find(shopName)["Id"]);
                        if(!CompanyShop.Rows.Contains(new object[] { companyId, shopId }))
                            CompanyShop.Rows.Add(new object[] { companyId, shopId });
                    }


                }

            _dataSet.Tables.AddRange( new DataTable[] { Towns, Companies, Shops, Models, CompanyShop });
            return _dataSet;
        }

        static DataTable InitData()
        {
            var dataTable = new DataTable("Company");

            DataColumn idColumn = new DataColumn("Id", Type.GetType("System.Int32"))
            {
                Unique = true,
                AllowDBNull = false,
                AutoIncrement = true,
                AutoIncrementSeed = 1,
                AutoIncrementStep = 1
            };

            DataColumn nameColumn = new DataColumn("Name", Type.GetType("System.String"));
            DataColumn discountColumn = new DataColumn("Discount", Type.GetType("System.Int32"));

            dataTable.Columns.AddRange(new DataColumn[] { idColumn, nameColumn, discountColumn });

            dataTable.Rows.Add(new object[] {null, "BMW", 5 });
            dataTable.Rows.Add(new object[] {null, "Audi", 3 });
            dataTable.Rows.Add(new object[] {null, "Nissan", 10 });

            return dataTable;
        }

        static DataSet ReadFromDB(string bdName)
        {
            DataSet ds = new DataSet();
            DataTable dTable = new DataTable();
            String sqlQuery;
            SQLiteConnection m_dbConn;
            m_dbConn = new SQLiteConnection();
            
            m_dbConn = new SQLiteConnection("Data Source=" + bdName + ";Version=3;");
            m_dbConn.Open();

            try
            {
                sqlQuery = "SELECT * FROM Cars";
                SQLiteDataAdapter adapter = new SQLiteDataAdapter(sqlQuery, m_dbConn);
                adapter.Fill(dTable);
            }
            catch (SQLiteException ex)
            {
                Console.WriteLine("Error: " + ex.Message);
            }
            ds.Tables.Add(dTable);
            return ds;
        }

        static byte[] DataSetToBytes(DataSet dataSet)
        {
            MemoryStream stream = new System.IO.MemoryStream();
            System.Runtime.Serialization.IFormatter formatter = new BinaryFormatter();
            formatter.Serialize(stream, dataSet);

            byte[] bytes = stream.GetBuffer();

            return bytes;
        }

        static DataSet BytesToDataSet(byte[] byteArrayData)
        {
            DataSet ds;
            using (MemoryStream stream = new MemoryStream(byteArrayData))
            {
                BinaryFormatter bformatter = new BinaryFormatter();
                ds = (DataSet)bformatter.Deserialize(stream);
            }
            return ds;
        }

        static byte[] RSAParamsToBytes(RSAParameters parameters)
        {
            MemoryStream stream = new System.IO.MemoryStream();
            System.Runtime.Serialization.IFormatter formatter = new BinaryFormatter();
            formatter.Serialize(stream, parameters);

            byte[] bytes = stream.GetBuffer();

            return bytes;
        }

        static RSAParameters BytesToRSAParams(byte[] byteArrayData)
        {
            RSAParameters parameters;
            using (MemoryStream stream = new MemoryStream(byteArrayData))
            {
                BinaryFormatter bformatter = new BinaryFormatter();
                parameters = (RSAParameters)bformatter.Deserialize(stream);
            }
            return parameters;
        }

        static byte[] ToBytes<T>(T parameters)
        {
            MemoryStream stream = new System.IO.MemoryStream();
            System.Runtime.Serialization.IFormatter formatter = new BinaryFormatter();
            formatter.Serialize(stream, parameters);

            byte[] bytes = stream.GetBuffer();

            return bytes;
        }

        static T FromBytes<T>(byte[] byteArrayData)
        {
            T parameters;
            using (MemoryStream stream = new MemoryStream(byteArrayData))
            {
                BinaryFormatter bformatter = new BinaryFormatter();
                parameters = (T)bformatter.Deserialize(stream);
            }
            return parameters;
        }

    }
}
