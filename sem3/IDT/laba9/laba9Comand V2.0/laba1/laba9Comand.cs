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

        Comand add, ml, tr, dt;
        helper TC1, TC2, TC3, TC4, BC3, PCC, PCD, VZ;

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
            this.m1 = null;
            this.m2 = null;
            this.m3 = null;
            this.pdet1 = null;
            this.pdet2 = null;
            this.pdet3 = null;
            this.add = new addition();
            this.ml = new multiplication();
            this.tr = new transpose();
            this.dt = new determinant();
            this.TC1 = new TextChangeTBN1(this, ref this.textBox1N, ref this.dataGridView1);
            this.TC2 = new TextChangeTBM1(this, ref this.textBox1M, ref this.dataGridView1);
            this.TC3 = new TextChangeTBM2(this, ref this.textBox2M, ref this.dataGridView2);
            this.TC4 = new TextChangeTBN2(this, ref this.textBox2N, ref this.dataGridView2);
            this.PCC = new preprocessingCalc(this, ref this.textBoxOp, ref this.dataGridView1, ref this.dataGridView2, ref this.dataGridView3);
            this.PCD = new preprocessingDet(this, ref this.checkedListBox1, ref this.dataGridView1, ref this.dataGridView2, ref this.dataGridView3);
            this.VZ = new visualizer(this, ref this.dataGridView3);
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
            PCC.execution();
            CalcCoal();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            PCD.execution();
            for (int i = 0; i < 3; i++)
                if (checkedListBox1.GetItemChecked(i))
                    DetCoal(i);
        }

        private void revers_Click(object sender, EventArgs e)
        {
            BC3.execution();
        }

        private void CalcCoal()
        {
            if (this.textBoxOp.Text == "!" && N1 != 0 && M1 != 0)
            {
                m3=tr.execution(m1,null);
                VZ.execution();
            }
            else if (this.textBoxOp.Text == "+" && N1 == N2 && M1 == M2 && N1 != 0 && M1 != 0)
            {
                m3 = add.execution(m1, m2);
                VZ.execution();
            }
            else if (this.textBoxOp.Text == "*" && N1 == M2 && N1 != 0 && M1 != 0 && N2 != 0)
            {
                m3 = ml.execution(m1, m2);
                VZ.execution();
            }
        }

        private void DetCoal(int i)
        {
            if (i == 0 && N1 == M1 && N1!=0)
            {
                m1 = dt.execution(m1, null);
                textBox2.Text = m1.det.ToString();
            }
            if (i == 1 && N2 == M2 && N2!=0)
            {
                m2 = dt.execution(m2, null);
                textBox1.Text = m2.det.ToString();
            }
            if (i == 2 && N3 == M3 && N3!=0)
            {
                m3 = dt.execution(m3, null);
                textBox3.Text = m3.det.ToString();
            }
        }
    }
}
