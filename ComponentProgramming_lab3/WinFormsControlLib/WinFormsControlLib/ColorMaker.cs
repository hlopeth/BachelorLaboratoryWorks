using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Globalization;
using System.Numerics;

namespace WinFormsControlLib
{
    public partial class ColorMaker : UserControl
    {
        Int32 red = 0;
        Int32 green = 0;
        Int32 blue = 0;
        public ColorMaker()
        {
            InitializeComponent();
        }

        bool IsDigitHex(char ch)
        {
            string s = "ABCDEFabcdef";
            return char.IsDigit(ch) || s.Contains(ch); 
        }

        private void ColorMaker_Load(object sender, EventArgs e)
        {

        }
        
        

        private void rb_Hex_CheckedChanged(object sender, EventArgs e)
        {
            if (rb_Hex.Checked)
            {
                numTb_Red.SetState("H");
                numTb_Green.SetState("H");
                numTb_Blue.SetState("H");
            }
        }

        private void rb_Dec_CheckedChanged(object sender, EventArgs e)
        {
           if (rb_Dec.Checked)
            {
                numTb_Red.SetState("D");
                numTb_Green.SetState("D");
                numTb_Blue.SetState("D");
            }
        }
        
        
        
        

        private void numTb_Red_TextChanged(object sender, EventArgs e)
        {
            try
            {

                if (numTb_Red.color <= 255)
                {
                    red = numTb_Red.color;
                    pb_Color.BackColor = Color.FromArgb(red, green, blue);
                }
            }
            catch
            { }
        }

        private void numTb_Green_TextChanged(object sender, EventArgs e)
        {
            try
            {

                if (numTb_Green.color <= 255)
                {
                    green = numTb_Green.color;
                    pb_Color.BackColor = Color.FromArgb(red, green, blue);
                }
            }
            catch
            { }
        }

        private void numTb_Blue_TextChanged(object sender, EventArgs e)
        {
            try
            {

                if (numTb_Blue.color <= 255)
                {
                    blue = numTb_Blue.color;
                    pb_Color.BackColor = Color.FromArgb(red, green, blue);
                }
            }
            catch
            { }
        }
    }
}
