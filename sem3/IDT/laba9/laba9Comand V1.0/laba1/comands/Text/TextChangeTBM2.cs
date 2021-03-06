using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1
{
    class TextChangeTBM2 : Comand
    {
        private laba9Comand WorcingPlace;
        private TextBox WorcObj;
        private DataGridView ProcesObj;

        public TextChangeTBM2(laba9Comand wp, ref TextBox wj, ref DataGridView po)
        {
            this.WorcingPlace = wp;
            this.WorcObj = wj;
            this.ProcesObj = po;
        }

        public override void execution()
        {
            if (WorcObj.Text.All(char.IsDigit) && WorcObj.Text != "")
            {
                ProcesObj.RowCount = Int32.Parse(WorcObj.Text);
                WorcingPlace.M2 = Int32.Parse(WorcObj.Text);
            }
            else if (WorcObj.Text != "")
            {
                WorcObj.Text = WorcObj.Text.Substring(0, (WorcObj.Text.Length - 1));
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
    }
}
