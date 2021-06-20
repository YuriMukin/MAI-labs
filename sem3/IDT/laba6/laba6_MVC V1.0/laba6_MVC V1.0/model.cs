using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Collections;

namespace laba6_MVC_V1._0
{
    public class model
    {
        private ArrayList listeners = new ArrayList();
        private Pen pen, pen1;
        private ArrayList lines;
        private int w,h;
        private int[] k;
        private Bitmap graf;
        private Graphics DrawPl;

        public model(int w, int h)
        {
            this.w = w;
            this.h = h;
            this.graf = new Bitmap(w, h);
            this.pen = new Pen(Color.Black, 2);
            this.pen1 = new Pen(Color.FromArgb(100, 128, 128, 128), 1);
            this.DrawPl = Graphics.FromImage(this.graf);
        }


        public Bitmap Drowing(ArrayList lin, int[] k)
        {
            this.k = k;
            this.lines = lin;
            int j;
            this.DrawPl.Clear(Color.LightGray);
            PointF tmp;
            DrawPl.DrawLine(pen, 0, h / 2, w, h / 2);
            DrawPl.DrawLine(pen, h / 2, 0, w / 2, h);
            for (int i = 10; i <= w; i += 10)
            {
                DrawPl.DrawLine(pen1, (this.h / 2) + i, 0, (this.h / 2) + i, this.h);
                DrawPl.DrawLine(pen1, (this.h / 2) - i, 0, (this.h / 2) - i, this.h);
                DrawPl.DrawLine(pen1, 0, (this.w / 2) + i, this.w, (this.w / 2) + i);
                DrawPl.DrawLine(pen1, 0, (this.w / 2) - i, this.w, (this.w / 2) - i);
            }
            foreach (PointF[] points in lines)
            {
                j = 0;
                tmp = points[0];
                for (int i = 1; i < k[j]; i++)
                {
                    DrawPl.DrawLine(pen, tmp, points[i]);
                    tmp = points[i];
                }
                j++;
            }
            UpdateObservers();
            return this.graf;
        }

        public ArrayList SetOfLines()
        {
            return lines;
        }

        public int[] retc()
        {
            return k;
        }

        public Bitmap ReDrowing()
        {
            return this.graf;
        }

        public void Register(IObserver o)
        {
            listeners.Add(o);
            o.UpdateState();
        }

        public void Deregister(IObserver o)
        {
            listeners.Remove(o);
        }

        public void UpdateObservers()
        {
            foreach (IObserver ob in listeners)
            {
                ob.UpdateState();
            }
        }
    }
}
