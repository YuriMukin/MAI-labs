namespace lab5
{
    partial class vorkingProcess
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
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.resolution = new System.Windows.Forms.TrackBar();
            this.strart = new System.Windows.Forms.Button();
            this.horizon = new System.Windows.Forms.Label();
            this.vertical = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.temp = new System.Windows.Forms.Label();
            this.rmp = new System.Windows.Forms.Label();
            this.tempi = new System.Windows.Forms.Label();
            this.RMPval = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.resolution)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(10, 11);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(2);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(75, 114);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // resolution
            // 
            this.resolution.LargeChange = 720;
            this.resolution.Location = new System.Drawing.Point(10, 130);
            this.resolution.Margin = new System.Windows.Forms.Padding(2);
            this.resolution.Maximum = 2160;
            this.resolution.Minimum = 720;
            this.resolution.Name = "resolution";
            this.resolution.Size = new System.Drawing.Size(193, 45);
            this.resolution.SmallChange = 720;
            this.resolution.TabIndex = 720;
            this.resolution.TabStop = false;
            this.resolution.Value = 720;
            this.resolution.Scroll += new System.EventHandler(this.resolution_Scroll);
            // 
            // strart
            // 
            this.strart.Location = new System.Drawing.Point(146, 11);
            this.strart.Margin = new System.Windows.Forms.Padding(2);
            this.strart.Name = "strart";
            this.strart.Size = new System.Drawing.Size(56, 19);
            this.strart.TabIndex = 2;
            this.strart.Text = "start";
            this.strart.UseVisualStyleBackColor = true;
            this.strart.Click += new System.EventHandler(this.strart_Click);
            // 
            // horizon
            // 
            this.horizon.AutoSize = true;
            this.horizon.Location = new System.Drawing.Point(89, 110);
            this.horizon.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.horizon.Name = "horizon";
            this.horizon.Size = new System.Drawing.Size(35, 13);
            this.horizon.TabIndex = 3;
            this.horizon.Text = "label1";
            // 
            // vertical
            // 
            this.vertical.AutoSize = true;
            this.vertical.Location = new System.Drawing.Point(166, 110);
            this.vertical.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.vertical.Name = "vertical";
            this.vertical.Size = new System.Drawing.Size(35, 13);
            this.vertical.TabIndex = 4;
            this.vertical.Text = "label2";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(136, 110);
            this.label3.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(12, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "x";
            // 
            // temp
            // 
            this.temp.AutoSize = true;
            this.temp.Location = new System.Drawing.Point(146, 35);
            this.temp.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.temp.Name = "temp";
            this.temp.Size = new System.Drawing.Size(0, 13);
            this.temp.TabIndex = 6;
            // 
            // rmp
            // 
            this.rmp.AutoSize = true;
            this.rmp.Location = new System.Drawing.Point(148, 52);
            this.rmp.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.rmp.Name = "rmp";
            this.rmp.Size = new System.Drawing.Size(0, 13);
            this.rmp.TabIndex = 7;
            // 
            // tempi
            // 
            this.tempi.AutoSize = true;
            this.tempi.Location = new System.Drawing.Point(143, 39);
            this.tempi.Name = "tempi";
            this.tempi.Size = new System.Drawing.Size(35, 13);
            this.tempi.TabIndex = 721;
            this.tempi.Text = "label1";
            // 
            // RMPval
            // 
            this.RMPval.AutoSize = true;
            this.RMPval.Location = new System.Drawing.Point(143, 65);
            this.RMPval.Name = "RMPval";
            this.RMPval.Size = new System.Drawing.Size(35, 13);
            this.RMPval.TabIndex = 722;
            this.RMPval.Text = "label2";
            // 
            // vorkingProcess
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(212, 167);
            this.Controls.Add(this.RMPval);
            this.Controls.Add(this.tempi);
            this.Controls.Add(this.rmp);
            this.Controls.Add(this.temp);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.vertical);
            this.Controls.Add(this.horizon);
            this.Controls.Add(this.strart);
            this.Controls.Add(this.resolution);
            this.Controls.Add(this.pictureBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "vorkingProcess";
            this.Text = "vorkingProcess";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.vorkingProcess_FormClosed);
            this.Load += new System.EventHandler(this.vorkingProcess_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.resolution)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TrackBar resolution;
        private System.Windows.Forms.Button strart;
        private System.Windows.Forms.Label horizon;
        private System.Windows.Forms.Label vertical;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label temp;
        private System.Windows.Forms.Label rmp;
        private System.Windows.Forms.Label tempi;
        private System.Windows.Forms.Label RMPval;
    }
}