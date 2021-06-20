using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using FactoryLibrary;

namespace lab5
{
    public partial class vorkingProcess : Form
    {
        public int x, y, k;
        public string pl="D:\\sprite\\", exp=".jpg";//pl - адрес папрки со спрайтами
        public bool ws;

        Timer t = new Timer();
        AbstractFactoryPC fact;
        client pc;

        private void resolution_Scroll(object sender, EventArgs e)
        {
            ws = false;
            t.Stop();
            this.y = resolution.Value;
            this.x = (this.y / 9) * 16;
            horizon.Text = ((resolution.Value / 9) * 16).ToString();
            vertical.Text = (resolution.Value).ToString();
        }

        public vorkingProcess(AbstractFactoryPC f)
        {
            InitializeComponent();
            this.fact = f;
        }

        private void vorkingProcess_FormClosed(object sender, FormClosedEventArgs e)
        {
            t.Stop();
        }

        private void strart_Click(object sender, EventArgs e)
        {
            this.k = 0;
            t.Interval = 1000 / pc.GPU.drows(this.x, this.y);
            ws = !ws;
            if (ws == true)
                t.Start();
            else
                t.Stop();
        }

        private void vorkingProcess_Load(object sender, EventArgs e)
        {
            this.y = resolution.Value;
            this.x = (resolution.Value / 9) * 16;
            horizon.Text = ((resolution.Value / 9) * 16).ToString();
            vertical.Text = (resolution.Value).ToString();
            ws = false;
            pc = new client(this.fact);
            t.Tick += new EventHandler(this.t_Tick);
        }

        private void t_Tick(object sendet, EventArgs e)
        {
            int[] wa = pc.work();
            RMPval.Text = wa[1].ToString();
            tempi.Text = wa[0].ToString();
            string pls = this.pl+this.k.ToString()+exp;
            pictureBox1.Image = Image.FromFile(pls);
            this.k++;
            if (this.k >= 3)
                this.k = 0;
        }
    }
}
