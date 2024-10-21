using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Engine
{
    public class CardLocation
    {
        Rectangle card_loc;
        int l_type, player;
        bool Empty = true;

        public CardLocation(Rectangle cl, int t, int _player)
        {
            card_loc = cl;
            l_type = t;
            player = _player;
        }

        //Get value
        public Rectangle getCardLoc
        {
            get { return card_loc; }
        }

        //Get value
        public int getType 
        { 
            get { return l_type; } 
        }

        //Get value
        public bool getIsEmpty
        { 
            get { return Empty; } 
        }

        //Set value
        public bool setIsEmpty
        {
            set { Empty = value; }
        }

        //Get value
        public int getPlayer
        {
            get { return player; }
        }

    }
}
