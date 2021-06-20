namespace laba6_MVC_V1._0
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.dotcor = new System.Windows.Forms.DataGridView();
            this.drtaw = new System.Windows.Forms.Button();
            this.countOfDot = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.dotcor)).BeginInit();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Location = new System.Drawing.Point(12, 12);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(250, 250);
            this.panel1.TabIndex = 0;
            this.panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.panel1_Paint);
            // 
            // dotcor
            // 
            this.dotcor.AllowUserToAddRows = false;
            this.dotcor.AllowUserToDeleteRows = false;
            this.dotcor.AllowUserToResizeColumns = false;
            this.dotcor.AllowUserToResizeRows = false;
            this.dotcor.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dotcor.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dotcor.ColumnHeadersVisible = false;
            this.dotcor.Location = new System.Drawing.Point(269, 13);
            this.dotcor.Name = "dotcor";
            this.dotcor.RowHeadersVisible = false;
            this.dotcor.RowHeadersWidth = 50;
            this.dotcor.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.DisableResizing;
            this.dotcor.Size = new System.Drawing.Size(100, 250);
            this.dotcor.TabIndex = 1;
            // 
            // drtaw
            // 
            this.drtaw.Location = new System.Drawing.Point(12, 269);
            this.drtaw.Name = "drtaw";
            this.drtaw.Size = new System.Drawing.Size(75, 23);
            this.drtaw.TabIndex = 2;
            this.drtaw.Text = "draw";
            this.drtaw.UseVisualStyleBackColor = true;
            this.drtaw.Click += new System.EventHandler(this.drtaw_Click);
            // 
            // countOfDot
            // 
            this.countOfDot.Location = new System.Drawing.Point(269, 269);
            this.countOfDot.Name = "countOfDot";
            this.countOfDot.Size = new System.Drawing.Size(100, 20);
            this.countOfDot.TabIndex = 3;
            this.countOfDot.TextChanged += new System.EventHandler(this.countOfDot_TextChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(379, 301);
            this.Controls.Add(this.countOfDot);
            this.Controls.Add(this.drtaw);
            this.Controls.Add(this.dotcor);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Form1";
            this.Text = "DrawByDots";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dotcor)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.DataGridView dotcor;
        private System.Windows.Forms.Button drtaw;
        private System.Windows.Forms.TextBox countOfDot;
    }
}

