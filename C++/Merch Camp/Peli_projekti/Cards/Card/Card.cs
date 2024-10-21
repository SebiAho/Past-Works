using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

using Peli_projekti.Engine;

namespace Peli_projekti.Cards
{
    public class Card
    {
        protected Rectangle card_loc,text_loc;
        protected int locX,locY,id, type;

        public Card(Vector2 t_loc, Vector2 c_loc, int _id)
        {
            locX = (int)c_loc.X;
            locY = (int)c_loc.Y;

            text_loc = new Rectangle((int)t_loc.X, (int)t_loc.Y, GameDef.CImageW, GameDef.CImageH);
            card_loc = new Rectangle(locX,locY, GameDef.CardW, GameDef.CardH);
            id = _id;

        }

        //Return card size
        public Rectangle getLoc
        {
            get { return card_loc; }
        }
        //Return texture
        public Rectangle getTex
        {
            get { return text_loc; }
        }

        //Card locations
        public Rectangle setLoc
        {
            set { card_loc = value; }
        }

        //Get value
        public int getType
        {
            get { return type; }
        }

        
        public int getId
        {
            get { return id; }
        }
    
    }
}
