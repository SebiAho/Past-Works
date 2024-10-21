using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

using Peli_projekti.Engine;

namespace Peli_projekti
{
    public class Gameboard
    {
        //Variables
        private List<List<Rectangle>> ObjectPosList = new List<List<Rectangle>>();//List for game object locations
        private List<List<CardLocation>> CardPosition = new List<List<CardLocation>>();//List of card position objects

        public Gameboard()
        {
            //Initialize object location
            ObjectPosList.Add(InitStackPos(250, 140));
            ObjectPosList.Add(InitBottomCardPos(150, 400));
            ObjectPosList.Add(InitTopCardPos(200, -400));

            //Initialize card locations
            CardPosition.Add(Decks());
            CardPosition.Add(InitPlayerCardLocations());
            CardPosition.Add(InitTopCardLocations());

        }

        //Initialize object positions
        //----------------------------------------------------------
        //Add stack positions to list (0)
        private List<Rectangle> InitStackPos(int x, int y)
        {
            List<Rectangle> object_pos_list = new List<Rectangle>();
            Rectangle Decks = new Rectangle(x,y,GameDef.CardW*2,GameDef.CardH);

            object_pos_list.Add(new Rectangle(Decks.X,Decks.Y,GameDef.CardW,GameDef.CardH));//Skill card stack

            object_pos_list.Add(new Rectangle(Decks.X + GameDef.CardW, Decks.Y, GameDef.CardW, GameDef.CardH));//Auction card stack

            object_pos_list.Add(new Rectangle(Decks.X + GameDef.CardW*2, Decks.Y, GameDef.CardW, GameDef.CardH));//Place Auction card loc

            object_pos_list.Add(new Rectangle(Decks.X + GameDef.CardW*3, Decks.Y, GameDef.CardW, GameDef.CardH));//Action card stack

            object_pos_list.Add(new Rectangle(Decks.X + GameDef.CardW*4, Decks.Y, GameDef.CardW, GameDef.CardH));//Discard card loc

            return object_pos_list;
        }
        
        //Initialize card positions that the player uses (1)
        private List<Rectangle> InitBottomCardPos(int x, int y)
        {
            List<Rectangle> object_pos_list = new List<Rectangle>();

            Rectangle BottomCards1 = new Rectangle(x, y, GameDef.CardW * 8, GameDef.CardH);
            Rectangle BottomCards2 = new Rectangle(BottomCards1.X, BottomCards1.Y+BottomCards1.Height, GameDef.CardW * 8, GameDef.CardH);
            Rectangle BottomCards3 = new Rectangle(BottomCards1.X, BottomCards2.Y+BottomCards2.Height, GameDef.CardW * 8, GameDef.CardH);
            


            object_pos_list.Add(new Rectangle(BottomCards1.X + GameDef.CardW, BottomCards1.Y, GameDef.CardW, GameDef.CardH));//0 Merc Card
            object_pos_list.Add(new Rectangle(BottomCards1.X + GameDef.CardW * 6, BottomCards1.Y, 76, 76));//1 Money

            for (int i = 0; i < 5; i++)
            {
                object_pos_list.Add(new Rectangle(BottomCards1.X + GameDef.CardW * (i+2), BottomCards1.Center.Y, GameDef.CardS, GameDef.CardS));//2 - 5 Tool Cards
            }
            
            for (int i = 0; i < 4; i++)
            {
                object_pos_list.Add(new Rectangle(BottomCards2.X + GameDef.CardW * (i+2), BottomCards2.Y, GameDef.CardW, GameDef.CardH));//3 - 7 Criminals
            }

            for (int i = 0; i < 6; i++)
            {
                object_pos_list.Add(new Rectangle(BottomCards3.X+GameDef.CardW*(i+1),BottomCards3.Y,GameDef.CardW,GameDef.CardH));//Skill Cards
            }

            object_pos_list.Add(new Rectangle(BottomCards1.X, BottomCards1.Y, GameDef.CardW, GameDef.CardH));//Auction card 1
            object_pos_list.Add(new Rectangle(BottomCards2.X, BottomCards2.Y, GameDef.CardW, GameDef.CardH));//Auction card 2
            object_pos_list.Add(new Rectangle(BottomCards3.X, BottomCards3.Y, GameDef.CardW, GameDef.CardH));//Auction card 3

            object_pos_list.Add(new Rectangle(BottomCards1.X + GameDef.CardW * 7, BottomCards1.Y, GameDef.CardW, GameDef.CardH));//Auction card 4
            object_pos_list.Add(new Rectangle(BottomCards2.X + GameDef.CardW * 7, BottomCards2.Y, GameDef.CardW, GameDef.CardH));//Auction card 5
            object_pos_list.Add(new Rectangle(BottomCards3.X + GameDef.CardW * 7, BottomCards3.Y, GameDef.CardW, GameDef.CardH));//Auction card 6

            return object_pos_list;

        }

