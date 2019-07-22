using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace WinFormsControlLib
{
    /// <summary>
    /// Логика взаимодействия для UserControl1.xaml
    /// </summary>
    public partial class UserControl1 : UserControl
    {
        public UserControl1()
        {
            InitializeComponent();
            Start();
        }
        
        void Start()
        {
            draw(null, null);
            DispatcherTimer timer = new DispatcherTimer();
            timer.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timer.Tick += draw;
            timer.Start();
        }

        private void draw(object sender, EventArgs e)
        {
            DateTime dt = DateTime.Now;
            rotateSecond.Angle = 6 * dt.Second;
            rotateMinute.Angle = 6 * dt.Minute;
            rotateHour.Angle = 30 * (dt.Hour % 12) + rotateMinute.Angle / 12;
        }
    }
}
