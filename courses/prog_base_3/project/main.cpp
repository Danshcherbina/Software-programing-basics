#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "Tetris.hpp"
using namespace sf;

void menu(sf::RenderWindow & window) {
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
    hsS=10;
    hsC=11;
    font.loadFromFile("game_over.ttf");
	Texture menuBackground;
	menuBackground.loadFromFile("images/background.jpg");
	Text menu1("Start tetris " , font, 20);
	Text menu2("Start snake " , font, 20);
	Text menu3("Start tetroCar " , font, 20);
	Text menu4("High score " , font, 20);
	Text menu5("Options " , font, 20);
	Text menu6("Exit " , font, 20);
	Sprite menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(120, 80);
	menu2.setPosition(120, 120);
	menu3.setPosition(120, 160);
	menu4.setPosition(120, 200);
	menu5.setPosition(120, 240);
	menu6.setPosition(120, 280);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		menu1.setColor(Color::Magenta);
		menu2.setColor(Color::Magenta);
		menu3.setColor(Color::Magenta);
		menu4.setColor(Color::Magenta);
		menu5.setColor(Color::Magenta);
		menu6.setColor(Color::Magenta);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(120, 80, 220, 20).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(120, 120, 220, 20).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(120, 160, 220, 20).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }
        if (IntRect(120, 200, 220, 20).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Blue); menuNum = 4; }
        if (IntRect(120, 240, 220, 20).contains(Mouse::getPosition(window))) { menu5.setColor(Color::Blue); menuNum = 5; }
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
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) {hsT=GameT(window,hsT);}
			if (menuNum == 2) isMenu=false;
			if (menuNum == 3) isMenu=false;
			if (menuNum == 4) isMenu=false;
			if (menuNum == 5) isMenu=false;
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
