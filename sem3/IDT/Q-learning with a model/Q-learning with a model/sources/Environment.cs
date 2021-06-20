using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.CodeDom;
using System.Collections;
using System.Diagnostics;
using System.Threading;

namespace Q_learning_with_a_model
{
    class Environment
    {
        private int[,] field;
        public Protagonist protagonist;
        private ArrayList enemys;
        private Q_model model;
        private model m;
        private bool is_end;

        public Environment(int n, int[] PP, int[,] EP, Q_model model, model m)
        {
            this.enemys = new ArrayList();
            this.model = model;
            this.m = m;
            this.field = new int[n, n];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    this.field[i, j] = 0;
            this.protagonist = new Protagonist(PP[0], PP[1], n, enemys, this, model);
            model.Set_Protagonist(this.protagonist);
            for (int i = 0; i < EP.GetLength(0); i++)
            {
                Enemy en = new Enemy(EP[i, 0], EP[i, 1], n);
                this.enemys.Add(en);
            }
        }

        public void Iteration()
        {
            foreach (Enemy en in this.enemys)
                en.Make_Step();
            this.protagonist.Make_Step();
        }

        public void Get_Reward(bool is_end)
        {
            if (is_end)
                this.protagonist.reward = 1;
            else
                this.protagonist.reward = -1;
        }

        public void Update_Field()
        {
            int n = this.field.GetLength(0);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    this.field[i, j] = 0;
            this.field[this.protagonist.Get_Position()[0], this.protagonist.Get_Position()[1]] = 1;
            foreach (Enemy en in this.enemys)
                this.field[en.Get_Position()[0], en.Get_Position()[1]] = 2;
        }

        public bool Is_finished()
        {
            bool end = false;
            foreach (Enemy en in enemys)
            {
                if ((protagonist.Get_Position()[0] == en.Get_Position()[0]) && (protagonist.Get_Position()[1] == en.Get_Position()[1]))
                    end = true;
            }
            return end;
        }

        public void Print_Fild()
        {
            int k = 0;
            foreach (int i in field)
            {
                if (k % field.GetLength(0) == 0)
                    Debug.Write("\n");
                Debug.Write(i);
                k++;
            }
            //Console.WriteLine("___");
        }

        public int play(bool silent)
        {
            is_end = Is_finished();
            int iter = 0;
            while (!is_end)
            {
                Iteration();
                Update_Field();
                is_end = Is_finished();
                Get_Reward(is_end);
                if (silent)
                    model.Ran_Model(silent);
                else
                {
                    //Print_Fild();
                    //Debug.WriteLine("_____");
                    m.draw(field);
                    Thread.Sleep(200);
                }
                iter++;
            }
            return iter;
        }
    }
}
