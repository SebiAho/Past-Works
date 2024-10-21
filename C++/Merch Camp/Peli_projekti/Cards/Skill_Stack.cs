using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Cards
{
    public class Skill_Stack : Stack
    {

        public Skill_Stack(Vector2 t_loc, Rectangle s_loc) : base(t_loc, s_loc)
        {
            Cards.Add(new Skill_Card(new Vector2(0, 700), new Vector2(0, 0), 1, 3, 4));
            Cards.Add(new Skill_Card(new Vector2(230, 700), new Vector2(0, 0), 2, 2, 4));
            Cards.Add(new Skill_Card(new Vector2(460, 700), new Vector2(0, 0), 3, 3, 1));
            Cards.Add(new Skill_Card(new Vector2(690, 700), new Vector2(0, 0), 4, 4, 2));
            Cards.Add(new Skill_Card(new Vector2(920, 700), new Vector2(0, 0), 5, 5, 2));
            Cards.Add(new Skill_Card(new Vector2(1150, 700), new Vector2(0, 0), 6, 2, 5));

            Cards.Add(new Skill_Card(new Vector2(1380, 700), new Vector2(0, 0), 1, 3, 4));
            Cards.Add(new Skill_Card(new Vector2(1610, 700), new Vector2(0, 0), 2, 2, 4));
            Cards.Add(new Skill_Card(new Vector2(0, 1050), new Vector2(0, 0), 1, 3, 4));
            Cards.Add(new Skill_Card(new Vector2(230, 1050), new Vector2(0, 0), 2, 2, 4));
            Cards.Add(new Skill_Card(new Vector2(460, 1050), new Vector2(0, 0), 3, 3, 1));
            Cards.Add(new Skill_Card(new Vector2(690, 1050), new Vector2(0, 0), 4, 4, 2));

            Cards.Add(new Skill_Card(new Vector2(920, 1050), new Vector2(0, 0), 5, 5, 2));
            Cards.Add(new Skill_Card(new Vector2(1150, 1050), new Vector2(0, 0), 6, 2, 5));
            Cards.Add(new Skill_Card(new Vector2(1380, 1050), new Vector2(0, 0), 1, 3, 4));
            Cards.Add(new Skill_Card(new Vector2(1610, 1050), new Vector2(0, 0), 2, 2, 4));
            Cards.Add(new Skill_Card(new Vector2(1380, 700), new Vector2(0, 0), 1, 3, 4));
            Cards.Add(new Skill_Card(new Vector2(1600, 700), new Vector2(0, 0), 2, 2, 4));

            Cards.Add(new Skill_Card(new Vector2(1380, 700), new Vector2(0, 0), 1, 3, 4));
            Cards.Add(new Skill_Card(new Vector2(1610, 700), new Vector2(0, 0), 2, 2, 4));
            Cards.Add(new Skill_Card(new Vector2(0, 1050), new Vector2(0, 0), 1, 3, 4));
            Cards.Add(new Skill_Card(new Vector2(230, 1050), new Vector2(0, 0), 2, 2, 4));
            Cards.Add(new Skill_Card(new Vector2(460, 1050), new Vector2(0, 0), 3, 3, 1));
            Cards.Add(new Skill_Card(new Vector2(690, 1050), new Vector2(0, 0), 4, 4, 2));

            Skill_Card S_card = (Skill_Card)Cards[0];
        }

        //Take a card from stack
        public Skill_Card getCard()
        {
            Card temp = Cards[0];
            removeCard();
            return (Skill_Card)temp;
        }

        //deal multiple cards from the stack
        public List<Skill_Card> dealCards(int amount)
        {
            List<Skill_Card> temp = new List<Skill_Card>();
            for (int i = 0; i < amount; i++)
            {
                temp.Add(getCard());
            }
            return temp;
        }
    }
}
