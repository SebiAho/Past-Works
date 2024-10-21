using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework;

namespace Peli_projekti.Engine
{
    class Input
    {
        static MouseState mouse_state, old_mouse_state;
        static KeyboardState key_state, old_key_state;
        public static void Update()
        {
            old_mouse_state = mouse_state;
            mouse_state = Mouse.GetState();

            old_key_state = key_state;
            key_state = Keyboard.GetState();
        }
        
        //Mouse
        //Hold left mouse button
        public static bool HoldMouse()
        {
            return mouse_state.LeftButton == ButtonState.Pressed;
        }

        //Release mouse button
        public static bool ReleaseLeftMouse()
        {
            return mouse_state.LeftButton == ButtonState.Released && old_mouse_state.LeftButton == ButtonState.Pressed;
        }

        //Left mouse click
        public static bool LeftMouseClick()
        {
            return mouse_state.LeftButton == ButtonState.Pressed && old_mouse_state.LeftButton == ButtonState.Released;
        }

        //Right mouse click
        public static bool RightMouseClick()
        {
            return mouse_state.RightButton == ButtonState.Pressed && old_mouse_state.RightButton == ButtonState.Released;
        }

        //Get the mouse position
        public static Vector2 MousePosition()
        {
            return new Vector2(mouse_state.X, mouse_state.Y);
        }

        public static bool PressKey(Keys k)
        {
            return key_state.IsKeyDown(k) && old_key_state.IsKeyUp(k);
        }
    }
}
