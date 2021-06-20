using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Q_learning_with_a_model
{
    public class Unit
    {
        private int[] position;
        public List<int[]> actions;
        private int n;

        public Unit(int x, int y, int n)
        {
            this.position = new int[2];
            this.position[0] = x;
            this.position[1] = y;
            this.actions = new List<int[]>();
            fill();
            this.n = n;
        }

        public void fill()
        {
            int[] ac = new int[] { 0, 0 };
            this.actions.Add(ac);
            ac = new int[] { -1, -1 };
            this.actions.Add(ac);
            ac = new int[] { 0, -1 };
            this.actions.Add(ac);
            ac = new int[] { 1, -1 };
            this.actions.Add(ac);
            ac = new int[] { -1, 0 };
            this.actions.Add(ac);
            ac = new int[] { 1, 0 };
            this.actions.Add(ac);
            ac = new int[] { -1, 1 };
            this.actions.Add(ac);
            ac = new int[] { 0, 1 };
            this.actions.Add(ac);
            ac = new int[] { 1, 1 };
            this.actions.Add(ac);
        }

        public int[] Get_Position()
        {
            return this.position;
        }

        public void Set_Position(int x, int y)
        {
            this.position[0] = x;
            this.position[1] = y;
        }

        public int Get_N()
        {
            return this.n;
        }
    }
}
