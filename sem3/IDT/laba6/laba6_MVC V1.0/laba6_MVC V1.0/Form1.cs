using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;

namespace laba6_MVC_V1._0
{
    public partial class Form1 : Form, IObserver
    {
        private Form1Controll controller;
        private model model;
        private int rows;
        private Graphics plase;

        public Form1(model model)
        {
            InitializeComponent();
            this.model = model;
            this.model.Register(this);
            attachController(makeController());
        }

        public void attachController(Form1Controll controller)
        {
            this.controller = controller;
        }

        protected Form1Controll makeController()
        {
            return new Form1Controll(this, model);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dotcor.ColumnCount = 2;
            this.rows = 0;
            plase = Graphics.FromHwnd(panel1.Handle);
        }

        private void countOfDot_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (countOfDot.Text != "")
                {
                    dotcor.RowCount = Convert.ToInt32(countOfDot.Text);
                    this.rows = Convert.ToInt32(countOfDot.Text);
                }
            }
            catch
            {
                if(countOfDot.Text!="")
                    countOfDot.Text = countOfDot.Text.Substring(0, (countOfDot.Text.Length - 1));
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        public void UpdateState()
        {
            if (controller != null)
            {
                plase.DrawImage(controller.ReDrow(), 0, 0);
                float[,] d = controller.dots();
                if(d!=null)
                {
                    dotcor.RowCount = d.GetLength(0);
                    for (int i = 0; i< d.GetLength(0); i++)
                    {
                        dotcor[0, i].Value = d[i, 0] - panel1.Width / 2;
                        dotcor[1, i].Value = (d[i, 1] - panel1.Height / 2)*(-1);
                    }
                }
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            plase.DrawImage(controller.ReDrow(), 0, 0);
        }

        private void drtaw_Click(object sender, EventArgs e)
        {
            plase.Clear(Color.LightGray);
            plase.DrawImage(controller.Drow(dotcor, panel1, rows), 0, 0);
        }
    }
}
