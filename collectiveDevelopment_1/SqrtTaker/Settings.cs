using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace SqrtTaker
{
    public partial class Settings : Form
    {
        private List<string> lang_files = new List<string>();
        ILanguage select_lang = new Language();
        private MainForm parentOfForm;
        public Settings(MainForm parent)
        {
            InitializeComponent();
            bt_appl.Enabled = false;
            string folder = @"..\..\Languages";        
            string[] files = Directory.GetFiles(folder, "*.txt");
            foreach (string file in files)
            {
                try
                {
                    StreamReader file_lang = new StreamReader(file);
                    if (file_lang.ReadLine() == "SQRT")
                    {                        
                        cb_language.Items.Add(file_lang.ReadLine());
                        lang_files.Add(file);                        
                    }
                }
                catch(Exception ex)
                { }
            }
            if (files.Length == 0)
            {
                MessageBox.Show("Не найден ни один локализационный файл");
                return;
            }
            cb_language.SelectedIndex = lang_files.FindIndex(x => x.Contains(parent.selectedLang));
            parentOfForm = parent;
            change_names(parentOfForm.selectedLang);
            if (cb_language.Items.Count>0)
                bt_appl.Enabled = true;
        }

      
        private void change_name(string new_name)
        {
            this.Text = new_name;
        }
        private void change_names(string file_lang)
        {
            select_lang.selectlanguage(file_lang);
            Dictionary<string, string> names = select_lang.get_new_lang();
            change_name(names["Settings"]);
            gb_lang.Text = names["Language"];
            gb_accu.Text = names["Accuracy"];
            bt_appl.Text = names["Apply"];
            bt_exit.Text = names["Exit"];
        }
        private void bt_appl_Click(object sender, EventArgs e)
        {                        
            string fileName = lang_files[cb_language.SelectedIndex];
            change_names(fileName);
            parentOfForm.changeSelctLang(fileName);
            parentOfForm.change_names();            
        }

        

        private void bt_exit_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void nUD_accu_ValueChanged(object sender, EventArgs e)
        {
            parentOfForm._sqrtTaker.SetAccur(Convert.ToInt32(nUD_accu.Value));
        }
    }
}