        /*
        //Initialize card position in on Left screen (2)
        private List<Rectangle> InitLeftCardPos(int x, int y)
        {
            List<Rectangle> object_pos_list = new List<Rectangle>();

            //Left Cards
            Rectangle LeftCards1 = new Rectangle(0, 0, GameDef.CardW, GameDef.CardH * 6);
            Rectangle LeftCards2 = new Rectangle(LeftCards1.X + GameDef.CardW, LeftCards1.Y, GameDef.CardW, GameDef.CardH * 6);
            Rectangle LeftCards3 = new Rectangle(LeftCards2.X + GameDef.CardW, LeftCards1.Y, GameDef.CardW, GameDef.CardH * 6);

            object_pos_list.Add(new Rectangle(LeftCards1.X, LeftCards1.Y, GameDef.CardW, GameDef.CardH));//Merc Card
            for (int i = 0; i < 4; i++)
            {
                object_pos_list.Add(new Rectangle(LeftCards1.X, LeftCards1.Y + GameDef.CardH * (i + 1), GameDef.CardW, GameDef.CardH));//Criminal Card
            }

            for (int i = 0; i < 4; i++)
            {
                object_pos_list.Add(new Rectangle(LeftCards2.X, LeftCards2.Y + GameDef.CardH * (i + 1), GameDef.CardW, GameDef.CardH));//Auction Card 1-5
            }
            object_pos_list.Add(new Rectangle(LeftCards1.X, LeftCards1.Y + GameDef.CardH * 5, GameDef.CardW, GameDef.CardH));//Auction Card 6

            object_pos_list.Add(new Rectangle(LeftCards3.X, LeftCards3.Y + GameDef.CardS, 76, 76));//Auction Card 6
            for (int i = 0; i < 5; i++)
            {
                object_pos_list.Add(new Rectangle(LeftCards3.X, LeftCards3.Y + GameDef.CardS * (i + 2), GameDef.CardS, GameDef.CardS));//Tool Card
            }

            return object_pos_list;
        }

        //Initialize card position in on Right screen (3)
        private List<Rectangle> InitRightCardPos(int x, int y)
        {
            List<Rectangle> object_pos_list = new List<Rectangle>();

            Rectangle RightCards1 = new Rectangle(x, y, GameDef.CardW, GameDef.CardH * 6);
            Rectangle RightCards2 = new Rectangle(RightCards1.X - GameDef.CardW, RightCards1.Y, GameDef.CardW, GameDef.CardH * 6);
            Rectangle RightCards3 = new Rectangle(RightCards2.X - GameDef.CardS, RightCards1.Y, GameDef.CardW, GameDef.CardH * 6);

            object_pos_list.Add(new Rectangle(RightCards1.X, RightCards1.Y, GameDef.CardW, GameDef.CardH));//Merc Card
            for (int i = 0; i < 4; i++)
            {
                object_pos_list.Add(new Rectangle(RightCards1.X, RightCards1.Y + GameDef.CardH * (i + 1), GameDef.CardW, GameDef.CardH));//Criminal Card
            }

            for (int i = 0; i < 4; i++)
            {
                object_pos_list.Add(new Rectangle(RightCards2.X, RightCards2.Y + GameDef.CardH * (i + 1), GameDef.CardW, GameDef.CardH));//Auction Card 1-5
            }
            object_pos_list.Add(new Rectangle(RightCards1.X, RightCards1.Y + GameDef.CardH * 5, GameDef.CardW, GameDef.CardH));//Auction Card 6

            object_pos_list.Add(new Rectangle(RightCards3.X, RightCards3.Y + GameDef.CardS, 76, 76));//Auction Card 6
            for (int i = 0; i < 5; i++)
            {
                object_pos_list.Add(new Rectangle(RightCards3.X, RightCards3.Y + GameDef.CardS * (i + 2), GameDef.CardS, GameDef.CardS));//Tool Card
            }

            return object_pos_list;
        }
        */

