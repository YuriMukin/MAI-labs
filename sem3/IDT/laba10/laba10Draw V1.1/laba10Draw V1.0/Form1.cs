using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Collections;

namespace laba10Draw_V1._0
{
    public partial class Form1 : Form
    {
        private PostfixNotationExpression converter;
        private Stack<double> st;
        private PointF[] points0, points1;
        private Pen pen, pen1, pen2;
        private Graphics plase0, plase1;
        private Color pc1, pc2, bgc;
        private int r, g, b, asz, lsz, j;
        private ArrayList lines0, lines1;
        public int[] k;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            lines0 = new ArrayList();
            lines1 = new ArrayList();
            r = 1;
            g = 1;
            b = 1;
            pc1 = Color.Black;
            pc2 = Color.Black;
            bgc = Color.White;
            oc.Enabled = false;
            lc.Enabled = false;
            bc.Enabled = false;
            this.converter = new PostfixNotationExpression();
            this.pen = new Pen(pc1, 2);
            this.pen1 = new Pen(pc2, 2);
            this.pen2 = new Pen(Color.FromArgb(100,128,128,128), 1);
            plase0 = Graphics.FromHwnd(panel1.Handle);
            plase1 = Graphics.FromHwnd(panel2.Handle);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            worc();
        }

        public void worc()
        {
            bool exep = true;
            PointF tmp;
            points0 = new PointF[(int)((Convert.ToDouble(to.Text) - Convert.ToDouble(from.Text)) / Convert.ToDouble(step.Text))+1];
            points1 = new PointF[(int)((Convert.ToDouble(to.Text) - Convert.ToDouble(from.Text)) / Convert.ToDouble(step.Text))+1];
            lines0.Clear();
            lines1.Clear();
            k = new int[(int)(Convert.ToDouble(to.Text) - Convert.ToDouble(from.Text) / Convert.ToDouble(step.Text) / 2)];
            j = 0;
            k[j] = 0;
            st = new Stack<double>();
            double ch;
            string[] fu = converter.ConvertToPostfixNotation(Function.Text);
            for (double i = Convert.ToDouble(to.Text); i >= Convert.ToDouble(from.Text); i -= Convert.ToDouble(step.Text))
            {
                foreach (string s in fu)
                {
                    string nwp = s;
                    if (nwp == "x")
                        nwp = Convert.ToString(i);
                    if (double.TryParse(nwp, out ch))
                        st.Push(ch);
                    else
                        exep = oerator(nwp);
                }
                if (exep == false)
                {
                    lines0.Add(points0);
                    lines1.Add(points1);
                    points0 = new PointF[(int)((Convert.ToDouble(to.Text) - Convert.ToDouble(from.Text)) / Convert.ToDouble(step.Text))];
                    points1 = new PointF[(int)((Convert.ToDouble(to.Text) - Convert.ToDouble(from.Text)) / Convert.ToDouble(step.Text))];
                    j++;
                    Debug.WriteLine("{0}", j);
                    k[j] = 0;
                }
                else
                {
                    double n = st.Pop() * (-1);
                    points0[k[j]] = new PointF((float)(i + panel1.Width / 2), (float)(n + panel1.Height / 2));
                    points1[k[j]] = new PointF((float)(i * 20 + panel2.Width / 2), (float)(n * 20 + panel2.Height / 2));
                    k[j]++;
                    //Debug.WriteLine("{0} {1}", i + panel1.Width / 2, (int)n + panel1.Height / 2);
                }
            }
            lines0.Add(points0);
            lines1.Add(points1);
            j++;
            k[j] = 0;
            plase0.Clear(bgc);
            plase0.DrawLine(pen1, 0, panel1.Height / 2, panel1.Width, panel1.Height / 2);
            plase0.DrawLine(pen1, panel1.Width / 2, 0, panel1.Width / 2, panel1.Height);
            for (int i = 10; i <= panel1.Width; i += 10)
            {
                plase0.DrawLine(pen2, (panel1.Height / 2) + i - 15, 0, (panel1.Height / 2) + i - 15, panel1.Height);
                plase0.DrawLine(pen2, (panel1.Height / 2) - i - 15, 0, (panel1.Height / 2) - i - 15, panel1.Height);
                plase0.DrawLine(pen2, 0, (panel1.Width / 2) + i + 15, panel1.Width, (panel1.Width / 2) + i + 15);
                plase0.DrawLine(pen2, 0, (panel1.Width / 2) - i + 15, panel1.Width, (panel1.Width / 2) - i + 15);
            }
            plase1.Clear(bgc);
            for (int i = 10; i <= panel2.Width; i += 10)
            {
                plase1.DrawLine(pen2, (panel2.Height / 2) + i * 2, 0, (panel2.Height / 2) + i * 2, panel2.Height);
                plase1.DrawLine(pen2, (panel2.Height / 2) - i * 2, 0, (panel2.Height / 2) - i * 2, panel2.Height);
                plase1.DrawLine(pen2, 0, (panel2.Width / 2) + i * 2, panel2.Width, (panel2.Width / 2) + i * 2);
                plase1.DrawLine(pen2, 0, (panel2.Width / 2) - i * 2, panel2.Width, (panel2.Width / 2) - i * 2);
            }
            plase1.DrawLine(pen1, 0, panel2.Height / 2, panel2.Width, panel2.Height / 2);
            plase1.DrawLine(pen1, panel2.Width / 2, 0, panel2.Width / 2, panel2.Height);
            foreach (PointF[] points in lines0)
            {
                j = 0;
                tmp = points[0];
                for (int i = 1; i < k[j]; i++)
                {
                    plase0.DrawLine(pen, tmp, points[i]);
                    tmp = points[i];
                }
                j++;
            }
            foreach (PointF[] points in lines1)
            {
                j = 0;
                tmp = points[0];
                for (int i = 1; i < k[j]; i++)
                {
                    plase1.DrawLine(pen, tmp, points[i]);
                    tmp = points[i];
                }
                j ++;
            }
            //plase.DrawLines(pen, points);
            //plase.DrawImage(b, 0, 0);
            Debug.WriteLine("");
        } 

