namespace MainForm
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
            this.lv_Binary = new System.Windows.Forms.ListView();
            this.b_Add = new System.Windows.Forms.Button();
            this.b_Change = new System.Windows.Forms.Button();
            this.b_Delete = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tabControl = new System.Windows.Forms.TabControl();
            this.tp_Binary = new System.Windows.Forms.TabPage();
            this.tp_XML = new System.Windows.Forms.TabPage();
            this.tp_Soap = new System.Windows.Forms.TabPage();
            this.tp_Json = new System.Windows.Forms.TabPage();
            this.lv_XML = new System.Windows.Forms.ListView();
            this.XMLPoints = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.BinaryPoints = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.lv_Soap = new System.Windows.Forms.ListView();
            this.lv_Json = new System.Windows.Forms.ListView();
            this.menuStrip1.SuspendLayout();
            this.tabControl.SuspendLayout();
            this.tp_Binary.SuspendLayout();
            this.tp_XML.SuspendLayout();
            this.tp_Soap.SuspendLayout();
            this.tp_Json.SuspendLayout();
            this.SuspendLayout();
            // 
            // lv_Binary
            // 
            this.lv_Binary.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.BinaryPoints});
            this.lv_Binary.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lv_Binary.FullRowSelect = true;
            this.lv_Binary.Location = new System.Drawing.Point(3, 3);
            this.lv_Binary.Name = "lv_Binary";
            this.lv_Binary.Size = new System.Drawing.Size(283, 210);
            this.lv_Binary.TabIndex = 0;
            this.lv_Binary.UseCompatibleStateImageBehavior = false;
            this.lv_Binary.View = System.Windows.Forms.View.List;
            // 
            // b_Add
            // 
            this.b_Add.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.b_Add.Location = new System.Drawing.Point(315, 188);
            this.b_Add.Name = "b_Add";
            this.b_Add.Size = new System.Drawing.Size(63, 23);
            this.b_Add.TabIndex = 1;
            this.b_Add.Text = "Add";
            this.b_Add.UseVisualStyleBackColor = true;
            this.b_Add.Click += new System.EventHandler(this.b_Add_Click);
            // 
            // b_Change
            // 
            this.b_Change.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.b_Change.Location = new System.Drawing.Point(315, 217);
            this.b_Change.Name = "b_Change";
            this.b_Change.Size = new System.Drawing.Size(63, 23);
            this.b_Change.TabIndex = 2;
            this.b_Change.Text = "Change";
            this.b_Change.UseVisualStyleBackColor = true;
            this.b_Change.Click += new System.EventHandler(this.b_Change_Click);
            // 
            // b_Delete
            // 
            this.b_Delete.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.b_Delete.Location = new System.Drawing.Point(315, 246);
            this.b_Delete.Name = "b_Delete";
            this.b_Delete.Size = new System.Drawing.Size(63, 23);
            this.b_Delete.TabIndex = 3;
            this.b_Delete.Text = "Delete";
            this.b_Delete.UseVisualStyleBackColor = true;
            this.b_Delete.Click += new System.EventHandler(this.b_Delete_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(390, 24);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveAsToolStripMenuItem,
            this.loadToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.saveAsToolStripMenuItem.Text = "Save As";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // loadToolStripMenuItem
            // 
            this.loadToolStripMenuItem.Name = "loadToolStripMenuItem";
            this.loadToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.loadToolStripMenuItem.Text = "Load";
            this.loadToolStripMenuItem.Click += new System.EventHandler(this.loadToolStripMenuItem_Click);
            // 
            // tabControl
            // 
            this.tabControl.Controls.Add(this.tp_Binary);
            this.tabControl.Controls.Add(this.tp_XML);
            this.tabControl.Controls.Add(this.tp_Soap);
            this.tabControl.Controls.Add(this.tp_Json);
            this.tabControl.Location = new System.Drawing.Point(12, 27);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(297, 242);
            this.tabControl.TabIndex = 5;
            // 
            // tp_Binary
            // 
            this.tp_Binary.Controls.Add(this.lv_Binary);
            this.tp_Binary.Location = new System.Drawing.Point(4, 22);
            this.tp_Binary.Name = "tp_Binary";
            this.tp_Binary.Padding = new System.Windows.Forms.Padding(3);
            this.tp_Binary.Size = new System.Drawing.Size(289, 216);
            this.tp_Binary.TabIndex = 0;
            this.tp_Binary.Text = "Binary";
            this.tp_Binary.UseVisualStyleBackColor = true;
            this.tp_Binary.Enter += new System.EventHandler(this.tp_Binary_Enter);
            // 
            // tp_XML
            // 
            this.tp_XML.Controls.Add(this.lv_XML);
            this.tp_XML.Location = new System.Drawing.Point(4, 22);
            this.tp_XML.Name = "tp_XML";
            this.tp_XML.Padding = new System.Windows.Forms.Padding(3);
            this.tp_XML.Size = new System.Drawing.Size(289, 216);
            this.tp_XML.TabIndex = 1;
            this.tp_XML.Text = "XML";
            this.tp_XML.UseVisualStyleBackColor = true;
            this.tp_XML.Enter += new System.EventHandler(this.tp_XML_Enter);
            // 
            // tp_Soap
            // 
            this.tp_Soap.Controls.Add(this.lv_Soap);
            this.tp_Soap.Location = new System.Drawing.Point(4, 22);
            this.tp_Soap.Name = "tp_Soap";
            this.tp_Soap.Padding = new System.Windows.Forms.Padding(3);
            this.tp_Soap.Size = new System.Drawing.Size(289, 216);
            this.tp_Soap.TabIndex = 2;
            this.tp_Soap.Text = "Soap";
            this.tp_Soap.UseVisualStyleBackColor = true;
            this.tp_Soap.Enter += new System.EventHandler(this.tp_Soap_Enter);
            // 
            // tp_Json
            // 
            this.tp_Json.Controls.Add(this.lv_Json);
            this.tp_Json.Location = new System.Drawing.Point(4, 22);
            this.tp_Json.Name = "tp_Json";
            this.tp_Json.Padding = new System.Windows.Forms.Padding(3);
            this.tp_Json.Size = new System.Drawing.Size(289, 216);
            this.tp_Json.TabIndex = 3;
            this.tp_Json.Text = "Json";
            this.tp_Json.UseVisualStyleBackColor = true;
            this.tp_Json.Enter += new System.EventHandler(this.tp_Json_Enter);
            // 
            // lv_XML
            // 
            this.lv_XML.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.XMLPoints});
            this.lv_XML.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lv_XML.Location = new System.Drawing.Point(3, 3);
            this.lv_XML.Name = "lv_XML";
            this.lv_XML.Size = new System.Drawing.Size(283, 210);
            this.lv_XML.TabIndex = 0;
            this.lv_XML.UseCompatibleStateImageBehavior = false;
            this.lv_XML.View = System.Windows.Forms.View.List;
            // 
            // XMLPoints
            // 
            this.XMLPoints.Text = "Points";
            // 
            // BinaryPoints
            // 
            this.BinaryPoints.Text = "Points";
            // 
            // lv_Soap
            // 
            this.lv_Soap.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lv_Soap.Location = new System.Drawing.Point(3, 3);
            this.lv_Soap.Name = "lv_Soap";
            this.lv_Soap.Size = new System.Drawing.Size(283, 210);
            this.lv_Soap.TabIndex = 0;
            this.lv_Soap.UseCompatibleStateImageBehavior = false;
            this.lv_Soap.View = System.Windows.Forms.View.List;
            // 
            // lv_Json
            // 
            this.lv_Json.Dock = System.Windows.Forms.DockStyle.Fill;
            this.lv_Json.Location = new System.Drawing.Point(3, 3);
            this.lv_Json.Name = "lv_Json";
            this.lv_Json.Size = new System.Drawing.Size(283, 210);
            this.lv_Json.TabIndex = 0;
            this.lv_Json.UseCompatibleStateImageBehavior = false;
            this.lv_Json.View = System.Windows.Forms.View.List;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(390, 281);
            this.Controls.Add(this.tabControl);
            this.Controls.Add(this.b_Delete);
            this.Controls.Add(this.b_Change);
            this.Controls.Add(this.b_Add);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "Point Viewer";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.tabControl.ResumeLayout(false);
            this.tp_Binary.ResumeLayout(false);
            this.tp_XML.ResumeLayout(false);
            this.tp_Soap.ResumeLayout(false);
            this.tp_Json.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListView lv_Binary;
        private System.Windows.Forms.Button b_Add;
        private System.Windows.Forms.Button b_Change;
        private System.Windows.Forms.Button b_Delete;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadToolStripMenuItem;
        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage tp_Binary;
        private System.Windows.Forms.TabPage tp_XML;
        private System.Windows.Forms.TabPage tp_Soap;
        private System.Windows.Forms.TabPage tp_Json;
        private System.Windows.Forms.ListView lv_XML;
        private System.Windows.Forms.ColumnHeader XMLPoints;
        private System.Windows.Forms.ColumnHeader BinaryPoints;
        private System.Windows.Forms.ListView lv_Soap;
        private System.Windows.Forms.ListView lv_Json;
    }
}

