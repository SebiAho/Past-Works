using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Cards
{
    public class Merch_Card : Card
    {
        int discount, income;

        public Merch_Card(Vector2 t_loc, Vector2 c_size, int _id, int _discount, int _income):base(t_loc,c_size,_id)
        {
            type = 1;
            discount = _discount;
            income = _income;
        }

        public int getDiscount
        {
            get { return discount; }
        }

        public int getIncome
        {
            get { return income; }
        }

    }
}
