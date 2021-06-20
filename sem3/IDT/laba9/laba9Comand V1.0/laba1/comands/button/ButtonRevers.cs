using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1
{
    class ButtonRevers : Comand
    {
        private laba9Comand WorcingPlace;
        private DataGridView ProcesObj0, ProcesObj1, ProcesObj2;
        private TextBox TObj0, TObj1, TObj2, TObj3, TObj4, TObj5, TObj6;

        public ButtonRevers(laba9Comand wp, ref DataGridView po0, ref DataGridView po1, ref DataGridView po2, ref TextBox Tj0,
            ref TextBox Tj1, ref TextBox Tj2, ref TextBox Tj3, ref TextBox Tj4, ref TextBox Tj5, ref TextBox Tj6)
        {
            this.WorcingPlace = wp;
            this.ProcesObj0 = po0;
            this.ProcesObj1 = po1;
            this.ProcesObj2 = po2;
            this.TObj0 = Tj0;
            this.TObj1 = Tj1;
            this.TObj2 = Tj2;
            this.TObj3 = Tj3;
            this.TObj4 = Tj4;
            this.TObj5 = Tj5;
            this.TObj6 = Tj6;
        }

        public override void execution()
        {
            if (WorcingPlace.pmat1 != null)
            {
                Debug.WriteLine("m1");
                WorcingPlace.N1 = WorcingPlace.pmat1.GetLength(1);
                WorcingPlace.M1 = WorcingPlace.pmat1.GetLength(0);
                ProcesObj0.RowCount = WorcingPlace.M1;
                ProcesObj0.ColumnCount = WorcingPlace.N1;
                TObj3.Text = WorcingPlace.pmat1.GetLength(1).ToString();
                TObj4.Text = WorcingPlace.pmat1.GetLength(0).ToString();
                for (int i = 0; i < WorcingPlace.M1; ++i)
                    for (int j = 0; j < WorcingPlace.N1; ++j)
                        ProcesObj0.Rows[i].Cells[j].Value = WorcingPlace.pmat1[i, j].ToString();
            }

            if (WorcingPlace.pmat2 != null)
            {
                Debug.WriteLine("m2");
                WorcingPlace.N2 = WorcingPlace.pmat2.GetLength(1);
                WorcingPlace.M2 = WorcingPlace.pmat2.GetLength(0);
                ProcesObj1.RowCount = WorcingPlace.M2;
                ProcesObj1.ColumnCount = WorcingPlace.N2;
                TObj5.Text = WorcingPlace.pmat2.GetLength(1).ToString();
                TObj6.Text = WorcingPlace.pmat2.GetLength(0).ToString();
                for (int i = 0; i < WorcingPlace.M2; ++i)
                    for (int j = 0; j < WorcingPlace.N2; ++j)
                        ProcesObj1.Rows[i].Cells[j].Value = WorcingPlace.pmat2[i, j].ToString();
            }

            if (WorcingPlace.mat3 != null)
            {
                Debug.WriteLine("m3");
                WorcingPlace.N3 = WorcingPlace.mat3.GetLength(1);
                WorcingPlace.M3 = WorcingPlace.mat3.GetLength(0);
                ProcesObj2.RowCount = WorcingPlace.M3;
                ProcesObj2.ColumnCount = WorcingPlace.N3;
                for (int i = 0; i < WorcingPlace.M3; ++i)
                    for (int j = 0; j < WorcingPlace.N3; ++j)
                        ProcesObj2.Rows[i].Cells[j].Value = WorcingPlace.mat3[i, j].ToString();
            }

            if (WorcingPlace.pdet1 != null)
            {
                TObj0.Text = WorcingPlace.pdet1;
            }

            if (WorcingPlace.pdet2 != null)
            {
                TObj1.Text = WorcingPlace.pdet2;
            }

            if (WorcingPlace.pdet3 != null)
            {
                TObj2.Text = WorcingPlace.pdet3;
            }
        }
    }
}
