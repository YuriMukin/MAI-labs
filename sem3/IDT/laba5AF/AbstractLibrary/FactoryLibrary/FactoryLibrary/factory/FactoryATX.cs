using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    public class FactoryATX : AbstractFactoryPC
    {
        public override AbstractComponentCoolingSystem CreateCooler()
        {
            return new ATX_Cooler();
        }

        public override AbstractComponentCPU CreateCPU()
        {
            return new ATX_CPU();
        }

        public override AbstractComponentDrive CreateDrive()
        {
            return new ATX_Drive();
        }

        public override AbstractComponentGPU CreateGPU()
        {
            return new ATX_GPU();
        }

        public override AbstractComponentRAM CreateRAM()
        {
            return new ATX_RAM();
        }
    }
}
