using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MathNet.Symbolics;
using System.Linq.Expressions;
using System.Diagnostics;

namespace SqrtTaker
{
    public partial class MainForm : Form
    {
        public ISqrt _sqrtTaker;
        private ILanguage _selectLang = new Language();
        private string _selectedLang;
        public MainForm()
        {
            InitializeComponent();
            _selectedLang = @"..\..\Languages\Rus.txt";
            _selectLang.selectlanguage(_selectedLang);
			_sqrtTaker = new SqrtTaker();
        }
        public string selectedLang
        {
            get
            {
                return _selectedLang;
            }
        }
        private void bt_GetSqrt_Click(object sender, EventArgs e)
        {
            string expression = tb_num.Text;
            string result = String.Empty;
            if (!String.IsNullOrWhiteSpace(expression))
            {
                try
                {
                    result = _sqrtTaker.GetSqrt(expression);
                }
                catch (Exception)
                {
                    result = _selectLang.get_new_lang()["Invalid input"];
                }
            }
            else
                result = _selectLang.get_new_lang()["Empty Str"];

            tb_result.Text = result;
        }
        public void changeSelctLang(string selectLang)
        {
            _selectedLang = selectLang;
            _selectLang.selectlanguage(_selectedLang);
        }
        void changeNameForm(string new_name)
        {
            this.Text = new_name;
        }
        MainForm this_form()
        {
            return this;
        }
        public void change_names()
        {
            _selectLang.selectlanguage(_selectedLang);
            Dictionary<string, string> names = _selectLang.get_new_lang();
            changeNameForm(names["Form name"]);
            gb_num.Text = names["Original number"];
            gb_result.Text = names["Root"];
            bt_GetSqrt.Text = names["TakeSQRT"];
            ToolStripMenuItem_menu.Text = names["Menu"];
            ToolStripMenuItem_exit.Text = names["Exit"];
            ToolStripMenuItem_settings.Text = names["Settings"];
            ToolStripMenuItem_documentation.Text = names["Documentation"];
            //Должны быть глоб переменные для хранения типов ошибок или что-то подобное.  Ниже приведены заготовки поз заполнения переменных.
            // = names["Empty Str"]; //Пустая строка
            // = names["Invalid input"]; //Неверный ввод
        }
        private void настройкиToolStripMenuItem_Click(object sender, EventArgs e)
        {
            var form_setting = new Settings(this_form());
            form_setting.ShowDialog();            
        }

        private void ToolStripMenuItem_exit_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void ToolStripMenuItem_documentation_Click(object sender, EventArgs e)
        {
            Process.Start(@"..\..\Languages\Руководство пользователя.pdf");
        }
    }
}
