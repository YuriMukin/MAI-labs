using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba7rel
{
    class Program
    {
        class B
        {
            public void mB()
            {
                Console.WriteLine("Not static");
            }
        }

        static class C
        {
            public static void mC()
            {
                Console.WriteLine("static");
            }
        }

        class A
        {
            public void m(B b)
            {
                Console.WriteLine("it's class B and hi is");
                b.mB();
                Console.WriteLine();
            }

            public void g()
            {
                Console.WriteLine("it's class C and hi is");
                C.mC();
                Console.WriteLine();
            }
        }

        static void Main(string[] args)
        {
            A a = new A();
            B b = new B();
            a.m(b);
            a.g();
            C.mC();

            Console.ReadKey();
        }
    }
}
