using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1
{
    class ButtonCalckDet : Comand
    {
        private laba9Comand WorcingPlace;
        private CheckedListBox WorcObj;
        private DataGridView ProcesObj0, ProcesObj1, ProcesObj2;
        private TextBox TObj0, TObj1, TObj2;

        public ButtonCalckDet(laba9Comand wp, ref CheckedListBox wj, ref DataGridView po0, ref DataGridView po1, ref DataGridView po2, 
            ref TextBox Tj0, ref TextBox Tj1, ref TextBox Tj2)
        {
            this.WorcingPlace = wp;
            this.WorcObj = wj;
            this.ProcesObj0 = po0;
            this.ProcesObj1 = po1;
            this.ProcesObj2 = po2;
            this.TObj0 = Tj0;
            this.TObj1 = Tj1;
            this.TObj2 = Tj2;
        }

        public override void execution()
        {
            WorcingPlace.pdet1 = TObj0.Text;
            TObj0.Text = "";
            WorcingPlace.pdet2 = TObj1.Text;
            TObj1.Text = "";
            WorcingPlace.pdet3 = TObj2.Text;
            TObj2.Text = "";
            for (int i = 0; i < 3; i++)
                if (WorcObj.GetItemChecked(i))
                    calcDet(i);
        }

        public void calcDet(int l)
        {
            if (l == 0)
                if (((WorcingPlace.N1 != 0) && (WorcingPlace.M1 != 0)) && (WorcingPlace.N1 == WorcingPlace.M1))
                {
                    double[,] mas = new double[WorcingPlace.M1, WorcingPlace.N1];
                    for (int i = 0; i < WorcingPlace.M1; ++i)
                        for (int j = 0; j < WorcingPlace.N1; ++j)
                            mas[i, j] = Convert.ToSingle(ProcesObj0.Rows[i].Cells[j].Value);
                    var mat = new matrix(WorcingPlace.M1, WorcingPlace.N1, mas);
                    TObj1.Text = mat.CalculateDeterminant().ToString();
                }
                else
                    TObj1.Text = "Non";


            if (l == 1)
                if (((WorcingPlace.N2 != 0) && (WorcingPlace.M2 != 0)) && (WorcingPlace.N2 == WorcingPlace.M2))
                {
                    double[,] mas = new double[WorcingPlace.M2, WorcingPlace.N2];
                    for (int i = 0; i < WorcingPlace.M2; ++i)
                        for (int j = 0; j < WorcingPlace.N2; ++j)
                            mas[i, j] = Convert.ToSingle(ProcesObj1.Rows[i].Cells[j].Value);
                    var mat = new matrix(WorcingPlace.M2, WorcingPlace.N2, mas);
                    TObj0.Text = mat.CalculateDeterminant().ToString();
                }
                else
                    TObj0.Text = "Non";

            if (l == 2)
                if ((WorcingPlace.N3 != 0) && (WorcingPlace.M3 != 0) && (WorcingPlace.N3 == WorcingPlace.M3))
                {
                    double[,] mas = new double[WorcingPlace.M3, WorcingPlace.N3];
                    for (int i = 0; i < WorcingPlace.M3; ++i)
                        for (int j = 0; j < WorcingPlace.N3; ++j)
                            mas[i, j] = Convert.ToSingle(ProcesObj2.Rows[i].Cells[j].Value);
                    var mat = new matrix(WorcingPlace.M3, WorcingPlace.N3, mas);
                    TObj2.Text = mat.CalculateDeterminant().ToString();
                }
                else
                    TObj2.Text = "Non";
        }
    }
}
