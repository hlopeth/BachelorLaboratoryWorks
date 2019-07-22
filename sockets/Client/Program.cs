using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Data;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using RabbitMQ.Client;
using RabbitMQ.Client.Events;
using System.Security.Cryptography;
using System.Data.SqlClient;

namespace Client
{
    class Program
    {
        static void Main(string[] args)
        {
            GetMessageViaSocket();
            //GetMessageViaMQ();
        }

        private static byte[] DecryptTextFromMemory(byte[] data, int length, byte[] key, byte[] iV)
        {
            try
            {
                MemoryStream msDecrypt = new MemoryStream(data);

                DES DESalg = DES.Create();

                CryptoStream csDecrypt = new CryptoStream(msDecrypt,
                    DESalg.CreateDecryptor(key, iV),
                    CryptoStreamMode.Read);

                byte[] fromEncrypt = new byte[length];

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

        static void GetMessageViaMQ()
        {
            var factory = new ConnectionFactory() { HostName = "localhost" };
            using (var connection = factory.CreateConnection())
            using (var channel = connection.CreateModel())
            {
                channel.ExchangeDeclare(exchange: "logs", type: "fanout");

                var queueName = channel.QueueDeclare().QueueName;
                channel.QueueBind(queue: queueName,
                                  exchange: "logs",
                                  routingKey: "");

                Console.WriteLine(" [*] Waiting for logs.");

                var consumer = new EventingBasicConsumer(channel);
                consumer.Received += (model, ea) =>
                {
                    var body = ea.Body;
                    var dt = FromBytes<DataSet>(body);
                    PrintDs(dt);
                };
                channel.BasicConsume(queue: queueName,
                                autoAck: true,
                                consumer: consumer);

                Console.WriteLine(" Press [enter] to exit.");
                Console.ReadLine();
            }
        }

        static void GetMessageViaSocket(int port = 11000)
        {
            try
            {
                SendMessageFromSocket(port);
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

        static void SendMessageFromSocket(int port)
        {
            byte[] RSAParams = new byte[256];
            byte[] encriptedKey = new byte[128];
            byte[] key = new byte[8];
            byte[] IV = new byte[8];
            byte[] len = new byte[256];


            //IPHostEntry ipHost = Dns.GetHostEntry("localhost");
            IPAddress ipAddr = IPAddress.Parse("25.12.0.19");//ipHost.AddressList[0];
            IPEndPoint ipEndPoint = new IPEndPoint(ipAddr, port);

            Socket sender = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            sender.Connect(ipEndPoint);
            using (var stream = new NetworkStream(sender))
            { 
                BinaryReader reader = new BinaryReader(stream, Encoding.Unicode, true);
                BinaryWriter writer = new BinaryWriter(stream, Encoding.Unicode, true);


                Console.WriteLine("Сокет соединяется с {0} ", sender.RemoteEndPoint.ToString());
                byte[] msg = Encoding.UTF8.GetBytes(" ");
                RSACryptoServiceProvider RSA = new RSACryptoServiceProvider();

                writer.Write(ToBytes<RSAParameters>(RSA.ExportParameters(false)));
                reader.Read(encriptedKey, 0, encriptedKey.Length);
                reader.Read(IV, 0, IV.Length);
                reader.Read(len, 0, len.Length);
                int bytesRec = FromBytes<int>(len);
                byte[] bytes = new byte[bytesRec];
                int a = 0;
                int step = bytesRec;
                while(a<bytesRec)
                {
                    if (a + step > bytesRec)
                        step = bytesRec - a;
                    a += reader.Read(bytes, a, step);
                }

                reader.Read(bytes, 0, bytesRec);
                
                key = RSA.Decrypt(encriptedKey, false);
                bytes = DecryptTextFromMemory(bytes, bytesRec, key, IV);
                var ds = FromBytes<DataSet>(bytes);
                PrintDs(ds);
                WriteToDB(ds);
                sender.Shutdown(SocketShutdown.Both);
                sender.Close();
            }
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

        static void WriteToDB(DataSet dataSet)
        {
            string sConnStr = new SqlConnectionStringBuilder()
            {
                DataSource = "DESKTOP-HPG2F1U\\SQLEXPRESS",
                InitialCatalog = "cars",
                IntegratedSecurity = true
            }.ConnectionString;

            using (var sConn = new SqlConnection(sConnStr))
            {
                sConn.Open();
                DataTable towns = dataSet.Tables["Towns"];
                SqlCommand sCommand;
                foreach (DataRow row1 in towns.Rows)
                {
                    sCommand = new SqlCommand
                    {
                        Connection = sConn,
                        CommandText = @"INSERT INTO Towns(Name, Population) 
                                    VALUES (@Name, @Population); SELECT SCOPE_IDENTITY();"
                    };
                    sCommand.Parameters.AddWithValue("@Name", row1.ItemArray[1]);
                    sCommand.Parameters.AddWithValue("@Population", row1.ItemArray[2]);
                    try
                    {
                        int id = Convert.ToInt32(sCommand.ExecuteScalar());
                        for (int i = 0; i < dataSet.Tables["Shops"].Rows.Count; i++)
                        {
                            DataRow r = dataSet.Tables["Shops"].Rows[i];
                            if (Convert.ToInt32(r.ItemArray[3]) == Convert.ToInt32(row1.ItemArray[0]))
                            {
                                dataSet.Tables["Shops"].Rows[i][3] = id;
                                dataSet.Tables["Shops"].Rows[i].AcceptChanges();
                            }
                        }
                    }
                    catch (SqlException ex)
                    {
                        Console.WriteLine(ex.Message);
                    }
                }

                    DataTable companies = dataSet.Tables["Companies"];
                    foreach (DataRow row2 in companies.Rows)
                    {
                        sCommand = new SqlCommand
                        {
                            Connection = sConn,
                            CommandText = @"INSERT INTO Companies(Name, Discount) 
                                    VALUES (@Name, @Discount); SELECT SCOPE_IDENTITY();"
                        };
                        sCommand.Parameters.AddWithValue("@Name", row2.ItemArray[1]);
                        sCommand.Parameters.AddWithValue("@Discount", row2.ItemArray[2]);
                        try
                        {
                            int id = Convert.ToInt32(sCommand.ExecuteScalar());
                            for (int i = 0; i < dataSet.Tables["Model"].Rows.Count; i++)
                            {
                                DataRow r = dataSet.Tables["Model"].Rows[i];
                                if (Convert.ToInt32(r.ItemArray[3]) == Convert.ToInt32(row2.ItemArray[0]))
                                {
                                    dataSet.Tables["Model"].Rows[i][3] = id;
                                    dataSet.Tables["Model"].Rows[i].AcceptChanges();
                                }
                            }

                            for (int i = 0; i < dataSet.Tables["CompanyShop"].Rows.Count; i++)
                            {
                                DataRow r = dataSet.Tables["CompanyShop"].Rows[i];
                                if (Convert.ToInt32(r.ItemArray[0]) == Convert.ToInt32(row2.ItemArray[0]))
                                {
                                    dataSet.Tables["CompanyShop"].Rows[i][0] = id;
                                    dataSet.Tables["CompanyShop"].AcceptChanges();
                                }
                            }

                        }
                        catch (SqlException ex)
                        {
                            Console.WriteLine(ex.Message);
                        }
                    }

                    DataTable models = dataSet.Tables["Model"];
                    foreach (DataRow row3 in models.Rows)
                    {
                        sCommand = new SqlCommand
                        {
                            Connection = sConn,
                            CommandText = @"INSERT INTO Model(Name, Price, CompanyId) 
                                    VALUES (@Name, @Price, @CompanyId); SELECT SCOPE_IDENTITY();"
                        };
                        sCommand.Parameters.AddWithValue("@Name", row3.ItemArray[1]);
                        sCommand.Parameters.AddWithValue("@Price", row3.ItemArray[2]);
                        sCommand.Parameters.AddWithValue("@CompanyId", row3.ItemArray[3]);
                        try
                        {
                            int id = Convert.ToInt32(sCommand.ExecuteScalar());

                        }
                        catch (SqlException ex)
                        {
                            Console.WriteLine(ex.Message);
                        }
                    }

                    DataTable shops = dataSet.Tables["Shops"];
                    foreach (DataRow row4 in shops.Rows)
                    {
                        sCommand = new SqlCommand
                        {
                            Connection = sConn,
                            CommandText = @"INSERT INTO Shops(Name, Phone, TownId) 
                                    VALUES (@Name, @Phone, @TownId); SELECT SCOPE_IDENTITY();"
                        };
                        sCommand.Parameters.AddWithValue("@Name", row4.ItemArray[1]);
                        sCommand.Parameters.AddWithValue("@Phone", row4.ItemArray[2]);
                        sCommand.Parameters.AddWithValue("@TownId", row4.ItemArray[3]);
                        try
                        {
                            int id = Convert.ToInt32(sCommand.ExecuteScalar());
                            for (int i = 0; i < dataSet.Tables["CompanyShop"].Rows.Count; i++)
                            {
                                DataRow r = dataSet.Tables["CompanyShop"].Rows[i];
                                if (Convert.ToInt32(r.ItemArray[1]) == Convert.ToInt32(row4.ItemArray[0]))
                                {
                                    dataSet.Tables["CompanyShop"].Rows[i][1] = id;
                                    dataSet.Tables["CompanyShop"].AcceptChanges();
                                }
                            }

                        }
                        catch (SqlException ex)
                        {
                            Console.WriteLine(ex.Message);
                        }
                    }

                DataTable companyShop = dataSet.Tables["CompanyShop"];
                foreach (DataRow row5 in companyShop.Rows)
                {
                    sCommand = new SqlCommand
                    {
                        Connection = sConn,
                        CommandText = @"INSERT INTO CompanyShop(CompanyId, ShopId) 
                                    VALUES (@CompanyId, @ShopId);"
                    };
                    sCommand.Parameters.AddWithValue("@CompanyId", row5.ItemArray[0]);
                    sCommand.Parameters.AddWithValue("@ShopId", row5.ItemArray[1]);
                    try
                    {
                        sCommand.ExecuteNonQuery();
                    }
                    catch (SqlException ex)
                    {
                        Console.WriteLine(ex.Message);
                    }
                }



            }
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
