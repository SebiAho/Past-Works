using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Peli_projekti.Cards
{
    public class Init_Decks
    {

        Merch_Stack M_Deck;
        Skill_Stack S_Deck;
        Criminal_Stack C_Deck;
        Tool_Stack T_Deck;
        Auction_Stack A_Deck;
        Rectangle Place_A_Card;
        Rectangle Discard_Card;

        public Init_Decks(Gameboard gameboard)
        {
            //Deck
            M_Deck = new Merch_Stack(new Vector2(0, 0), new Rectangle(0, 0, 0, 0));//Doesnt show on the screen
            M_Deck.shuffle_stack();

            T_Deck = new Tool_Stack(new Vector2(0, 0), new Rectangle(0, 0, 0, 0));
            T_Deck.shuffle_stack();

            C_Deck = new Criminal_Stack(new Vector2(0, 0), new Rectangle(0, 0, 0, 0));
            C_Deck.shuffle_stack();

            S_Deck = new Skill_Stack(new Vector2(0, 300), gameboard.GetCardLoc[0][0]);
            S_Deck.shuffle_stack();

            A_Deck = new Auction_Stack(new Vector2(140,300), gameboard.GetCardLoc[0][1]);
            A_Deck.shuffle_stack();
            
            Place_A_Card = gameboard.GetCardLoc[0][2];

            Discard_Card = gameboard.GetCardLoc[0][4];

        }

        public Merch_Stack Merc
        {
            get { return M_Deck;}
        }

        public Tool_Stack Tool
        {
            get { return T_Deck; }
        }

        public Criminal_Stack Criminal
        {
            get { return C_Deck; }
        }

        public Skill_Stack Skill
        {
            get { return S_Deck; }
        }

        public Auction_Stack Auction
        {
            get { return A_Deck; }
        }

        public Rectangle Placed_A
        {
            get { return Place_A_Card; }
            set { Place_A_Card = value; }
        }

        public Rectangle Discard
        {
            get { return Discard_Card; }
        }

    }
}
