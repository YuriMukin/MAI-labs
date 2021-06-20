using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    class Notebook_RAM : AbstractComponentRAM
    {
        public override string RAMName => "samsung bdye";
        public override string RAMPrice => "110";
        public override int RAMFrequency => 2400;
        public override int RAMVolume => 16384;
    }
}
