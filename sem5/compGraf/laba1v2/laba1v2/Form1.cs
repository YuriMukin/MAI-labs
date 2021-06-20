using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Drawing;
using System.Timers;
using System.Linq.Expressions;

namespace laba1v2
{
    public partial class Form1 : Form
    {
        private function f;
        private double ex, mxs, mys, approximation;
        private System.Timers.Timer timer0, timer1;

        public Form1()
        {
            InitializeComponent();
            name.AutoSize = false;//наводим красоту 
            name.Paint += name_Paint; ;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            ex = 0;
            drawing();
            timer0 = new System.Timers.Timer();//таймер для приближения/удаления (можно обойтись и без этого, но таким образом можно добиться плавного перехода)
            timer0.Interval = 40; //1000 миллисекунд = 1с => 1000/40=25 перерисовок в секунду. Больше лучше,но увеличивает нагрузку
            timer0.AutoReset = true;
            timer0.Enabled = true;
            timer0.Elapsed += new ElapsedEventHandler(resize);
            timer1 = new System.Timers.Timer();//таймер для смещения (ситуация аналогична первому таймеру)
            timer1.Interval = 40;
            timer1.AutoReset = true;
            timer1.Enabled = false;
            timer1.Elapsed += new ElapsedEventHandler(moving);
        }

        //обрабатываем нажатие на кнопку
        private void draw_Click(object sender, EventArgs e)
        {
            try
            {
                drawing();
            }
            catch
            {
                MessageBox.Show("Incorrect value entered", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        //реагируем на прокрутку колесика 
        private void chart1_MouseWheel(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            ex += -(double)e.Delta / 1200; 
        }

        private void resize(object sender, ElapsedEventArgs e)//эту функцию использует нулевой таймер 
        {
            try
            {
                bool t1 = chart1.ChartAreas[0].AxisX.Minimum - ex != chart1.ChartAreas[0].AxisX.Maximum + ex; //убедимся, что пытаемся установить адекватные границы 
                bool t2 = chart1.ChartAreas[0].AxisY.Minimum - ex != chart1.ChartAreas[0].AxisY.Maximum + ex;
                bool t3 = (Math.Abs(chart1.ChartAreas[0].AxisX.Minimum - ex) > 0.1) && (Math.Abs(chart1.ChartAreas[0].AxisX.Maximum + ex) > 0.1) 
                    && (Math.Abs(chart1.ChartAreas[0].AxisY.Minimum - ex) > 0.1) && (Math.Abs(chart1.ChartAreas[0].AxisY.Maximum + ex) > 0.1);
                if (t1 && t2 && t3)
                {
                    this.chart1.BeginInvoke((MethodInvoker)(delegate //таймер создает новый поток поэтому применяем магию многопоточности 
                    {
                        this.chart1.ChartAreas[0].AxisX.Minimum = this.chart1.ChartAreas[0].AxisX.Minimum - ex; //смещаем границы
                        this.chart1.ChartAreas[0].AxisX.Maximum = this.chart1.ChartAreas[0].AxisX.Maximum + ex;
                        this.chart1.ChartAreas[0].AxisY.Minimum = this.chart1.ChartAreas[0].AxisY.Minimum - ex;
                        this.chart1.ChartAreas[0].AxisY.Maximum = this.chart1.ChartAreas[0].AxisY.Maximum + ex;
                        ex = 0; //обнуляем смещение для корректной обработки дальнейших изменений масштаба 
                    }));
                }
                this.chart1.BeginInvoke((MethodInvoker)(delegate //таймер создает новый поток поэтому применяем магию многопоточности 
                {
                    ex = 0; //не смотря ни на что обнуляем смещение 
                }));
            }
            catch
            { 
            }
        }

        private void moving(object sender, ElapsedEventArgs e)//эту функцию использует первый таймер 
        {
            try
            {
                this.chart1.BeginInvoke((MethodInvoker)(delegate
                {//определить сместился курсор и с поправкой на масштаб смещается график 
                    this.chart1.ChartAreas[0].AxisX.Minimum = this.chart1.ChartAreas[0].AxisX.Minimum + (mxs - Cursor.Position.X) / approximation; 
                    this.chart1.ChartAreas[0].AxisX.Maximum = this.chart1.ChartAreas[0].AxisX.Maximum + (mxs - Cursor.Position.X) / approximation;
                    this.chart1.ChartAreas[0].AxisY.Minimum = this.chart1.ChartAreas[0].AxisY.Minimum + (-mys + Cursor.Position.Y) / approximation;
                    this.chart1.ChartAreas[0].AxisY.Maximum = this.chart1.ChartAreas[0].AxisY.Maximum + (-mys + Cursor.Position.Y) / approximation;
                    mxs = Cursor.Position.X;//меняем старые текущие позиции на новые
                    mys = Cursor.Position.Y;
                }));
            }
            catch
            {
            }
        }

        private void drawing()
        {
            //пересчитываем значение функции с заданными значениями
            f = new function(Convert.ToDouble(from.Text), Convert.ToDouble(to.Text), Convert.ToDouble(step.Text), Convert.ToDouble(constanta.Text));
            this.chart1.ChartAreas[0].AxisX.Minimum = f.Xmin;//устанавливаем актуальные границы
            this.chart1.ChartAreas[0].AxisX.Maximum = f.Xmax;
            this.chart1.ChartAreas[0].AxisY.Minimum = f.Ymin;
            this.chart1.ChartAreas[0].AxisY.Maximum = f.Ymax;
            chart1.Series[0].Points.Clear();//очищаем панель
            chart1.Series[0].Name = "r = " + constanta.Text + "sin(2*fi)" + '\n' + from.Text + "<=fi<=" + to.Text;//подписываем график
            foreach (PointF p in f.points)//добавляем все вычисленные значения 
                chart1.Series[0].Points.AddXY(p.X, p.Y);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            //останавливаем оба таймера, чтобы избежать ошибок вызванных завершением основного потока
            timer0.Enabled = false;
            timer1.Enabled = false;
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {//останавливаем таймер 0, чтобы окно было приятно перетаскивать(есть неприятные фризы если этого не сделать)
            timer0.Enabled = false;
        }

        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
            timer0.Enabled = true;
        }

        private void chart1_MouseDown(object sender, MouseEventArgs e)
        {//включаем таймер для скроллинга графика и запоминаем начальное положение курсора
            timer0.Enabled = false;
            mxs = Cursor.Position.X;
            mys = Cursor.Position.Y;
            approximation = (int)(600 / (Math.Abs(f.Xmin) + Math.Abs(f.Xmax)));
            timer1.Enabled = true;
        }

        private void chart1_MouseUp(object sender, MouseEventArgs e)
        {
            timer0.Enabled = true;
            timer1.Enabled = false;
        }

        //наводим красоту 
        private void name_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.Clear(this.BackColor);
            e.Graphics.RotateTransform(-90);
            SizeF textSize = e.Graphics.MeasureString(name.Text, name.Font);
            name.Width = (int)textSize.Height + 2;
            name.Height = (int)textSize.Width + 2;
            e.Graphics.TranslateTransform(-name.Height / 2, name.Width / 2);
            e.Graphics.DrawString(name.Text, name.Font, Brushes.Black, -(textSize.Width / 2), -(textSize.Height / 2));
        }
    }
}
