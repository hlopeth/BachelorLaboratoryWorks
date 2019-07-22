using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;


namespace SqrtTaker
{
    class Language:ILanguage
    {
        
        Dictionary<string, string> Interface;
        string tempalte_int = @"..\..\Template.txt";
       
        void ILanguage.selectlanguage(string path)
        {
            if(Interface!=null)
                Interface.Clear();
            Interface = new Dictionary<string, string>();
            if (!File.Exists(path))
            {
                MessageBox.Show("Файл настроек языка не существует");
                return;
            }
            
            if (!File.Exists(tempalte_int))
            {
                MessageBox.Show("Файл с шаблонами инетерфейса не существует");
                return;
            }
            StreamReader file_lang = new StreamReader(path);
            file_lang.ReadLine();
            file_lang.ReadLine();
            StreamReader file_tmpl = new StreamReader(tempalte_int);
            while (file_tmpl.Peek()>=0)
            {
                Interface.Add(file_tmpl.ReadLine(), file_lang.ReadLine());
            }
            
        }
        Dictionary<string, string> ILanguage.get_new_lang()
        {
            return Interface;
        }
    }
}
