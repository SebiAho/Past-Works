using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Peli_projekti.Engine
{
    public class Game_Spaces
    {
        int Current, Top, Round, Turn_space, old_round;
        bool Switch_Player, Switch_Round;

        public Game_Spaces()
        {
            Turn_space = 0;
            Current = 0;
            Top = 1;
            Switch_Player = false;
        }

        public void Update(int max_spaces)
        {
            SetGameRounds(max_spaces);
        }


        private void SetGameRounds(int max_spaces)//Sets the current player and number of the game round
        {
            if (Turn_space == max_spaces && Current == 0)
            {
                Turn_space = 0;
                Current = 1;
                Top = 0;
                Switch_Player = true;
            }
            if (Turn_space == max_spaces && Current == 1)
            {
                Round++;
                Turn_space = 0;
                Current = 0;
                Top = 1;
                Switch_Player = true;
            }

            if (old_round < Round)
            {
                old_round = Round;
                Switch_Round = true;
            }
            else
            {
                Switch_Round = false;
            }
        }

        public int getCurrent
        {
            get { return Current; }
        }

        public int getTop
        {
            get { return Top; }
        }

        public int getRound
        {
            get { return Round; }
        }

        public int getTurnSpace
        {
            get { return Turn_space; }     
        }

        public int setTurnSpace
        {
            set { Turn_space = value; }
        }

        public bool newRound
        {
            get {return Switch_Round; }
        }

        //Check when player changes 
        public bool getSwitchPlayer
        {
            get { return Switch_Player; }
        }

        public void setSwitchPlayer()
        {
            if (Input.LeftMouseClick() == true)
            {
                Switch_Player = false;
            }
        }

        
    }
}
