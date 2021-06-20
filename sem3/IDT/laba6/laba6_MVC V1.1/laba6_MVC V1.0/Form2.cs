using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace laba6_MVC_V1._0
{
    public partial class Form2 : Form, IObserver
    {
        private Form2Controll controller;
        private model model;
        private int[] k;
        private Graphics plase;

        public Form2(model model)
        {
            InitializeComponent();
            this.model = model;
            this.model.Register(this);
            attachController(makeController());
        }

        public void attachController(Form2Controll controller)
        {
            this.controller = controller;
        }

        protected Form2Controll makeController()
        {
            return new Form2Controll(this, model);
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            plase = Graphics.FromHwnd(panel1.Handle);
        }

        public void UpdateState()
        {
            if (controller != null)
                plase.DrawImage(controller.ReDrow(), 0, 0);
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            plase.DrawImage(controller.ReDrow(), 0, 0);
        }

        private void Draw_Click(object sender, EventArgs e)
        {
            try
            {
                plase.Clear(Color.LightGray);
                plase.DrawImage(controller.Drow(Convert.ToDouble(to.Text), Convert.ToDouble(from.Text), Convert.ToDouble(step.Text), function.Text, panel1.Width, panel1.Height), 0, 0);
            }
            catch
            {
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
    }
}
