using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    public abstract class AbstractComponentCoolingSystem
    {
        public abstract string CullerName { get; }
        public abstract string CullerPrice { get; }
        public abstract int RMP(int fr, double f);
        public abstract int square { get; }
        public abstract int TDPout(int fr, double f);
    }
}
