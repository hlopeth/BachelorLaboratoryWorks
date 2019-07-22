using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SqrtTaker
{
    interface ILanguage
    {
        void selectlanguage(string path);
        Dictionary<string, string> get_new_lang();

    }
}
