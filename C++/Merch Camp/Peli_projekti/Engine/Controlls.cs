using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Peli_projekti.Cards;
using Microsoft.Xna.Framework.Input;

namespace Peli_projekti.Engine
{
    public class Controlls
    {
        Camera camera;
        
        Matrix CameraTransform;

        List<List<Rectangle>> CardPos;
        List<List<CardLocation>> CardLoc;

        GameTime time;
        double clickTimer;
        const double timerDelay = 200;

        public Controlls(List<List<Rectangle>> _cardLoc, List<List<CardLocation>> _cardPos)
        {
            camera = new Camera();

            CardPos = _cardLoc;
            CardLoc = _cardPos;
        }

        public void Update(Matrix camTransform, GameTime _time)
        {
            Input.Update();
            CameraTransform = camTransform;
            time = _time;
        }
        
        //Left mouse douple click 
        public bool LeftMouseDoupleClick()
        {
            bool result = false;
            clickTimer += time.ElapsedGameTime.TotalMilliseconds;
            if (Input.LeftMouseClick() == true)
            {
                if (clickTimer < timerDelay)
                {
                    result = true;
                }
                clickTimer = 0;
                
            }
            return result;
        }

        //Card controlls
        //Mouse's relative position to camera
        public Rectangle MouseRelPos()
        {
            Vector2 mpos = Vector2.Transform(Input.MousePosition(), Matrix.Invert(CameraTransform));

            return new Rectangle((int)mpos.X, (int)mpos.Y, 0, 0);
        }

        //Mouse position rectangle
        public Rectangle MousePosRect()
        {
            return new Rectangle((int)Input.MousePosition().X, (int)Input.MousePosition().Y, 0, 0);
        }

        
        //Checks if mouse is on a location of a gameboard object and return its value on click
        public Point SetClickValue()
        {
            Point ClickValue = GameDef.d_value;
            {
                for (int y = 0; y < CardPos.Count(); y++)
                {
                    for (int x = 0; x < CardPos[y].Count(); x++)
                    {
                        if (Input.LeftMouseClick() == true && MouseRelPos().Intersects(CardPos[y][x]))
                        {
                            ClickValue.Y = y;
                            ClickValue.X = x;
                        }
                        
                    }
                }
            }
            return ClickValue;
        }

        //Checks if mouse is on a location of a gameboard object and return its value on click
        public Point SetReleaseValue()
        {
            Point ReleaseValue = new Point(0, 0);
            for (int y = 0; y < CardPos.Count(); y++)
            {
                for (int x = 0; x < CardPos[y].Count(); x++)
                {
                    if (Input.ReleaseLeftMouse() == true && MouseRelPos().Intersects(CardPos[y][x]))
                    {
                        ReleaseValue.Y = y;
                        ReleaseValue.X = x;
                        Console.WriteLine(ReleaseValue);
                        break;
                    }
                }
            }
            return ReleaseValue;
        }

        //Check if card location is empty
        public bool CheckIsLockEmpty(Point locValue)
        {
            Point temp = locValue;

            Console.WriteLine(CardLoc[temp.Y][temp.X].getIsEmpty);
            return CardLoc[temp.Y][temp.X].getIsEmpty;
        }

        //Camera controlls--------------------------------------
        private Vector2 cameraPos = new Vector2(0, 0);

        public Vector2 CamControls(List<Rectangle> CamBorder)
        {
            if (GameDef.ScreenSize.Width == 1200)
            {
                //Upper Screen
                if (MousePosRect().Intersects(CamBorder[0]))
                {
                    cameraPos.X = 0;
                    cameraPos.Y = -400;
                }

                //Lower Screen
                if (MousePosRect().Intersects(CamBorder[1]))
                {
                    cameraPos.X = 0;
                    cameraPos.Y = 0;
                }
            }
            //Quck fix to ensure functionality on smaller resolutions
            if (GameDef.ScreenSize.Width == 800)
            {
                //Upper Screen
                if (MousePosRect().Intersects(CamBorder[0]))
                {
                    cameraPos.Y = -400;
                }

                //Lower Screen
                if (MousePosRect().Intersects(CamBorder[1]))
                {
                    cameraPos.Y = 0;
                }

                //Right Screen
                if (MousePosRect().Intersects(CamBorder[2]))
                {
                    cameraPos.X = 100;
                }

                //Lower Middle Screen(player area)
                if (MousePosRect().Intersects(CamBorder[3]))
                {
                    cameraPos.X = 0;

                }
            }
            return cameraPos;
        }
         
    }
}
