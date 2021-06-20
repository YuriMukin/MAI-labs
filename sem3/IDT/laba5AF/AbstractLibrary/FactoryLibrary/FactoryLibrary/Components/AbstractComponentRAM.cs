using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    public abstract class AbstractComponentRAM
    {
        public abstract string RAMName { get; }
        public abstract string RAMPrice { get; }
        public abstract int RAMVolume { get; }
        public abstract int RAMFrequency { get; }
    }
}
