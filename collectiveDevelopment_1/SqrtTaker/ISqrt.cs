using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SqrtTaker
{
    class SqrtException : Exception
    {
        public SqrtException(string message) : base(message) {}
    }

    public interface ISqrt
    {
        string GetSqrt(string espression);
        void SetAccur(int accur);
    }

}
