using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Q_learning_with_a_model
{
    public partial class Form1 : Form, IObserver
    {
        public delegate void InvokeRefreshDelegate();
        private controller controller;
        private model model;
        private Graphics plase;
        private bool lang;
        private int n;
        private string info, title;

        public Form1(model model)
        {
            InitializeComponent();
            this.model = model;
            this.model.Register(this);
            model.Register(this);
            lang = true;
            Set_Language();
            attachController(makeController());
        }

        public void Set_Language()
        {
            if (lang)
            {
                toolTip1.SetToolTip(enm_count, "Enter the number of enemies");
                toolTip1.SetToolTip(lear_iters, "Enter the number of training attempts");
                toolTip1.SetToolTip(modulat_coubt, "Number of demo modulation");
                toolTip1.SetToolTip(fild_size, "Side Size");
                toolTip1.SetToolTip(enemy_coord, "The initial coordinates of the enemies on the field");
                toolTip1.SetToolTip(score, "The number of points scored agents");
                toolTip1.SetToolTip(progressBar1, "Learning process");
                toolTip1.SetToolTip(panel1, "Battlefield");
                start.Text = "Start";
                info = "The program emulates a game of blind men. from 1 to n opponents 'blindly' try to find \n an agent on a field of size n-n, who, in turn, learns to escape from them using the Q-learning algorithm";
                title = "Information";
            }
            else
            {
                toolTip1.SetToolTip(enm_count, "Количество противников");
                toolTip1.SetToolTip(lear_iters, "Количество циклов обучения");
                toolTip1.SetToolTip(modulat_coubt, "Количество демонстрационных симуляций");
                toolTip1.SetToolTip(fild_size, "Казмер поля");
                toolTip1.SetToolTip(enemy_coord, "Начальные координаты противников на поле");
                toolTip1.SetToolTip(score, "Количество очков набранных агентом в ходе соревнования");
                toolTip1.SetToolTip(progressBar1, "Процесс обучения");
                toolTip1.SetToolTip(panel1, "Поле");
                start.Text = "Запустить";
                info = "программа эмулирует игру в жмурки. от 1 до n противников 'в слепую' пытаются отыскать \n агента на поле размером n-n, тот, в свою очередь учится сбегать от них с помощью алгоритма Q-learning";
                title = "краткая справка";
            }
        }

        public void attachController(controller controller)
        {
            this.controller = controller;
        }

        protected controller makeController()
        {
            return new controller(this, model);
        }

        private void enm_count_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (enm_count.Text != "")
                enemy_coord.RowCount = Convert.ToInt32(enm_count.Text);
                n= Convert.ToInt32(enm_count.Text);
            }
            catch
            {
                enm_count.Text = "";
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            enemy_coord.ColumnCount = 2;
            score.ColumnCount = 1;
            progressBar1.Maximum = 100;
            plase = Graphics.FromHwnd(panel1.Handle);
        }

        private void lear_iters_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (lear_iters.Text != "")
                    progressBar1.Maximum = Convert.ToInt32(lear_iters.Text);
            }
            catch
            {
                lear_iters.Text = "";
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        public void UpdateState()
        {
            if (controller != null)
            {
                if (model.silent)
                    progressBar1.Value = model.process;
                if (!model.silent)
                {
                    progressBar1.Value = progressBar1.Maximum;
                    plase.DrawImage(model.graf, 0, 0);
                    score[0, model.k].Value = model.score;
                }
            }
        }

        private void modulat_coubt_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (modulat_coubt.Text != "")
                    score.RowCount = Convert.ToInt32(modulat_coubt.Text);
            }
            catch
            {
                modulat_coubt.Text = "";
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void fild_size_TextChanged(object sender, EventArgs e)
        {
            try
            {
                if (fild_size.Text != "")
                    Convert.ToInt32(fild_size.Text);
            }
            catch
            {
                fild_size.Text = "";
                MessageBox.Show("invalid value", "warning", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }

        private void start_Click(object sender, EventArgs e)
        {
            BeginInvoke(new InvokeRefreshDelegate(ControlCol));
        }

        public void ControlCol()
        {
            int[,] enpos = new int[n, 2];
            for (int i = 0; i < n; i++)
            {
                enpos[i, 0] = Convert.ToInt32(enemy_coord[0, i].Value);
                enpos[i, 1] = Convert.ToInt32(enemy_coord[1, i].Value);
            }
            controller.ran_model(enpos, Convert.ToInt32(lear_iters.Text), Convert.ToInt32(modulat_coubt.Text), Convert.ToInt32(fild_size.Text));
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {
            MessageBox.Show(info, title, MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void toolStripButton3_Click(object sender, EventArgs e)
        {
            lang = true;
            Set_Language();
        }

        private void toolStripButton2_Click(object sender, EventArgs e)
        {
            lang = false;
            Set_Language();
        }
    }
}
