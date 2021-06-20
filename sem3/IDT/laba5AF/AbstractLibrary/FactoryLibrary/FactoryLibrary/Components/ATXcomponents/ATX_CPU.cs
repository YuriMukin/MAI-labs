using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    class ATX_CPU : AbstractComponentCPU
    {
        Random rnd = new Random(99);
        public override string CPUName => "core i7-7700k";
        public override string CPUPrice => "360";
        public override int CorsCount => 4;
        public override int TreadsCount => 8;
        public override int CPUFrequency => 4700;
        public override double voltage => 1.25;
        public new int FrequencyErr = 0;
        public override int temp(int td)
        {
            this.FrequencyErr = Math.Abs(rnd.Next() % 100);
            double t = this.voltage * (this.CPUFrequency + this.FrequencyErr) / td;
            return (int)t;
        }
    }
}
