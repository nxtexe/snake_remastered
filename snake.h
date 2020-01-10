#pragma once
#include<iostream>
#include<conio.h>
#include<string>
#include<thread>//declaration of this_thread and thread for multithreading purposes specifically this_thread for
              //running game loop and thread for running input loop
#include<chrono>//declaration of chrono for milliseconds object use
#include<vector>
#include<stdlib.h>//declaration of _getch()
#include<ctime>//declaration of 

#ifndef __CLS__
#define __CLS__
#ifdef _WIN32
#define cls system("cls")
#else
#define cls system("clear")
#endif
#endif

#ifndef __GLOBALS__
#define __GLOBALS__
extern bool is_running;//condition for while loop on input thread
extern char c;//stores character recieved on input loop
extern char* ref;//reference to c
#endif
class Game;
class Sprite {
private:
	std::string character;//stores character of the sprite
	int x;//x position
	int y;//y positon
	int heading;//which direction the player is heading; 180 up -180 down 90 right -90 left
public:
	int length;//length of the snake
	Sprite();//default constructor
	Sprite(const std::string&);//to parameter is what character represents the sprite
	void render();//prints character to screen
	void setX(const int&);//sets the x position of the sprite
	void setY(const int&);//sets the y positon of the sprite
	void set_position(const int&, const int&);//sets the x and y positions of the sprite and renders the sprite at said x and y coords
	void set_heading(const int&);//sets the heading of the sprite
	void move(const char*, const int&, const Game&);//moves the character around the field of play; getting error in
	                                                //visual studio 19 saying const Game& is missing type specifier
	const int& xPos() const;//gets current x position of sprite; border characters have x y of 0
	const int& yPos() const;//gets current y position of sprite

};

class Game {
private:
	Sprite hor_border;
	Sprite ver_border;//stores the border character as a sprite object
	int width, height, mode, level, difficulty;//difficulty denotes how fast the game loop runs which dictates speed of player
	                                           //mode denotes if the player wants to see highscores or play the game
	                                           //level denots if the player would like to play with boundaries or infinite
	                                           //width and height denote the size of the game map
public:
	Game();
	int score;//keeps the player score
	void start();//renders border, instructions etc
	void draw_border();//prints the game border
	void render_score();//prints initial score
	void update_score();//changes the score without erasing screen
	void render_instructions();//prints instructions to the right of game boundary
	bool set_width(const int&);//sets width of game boundary
	bool set_height(const int&);//sets height of game boundary
	void main_menu();//prints main menu
	void level_menu();//prints level select menu
	void difficulty_menu();//prints difficulty select menu
	enum Level { UNBOUNDED=1, BOUNDED };//enum value is used to manipulate game object member object level
	enum Difficulty { EASY=1, MEDIUM, HARD };//enum value is used to manipulate game object member object difficulty
	enum mode { PLAY = 1, HIGHSCORES = 2 };//enum value is used to manipulate game object member object mode
	enum set { MODE, LEVEL, DIFFICULY };//enum value is used to manipulate game object member objects level, difficulty and mode in set_params member function
	void set_params(const int, const int);//sets mode, level and difficulty. Flag being an integral from set
	const int get_params(const int) const;//gets mode, level and difficulty. Flag being an integral from set
};

void gotoxy(const short& x, const short& y);//moves mouse cursor to x y position; stolen code
void get_char();//used for input loop on separate thread

