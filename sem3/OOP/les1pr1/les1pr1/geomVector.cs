using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace les1pr1
{
    class geomVector
    {
        public int xCor;
        public int yCor;
        public int zCor;

        public geomVector(int x, int y, int z)// конструктор класса
        {
            this.xCor = x;
            this.yCor = y;
            this.zCor = z;
        }

        public geomVector()// конструктор класса по умолчанию
        {
            this.xCor = 0;
            this.yCor = 0;
            this.zCor = 0;
        }

        public void infoOut() //вывод координат
        {
            int a = this.xCor; int b = this.yCor; int c = this.zCor;
            Console.WriteLine(" X coord.- {0}, Y coord.- {1}, Z coord.- {2}\n", a, b, c);
        }

        public int scalar(geomVector b)//скалярное произведение
        {
            return (this.xCor * b.xCor + this.yCor * b.yCor + this.zCor * b.zCor);
        }

        public int vectorp(geomVector b)//векторное произведение
        {
            return (this.yCor * b.zCor - this.zCor * b.yCor - this.xCor * b.zCor + b.xCor * this.zCor + this.xCor * b.yCor - b.xCor * this.yCor);
        }

        public static geomVector operator +(geomVector a, geomVector b)//перегрузка сложения
        {
            return new geomVector(a.xCor + b.xCor, a.yCor + b.yCor, a.zCor + b.zCor);
        }

        public static geomVector operator -(geomVector a, geomVector b)//перегрузка вычитания
        {
            return new geomVector(a.xCor - b.xCor, a.yCor - b.yCor, a.zCor - b.zCor);
        }

        public double Modul()//метод для нахождения модуля
        {
            return (Math.Sqrt(this.xCor * this.xCor + this.yCor * this.yCor + this.zCor * this.zCor));
        }
    }
}
