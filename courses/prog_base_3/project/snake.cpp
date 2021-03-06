#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include "Tetris.hpp"

using namespace sf;

void restart(std::vector<RectangleShape>& player, Text& score, int& currentScore, RectangleShape* apple = NULL);
void drawPlayer(std::vector<RectangleShape>& player, RenderWindow& window);
void movePlayer(std::vector<RectangleShape>& player, int move, Vector2f& lastPosition);
bool checkLose(std::vector<RectangleShape>& player);
bool DoRectsCollide(RectangleShape& apple, std::vector<RectangleShape>& player);

enum MOVING{UP, DOWN, LEFT, RIGHT};
const int SCREEN_WIDTH = 420, SCREEN_HEIGHT = 540;

Clock invinvibleTimer;

int snake(sf::RenderWindow & window, int hs)
{
    int h=hs;
	srand(static_cast<unsigned int>(time(0)));

	bool isPlaying = false;

	std::vector<RectangleShape> player;

	int move = UP;
	Clock moveClock;
	Clock inputClock;

	Font font;
    if (!font.loadFromFile("game_over.ttf")){
		std::cout << "Can't find the font file" << std::endl;
		return EXIT_FAILURE;
	}

    Text pauseMessage;
    pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(10);
    pauseMessage.setPosition(SCREEN_WIDTH / 3+10, SCREEN_HEIGHT - 40);
    pauseMessage.setColor(Color::Green);
    pauseMessage.setString("Press space to start the game,\n ESC to exit");

	Text score;
	score.setFont(font);
	score.setCharacterSize(10);
	score.setPosition(20, 490);
	score.setColor(Color::Green);
	int currentScore = 0;

	Text hscore;
	hscore.setFont(font);
	hscore.setCharacterSize(10);
	hscore.setPosition(20, 510);
	hscore.setColor(Color::Green);
	hscore.setString("Highscore: " + intToStr(h));

    RectangleShape wallUp(Vector2f(SCREEN_WIDTH,2));
    wallUp.setFillColor(Color::Green);
    wallUp.setPosition(0, 0);

    RectangleShape wallRDown(Vector2f(2,480));
    wallRDown.setFillColor(Color::Green);
    wallRDown.setPosition(418, 0);

    RectangleShape wallLDown(Vector2f(2,480));
    wallLDown.setFillColor(Color::Green);
    wallLDown.setPosition(0, 0);

	RectangleShape scoreBox(Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT - 480));
	scoreBox.setFillColor(Color::Black);
	scoreBox.setOutlineColor(Color::Green);
	scoreBox.setOutlineThickness(-3.f);
	scoreBox.setPosition(0, 480);
	RectangleShape apple(Vector2f(8, 8));
	apple.setPosition(-10, -10);
	apple.setFillColor(Color::Red);
	restart(player, score, currentScore);
	int Konami = 0;

    while (window.isOpen())
    {
		Vector2f lastPosition(player.at(0).getPosition().x, player.at(0).getPosition().y);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
			if(event.type == event.KeyPressed){
				if(event.key.code == Keyboard::Space){
                    hscore.setString("Highscore: " + intToStr(h));
					if(!isPlaying)
						isPlaying = true;
					restart(player, score, currentScore, &apple);
					move = UP;
					moveClock.restart();
				}
				if(event.key.code == Keyboard::Escape){
					return h;
				}
				if(inputClock.getElapsedTime().asSeconds() >= 0.07){
					if(event.key.code == Keyboard::Up && move != DOWN)
						move = UP; inputClock.restart();
					if(event.key.code == Keyboard::Down && move != UP)
						move = DOWN; inputClock.restart();
					if(event.key.code == Keyboard::Left && move != RIGHT)
						move = LEFT; inputClock.restart();
					if(event.key.code == Keyboard::Right && move != LEFT)
						move = RIGHT; inputClock.restart();
				}

				//Konami Code :D When entered correctly, adds 10000 to score
				if(isPlaying){
					if(event.key.code == Keyboard::Up && Konami == 0)
						Konami = 1;
					else if(event.key.code == Keyboard::Up && Konami == 1)
						Konami = 2;
					else if(event.key.code == Keyboard::Down && Konami == 2)
						Konami = 3;
					else if(event.key.code == Keyboard::Down && Konami == 3)
						Konami = 4;
					else if(event.key.code == Keyboard::Left && Konami == 4)
						Konami = 5;
					else if(event.key.code == Keyboard::Right && Konami == 5)
						Konami = 6;
					else if(event.key.code == Keyboard::Left && Konami == 6)
						Konami = 7;
					else if(event.key.code == Keyboard::Right && Konami == 7)
						Konami = 8;
					else if(event.key.code == Keyboard::B && Konami == 8)
						Konami = 9;
					else if(event.key.code == Keyboard::A && Konami == 9){
						std::cout << "Konami Test\n";
						currentScore += 10000;
						score.setString("Score: " + intToStr(currentScore));
						Konami = 0;
						hscore.setString("Highscore: " + intToStr(h));
					}
					else Konami = 0;
				}
			}
        }

		window.clear();
		drawPlayer(player, window);
		window.draw(wallUp);
		window.draw(wallRDown);
		window.draw(wallLDown);
		window.draw(scoreBox);
		window.draw(score);
		window.draw(hscore);
		window.draw(apple);

		if(isPlaying){
			if(moveClock.getElapsedTime().asSeconds() >= .09){
				movePlayer(player, move, lastPosition);
				moveClock.restart();
			}
			if(DoRectsCollide(apple, player)){
				currentScore += 10;
				hscore.setString("Highscore: " + intToStr(h));
				score.setString("Score: " + intToStr(currentScore));
			}
			if(checkLose(player))
				isPlaying = false;
		}
		else{
			window.draw(pauseMessage);
			if(currentScore>h){
                h=currentScore;
			}
		}

        window.display();
    }

    return h;
}

