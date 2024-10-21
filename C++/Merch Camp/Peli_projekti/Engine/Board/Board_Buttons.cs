using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Engine
{
    public class Board_Buttons
    {
        Rectangle Exit_Button, Next_Button, Music_Toggle;
        Texture2D Textures;
        bool Music, Exit, Phase;
        int Mute_Button;

        public Board_Buttons(Texture2D _textures)
        {
            Exit_Button = new Rectangle(GameDef.BoardSize.Width-550, -400, 70, 70);
            Next_Button = new Rectangle((GameDef.BoardSize.Width - 536)/2-80, 400, 160, 70);
            Music_Toggle = new Rectangle(GameDef.BoardSize.Width-550,920, 70, 70);
            Mute_Button = 530;

            Textures = _textures;
            Exit = false;
        }

        public void Update(Controlls controlls)
        {
            //Next Phase
            if (controlls.MouseRelPos().Intersects(Next_Button) && controlls.LeftMouseDoupleClick() == true)
            {
                Phase = true;
            }
            else
            {
                Phase = false;
            }

            //Enable music
            if (controlls.MouseRelPos().Intersects(Music_Toggle) && Input.LeftMouseClick() == true)
            {
                if (Mute_Button == 420)
                {
                    Mute_Button = 530;
                    Music = false;
                }
                else if (Mute_Button == 530)
                {
                    Mute_Button = 420;
                    Music = true;
                }
            }

            //Exit
            if (controlls.MouseRelPos().Intersects(Exit_Button) && controlls.LeftMouseDoupleClick() == true)
            {
                Exit = true;
            }
        }

        public bool getMusic
        {
            get { return Music; }
        }

        public bool getExit
        {
            get { return Exit; }
        }

        public int getPhase(int _phase)
        {
            if(Phase == true)
            {
                _phase++;
            }
            return _phase++;
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(Textures, Exit_Button, new Rectangle(0, 0, 100, 100), Color.White);
            spriteBatch.Draw(Textures, Next_Button, new Rectangle(100, 0, 190, 100), Color.White);
            spriteBatch.Draw(Textures, Music_Toggle, new Rectangle(Mute_Button, 0, 100, 100), Color.White);
        }

    }
}
