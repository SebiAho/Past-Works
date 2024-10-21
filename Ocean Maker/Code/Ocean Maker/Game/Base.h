#pragma once

//Contains constant values used in the game
enum State {EXIT, MAIN_MENU, INIT_LEVEL, SELECT_LEVEL, CONTROLS, GAME, LEVEL_CLEAR, E_INIT_METHOD, E_INIT, E_INIT_INPUT, E_SELECT_LEVEL, E_EDITOR, E_DELETE_LEVEL};
enum direction {UP,DOWN,LEFT,RIGHT};

const static int SCREEN_WIDTH = 1000;
const static int SCREEN_HEIGHT = 800;

const static int FRAMERATE = 60;
const static int TILESIZE = 100;//Tile size
const static int TEXTSIZE = 100;// Size of tile image

const static int T_INSCREEN_X = (int)(SCREEN_WIDTH / TILESIZE);//Amount of tiles in screen horizontally
const static int T_INSCREEN_Y = (int)(SCREEN_HEIGHT / TILESIZE);//Amount of tiles in screen vertically
static const int MAX_MAP_WIDTH = 22, MAX_MAP_HEIGTH = 22;
