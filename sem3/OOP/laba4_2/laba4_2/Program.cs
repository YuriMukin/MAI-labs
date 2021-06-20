using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba4_2
{
    class Program
    {
        public interface D
        {
            void mD();
        }

        public interface E
        {
            void mE();
        }

        public interface F
        {
            void mF();
        }

        public class B : D, E, F
        {
            public void mB()
            {
                Console.WriteLine("method of B");
            }

            public void mD()
            {
                Console.WriteLine("method of D");
            }

            public void mE()
            {
                Console.WriteLine("method of E");
            }

            public void mF()
            {
                Console.WriteLine("method of F");
            }
        }

        public interface C
        {
            void mC();
        }

        public interface K : C
        {
            void mK();
        }

        public class A : B, K
        {
            public void mA()
            {
                Console.WriteLine("method of A");
            }

            public void mC()
            {
                Console.WriteLine("method of C");
            }

            public void mK()
            {
                Console.WriteLine("method of K");
            }
        }

        static void Main(string[] args)
        {
            C c = new A();
            c.mC();
            Console.WriteLine();
            K k = (K)c;
            //k.mC();
            k.mK();
            Console.WriteLine();
            A a = (A)k;
            //a.mC();
            //a.mK();
            a.mA();
            /*a.mA();
            a.mK();
            a.mC();
            a.mB();
            a.mD();
            a.mE();
            a.mF();*/
            Console.ReadKey();
        }
    }
}
