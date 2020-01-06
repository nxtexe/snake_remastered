#include "snake.h"
#include<ctype.h>

bool is_running = true;
char c = 'd';
char* ref = &c;
int main() {
	srand(time(NULL));//initialized rand()
	Game game;
	Sprite snake("*");
	Sprite fruit("o");
	game.set_width(45);
	game.set_height(25);
	//below input loops get parameters to initialize the game; mode, level, difficulty repsectively
	char choice = '-1';//stores player choice for switch cases
	bool invalid = true;//menu input loop condition
	game.main_menu();//print menu
	while(invalid) {//input loop for menu
		std::cin >> choice;
		switch ((int)choice-48) {
			case game.PLAY:
				game.set_params(game.MODE, game.PLAY);
				cls;
				invalid = false;
				break;
			case game.HIGHSCORES:
				game.set_params(game.MODE, game.HIGHSCORES);
				cls;
				invalid = false;
				break;
			default:
				std::cout << "Invalid!";
				std::cout << "\n>";
				std::cin.sync();
				std::cin.clear();
				break;
		}
	}
	invalid = true;//menu input loop condition
	std::cin.sync();
	std::cin.clear();//clear stream
	game.level_menu();//print level menu
	while (invalid) {//input loop for menu
		std::cin >> choice;
		switch ((int)choice-48) {
			case game.INFINITE:
				game.set_params(game.LEVEL, game.INFINITE);
				cls;
				invalid = false;
				break;
			case game.BOUNDED:
				game.set_params(game.LEVEL, game.BOUNDED);
				cls;
				invalid = false;
				break;
			default:
				std::cout << "Invalid!";
				std::cout << "\n>";
				std::cin.sync();
				std::cin.clear();
				break;
		}
	}
	invalid = true;//menu input loop condition
	std::cin.sync();
	std::cin.clear();//clear stream
	game.difficulty_menu();//print menu
	while (invalid) {//input loop for menu
		std::cin >> choice;
		switch ((int)choice - 48) {
		case game.EASY:
			game.set_params(game.DIFFICULY, game.EASY);
			cls;
			invalid = false;
			break;
		case game.MEDIUM:
			game.set_params(game.DIFFICULY, game.MEDIUM);
			cls;
			invalid = false;
			break;
		case game.HARD:
			game.set_params(game.DIFFICULY, game.HARD);
			cls;
			invalid = false;
			break;
		default:
			std::cout << "Invalid!";
			std::cout << "\n>";
			std::cin.sync();
			std::cin.clear();
			break;
		}
	}
	std::thread t1(get_char);//input loop thread
	game.start();
	std::vector<Sprite> snake_body;//stores segments of the snake
	snake_body.push_back(snake);//add head to vector of type Snake
	int last_tailX, last_tailY;//stores position of tail
	fruit.set_position(rand() % 44, rand() % 26);
	while (true) {
		for (int i = 0; i < snake_body.size(); i++) {
			gotoxy(snake_body[i].xPos(), snake_body[i].yPos());
			std::cout << ' ';//clears tail from current position
			int tempX = snake_body[i].xPos(), tempY = snake_body[i].yPos();//store current position in temporarily in scope
			if (i > 0) {
				snake_body[i].set_position(last_tailX, last_tailY);//sets tail position to tail sprite infront; mimics snake like movement
			}
			last_tailX = tempX;//stores temporary variable outside of scope to keep track of last tail sprite and continue simulating movement
			last_tailY = tempY;
		}
		Game& game_ref = game;//reference to game object
		snake_body[0].move(ref, game.score, game_ref);//move the snake even if no new input recieved
		for (int i = 1; i < snake_body.size(); i++) {//snake head-tail collision detection
			if (snake_body[0].xPos() == snake_body[i].xPos() && snake_body[0].yPos() == snake_body[i].yPos()) {//if they collide
				cls;//clear screen
				std::cout << "Game Over!" << std::endl;//game over
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