using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    class ATX_Cooler : AbstractComponentCoolingSystem
    {
        public override string CullerName => "Thermalright spb 120";
        public override string CullerPrice => "70";
        public override int square => 2100;
        public override int RMP(int fr, double f)
        {
            double rm = fr*f/10;
            return  (int)rm;
        }
        public override int TDPout(int fr, double f)
        {
            return ( this.square * RMP(fr,f)/10000);
        }
    }
}
