using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba1
{
    class TextChangeTBN1 : Comand
    {
        private laba9Comand WorcingPlace;
        private TextBox WorcObj;
        private DataGridView ProcesObj;

        public TextChangeTBN1(laba9Comand wp, ref TextBox wj, ref DataGridView po)
        {
            this.WorcingPlace = wp;
            this.WorcObj = wj;
            this.ProcesObj = po;
        }

        public override void execution()
        {
            if (WorcObj.Text.All(char.IsDigit) && WorcObj.Text != "")
            {
                ProcesObj.ColumnCount = Int32.Parse(WorcObj.Text);
                WorcingPlace.N1 = Int32.Parse(WorcObj.Text);
            }
            else if (WorcObj.Text != "")
            {
                WorcObj.Text = WorcObj.Text.Substring(0, (WorcObj.Text.Length - 1));
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }
    }
}
