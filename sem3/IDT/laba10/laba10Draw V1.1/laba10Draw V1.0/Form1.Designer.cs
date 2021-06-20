namespace laba10Draw_V1._0
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
            this.Function = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.from = new System.Windows.Forms.TextBox();
            this.to = new System.Windows.Forms.TextBox();
            this.step = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.oc = new System.Windows.Forms.TrackBar();
            this.lc = new System.Windows.Forms.TrackBar();
            this.bc = new System.Windows.Forms.TrackBar();
            this.orcol = new System.Windows.Forms.Panel();
            this.lincil = new System.Windows.Forms.Panel();
            this.baccol = new System.Windows.Forms.Panel();
            this.lin = new System.Windows.Forms.RadioButton();
            this.orts = new System.Windows.Forms.RadioButton();
            this.back = new System.Windows.Forms.RadioButton();
            this.lisz = new System.Windows.Forms.TextBox();
            this.axsz = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.panel2 = new System.Windows.Forms.Panel();
            ((System.ComponentModel.ISupportInitialize)(this.oc)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lc)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bc)).BeginInit();
            this.SuspendLayout();
            // 
            // Function
            // 
            this.Function.Location = new System.Drawing.Point(43, 418);
            this.Function.Name = "Function";
            this.Function.Size = new System.Drawing.Size(169, 20);
            this.Function.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(12, 416);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(25, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "y=";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(219, 418);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 20);
            this.button1.TabIndex = 2;
            this.button1.Text = "calculate";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // from
            // 
            this.from.Location = new System.Drawing.Point(459, 420);
            this.from.Name = "from";
            this.from.Size = new System.Drawing.Size(100, 20);
            this.from.TabIndex = 3;
            // 
            // to
            // 
            this.to.Location = new System.Drawing.Point(594, 421);
            this.to.Name = "to";
            this.to.Size = new System.Drawing.Size(100, 20);
            this.to.TabIndex = 4;
            // 
            // step
            // 
            this.step.Location = new System.Drawing.Point(751, 421);
            this.step.Name = "step";
            this.step.Size = new System.Drawing.Size(37, 20);
            this.step.TabIndex = 5;
            this.step.TextChanged += new System.EventHandler(this.step_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(309, 418);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(144, 20);
            this.label2.TabIndex = 6;
            this.label2.Text = "variable varies from";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(565, 421);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(23, 20);
            this.label3.TabIndex = 7;
            this.label3.Text = "to";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(705, 421);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(40, 20);
            this.label4.TabIndex = 8;
            this.label4.Text = "step";
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(416, 8);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(376, 407);
            this.panel1.TabIndex = 9;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            // 
            // oc
            // 
            this.oc.LargeChange = 1;
            this.oc.Location = new System.Drawing.Point(13, 14);
            this.oc.Maximum = 255;
            this.oc.Minimum = 1;
            this.oc.Name = "oc";
            this.oc.Size = new System.Drawing.Size(369, 45);
            this.oc.TabIndex = 10;
            this.oc.Value = 1;
            this.oc.Scroll += new System.EventHandler(this.oc_Scroll);
            // 
            // lc
            // 
            this.lc.LargeChange = 1;
            this.lc.Location = new System.Drawing.Point(13, 66);
            this.lc.Maximum = 255;
            this.lc.Minimum = 1;
            this.lc.Name = "lc";
            this.lc.Size = new System.Drawing.Size(369, 45);
            this.lc.TabIndex = 11;
            this.lc.Value = 1;
            this.lc.Scroll += new System.EventHandler(this.lc_Scroll);
            // 
            // bc
            // 
            this.bc.LargeChange = 1;
            this.bc.Location = new System.Drawing.Point(13, 118);
            this.bc.Maximum = 255;
            this.bc.Minimum = 1;
            this.bc.Name = "bc";
            this.bc.Size = new System.Drawing.Size(369, 45);
            this.bc.TabIndex = 12;
            this.bc.Value = 1;
            this.bc.Scroll += new System.EventHandler(this.bc_Scroll);
            // 
            // orcol
            // 
            this.orcol.Location = new System.Drawing.Point(121, 184);
            this.orcol.Name = "orcol";
            this.orcol.Size = new System.Drawing.Size(30, 30);
            this.orcol.TabIndex = 13;
            // 
            // lincil
            // 
            this.lincil.Location = new System.Drawing.Point(16, 184);
            this.lincil.Name = "lincil";
            this.lincil.Size = new System.Drawing.Size(30, 30);
            this.lincil.TabIndex = 14;
            // 
            // baccol
            // 
            this.baccol.Location = new System.Drawing.Point(228, 184);
            this.baccol.Name = "baccol";
            this.baccol.Size = new System.Drawing.Size(30, 30);
            this.baccol.TabIndex = 15;
            // 
            // lin
            // 
            this.lin.AutoSize = true;
            this.lin.Location = new System.Drawing.Point(16, 161);
            this.lin.Name = "lin";
            this.lin.Size = new System.Drawing.Size(67, 17);
            this.lin.TabIndex = 16;
            this.lin.TabStop = true;
            this.lin.Text = "line color";
            this.lin.UseVisualStyleBackColor = true;
            this.lin.CheckedChanged += new System.EventHandler(this.lin_CheckedChanged);
            // 
            // orts
            // 
            this.orts.AutoSize = true;
            this.orts.Location = new System.Drawing.Point(121, 161);
            this.orts.Name = "orts";
            this.orts.Size = new System.Drawing.Size(69, 17);
            this.orts.TabIndex = 17;
            this.orts.TabStop = true;
            this.orts.Text = "axis color";
            this.orts.UseVisualStyleBackColor = true;
            this.orts.CheckedChanged += new System.EventHandler(this.orts_CheckedChanged);
            // 
            // back
            // 
            this.back.AutoSize = true;
            this.back.Location = new System.Drawing.Point(228, 161);
            this.back.Name = "back";
            this.back.Size = new System.Drawing.Size(108, 17);
            this.back.TabIndex = 18;
            this.back.TabStop = true;
            this.back.Text = "backgroung color";
            this.back.UseVisualStyleBackColor = true;
            this.back.CheckedChanged += new System.EventHandler(this.back_CheckedChanged);
            // 
            // lisz
            // 
            this.lisz.Location = new System.Drawing.Point(126, 220);
            this.lisz.Name = "lisz";
            this.lisz.Size = new System.Drawing.Size(25, 20);
            this.lisz.TabIndex = 19;
            this.lisz.TextChanged += new System.EventHandler(this.lisz_TextChanged);
            // 
            // axsz
            // 
            this.axsz.Location = new System.Drawing.Point(311, 220);
            this.axsz.Name = "axsz";
            this.axsz.Size = new System.Drawing.Size(25, 20);
            this.axsz.TabIndex = 20;
            this.axsz.TextChanged += new System.EventHandler(this.axsz_TextChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(-1, 222);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(121, 18);
            this.label5.TabIndex = 21;
            this.label5.Text = "set line thickness";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label6.Location = new System.Drawing.Point(180, 222);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(125, 18);
            this.label6.TabIndex = 22;
            this.label6.Text = "set axis thickness";
            // 
            // panel2
            // 
            this.panel2.Location = new System.Drawing.Point(121, 252);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(160, 160);
            this.panel2.TabIndex = 23;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 454);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.axsz);
            this.Controls.Add(this.lisz);
            this.Controls.Add(this.back);
            this.Controls.Add(this.orts);
            this.Controls.Add(this.lin);
            this.Controls.Add(this.baccol);
            this.Controls.Add(this.lincil);
            this.Controls.Add(this.orcol);
            this.Controls.Add(this.bc);
            this.Controls.Add(this.lc);
            this.Controls.Add(this.oc);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.step);
            this.Controls.Add(this.to);
            this.Controls.Add(this.from);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Function);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.oc)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lc)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bc)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox Function;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox from;
        private System.Windows.Forms.TextBox to;
        private System.Windows.Forms.TextBox step;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TrackBar oc;
        private System.Windows.Forms.TrackBar lc;
        private System.Windows.Forms.TrackBar bc;
        private System.Windows.Forms.Panel orcol;
        private System.Windows.Forms.Panel lincil;
        private System.Windows.Forms.Panel baccol;
        private System.Windows.Forms.RadioButton lin;
        private System.Windows.Forms.RadioButton orts;
        private System.Windows.Forms.RadioButton back;
        private System.Windows.Forms.TextBox lisz;
        private System.Windows.Forms.TextBox axsz;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Panel panel2;
    }
}

