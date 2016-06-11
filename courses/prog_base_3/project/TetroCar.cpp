#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "Tetris.hpp"

using namespace sf;

const int WIDTH = 10;
const int HEIGHT = 18;
const int SIZE = 30;


bool SHAPE[4][3] = { {0,1,0},
                      {1,1,1},
                      {0,1,0},
                      {1,0,1} };

enum wallIndexes { I = 0, J = 1, S = 2};

bool WALLS[][9] ={  {1,1,1,1,1,1,0,0,0} ,
                       {0,0,0,1,1,1,1,1,1} ,
                       {1,1,1,0,0,0,1,1,1} };

class Wall
{
    private:
        int wallIndex;
        int data[9], posX, posY;
        sf::Color color;

        void fillData()
        {
                for(int m=0;m < 9;m++)
                    data[m] = WALLS[wallIndex][m];
        }

    public:
        Wall()
        {
            posX = 1;
            posY = 0;
            generate();
        }

        void generate()
        {
            int g = rand() % 3;
            wallIndex = (wallIndexes)g;
            color = sf::Color::White;
            fillData();
        }

        void move(int y)
        {
            if(isValid(y))
            {
                posY += y;
            }
        }

        bool isValid(int yOffset = 0)
        {
                for(int x=0;x < 9;x++)
                    if(data[x] && (posY +yOffset > HEIGHT) )
                    {
                        return false;
                    }

            return true;
        }

        void draw(sf::RenderWindow & window)
        {
                for(int m=0;m < 9;m++)
                    if(data[m])
                    {
                        drawQuad(window, (m + posX) * SIZE, posY * SIZE, color);
                    }
        }

        int getPosY()
        {
            return posY;
        }
        int getPosX(){
            return posX;
        }

        bool getEl(int x){
            return data[x];
        }
};

class Player
{
    private:
        int data[4][3], posX, posY, color;

        void fillData()
        {
            for(int i=0;i < 4;i++)
                for(int m=0;m < 3;m++)
                    data[i][m] = SHAPE[i][m];
        }

    public:
        Player()
        {
            posX = 1;
            posY = 14;
            fillData();
        }

        void move(int x)
        {
            if(isValid(x))
            {
                posX += x;
            }

        }

        bool isValid(int xOffset = 0)
        {
            for(int y=0;y < 4;y++)
                for(int x=0;x < 3;x++)
                    if((data[y][x] && (posX + x + xOffset >= WIDTH || posX + xOffset <= 0)) )
                    {
                        return false;
                    }

            return true;
        }

        void draw(sf::RenderWindow & window)
        {
            for(int i=0;i < 4;i++)
                for(int m=0;m < 3;m++)
                    if(data[i][m])
                    {
                        drawQuad(window, (m + posX) * SIZE, (i + posY) * SIZE, sf::Color::Cyan);
                    }
        }
        int getPosX(){
            return posX;
        }
        int getPosY(){
            return posY;
        }


};

int GameTc(sf::RenderWindow & window, int hs)
{
    srand(time(0));
    window.setFramerateLimit(30);
    Player player=Player();
    int score=0;
    Clock moveClock;
    bool gameOver = false;
    Wall wall;
    Font font;
    font.loadFromFile("game_over.ttf");
    Text text1("Score: " , font, 10);
    text1.setPosition(310,90);
    text1.setColor(sf::Color::Green);
    sf::RectangleShape rectangle(sf::Vector2f(5, 540));
    rectangle.setFillColor(sf::Color::White);
    sf::RectangleShape rectangle1(sf::Vector2f(5, 540));
    rectangle1.setFillColor(sf::Color::White);
    rectangle.setPosition(sf::Vector2f(301, 1));
    rectangle1.setPosition(sf::Vector2f(24, 1));
    Text text("Score: ", font, 20);
    text.setPosition(20,90);
    text.setColor(sf::Color::Green);
    wall=Wall();
    int h=hs;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                return h;
                }
            if(event.type == sf::Event::Closed){
                window.close();
                return h;
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right&&!gameOver)
            {
                player.move(3);
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left&&!gameOver)
            {
                player.move(-3);
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
                gameOver = false;
        }
        window.clear();
        if(!gameOver){
                if(score<20){
			if(moveClock.getElapsedTime().asSeconds() >= .035){
				wall.move(1);
				moveClock.restart();
			}}
			else if(score<40){
            if(moveClock.getElapsedTime().asSeconds() >= .033){
				wall.move(1);
				moveClock.restart();
			}
			} else if(moveClock.getElapsedTime().asSeconds() >= .03){
				wall.move(1);
				moveClock.restart();
			}
            for(int i=0;i<9;i++){
                if(wall.getEl(i)&&(player.getPosY()+1==wall.getPosY())){
                    if(wall.getPosX()+i==player.getPosX()){
                            if(score>h){
                                h=score;
                            }
                        text.setString("Score " + intToStr(score) + "\n" + "Press enter to restart\n ESC to exit the game");
                        score=0;
                        gameOver=true;
                    }
                }
            }
             player.draw(window);
             wall.draw(window);
             window.draw(rectangle);
            window.draw(rectangle1);
            text1.setString("Score " + intToStr(score)+"\n\nHighscore:\n"+intToStr(h));
            window.draw(text1);
		}
        if(wall.getPosY()==HEIGHT){
            score++;
            wall=Wall();
        }
        if(gameOver)
        {
            text.setCharacterSize(20);
            window.draw(text);
            window.display();
            continue;
        }
        window.display();
    }
    return h;
}
