using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Engine
{
    class Camera
    {
        private List<Rectangle> CameraBorderList;
        public Vector2 CameraPos;
        private Matrix CameraForm;
        
        public Camera()
        {
            CameraPos = Vector2.Zero;
            
            InitCameraBorders(40);
        }

        public void Move(Vector2 amount)
        {
            CameraPos += amount;
        }

        public Vector2 Pos
        {
            get{return CameraPos;}
            set { CameraPos = value; }
        }

        public Matrix GetTransformation(GraphicsDevice graphicDevice)
        {
            CameraForm = Matrix.CreateTranslation(new Vector3(-CameraPos.X, -CameraPos.Y, 0)) * Matrix.CreateTranslation(new Vector3(graphicDevice.Viewport.Width*0.005f, graphicDevice.Viewport.Height*0.005f,0));

            return CameraForm;
        }

        //Initializes borders upon whis the mouse will move the camera
        private void InitCameraBorders(int borderWidth)
        {
            Rectangle TopBorder, BottomBorder, LeftBorder, RightBorder;

            TopBorder = new Rectangle(GameDef.ScreenSize.Left, GameDef.ScreenSize.Top, GameDef.ScreenSize.Width, borderWidth);//Top border
            BottomBorder = new Rectangle(GameDef.ScreenSize.Left+borderWidth, GameDef.ScreenSize.Bottom - borderWidth, GameDef.ScreenSize.Width - 2 * borderWidth, borderWidth);//Bottom border
            LeftBorder = new Rectangle(GameDef.ScreenSize.Left, GameDef.ScreenSize.Top, borderWidth, GameDef.ScreenSize.Height);//LeftBorder
            RightBorder = new Rectangle(GameDef.ScreenSize.Right - borderWidth, GameDef.ScreenSize.Top, borderWidth, GameDef.ScreenSize.Height);//RightBorder

            CameraBorderList = new List<Rectangle> { TopBorder, BottomBorder, LeftBorder, RightBorder };
        }

        //Return camera borders
        public List<Rectangle> GetCameraBorder()
        {
            return CameraBorderList;
        }

    }
}
