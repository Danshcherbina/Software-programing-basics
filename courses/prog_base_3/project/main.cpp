#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "Tetris.hpp"
#include "Snake.hpp"
#include "TetroCar.hpp"
using namespace sf;

void hshow(sf::RenderWindow & window, int tetris, int snake, int tCar){
    Texture hsBackground;
	hsBackground.loadFromFile("images/background.jpg");
	Sprite hSBg(hsBackground);
    Font font;
    font.loadFromFile("game_over.ttf");
    Text hs1("Tetris: "+intToStr(tetris) , font, 20);
    Text hs2("Snake: "+intToStr(snake) , font, 20);
    Text hs3("Tetro car: "+intToStr(tCar) , font, 20);
    Text backB("Back ", font, 20);
    hs1.setPosition(120, 80);
	hs2.setPosition(120, 120);
	hs3.setPosition(120, 160);
	backB.setPosition(120, 200);
	hSBg.setPosition(0, 0);
	bool isHs=1;
	int btNum=0;
    while(isHs){
        hs1.setColor(Color::Magenta);
		hs2.setColor(Color::Magenta);
		hs3.setColor(Color::Magenta);
		if(btNum!=1)
		backB.setColor(Color::Magenta);
		window.clear(Color(129, 181, 221));
		if (IntRect(120, 200, 100, 20).contains(Mouse::getPosition(window))) { backB.setColor(Color::Blue); btNum = 1; }
		sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
                return;
        }
            if(event.type == sf::Event::KeyPressed&&(event.key.code==sf::Keyboard::Down||event.key.code==sf::Keyboard::Up)){
                backB.setColor(Color::Blue);
                btNum=1;
            }
            if (Mouse::isButtonPressed(Mouse::Left)||(event.type == sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Return))
		{
		    if (btNum == 1) return;
		    continue;
		}
            continue;
        }
        window.draw(hSBg);
		window.draw(hs1);
		window.draw(hs2);
		window.draw(hs3);
		window.draw(backB);
		window.display();
    }
}

void menu(sf::RenderWindow & window) {
    Music music;//создаем объект музыки
    music.openFromFile("bg_music.wav");//загружаем файл
    music.play();//воспроизводим музыку
    music.setLoop(true);
    char *fname = "high_score.txt";
    FILE * fp;
    fp=fopen(fname,"r");
    Font font;
    int hsT=0;
    int hsS=0;
    int hsC=0;
    fscanf(fp,"%i", &hsT);
    fscanf(fp,"%i", &hsS);
    fscanf(fp,"%i", &hsC);
    font.loadFromFile("game_over.ttf");
	Texture menuBackground;
	menuBackground.loadFromFile("images/background.jpg");
	Text menu1("Start tetris " , font, 20);
	Text menu2("Start snake " , font, 20);
	Text menu3("Start tetroCar " , font, 20);
	Text menu4("High score " , font, 20);
	Text menu5("Music " , font, 20);
	Text menu6("Exit " , font, 20);
	Sprite menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 1;
	int stat=1;
	menu1.setPosition(120, 80);
	menu2.setPosition(120, 120);
	menu3.setPosition(120, 160);
	menu4.setPosition(120, 200);
	menu5.setPosition(120, 240);
	menu6.setPosition(120, 280);
	menuBg.setPosition(0, 0);
    menu5.setColor(Color::Magenta);
	while (isMenu)
	{
	    if(menuNum!=1)
		menu1.setColor(Color::Magenta);
		else menu1.setColor(Color::Blue);
		if(menuNum!=2)
		menu2.setColor(Color::Magenta);
		else menu2.setColor(Color::Blue);
		if(menuNum!=3)
		menu3.setColor(Color::Magenta);
		else menu3.setColor(Color::Blue);
		if(menuNum!=4)
		menu4.setColor(Color::Magenta);
		else menu4.setColor(Color::Blue);
		if(menuNum!=6)
		menu6.setColor(Color::Magenta);
		else menu6.setColor(Color::Blue);
		window.clear(Color(129, 181, 221));

		if (IntRect(120, 80, 220, 20).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(120, 120, 220, 20).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(120, 160, 220, 20).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }
        if (IntRect(120, 200, 220, 20).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Blue); menuNum = 4; }
        if (IntRect(120, 240, 220, 20).contains(Mouse::getPosition(window))) {  menuNum = 5; }
        if (IntRect(120, 280, 200, 20).contains(Mouse::getPosition(window))) { menu6.setColor(Color::Blue); menuNum = 6; }
         sf::Event event;
        while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed){
                freopen(fname, "w",fp);
                fprintf(fp,"%i\n", hsT);
                fprintf(fp,"%i\n", hsS);
                fprintf(fp,"%i\n", hsC);
                fclose(fp);
                window.close();
                return;
        }
        if(event.type == sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Up){
                if(menuNum==1)
                menuNum=6;
                else menuNum--;
            }
        if(event.type == sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Down){
                if(menuNum==6)
                menuNum=1;
                else menuNum++;
            }
		if (Mouse::isButtonPressed(Mouse::Left)||(event.type == sf::Event::KeyPressed&&event.key.code==sf::Keyboard::Return))
		{
			if (menuNum == 1) {hsT=GameT(window,hsT);}
			if (menuNum == 2) {hsS=snake(window,hsS);};
			if (menuNum == 3) {hsC=GameTc(window, hsC);}
			if (menuNum == 4) hshow(window, hsT, hsS, hsC);
			if (menuNum == 5) {if(stat==1){
                menu5.setColor(Color::Blue);
                music.pause();
                stat=0;
			}else {
			    menu5.setColor(Color::Magenta);
			    music.play();
			    stat=1;
			}
			}
			if (menuNum == 6)  {
                window.close();
                isMenu = false;
                freopen(fname, "w",fp);
                fprintf(fp,"%i\n", hsT);
                fprintf(fp,"%i\n", hsS);
                fprintf(fp,"%i\n", hsC);
                fclose(fp);
            }
            continue;

		}
		continue;
        }
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);
		window.draw(menu5);
		window.draw(menu6);
		window.display();
	}
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(420, 540), "Course");
	menu(window);
    return 0;
}
