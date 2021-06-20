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
    public partial class worc : Form
    {
        public event EventHandler ApplyHandler0;

        public int r, g, b;

        public worc()
        {
            InitializeComponent();
        }

        private void Red_Scroll(object sender, EventArgs e)
        {
            r = red.Value;
            if (ApplyHandler0 != null)
                ApplyHandler0(this, new EventArgs());
            label2.Text = r.ToString();
        }

        private void Blue_Scroll(object sender, EventArgs e)
        {
            b = blue.Value;
            if (ApplyHandler0 != null)
                ApplyHandler0(this, new EventArgs());
            label4.Text = b.ToString();
        }

        private void Grin_Scroll(object sender, EventArgs e)
        {
            g = grin.Value;
            if (ApplyHandler0 != null)
                ApplyHandler0(this, new EventArgs());
            label6.Text = g.ToString();
        }
    }
}
