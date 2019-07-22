using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MainForm
{
    public partial class Point_Constructor : Form
    {
        public Point_Constructor(int x = 0, int y = 0, int z = 0)
        {
            InitializeComponent();
            nud_x.Value = x;
            nud_y.Value = y;
            nud_z.Value = z;
        }

        public int X
        {
            get { return Convert.ToInt32(nud_x.Value); }
        }

        public int Y
        {
            get { return Convert.ToInt32(nud_y.Value); }
        }

        public int Z
        {
            get { return Convert.ToInt32(nud_z.Value); }
        }
    }
}
