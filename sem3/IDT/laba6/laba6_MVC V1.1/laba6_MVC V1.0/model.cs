using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Collections;
using System.Timers;

namespace laba6_MVC_V1._0
{
    public class model
    {
        private ArrayList listeners = new ArrayList();
        private Pen pen, pen1;
        private ArrayList lines;
        private int w, h, j, i;
        public int count;
        private int[] k;
        private Bitmap graf;
        private PointF[] points;
        public PointF tmp;
        private Graphics DrawPl;
        private Timer timer;

        public model(int w, int h)
        {
            this.w = w;
            this.h = h;
            this.graf = new Bitmap(w, h);
            this.pen = new Pen(Color.Black, 2);
            this.pen1 = new Pen(Color.FromArgb(100, 128, 128, 128), 1);
            this.DrawPl = Graphics.FromImage(this.graf);
            this.timer = new Timer();
            this.timer.AutoReset = true;
            this.timer.Enabled = false;
            this.timer.Interval = 500;
            this.timer.Elapsed += new ElapsedEventHandler(timer_Elapsed);
        }


        public Bitmap Drowing(ArrayList lin, int[] k)
        {
            this.k = k;
            this.lines = lin;
            j = 0;
            count = 0;
            this.DrawPl.Clear(Color.LightGray);
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
                i = 1;
                this.points = points;
                this.timer.Enabled = true;
            }
            return this.graf;
        }

        void timer_Elapsed(object sender, ElapsedEventArgs e)
        {
            if (i < k[j])
            {
                this.tmp = points[i - 1];
                DrawPl.DrawLine(pen, tmp, points[i]);
                i++;
                count++;
                UpdateObservers();
            }
            else
            {
                this.timer.Enabled = false;
                this.j++;
            }
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
