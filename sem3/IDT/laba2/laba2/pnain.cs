using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace laba2
{
    public partial class pnain : Form
    {
        public pnain()
        {
            InitializeComponent();
        }
        public string name_of_prod;

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                name_of_prod = textBox1.Text;
                Close();
            }
        }

        private void pnain_Load(object sender, EventArgs e)
        {
            textBox1.Text = "";
        }
    }
}
