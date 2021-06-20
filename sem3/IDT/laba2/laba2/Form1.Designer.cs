namespace laba2
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
            this.Cost_of_pd = new System.Windows.Forms.GroupBox();
            this.CastName = new System.Windows.Forms.ListBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.ProdName = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.coast = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.num_of_ws = new System.Windows.Forms.TextBox();
            this.discount = new System.Windows.Forms.TextBox();
            this.num_of_rs = new System.Windows.Forms.NumericUpDown();
            this.wholesale = new System.Windows.Forms.RadioButton();
            this.retail = new System.Windows.Forms.RadioButton();
            this.retail_base = new System.Windows.Forms.ListBox();
            this.wholesale_base = new System.Windows.Forms.ListBox();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.changeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addNameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.addProductToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.clearBaseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ret_bas_show = new System.Windows.Forms.Button();
            this.who_bas_show = new System.Windows.Forms.Button();
            this.calcsumm = new System.Windows.Forms.Button();
            this.summout = new System.Windows.Forms.TextBox();
            this.textSize = new System.Windows.Forms.TextBox();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.toolStripButton2 = new System.Windows.Forms.ToolStripButton();
            this.Cost_of_pd.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.num_of_rs)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // Cost_of_pd
            // 
            this.Cost_of_pd.Controls.Add(this.CastName);
            this.Cost_of_pd.Controls.Add(this.button1);
            this.Cost_of_pd.Controls.Add(this.label2);
            this.Cost_of_pd.Controls.Add(this.label1);
            this.Cost_of_pd.Controls.Add(this.ProdName);
            this.Cost_of_pd.Controls.Add(this.groupBox2);
            this.Cost_of_pd.Location = new System.Drawing.Point(12, 52);
            this.Cost_of_pd.Name = "Cost_of_pd";
            this.Cost_of_pd.Size = new System.Drawing.Size(254, 386);
            this.Cost_of_pd.TabIndex = 0;
            this.Cost_of_pd.TabStop = false;
            this.Cost_of_pd.Text = "info read";
            // 
            // CastName
            // 
            this.CastName.FormattingEnabled = true;
            this.CastName.Items.AddRange(new object[] {
            "ООО айсберг",
            "ОАО кристалл",
            "Солоухов",
            "Климов"});
            this.CastName.Location = new System.Drawing.Point(13, 47);
            this.CastName.Name = "CastName";
            this.CastName.Size = new System.Drawing.Size(226, 95);
            this.CastName.TabIndex = 6;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(78, 368);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 5;
            this.button1.Text = "to data base";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(10, 143);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "product";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(10, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(79, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "customer name";
            // 
            // ProdName
            // 
            this.ProdName.FormattingEnabled = true;
            this.ProdName.Items.AddRange(new object[] {
            "жаренные гвозди",
            "резина",
            "струны",
            "арматура"});
            this.ProdName.Location = new System.Drawing.Point(13, 159);
            this.ProdName.Name = "ProdName";
            this.ProdName.Size = new System.Drawing.Size(226, 21);
            this.ProdName.TabIndex = 2;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.coast);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.num_of_ws);
            this.groupBox2.Controls.Add(this.discount);
            this.groupBox2.Controls.Add(this.num_of_rs);
            this.groupBox2.Controls.Add(this.wholesale);
            this.groupBox2.Controls.Add(this.retail);
            this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.groupBox2.Location = new System.Drawing.Point(7, 196);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(239, 157);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "choose the type of act";
            // 
            // coast
            // 
            this.coast.Location = new System.Drawing.Point(132, 24);
            this.coast.Name = "coast";
            this.coast.Size = new System.Drawing.Size(100, 20);
            this.coast.TabIndex = 7;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 28);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(123, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "enter the cost of product";
            // 
            // num_of_ws
            // 
            this.num_of_ws.Enabled = false;
            this.num_of_ws.Location = new System.Drawing.Point(6, 131);
            this.num_of_ws.Name = "num_of_ws";
            this.num_of_ws.Size = new System.Drawing.Size(226, 20);
            this.num_of_ws.TabIndex = 4;
            this.num_of_ws.TextChanged += new System.EventHandler(this.num_of_ws_TextChanged);
            // 
            // discount
            // 
            this.discount.Enabled = false;
            this.discount.Location = new System.Drawing.Point(132, 76);
            this.discount.Name = "discount";
            this.discount.Size = new System.Drawing.Size(100, 20);
            this.discount.TabIndex = 3;
            this.discount.TextChanged += new System.EventHandler(this.discount_TextChanged);
            // 
            // num_of_rs
            // 
            this.num_of_rs.Enabled = false;
            this.num_of_rs.Location = new System.Drawing.Point(6, 76);
            this.num_of_rs.Maximum = new decimal(new int[] {
            19,
            0,
            0,
            0});
            this.num_of_rs.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.num_of_rs.Name = "num_of_rs";
            this.num_of_rs.Size = new System.Drawing.Size(85, 20);
            this.num_of_rs.TabIndex = 2;
            this.num_of_rs.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // wholesale
            // 
            this.wholesale.AutoSize = true;
            this.wholesale.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.wholesale.Location = new System.Drawing.Point(6, 108);
            this.wholesale.Name = "wholesale";
            this.wholesale.Size = new System.Drawing.Size(72, 17);
            this.wholesale.TabIndex = 1;
            this.wholesale.TabStop = true;
            this.wholesale.Text = "wholesale";
            this.wholesale.UseVisualStyleBackColor = true;
            this.wholesale.CheckedChanged += new System.EventHandler(this.wholesale_CheckedChanged);
            // 
            // retail
            // 
            this.retail.AutoSize = true;
            this.retail.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.retail.Location = new System.Drawing.Point(6, 53);
            this.retail.Name = "retail";
            this.retail.Size = new System.Drawing.Size(47, 17);
            this.retail.TabIndex = 0;
            this.retail.TabStop = true;
            this.retail.Text = "retail";
            this.retail.UseVisualStyleBackColor = true;
            this.retail.CheckedChanged += new System.EventHandler(this.retail_CheckedChanged);
            // 
            // retail_base
            // 
            this.retail_base.FormattingEnabled = true;
            this.retail_base.Location = new System.Drawing.Point(292, 58);
            this.retail_base.Name = "retail_base";
            this.retail_base.Size = new System.Drawing.Size(399, 147);
            this.retail_base.TabIndex = 1;
            // 
            // wholesale_base
            // 
            this.wholesale_base.FormattingEnabled = true;
            this.wholesale_base.Location = new System.Drawing.Point(292, 252);
            this.wholesale_base.Name = "wholesale_base";
            this.wholesale_base.Size = new System.Drawing.Size(399, 160);
            this.wholesale_base.TabIndex = 2;
            // 
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(292, 447);
            this.trackBar1.Maximum = 25;
            this.trackBar1.Minimum = 8;
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(399, 45);
            this.trackBar1.TabIndex = 3;
            this.trackBar1.Value = 8;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.changeToolStripMenuItem,
            this.clearBaseToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(703, 24);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // changeToolStripMenuItem
            // 
            this.changeToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addNameToolStripMenuItem,
            this.addProductToolStripMenuItem});
            this.changeToolStripMenuItem.Name = "changeToolStripMenuItem";
            this.changeToolStripMenuItem.Size = new System.Drawing.Size(72, 20);
            this.changeToolStripMenuItem.Text = "add name";
            // 
            // addNameToolStripMenuItem
            // 
            this.addNameToolStripMenuItem.Name = "addNameToolStripMenuItem";
            this.addNameToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.addNameToolStripMenuItem.Text = "add name";
            this.addNameToolStripMenuItem.Click += new System.EventHandler(this.addNameToolStripMenuItem_Click);
            // 
            // addProductToolStripMenuItem
            // 
            this.addProductToolStripMenuItem.Name = "addProductToolStripMenuItem";
            this.addProductToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.addProductToolStripMenuItem.Text = "add product";
            this.addProductToolStripMenuItem.Click += new System.EventHandler(this.addProductToolStripMenuItem_Click);
            // 
            // clearBaseToolStripMenuItem
            // 
            this.clearBaseToolStripMenuItem.Name = "clearBaseToolStripMenuItem";
            this.clearBaseToolStripMenuItem.Size = new System.Drawing.Size(71, 20);
            this.clearBaseToolStripMenuItem.Text = "clear base";
            this.clearBaseToolStripMenuItem.Click += new System.EventHandler(this.clearBaseToolStripMenuItem_Click);
            // 
            // ret_bas_show
            // 
            this.ret_bas_show.Location = new System.Drawing.Point(617, 211);
            this.ret_bas_show.Name = "ret_bas_show";
            this.ret_bas_show.Size = new System.Drawing.Size(75, 23);
            this.ret_bas_show.TabIndex = 5;
            this.ret_bas_show.Text = "show retail";
            this.ret_bas_show.UseVisualStyleBackColor = true;
            this.ret_bas_show.Click += new System.EventHandler(this.ret_bas_show_Click);
            // 
            // who_bas_show
            // 
            this.who_bas_show.Location = new System.Drawing.Point(616, 418);
            this.who_bas_show.Name = "who_bas_show";
            this.who_bas_show.Size = new System.Drawing.Size(75, 23);
            this.who_bas_show.TabIndex = 6;
            this.who_bas_show.Text = "show whol.";
            this.who_bas_show.UseVisualStyleBackColor = true;
            this.who_bas_show.Click += new System.EventHandler(this.who_bas_show_Click);
            // 
            // calcsumm
            // 
            this.calcsumm.Location = new System.Drawing.Point(12, 454);
            this.calcsumm.Name = "calcsumm";
            this.calcsumm.Size = new System.Drawing.Size(75, 23);
            this.calcsumm.TabIndex = 7;
            this.calcsumm.Text = "calc. summ";
            this.calcsumm.UseVisualStyleBackColor = true;
            this.calcsumm.Click += new System.EventHandler(this.calcsumm_Click);
            // 
            // summout
            // 
            this.summout.Location = new System.Drawing.Point(135, 457);
            this.summout.Name = "summout";
            this.summout.ReadOnly = true;
            this.summout.Size = new System.Drawing.Size(131, 20);
            this.summout.TabIndex = 8;
            // 
            // textSize
            // 
            this.textSize.Location = new System.Drawing.Point(292, 417);
            this.textSize.Name = "textSize";
            this.textSize.ReadOnly = true;
            this.textSize.Size = new System.Drawing.Size(20, 20);
            this.textSize.TabIndex = 9;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripButton1,
            this.toolStripButton2});
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(703, 25);
            this.toolStrip1.TabIndex = 10;
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
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(703, 489);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.textSize);
            this.Controls.Add(this.summout);
            this.Controls.Add(this.calcsumm);
            this.Controls.Add(this.who_bas_show);
            this.Controls.Add(this.ret_bas_show);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.wholesale_base);
            this.Controls.Add(this.retail_base);
            this.Controls.Add(this.Cost_of_pd);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "sales accounting";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Cost_of_pd.ResumeLayout(false);
            this.Cost_of_pd.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.num_of_rs)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox Cost_of_pd;
        private System.Windows.Forms.ListBox retail_base;
        private System.Windows.Forms.ListBox wholesale_base;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox ProdName;
        private System.Windows.Forms.TextBox num_of_ws;
        private System.Windows.Forms.TextBox discount;
        private System.Windows.Forms.RadioButton wholesale;
        private System.Windows.Forms.RadioButton retail;
        private System.Windows.Forms.NumericUpDown num_of_rs;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox coast;
        private System.Windows.Forms.ListBox CastName;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem changeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem clearBaseToolStripMenuItem;
        private System.Windows.Forms.Button ret_bas_show;
        private System.Windows.Forms.Button who_bas_show;
        private System.Windows.Forms.Button calcsumm;
        private System.Windows.Forms.TextBox summout;
        private System.Windows.Forms.ToolStripMenuItem addNameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem addProductToolStripMenuItem;
        private System.Windows.Forms.TextBox textSize;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.ToolStripButton toolStripButton2;
    }
}

