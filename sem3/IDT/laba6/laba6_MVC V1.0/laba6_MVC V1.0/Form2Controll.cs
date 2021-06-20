using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Collections;
using System.Windows.Forms;

namespace laba6_MVC_V1._0
{
    public class Form2Controll
    {
        private model model;
        private Form2 view;
        private PostfixNotationExpression converter;
        private Stack<double> st;

        public Form2Controll(Form2 view, model model)
        {
            this.model = model;
            this.view = view;
            this.converter = new PostfixNotationExpression();
        }

        public Bitmap Drow(double to, double from, double step, string func, int w, int h)
        {
            ArrayList lines = new ArrayList();
            int j = 0;
            st = new Stack<double>();
            int[] k = new int[(int)(((to - from) / step) + 1)];
            double ch;
            bool exep = true;
            string[] fu = converter.ConvertToPostfixNotation(func);
            PointF[] points = new PointF[(int)(((to-from)/step)+1)];
            for (double i = to; i >= from; i -= step)
            {
                foreach (string s in fu)
                {
                    string nwp = s;
                    if (nwp == "x")
                        nwp = Convert.ToString(i);
                    if (double.TryParse(nwp, out ch))
                        st.Push(ch);
                    else
                        exep = oerator(nwp);
                }
                if (exep == false)
                {
                    lines.Add(points);
                    points = new PointF[(int)(((to - from) / step) + 1)];
                    j++;
                    k[j] = 0;
                }
                else
                {
                    double n = st.Pop() * (-1);
                    points[k[j]] = new PointF((float)(i + w / 2), (float)(n + h / 2));
                    k[j]++;
                }
            }
            lines.Add(points);
            return model.Drowing(lines, k);
        }

        public Bitmap ReDrow()
        {
            return model.ReDrowing();
        }

        public bool oerator(string s)
        {
            double op2;
            switch (s)
            {
                case "+":
                    st.Push(st.Pop() + st.Pop());
                    return true;
                    break;
                case "*":
                    st.Push(st.Pop() * st.Pop());
                    return true;
                    break;
                case "-":
                    op2 = st.Pop();
                    st.Push(st.Pop() - op2);
                    return true;
                    break;
                case "/":
                    op2 = st.Pop();
                    if (op2 != 0.0)
                    {
                        st.Push(st.Pop() / op2);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                    break;
                case "^":
                    op2 = st.Pop();
                    st.Push(Math.Pow(st.Pop(), op2));
                    return true;
                    break;
                default:
                    return false;
                    break;
            }
        }
    }
}
