using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Simulation_lab1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        int nn_num;

        private void tp_Puasson_Click(object sender, EventArgs e)
        {

        }

        private void bt_Start_Click(object sender, EventArgs e)
        {
            switch (RPannel.SelectedIndex)
            {
                case 0:
                    FillR1();
                    break;
                case 1:
                    FillR2();
                    break;
                case 2:
                    FillTriangle();
                    break;
                case 3:
                    FillErland();
                    break;
                case 4:
                    FillPuasson();
                    break;
                case 5:
                    FillN();
                    break;
                case 6:
                    FillExp();
                    break;
            }
        }

        double nn(int z0)
        {
            int num = 1;
            for (int index = 0; index < nn_num; ++index)
            {
                num = (29 * z0 + 31) % 3988;
                z0 = num;
            }
            ++nn_num;
            return (double)num / 3988.0;
        }

        void FillR1()
        {
            int a = 29;
            int b = 31;
            int c = 3988;
            lb_R1.Items.Clear();
            int z0 = Convert.ToInt32(nud_firstNum.Value);
            if (cb_Rand.Checked)
            {
                z0 = DateTime.Now.Millisecond;
                nud_firstNum.Value = z0;
            }
            int n = Convert.ToInt32(nudR1_n.Value);
            int[] m = new int[100];
            for (int i = 0; i < 100; i++)
                m[i] = 0;
            for (int i = 0; i < n; i++)
            {
                if (cb_Norm.Checked)
                    lb_R1.Items.Add((object)((double)z0 / (double)c));
                else
                    lb_R1.Items.Add(z0);
                ++m[(int)Math.Truncate((double)z0 / (double)c * 100.0)];
                int zn = (a * z0 + b) % c;
                z0 = zn;
            }
            chart_R1.Series[0].Points.Clear();
            for (int i = 0; i < 100; i++)
                chart_R1.Series[0].Points.AddY(m[i]);
            chart_R1.ChartAreas[0].AxisX.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.False;
        }

        void FillR2()
        {
            lb_R2.Items.Clear();
            nn_num = 10;
            int z0 = DateTime.Now.Millisecond;
            int n = Convert.ToInt32(nudR2_n.Value);
            int a = Convert.ToInt32(nud_Left.Value);
            int b = Convert.ToInt32(nud_Right.Value);
            int[] m = new int[100];
            for (int i = 0; i < 100; i++)
                m[i] = 0;
            for (int i = 0; i < n; i++)
            {
                double h = nn(z0);
                ++m[(int)Math.Truncate(h * 100.0)];
                h = (double)a + (double)(b - a) * h;
                lb_R2.Items.Add(h);
            }
            chart_R2.Series[0].Points.Clear();
            for (int i = 0; i < 100; i++)
                chart_R2.Series[0].Points.AddY(m[i]);
            chart_R2.ChartAreas[0].AxisX.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.False;
        }

        void FillTriangle()
        {
            lb_Triangle.Items.Clear();
            this.nn_num = 10;
            int z0 = DateTime.Now.Millisecond;
            double num1 = Convert.ToInt32(nudT_Left.Value);
            double num2 = Convert.ToInt32(nudT_Moda.Value);
            double num3 = Convert.ToInt32(nudT_Right.Value);
            int n = Convert.ToInt32(nudT_n.Value);
            if (num2 >= num3 || num2 <= num1)
            {
                num2 = Math.Round((num3 + num1) / 2.0);
                nudT_Moda.Value = (int)num2;
            }
            int[] m = new int[100];
            for (int i = 0; i < 100; i++)
                m[i] = 0;
            for (int i = 0; i < n; i++)
            {
                double h = this.nn(z0);
                h = h >= (num2 - num1) / (num3 - num1) ? num3 - Math.Sqrt((num3 - num2) * (num3 - num1) * (1.0 - h)) : num1 + Math.Sqrt((num2 - num1) * (num3 - num1) * h);
                ++m[(int)Math.Truncate((h - num1) / (num3 - num1) * 100.0)];
                lb_Triangle.Items.Add(h);
            }
            chart_Triangle.Series[0].Points.Clear();
            for (int i = 0; i < 100; i++)
                chart_Triangle.Series[0].Points.AddY(m[i]);
            chart_Triangle.ChartAreas[0].AxisX.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.False;
        }

        void FillErland()
        {
            lb_Erland.Items.Clear();
            nn_num = 10;
            int z0 = DateTime.Now.Millisecond;
            int n = Convert.ToInt32(nudE_n.Value);
            int num1 = Convert.ToInt32(nudE_Norm.Value);
            int num2 = Convert.ToInt32(nudE_Moda.Value);
            int[] m = new int[100];
            for (int i = 0; i < 100; i++)
            {
                m[i] = 0;
            }

            for (int i = 0; i < n; i++)
            {
                double h = 1.0;
                for (int index = 1; index <= num1; ++index)
                    h = h * this.nn(z0);
                h = (double)-num2 * Math.Log(h);
                if (h < 150.0)
                    ++m[(int)Math.Truncate(h * 2.0 / 3.0)];
                lb_Erland.Items.Add(h);
            }
            chart_Erland.Series[0].Points.Clear();
            for (int i = 0; i < 100; i++)
                chart_Erland.Series[0].Points.AddY(m[i]);
            chart_Erland.ChartAreas[0].AxisX.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.False;
        }

        void FillPuasson()
        {
            lb_Puasson.Items.Clear();
            this.nn_num = 10;
            int z0 = DateTime.Now.Millisecond;
            int n = Convert.ToInt32(nudP_n.Value);
            int L = Convert.ToInt32(nudP_L.Value);
            int[] m = new int[100];
            for (int i = 0; i < 100; i++)
                m[i] = 0;
            for (int i = 0; i < n; i++)
            {
                int index = 0;
                double num2 = Math.Exp((double)-L);
                double num3 = this.nn(z0);
                while (num3 > 0.0)
                {
                    num2 = num2 * (double)L / (double)(index + 1);
                    ++index;
                    num3 -= num2;
                }
                if (index < 100)
                    ++m[index];
                lb_Puasson.Items.Add(index);
            }
            chart_Puasson.Series[0].Points.Clear();
            for (int i = 0; i < 100; i++)
                chart_Puasson.Series[0].Points.AddY(m[i]);
            chart_Puasson.ChartAreas[0].AxisX.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.False;
        }

        void FillN()
        {
            lb_N.Items.Clear();
            nn_num = 10;
            int z0 = DateTime.Now.Millisecond;
            int n = Convert.ToInt32(nudN_n.Value);
            int M = Convert.ToInt32(nudN_M.Value);
            int D = Convert.ToInt32(nudN_D.Value);
            int[] m = new int[100];
            for (int i = 0; i < 100; i++)
                m[i] = 0;
            for (int i = 0; i < n; i++)
            {
                double num3 = Math.Sin(2.0 * Math.PI * nn(z0)) * Math.Sqrt(-2.0 * Math.Log(nn(z0)));
                double num4 = (double)M + (double)D * num3;
                if (num4 < 300.0 && num4 > 0.0)
                    ++m[(int)num4 / 3];
                lb_N.Items.Add((object)num4);
            }
            chart_N.Series[0].Points.Clear();
            for (int i = 0; i < 100; i++)
                chart_N.Series[0].Points.AddY(m[i]);
            chart_N.ChartAreas[0].AxisX.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.False;
        }

        void FillExp()
        {
            lb_Exp.Items.Clear();
            this.nn_num = 10;
            int z0 = DateTime.Now.Millisecond;
            int n = Convert.ToInt32(nudExp_n.Value);
            int M = Convert.ToInt32(nudExp_M.Value);
            int[] m = new int[100];
            for (int i = 0; i < 100; i++)
                m[i] = 0;
            for (int i = 0; i < n; i++)
            {
                double num1 = -Math.Log(nn(z0)) * (double)M;
                if (num1 < 200.0 && num1 > 0.0)
                    ++m[(int)num1 / 2];
                lb_Exp.Items.Add(num1);
            }
            chart_Exp.Series[0].Points.Clear();
            for (int i = 0; i < 100; i++)
                chart_Exp.Series[0].Points.AddY(m[i]);
            chart_Exp.ChartAreas[0].AxisX.Enabled = System.Windows.Forms.DataVisualization.Charting.AxisEnabled.False;
        }
    }
}
