using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using Peli_projekti.Player;
using Peli_projekti.Cards;

namespace Peli_projekti.Engine
{
    public class SelecFunctions
    {
        Texture2D cards;
        Rectangle MouseCard, CardImage = new Rectangle(GameDef.d_image.X,GameDef.d_image.Y,0,0), placed_Auct_loc;
        Controlls contr;

        Point click, release;
        int p_turn, l_index, old_round, victory = 0;

        bool got_card = false, got_merch, auction_placed = false;

        Point Card_id = new Point(0,0);
        
        List<Players> players;
        Init_Decks Deck;
        Auction_Card placed_auction_card;

        public SelecFunctions(Texture2D _texture, Rectangle _placed_auct_loc)
        {
            cards = _texture;
            placed_Auct_loc = _placed_auct_loc;
        }

        public void Update(Controlls _contr, List<Players> _players, Init_Decks _deck, int _pturn, Game_Spaces _space)
        {
            players = _players;
            p_turn = _pturn;
            contr = _contr;
            Deck = _deck;

            click = _contr.SetClickValue();
            release = _contr.SetReleaseValue();
            
            MouseCard = new Rectangle(contr.MouseRelPos().X - GameDef.CardW/2, contr.MouseRelPos().Y - GameDef.CardH/2, GameDef.CardW, GameDef.CardH);
            //CardImage = new Rectangle(900, 0, 1,1);

            if (click.Y == 0)
            {
                if (click.X == 0 && _space.getTurnSpace == 2 && players[p_turn].getUsedAction == false)//Skill Deck
                {
                    Take_Skill();
                    
                }
                if (click.X == 1 && _space.getTurnSpace == 1)//Auction Deck
                {
                    place_Auction();
                }
                if (click.X == 2 && _space.getTurnSpace == 1)//Place Auction Deck
                {

                }
                if (click.X == 3)//Action Deck
                {

                }
            }

            if (release.Y == 0 && release.X == 4 && got_card == true)//Discard card
            {
                Discard_Card();
            }

            if (click.Y == 1)
            {
                if (click.X == 0)//Merc
                {
                    Card_id.Y = 1;
                    Card_id.X = players[p_turn].getMerc.getId;

                    contr.CheckIsLockEmpty(click);
                    CardImage = players[p_turn].getMerc.getTex;
                    got_merch = true;
                }

                for (int i = 0; i < 5; i++)//Tool
                {
                    if (click.X == 2 + i && players[p_turn].getTool[i].getEnabled == false && players[p_turn].getUsedAction == false)
                    {
                        openTool(_space.getRound, _space.getTurnSpace, i);
                    }
                }

                for (int i = 0; i < 6; i++)
                {
                    if (click.X == 11+i && contr.CheckIsLockEmpty(click) == false)//Skill
                    {
                            Card_id.Y = 4;
                            l_index = i;
                            Card_id.X = players[p_turn].getSkill[i].getId;
                            CardImage = players[p_turn].getSkill[i].getTex;
                            got_card = true;
                    }
                }
            }

            for (int i = 0; i < players[p_turn].getCriminal.Count(); i++)//Criminal
            {
                if (release.Y == 1 && release.X == 7 + i && got_merch == true && _space.getTurnSpace == 2 && players[p_turn].getUsedAction == false)
                {
                    HuntCriminal(i);
                    players[p_turn].getUsedAction = true;
                }
            }

            if (Input.HoldMouse() == false)//Set default values
            {
                CardImage = new Rectangle(0, 0, 0, 0);
                click = GameDef.d_value;
                got_card = false;
                got_merch = false;
            }

            if (old_round != _space.getRound)//Reset has used action variaples
            {
                players[0].getOpenedTool = false;
                players[1].getOpenedTool = false;

                players[0].getUsedAction = false;
                players[1].getUsedAction = false;
            }
            old_round = _space.getRound;
        }

        //Specific fuctions
        public void Discard_Card()//Remove skill card
        {
            if (players[p_turn].getSkill.Count() > 0)
            {
                if (Card_id.Y == 4 && l_index >= 0 && l_index <= players[p_turn].getSkill.Count())
                {                
                    players[p_turn].getSkill.RemoveAt(l_index);
                }
            }
        }

        public void Take_Skill()//Take card and add it on player cards
        {
            int cost = 4 - players[p_turn].getMerc.getDiscount;
                if (contr.CheckIsLockEmpty(release) == true && players[p_turn].getSkill.Count() < 6 && players[p_turn].getMoney >= cost)
                {
                    players[p_turn].AddSkill(Deck.Skill.getCard());
                    players[p_turn].getMoney -= cost;
                    players[p_turn].getUsedAction = true;
                }            
        }

        public void place_Auction()
        {
            placed_auction_card = Deck.Auction.getCard();
            auction_placed = true;
        }

        public void openTool(int _round, int phase, int _i)//ERROR CHECK!!!
        {        
            Random rand = new Random();
            
            if (_round == 0)
            {
                players[p_turn].getTool[_i].Enable();
            }
            else if (phase == 0 && rand.Next(1,6) == 6)
            {
                players[p_turn].getTool[_i].Enable();
            }
            players[p_turn].getUsedAction = true;
        }

        public void HuntCriminal(int _i)
        {
            Random rand = new Random();
            if (rand.Next(0, 6) <= players[p_turn].getCriminal[_i].getTakeDead)
            {
                Console.WriteLine("Arrest alive");
                players[p_turn].getCriminal.RemoveAt(_i);
            }
            else
            {
                Console.WriteLine("Arrest dead");
                players[p_turn].getCriminal.RemoveAt(_i);
            }

        }

        public int get_Continue
        {
            get { return victory; } 
        }

        
        public void Draw(SpriteBatch spriteBatch)
        {
            if (Input.HoldMouse() == true)
            {
               spriteBatch.Draw(cards,MouseCard,CardImage,Color.White);
            }

            if (auction_placed == true)
            {
                spriteBatch.Draw(cards, placed_Auct_loc, placed_auction_card.getTex, Color.White);
            }
            
            
        }
    }

}
