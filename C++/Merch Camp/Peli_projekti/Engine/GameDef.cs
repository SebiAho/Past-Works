using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.Xna.Framework;

namespace Peli_projekti.Engine
{
    public class GameDef
    {
        //The size of game window
        public static Rectangle ScreenSize = new Rectangle(0, 0, 1200, 1000);
        //public static Rectangle ScreenSize = new Rectangle(0, 0, 800, 600);
        
        //the size of gameboard
        public static Rectangle BoardSize = new Rectangle(0, 0, 1664, 1536);
        
        
        //Image Size
        public static int   CImageW = 229,//Large card image width
                            CImageH = 342,//Large card image height
                            CImageS = 113,//Small card image size
                            CoinImage = 114;//Coin image size
        
        //Card Size            
        public static int   CardW = 110,//Large card width
                            CardH = 194,//Large card height
                            CardS = 96;//Small card size
        
        //Other Texture Size's
        public static int CoinS = 75;//Coin size

        public static Point d_value = new Point(-1, -1);//Default value
        public static Point d_image = new Point(0, 0);//Default (Trancparent) image location
    }

}
