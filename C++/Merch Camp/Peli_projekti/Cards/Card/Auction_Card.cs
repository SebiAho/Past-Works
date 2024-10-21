using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Cards
{
    public class Auction_Card : Card
    {
        int cost, addCost;
        public Auction_Card(Vector2 t_loc, Vector2 c_size, int _id, int _cost) : base(t_loc, c_size, _id)
        {
            type = 3;

            cost = _cost;
            addCost = 0;
        }

        public int getCost
        {
            get { return cost + addCost; }
        }

        public int setCost
        {
            set {addCost = value; }
        }
    }
}
