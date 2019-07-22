namespace WinFormsControlLib
{
    partial class ColorMaker
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

        #region Код, автоматически созданный конструктором компонентов

        /// <summary> 
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.rb_Dec = new System.Windows.Forms.RadioButton();
            this.rb_Hex = new System.Windows.Forms.RadioButton();
            this.pb_Color = new System.Windows.Forms.PictureBox();
            this.numTb_Blue = new WinFormsControlLib.NumTb(this.components);
            this.numTb_Green = new WinFormsControlLib.NumTb(this.components);
            this.numTb_Red = new WinFormsControlLib.NumTb(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.pb_Color)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 14);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Красный";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 43);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(52, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Зеленый";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 73);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(38, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Синий";
            // 
            // rb_Dec
            // 
            this.rb_Dec.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.rb_Dec.AutoSize = true;
            this.rb_Dec.Checked = true;
            this.rb_Dec.Location = new System.Drawing.Point(6, 214);
            this.rb_Dec.Name = "rb_Dec";
            this.rb_Dec.Size = new System.Drawing.Size(45, 17);
            this.rb_Dec.TabIndex = 6;
            this.rb_Dec.TabStop = true;
            this.rb_Dec.Text = "Dec";
            this.rb_Dec.UseVisualStyleBackColor = true;
            this.rb_Dec.CheckedChanged += new System.EventHandler(this.rb_Dec_CheckedChanged);
            // 
            // rb_Hex
            // 
            this.rb_Hex.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.rb_Hex.AutoSize = true;
            this.rb_Hex.Location = new System.Drawing.Point(61, 214);
            this.rb_Hex.Name = "rb_Hex";
            this.rb_Hex.Size = new System.Drawing.Size(44, 17);
            this.rb_Hex.TabIndex = 7;
            this.rb_Hex.Text = "Hex";
            this.rb_Hex.UseVisualStyleBackColor = true;
            this.rb_Hex.CheckedChanged += new System.EventHandler(this.rb_Hex_CheckedChanged);
            // 
            // pb_Color
            // 
            this.pb_Color.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pb_Color.BackColor = System.Drawing.Color.Black;
            this.pb_Color.Location = new System.Drawing.Point(130, 11);
            this.pb_Color.Name = "pb_Color";
            this.pb_Color.Size = new System.Drawing.Size(212, 220);
            this.pb_Color.TabIndex = 8;
            this.pb_Color.TabStop = false;
            // 
            // numTb_Blue
            // 
            this.numTb_Blue.Location = new System.Drawing.Point(61, 66);
            this.numTb_Blue.Name = "numTb_Blue";
            this.numTb_Blue.Size = new System.Drawing.Size(44, 20);
            this.numTb_Blue.TabIndex = 11;
            this.numTb_Blue.Text = "0";
            this.numTb_Blue.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numTb_Blue.TextChanged += new System.EventHandler(this.numTb_Blue_TextChanged);
            // 
            // numTb_Green
            // 
            this.numTb_Green.Location = new System.Drawing.Point(61, 40);
            this.numTb_Green.Name = "numTb_Green";
            this.numTb_Green.Size = new System.Drawing.Size(44, 20);
            this.numTb_Green.TabIndex = 10;
            this.numTb_Green.Text = "0";
            this.numTb_Green.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numTb_Green.TextChanged += new System.EventHandler(this.numTb_Green_TextChanged);
            // 
            // numTb_Red
            // 
            this.numTb_Red.Location = new System.Drawing.Point(61, 14);
            this.numTb_Red.Name = "numTb_Red";
            this.numTb_Red.Size = new System.Drawing.Size(44, 20);
            this.numTb_Red.TabIndex = 9;
            this.numTb_Red.Text = "0";
            this.numTb_Red.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numTb_Red.TextChanged += new System.EventHandler(this.numTb_Red_TextChanged);
            // 
            // ColorMaker
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.numTb_Blue);
            this.Controls.Add(this.numTb_Green);
            this.Controls.Add(this.numTb_Red);
            this.Controls.Add(this.pb_Color);
            this.Controls.Add(this.rb_Hex);
            this.Controls.Add(this.rb_Dec);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Name = "ColorMaker";
            this.Size = new System.Drawing.Size(355, 243);
            this.Load += new System.EventHandler(this.ColorMaker_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pb_Color)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.RadioButton rb_Dec;
        private System.Windows.Forms.RadioButton rb_Hex;
        private System.Windows.Forms.PictureBox pb_Color;
        private NumTb numTb_Red;
        private NumTb numTb_Green;
        private NumTb numTb_Blue;
    }
}
