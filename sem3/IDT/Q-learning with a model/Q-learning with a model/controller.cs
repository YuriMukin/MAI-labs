using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Q_learning_with_a_model
{
    public class controller
    {
        private model model;
        private Form1 view;

        public controller(Form1 view, model model)
        {
            this.model = model;
            this.view = view;
        }

        public void ran_model(int[,] en, int l, int r, int n)
        {
            int[] pr = new int[] { 1, 1 };
            model.work(pr, en, l, r, n);
        }
    }
}
