using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Collections.Generic;
using System.Runtime.Serialization.Formatters.Soap;
using System.Runtime.Serialization.Json;
using System.Runtime.Serialization.Formatters.Binary;
using System.Xml.Serialization;


namespace MainForm
{
    public partial class MainForm : Form
    {
        enum State { Binary, XML, Soap, Json };
        State CurrentState;
        static int arr_points_Max = 100;
        Point3D[] arr_points = new Point3D[arr_points_Max];
        PointCollection collection_points = new PointCollection();
        ArrayList arrList_points = new ArrayList();
        List<Point3D> list_points = new List<Point3D>();
        public MainForm()
        {
            InitializeComponent();
            CurrentState = State.Binary;
        }

        private void b_Add_Click(object sender, EventArgs e)
        {
            Point_Constructor point_Constructor = new Point_Constructor();
            point_Constructor.ShowDialog();
            if (point_Constructor.DialogResult == DialogResult.OK)
            {
                Point3D point = new Point3D()
                {
                    x = point_Constructor.X,
                    y = point_Constructor.Y,
                    z = point_Constructor.Z
                };
                switch(CurrentState)
                {
                    case State.Binary: BinaryAdd(point); break;
                    case State.XML: XMLAdd(point); break;
                    case State.Soap: SoapAdd(point); break;
                    case State.Json: JsonAdd(point); break;
                }
            }
        }

        void BinaryAdd(Point3D point)
        {
            int i = lv_Binary.Items.Count;
            if(i>arr_points_Max)
            {
                MessageBox.Show("Array Overflow");
                return;
            }
            arr_points[i] = point;
            lv_Binary.Items.Add(point.ToString()).Tag = i;
        }

        void XMLAdd(Point3D point)
        {
            collection_points.Add(point);
            lv_XML.Items.Add(point.ToString()).Tag = point;
        }

        void SoapAdd(Point3D point)
        {
            arrList_points.Add(point);
            lv_Soap.Items.Add(point.ToString()).Tag = point;
        }

        void JsonAdd(Point3D point)
        {
            list_points.Add(point);
            lv_Json.Items.Add(point.ToString()).Tag = point;
        }

        private void b_Delete_Click(object sender, EventArgs e)
        {
            switch (CurrentState)
            {
                case State.Binary: BinaryDelete(); break;
                case State.XML: XMLDelete(); break;
                case State.Soap: SoapDelete(); break;
                case State.Json: JsonDelete(); break;
            }
        }

        void BinaryDelete()
        {
            if (lv_Binary.SelectedItems.Count > 0)
            {
                foreach (ListViewItem item in lv_Binary.SelectedItems)
                {
                    int i = (int)item.Tag;
                    for(int j=i;j<lv_Binary.Items.Count-1;j++)
                    {
                        lv_Binary.Items[j].Text = lv_Binary.Items[j + 1].Text;
                        arr_points[j] = arr_points[j + 1];
                    }
                    arr_points[lv_Binary.Items.Count] = null;
                    lv_Binary.Items[lv_Binary.Items.Count - 1].Remove();
                }
            }
        }

        void XMLDelete()
        {
            if (lv_XML.SelectedItems.Count > 0)
            {
                foreach(ListViewItem item in lv_XML.SelectedItems)
                {
                    collection_points.Remove(item.Tag as Point3D);
                    item.Remove();
                }
            }
        }

        void SoapDelete()
        {
            if (lv_Soap.SelectedItems.Count > 0)
            {
                foreach (ListViewItem item in lv_Soap.SelectedItems)
                {
                    arrList_points.Remove(item.Tag as Point3D);
                    item.Remove();
                }
            }
        }

        void JsonDelete()
        {
            if (lv_Json.SelectedItems.Count > 0)
            {
                foreach (ListViewItem item in lv_Json.SelectedItems)
                {
                    list_points.Remove(item.Tag as Point3D);
                    item.Remove();
                }
            }
        }

