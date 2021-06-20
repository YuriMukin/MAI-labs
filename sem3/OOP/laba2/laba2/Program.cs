using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba2
{
    class A
    {

        public void mA()
        {
            Console.WriteLine("a method of A");
        }

        public K kA
        {
            get { Console.Write("get k ->"); return k; }
        }
        public B bA
        {
            get { Console.Write("get b ->"); return b; }
        }
        private B b = new B();
        private K k = new K();
    }

    class K
    {
        public void mK()
        {
            Console.WriteLine("method of K");
        }

        public J jA
        {
            get { Console.Write("get j ->"); return j; }
        }

        private J j = new J();
    }

    class B
    {
        public void mB()
        {
            Console.WriteLine("method of B");
        }

        public D dA
        {
            get { Console.Write("get d ->"); return d; }
        }

        public E eA
        {
            get { Console.Write("get e ->"); return e; }
        }

        public F fA
        {
            get { Console.Write("get f ->"); return f; }
        }

        private D d = new D();
        private E e = new E();
        private F f = new F();
    }

    class J
    {
        public J() { }
        public void mJ()
        {
            Console.WriteLine(" method of J");
        }
    }

    class D
    {
        public D() { }
        public void mD()
        {
            Console.WriteLine(" method of D");
        }
    }

    class E
    {
        public E() { }
        public void mE()
        {
            Console.WriteLine(" method of E");
        }
    }

    class F
    {
        public F() { }
        public void mF()
        {
            Console.WriteLine(" method of F");
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            A a = new A();
            a.mA();
            a.bA.mB();
            a.kA.mK();

            a.bA.dA.mD();
            a.bA.eA.mE();
            a.bA.fA.mF();

            a.kA.jA.mJ();
            Console.ReadKey();
        }
    }
}

