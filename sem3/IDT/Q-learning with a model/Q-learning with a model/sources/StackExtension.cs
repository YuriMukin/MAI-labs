using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Q_learning_with_a_model
{
    public static class StackExtension
    {
        public static Stack<T> Copy<T>(this Stack<T> l1)
        {
            Stack<T> cop = new Stack<T>();
            //Debug.WriteLine(l1.Count);
            T[] tmp = new T[l1.Count];
            l1.CopyTo(tmp, 0);
            for (int i = 0; i < l1.Count; i++)
            {
                //Debug.Write(i + " ");
                cop.Push(tmp[i]);
            }
            //Debug.WriteLine(" ");
            return cop;
        }

        public static Stack<T> Cut<T>(this Stack<T> l1, int a)
        {
            if (a < l1.Count)
            {
                Stack<T> cop = new Stack<T>();
                //Debug.WriteLine(l1.Count);
                T[] tmp = new T[l1.Count];
                l1.CopyTo(tmp, 0);
                for (int i = 0; i < l1.Count - a; i++)
                {
                    //Debug.Write(i + " ");
                    cop.Push(tmp[i]);
                }
                //Debug.WriteLine(" ");
                return cop;
            }
            else
                return l1;
        }

        public static string CopyToString<T>(this Stack<T> l1)
        {
            string cop = "";
            //Debug.WriteLine(l1.Count);
            T[] tmp = new T[l1.Count];
            l1.CopyTo(tmp, 0);
            for (int i = 0; i < l1.Count; i++)
            {
                //Debug.Write(i + " ");
                cop += tmp[i].ToString();
            }
            //Debug.WriteLine(" ");
            return cop;
        }

        public static Stack<double> Max(this Stack<double> l1)
        {
            Stack<double> cop = new Stack<double>();
            double[] tmp = new double[l1.Count];
            l1.CopyTo(tmp, 0);
            double max = tmp[0];
            for (int i = 1; i < l1.Count; i++)
            {
                if (tmp[i] > max)
                    max = tmp[i];
            }
            cop.Push(max);
            return cop;
        }
    }
}
