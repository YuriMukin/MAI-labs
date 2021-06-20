using System;
using System.IO;
using System.Diagnostics;
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
    public partial class Form2 : Form
    {
        public event EventHandler ApplyHandler0;

        Timer t = new Timer();

        public string pl;
        public string plase;
        public bool cond;
        public int k;

        private Boolean FillListBox(string aPath)
        {
            DirectoryInfo di = new DirectoryInfo(aPath);
            FileInfo[] fi = di.GetFiles("*.jpg");
            listBox1.Items.Clear();
            foreach (FileInfo fc in fi)
            {
                listBox1.Items.Add(fc.Name);
                plase = aPath;
            }
            if (fi.Length == 0) return false;
            else
            {
                listBox1.SelectedIndex = 0;
                pl = aPath+(string)listBox1.SelectedItem;
                return true;
            }
        }

        public Form2()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();

            OpenFileDialog picsol = new OpenFileDialog();
            if (picsol.ShowDialog() == DialogResult.OK)
            {
                listBox1.Items.Add(picsol.FileName);
                listBox1.SelectedIndex = 0;
                pl = (string)listBox1.SelectedItem;
                if (ApplyHandler0 != null)
                    ApplyHandler0(this, new EventArgs());
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            plase = "";
            FolderBrowserDialog fb = new FolderBrowserDialog();
            fb.Description = "Выберите папку";
            fb.ShowNewFolderButton = false;
            if (fb.ShowDialog() == DialogResult.OK)
                if (!FillListBox(fb.SelectedPath + "\\"))
                {
                    pl = null;
                }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (listBox1.Items.Count > 1)
            {
                k = 0;
                cond = !cond;
                if (cond == true)
                {
                    t.Start();
                }
                else
                {
                    t.Stop();
                }
            }
            else
                MessageBox.Show("please select a folder with several images", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            cond = false;
            plase = "";
            t.Interval = (int.Parse(textBox1.Text))*1000;
            t.Tick += new EventHandler(this.t_Tick);
            toolTip1.SetToolTip(this.button3, "when pressed again, the display will stop");
            toolTip1.SetToolTip(this.listBox1, "here file names");
        }

        private void t_Tick(object sendet, EventArgs e)
        {
            listBox1.SelectedIndex = k;
            pl = plase + (string)listBox1.SelectedItem;
            ApplyHandler0(this, new EventArgs());
            k++;
            if (k + 1 > listBox1.Items.Count)
                k = 0;
            //Debug.WriteLine("at {0}", k);
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            try
            {
                cond = false;
                t.Stop();
                t.Interval = (int.Parse(textBox1.Text))*1000;
            }
            catch
            {
                if (textBox1.Text != "")
                {
                    textBox1.Text = textBox1.Text.Substring(0, (textBox1.Text.Length - 1));
                    MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
            }
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e)
        {
            t.Stop();
        }
    }
}
