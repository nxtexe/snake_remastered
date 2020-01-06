#include "snake.h"
#ifdef _WIN32

#include <windows.h>

void gotoxy(const short& x, const short& y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

#else

#include <unistd.h>
#include <term.h>

void gotoxy(const int& x, const int& y)
{
	int err;
	if (!cur_term)
		if (setupterm(NULL, STDOUT_FILENO, &err) == ERR)
			return;
	putp(tparm(tigetstr("cup"), y, x, 0, 0, 0, 0, 0, 0, 0));
}

#endif 



Sprite::Sprite() : character("*"), x(1), y(1), heading(90), length(1) {
	/* */
}

Sprite::Sprite(const std::string& character) : x(1), y(1), heading(90), length(1) {
	this->character = character;
}

const int& Sprite::xPos() const {
	return x;
}

const int& Sprite::yPos() const {
	return y;
}
void Sprite::move(const char* c, const int& score, const Game& game) {
	if (*c == 'A' || *c == 'a') {
		if (length > 1 && heading != 90)
			set_heading(-90);
		else if (length == 1)
			set_heading(-90);
	}
	else if (*c == 'D' || *c == 'd') {
		if (length > 1 && heading != -90)
			set_heading(90);
		else if (length == 1)
			set_heading(90);
	}
	else if (*c == 'W' || *c == 'w') {
		if (length > 1 && heading != -180)
			set_heading(180);
		else if (length == 1)
			set_heading(180);
	}
	else if (*c == 'S' || *c == 's') {
		if (length > 1 && heading != 180)
			set_heading(-180);
		else if (length == 1)
			set_heading(-180);
	}
	else if (*c == 27) {
		system("cls");
		std::cout << "Game Over!" << std::endl;
		std::cout << "Score: " << score << std::endl;
		is_running = true;
		system("pause");
		exit(0);
	}
	else if (*c == '\r') {
		system("pause");
	}
	int x = xPos(), y = yPos();
	if (game.get_params(game.LEVEL) == game.BOUNDED) {
		std::cout << std::boolalpha << (game.get_params(game.LEVEL) == game.BOUNDED);
		if (heading == 90 && x < 43)//continue in said direction until player moves
			set_position(x + 1, y);
		else if (heading == 90 && x >= 43) {
			system("cls");
			std::cout << "Game Over!" << std::endl;
			std::cout << "Score: " << score << std::endl;
			is_running = true;
			system("pause");
			exit(0);
		}
		else if (heading == -90 && x > 1)
			set_position(x - 1, y);
		else if (heading == -90 && x <= 1) {
			system("cls");
			std::cout << "Game Over!" << std::endl;
			std::cout << "Score: " << score << std::endl;
			is_running = true;
			system("pause");
			exit(0);
		}
		else if (heading == 180 && y > 1)
			set_position(x, y - 1);
		else if (heading == 180 && y <= 1) {
			system("cls");
			std::cout << "Game Over!" << std::endl;
			std::cout << "Score: " << score << std::endl;
			is_running = true;
			system("pause");
			exit(0);
		}
		else if (heading == -180 && y < 25)
			set_position(x, y + 1);
		else if (heading == -180 && y >= 25) {
			system("cls");
			std::cout << "Game Over!" << std::endl;
			std::cout << "Score: " << score << std::endl;
			is_running = true;
			system("pause");
			exit(0);
		}
	}
	
}
void Sprite::set_heading(const int& heading) {
	this->heading = heading;
}

void Sprite::set_position(const int& x, const int& y) {
	setX(x);
	setY(y);
	render();
}

void Sprite::setX(const int& x) {
	this->x = x;
}

void Sprite::setY(const int& y) {
	this->y = y;
}

void Sprite::render() {
	if (x > 0 && y > 0)//don't erase border :(
		gotoxy(x, y);
	std::cout << character;
}

Game::Game() : width(10), height(10), score(0), ver_border("|"), hor_border("-"), difficulty(-1), level(-1), mode(-1) {}
void Game::start() {
	ver_border.setX(0);
	ver_border.setY(0);
	hor_border.setX(0);
	hor_border.setY(0);
	render_instructions();
	draw_border();
	render_score();
}
void Game::update_score() {
	gotoxy(52, 0);
	std::cout << score;
}
bool Game::set_width(const int& width) {
	this->width = width;
	return true;
}

bool Game::set_height(const int& height) {
	this->height = height;
	return true;
}

void Game::draw_border() {
	gotoxy(0, 0);
	for (int i = 0; i < width; i++) {
		hor_border.render();
	}
	std::cout << std::endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j <= width; j++) {
			if (j == 0 || j == width - 1)
				ver_border.render();
			else
				std::cout << ' ';
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < width; i++) {
		hor_border.render();
	}
}
void Game::render_score() {
	gotoxy(45, 0);
	std::cout << "Score: " << score;
}

void Game::render_instructions() {
	gotoxy(75, 10);
	std::cout << "W - Up";
	gotoxy(55, 15);
	std::cout << "A - Left";
	gotoxy(75, 15);
	std::cout << "S - Down";
	gotoxy(95, 15);
	std::cout << "D - Right";
}

void Game::main_menu() {
	std::cout << "1. Play" << std::endl
		      << "2. Highscores\n>";
}

void Game::level_menu() {
	std::cout << "1. Infinite" << std::endl
		      << "2. Bounded\n>";
}

void Game::difficulty_menu() {
	std::cout << "1. Easy" << std::endl
		      << "2. Medium" << std::endl
			  << "3. Hard\n>";
}
void Game::set_params(const int flag, const int val) {
	switch (flag) {
		case MODE:
			mode = val;
		case LEVEL:
			level = val;
		case DIFFICULY:
			difficulty = val;
		default:
			break;
			return;
	}
}
const int Game::get_params(const int flag) const {
	switch (flag) {
		case MODE:
			return mode;
		case LEVEL:
			return level;
		case DIFFICULY:
			return difficulty;
		default:
			break;
			return 0;
	}
}
void get_char() {
	while (is_running)
		*ref = _getch();
}