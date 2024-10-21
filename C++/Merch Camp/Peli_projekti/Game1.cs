using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

using Peli_projekti.Engine;
using Peli_projekti.Cards;
using Peli_projekti.Player;

namespace Peli_projekti
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;

        //Game variaples

        //Imagemap
        Texture2D Cards, textures;
        //Font
        SpriteFont MoneyFont, EngineFont;

        //Screensize
        Rectangle Screensize;

        //Game variaples
        int Game_State, Player_Turn;

        //Object positions
        public List<List<CardLocation>> CardPositions;
        BoardFunctions board_functions;

        //Deck
        Init_Decks Init_Deck;

        //Players
        Players Player1, Player2;
        List<Players> players;

        //Audio
        SoundEffect soundEngine;
        SoundEffectInstance soundEngineInstance;
        SoundEffect BackgroundMusic;

        //Classes
        MainMenu main_menu;
        Gameboard gameboard;//gameboard structure
        Camera camera;
        Controlls controlls;
        SelecFunctions SelectCard;

        Game_Spaces GTurn;
        Engine_Text Game_text;
        Board_Buttons buttons;

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            graphics.PreferredBackBufferWidth = GameDef.ScreenSize.Width;
            graphics.PreferredBackBufferHeight = GameDef.ScreenSize.Height;

            Content.RootDirectory = "Content";
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            
            IsMouseVisible = true;

            //Screen size
            Screensize = new Rectangle(0, 0, GraphicsDevice.Viewport.Width, GraphicsDevice.Viewport.Height);
            gameboard = new Gameboard();

            //Classes
            camera = new Camera();
            controlls = new Controlls(gameboard.GetCardLoc, gameboard.GetCardPos);
            GTurn = new Game_Spaces();
            
            //Deck
            Init_Deck = new Init_Decks(gameboard);

            //Players
            Player1 = new Players(1, 0, Color.LightSlateGray);
            Player1.InitCards(Init_Deck.Merc.getCard(), Init_Deck.Tool.dealCards(5), Init_Deck.Criminal.dealCards(4), Init_Deck.Skill.dealCards(5));
            Player1.getMoney = Player1.getMerc.getIncome;

            Player2 = new Players(2, 0, Color.Beige);
            Player2.InitCards(Init_Deck.Merc.getCard(), Init_Deck.Tool.dealCards(5), Init_Deck.Criminal.dealCards(4), Init_Deck.Skill.dealCards(6));

            players = new List<Players>();
            players.Add(Player1);
            players.Add(Player2);

            //Other initializations
            CardPositions = gameboard.GetCardPos;
            Game_State = 1;
            Player_Turn = 0;

            base.Initialize();
        }

        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        { 
            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);
            
            //Textures
            Cards = Content.Load<Texture2D>("Cards");
            textures = Content.Load<Texture2D>("Graphics");

            //Font
            MoneyFont = Content.Load<SpriteFont>("GameFont");
            EngineFont = Content.Load<SpriteFont>("GameFont2");

            //Audio
            soundEngine = Content.Load<SoundEffect>("Main_16bit");
            soundEngineInstance = soundEngine.CreateInstance();
            soundEngineInstance.IsLooped = true;

            //Classes
            main_menu = new MainMenu(textures);
            board_functions = new BoardFunctions(Cards, textures,MoneyFont,gameboard.GetCardLoc[1][1],gameboard.GetCardLoc[2][1]);
            SelectCard = new SelecFunctions(Cards, gameboard.GetCardLoc[0][2]);
            Game_text = new Engine_Text(EngineFont, MoneyFont);
            buttons = new Board_Buttons(textures);

        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {

        }
        
        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            // Allows the game to exit
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed)
                this.Exit();

            controlls.Update(camera.GetTransformation(GraphicsDevice),gameTime);//Update controls


            if (Game_State == 1)//Title
            {
                Game_State = main_menu.Update(2, 0, controlls);
            }
            
            if (Game_State == 2)//Game
            {
                GTurn.Update(3);
                Player_Turn = GTurn.getCurrent;
                board_functions.Update(CardPositions, Player_Turn, players);//Update board functions

                if (GTurn.getSwitchPlayer == true)//Prepare for Next player
                {
                    GTurn.setSwitchPlayer();
                    if (Input.LeftMouseClick() == true)
                    {
                        players[GTurn.getCurrent].getMoney += players[GTurn.getCurrent].getMerc.getIncome;
                    }
                }
                else
                {
                    
                    
                    controlls.SetReleaseValue();
                    
                    camera.CameraPos = controlls.CamControls(camera.GetCameraBorder());//camera controls


                    SelectCard.Update(controlls, players, Init_Deck, board_functions.getCurrent, GTurn);

                    buttons.Update(controlls);
                    GTurn.setTurnSpace = buttons.getPhase(GTurn.getTurnSpace);//Change player turn                    

                    Game_text.Update(camera.CameraPos,GTurn.getRound,Player_Turn,GTurn.getTurnSpace);
                    if (buttons.getMusic == true)
                    {
                        soundEngineInstance.Volume = 0.75f;
                        soundEngineInstance.Play();
                    }
                    else
                    {
                        soundEngineInstance.Pause();
                    }

                    if (buttons.getExit != false)//Exit button
                    {
                        Game_State = 0;
                    }

                    //Quick and dirty victory condition
                    if (players[GTurn.getCurrent].getCriminal.Count == 0)
                    {
                        if (Input.LeftMouseClick() == true)
                        {
                            Game_State = 0;
                        }
                    }
                }
            }

            if(Game_State == 0)//Exit
            {
                this.Exit();
            }

            //S_stack.getCard[1].getId;
            
            base.Update(gameTime);
        }
        
        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {
       
            GraphicsDevice.Clear(players[Player_Turn].getColor);

            spriteBatch.Begin(SpriteSortMode.Immediate, null, null, null, null, null, camera.GetTransformation(GraphicsDevice));
            if (Game_State == 1)
            {
                main_menu.Draw(spriteBatch);
            }

            if (Game_State == 2)
            {
                if (GTurn.getSwitchPlayer == true)//Prefent players from seeink each others screen;
                {
                    spriteBatch.DrawString(MoneyFont, "Click to start next player turn", new Vector2(GameDef.ScreenSize.Width * 0.25f, GameDef.ScreenSize.Height * 0.5f), Color.Black);
                }

                //Quick and dirty victory condition
                else if (players[GTurn.getCurrent].getCriminal.Count == 0)
                {
                    int temp = GTurn.getCurrent + 1;
                    spriteBatch.DrawString(MoneyFont, "The winner is player " + temp, new Vector2(GameDef.ScreenSize.Width * 0.25f, GameDef.ScreenSize.Height * 0.5f), Color.Red);
                }
               
                
                else
                {
                    Game_text.Draw(spriteBatch);
                    buttons.Draw(spriteBatch);
                    for (int x = 0; x < CardPositions.Count; x++)
                    {
                        for (int y = 0; y < CardPositions[x].Count; y++)
                        {
                            spriteBatch.Draw(textures, CardPositions[x][y].getCardLoc, new Rectangle(0, 100, GameDef.CardW, GameDef.CardH), Color.White);//Large card top
                        }
                    }
                    spriteBatch.Draw(textures, Init_Deck.Skill.getLoc, Init_Deck.Skill.getText, Color.White);//Skill Deck
                    spriteBatch.Draw(textures, Init_Deck.Auction.getLoc, Init_Deck.Auction.getText, Color.White);//Auction Deck
                    spriteBatch.Draw(textures, gameboard.GetCardLoc[0][2], new Rectangle(0,100,GameDef.CardW,GameDef.CardH), Color.White);//Auction Card place
                    spriteBatch.Draw(textures, Init_Deck.Discard, new Rectangle(120, 100, 130, GameDef.CardH), Color.White);//Discard Deck


                    board_functions.Draw(spriteBatch);

                    SelectCard.Draw(spriteBatch);

                }
            }

            spriteBatch.End();
            base.Draw(gameTime);
        }
    }
}
