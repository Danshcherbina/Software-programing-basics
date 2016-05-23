#include <SFML/Graphics.hpp>
using namespace sf;

void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	menuTexture4.loadFromFile("images/444.png");
	menuBackground.loadFromFile("images/background.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menu4(menuTexture4), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(570, 130);
	menu2.setPosition(570, 190);
	menu3.setPosition(570, 250);
	menu4.setPosition(560, 300);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menu4.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(570, 130, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(570, 190, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(570, 250, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }
        if (IntRect(560, 300, 300, 50).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Blue); menuNum = 4; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню
			if (menuNum == 2) isMenu=false;
			if (menuNum == 3) isMenu=false;
			if (menuNum == 4)  { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);
		window.display();
	}
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1376, 768), "Course");
	menu(window);
    return 0;
}
