using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;
using System.Diagnostics;

namespace laba1v2
{
    class drawer
    {
        private Bitmap graf;
        private Pen pen0, pen1;
        private Graphics DrawPl;

        public drawer()
        {
            this.pen0 = new Pen(Color.Black, 2);
            this.pen1 = new Pen(Color.FromArgb(100, 128, 128, 128), 1);
        }
        public Bitmap draw(int wighd, int height)
        {
            this.graf = new Bitmap(wighd, height);
            this.DrawPl = Graphics.FromImage(this.graf);
            DrawPl.DrawLine(pen0, 0, height / 2, wighd, height / 2);
            DrawPl.DrawLine(pen0, wighd / 2, 0, wighd / 2, height);
            return this.graf;
        }
    }
}
