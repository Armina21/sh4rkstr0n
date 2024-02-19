#ifndef _SFMLJEU_H
#define _SFMLJEU_H

#include "Jeu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

/**
    La classe g�rant le jeu avec un affichage SFML
*/

class sfmlJeu
{

private:
    Jeu jeu;
    sf::RenderWindow *m_window;

    // Textures
    sf::Texture tx_Joueur1;
    sf::Texture tx_Joueur2;
    sf::Texture tx_map;
    sf::Texture tx_invincible;
    sf::Texture tx_ralenti;
    sf::Texture tx_stop;
    sf::Texture tx_upanddown;
    sf::Texture tx_arrows;

    // Sprites
    sf::Sprite sp_Joueur1;
    sf::Sprite sp_Joueur2;
    sf::Sprite sp_invincible;
    sf::Sprite sp_ralenti;
    sf::Sprite sp_stop;
    sf::Sprite sp_upanddown;
    sf::Sprite sp_arrows;

    // Police et texte
    sf::Font m_font;
    sf::Text m_textinit;
    sf::Text m_text;
    sf::Text player1Score;
    sf::Text player2Score;

    // Effets sonores
    sf::SoundBuffer m_soundbuffer;
    sf::Sound m_sound;

    // Musique
    sf::Music music;

    // Elements logiques
    bool endOfGame;


    // Fonctions
    void initVariables();
	void initWindow();
	void sfmlInit();

public:
    // Constructeurs / Destructeurs
    sfmlJeu();
    ~sfmlJeu();

    // Accesseurs
    const bool running() const;
    const bool getEndOfGame() const;

    // Fonctions
    void sfmlBoucle();
    void sfmlAff();
    void Apropos();
    void MenuJouer();

    void InGame(bool &choixMode, bool &choixTerr);
};

#endif
