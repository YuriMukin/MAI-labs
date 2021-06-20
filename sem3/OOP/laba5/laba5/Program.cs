using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba5
{
    public interface IA
    {
        void mIA();
    }

    public interface IC : IA
    {
        void met();
    }

    public class B : IA
    {
        public void met()
        {
            Console.WriteLine("method of B");
        }

        public void mIA()
        {
            Console.WriteLine("method of IA");
        }
    }

    public class D : B, IC
    {
        public void mD()
        {
            Console.WriteLine("method of D");
        }

        public void met()
        {
            Console.WriteLine("method of IC");
        }
    }
    /*
            D
           / \
          B   IC
           \ /
            IA
     */

    class Program
    {
        static void Main(string[] args)
        {
            IC d=new D();
            d.met();
            ((B)d).met();
            Console.ReadKey();
        }
    }
}
