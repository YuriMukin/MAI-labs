using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    public abstract class AbstractFactoryPC
    {
        public abstract AbstractComponentCPU CreateCPU();
        public abstract AbstractComponentGPU CreateGPU();
        public abstract AbstractComponentRAM CreateRAM();
        public abstract AbstractComponentDrive CreateDrive();
        public abstract AbstractComponentCoolingSystem CreateCooler();
    }
}
