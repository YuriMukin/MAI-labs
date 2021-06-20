using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    class Notebook_GPU : AbstractComponentGPU
    {
        public override string GPUName => "gtx xxxx";
        public override string GPUPrice => "500";
        public override int CorsCount => 2560;
        public override int GPUFrequency => 1000;
        public override int GPUTDP => 80;
        public override int drows(int resX, int resY)
        {
            return  (this.CorsCount * this.GPUFrequency*50)/ (resX * resY);
        }
    }
}
