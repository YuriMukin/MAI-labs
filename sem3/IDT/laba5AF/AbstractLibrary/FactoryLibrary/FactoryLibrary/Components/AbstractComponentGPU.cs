using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    public abstract class AbstractComponentGPU
    {
        public abstract string GPUName { get; }
        public abstract string GPUPrice { get; }
        public abstract int CorsCount { get; }
        public abstract int GPUTDP { get; }
        public abstract int GPUFrequency { get; }
        public abstract int drows(int resX, int resY);
    }
}
