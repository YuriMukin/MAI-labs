using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    public abstract class AbstractComponentDrive
    {
        public abstract string DriveName { get; }
        public abstract string DrivePrice { get; }
        public abstract int DriveSpead { get; }
    }
}
