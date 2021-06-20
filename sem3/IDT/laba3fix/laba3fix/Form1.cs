using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace laba3fix
{
    public partial class Form1 : Form
    {
        public int r, g, b;
        int pbh, pbw;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            pbh = pictureBox1.Height;
            pbw = pictureBox1.Width;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form2 form = new Form2();
            form.ApplyHandler0 += new EventHandler(picterShow);
            form.Owner = this;
            form.Show();
        }

        private void collor_chaing(object sender, EventArgs e)
        {
            worc form = (worc)sender;
            r = form.r;
            g = form.g;
            b = form.b;
            this.BackColor = Color.FromArgb(r, g, b);
        }

        private void picterShow(object sender, EventArgs e)
        {
            double mh, mw;
            Form2 form = (Form2)sender;
            pictureBox1.Image = Image.FromFile(form.pl);
            if ((pictureBox1.Image.Width > pbw) || (pictureBox1.Image.Height > pbh))
            {
                pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;

                mh = (double)pbh / (double)pictureBox1.Image.Height;
                mw = (double)pbh / (double)pictureBox1.Image.Width;

                if (mh < mw)
                {
                    pictureBox1.Width = Convert.ToInt16(pictureBox1.Image.Width * mh);
                    pictureBox1.Height = pbh;
                }
                else
                {
                    pictureBox1.Width = pbw;
                    pictureBox1.Height = Convert.ToInt16(pictureBox1.Image.Height * mw);
                }
            }
            else
                if (pictureBox1.SizeMode == PictureBoxSizeMode.StretchImage)
                pictureBox1.SizeMode = PictureBoxSizeMode.AutoSize;
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            worc form = new worc();
            form.ApplyHandler0 += new EventHandler(collor_chaing);
            form.Owner = this;
            form.Show();
        }
    }
}
