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
    public partial class Form1 : Form
    {
        public static int N1, M1, N2, M2, N3, M3;
        public Form1()
        {
            InitializeComponent();
        }

        private void textBox1N_TextChanged(object sender, EventArgs e)
        {
            if (textBox1N.Text.All(char.IsDigit) && textBox1N.Text != "")
            {
                dataGridView1.ColumnCount = Int32.Parse(textBox1N.Text);
                N1 = Int32.Parse(textBox1N.Text);
            }
            else if (textBox1N.Text != "")
            {
                textBox1N.Text = textBox1N.Text.Substring(0, (textBox1N.Text.Length - 1));
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void textBox1M_TextChanged(object sender, EventArgs e)
        {
            if (textBox1M.Text.All(char.IsDigit) && textBox1M.Text != "")
            {
                dataGridView1.RowCount = Int32.Parse(textBox1M.Text);
                M1 = Int32.Parse(textBox1M.Text);
            }
            else if (textBox1M.Text != "")
            {
                textBox1M.Text = textBox1M.Text.Substring(0, (textBox1M.Text.Length - 1));
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void textBox2M_TextChanged(object sender, EventArgs e)
        {
            if (textBox2M.Text.All(char.IsDigit) && textBox2M.Text != "")
            {
                dataGridView2.RowCount = Int32.Parse(textBox2M.Text);
                M2 = Int32.Parse(textBox2M.Text);
            }
            else if (textBox2M.Text != "")
            {
                textBox1N.Text = textBox2M.Text.Substring(0, (textBox2M.Text.Length - 1));
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }


        private void textBox2N_TextChanged(object sender, EventArgs e)
        {
            if (textBox2N.Text.All(char.IsDigit) && textBox2N.Text != "")
            {
                dataGridView2.ColumnCount = Int32.Parse(textBox2N.Text);
                N2 = Int32.Parse(textBox2N.Text);
            }
            else if (textBox2N.Text != "")
            {
                textBox1N.Text = textBox2N.Text.Substring(0, (textBox2N.Text.Length - 1));
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            dataGridView1.RowCount = M1;
            dataGridView1.ColumnCount = N1;
        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            dataGridView2.RowCount = M2;
            dataGridView2.ColumnCount = N2;
        }

        private void dataGridView1_EditingControlShowing(object sender, DataGridViewEditingControlShowingEventArgs e)
        {

        }

        private void dataGridView3_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            dataGridView3.RowCount = 0;
            dataGridView3.ColumnCount = 0;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            N1 = 0;
            M1 = 0;
            N2 = 0;
            M2 = 0;
            N3 = 0;
            M3 = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (ChecIn(1) == true)
            {
                if (textBoxOp.Text == "!")
                    transpos();
                if (textBoxOp.Text == "+")
                    if (ChecIn(2) == true)
                        summ();
                    else
                        MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                if (textBoxOp.Text == "*")
                    if (ChecIn(2) == true)
                        comp();
                    else
                        MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox2.Text = "";
            textBox1.Text = "";
            textBox3.Text = "";
            for (int i = 0; i < 3; i++)
                if (checkedListBox1.GetItemChecked(i))
                    calcDet(i);
        }

        public bool ChecIn(int c)
        {
            int k;
            double tm;
            if (c == 1)
            {
                k = 0;
                for (int i = 0; i < M1; ++i)
                    for (int j = 0; j < N1; ++j)
                    {
                        string tmp = (string)dataGridView1.Rows[i].Cells[j].Value;
                        if (!double.TryParse(tmp, out tm))
                            k++;
                    }
                return (k == 0);
            }
            else
            {
                k = 0;
                for (int i = 0; i < M2; ++i)
                    for (int j = 0; j < N2; ++j)
                    {
                        string tmp = (string)dataGridView2.Rows[i].Cells[j].Value;
                        if (!double.TryParse(tmp, out tm))
                            k++;
                    }
                return (k == 0);
            }
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        public void transpos()
        {
            double[,] mas = new double[M1, N1];
            for (int i = 0; i < M1; ++i)
                for (int j = 0; j < N1; ++j)
                    mas[i, j] = Convert.ToSingle(dataGridView1.Rows[i].Cells[j].Value);
            var mat = new matrix(M1, N1, mas);
            matrix res = !mat;
            dataGridView3.RowCount = N1;
            N3 = N1;
            dataGridView3.ColumnCount = M1;
            M3 = M1;
            for (int i = 0; i < N1; ++i)
                for (int j = 0; j < M1; ++j)
                    dataGridView3.Rows[i].Cells[j].Value = res.mat[i, j];
        }

        public void summ()
        {
            double[,] mas0 = new double[M1, N1];
            double[,] mas1 = new double[M2, N2];
            for (int i = 0; i < M1; ++i)
                for (int j = 0; j < N1; ++j)
                    mas0[i, j] = Convert.ToSingle(dataGridView1.Rows[i].Cells[j].Value);
            for (int i = 0; i < M2; ++i)
                for (int j = 0; j < N2; ++j)
                    mas1[i, j] = Convert.ToSingle(dataGridView2.Rows[i].Cells[j].Value);
            var mat0 = new matrix(M1, N1, mas0);
            var mat1 = new matrix(M2, N2, mas1);
            matrix res = mat0 + mat1;
            dataGridView3.RowCount = N1;
            N3 = N1;
            dataGridView3.ColumnCount = M1;
            M3 = M1;
            for (int i = 0; i < N1; ++i)
                for (int j = 0; j < M1; ++j)
                    dataGridView3.Rows[i].Cells[j].Value = res.mat[i, j];
        }

        public void comp()
        {
            double[,] mas0 = new double[M1, N1];
            double[,] mas1 = new double[M2, N2];
            for (int i = 0; i < M1; ++i)
                for (int j = 0; j < N1; ++j)
                    mas0[i, j] = Convert.ToSingle(dataGridView1.Rows[i].Cells[j].Value);
            for (int i = 0; i < M2; ++i)
                for (int j = 0; j < N2; ++j)
                    mas1[i, j] = Convert.ToSingle(dataGridView2.Rows[i].Cells[j].Value);
            var mat0 = new matrix(M1, N1, mas0);
            var mat1 = new matrix(M2, N2, mas1);
            if (N1 == M2)
            {
                matrix res = mat0 * mat1;
                dataGridView3.RowCount = M1;
                N3 = M1;
                dataGridView3.ColumnCount = N2;
                M3 = N2;
                for (int i = 0; i < M1; ++i)
                    for (int j = 0; j < N2; ++j)
                        dataGridView3.Rows[i].Cells[j].Value = res.mat[i, j];
            }
            else if (M1 == N2)
            {
                DialogResult result = MessageBox.Show("matrices cannot be multiplied in that order, try to multiply matrices in a different order?",
                    "Attention", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                if (result == DialogResult.Yes)
                {
                    matrix res = mat1 * mat0;
                    dataGridView3.RowCount = N2;
                    N3 = N2;
                    dataGridView3.ColumnCount = M1;
                    M3 = M1;
                    for (int i = 0; i < N2; ++i)
                        for (int j = 0; j < M1; ++j)
                            dataGridView3.Rows[i].Cells[j].Value = res.mat[i, j];
                }
            }
        }

        public void calcDet(int l)
        {
            if (l == 0)
                if (((N1 != 0) && (M1 != 0)) && (N1 == M1))
                {
                    double[,] mas = new double[M1, N1];
                    for (int i = 0; i < M1; ++i)
                        for (int j = 0; j < N1; ++j)
                            mas[i, j] = Convert.ToSingle(dataGridView1.Rows[i].Cells[j].Value);
                    var mat = new matrix(M1, N1, mas);
                    textBox2.Text = mat.CalculateDeterminant().ToString();
                }
                else
                    textBox2.Text = "Non";


            if (l == 1)
                if (((N2 != 0) && (M2 != 0)) && (N2 == M2))
                {
                    double[,] mas = new double[M2, N2];
                    for (int i = 0; i < M2; ++i)
                        for (int j = 0; j < N2; ++j)
                            mas[i, j] = Convert.ToSingle(dataGridView2.Rows[i].Cells[j].Value);
                    var mat = new matrix(M2, N2, mas);
                    textBox1.Text = mat.CalculateDeterminant().ToString();
                }
                else
                    textBox1.Text = "Non";

            if (l == 2)
                if ((N3 != 0) && (M3 != 0) && (N3 == M3))
                {
                    double[,] mas = new double[M3, N3];
                    for (int i = 0; i < M3; ++i)
                        for (int j = 0; j < N3; ++j)
                            mas[i, j] = Convert.ToSingle(dataGridView3.Rows[i].Cells[j].Value);
                    var mat = new matrix(M3, N3, mas);
                    textBox3.Text = mat.CalculateDeterminant().ToString();
                }
                else
                    textBox3.Text = "Non";
        }

    }
}
