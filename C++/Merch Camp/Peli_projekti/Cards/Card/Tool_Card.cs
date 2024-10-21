using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

using Peli_projekti.Engine;

namespace Peli_projekti.Cards
{
    public class Tool_Card : Card
    {
        bool Enabled;
        public Tool_Card(Vector2 t_loc, Vector2 c_size, int _id) : base(t_loc, c_size, _id)
        {
            type = 2;

            text_loc = new Rectangle((int)t_loc.X, (int)t_loc.Y, GameDef.CImageS, GameDef.CImageS);
            card_loc = new Rectangle(locX, locY, GameDef.CardS, GameDef.CardS);
            Enabled = false;
        }
        public bool getEnabled
        {
            get { return Enabled; }
        }
        public void Enable()
        {
            Enabled = true;
        }
    }
}