        //Initialize card position in on top screen (4)
        private List<Rectangle> InitTopCardPos(int x, int y)
        {
            List<Rectangle> object_pos_list = new List<Rectangle>();
            //Position Rectangles
            Rectangle UpperCards1 = new Rectangle(x, y, GameDef.CardW * 6, GameDef.CardH);
            Rectangle UpperCards2 = new Rectangle(UpperCards1.X, UpperCards1.Y + GameDef.CardH, GameDef.CardW, GameDef.CardH * 6);
            Rectangle UpperCards3 = new Rectangle(UpperCards2.X, UpperCards2.Y + GameDef.CardH, GameDef.CardW, GameDef.CardH * 6);

            
            object_pos_list.Add(new Rectangle(UpperCards1.X, UpperCards1.Y, GameDef.CardW, GameDef.CardH));//Merc Card
            object_pos_list.Add(new Rectangle(UpperCards3.X, UpperCards3.Y, 76, 76));//Coins

            for (int i = 0; i < 4; i++)
            {
                object_pos_list.Add(new Rectangle(UpperCards1.X + GameDef.CardW * (i + 2), UpperCards1.Y, GameDef.CardW, GameDef.CardH));//Criminal Card
            }

            for (int i = 0; i < 5; i++)
            {
                object_pos_list.Add(new Rectangle(UpperCards2.X + GameDef.CardW * (i + 1), UpperCards2.Y, GameDef.CardW, GameDef.CardH));//Auction Card 1 -5
            }
            object_pos_list.Add(new Rectangle(UpperCards1.X + GameDef.CardW * 6, UpperCards1.Y, GameDef.CardW, GameDef.CardH));//Auction Card 6

            for (int i = 0; i < 5; i++)
            {
                object_pos_list.Add(new Rectangle(UpperCards3.Right + GameDef.CardW * i, UpperCards3.Y, GameDef.CardS, GameDef.CardS));//Tool Card
            }
            

            return object_pos_list;
        }

        //----------------------------------------------------------
                
        //Initialize card objects

        //Prefents index confusion
        private List<CardLocation> Decks()
        {
            List<CardLocation> Desc = new List<CardLocation>();
            Desc.Add(new CardLocation(ObjectPosList[0][0],4,GameDef.d_value.X));
            return Desc;
        }

        private List<CardLocation> InitPlayerCardLocations()
        {
            List<CardLocation> _initCardLoc = new List<CardLocation>();

            _initCardLoc.Add(new CardLocation(ObjectPosList[1][0], 1, 1));//Merc
            for (int i = 0; i < 5; i++)
            {
                _initCardLoc.Add(new CardLocation(ObjectPosList[1][2 + i], 2, 1));//Tool
            }

            for (int i = 0; i < 4; i++)
            {
                _initCardLoc.Add(new CardLocation(ObjectPosList[1][7 + i], 3, 1));//Criminals
            }

            for (int i = 0; i < 6; i++)
            {
                _initCardLoc.Add(new CardLocation(ObjectPosList[1][11 + i], 4, 1));//Skill
            }

            for (int i = 0; i < 6; i++)
            {
                _initCardLoc.Add(new CardLocation(ObjectPosList[1][17 + i], 5, 1));//Auction
            }

            return _initCardLoc;
        }

        private List<CardLocation> InitTopCardLocations()
        {
            List<CardLocation> _initCardLoc = new List<CardLocation>();

            _initCardLoc.Add(new CardLocation(ObjectPosList[2][0],1,2));//Merc

            for (int i = 0; i < 5; i++)
            {
                _initCardLoc.Add(new CardLocation(ObjectPosList[2][12 + i], 5, 2));//Tool
            }
            for (int i = 0; i < 4; i++)
            {
                _initCardLoc.Add(new CardLocation(ObjectPosList[2][2 + i],2,2));//Criminal
            }

            for (int i = 0; i < 6; i++)
            {
                _initCardLoc.Add(new CardLocation(ObjectPosList[2][6 + i],3,2));//Auction
            }

            return _initCardLoc;
        }

        //Return card position object list
        public List<List<CardLocation>> GetCardPos
        {
            get { return CardPosition; }
        }

        //Return object position Rectangle list
        public List<List<Rectangle>> GetCardLoc
        {
            get { return ObjectPosList; }
        }

    }
}