        private void b_Change_Click(object sender, EventArgs e)
        {
            bool itemSelected = false;
            switch(CurrentState)
            {
                case State.Binary:
                    if (lv_Binary.SelectedItems.Count > 0)
                        itemSelected = true;
                    break;
                case State.XML:
                    if (lv_XML.SelectedItems.Count > 0)
                        itemSelected = true;
                    break;
                case State.Soap:
                    if (lv_Soap.SelectedItems.Count > 0)
                        itemSelected = true;
                    break;
                case State.Json:
                    if (lv_Json.SelectedItems.Count > 0)
                        itemSelected = true;
                    break;
            }

            if(itemSelected)
            {
                ListViewItem item = null;
                Point3D point = null;
                switch (CurrentState)
                {
                    case State.Binary:
                        item = lv_Binary.SelectedItems[0];
                        point = arr_points[(int)item.Tag] as Point3D;
                        break;
                    case State.XML:
                        item = lv_XML.SelectedItems[0];
                        point = item.Tag as Point3D;
                        break;
                    case State.Soap:
                        item = lv_Soap.SelectedItems[0];
                        point = item.Tag as Point3D;
                        break;
                    case State.Json:
                        item = lv_Json.SelectedItems[0];
                        point = item.Tag as Point3D;
                        break;
                }
                Point_Constructor point_Constructor = new Point_Constructor(point.x, point.y, point.z);
                point_Constructor.ShowDialog();

                if(point_Constructor.DialogResult == DialogResult.OK)
                {
                    point.x = point_Constructor.X;
                    point.y = point_Constructor.Y;
                    point.z = point_Constructor.Z;
                    item.Text = point.ToString();
                }
            }
        }

        void BinaryChange(Point3D point)
        {
            ListViewItem item = lv_Binary.SelectedItems[0];
        }

        void XMLChange(Point3D point)
        {
            ListViewItem item = lv_Binary.SelectedItems[0];

        }

        void SoapChange(Point3D point)
        {
            ListViewItem item = lv_Binary.SelectedItems[0];

        }

        void JsonChange(Point3D point)
        {
            ListViewItem item = lv_Binary.SelectedItems[0];

        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            switch(CurrentState)
            {
                case State.Binary: BinarySave(); break;
                case State.XML: XMLSave(); break;
                case State.Soap: SoapSave(); break;
                case State.Json: JsonSave(); break;
            }
        }
        void BinarySave()
        {
            BinaryFormatter formatter = new BinaryFormatter();
            SaveFileDialog svfDialog = new SaveFileDialog();
            svfDialog.Filter = "Point file binary (*.pfb)|*.pfb";
            svfDialog.DefaultExt = "pfb";
            if (svfDialog.ShowDialog() == DialogResult.OK)
            {
                using (FileStream fs = new FileStream(svfDialog.FileName, FileMode.OpenOrCreate))
                {
                    formatter.Serialize(fs, arr_points);
                }
            }
        }

        void XMLSave()
        {
            XmlSerializer formatter = new XmlSerializer(typeof(PointCollection));
            SaveFileDialog svfDialog = new SaveFileDialog();
            svfDialog.Filter = "Point file XML (*.pfxml)|*.pfxml";
            svfDialog.DefaultExt = "pfxlm";
            if (svfDialog.ShowDialog() == DialogResult.OK)
            {
                using (FileStream fs = new FileStream(svfDialog.FileName, FileMode.OpenOrCreate))
                {
                    
                    formatter.Serialize(fs, collection_points);
                }
            }
        }

