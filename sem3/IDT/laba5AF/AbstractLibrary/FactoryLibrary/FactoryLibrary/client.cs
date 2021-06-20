using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    public class client
    {
        public AbstractComponentCPU CPU { get; set; }
        public AbstractComponentGPU GPU { get; set; }
        public AbstractComponentRAM RAM { get; set; }
        public AbstractComponentDrive Drive { get; set; }
        public AbstractComponentCoolingSystem Cooler { get; set; }

        public client(AbstractFactoryPC factory)
        {
            this.CPU = factory.CreateCPU();
            this.GPU = factory.CreateGPU();
            this.RAM = factory.CreateRAM();
            this.Drive = factory.CreateDrive();
            this.Cooler = factory.CreateCooler();
        }

        public int price()
        {
            if (CPU != null && GPU != null && RAM != null && Drive != null && Cooler != null)
            {
                return int.Parse(CPU.CPUPrice + GPU.GPUPrice + RAM.RAMPrice + Drive.DrivePrice + Cooler.CullerPrice);
            }
            else
            {
                return 0;
            }
        }

        public int[] work()
        {
            int[] mon = new int[2];
            mon[0] = this.CPU.temp(this.Cooler.TDPout(this.CPU.CPUFrequency + this.CPU.FrequencyErr, this.CPU.voltage));
            mon[1] = this.Cooler.RMP(this.CPU.CPUFrequency + this.CPU.FrequencyErr, this.CPU.voltage);
            return mon;
        }
    }
}
