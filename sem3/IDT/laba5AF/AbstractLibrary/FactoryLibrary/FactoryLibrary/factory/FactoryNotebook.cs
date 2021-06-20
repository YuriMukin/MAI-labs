using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    public class FactoryNotebook : AbstractFactoryPC
    {
        public override AbstractComponentCoolingSystem CreateCooler()
        {
            return new Notebook_Cooler();
        }

        public override AbstractComponentCPU CreateCPU()
        {
            return new Notebook_CPU();
        }

        public override AbstractComponentDrive CreateDrive()
        {
            return new Notebook_Drive();
        }

        public override AbstractComponentGPU CreateGPU()
        {
            return new Notebook_GPU();
        }

        public override AbstractComponentRAM CreateRAM()
        {
            return new Notebook_RAM();
        }
    }
}
