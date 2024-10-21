using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Cards
{
    public class Tool_Stack : Stack
    {
        public Tool_Stack(Vector2 t_loc, Rectangle s_loc) : base(t_loc, s_loc)
        {
            //                          Texture            Location       id
            Cards.Add(new Tool_Card(new Vector2(0, 1750), new Vector2(0, 0), 1));
            Cards.Add(new Tool_Card(new Vector2(120, 1750), new Vector2(0, 0), 2));
            Cards.Add(new Tool_Card(new Vector2(240, 1750), new Vector2(0, 0), 3));
            Cards.Add(new Tool_Card(new Vector2(360, 1750), new Vector2(0, 0), 4));
            Cards.Add(new Tool_Card(new Vector2(480, 1750), new Vector2(0, 0), 5));
            Cards.Add(new Tool_Card(new Vector2(600, 1750), new Vector2(0, 0), 6));

            Cards.Add(new Tool_Card(new Vector2(720, 1750), new Vector2(0, 0), 1));
            Cards.Add(new Tool_Card(new Vector2(840, 1750), new Vector2(0, 0), 2));
            Cards.Add(new Tool_Card(new Vector2(120, 1750), new Vector2(0, 0), 3));
            Cards.Add(new Tool_Card(new Vector2(240, 1750), new Vector2(0, 0), 4));
            Cards.Add(new Tool_Card(new Vector2(360, 1750), new Vector2(0, 0), 5));
            Cards.Add(new Tool_Card(new Vector2(480, 1750), new Vector2(0, 0), 6));
            Tool_Card S_card = (Tool_Card)Cards[0];
        }

        //Take a card from stack
        public Tool_Card getCard()
        {
            Card temp = Cards[0];
            removeCard();
            return (Tool_Card)temp;
        }

        //deal multiple cards from the stack
        public List<Tool_Card> dealCards(int amount)
        {
            List<Tool_Card> temp = new List<Tool_Card>();
            for (int i = 0; i < amount; i++)
            {
                temp.Add(getCard());
            }
            return temp;
        }
    }
}
