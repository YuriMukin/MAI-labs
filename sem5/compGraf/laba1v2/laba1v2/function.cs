using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;

namespace laba1v2
{
    //тут будем вычислять набор значений для построения графика 
    class function
    {
        private double a;
        public float Ymax, Ymin, Xmax, Xmin;
        public Stack<PointF> points;
        public function(double st, double ed, double sp, double a)
        {
            this.a = a;
            this.VoVal(st, ed, sp);
        }

        //пройдемся по промежутку заданному пользователем с заданным шагом и найдите значения миемумов и максимумов
        public void VoVal(double st, double ed, double sp)
        {
            PointF tmp = value(st);
            Ymax = tmp.Y;
            Xmax = tmp.X;
            Ymin = Ymax;
            Xmin = Xmax;
            this.points = new Stack<PointF>();
            for (double i = st; i <= ed; i += sp)
            {
                tmp = value(i);
                this.points.Push(tmp);
                if (tmp.Y > Ymax)
                    Ymax = tmp.Y;
                if (tmp.Y < Ymin)
                    Ymin = tmp.Y;
                if (tmp.X > Xmax)
                    Xmax = tmp.X;
                if (tmp.X < Xmin)
                    Xmin = tmp.X;
            }
        }
        // преобразуем полярные координаты в декартовы
        public PointF value(double phi)
        {
            return new PointF((float)(this.r(phi) * Math.Cos(phi)), (float)(this.r(phi) * Math.Sin(phi)));
        }
        //вычисляем значение радиус вектора 
        private double r(double phi)
        {
            return this.a * Math.Cos(3*phi);
        }
    }
}
