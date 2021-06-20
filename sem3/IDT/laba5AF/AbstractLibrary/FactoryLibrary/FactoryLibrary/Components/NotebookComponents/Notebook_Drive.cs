using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryLibrary
{
    class Notebook_Drive : AbstractComponentDrive
    {
        public override string DriveName => "samsung evo";
        public override string DrivePrice => "100";
        public override int DriveSpead => 623;
    }
}
