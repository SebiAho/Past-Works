using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Cards
{
    public class Skill_Card : Card
    {
        int auct, cost;

        public Skill_Card(Vector2 t_loc, Vector2 c_size, int _id, int _auct, int _cost):base(t_loc,c_size,_id)
        {
            type = 4;
            auct = _auct;
            cost = _cost;
        }

        public int getCost
        {
            get { return cost; }
        }

        public int getAuct
        {
            get { return auct; }
        }
    }
}
