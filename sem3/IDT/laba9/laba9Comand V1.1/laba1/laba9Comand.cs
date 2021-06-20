using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace laba1
{
    public partial class laba9Comand : Form
    {
        public int N1, M1, N2, M2, N3, M3;
        public double[,] mat1, mat2, mat3, pmat1, pmat2;
        public string pdet1, pdet2, pdet3;
        public matrix m1, m2, m3;

        Comand  BC1, BC2, BC3;
        helper TC1, TC2, TC3, TC4;

        public laba9Comand()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.N1 = 0;
            this.M1 = 0;
            this.N2 = 0;
            this.M2 = 0;
            this.N3 = 0;
            this.M3 = 0;
            this.mat1 = null;
            this.mat2 = null;
            this.mat3 = null;
            this.pdet1 = null;
            this.pdet2 = null;
            this.pdet3 = null;
            this.TC1 = new TextChangeTBN1(this, ref this.textBox1N, ref this.dataGridView1);
            this.TC2 = new TextChangeTBM1(this, ref this.textBox1M, ref this.dataGridView1);
            this.TC3 = new TextChangeTBM2(this, ref this.textBox2M, ref this.dataGridView2);
            this.TC4 = new TextChangeTBN2(this, ref this.textBox2N, ref this.dataGridView2);
            this.BC1 = new ButtonCalcClick(this, ref this.textBoxOp, ref dataGridView3);
            this.BC2 = new ButtonCalckDet(this, ref this.checkedListBox1, ref this.dataGridView1, ref this.dataGridView2, ref this.dataGridView3,
                ref this.textBox1, ref this.textBox2, ref this.textBox3);
            this.BC3 = new ButtonRevers(this, ref this.dataGridView1, ref this.dataGridView2, ref this.dataGridView3,
                ref this.textBox1, ref this.textBox2, ref this.textBox3, ref this.textBox1N, ref this.textBox1M, ref this.textBox2N, ref this.textBox2M);
        }

        private void textBox1N_TextChanged(object sender, EventArgs e)
        {
            TC1.execution();
        }

        private void textBox1M_TextChanged(object sender, EventArgs e)
        {
            TC2.execution();
        }

        private void textBox2M_TextChanged(object sender, EventArgs e)
        {
            TC3.execution();
        }

        private void textBox2N_TextChanged(object sender, EventArgs e)
        {
            TC4.execution();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            preprocess(textBoxOp.Text);
            BC1.execution();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            BC2.execution();
        }

        private void revers_Click(object sender, EventArgs e)
        {
            BC3.execution();
        }

        public void preprocess(string wtb)
        {
            if (wtb == "!" && N1 != 0 && M1 != 0)
            {
                prepairMat1();
                dataGridView3.RowCount = N1;
                N3 = N1;
                dataGridView3.ColumnCount = M1;
                M3 = M1;
            }
            else if (wtb == "+" && N1 == N2 && M1 == M2 && N1 != 0 && M1 != 0)
            {
                prepairMat1();
                prepairMat2();
                dataGridView3.RowCount = M1;
                N3 = N1;
                dataGridView3.ColumnCount = N1;
                M3 = M1;

            }
            else if (wtb == "*" && N1 == M2 && N1 != 0 && M1 != 0 && N2 != 0)
            {
                prepairMat1();
                prepairMat2();
                dataGridView3.RowCount = M1;
                N3 = M1;
                dataGridView3.ColumnCount = N2;
                M3 = N2;
            }
        }

        public void prepairMat1()
        {
            pmat1 = mat1;
            mat1 = new double[M1, N1];
            for (int i = 0; i < M1; ++i)
                for (int j = 0; j < N1; ++j)
                    mat1[i, j] = Convert.ToSingle(dataGridView1.Rows[i].Cells[j].Value);
            m1 = new matrix(M1, N1, mat1);
            if (M3 != 0 && N3 != 0)
            {
                mat3 = new double[M3, N3];
                for (int i = 0; i < M3; ++i)
                    for (int j = 0; j < N3; ++j)
                        mat3[i, j] = Convert.ToDouble(dataGridView3.Rows[i].Cells[j].Value);
            }
        }

        public void prepairMat2()
        {
            pmat2 = mat2;
            mat2 = new double[M2, N2];
            for (int i = 0; i < M2; ++i)
                for (int j = 0; j < N2; ++j)
                    mat2[i, j] = Convert.ToSingle(dataGridView2.Rows[i].Cells[j].Value);
            m2 = new matrix(M2, N2, mat2);
            if (M3 != 0 && N3 != 0)
            {
                mat3 = new double[M3, N3];
                for (int i = 0; i < M3; ++i)
                    for (int j = 0; j < N3; ++j)
                        mat3[i, j] = Convert.ToDouble(dataGridView3.Rows[i].Cells[j].Value);
            }
        }
    }
}
