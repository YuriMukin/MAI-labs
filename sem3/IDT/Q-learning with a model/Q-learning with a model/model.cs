using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.Drawing;

namespace Q_learning_with_a_model
{
    public class model
    {
        public delegate void InvokeRefreshDelegate();
        private ArrayList listeners = new ArrayList();
        public bool silent;
        public int process, score,k;
        private int w, h, n;
        public Bitmap graf;
        private Graphics DrawPl;

        public model()
        {
            w = 300;
            h = 300;
            n = 0;
            graf = new Bitmap(w, h);
            DrawPl = Graphics.FromImage(this.graf);
        }

        public void work(int[] pr_cor, int[,] en_cor, int learn, int result, int n)
        {
            Q_model q = new Q_model();
            Environment env;
            this.n = n;
            for (int i=0; i<learn; i++)
            {
                silent = true;
                env = new Environment(n, pr_cor, en_cor, q, this);
                env.protagonist.eps = 0.2;
                env.play(silent);
                process = i;
                UpdateObservers();
            }
            k = 0;
            while (k < result)
            {
                silent = false;
                env = new Environment(n, pr_cor, en_cor, q, this);
                env.protagonist.eps = 0.2;
                score = env.play(silent);
                UpdateObservers();
                k++;
            }
        }

        public void draw(int[,] fild)
        {
            this.DrawPl.Clear(Color.LightGray);
            Pen pen1 = new Pen(Color.FromArgb(100, 128, 128, 128), 1);
            for (int i =0;i<h; i+=h/n)
            {
                DrawPl.DrawLine(pen1, i, 0, i, h);
                DrawPl.DrawLine(pen1, 0, i, w, i);
            }
            Brush br1 = Brushes.Black;
            Brush br2 = Brushes.Red;
            for (int i=0; i<n; i++)
                for (int j =0; j<n; j++)
                {
                    if (fild[i, j] == 1)
                    {
                        int x = (i + 1) * (h / (n)) - h / (n * 2);
                        int y = (j + 1) * (h / (n)) - h / (n * 2);
                        DrawPl.FillPie(br2,x,y, h / (n ), h / (n ),360,360);
                    }
                    if (fild[i, j] == 2)
                    {
                        int x = (i+1) * (h / (n)) - h / (n * 2);
                        int y = (j+1) * (h / (n)) - h / (n * 2);
                        DrawPl.FillPie(br1, x, y, h / (n ), h / (n ), 360, 360);
                    }
                }
            UpdateObservers();
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
