using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormsControlLib
{
    public partial class NumTb : TextBox
    {
        string State;
        public Int32 color = 0;
        public NumTb()
        {
            InitializeComponent();
            this.Text = "0";
            this.color = 0;
            State = "D";
        }
        
        public NumTb(IContainer container)
        {
            container.Add(this);

            InitializeComponent();
            this.Text = "0";
            this.color = 0;
            State = "D";
        }

        bool IsDigitHex(char ch)
        {
            string s = "ABCDEFabcdef";
            return char.IsDigit(ch) || s.Contains(ch);
        }
        protected override void OnKeyPress(KeyPressEventArgs e)
        {
            if (State == "D")
            {
                if (!char.IsDigit(e.KeyChar) && !char.IsControl((e.KeyChar)))
                    e.Handled = true;
                base.OnKeyPress(e);
            }
            else
            {
                if (!IsDigitHex(e.KeyChar) && !char.IsControl((e.KeyChar)))
                    e.Handled = true;
                base.OnKeyPress(e);
            }
        }
       
        public void SetState(string st)
        {
            if (st == "H" && State == "D")
            { State = st; this.Text = /*Convert.ToUInt32(this.Text)*/color.ToString("X"); }
            if (st == "D" && State == "H")
            { State = st; this.Text = /*Convert.ToUInt32(this.Text, 16)*/color.ToString(); }
        }
        protected override void OnTextChanged(EventArgs e)
        {
            Int32 backupColor = color;
            try
            {
                if (State == "D")
                {
                    color = Convert.ToInt32(this.Text);
                }
                else
                {
                    color = Convert.ToInt32(this.Text, 16);
                }
            }
            catch
            { color = backupColor; }
            base.OnTextChanged(e);
        }

        protected override void OnValidating(CancelEventArgs e)
        {
            try
            {
                if (String.IsNullOrEmpty(this.Text))
                    this.Text = "0";
                if (State == "D")
                {
                    if (Convert.ToUInt32(this.Text) > 255)
                        e.Cancel = true;
                    else
                        e.Cancel = false;
                }
                else
                {
                    if (Convert.ToUInt32(this.Text, 16) > 255)
                        e.Cancel = true;
                    else
                        e.Cancel = false;
                }
            }
            catch
            { e.Cancel = false; }
            base.OnValidating(e);
        }
        
    }
}
