using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Globalization;

namespace laba2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        ArrayList data;
        sales sale;

        private void Form1_Load(object sender, EventArgs e)
        {
            data = new ArrayList();
            textSize.Text = "8";
            ProdName.Text = "";
            Cost_of_pd.Text = "";
            coast.Text = "";
            num_of_ws.Text = "";
            discount.Text = "";
            toolTip1.SetToolTip(this.CastName, "here you can set name of castomer");
            toolTip1.SetToolTip(this.ProdName, "here you can set name of product");
            toolTip1.SetToolTip(this.coast, "here you can set cost of product");
            toolTip1.SetToolTip(this.num_of_rs, "here you can set quantity of product");
            toolTip1.SetToolTip(this.discount, "here you can set amount of discount");
            toolTip1.SetToolTip(this.num_of_ws, "here you can set quantity of product");
            toolTip1.SetToolTip(this.summout, "it's final income");
            toolTip1.SetToolTip(this.retail_base, "here will bee records about retail sales");
            toolTip1.SetToolTip(this.wholesale_base, "here will bee records about wholesale sales");
            toolTip1.SetToolTip(this.textSize, "it's text size");
        }

        private void retail_CheckedChanged(object sender, EventArgs e)
        {
            num_of_rs.Enabled = !num_of_rs.Enabled;
            discount.Enabled = !discount.Enabled;
        }

        private void wholesale_CheckedChanged(object sender, EventArgs e)
        {
            num_of_ws.Enabled = !num_of_ws.Enabled;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                double c = Double.Parse(coast.Text);
                if ((CastName.SelectedIndex != -1)&&(ProdName.Text!=""))
                {
                    if(retail.Checked)
                    {
                        sale = new retail((string)CastName.SelectedItem, ProdName.Text, c, (int)num_of_rs.Value, int.Parse(discount.Text));
                    }
                    else
                    {
                        sale = new wholesale((string)CastName.SelectedItem, ProdName.Text, c, int.Parse(num_of_ws.Text));
                    }
                    data.Add(sale);
                }
                else
                    MessageBox.Show("customer or product not selected", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            catch
            {
                coast.Text = "";
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }


        private void discount_TextChanged(object sender, EventArgs e)
        {
            try
            {
                Int32.Parse(discount.Text);
            }
            catch
            {
                if (discount.Text != "")
                {
                    discount.Text = discount.Text.Substring(0, (discount.Text.Length - 1));
                    MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }

        private void num_of_ws_TextChanged(object sender, EventArgs e)
        {
            try
            {
                Int32.Parse(num_of_ws.Text);
            }
            catch
            {
                if (num_of_ws.Text != "")
                {
                    num_of_ws.Text = num_of_ws.Text.Substring(0, (num_of_ws.Text.Length - 1));
                    MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }

        private void ret_bas_show_Click(object sender, EventArgs e)
        {
            retail_base.Items.Clear();
            for (int i = 0; i < data.Count; i++)
            {
                sale = (sales)data[i];
                if (sale.GetType().Name == "retail")
                {
                    Debug.WriteLine("\n"+ sale.info()+ "\n");
                    retail_base.Items.Add(sale.info());
                }
            }
        }

        private void who_bas_show_Click(object sender, EventArgs e)
        {
            wholesale_base.Items.Clear();
            for (int i = 0; i < data.Count; i++)
            {
                sale = (sales)data[i];
                if (sale.GetType().Name == "wholesale")
                {
                    wholesale_base.Items.Add(sale.info());
                }
            }
        }

        private void clearBaseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            wholesale_base.Items.Clear();
            retail_base.Items.Clear();
            data.Clear();
        }

        private void calcsumm_Click(object sender, EventArgs e)
        {
            double s = 0;
            for (int i = 0; i < data.Count; i++)
            {
                sale = (sales)data[i];
                s = s + sale.summ();
            }
            summout.Text = string.Format("{0:f2}", s);
        }

        private void addNameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SuNaIn fnam = new SuNaIn();
            fnam.ShowDialog();
            CastName.Items.Insert(0, fnam.name_of_cast);
        }

        private void addProductToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pnain fnam = new pnain();
            fnam.ShowDialog();
            ProdName.Items.Add(fnam.name_of_prod);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            retail_base.Font = new Font("Microsoft Sans Serif", trackBar1.Value);
            wholesale_base.Font = new Font("Microsoft Sans Serif", trackBar1.Value);
            textSize.Text = Convert.ToString(trackBar1.Value);
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            SuNaIn fnam = new SuNaIn();
            fnam.ShowDialog();
            CastName.Items.Insert(0, fnam.name_of_cast);
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            pnain fnam = new pnain();
            fnam.ShowDialog();
            ProdName.Items.Add(fnam.name_of_prod);
        }
    }
}
