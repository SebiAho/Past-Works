using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Cards
{
    public class Criminal_Stack : Stack
    {
        public Criminal_Stack(Vector2 t_loc, Rectangle s_loc) : base(t_loc, s_loc)
        {
            Cards.Add(new Criminal_Card(new Vector2(0, 350), new Vector2(0, 0), 1, 5));
            Cards.Add(new Criminal_Card(new Vector2(230, 350), new Vector2(0, 0), 2, 5));
            Cards.Add(new Criminal_Card(new Vector2(460, 350), new Vector2(0, 0), 3, 4));
            Cards.Add(new Criminal_Card(new Vector2(690, 350), new Vector2(0, 0), 4, 4));
            Cards.Add(new Criminal_Card(new Vector2(920, 350), new Vector2(0, 0), 5, 3));
            Cards.Add(new Criminal_Card(new Vector2(1150, 350), new Vector2(0, 0), 6, 3));

            Cards.Add(new Criminal_Card(new Vector2(1380, 350), new Vector2(0, 0), 1, 3));
            Cards.Add(new Criminal_Card(new Vector2(1610, 350), new Vector2(0, 0), 2, 3));
            Cards.Add(new Criminal_Card(new Vector2(0, 350), new Vector2(0, 0), 3, 5));
            Cards.Add(new Criminal_Card(new Vector2(230, 350), new Vector2(0, 0), 4, 5));
            Cards.Add(new Criminal_Card(new Vector2(460, 350), new Vector2(0, 0), 5, 4));
            Cards.Add(new Criminal_Card(new Vector2(690, 350), new Vector2(0, 0), 6, 4));
            Criminal_Card S_card = (Criminal_Card)Cards[0];
        }

        //Take a card from stack
        public Criminal_Card getCard()
        {
            Card temp = Cards[0];
            removeCard();
            return (Criminal_Card)temp;
        }

        //deal multiple cards from the stack
        public List<Criminal_Card> dealCards(int amount)
        {
            List<Criminal_Card> temp = new List<Criminal_Card>();
            for (int i = 0; i < amount; i++)
            {
                temp.Add(getCard());
            }
            return temp;
        }
    }
}
