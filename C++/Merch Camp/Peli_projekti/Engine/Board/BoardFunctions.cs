using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Peli_projekti.Player;
using Peli_projekti.Cards;
using Microsoft.Xna.Framework;
using Peli_projekti.Engine.Board;

namespace Peli_projekti.Engine
{
    public class BoardFunctions
    {
        List<Players> players;
        List<List<CardLocation>> Card_Loc;
        int p_turn;
        int Current,Top;
        Texture2D Placeholder, textures;
        Misc misc;
        List<Rectangle> money_loc = new List<Rectangle>();

        public BoardFunctions(Texture2D _placeholder, Texture2D _textures,SpriteFont _font, Rectangle p1_m_loc, Rectangle p2_m_loc)
        {
            Placeholder = _placeholder;
            textures = _textures;

            money_loc.Add(p1_m_loc);
            money_loc.Add(p2_m_loc);

            misc = new Misc(textures,_font,money_loc);
        }

        public void Update(List<List<CardLocation>> _cardloc, int _playerturn, List<Players> _players)
        {
            players = _players;

            Card_Loc = _cardloc;//Location of cards
            p_turn = _playerturn;//Player turn

            Initialize_Board();
            misc.Update(players[Current].getMoney, players[Top].getMoney);

            Is_Empty();
        }

        //Initializes gameboard
        public void Initialize_Board()
        {
            //get players
            SetCurrentPlayer();

            //Current player
            //Merch
            players[Current].getMerc.setLoc = Card_Loc[1][0].getCardLoc;
            
            //Tool
            if (players[Current].getTool == null) { }//Check if list is empty
            else
            {
                for (int i = 0; i < players[Current].getTool.Count(); i++)
                {
                    players[Current].getTool[i].setLoc = Card_Loc[1][1 + i].getCardLoc;
                    
                }
            }

            //Criminal
            if (players[Current].getCriminal == null) { }
            else
            {
                for (int i = 0; i < players[Current].getCriminal.Count(); i++)
                {
                    players[Current].getCriminal[i].setLoc = Card_Loc[1][6 + i].getCardLoc;
                }
            }

            //Skill
            if (players[Current].getSkill == null) { }
            else
            {
                for (int i = 0; i < players[Current].getSkill.Count(); i++)
                {
                    players[Current].getSkill[i].setLoc = Card_Loc[1][10 + i].getCardLoc;
                }
            }
            

            //Auction
            if (players[Current].getAuction == null) { }
            else
            {
                for (int i = 0; i < players[Current].getAuction.Count(); i++)
                {
                    players[Current].getAuction[i].setLoc = Card_Loc[1][16 + i].getCardLoc;
                }
            }


            //Top Player-------------------------------
            //Merc
            players[Top].getMerc.setLoc = Card_Loc[2][0].getCardLoc;

            //Tool
            if (players[Top].getTool == null) { }//Check if list is empty
            else
            {
                for (int i = 0; i < players[Top].getTool.Count(); i++)
                {
                    players[Top].getTool[i].setLoc = Card_Loc[2][1 + i].getCardLoc;
                }
            }

            //Criminal
            if (players[Top].getCriminal == null) { }
            else
            {
                for (int i = 0; i < players[Top].getCriminal.Count(); i++)
                {
                    players[Top].getCriminal[i].setLoc = Card_Loc[2][6 + i].getCardLoc;
                }
            }

            //Auction
            if (players[Top].getAuction == null) { }
            else
            {
                for (int i = 0; i < players[Top].getAuction.Count(); i++)
                {
                    players[Top].getAuction[i].setLoc = Card_Loc[2][16 + i].getCardLoc;
                }
            }
        }

        public Color getColor//Change board color
        {
            get { return players[Current].getColor; }
        }

        private void SetCurrentPlayer()
        {
            //get players
            if (p_turn == 0)
            {
                Current = 0;
                Top = 1;
            }
            else if (p_turn == 1)
            {
                Current = 1;
                Top = 0;
            }
        }

