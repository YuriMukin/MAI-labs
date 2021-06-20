using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Q_learning_with_a_model
{
    class Enemy: Unit
    {
        Random rnd;

        public Enemy(int x, int y, int n) : base(x, y, n) { rnd = new Random(); }

        public void Make_Step()
        {
            int i=0;
            bool expr = false;
            while (!expr)
            {
                i = rnd.Next(9);
                int nx, ny;
                nx = Get_Position()[0] + actions[i][0];
                ny = Get_Position()[1] + actions[i][1];
                expr = (nx < Get_N()) && (ny < Get_N()) && (0 <= nx) && (0 <= ny);
                if (expr)
                    Set_Position(nx, ny);
            }
        }
    }
}
