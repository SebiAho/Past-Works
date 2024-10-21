using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Engine
{
    class Money_Counter
    {

        int p1_money, p2_money = 0;
        string p1_text_money, p2_text_money;
  
        SpriteFont Font;
        Texture2D texture;
        List<Rectangle> money_loc;

        public Money_Counter(SpriteFont _font, Texture2D _texture, List<Rectangle> _money_loc)
        {
            Font = _font;
            texture = _texture;
            money_loc = _money_loc;
        }

        public void Update(int _p1_money, int _p2_money)
        {
            p1_text_money = _p1_money.ToString();
            p2_text_money = _p2_money.ToString();
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(texture, money_loc[0], new Rectangle(300,0, 115, 115), Color.White);
            spriteBatch.DrawString(Font, p1_text_money, new Vector2(money_loc[0].X + GameDef.CoinS*0.25f, money_loc[0].Y + GameDef.CoinS*0.15f), Color.YellowGreen);

            spriteBatch.Draw(texture, money_loc[1], new Rectangle(300, 0, 115, 115), Color.White);
            spriteBatch.DrawString(Font, p2_text_money, new Vector2(money_loc[1].X + GameDef.CoinS * 0.25f, money_loc[1].Y + GameDef.CoinS * 0.15f), Color.GreenYellow);
        }

    }
}
