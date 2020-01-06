#pragma once
#include<iostream>
#include<conio.h>
#include<string>
#include<thread>
#include<chrono>
#include<vector>
#include<stdlib.h>
#include<ctime>

#ifndef __GLOBALS__
#define __GLOBALS__
extern bool is_running;
extern char c;
extern char* ref;
#endif
class Sprite {
private:
	std::string character;
	int x;
	int y;
	int heading;
public:
	int length;
	Sprite();
	Sprite(const std::string&);
	void render();
	void setX(const int&);
	void setY(const int&);
	void set_position(const int&, const int&);
	void set_heading(const int&);//180 up -180 down 90 right -90 left
	void move(const char*, const int&, const Game&);
	const int& xPos() const;
	const int& yPos() const;

};

class Game {
private:
	Sprite hor_border;
	Sprite ver_border;
	int width, height, mode, level, difficulty;
public:
	Game();
	int score;
	void start();
	void draw_border();
	void render_score();
	void update_score();
	void render_instructions();
	bool set_width(const int&);
	bool set_height(const int&);
	void main_menu();
	void level_menu();
	void difficulty_menu();
	enum Level { INFINITE=1, BOUNDED };
	enum Difficulty { EASY=1, MEDIUM, HARD };
	enum mode { PLAY = 1, HIGHSCORES = 2 };
	enum set { MODE, LEVEL, DIFFICULY };
	void set_params(const int, const int);//sets mode, level and difficulty. Flag being an integral from set
	const int get_params(const int) const;//gets mode, level and difficulty. Flag being an integral from set
};

void gotoxy(const short& x, const short& y);
void get_char();