void restart(std::vector<RectangleShape>& player, Text& score, int& currentScore, RectangleShape* apple){
	player.clear();
	player.push_back(RectangleShape(Vector2f(8, 8)));
	player.at(0).setPosition(SCREEN_WIDTH / 2, 400);
	score.setString("Score: 0");
	currentScore = 0;

	int x, y;
	x = rand() % SCREEN_WIDTH;
	y = rand() % 470;
		if(apple != NULL){
			do{
				if(x % 10 != 0)
					x = rand() % SCREEN_WIDTH;
				if(y % 10 != 0)
					y = rand() % 470;
			}while(x % 10 != 0 || y % 10 != 0);
			apple->setPosition(x, y);
		}
}

void drawPlayer(std::vector<RectangleShape>& player, RenderWindow& window){
	std::vector<RectangleShape>::iterator iter;
	for(iter = player.begin(); iter < player.end(); iter++){
		window.draw(*iter);
	}
}

void movePlayer(std::vector<RectangleShape>& player, int move, Vector2f& lastPosition){
	std::vector<RectangleShape>::iterator iter, beforeIter;
	switch (move)
	{
	case UP: player.at(0).move(0, -10); break;
	case DOWN: player.at(0).move(0, 10); break;
	case LEFT: player.at(0).move(-10, 0); break;
	case RIGHT: player.at(0).move(10, 0); break;
	default: break;
	}
	Vector2f newPosition(lastPosition);
	for(iter = player.begin() + 1; iter < player.end(); iter++){
		if(player.begin() + 1 != player.end()){
			lastPosition = iter->getPosition();
			iter->setPosition(newPosition);
			newPosition = lastPosition;
		}
	}

}


bool DoRectsCollide(RectangleShape& apple, std::vector<RectangleShape>& player){
	int x, y;

	if(apple.getPosition() == player.at(0).getPosition()){
		x = rand() % SCREEN_WIDTH;
		y = rand() % 470;

		do{
			if(x % 10 != 0)
				x = rand() % SCREEN_WIDTH;
			if(y % 10 != 0)
				y = rand() % 470;
		}while(x % 10 != 0 || y % 10 != 0);
		apple.setPosition(x, y);

		for(int i = 0; i < 3; i++){
			player.push_back(RectangleShape(Vector2f(8, 8)));
			player.back().setPosition(player.begin()->getPosition().x, player.begin()->getPosition().y);
		}
		invinvibleTimer.restart();
		return true;
	}
	else
		return false;
}

bool checkLose(std::vector<RectangleShape>& player){
	std::vector<RectangleShape>::iterator iter;
	if(player.at(0).getPosition().x < 0 || player.at(0).getPosition().x > SCREEN_WIDTH - 10 ||
	   player.at(0).getPosition().y < 0 || player.at(0).getPosition().y > 470){
			return true;
	}
	if(invinvibleTimer.getElapsedTime().asSeconds() >= .12){
		for(iter = player.begin() + 1; iter < player.end(); iter++){
			if(player.at(0).getPosition() == iter->getPosition())
				return true;
		}
	}
	return false;
}
