#include "sfmlMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

MenuPrinc::MenuPrinc(float width, float height)
{
    if (!police.loadFromFile("data/fonts/VCR_OSD_MONO_1.001.ttf"))
    {
        cout << "Error data/fonts/VCR_OSD_MONO_1.001.ttf not found" << endl;
    }
    else
    {
        mainTx.loadFromFile("data/img/mainmenu.jpg");
        mainSp.setTexture(mainTx);
        optionsMenuPrinc[0].setFont(police);
        optionsMenuPrinc[0].setFillColor(sf::Color{230, 60, 0});
        optionsMenuPrinc[0].setString("Jouer");
        optionsMenuPrinc[0].setCharacterSize(76);
        optionsMenuPrinc[0].setPosition(sf::Vector2f(width / 1.7, height / 5));

        optionsMenuPrinc[1].setFont(police);
        optionsMenuPrinc[1].setFillColor(sf::Color::White);
        optionsMenuPrinc[1].setString("A propos");
        optionsMenuPrinc[1].setCharacterSize(76);
        optionsMenuPrinc[1].setPosition(sf::Vector2f(width / 1.7, height / 5 + 200));

        optionsMenuPrinc[2].setFont(police);
        optionsMenuPrinc[2].setFillColor(sf::Color::White);
        optionsMenuPrinc[2].setString("Quitter");
        optionsMenuPrinc[2].setCharacterSize(76);
        optionsMenuPrinc[2].setPosition(sf::Vector2f(width / 1.7, height / 5 + 400));
    }
    chosen = 0;
}

MenuPrinc::~MenuPrinc() {}

void MenuPrinc::setChosen(int n)
{
    chosen = n;
}

void MenuPrinc::draw(sf::RenderWindow *window)
{
    window->draw(mainSp);
    for (int i = 0; i < 3; i++)
    {
        window->draw(optionsMenuPrinc[i]);
    }
}

void MenuPrinc::MoveDown()
{
    if (chosen + 1 <= 3)
    {
        optionsMenuPrinc[chosen].setFillColor(sf::Color::White);
        chosen++;
        if (chosen == 3)
        {
            chosen = 0;
        }
        optionsMenuPrinc[chosen].setFillColor(sf::Color{230, 60, 0});
    }
}

void MenuPrinc::MoveUp()
{
    if (chosen - 1 >= -1)
    {
        optionsMenuPrinc[chosen].setFillColor(sf::Color::White);
        chosen--;
        if (chosen == -1)
        {
            chosen = 2;
        }
        optionsMenuPrinc[chosen].setFillColor(sf::Color{230, 60, 0});
    }
}

MenuPickGamemode::MenuPickGamemode(float width, float height)
{
    if (!police.loadFromFile("data/fonts/VCR_OSD_MONO_1.001.ttf"))
    {
        cout << "Error data/fonts/VCR_OSD_MONO_1.001.ttf not found" << endl;
    }

    optionsMenuPickGamemode[0].setFont(police);
    optionsMenuPickGamemode[0].setFillColor(sf::Color{230, 60, 0});
    optionsMenuPickGamemode[0].setString("Solo");
    optionsMenuPickGamemode[0].setCharacterSize(36);
    optionsMenuPickGamemode[0].setPosition(sf::Vector2f(width / 3.3 + 72, height / 2 - 40));

    optionsMenuPickGamemode[1].setFont(police);
    optionsMenuPickGamemode[1].setFillColor(sf::Color::White);
    optionsMenuPickGamemode[1].setString("MultiJoueur");
    optionsMenuPickGamemode[1].setCharacterSize(36);
    optionsMenuPickGamemode[1].setPosition(sf::Vector2f(width / 3.3, height / 2));

    chosen = 0;
}

MenuPickGamemode::~MenuPickGamemode() {}

void MenuPickGamemode::setChosen(int n)
{
    chosen = n;
}

void MenuPickGamemode::draw(sf::RenderWindow *window)
{
    for (int i = 0; i < 2; i++)
    {
        window->draw(optionsMenuPickGamemode[i]);
    }
}

void MenuPickGamemode::MoveDown()
{
    if (chosen + 1 <= 2)
    {
        optionsMenuPickGamemode[chosen].setFillColor(sf::Color::White);
        chosen++;
        if (chosen == 2)
        {
            chosen = 0;
        }
        optionsMenuPickGamemode[chosen].setFillColor(sf::Color{230, 60, 0});
    }
}

void MenuPickGamemode::MoveUp()
{
    if (chosen - 1 >= -1)
    {
        optionsMenuPickGamemode[chosen].setFillColor(sf::Color::White);
        chosen--;
        if (chosen == -1)
        {
            chosen = 1;
        }
        optionsMenuPickGamemode[chosen].setFillColor(sf::Color{230, 60, 0});
    }
}

MenuPickMap::MenuPickMap(float width, float height)
{
    if (!police.loadFromFile("data/fonts/VCR_OSD_MONO_1.001.ttf"))
    {
        cout << "Error data/fonts/VCR_OSD_MONO_1.001.ttf not found" << endl;
    }

    optionsMenuPickMap[0].setFont(police);
    optionsMenuPickMap[0].setFillColor(sf::Color{230, 60, 0});
    optionsMenuPickMap[0].setString("Sans Bordures");
    optionsMenuPickMap[0].setCharacterSize(36);
    optionsMenuPickMap[0].setPosition(sf::Vector2f(width / 1.97, height / 2 - 40));

    optionsMenuPickMap[1].setFont(police);
    optionsMenuPickMap[1].setFillColor(sf::Color::White);
    optionsMenuPickMap[1].setString("Bordures");
    optionsMenuPickMap[1].setCharacterSize(36);
    optionsMenuPickMap[1].setPosition(sf::Vector2f(width / 1.95 + 36, height / 2));

    chosen = 0;
}

MenuPickMap::~MenuPickMap() {}

void MenuPickMap::setChosen(int n)
{
    chosen = n;
}

void MenuPickMap::draw(sf::RenderWindow *window)
{
    for (int i = 0; i < 2; i++)
    {
        window->draw(optionsMenuPickMap[i]);
    }
}

void MenuPickMap::MoveDown()
{
    if (chosen + 1 <= 2)
    {
        optionsMenuPickMap[chosen].setFillColor(sf::Color::White);
        chosen++;
        if (chosen == 2)
        {
            chosen = 0;
        }
        optionsMenuPickMap[chosen].setFillColor(sf::Color{230, 60, 0});
    }
}

void MenuPickMap::MoveUp()
{
    if (chosen - 1 >= -1)
    {
        optionsMenuPickMap[chosen].setFillColor(sf::Color::White);
        chosen--;
        if (chosen == -1)
        {
            chosen = 1;
        }
        optionsMenuPickMap[chosen].setFillColor(sf::Color{230, 60, 0});
    }
}