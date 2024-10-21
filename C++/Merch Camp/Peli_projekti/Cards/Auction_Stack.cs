using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Cards
{
    public class Auction_Stack : Stack
    {

        public Auction_Stack(Vector2 t_loc, Rectangle s_loc) : base(t_loc, s_loc)
        {
            Cards.Add(new Auction_Card(new Vector2(0, 1400), new Vector2(0, 0), 1, 3));
            Cards.Add(new Auction_Card(new Vector2(230, 1400), new Vector2(0, 0), 2, 2));
            Cards.Add(new Auction_Card(new Vector2(460, 1400), new Vector2(0, 0), 3, 3));
            Cards.Add(new Auction_Card(new Vector2(690, 1400), new Vector2(0, 0), 4, 4));
            Cards.Add(new Auction_Card(new Vector2(920, 1400), new Vector2(0, 0), 5, 5));
            Cards.Add(new Auction_Card(new Vector2(1250, 1400), new Vector2(0, 0), 6, 2));

            Cards.Add(new Auction_Card(new Vector2(1380, 1400), new Vector2(0, 0), 1, 3));
            Cards.Add(new Auction_Card(new Vector2(1610, 1400), new Vector2(0, 0), 2, 2));
            Cards.Add(new Auction_Card(new Vector2(0, 1400), new Vector2(0, 0), 1, 3));
            Cards.Add(new Auction_Card(new Vector2(230, 1400), new Vector2(0, 0), 2, 2));
            Cards.Add(new Auction_Card(new Vector2(460, 1400), new Vector2(0, 0), 3, 3));
            Cards.Add(new Auction_Card(new Vector2(690, 1400), new Vector2(0, 0), 4, 4));

            Cards.Add(new Auction_Card(new Vector2(920, 1400), new Vector2(0, 0), 5, 5));
            Cards.Add(new Auction_Card(new Vector2(1250, 1400), new Vector2(0, 0), 6, 2));
            Cards.Add(new Auction_Card(new Vector2(1380, 1400), new Vector2(0, 0), 1, 3));
            Cards.Add(new Auction_Card(new Vector2(1610, 1400), new Vector2(0, 0), 2, 2));

            Auction_Card S_card = (Auction_Card)Cards[0];
        }

        //Take a card from stack
        public Auction_Card getCard()
        {
            Card temp = Cards[0];
            removeCard();
            return (Auction_Card)temp;
        }

        //deal multiple cards from the stack
        public List<Auction_Card> dealCards(int amount)
        {
            List<Auction_Card> temp = new List<Auction_Card>();
            for (int i = 0; i < amount; i++)
            {
                temp.Add(getCard());
            }
            return temp;
        }
    }
}
