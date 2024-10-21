using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Cards
{
    public class Merch_Stack : Stack
    {
        public Merch_Stack(Vector2 t_loc, Rectangle s_loc) : base(t_loc, s_loc)
        {            
            Cards.Add(new Merch_Card(new Vector2(230, 0), new Vector2(0, 0), 2, 0, 5));
            Cards.Add(new Merch_Card(new Vector2(460, 0), new Vector2(0, 0), 1, 1, 4));
            Cards.Add(new Merch_Card(new Vector2(690, 0), new Vector2(0, 0), 2, 0, 5));
            Cards.Add(new Merch_Card(new Vector2(920, 0), new Vector2(0, 0), 1, 1, 4));
        }

        //Take a card from stack
        public Merch_Card getCard()
        {
            Card temp = Cards[0];
            removeCard();
            return (Merch_Card)temp;
        }

    }
}
