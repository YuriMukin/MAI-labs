using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1
{
    class preprocessingCalc : helper
    {
        private laba9Comand WorcingPlace;
        private TextBox WorcObj;
        private DataGridView ProcesObj0, ProcesObj1, ProcesObj2;

        public preprocessingCalc(laba9Comand wp, ref TextBox wj, ref DataGridView po0, ref DataGridView po1, ref DataGridView po2)
        {
            this.WorcingPlace = wp;
            this.WorcObj = wj;
            this.ProcesObj0 = po0;
            this.ProcesObj1 = po1;
            this.ProcesObj2 = po2;
        }

        public override void execution()
        {
            if ((ChecIn(1) == true) && (WorcingPlace.N1 != 0) && (WorcingPlace.M1 != 0))
            {
                if ((WorcObj.Text == "!"))
                {
                    prepairMat1();
                    ProcesObj2.RowCount = WorcingPlace.N1;
                    WorcingPlace.N3 = WorcingPlace.N1;
                    ProcesObj2.ColumnCount = WorcingPlace.M1;
                    WorcingPlace.M3 = WorcingPlace.M1;
                }
                if (WorcObj.Text == "+")
                    if ((ChecIn(2) == true)&&(WorcingPlace.M1 == WorcingPlace.M2)&&(WorcingPlace.N1 == WorcingPlace.N2))
                    {
                        prepairMat1();
                        prepairMat2();
                        ProcesObj2.RowCount = WorcingPlace.M1;
                        WorcingPlace.N3 = WorcingPlace.N1;
                        ProcesObj2.ColumnCount = WorcingPlace.N1;
                        WorcingPlace.M3 = WorcingPlace.M1;
                    }
                    else
                        MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                if (WorcObj.Text == "*")
                    if ((ChecIn(2) == true) && (WorcingPlace.N1 == WorcingPlace.M2) &&(WorcingPlace.N2 != 0))
                    {
                        prepairMat1();
                        prepairMat2();
                        ProcesObj2.RowCount = WorcingPlace.M1;
                        WorcingPlace.N3 = WorcingPlace.N2;
                        ProcesObj2.ColumnCount = WorcingPlace.N2;
                        WorcingPlace.M3 = WorcingPlace.M1;
                    }
                    else
                        MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        public void prepairMat1()
        {
            WorcingPlace.pmat1 = WorcingPlace.mat1;
            WorcingPlace.mat1 = new double[WorcingPlace.M1, WorcingPlace.N1];
            for (int i = 0; i < WorcingPlace.M1; ++i)
                for (int j = 0; j < WorcingPlace.N1; ++j)
                    WorcingPlace.mat1[i, j] = Convert.ToSingle(ProcesObj0.Rows[i].Cells[j].Value);
            WorcingPlace.m1 = new matrix(WorcingPlace.M1, WorcingPlace.N1, WorcingPlace.mat1);
            if (WorcingPlace.M3 != 0 && WorcingPlace.N3 != 0)
            {
                WorcingPlace.mat3 = new double[WorcingPlace.M3, WorcingPlace.N3];
                for (int i = 0; i < WorcingPlace.M3; ++i)
                    for (int j = 0; j < WorcingPlace.N3; ++j)
                        WorcingPlace.mat3[i, j] = Convert.ToDouble(ProcesObj2.Rows[i].Cells[j].Value);
            }
        }

        public void prepairMat2()
        {
            WorcingPlace.pmat2 = WorcingPlace.mat2;
            WorcingPlace.mat2 = new double[WorcingPlace.M2, WorcingPlace.N2];
            for (int i = 0; i < WorcingPlace.M2; ++i)
                for (int j = 0; j < WorcingPlace.N2; ++j)
                    WorcingPlace.mat2[i, j] = Convert.ToSingle(ProcesObj1.Rows[i].Cells[j].Value);
            WorcingPlace.m2 = new matrix(WorcingPlace.M2, WorcingPlace.N2, WorcingPlace.mat2);
            if (WorcingPlace.M3 != 0 && WorcingPlace.N3 != 0)
            {
                WorcingPlace.mat3 = new double[WorcingPlace.M3, WorcingPlace.N3];
                for (int i = 0; i < WorcingPlace.M3; ++i)
                    for (int j = 0; j < WorcingPlace.N3; ++j)
                        WorcingPlace.mat3[i, j] = Convert.ToDouble(ProcesObj2.Rows[i].Cells[j].Value);
            }
        }

        public bool ChecIn(int c)
        {
            int k;
            double tm;
            if (c == 1)
            {
                k = 0;
                for (int i = 0; i < WorcingPlace.M1; ++i)
                    for (int j = 0; j < WorcingPlace.N1; ++j)
                    {
                        string tmp = (string)ProcesObj0.Rows[i].Cells[j].Value;
                        if (!double.TryParse(tmp, out tm))
                            k++;
                    }
                return (k == 0);
            }
            else
            {
                k = 0;
                for (int i = 0; i < WorcingPlace.M2; ++i)
                    for (int j = 0; j < WorcingPlace.N2; ++j)
                    {
                        string tmp = (string)ProcesObj1.Rows[i].Cells[j].Value;
                        if (!double.TryParse(tmp, out tm))
                            k++;
                    }
                return (k == 0);
            }
        }
    }
}
