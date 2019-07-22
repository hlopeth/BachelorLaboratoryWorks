namespace MainForm
{
    partial class Point_Constructor
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
            this.gb_x = new System.Windows.Forms.GroupBox();
            this.gb_y = new System.Windows.Forms.GroupBox();
            this.gb_z = new System.Windows.Forms.GroupBox();
            this.bt_OK = new System.Windows.Forms.Button();
            this.nud_x = new System.Windows.Forms.NumericUpDown();
            this.nud_y = new System.Windows.Forms.NumericUpDown();
            this.nud_z = new System.Windows.Forms.NumericUpDown();
            this.gb_x.SuspendLayout();
            this.gb_y.SuspendLayout();
            this.gb_z.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.nud_x)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_y)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_z)).BeginInit();
            this.SuspendLayout();
            // 
            // gb_x
            // 
            this.gb_x.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gb_x.Controls.Add(this.nud_x);
            this.gb_x.Location = new System.Drawing.Point(12, 12);
            this.gb_x.Name = "gb_x";
            this.gb_x.Size = new System.Drawing.Size(230, 47);
            this.gb_x.TabIndex = 0;
            this.gb_x.TabStop = false;
            this.gb_x.Text = "X";
            // 
            // gb_y
            // 
            this.gb_y.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gb_y.Controls.Add(this.nud_y);
            this.gb_y.Location = new System.Drawing.Point(12, 65);
            this.gb_y.Name = "gb_y";
            this.gb_y.Size = new System.Drawing.Size(230, 47);
            this.gb_y.TabIndex = 1;
            this.gb_y.TabStop = false;
            this.gb_y.Text = "Y";
            // 
            // gb_z
            // 
            this.gb_z.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.gb_z.Controls.Add(this.nud_z);
            this.gb_z.Location = new System.Drawing.Point(12, 118);
            this.gb_z.Name = "gb_z";
            this.gb_z.Size = new System.Drawing.Size(230, 47);
            this.gb_z.TabIndex = 1;
            this.gb_z.TabStop = false;
            this.gb_z.Text = "Z";
            // 
            // bt_OK
            // 
            this.bt_OK.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.bt_OK.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.bt_OK.Location = new System.Drawing.Point(12, 171);
            this.bt_OK.Name = "bt_OK";
            this.bt_OK.Size = new System.Drawing.Size(230, 36);
            this.bt_OK.TabIndex = 2;
            this.bt_OK.Text = "OK";
            this.bt_OK.UseVisualStyleBackColor = true;
            // 
            // nud_x
            // 
            this.nud_x.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.nud_x.Location = new System.Drawing.Point(6, 19);
            this.nud_x.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.nud_x.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.nud_x.Name = "nud_x";
            this.nud_x.Size = new System.Drawing.Size(218, 20);
            this.nud_x.TabIndex = 0;
            // 
            // nud_y
            // 
            this.nud_y.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.nud_y.Location = new System.Drawing.Point(6, 19);
            this.nud_y.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.nud_y.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.nud_y.Name = "nud_y";
            this.nud_y.Size = new System.Drawing.Size(218, 20);
            this.nud_y.TabIndex = 1;
            // 
            // nud_z
            // 
            this.nud_z.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.nud_z.Location = new System.Drawing.Point(6, 19);
            this.nud_z.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.nud_z.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            -2147483648});
            this.nud_z.Name = "nud_z";
            this.nud_z.Size = new System.Drawing.Size(218, 20);
            this.nud_z.TabIndex = 1;
            // 
            // Point_Constructor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(254, 226);
            this.Controls.Add(this.bt_OK);
            this.Controls.Add(this.gb_z);
            this.Controls.Add(this.gb_y);
            this.Controls.Add(this.gb_x);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "Point_Constructor";
            this.Text = "Point Сonstructor";
            this.gb_x.ResumeLayout(false);
            this.gb_y.ResumeLayout(false);
            this.gb_z.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.nud_x)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_y)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nud_z)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox gb_x;
        private System.Windows.Forms.GroupBox gb_y;
        private System.Windows.Forms.GroupBox gb_z;
        private System.Windows.Forms.Button bt_OK;
        private System.Windows.Forms.NumericUpDown nud_x;
        private System.Windows.Forms.NumericUpDown nud_y;
        private System.Windows.Forms.NumericUpDown nud_z;
    }
}