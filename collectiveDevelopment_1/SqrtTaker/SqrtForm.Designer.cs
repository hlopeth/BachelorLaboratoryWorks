namespace SqrtTaker
{
    partial class MainForm
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
            this.gb_num = new System.Windows.Forms.GroupBox();
            this.tb_num = new System.Windows.Forms.TextBox();
            this.gb_result = new System.Windows.Forms.GroupBox();
            this.tb_result = new System.Windows.Forms.TextBox();
            this.bt_GetSqrt = new System.Windows.Forms.Button();
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.ToolStripMenuItem_menu = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem_settings = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem_documentation = new System.Windows.Forms.ToolStripMenuItem();
            this.ToolStripMenuItem_exit = new System.Windows.Forms.ToolStripMenuItem();
            this.gb_num.SuspendLayout();
            this.gb_result.SuspendLayout();
            this.menuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // gb_num
            // 
            this.gb_num.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gb_num.Controls.Add(this.tb_num);
            this.gb_num.Location = new System.Drawing.Point(0, 27);
            this.gb_num.Name = "gb_num";
            this.gb_num.Size = new System.Drawing.Size(264, 52);
            this.gb_num.TabIndex = 0;
            this.gb_num.TabStop = false;
            this.gb_num.Text = "Исходное выражение";
            // 
            // tb_num
            // 
            this.tb_num.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tb_num.Location = new System.Drawing.Point(3, 16);
            this.tb_num.Name = "tb_num";
            this.tb_num.Size = new System.Drawing.Size(258, 20);
            this.tb_num.TabIndex = 0;
            // 
            // gb_result
            // 
            this.gb_result.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gb_result.Controls.Add(this.tb_result);
            this.gb_result.Location = new System.Drawing.Point(0, 111);
            this.gb_result.Name = "gb_result";
            this.gb_result.Size = new System.Drawing.Size(264, 61);
            this.gb_result.TabIndex = 1;
            this.gb_result.TabStop = false;
            this.gb_result.Text = "Корень выражения";
            // 
            // tb_result
            // 
            this.tb_result.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tb_result.Enabled = false;
            this.tb_result.Location = new System.Drawing.Point(3, 16);
            this.tb_result.Name = "tb_result";
            this.tb_result.Size = new System.Drawing.Size(258, 20);
            this.tb_result.TabIndex = 0;
            // 
            // bt_GetSqrt
            // 
            this.bt_GetSqrt.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.bt_GetSqrt.Location = new System.Drawing.Point(0, 82);
            this.bt_GetSqrt.Name = "bt_GetSqrt";
            this.bt_GetSqrt.Size = new System.Drawing.Size(264, 23);
            this.bt_GetSqrt.TabIndex = 1;
            this.bt_GetSqrt.Text = "Взять квадратный корень";
            this.bt_GetSqrt.UseVisualStyleBackColor = true;
            this.bt_GetSqrt.Click += new System.EventHandler(this.bt_GetSqrt_Click);
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItem_menu,
            this.ToolStripMenuItem_exit});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(264, 24);
            this.menuStrip.TabIndex = 2;
            this.menuStrip.Text = "menuStrip2";
            // 
            // ToolStripMenuItem_menu
            // 
            this.ToolStripMenuItem_menu.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItem_settings,
            this.ToolStripMenuItem_documentation});
            this.ToolStripMenuItem_menu.Name = "ToolStripMenuItem_menu";
            this.ToolStripMenuItem_menu.Size = new System.Drawing.Size(53, 20);
            this.ToolStripMenuItem_menu.Text = "Меню";
            // 
            // ToolStripMenuItem_settings
            // 
            this.ToolStripMenuItem_settings.Name = "ToolStripMenuItem_settings";
            this.ToolStripMenuItem_settings.Size = new System.Drawing.Size(221, 22);
            this.ToolStripMenuItem_settings.Text = "Настройки";
            this.ToolStripMenuItem_settings.Click += new System.EventHandler(this.настройкиToolStripMenuItem_Click);
            // 
            // ToolStripMenuItem_documentation
            // 
            this.ToolStripMenuItem_documentation.Name = "ToolStripMenuItem_documentation";
            this.ToolStripMenuItem_documentation.Size = new System.Drawing.Size(221, 22);
            this.ToolStripMenuItem_documentation.Text = "Руководство пользователя";
            this.ToolStripMenuItem_documentation.Click += new System.EventHandler(this.ToolStripMenuItem_documentation_Click);
            // 
            // ToolStripMenuItem_exit
            // 
            this.ToolStripMenuItem_exit.Name = "ToolStripMenuItem_exit";
            this.ToolStripMenuItem_exit.Size = new System.Drawing.Size(53, 20);
            this.ToolStripMenuItem_exit.Text = "Выход";
            this.ToolStripMenuItem_exit.Click += new System.EventHandler(this.ToolStripMenuItem_exit_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(264, 171);
            this.Controls.Add(this.bt_GetSqrt);
            this.Controls.Add(this.gb_result);
            this.Controls.Add(this.gb_num);
            this.Controls.Add(this.menuStrip);
            this.Name = "MainForm";
            this.Text = "SqrtTerr";
            this.gb_num.ResumeLayout(false);
            this.gb_num.PerformLayout();
            this.gb_result.ResumeLayout(false);
            this.gb_result.PerformLayout();
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox gb_num;
        private System.Windows.Forms.TextBox tb_num;
        private System.Windows.Forms.GroupBox gb_result;
        private System.Windows.Forms.TextBox tb_result;
        private System.Windows.Forms.Button bt_GetSqrt;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItem_menu;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItem_settings;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItem_documentation;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItem_exit;
    }
}

