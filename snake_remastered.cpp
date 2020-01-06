#include<iostream>
#include<conio.h>
#include<string>
#include<thread>
#include<chrono>
#include<vector>
#include<stdlib.h>
#include<ctime>

#ifdef _WIN32

#define cls system("cls")
#include <windows.h>

void gotoxy(const short& x, const short& y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

#else

#define cls system("clear")

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
bool is_running = false;
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
	void move(const char&, const int&);
	const int& xPos() const;
	const int& yPos() const;

};

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
void Sprite::move(const char& c, const int& score) {
	if (c == 'A' || c == 'a') {
		if (length > 1 && heading != 90)
			set_heading(-90);
		else if (length == 1)
			set_heading(-90);
	}
	else if (c == 'D' || c == 'd') {
		if (length > 1 && heading != -90)
			set_heading(90);
		else if (length == 1)
			set_heading(90);
	}
	else if (c == 'W' || c == 'w') {
		if (length > 1 && heading != -180)
			set_heading(180);
		else if (length == 1)
			set_heading(180);
	}
	else if (c == 'S' || c == 's') {
		if (length > 1 && heading != 180)
			set_heading(-180);
		else if (length == 1)
			set_heading(-180);
	}
	else if (c == 27) {
		cls;
		std::cout << "Game Over!" << std::endl;
		std::cout << "Score: " << score << std::endl;
		is_running = false;
		system("pause");
		exit(0);
	}
	else if (c == '\r') {
		system("pause");
	}
	int x = xPos(), y = yPos();
	if (heading == 90 && x < 43)//continue in said direction until player moves
		set_position(x + 1, y);
	else if (heading == 90 && x >= 43) {
		cls;
		std::cout << "Game Over!" << std::endl;
		std::cout << "Score: " << score << std::endl;
		is_running = false;
		system("pause");
		exit(0);
	}
	else if (heading == -90 && x > 1)
		set_position(x - 1, y);
	else if (heading == -90 && x <= 1) {
		cls;
		std::cout << "Game Over!" << std::endl;
		std::cout << "Score: " << score << std::endl;
		is_running = false;
		system("pause");
		exit(0);
	}
	else if (heading == 180 && y > 1)
		set_position(x, y - 1);
	else if (heading == 180 && y <= 1) {
		cls;
		std::cout << "Game Over!" << std::endl;
		std::cout << "Score: " << score << std::endl;
		is_running = false;
		system("pause");
		exit(0);
	}
	else if (heading == -180 && y < 25)
		set_position(x, y + 1);
	else if (heading == -180 && y >= 25) {
		cls;
		std::cout << "Game Over!" << std::endl;
		std::cout << "Score: " << score << std::endl;
		is_running = false;
		system("pause");
		exit(0);
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

class Game {
private:
	Sprite hor_border;
	Sprite ver_border;
	int width, height;
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
};

Game::Game() : width(10), height(10), score(0), ver_border("|"), hor_border("-") {}
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

char c;
char& ref = c;
void get_char() {
	while (is_running)
		ref = _getch();
}

int main() {
	srand(time(NULL));
	Game game;
	Sprite snake("*");
	Sprite fruit("o");
	game.set_width(45);
	game.set_height(25);
	game.start();
	std::thread t1(get_char);
	std::vector<Sprite> snake_body;
	snake_body.push_back(snake);
	int last_tailX, last_tailY;
	fruit.set_position(rand() % 44, rand() % 26);
	while (true) {
		for (int i = 0; i < snake_body.size(); i++) {
			gotoxy(snake_body[i].xPos(), snake_body[i].yPos());
			std::cout << ' ';
			int tempX = snake_body[i].xPos(), tempY = snake_body[i].yPos();
			if (i > 0) {
				snake_body[i].set_position(last_tailX, last_tailY);
			}
			last_tailX = tempX;
			last_tailY = tempY;
		}
		snake_body[0].move(ref, game.score);
		for (int i = 1; i < snake_body.size(); i++) {
			if (snake_body[0].xPos() == snake_body[i].xPos() && snake_body[0].yPos() == snake_body[i].yPos()) {
				cls;
				std::cout << "Game Over!" << std::endl;
				std::cout << "Score: " << game.score << std::endl;
				is_running = false;
				system("pause");
				exit(0);
			}
		}
		int fruitX = fruit.xPos(), fruitY = fruit.yPos(), x = snake_body[0].xPos(), y = snake_body[0].yPos();
		if (fruitX == x && fruitY == y) {
			snake_body[0].length += 1;
			Sprite tail("*");
			snake_body.push_back(tail);
			game.score += 1000;
			gotoxy(fruitX, fruitY);
			std::cout << ' ';
			fruit.setX(rand() % 45 + 1);
			fruit.setY(rand() % 26 + 1);
			for (int i = 0; i < snake_body.size(); i++) {
				if (fruit.xPos() == snake_body[i].xPos() && fruit.yPos() == snake_body[i].yPos()
					|| fruit.xPos() > 43 || fruit.yPos() > 24) {
					fruit.setX(rand() % 44);
					fruit.setY(rand() % 26);
				}
				else {
					continue;
				}
			}
			fruit.render();
		}
		game.update_score();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		fruit.render();
	}
}
