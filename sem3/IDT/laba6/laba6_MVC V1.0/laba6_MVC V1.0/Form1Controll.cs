using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;

namespace laba6_MVC_V1._0
{
    public class Form1Controll
    {
        private model model;
        private Form1 view;

        public Form1Controll(Form1 view, model model)
        {
            this.model = model;
            this.view = view;
        }

        public Bitmap Drow(DataGridView dotcor, Panel panel1, int rows)
        {
            int j = 0;
            int[] k = new int[rows];
            k[j] = 0;
            ArrayList lines = new ArrayList();
            PointF[] points = new PointF[rows];
            for (int i = 0; i < rows; i++)
            {
                try
                {
                    points[k[j]] = new PointF(Convert.ToSingle(dotcor[0, i].Value) + (panel1.Width / 2), Convert.ToSingle(dotcor[1, i].Value) * (-1) + (panel1.Height / 2));
                    k[j]++;
                }
                catch
                {
                    lines.Add(points);
                    points = new PointF[rows];
                    j++;
                    k[j] = 0;
                }
            }
            lines.Add(points);
            return model.Drowing(lines, k);
        }

        public Bitmap ReDrow()
        {
            return model.ReDrowing();
        }

        public float[,] dots()
        {
            int len = 0;
            ArrayList l = model.SetOfLines();
            int[] k = model.retc();
            if (k != null)
            {
                foreach (PointF[] p in l)
                {
                    len += p.Length;
                }
                float[,] points = new float[len, 2];
                int s = 0;
                foreach (PointF[] p in l)
                {
                    int j = 0;
                    for (int i = 0; i < k[j]; i++)
                    {
                        points[s, 0] = p[i].X;
                        points[s, 1] = p[i].Y;
                        s++;
                    }
                    j++;
                }
                return points;
            }
            return null;
        }
    }
}
