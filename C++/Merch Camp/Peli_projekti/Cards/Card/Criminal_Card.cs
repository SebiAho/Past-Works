using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Cards
{
    public class Criminal_Card : Card
    {
        int takeDead;

        public Criminal_Card(Vector2 t_loc, Vector2 c_size, int _id, int _takeDead) : base(t_loc, c_size, _id)
        {
            type = 3;
            takeDead = _takeDead;
        }

        public int getTakeDead
        {
            get { return takeDead; }
        }

    }
}