        private void Is_Empty()
        {
            //Set all empty
            for (int y = 0; y < Card_Loc.Count; y++)
            {
                for (int x = 0; x < Card_Loc[y].Count; x++)
                {
                    Card_Loc[y][x].setIsEmpty = true;
                }
            }

            //Current
            //Ceck Merc location
            if (Card_Loc[1][0].getCardLoc.Intersects(players[Current].getMerc.getLoc))
            {
                Card_Loc[1][0].setIsEmpty = false;
            }

            //Check Tool location
            if (players[Top].getTool == null) { }
            else
            {
                for (int i = 0; i < players[Current].getTool.Count(); i++)
                {
                    if (Card_Loc[1][1 + i].getCardLoc.Intersects(players[Current].getTool[i].getLoc))
                    {
                        Card_Loc[1][1 + i].setIsEmpty = false;
                    }
                }
            }

            //Check Criminal location
            if (players[Top].getCriminal == null) { }
            else
            {
                for (int i = 0; i < players[Current].getCriminal.Count(); i++)
                {
                    if (Card_Loc[1][6 + i].getCardLoc.Intersects(players[Current].getCriminal[i].getLoc))
                    {
                        Card_Loc[1][6 + i].setIsEmpty = false;
                    }
                }
            }

            //Check Skill location
            if (players[Current].getSkill == null) { }
            else
            {
                for (int i = 0; i < players[Current].getSkill.Count(); i++)
                {
                    if (Card_Loc[1][10 + i].getCardLoc.Intersects(players[Current].getSkill[i].getLoc))
                    {
                        Card_Loc[1][10 + i + 1].setIsEmpty = false;//i +1 Voi tuottaa ongelmia
                    }
                }
            }

            //Check Auction location
            if (players[Top].getAuction == null) { }
            else
            {
                for (int i = 0; i < players[Current].getAuction.Count(); i++)
                {
                    if (Card_Loc[1][16 + i].getCardLoc.Intersects(players[Current].getAuction[i].getLoc))
                    {
                        Card_Loc[1][16 + i].setIsEmpty = false;
                    }
                }
            }
            //Top
            //Check Tool location

        }

        public int getCurrent//Get current player;
        {
            get { return Current; }
        }

        public int getTop//Get top player;
        {
            get { return Top; }
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            //Current player-------------------------------------------------

            //Draw Merc
             spriteBatch.Draw(Placeholder,players[Current].getMerc.getLoc,players[Current].getMerc.getTex,Color.White);
            
            //Draw tool
            if (players[Current].getTool == null) { }//Check if list is empty
            else
            {
                for (int i = 0; i < players[Current].getTool.Count(); i++)
                {
                    if (players[Current].getTool[i].getEnabled == false)
                    {

                        spriteBatch.Draw(Placeholder, players[Current].getTool[i].getLoc, new Rectangle(960, 1750, GameDef.CImageS, GameDef.CImageS), Color.White);
                    }
                    else
                    {
                        spriteBatch.Draw(Placeholder, players[Current].getTool[i].getLoc, players[Current].getTool[i].getTex, Color.White);
                    }
                }
            }

            //Draw Criminal
            if (players[Current].getCriminal == null) { }
            else
            {
                for (int i = 0; i < players[Current].getCriminal.Count(); i++)
                {
                    spriteBatch.Draw(Placeholder, players[Current].getCriminal[i].getLoc, players[Current].getCriminal[i].getTex, Color.White);
                }
            }

            //Draw skill
            for (int i = 0; i < players[Current].getSkill.Count(); i++)
            {
                spriteBatch.Draw(Placeholder,players[Current].getSkill[i].getLoc,players[Current].getSkill[i].getTex,Color.White);
            }

            //Draw Auction
            if (players[Current].getAuction == null) { }
            else
            {
                for (int i = 0; i < players[Current].getAuction.Count(); i++)
                {
                    spriteBatch.Draw(Placeholder, players[Current].getAuction[i].getLoc, players[Current].getAuction[i].getTex, Color.White);
                }
            }

            //Top Cards-----------------------------------

            //Draw Merc
            spriteBatch.Draw(Placeholder, players[Top].getMerc.getLoc, players[Top].getMerc.getTex, Color.White);

            //Draw tool
            if (players[Top].getTool == null) { }//Check if list is empty
            else
            {
                for (int i = 0; i < players[Top].getTool.Count(); i++)
                {
                    if (players[Top].getTool[i].getEnabled == false)
                    {

                        spriteBatch.Draw(Placeholder, players[Top].getTool[i].getLoc, new Rectangle(960, 1750, GameDef.CImageS, GameDef.CImageS), Color.White);
                    }
                    else
                    {
                        spriteBatch.Draw(Placeholder, players[Top].getTool[i].getLoc, players[Top].getTool[i].getTex, Color.White);
                    }
                }
            }
            
            //Draw Criminal
            if (players[Top].getCriminal == null) { }
            else
            {
                for (int i = 0; i < players[Top].getCriminal.Count(); i++)
                {
                    spriteBatch.Draw(Placeholder, players[Top].getCriminal[i].getLoc, players[Top].getCriminal[i].getTex, Color.White);
                }
            }

           
            //Draw Auction
            if (players[Top].getAuction == null) { }
            else
            {
                for (int i = 0; i < players[Top].getAuction.Count(); i++)
                {
                    spriteBatch.Draw(Placeholder, players[Top].getAuction[i].getLoc, players[Top].getAuction[i].getTex, Color.White);
                }
            }

            misc.Draw(spriteBatch);
            
        }
    }
}
