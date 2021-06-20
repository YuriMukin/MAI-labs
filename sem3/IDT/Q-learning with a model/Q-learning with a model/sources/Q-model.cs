using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Q_learning_with_a_model
{
    class Q_model
    {
        private double alpha, gamma;
        private Protagonist pr;
        public Dictionary<string, double> Generational_Experience;

        public Q_model()
        {
            this.alpha = 0.95;
            this.gamma = 0.95;
            this.Generational_Experience = new Dictionary<string, double>();
        }

        public void Set_Protagonist(Protagonist pr)
        {
            this.pr = pr;
        }

        public void Ran_Model(bool ran)
        {
            pr.prev_state = pr.curr_state.Cut(2);
            pr.prev_state.Push(pr.dx);
            pr.prev_state.Push(pr.dy);
            pr.curr_state = pr.Get_Features();
            pr.curr_state.Push(pr.dx);
            pr.curr_state.Push(pr.dy);
            if (ran)
            {
                Debug.WriteLine(pr.prev_state.CopyToString());
                Debug.WriteLine(pr.curr_state.CopyToString());
            }
            int r = pr.reward;
            if (!Generational_Experience.ContainsKey(pr.prev_state.CopyToString()))
                Generational_Experience.Add(pr.prev_state.CopyToString(), 0);
            Stack<int> may_cond = new Stack<int>();
            Stack<double> nvec = new Stack<double>();
            foreach (int[] mmv in pr.actions)
            {
                may_cond = pr.curr_state.Cut(2);
                may_cond.Push(mmv[0]);
                may_cond.Push(mmv[1]);
                if (!Generational_Experience.ContainsKey(may_cond.CopyToString()))
                    Generational_Experience.Add(may_cond.CopyToString(),0);
                nvec.Push(Generational_Experience[may_cond.CopyToString()]);
            }
            nvec = nvec.Max();
            Generational_Experience[pr.prev_state.CopyToString()] = Generational_Experience[pr.prev_state.CopyToString()] + alpha * (-Generational_Experience[pr.prev_state.CopyToString()] + r + gamma * nvec.Pop());
        }
    }
}
