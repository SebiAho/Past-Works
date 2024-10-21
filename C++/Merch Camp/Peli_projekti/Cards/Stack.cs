using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Peli_projekti.Engine;

namespace Peli_projekti.Cards
{
    public class Stack
    {
        Rectangle text_loc;
        Rectangle stack_loc;
        protected List<Card> Cards;
        
        public Stack(Vector2 t_loc, Rectangle s_loc)
        {
            text_loc = new Rectangle((int)t_loc.X, (int)t_loc.Y, 130, GameDef.CardH);
            stack_loc = s_loc;
            Cards = new List<Card>();
        }

        public void shuffle_stack()
        {
            Random rand = new Random();
           
            List<Card> temp = new List<Card>(Cards);
            for (int i = Cards.Count - 1; i >=0 ; i--)
            {
                int r = rand.Next(0,i+1);
                Card tempc = temp[r];
                temp[r] = temp[i];
                temp[i] = tempc;
            }
            Cards = temp;

        }

        //remove card
        protected void removeCard()
        {
            Cards.RemoveAt(0);
        }

        //Take a card from stack
        virtual public Card getCard()
        {
            Card temp = Cards[0];
            removeCard();
            return temp;
        }

        //deal multiple cards from the stack
        virtual public List<Card> dealCards(int amount)
        {
            List<Card> temp = new List<Card>();
            for (int i = 0; i < amount; i++)
            {
                temp.Add(getCard());
            }
            return temp;
        }
        
        virtual public List<Card> getStack
        {
            get { return Cards; }
        }

        //Texture location
        public Rectangle getText
        {
            get { return text_loc; }
        }

        //Stack position
        public Rectangle getLoc
        {
            get { return stack_loc; }
        }

    }
}
