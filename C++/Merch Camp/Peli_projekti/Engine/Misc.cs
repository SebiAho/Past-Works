using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Engine.Board
{
    class Misc
    {
        Texture2D texture;
        SpriteFont Font;
        
        Money_Counter money_counter;

        public Misc(Texture2D _texture, SpriteFont _font, List<Rectangle> _moneyLoc)
        {
            texture = _texture;
            money_counter = new Money_Counter(_font, texture, _moneyLoc);
       
        }
        
        public void Update(int current_money, int top_money)
        {
            money_counter.Update(current_money, top_money);
        }

        public void Player_Turn_Screen()//Prevents players from seeing other players skill cards
        {
            
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            money_counter.Draw(spriteBatch);
            
            
        }
    }

}
