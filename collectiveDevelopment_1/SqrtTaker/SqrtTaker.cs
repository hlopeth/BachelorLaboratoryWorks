using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Symbolics;

namespace SqrtTaker
{
    class SqrtTaker : ISqrt
    {
        private int _accuracy = 3;
        public string GetSqrt(string espression)
        {
            string result = String.Empty;
            string AddToResult = "";

            espression = espression.Replace('.', ',');
            double num;
            if(Double.TryParse(espression,out num))
            {
                if (num < 0 && num % 1 != 0)
                {
                    espression = espression.Substring(1);
                    AddToResult = "*i";
                }
            }
            espression = espression.Replace(',', '.');


            var expression = Infix.ParseOrUndefined("sqrt(" + espression + ")");


            if (expression == Expression.Undefined)
                throw new SqrtException("Unable to parse expression");

            try
            {
                var sub_result = Evaluate.Evaluate(null, expression);

                if (sub_result.IsReal)
                    if (sub_result.RealValue != 0)
                        {
                            result = "+/- " + sub_result.RealValue.ToString();
                        }
                    else
                        result = "0";
                else if (sub_result.IsComplex)
                    result = sub_result.ComplexValue.Real.ToString() + " + i*" + sub_result.ComplexValue.Imaginary.ToString();
                else
                    result = sub_result.ToString();
            }
            catch (NullReferenceException ex)
            {
                result = Infix.Format(Calculus.Taylor(5, Infix.ParseOrThrow(espression), Infix.ParseOrThrow("1"), expression)) + " + ...";
            }
            int i = 0;

            while (i < result.Length)
            {
                if (result[i] == ',')
                {
                    int j = i+1;
                    for (; j-i < _accuracy && j < result.Length && Char.IsNumber(result[j]); j++)
                    { }
                    i = j + 1;
                    for (; j < result.Length && Char.IsNumber(result[j]); j++)
                    { }
                    if (_accuracy == 0)
                        i = i - 2;
                    result = result.Remove(i, j-i);
                }
                else
                    i++;
            }
            return result + AddToResult;
        }

        public void SetAccur(int accur)
        {
            _accuracy = accur;
        }
    }
}
