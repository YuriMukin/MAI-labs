using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1
{
    class ButtonCalcClick : Comand
    {
        private laba9Comand WorcingPlace;
        private TextBox WorcObj;
        private DataGridView ProcesObj0;

        public ButtonCalcClick(laba9Comand wp, ref TextBox wj, ref DataGridView po0)
        {
            this.WorcingPlace = wp;
            this.WorcObj = wj;
            this.ProcesObj0 = po0;
        }

        public override void execution()
        {
            if (WorcObj.Text == "!")
            {
                WorcingPlace.m3 = !WorcingPlace.m1;
                revrite();
            }
            else if (WorcObj.Text == "+")
            {
                WorcingPlace.m3 = WorcingPlace.m1 + WorcingPlace.m2;
                revrite();
            }
            else if (WorcObj.Text == "*")
            {
                WorcingPlace.m3 = WorcingPlace.m1 * WorcingPlace.m2;
                revrite();
            }
        }

        public void revrite()
        {
            for (int i = 0; i < WorcingPlace.N3; ++i)
                for (int j = 0; j < WorcingPlace.M3; ++j)
                    ProcesObj0.Rows[i].Cells[j].Value = WorcingPlace.m3.mat[i, j];
        }
    }
}
