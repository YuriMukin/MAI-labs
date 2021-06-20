using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace Q_learning_with_a_model
{
    class Protagonist: Unit
    {
        public Stack<int> prev_state, curr_state;
        private Environment env;
        private ArrayList enemys;
        public int dx, dy, reward;
        private Random rnd;
        private Q_model qmodel;
        public double eps;

        public Protagonist(int x, int y, int n, ArrayList enemys, Environment env, Q_model qmod) : base(x,y,n)
        {
            this.enemys = enemys;
            this.env = env;
            this.dx = 0;
            this.dy = 0;
            this.eps = 0.95;
            this.rnd = new Random();
            this.qmodel = qmod;
            this.prev_state = Get_Features();
            this.prev_state.Push(dx);
            this.prev_state.Push(dy);
            this.curr_state = Get_Features();
            this.curr_state.Push(dx);
            this.curr_state.Push(dy);
        }

        public int[] strategy()
        {
            int i = rnd.Next(9);
            double[] best = new double[] { 0, 0, 0};
            Stack<int> namel;
            Stack<int> name;
            int[] act = new int[] { 0, 0 };
            if (rnd.NextDouble() < eps)
                act = actions[i];
            else
            {
                namel = Get_Features();
                foreach(int[] acti in actions)
                {
                    name = namel.Copy();
                    name.Push(acti[0]);
                    name.Push(acti[1]);
                    if (!qmodel.Generational_Experience.ContainsKey(name.CopyToString()))
                        qmodel.Generational_Experience.Add(name.CopyToString(), 0);
                    if(best[2]< qmodel.Generational_Experience[name.CopyToString()])
                    {
                        best[0] = acti[0];
                        best[1] = acti[1];
                        best[2] = qmodel.Generational_Experience[name.CopyToString()];
                    }
                }
                act[0] = (int)best[0];
                act[1] = (int)best[1];
            }
            return act;
        }

        public void Make_Step()
        {
            int[] a = strategy();
            int nx, ny;
            nx = Get_Position()[0] + a[0];
            ny = Get_Position()[1] + a[1];
            bool expr = (nx < Get_N()) && (ny < Get_N()) && (0 <= nx) && (0 <= ny);
            if (expr)
                Set_Position(nx, ny);
        }

        public Stack<int> Get_Features()
        {
            Stack<int> Features = new Stack<int>();
            foreach(Enemy en in this.enemys)
            {
                Features.Push(en.Get_Position()[0]);
                Features.Push(en.Get_Position()[1]);
            }
            Features.Push(this.Get_Position()[0]);
            Features.Push(this.Get_Position()[1]);
            return Features;
        }
    }
}
