using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Engine
{
    public class Engine_Text
    {
        SpriteFont font1, font2;
        Vector2 camera_pos;

        int Round, Current, Turn_Phase;

        string[] Game_Phase = {"Benefit roll phase","Betting phase","Action phase",""};

        public Engine_Text(SpriteFont _font1, SpriteFont _font2)
        {
            font1 = _font1;
            font2 = _font2;
        }
        public void Update(Vector2 c_pos, int _round, int _current, int _phace)
        {
            camera_pos = c_pos;
            Round = _round+1;
            Current = _current+1;
            Turn_Phase = _phace;
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.DrawString(font1,"Round: " + Round, new Vector2(0,camera_pos.Y), Color.Black);
            spriteBatch.DrawString(font1, "Player: "+ Current, new Vector2(0, camera_pos.Y+20), Color.Black);
            spriteBatch.DrawString(font1, Game_Phase[Turn_Phase], new Vector2(0, camera_pos.Y+40), Color.Black);
        }

    }       
}
