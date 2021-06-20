using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba3_4
{
    class Program
    {
        abstract class shape
        {
            public shape(string n_ame)
            {
                this.name = n_ame;
            }
            protected string name;

            public string Name => name;

            public void PrintInfo()
            {
                Console.WriteLine("it's just a {0}", this.name);
            }

            public abstract double area();
            public abstract double perimeter();
        }

        class circal : shape
        {
            protected double rad { get; set; }
            public circal(string name, double radius)
                : base(name)
            {
                this.rad = radius;
            }
            public double Rad { get => rad; }
            public override double area()
            {
                return (this.rad * this.rad * Math.PI);
            }

            public override double perimeter()
            {
                return (this.rad * Math.PI * 2);
            }
        }

        class parallelepiped : shape
        {
            public parallelepiped(string name, double e1, double e2, double an)
                : base(name)
            {
                this.edge1 = e1;
                this.edge2 = e2;
                this.angle = an;
            }

            protected double edge1, edge2, angle;

            public double Edge1
            {
                get => edge1;
                set => edge1 = value;
            }

            public double Edge2
            {
                get => edge2;
                set => edge2 = value;
            }

            public double Angle
            {
                get => angle;
                set => angle = value;
            }

            public override double area()
            {
                return (this.edge1 * this.edge2 * Math.Sin(this.angle));
            }

            public override double perimeter()
            {
                return (this.edge1 * 2 + this.edge2 * 2);
            }

            public bool IsSquare()
            {
                return (this.edge1 == this.edge2 && this.angle == 90.0);
            }
        }

        class square : parallelepiped
        {
            public square(string name, double edge)
                : base(name, edge, edge, 90) { }

            public double diag()
            {
                return (Math.Sqrt(this.edge1 * this.edge1 * 2));
            }

            public double re
            {
                get => edge1;
                set
                {
                    edge1 = value;
                    edge2 = value;
                    angle = 90;
                }
            }
        }

        class triangle : shape
        {
            public double D1 { get; set; }
            public double D2 { get; set; }
            public double D3 { get; set; }

            public triangle(string name, double d1, double d2, double d3)
                : base(name)
            {
                this.D1 = d1;
                this.D2 = d2;
                this.D3 = d3;
            }

            public override double area()
            {
                double p = this.perimeter();
                return (Math.Sqrt(p * (p - D1) * (p - D2) * (p - D3)));
            }

            public override double perimeter()
            {
                return (D1 + D2 + D3);
            }

            public bool IsRight()
            {
                return (D1 * D1 + D2 * D2 == D3 * D3 || D3 * D3 + D2 * D2 == D1 * D1 || D1 * D1 + D3 * D3 == D2 * D2);
            }
        }

        static void Main(string[] args)
        {
            shape[] arr = new shape[6];

            arr[0] = new circal("circle", 3);
            arr[1] = new parallelepiped("parallelepiped", 3, 7, 60);
            arr[2] = new parallelepiped("parallelepiped", 7, 7, 90);
            arr[3] = new square("square", 3);
            arr[4] = new triangle("triangle", 4, 6, 3);
            arr[5] = new triangle("triangle", 4, 6, Math.Sqrt(20));

            foreach (shape el in arr)
            {
                el.PrintInfo();
                Console.WriteLine("area={0}", el.area());
                Console.WriteLine("perimeter={0}", el.perimeter());

                if (el is circal)
                {
                    circal th = (circal)el;
                    Console.WriteLine("rad. is {0}", th.Rad);
                }
                if (el is parallelepiped)
                {
                    parallelepiped th = (parallelepiped)el;
                    Console.WriteLine("Is is square? {0}", th.IsSquare() ? "yes" : "no");
                }
                if (el is square)
                {
                    square th = (square)el;
                    Console.WriteLine("edge = {0}, diag = {1}", th.re, th.diag());
                }
                if (el is triangle)
                {
                    triangle th = (triangle)el;
                    Console.WriteLine("desh 1={0} desh 2={1} desh 3={2}", th.D1, th.D2, th.D3);
                    Console.WriteLine("is rectangular? {0}", th.IsRight() ? "yes" : "no");
                }
                Console.WriteLine("\n");
            }
            Console.ReadKey();
        }
    }
}