        private void step_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (step.Text != "")
                    Double.Parse(step.Text);
            }
            catch
            {
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                step.Text = "";
            }
        }

        private void lin_CheckedChanged(object sender, EventArgs e)
        {
            oc.Enabled = true;
            lc.Enabled = true;
            bc.Enabled = true;
        }

        private void orts_CheckedChanged(object sender, EventArgs e)
        {
            oc.Enabled = true;
            lc.Enabled = true;
            bc.Enabled = true;
        }

        private void axsz_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (axsz.Text != "")
                {
                    asz = Int32.Parse(axsz.Text);
                    pen1.Width = asz;
                }
            }
            catch
            {
                axsz.Text = "";
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void back_CheckedChanged(object sender, EventArgs e)
        {
            oc.Enabled = true;
            lc.Enabled = true;
            bc.Enabled = true;
        }

        private void lisz_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (lisz.Text != "")
                {
                    lsz = Int32.Parse(lisz.Text);
                    pen.Width = lsz;
                }
            }
            catch
            {
                lisz.Text = "";
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        public bool oerator(string s)
        {
            double op2;
            switch (s)
            {
                case "+":
                    st.Push(st.Pop() + st.Pop());
                    return true;
                    break;
                case "*":
                    st.Push(st.Pop() * st.Pop());
                    return true;
                    break;
                case "-":
                    op2 = st.Pop();
                    st.Push(st.Pop() - op2);
                    return true;
                    break;
                case "/":
                    op2 = st.Pop();
                    if (op2 != 0.0)
                    {
                        st.Push(st.Pop() / op2);
                        return true;
                    }
                    else
                    {
                        Debug.WriteLine("Ошибка. Деление на ноль");
                        return false;
                    }
                    break;
                case "^":
                    op2 = st.Pop();
                    st.Push(Math.Pow(st.Pop(), op2));
                    return true;
                    break;
                default:
                    Debug.WriteLine("Ошибка. Неизвестная команда");
                    return false;
                    break;
            }
        }

        private void oc_Scroll(object sender, EventArgs e)
        {
            r = oc.Value;
            colCh();
        }

        private void lc_Scroll(object sender, EventArgs e)
        {
            g = lc.Value;
            colCh();
        }

        private void bc_Scroll(object sender, EventArgs e)
        {
            b = bc.Value;
            colCh();
        }

        public void colCh()
        {
            if (lin.Checked)
            {
                pc1 = Color.FromArgb(r,g,b);
                pen.Color = pc1;
                Graphics.FromHwnd(lincil.Handle).Clear(pc1);
            }
            if (orts.Checked)
            {
                pc2 = Color.FromArgb(r, g, b);
                pen1.Color = pc2;
                Graphics.FromHwnd(orcol.Handle).Clear(pc2);
            }
            if (back.Checked)
            {
                bgc = Color.FromArgb(r, g, b);
                Graphics.FromHwnd(baccol.Handle).Clear(bgc);
            }
        }

        public void redrow()
        {
            PointF tmp;
            plase0.Clear(bgc);
            for (int i = 10; i <= panel1.Width; i += 10)
            {
                plase0.DrawLine(pen2, (panel1.Height / 2) + i - 15, 0, (panel1.Height / 2) + i - 15, panel1.Height);
                plase0.DrawLine(pen2, (panel1.Height / 2) - i - 15, 0, (panel1.Height / 2) - i - 15, panel1.Height);
                plase0.DrawLine(pen2, 0, (panel1.Width / 2) + i + 15, panel1.Width, (panel1.Width / 2) + i + 15);
                plase0.DrawLine(pen2, 0, (panel1.Width / 2) - i + 15, panel1.Width, (panel1.Width / 2) - i + 15);
            }
            plase0.DrawLine(pen1, 0, panel1.Height / 2, panel1.Width, panel1.Height / 2);
            plase0.DrawLine(pen1, panel1.Width / 2, 0, panel1.Width / 2, panel1.Height);
            plase1.Clear(bgc);
            for (int i = 10; i <= panel2.Width; i += 10)
            {
                plase1.DrawLine(pen2, (panel2.Height / 2) + i*2, 0, (panel2.Height / 2) + i*2, panel2.Height);
                plase1.DrawLine(pen2, (panel2.Height / 2) - i*2, 0, (panel2.Height / 2) - i*2, panel2.Height);
                plase1.DrawLine(pen2, 0, (panel2.Width / 2) + i*2, panel2.Width, (panel2.Width / 2) + i*2);
                plase1.DrawLine(pen2, 0, (panel2.Width / 2) - i*2 , panel2.Width, (panel2.Width / 2) - i*2);
            }
            plase1.DrawLine(pen1, 0, panel2.Height / 2, panel2.Width, panel2.Height / 2);
            plase1.DrawLine(pen1, panel2.Width / 2, 0, panel2.Width / 2, panel2.Height);
            foreach (PointF[] points in lines0)
            {
                j = 0;
                tmp = points[0];
                for (int i = 1; i < k[j]; i++)
                {
                    plase0.DrawLine(pen, tmp, points[i]);
                    tmp = points[i];
                }
                j++;
            }
            foreach (PointF[] points in lines1)
            {
                j = 0;
                tmp = points[0];
                for (int i = 1; i < k[j]; i++)
                {
                    plase1.DrawLine(pen, tmp, points[i]);
                    tmp = points[i];
                }
                j++;
            }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            redrow();
        }
    }
}
