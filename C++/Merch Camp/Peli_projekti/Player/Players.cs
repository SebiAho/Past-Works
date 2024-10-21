using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework;
using Peli_projekti.Cards;

namespace Peli_projekti.Player
{
    public class Players
    {

        int P_id;
        int P_Money;
        bool used_action = false, opened_tool = false;
        Merch_Card P_Merch;
        List<Tool_Card> P_Tool;
        List<Criminal_Card> P_Criminal;
        List<Skill_Card> P_Skill;
        List<Auction_Card> P_Auction;



        Color P_color;

        public Players(int _id, int money, Color _color)
        {
            P_id = _id;
            P_color = _color;

            P_Money = money;
        }

        public void InitCards(Merch_Card Merch, List<Tool_Card> Tool, List<Criminal_Card> Criminal, List<Skill_Card> Skill)
        {
            P_Merch = Merch;
            P_Tool = Tool;
            P_Criminal = Criminal;
            P_Skill = Skill;
        }

        //id
        public int getId
        {
            get { return P_id; }
        }

        //Color
        public Color getColor
        {
            get { return P_color; }
        }

        //Money
        public int getMoney
        {
            get { return P_Money; }
            set { P_Money = value; }
        }

        //Merc
        public Merch_Card getMerc
        {
            get { return P_Merch; }
        }

        //Tool
        public List<Tool_Card> getTool
        {
            get { return P_Tool; }
            set { P_Tool = value; }
        }

        public bool getOpenedTool
        {
            get { return opened_tool; }
            set { opened_tool = value; }
        }

        //Criminal
        public List<Criminal_Card> getCriminal
        {
            get { return P_Criminal; }
            set { P_Criminal = value; }
        }

        //Skill
        public List<Skill_Card> getSkill
        {
            get { return P_Skill; }
            set { P_Skill = value; }
        }

        public void AddSkill(Skill_Card skill)
        {
            if (P_Skill.Count() < 6)
            {
                P_Skill.Add(skill);
            }
        }

        //Auction
        public List<Auction_Card> getAuction
        {
            get { return P_Auction; }
            set { P_Auction = value; }
        }

        public void AddAuction(Auction_Card auct)
        {
            if (P_Auction.Count() < 6)
            {
                P_Auction.Add(auct);
            }
        }

        public bool getUsedAction
        {
            get { return used_action; }
            set { used_action = value; }
        }
    }
}
