using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace MainForm
{
    public class PointCollection : System.Collections.CollectionBase
    {
        public Point3D Add()
        {
            Point3D Item = new Point3D();
            List.Add(Item);
            return Item;
        }
        public Point3D Add(Point3D Item)
        {
            List.Add(Item);
            return Item;
        }
        public void Insert(int Index, Point3D Item)
        {
            List.Insert(Index, Item);
        }
        public void Remove(Point3D Item)
        {
            List.Remove(Item);
        }
        public Point3D this[int Index]
        {
            get
            {
                return (Point3D)List[Index];
            }
        }
    }
}
