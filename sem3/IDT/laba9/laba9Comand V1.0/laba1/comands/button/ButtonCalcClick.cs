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
        private DataGridView ProcesObj0, ProcesObj1, ProcesObj2;

        public ButtonCalcClick(laba9Comand wp, ref TextBox wj, ref DataGridView po0, ref DataGridView po1, ref DataGridView po2)
        {
            this.WorcingPlace = wp;
            this.WorcObj = wj;
            this.ProcesObj0 = po0;
            this.ProcesObj1 = po1;
            this.ProcesObj2 = po2;
        }

        public override void execution()
        {
            if (ChecIn(1) == true)
            {
                if (WorcObj.Text == "!")
                    transpos();
                if (WorcObj.Text == "+")
                    if (ChecIn(2) == true)
                        summ();
                    else
                        MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                if (WorcObj.Text == "*")
                    if (ChecIn(2) == true)
                        comp();
                    else
                        MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
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

        public void transpos()
        {
            double[,] mas = new double[WorcingPlace.M1, WorcingPlace.N1];
            for (int i = 0; i < WorcingPlace.M1; ++i)
                for (int j = 0; j < WorcingPlace.N1; ++j)
                    mas[i, j] = Convert.ToSingle(ProcesObj0.Rows[i].Cells[j].Value);
            WorcingPlace.pmat1 = WorcingPlace.mat1;
            WorcingPlace.mat1 = mas;
            if (WorcingPlace.M3 != 0 && WorcingPlace.N3 != 0)
            {
                WorcingPlace.mat3 = new double[WorcingPlace.M3, WorcingPlace.N3];
                for (int i = 0; i < WorcingPlace.M3; ++i)
                    for (int j = 0; j < WorcingPlace.N3; ++j)
                        WorcingPlace.mat3[i, j] = Convert.ToDouble(ProcesObj2.Rows[i].Cells[j].Value);
            }
            var mat = new matrix(WorcingPlace.M1, WorcingPlace.N1, mas);
            matrix res = !mat;
            ProcesObj2.RowCount = WorcingPlace.N1;
            WorcingPlace.N3 = WorcingPlace.N1;
            ProcesObj2.ColumnCount = WorcingPlace.M1;
            WorcingPlace.M3 = WorcingPlace.M1;
            for (int i = 0; i < WorcingPlace.N1; ++i)
                for (int j = 0; j < WorcingPlace.M1; ++j)
                    ProcesObj2.Rows[i].Cells[j].Value = res.mat[i, j];
        }

        public void summ()
        {
            double[,] mas0 = new double[WorcingPlace.M1, WorcingPlace.N1];
            double[,] mas1 = new double[WorcingPlace.M2, WorcingPlace.N2];
            for (int i = 0; i < WorcingPlace.M1; ++i)
                for (int j = 0; j < WorcingPlace.N1; ++j)
                    mas0[i, j] = Convert.ToDouble(ProcesObj0.Rows[i].Cells[j].Value);
            WorcingPlace.pmat1 = WorcingPlace.mat1;
            WorcingPlace.mat1 = mas0;
            for (int i = 0; i < WorcingPlace.M2; ++i)
                for (int j = 0; j < WorcingPlace.N2; ++j)
                    mas1[i, j] = Convert.ToDouble(ProcesObj1.Rows[i].Cells[j].Value);
            WorcingPlace.pmat2 = WorcingPlace.mat2;
            WorcingPlace.mat2 = mas1;
            if (WorcingPlace.M3 != 0 && WorcingPlace.N3 != 0)
            {
                WorcingPlace.mat3 = new double[WorcingPlace.M3, WorcingPlace.N3];
                for (int i = 0; i < WorcingPlace.M3; ++i)
                    for (int j = 0; j < WorcingPlace.N3; ++j)
                        WorcingPlace.mat3[i, j] = Convert.ToDouble(ProcesObj2.Rows[i].Cells[j].Value);
            }
            var mat0 = new matrix(WorcingPlace.M1, WorcingPlace.N1, mas0);
            var mat1 = new matrix(WorcingPlace.M2, WorcingPlace.N2, mas1);
            if ((mat1.IsSameM(mat0)) && (mat1.IsSameN(mat0)))
            {
                matrix res = mat0 + mat1;
                ProcesObj2.RowCount = WorcingPlace.M1;
                WorcingPlace.N3 = WorcingPlace.N1;
                ProcesObj2.ColumnCount = WorcingPlace.N1;
                WorcingPlace.M3 = WorcingPlace.M1;
                for (int i = 0; i < WorcingPlace.M1; ++i)
                    for (int j = 0; j < WorcingPlace.N1; ++j)
                        ProcesObj2.Rows[i].Cells[j].Value = res.mat[i, j];
            }
            else
                MessageBox.Show("these matrices cannot be folded",
                        "Attention", MessageBoxButtons.OK, MessageBoxIcon.Question);
        }

        public void comp()
        {
            double[,] mas0 = new double[WorcingPlace.M1, WorcingPlace.N1];
            double[,] mas1 = new double[WorcingPlace.M2, WorcingPlace.N2];
            for (int i = 0; i < WorcingPlace.M1; ++i)
                for (int j = 0; j < WorcingPlace.N1; ++j)
                    mas0[i, j] = Convert.ToDouble(ProcesObj0.Rows[i].Cells[j].Value);
            WorcingPlace.pmat1 = WorcingPlace.mat1;
            WorcingPlace.mat1 = mas0;
            for (int i = 0; i < WorcingPlace.M2; ++i)
                for (int j = 0; j < WorcingPlace.N2; ++j)
                    mas1[i, j] = Convert.ToDouble(ProcesObj1.Rows[i].Cells[j].Value);
            WorcingPlace.pmat2 = WorcingPlace.mat2;
            WorcingPlace.mat2 = mas1;
            var mat0 = new matrix(WorcingPlace.M1, WorcingPlace.N1, mas0);
            var mat1 = new matrix(WorcingPlace.M2, WorcingPlace.N2, mas1);
            if (WorcingPlace.M3 != 0 && WorcingPlace.N3 != 0)
            {
                WorcingPlace.mat3 = new double[WorcingPlace.M3, WorcingPlace.N3];
                for (int i = 0; i < WorcingPlace.M3; ++i)
                    for (int j = 0; j < WorcingPlace.N3; ++j)
                        WorcingPlace.mat3[i, j] = Convert.ToDouble(ProcesObj2.Rows[i].Cells[j].Value);
            }
            if (WorcingPlace.N1 == WorcingPlace.M2)
            {
                matrix res = mat0 * mat1;
                ProcesObj2.RowCount = WorcingPlace.M1;
                WorcingPlace.N3 = WorcingPlace.M1;
                ProcesObj2.ColumnCount = WorcingPlace.N2;
                WorcingPlace.M3 = WorcingPlace.N2;
                for (int i = 0; i < WorcingPlace.M1; ++i)
                    for (int j = 0; j < WorcingPlace.N2; ++j)
                        ProcesObj2.Rows[i].Cells[j].Value = res.mat[i, j];
            }
            else if (WorcingPlace.M1 == WorcingPlace.N2)
            {
                DialogResult result = MessageBox.Show("matrices cannot be multiplied in that order, try to multiply matrices in a different order?",
                    "Attention", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (result == DialogResult.Yes)
                {
                    matrix res = mat1 * mat0;
                    ProcesObj2.RowCount = WorcingPlace.N2;
                    WorcingPlace.N3 = WorcingPlace.N2;
                    ProcesObj2.ColumnCount = WorcingPlace.M1;
                    WorcingPlace.M3 = WorcingPlace.M1;
                    for (int i = 0; i < WorcingPlace.N2; ++i)
                        for (int j = 0; j < WorcingPlace.M1; ++j)
                            ProcesObj2.Rows[i].Cells[j].Value = res.mat[i, j];
                }
            }
        }

    }
}
