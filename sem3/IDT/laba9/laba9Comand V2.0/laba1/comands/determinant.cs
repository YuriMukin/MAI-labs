using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1
{
    class determinant : Comand
    {
        public override matrix execution(matrix f, matrix s)
        {
            f.CalcDet();
            return f;
        }
    }
}
