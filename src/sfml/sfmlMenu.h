#ifndef _SFMLMenu_H
#define _SFMLMenu_H

#include <SFML/Graphics.hpp>

class MenuPrinc
{
public:
    sf::Text optionsMenuPrinc[3];         // différentes options du menu
    MenuPrinc(float width, float height); //"fenêtre" contenant le menu
    ~MenuPrinc();                         // destructeur

    void draw(sf::RenderWindow *window); // dessiner la fenêtre menu
    void MoveUp();                       // Permet de naviguer vers le haut
    void MoveDown();                     // Permet de naviguer vers le bas
    void setChosen(int n);               // Définit chosen sur la valeur en paramètre
    int pressed()                        // Récupère la touche pressée
    {
        return chosen;
    }

private:
    int chosen;         // Valeur selectionnée
    sf::Font police;    // Police d'écriture
    sf::Texture mainTx; // Texture main
    sf::Sprite mainSp;  // Sprite main
};

class MenuPickGamemode
{
public:
    sf::Text optionsMenuPickGamemode[2];
    MenuPickGamemode(float width, float height);
    ~MenuPickGamemode();

    void draw(sf::RenderWindow *window);
    void MoveUp();
    void MoveDown();
    void setChosen(int n);
    int pressed()
    {
        return chosen;
    }

private:
    int chosen;
    sf::Font police;
};

class MenuPickMap
{
public:
    sf::Text optionsMenuPickMap[2];
    MenuPickMap(float width, float height);
    ~MenuPickMap();

    void draw(sf::RenderWindow *window);
    void MoveUp();
    void MoveDown();
    void setChosen(int n);
    int pressed()
    {
        return chosen;
    }

private:
    int chosen;
    sf::Font police;
    bool rect;
};

#endif
