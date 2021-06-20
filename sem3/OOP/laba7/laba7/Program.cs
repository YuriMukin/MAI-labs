using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba7
{
    class Program
    {
        public class computer
        {
            private string spec;
            private monitor[] m = null;
            private int numb, max;
            private mous mu;

            public mous Mu { get { return mu; } }

            public computer(string s) //стандартный конструктор
            {
                this.spec = s;
                this.max = 3;
                this.m = new monitor[max];
                numb = 0;
                this.mu = null;
            }

            public computer(string s, int k) //на случай передачи максимального кол-во мониторов
            {
                this.spec = s;
                this.max = k+1;
                this.m = new monitor[max];
                numb = 0;
                this.mu = null;
            }

            public computer(string s, monitor e, int k) //на случай конекта монетора и передачи макс. кол-во мониторов
            {
                this.spec = s;
                this.max = k+1;
                this.m = new monitor[max];
                this.numb = 0;
                this.m[numb] = e;
                this.numb++;
                this.mu = null;
            }

            public computer(string s, monitor e) //на случай подключения монитора
            {
                this.spec = s;
                this.max = 3;
                this.m = new monitor[max];
                this.numb = 0;
                this.m[numb] = e;
                e.ConPC(this);
                this.numb++;
                this.mu = null;
            }

            public void AddMon(monitor e) //добавление монитора 1-N
            {
                if (this.numb < this.max)
                {
                    this.m[numb] = e;
                    this.numb++;
                    e.ConPC(this);
                    Console.WriteLine("\nmonitor №{0} wos connected!\n", numb);
                }
                else
                    Console.WriteLine("mximum number of monitors was reached!");
            }

            public void Mcon(mous m)//добавление мыши 1-1
            {
                this.mu = m;
                m.PtoM(this);
                Console.WriteLine("\nmouse wos connected!\n");
            }

            public void SpecOut()
            {
                Console.WriteLine("{0} \n{1} monitors conected/max monitors number {2}",this.spec, this.numb, this.max);
            }

            public monitor GetMS(int i)
            {
                if (i-1<=this.numb)
                    return this.m[i-1];
                else
                return null;
            }
        }

        public class monitor
        {
            private string name;
            private int resX, resY;
            private computer PC;

            public computer pc { get { return PC; } }

            public monitor(string s)
            {
                this.name = s;
                this.resX = 1080;
                this.resY = 1920;
            }

            public monitor(string s, int x, int y)
            {
                this.name = s;
                this.resX = x;
                this.resY = y;
            }

            public void ConPC(computer p)
            {
                this.PC = p;
            }

            public void MonInfo()
            {
                Console.WriteLine("it's {0}, with resolution {1}x{2}", this.name, this.resX, this.resY);
            }

            public int QtyPix()
            {
                return (this.resX * this.resY);
            }
        }

        public class mous
        {
            private computer perC;
            private string nameM;
            private int dpi;

            public mous(string n, int d)
            {
                this.dpi = d;
                this.nameM = n;
                this.perC = null;
            }

            public computer PerC { get { return perC; } }

            public void PtoM(computer c)
            {
                this.perC = c;
            }

            public void aboutM()
            {
                Console.WriteLine("it's {0}, with DPI {1}", this.nameM, this.dpi);
            }
        }

        static void Main(string[] args)
        {
            monitor mon0 = new monitor("ASUS");
            monitor mon1 = new monitor("LG", 720, 1280);
            monitor mon2 = new monitor("IIyama");
            computer PC = new computer("i7-6700k,16gb,gtx10170,256gb", mon0,2);
            mous mu = new mous("logitec", 6000);
            PC.Mcon(mu);
            mu.PerC.SpecOut();
            Console.WriteLine();
            PC.Mu.aboutM();
            PC.AddMon(mon2);
            PC.AddMon(mon1);
            Console.WriteLine();
            for (int i=1; i<=3; i++)
                PC.GetMS(i).MonInfo();
            Console.WriteLine();
            mon2.pc.SpecOut();
            Console.WriteLine();
            Console.WriteLine("monitor namber 3 consist {0} pixels", PC.GetMS(3).QtyPix());
            Console.ReadKey();
        }
    }
}
