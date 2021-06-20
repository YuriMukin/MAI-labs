namespace laba3fix
{
    partial class worc
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.red = new System.Windows.Forms.TrackBar();
            this.grin = new System.Windows.Forms.TrackBar();
            this.blue = new System.Windows.Forms.TrackBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.red)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.grin)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.blue)).BeginInit();
            this.SuspendLayout();
            // 
            // red
            // 
            this.red.Location = new System.Drawing.Point(10, 11);
            this.red.Margin = new System.Windows.Forms.Padding(2);
            this.red.Maximum = 255;
            this.red.Minimum = 1;
            this.red.Name = "red";
            this.red.Size = new System.Drawing.Size(581, 45);
            this.red.TabIndex = 0;
            this.red.Value = 1;
            this.red.Scroll += new System.EventHandler(this.Red_Scroll);
            // 
            // grin
            // 
            this.grin.Location = new System.Drawing.Point(10, 62);
            this.grin.Margin = new System.Windows.Forms.Padding(2);
            this.grin.Maximum = 255;
            this.grin.Minimum = 1;
            this.grin.Name = "grin";
            this.grin.Size = new System.Drawing.Size(581, 45);
            this.grin.TabIndex = 1;
            this.grin.Value = 1;
            this.grin.Scroll += new System.EventHandler(this.Grin_Scroll);
            // 
            // blue
            // 
            this.blue.Location = new System.Drawing.Point(10, 113);
            this.blue.Margin = new System.Windows.Forms.Padding(2);
            this.blue.Maximum = 255;
            this.blue.Minimum = 1;
            this.blue.Name = "blue";
            this.blue.Size = new System.Drawing.Size(581, 45);
            this.blue.TabIndex = 2;
            this.blue.Value = 1;
            this.blue.Scroll += new System.EventHandler(this.Blue_Scroll);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 161);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(25, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "red:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(54, 161);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "label2";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(123, 161);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(27, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "grin:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(164, 161);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(35, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "label4";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(231, 161);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(30, 13);
            this.label5.TabIndex = 7;
            this.label5.Text = "blue:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(272, 161);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(35, 13);
            this.label6.TabIndex = 8;
            this.label6.Text = "label6";
            // 
            // worc
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(600, 183);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.blue);
            this.Controls.Add(this.grin);
            this.Controls.Add(this.red);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "worc";
            this.Text = "worc";
            ((System.ComponentModel.ISupportInitialize)(this.red)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.grin)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.blue)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TrackBar red;
        private System.Windows.Forms.TrackBar grin;
        private System.Windows.Forms.TrackBar blue;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
    }
}