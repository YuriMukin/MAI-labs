using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    public abstract class AbstractComponentCPU
    {
        public abstract string CPUName { get; }
        public abstract string CPUPrice { get; }
        public abstract int CorsCount { get; }
        public abstract int temp(int td);
        public abstract int TreadsCount { get; }
        public abstract double voltage { get; }
        public abstract int CPUFrequency { get; }
        public int FrequencyErr;
    }
}
