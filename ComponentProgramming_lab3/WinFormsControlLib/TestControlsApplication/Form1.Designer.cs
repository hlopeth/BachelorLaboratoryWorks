namespace TestControlsApplication
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.colorMaker1 = new WinFormsControlLib.ColorMaker();
            this.filePathSelect2 = new WinFormsControlLib.FilePathSelect();
            this.component1 = new WinFormsControlLib.NumberBox(this.components);
            this.filePathSelect1 = new WinFormsControlLib.FilePathSelect();
            this.elementHost1 = new System.Windows.Forms.Integration.ElementHost();
            this.userControl11 = new WinFormsControlLib.UserControl1();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.component1);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(585, 48);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Упражнение 1";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.filePathSelect2);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox2.Location = new System.Drawing.Point(0, 48);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(585, 53);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Упражнение 2";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.colorMaker1);
            this.groupBox3.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox3.Location = new System.Drawing.Point(0, 101);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(585, 164);
            this.groupBox3.TabIndex = 5;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Упражнение 3";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.elementHost1);
            this.groupBox4.Dock = System.Windows.Forms.DockStyle.Top;
            this.groupBox4.Location = new System.Drawing.Point(0, 265);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(585, 205);
            this.groupBox4.TabIndex = 6;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Упражнение 4";
            // 
            // colorMaker1
            // 
            this.colorMaker1.Dock = System.Windows.Forms.DockStyle.Left;
            this.colorMaker1.Location = new System.Drawing.Point(3, 16);
            this.colorMaker1.Name = "colorMaker1";
            this.colorMaker1.Size = new System.Drawing.Size(285, 145);
            this.colorMaker1.TabIndex = 0;
            // 
            // filePathSelect2
            // 
            this.filePathSelect2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.filePathSelect2.FileName = "";
            this.filePathSelect2.Location = new System.Drawing.Point(3, 16);
            this.filePathSelect2.Name = "filePathSelect2";
            this.filePathSelect2.Size = new System.Drawing.Size(579, 34);
            this.filePathSelect2.TabIndex = 2;
            // 
            // component1
            // 
            this.component1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.component1.ForeColor = System.Drawing.Color.Red;
            this.component1.Location = new System.Drawing.Point(3, 16);
            this.component1.Name = "component1";
            this.component1.Size = new System.Drawing.Size(579, 20);
            this.component1.TabIndex = 0;
            // 
            // filePathSelect1
            // 
            this.filePathSelect1.FileName = "";
            this.filePathSelect1.Location = new System.Drawing.Point(28, 146);
            this.filePathSelect1.Name = "filePathSelect1";
            this.filePathSelect1.Size = new System.Drawing.Size(8, 8);
            this.filePathSelect1.TabIndex = 1;
            // 
            // elementHost1
            // 
            this.elementHost1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.elementHost1.Location = new System.Drawing.Point(3, 16);
            this.elementHost1.Name = "elementHost1";
            this.elementHost1.Size = new System.Drawing.Size(579, 186);
            this.elementHost1.TabIndex = 0;
            this.elementHost1.Text = "elementHost1";
            this.elementHost1.Child = this.userControl11;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(585, 504);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.filePathSelect1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private WinFormsControlLib.NumberBox component1;
        private WinFormsControlLib.FilePathSelect filePathSelect1;
        private WinFormsControlLib.FilePathSelect filePathSelect2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private WinFormsControlLib.ColorMaker colorMaker1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Integration.ElementHost elementHost1;
        private WinFormsControlLib.UserControl1 userControl11;
    }
}

