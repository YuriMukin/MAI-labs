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

        Comand TC1, TC2, TC3, TC4, BC1, BC2, BC3;

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
            this.BC1 = new ButtonCalcClick(this, ref this.textBoxOp, ref this.dataGridView1, ref this.dataGridView2, ref this.dataGridView3);
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
    }
}