        void SoapSave()
        {

            SaveFileDialog svfDialog = new SaveFileDialog();
            svfDialog.Filter = "Point file soap (*.pfs)|*.pfs";
            svfDialog.DefaultExt = "pfs";
            if (svfDialog.ShowDialog() == DialogResult.OK)
            {
                FileStream fStream = null;
                SoapFormatter mySoapFormatter = new SoapFormatter();
                try
                {
                    fStream = new FileStream(svfDialog.FileName, FileMode.Create, FileAccess.Write);
                    mySoapFormatter.Serialize(fStream, arrList_points);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
                finally
                {
                    if (fStream != null) fStream.Close();
                }
            }
        }

        void JsonSave()
        {
            DataContractJsonSerializer formatter = new DataContractJsonSerializer(typeof(List<Point3D>));
            SaveFileDialog svfDialog = new SaveFileDialog();
            svfDialog.Filter = "Point file Json (*.pfjson)|*.pfjson";
            svfDialog.DefaultExt = "pfjson";
            if (svfDialog.ShowDialog() == DialogResult.OK)
            {
                using (FileStream fs = new FileStream(svfDialog.FileName, FileMode.OpenOrCreate))
                {
                    formatter.WriteObject(fs, list_points);
                }
            }
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                switch (CurrentState)
                {
                    case State.Binary: BinaryLoad(); break;
                    case State.XML: XML_Load(); break;
                    case State.Soap: SoapLoad(); break;
                    case State.Json: JsonLoad(); break;
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            
        }
        
        void BinaryLoad()
        {
            BinaryFormatter formatter = new BinaryFormatter();
            OpenFileDialog opfDialog = new OpenFileDialog();
            opfDialog.Filter = "Point file binary (*.pfb)|*.pfb";
            if (opfDialog.ShowDialog() == DialogResult.OK)
            {
                using (FileStream fs = new FileStream(opfDialog.FileName, FileMode.OpenOrCreate))
                {
                    arr_points = (Point3D[])formatter.Deserialize(fs);
                    lv_Binary.Clear();
                    for(int i=0;arr_points[i]!=null;i++)
                    {
                        lv_Binary.Items.Add(arr_points[i].ToString()).Tag = i;
                    }
                }
            }

        }
        void XML_Load()
        {
            XmlSerializer formatter = new XmlSerializer(typeof(PointCollection));
            OpenFileDialog opfDialog = new OpenFileDialog();
            opfDialog.Filter = "Point file XML (*.pfxml)|*.pfxml";
            if (opfDialog.ShowDialog() == DialogResult.OK)
            {
                using (FileStream fs = new FileStream(opfDialog.FileName, FileMode.OpenOrCreate))
                {
                    collection_points = (PointCollection)formatter.Deserialize(fs);
                    lv_XML.Clear();
                    foreach (Point3D point in collection_points)
                    {
                        lv_XML.Items.Add(point.ToString()).Tag = point;
                    }
                }
            }
        }

        void SoapLoad()
        {
            FileStream fStream = null;
            SoapFormatter mySoapFormatter = new SoapFormatter();
            OpenFileDialog opfDialog = new OpenFileDialog();
            opfDialog.Filter = "Point file soap (*.pfs)|*.pfs";
            if (opfDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    fStream = new FileStream(opfDialog.FileName, FileMode.Open, FileAccess.Read);
                    arrList_points = (ArrayList)mySoapFormatter.Deserialize(fStream);
                    lv_Soap.Items.Clear();
                    foreach (Point3D point in arrList_points)
                    {
                        lv_Soap.Items.Add(point.ToString()).Tag = point;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
                finally
                {
                    if (fStream != null) fStream.Close();
                }
            }
        }

        void JsonLoad()
        {
            DataContractJsonSerializer formatter = new DataContractJsonSerializer(typeof(List<Point3D>));
            OpenFileDialog opfDialog = new OpenFileDialog();
            opfDialog.Filter = "Point file Json (*.pfjson)|*.pfjson";
            if (opfDialog.ShowDialog() == DialogResult.OK)
            {
                using (FileStream fs = new FileStream(opfDialog.FileName, FileMode.OpenOrCreate))
                {
                    list_points = (List<Point3D>)formatter.ReadObject(fs);
                    lv_Json.Clear();
                    foreach (Point3D point in list_points)
                    {
                        lv_Json.Items.Add(point.ToString()).Tag = point;
                    }
                }
            }
        }

        private void tp_Binary_Enter(object sender, EventArgs e)
        {
            CurrentState = State.Binary;
        }

        private void tp_XML_Enter(object sender, EventArgs e)
        {
            CurrentState = State.XML;
        }

        private void tp_Soap_Enter(object sender, EventArgs e)
        {
            CurrentState = State.Soap;
        }

        private void tp_Json_Enter(object sender, EventArgs e)
        {
            CurrentState = State.Json;
        }
    }
}
