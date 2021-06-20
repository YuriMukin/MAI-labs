namespace lab5
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
            this.Notebook = new System.Windows.Forms.RadioButton();
            this.ATX_PC = new System.Windows.Forms.RadioButton();
            this.st_worc = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Notebook
            // 
            this.Notebook.AutoSize = true;
            this.Notebook.Location = new System.Drawing.Point(17, 16);
            this.Notebook.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Notebook.Name = "Notebook";
            this.Notebook.Size = new System.Drawing.Size(90, 21);
            this.Notebook.TabIndex = 0;
            this.Notebook.TabStop = true;
            this.Notebook.Text = "Notebook";
            this.Notebook.UseVisualStyleBackColor = true;
            this.Notebook.CheckedChanged += new System.EventHandler(this.Notebook_CheckedChanged);
            // 
            // ATX_PC
            // 
            this.ATX_PC.AutoSize = true;
            this.ATX_PC.Location = new System.Drawing.Point(17, 46);
            this.ATX_PC.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.ATX_PC.Name = "ATX_PC";
            this.ATX_PC.Size = new System.Drawing.Size(78, 21);
            this.ATX_PC.TabIndex = 1;
            this.ATX_PC.TabStop = true;
            this.ATX_PC.Text = "ATX PC";
            this.ATX_PC.UseVisualStyleBackColor = true;
            this.ATX_PC.CheckedChanged += new System.EventHandler(this.ATX_PC_CheckedChanged);
            // 
            // st_worc
            // 
            this.st_worc.Location = new System.Drawing.Point(213, 16);
            this.st_worc.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.st_worc.Name = "st_worc";
            this.st_worc.Size = new System.Drawing.Size(136, 28);
            this.st_worc.TabIndex = 2;
            this.st_worc.Text = "start working";
            this.st_worc.UseVisualStyleBackColor = true;
            this.st_worc.Click += new System.EventHandler(this.st_worc_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(365, 92);
            this.Controls.Add(this.st_worc);
            this.Controls.Add(this.ATX_PC);
            this.Controls.Add(this.Notebook);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton Notebook;
        private System.Windows.Forms.RadioButton ATX_PC;
        private System.Windows.Forms.Button st_worc;
    }
}

