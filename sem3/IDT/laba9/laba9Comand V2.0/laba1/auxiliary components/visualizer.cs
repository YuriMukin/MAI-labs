using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1
{
    class visualizer : helper
    {
        private laba9Comand WorcingPlace;
        private DataGridView ProcesObj;

        public visualizer(laba9Comand wp, ref DataGridView po0)
        {
            this.WorcingPlace = wp;
            this.ProcesObj = po0;
        }

        public override void execution()
        {
            for (int i = 0; i < WorcingPlace.M3; ++i)
                for (int j = 0; j < WorcingPlace.N3; ++j)
                    ProcesObj.Rows[i].Cells[j].Value = WorcingPlace.m3.mat[i, j].ToString();
        }
    }
}
