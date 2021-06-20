namespace Q_learning_with_a_model
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.enm_count = new System.Windows.Forms.TextBox();
            this.lear_iters = new System.Windows.Forms.TextBox();
            this.modulat_coubt = new System.Windows.Forms.TextBox();
            this.enemy_coord = new System.Windows.Forms.DataGridView();
            this.score = new System.Windows.Forms.DataGridView();
            this.start = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.fild_size = new System.Windows.Forms.TextBox();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton3 = new System.Windows.Forms.ToolStripButton();
            ((System.ComponentModel.ISupportInitialize)(this.enemy_coord)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.score)).BeginInit();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // enm_count
            // 
            this.enm_count.Location = new System.Drawing.Point(11, 193);
            this.enm_count.Name = "enm_count";
            this.enm_count.Size = new System.Drawing.Size(100, 20);
            this.enm_count.TabIndex = 0;
            this.enm_count.TextChanged += new System.EventHandler(this.enm_count_TextChanged);
            // 
            // lear_iters
            // 
            this.lear_iters.Location = new System.Drawing.Point(11, 219);
            this.lear_iters.Name = "lear_iters";
            this.lear_iters.Size = new System.Drawing.Size(100, 20);
            this.lear_iters.TabIndex = 1;
            this.lear_iters.TextChanged += new System.EventHandler(this.lear_iters_TextChanged);
            // 
            // modulat_coubt
            // 
            this.modulat_coubt.Location = new System.Drawing.Point(11, 245);
            this.modulat_coubt.Name = "modulat_coubt";
            this.modulat_coubt.Size = new System.Drawing.Size(100, 20);
            this.modulat_coubt.TabIndex = 2;
            this.modulat_coubt.TextChanged += new System.EventHandler(this.modulat_coubt_TextChanged);
            // 
            // enemy_coord
            // 
            this.enemy_coord.AllowUserToAddRows = false;
            this.enemy_coord.AllowUserToDeleteRows = false;
            this.enemy_coord.AllowUserToResizeColumns = false;
            this.enemy_coord.AllowUserToResizeRows = false;
            this.enemy_coord.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.enemy_coord.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.enemy_coord.ColumnHeadersVisible = false;
            this.enemy_coord.EnableHeadersVisualStyles = false;
            this.enemy_coord.Location = new System.Drawing.Point(11, 37);
            this.enemy_coord.Name = "enemy_coord";
            this.enemy_coord.RowHeadersVisible = false;
            this.enemy_coord.RowHeadersWidth = 50;
            this.enemy_coord.Size = new System.Drawing.Size(100, 150);
            this.enemy_coord.TabIndex = 3;
            // 
            // score
            // 
            this.score.AllowUserToAddRows = false;
            this.score.AllowUserToDeleteRows = false;
            this.score.AllowUserToResizeColumns = false;
            this.score.AllowUserToResizeRows = false;
            this.score.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.score.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.score.ColumnHeadersVisible = false;
            this.score.EnableHeadersVisualStyles = false;
            this.score.Location = new System.Drawing.Point(118, 38);
            this.score.Name = "score";
            this.score.ReadOnly = true;
            this.score.RowHeadersVisible = false;
            this.score.RowHeadersWidth = 100;
            this.score.Size = new System.Drawing.Size(100, 227);
            this.score.TabIndex = 4;
            // 
            // start
            // 
            this.start.Location = new System.Drawing.Point(143, 271);
            this.start.Name = "start";
            this.start.Size = new System.Drawing.Size(75, 23);
            this.start.TabIndex = 5;
            this.start.Text = "start";
            this.start.UseVisualStyleBackColor = true;
            this.start.Click += new System.EventHandler(this.start_Click);
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(225, 38);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(300, 300);
            this.panel1.TabIndex = 6;
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(11, 315);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(207, 23);
            this.progressBar1.TabIndex = 7;
            // 
            // fild_size
            // 
            this.fild_size.Location = new System.Drawing.Point(11, 272);
            this.fild_size.Name = "fild_size";
            this.fild_size.Size = new System.Drawing.Size(100, 20);
            this.fild_size.TabIndex = 8;
            this.fild_size.TextChanged += new System.EventHandler(this.fild_size_TextChanged);
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton1,
            this.toolStripButton2,
            this.toolStripButton3});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(534, 25);
            this.toolStrip1.TabIndex = 9;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton1.Text = "toolStripButton1";
            this.toolStripButton1.Click += new System.EventHandler(this.toolStripButton1_Click);
            // 
            // toolStripButton2
            // 
            this.toolStripButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton2.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton2.Image")));
            this.toolStripButton2.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton2.Name = "toolStripButton2";
            this.toolStripButton2.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton2.Text = "toolStripButton2";
            this.toolStripButton2.Click += new System.EventHandler(this.toolStripButton2_Click);
            // 
            // toolStripButton3
            // 
            this.toolStripButton3.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton3.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton3.Image")));
            this.toolStripButton3.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton3.Name = "toolStripButton3";
            this.toolStripButton3.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton3.Text = "toolStripButton3";
            this.toolStripButton3.Click += new System.EventHandler(this.toolStripButton3_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(534, 345);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.fild_size);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.start);
            this.Controls.Add(this.score);
            this.Controls.Add(this.enemy_coord);
            this.Controls.Add(this.modulat_coubt);
            this.Controls.Add(this.lear_iters);
            this.Controls.Add(this.enm_count);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.Text = "Q-learning";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.enemy_coord)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.score)).EndInit();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox enm_count;
        private System.Windows.Forms.TextBox lear_iters;
        private System.Windows.Forms.TextBox modulat_coubt;
        private System.Windows.Forms.DataGridView enemy_coord;
        private System.Windows.Forms.DataGridView score;
        private System.Windows.Forms.Button start;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.TextBox fild_size;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.ToolStripButton toolStripButton2;
        private System.Windows.Forms.ToolStripButton toolStripButton3;
    }
}

