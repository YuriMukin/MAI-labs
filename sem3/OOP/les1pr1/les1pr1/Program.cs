using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace les1pr1
{
    class Program
    {
        static void Main(string[] args)
        {
            geomVector fer0 = new geomVector(6, 0, 7);//задание векторов
            geomVector fer1 = new geomVector(8, 9, 3);
            geomVector fer2 = new geomVector();
            geomVector fer3 = new geomVector();
            fer0.infoOut();
            fer1.infoOut();
            int s = fer0.scalar(fer1);
            int v = fer0.vectorp(fer1);
            Console.WriteLine(" skalara = {0}; vect = {1}\n", s, v);
            fer2 = fer0 - fer1;
            fer3 = fer0 + fer1;
            fer2.infoOut();
            fer3.infoOut();
            Console.WriteLine(" modul of fer1 = {0}\n", fer1.Modul());
            Console.ReadKey();
        }
    }
}
