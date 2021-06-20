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
    public partial class SuNaIn : Form
    {
        public SuNaIn()
        {
            InitializeComponent();
        }
        public string name_of_cast;

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                name_of_cast = textBox1.Text;
                Close();
            }
        }

        private void SuNaIn_Load(object sender, EventArgs e)
        {
            textBox1.Text = "";
        }
    }
}
