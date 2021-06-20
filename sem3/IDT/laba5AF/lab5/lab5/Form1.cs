using System;
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
    public partial class Form1 : Form
    {
        AbstractFactoryPC fact;

        public Form1()
        {
            InitializeComponent();
        }

        private void Notebook_CheckedChanged(object sender, EventArgs e)
        {
            fact = new FactoryNotebook();
        }

        private void ATX_PC_CheckedChanged(object sender, EventArgs e)
        {
            fact = new FactoryATX();
        }

        private void st_worc_Click(object sender, EventArgs e)
        {
            vorkingProcess form = new vorkingProcess(fact);
            form.ShowDialog();
        }
    }
}
