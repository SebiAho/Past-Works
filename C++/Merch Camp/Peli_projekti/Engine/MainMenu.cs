using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace Peli_projekti.Engine
{
    public class MainMenu
    {
        Texture2D textures;

        Rectangle startButtonPosition, exitButtonPosition;
        Rectangle start_image, exit_image;

        public MainMenu(Texture2D  _textures)
        {
           
            textures = _textures; //Hakee näppäin kuvat Game1 luokasta

            startButtonPosition = new Rectangle((GameDef.ScreenSize.Width / 2) - 50, 200, 100, 20);//Initialisoi sijainnin
            exitButtonPosition = new Rectangle((GameDef.ScreenSize.Width / 2) - 50, 250, 100, 20);//Initialisoi sijainnin

            start_image = new Rectangle(640, 30, 100, 20);//Asettaa start painikkeen kuvan sijainnin Graphics tiedostossa
            exit_image = new Rectangle(640, 0, 100, 20);//Asettaa exit painikkeen kuvan sijainnin Graphics tiedostossa
            
        }

        public int Update(int start_value, int exit_value, Controlls controlls)
        {
            int gamestate = 1;
            Rectangle mousepos = controlls.MouseRelPos();

            if (mousepos.Intersects(startButtonPosition) && Input.LeftMouseClick() == true)
            {
                gamestate = start_value;
            }

            if (mousepos.Intersects(exitButtonPosition) && Input.LeftMouseClick() == true)
            {
                gamestate = exit_value;
            }

            return gamestate;
        }
        
        public void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Draw(textures, startButtonPosition, start_image, Color.White);
            spriteBatch.Draw(textures, exitButtonPosition, exit_image, Color.White);
        }
    }
}
