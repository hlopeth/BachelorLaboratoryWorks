namespace SqrtTaker
{
    partial class Settings
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
            this.gb_lang = new System.Windows.Forms.GroupBox();
            this.cb_language = new System.Windows.Forms.ComboBox();
            this.gb_accu = new System.Windows.Forms.GroupBox();
            this.nUD_accu = new System.Windows.Forms.NumericUpDown();
            this.bt_appl = new System.Windows.Forms.Button();
            this.bt_exit = new System.Windows.Forms.Button();
            this.gb_lang.SuspendLayout();
            this.gb_accu.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nUD_accu)).BeginInit();
            this.SuspendLayout();
            // 
            // gb_lang
            // 
            this.gb_lang.Controls.Add(this.cb_language);
            this.gb_lang.Location = new System.Drawing.Point(3, 0);
            this.gb_lang.Name = "gb_lang";
            this.gb_lang.Size = new System.Drawing.Size(196, 44);
            this.gb_lang.TabIndex = 0;
            this.gb_lang.TabStop = false;
            this.gb_lang.Text = "Язык";
            // 
            // cb_language
            // 
            this.cb_language.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cb_language.FormattingEnabled = true;
            this.cb_language.Location = new System.Drawing.Point(9, 16);
            this.cb_language.Name = "cb_language";
            this.cb_language.Size = new System.Drawing.Size(170, 21);
            this.cb_language.TabIndex = 0;
            // 
            // gb_accu
            // 
            this.gb_accu.Controls.Add(this.nUD_accu);
            this.gb_accu.Location = new System.Drawing.Point(3, 50);
            this.gb_accu.Name = "gb_accu";
            this.gb_accu.Size = new System.Drawing.Size(196, 44);
            this.gb_accu.TabIndex = 1;
            this.gb_accu.TabStop = false;
            this.gb_accu.Text = "Точность";
            // 
            // nUD_accu
            // 
            this.nUD_accu.Location = new System.Drawing.Point(9, 16);
            this.nUD_accu.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.nUD_accu.Name = "nUD_accu";
            this.nUD_accu.Size = new System.Drawing.Size(170, 20);
            this.nUD_accu.TabIndex = 0;
            this.nUD_accu.Value = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.nUD_accu.ValueChanged += new System.EventHandler(this.nUD_accu_ValueChanged);
            // 
            // bt_appl
            // 
            this.bt_appl.Location = new System.Drawing.Point(12, 100);
            this.bt_appl.Name = "bt_appl";
            this.bt_appl.Size = new System.Drawing.Size(75, 23);
            this.bt_appl.TabIndex = 2;
            this.bt_appl.Text = "ОК";
            this.bt_appl.UseVisualStyleBackColor = true;
            this.bt_appl.Click += new System.EventHandler(this.bt_appl_Click);
            // 
            // bt_exit
            // 
            this.bt_exit.Location = new System.Drawing.Point(107, 100);
            this.bt_exit.Name = "bt_exit";
            this.bt_exit.Size = new System.Drawing.Size(75, 23);
            this.bt_exit.TabIndex = 3;
            this.bt_exit.Text = "Выход";
            this.bt_exit.UseVisualStyleBackColor = true;
            this.bt_exit.Click += new System.EventHandler(this.bt_exit_Click);
            // 
            // Settings
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(207, 131);
            this.Controls.Add(this.bt_exit);
            this.Controls.Add(this.bt_appl);
            this.Controls.Add(this.gb_accu);
            this.Controls.Add(this.gb_lang);
            this.Name = "Settings";
            this.Text = "Настройки";
            this.gb_lang.ResumeLayout(false);
            this.gb_accu.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.nUD_accu)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox gb_lang;
        private System.Windows.Forms.ComboBox cb_language;
        private System.Windows.Forms.GroupBox gb_accu;
        private System.Windows.Forms.NumericUpDown nUD_accu;
        private System.Windows.Forms.Button bt_appl;
        private System.Windows.Forms.Button bt_exit;
    }
}