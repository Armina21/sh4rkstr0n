#include <cassert>
#include <time.h>
#include "sfmlJeu.h"
#include <stdlib.h>
#include "sfmlMenu.h"

using namespace sf;

#include <iostream>
using namespace std;
int numpage = 0;

/*
                        Sélecteur de pages
        numpage                 |           Page affichée

            0                   |           Menu Principal
            1                   |             MenuJouer
            -1                  |              Quitter
            2                   |             A propos

            10                  |          Solo + Bordures
            11                  |         Solo + Sans Bordures

            20                  |       Multijoueur + Bordures
            21                  |      Multijoueur + Sans Bordures

*/

const int TAILLE_SPRITE = 20;

// Fonctions privées
void sfmlJeu::initVariables()
{
    this->m_window = nullptr;
    this->endOfGame = false;
}

void sfmlJeu::initWindow()
{
    int dimx = jeu.getConstTerrain().getDimX() * TAILLE_SPRITE;
    int dimy = jeu.getConstTerrain().getDimY() * TAILLE_SPRITE;
    m_window = new RenderWindow(VideoMode(dimx, dimy), "Tron", sf::Style::Titlebar | sf::Style::Close);
    m_window->setFramerateLimit(60);
    m_window->setPosition(sf::Vector2i(dimx / 4, dimy / 4));
    // m_window->setIcon(65,85,sf::Uint8()); icon?
}

void sfmlJeu::sfmlInit()
{
    if (!tx_map.loadFromFile("data/img/background.jpg"))
    {
        cout << "Error data/img/background.jpg not found" << endl;
    }
    else
        tx_map.setSmooth(true);
    if (!tx_Joueur1.loadFromFile("data/img/shark1.png"))
    {
        cout << "Error data/img/shark1.png not found (J1)" << endl;
    }
    else
    {
        sp_Joueur1.setTexture(tx_Joueur1);
        sp_Joueur1.setOrigin(tx_Joueur1.getSize().x / 2.f, tx_Joueur1.getSize().y / 2.f);
        float tailleJoueur1 = tx_Joueur1.getSize().x;
        Vector2f scaleJoueur1(TAILLE_SPRITE * 2 / tailleJoueur1, TAILLE_SPRITE * 2 / tailleJoueur1);
        sp_Joueur1.setScale(scaleJoueur1);
    }

    if (!tx_Joueur2.loadFromFile("data/img/shark2.png"))
    {
        cout << "Error data/img/shark2.png not found (J2)" << endl;
    }
    else
    {
        sp_Joueur2.setTexture(tx_Joueur2);
        sp_Joueur2.setOrigin(tx_Joueur2.getSize().x / 2.f, tx_Joueur2.getSize().y / 2.f);
        float tailleJoueur2 = tx_Joueur2.getSize().x;
        Vector2f scaleJoueur2(TAILLE_SPRITE * 2 / tailleJoueur2, TAILLE_SPRITE * 2 / tailleJoueur2);
        sp_Joueur2.setScale(scaleJoueur2);
    }

    if (!tx_invincible.loadFromFile("data/img/effets/invincible.png"))
    {
        cout << "Error data/img/effets/invincible.png" << endl;
    }
    else
    {
        sp_invincible.setTexture(tx_invincible);
        float tailleInvincible = tx_invincible.getSize().x;
        Vector2f scaleInvincible(TAILLE_SPRITE / tailleInvincible, TAILLE_SPRITE / tailleInvincible);
        sp_invincible.setScale(scaleInvincible);
    }

    if (!tx_ralenti.loadFromFile("data/img/effets/ralenti.png"))
    {
        cout << "Error data/img/effets/ralenti.png" << endl;
    }
    else
    {
        sp_ralenti.setTexture(tx_ralenti);
        float tailleRalenti = tx_ralenti.getSize().x;
        Vector2f scaleRalenti(TAILLE_SPRITE / tailleRalenti, TAILLE_SPRITE / tailleRalenti);
        sp_ralenti.setScale(scaleRalenti);
    }

    if (!tx_stop.loadFromFile("data/img/effets/stop.png"))
    {
        cout << "Error data/img/effets/stop.png" << endl;
    }
    else
    {
        sp_stop.setTexture(tx_stop);
        float tailleStop = tx_stop.getSize().x;
        Vector2f scaleStop(TAILLE_SPRITE / tailleStop, TAILLE_SPRITE / tailleStop);
        sp_stop.setScale(scaleStop);
    }

    if (!tx_upanddown.loadFromFile("data/img/upanddown.png"))
    {
        cout << "Error data/img/effets/upanddown.png" << endl;
    }
    else
    {
        sp_upanddown.setTexture(tx_upanddown);
        sp_upanddown.setPosition(1100, 600);
    }
    if (!tx_arrows.loadFromFile("data/img/arrows.png"))
    {
        cout << "Error data/img/effets/arrows.png" << endl;
    }
    else
    {
        sp_arrows.setTexture(tx_arrows);
        sp_arrows.setPosition(1100, 580);
    }

    if (!m_soundbuffer.loadFromFile("data/sounds/crash.wav"))
    {
        cout << "Error data/sounds/crash.wav not found" << endl;
    }
    else
    {
        m_sound.setBuffer(m_soundbuffer);
    }

    if (!music.openFromFile("data/sounds/flowers.ogg"))
    {
        cout << "Error data/sounds/flowers.ogg not found" << endl;
    }
    else
    {
        music.setLoop(true);
        music.setVolume(40);
        music.play();
    }
    if (!m_font.loadFromFile("data/fonts/zig.ttf"))
    {
        cout << "Error data/fonts/zig.ttf not found" << endl;
    }
    else
    {
        // Titre du jeu
        m_textinit.setFont(m_font);
        m_textinit.setString("Sh4rkSTr0n");
        m_textinit.setCharacterSize(66);
        m_textinit.setFillColor(Color::Red);
        m_textinit.setPosition(Vector2f(650, 30));
        m_textinit.setOutlineThickness(2);

        // Score du joueur 1
        player1Score.setFont(m_font);
        player1Score.setFillColor(Color::Blue);
        player1Score.setCharacterSize(16);
        player1Score.setPosition(50, 50);

        // Score du joueur 2
        player2Score.setFont(m_font);
        player2Score.setFillColor(Color::Red);
        player2Score.setCharacterSize(16);
        player2Score.setPosition(50, 650);
    }
}

// Accesseurs
const bool sfmlJeu::running() const
{
    return this->m_window->isOpen();
}

const bool sfmlJeu::getEndOfGame() const
{
    return this->endOfGame;
}

sfmlJeu::sfmlJeu() : jeu()
{
    this->initVariables();
    this->initWindow();
    this->sfmlInit();
}

sfmlJeu::~sfmlJeu()
{
    if (m_window != NULL)
        delete m_window;
}

void sfmlJeu::sfmlAff()
{
    m_window->clear(Color(230, 240, 255, 255));

    const Terrain &ter = jeu.getConstTerrain();
    const Joueur &j1 = jeu.getConstJ1();
    const Joueur &j2 = jeu.getConstJ2();

    // Afficher la map
    Sprite sp_map(tx_map);
    sp_map.setTextureRect(IntRect(0, 0, ter.getDimX() * TAILLE_SPRITE, ter.getDimY() * TAILLE_SPRITE));
    m_window->draw(sp_map); // Affichage de la map

    // Afficher les trainées, la bordure et les malus
    CircleShape c(6);
    RectangleShape r(Vector2f(20,20));
    for (int x = 0; x < ter.getDimX(); ++x)
        for (int y = 0; y < ter.getDimY(); ++y)
        {
            if (ter.getXY(vec2D(x, y)) == 74) // cast "J" en entier
            {
                c.setPosition(Vector2f(x * TAILLE_SPRITE, y * TAILLE_SPRITE));
                c.setFillColor(Color::Blue);
                m_window->draw(c); // Affichage de la trainée du Joueur 1
            }
            if (ter.getXY(vec2D(x, y)) == 75) // cast "K" en entier
            {
                c.setPosition(Vector2f(x * TAILLE_SPRITE, y * TAILLE_SPRITE));
                c.setFillColor(Color::Red);
                m_window->draw(c); // Affichage de la trainée du Joueur 2
            }

            if (ter.getXY(vec2D(x, y)) == 73) // cast "I" en entier
            {
                sp_invincible.setPosition(Vector2f(x * TAILLE_SPRITE, y * TAILLE_SPRITE));
                m_window->draw(sp_invincible);
            }
            if (ter.getXY(vec2D(x, y)) == 82) // cast "R" en entier
            {
                sp_ralenti.setPosition(Vector2f(x * TAILLE_SPRITE, y * TAILLE_SPRITE));
                m_window->draw(sp_ralenti);
            }
            if (ter.getXY(vec2D(x, y)) == 83) // cast "S" en entier
            {
                sp_stop.setPosition(Vector2f(x * TAILLE_SPRITE, y * TAILLE_SPRITE));
                m_window->draw(sp_stop);
            }
            if (ter.getXY(vec2D(x, y)) == 35) // cast "#" en entier
            {
                r.setPosition(Vector2f(x * TAILLE_SPRITE, y * TAILLE_SPRITE));
                r.setFillColor(Color{153,0,76});
                m_window->draw(r);
            }
        }

    // Afficher le sprite de Joueur1
    sp_Joueur1.setPosition(Vector2f(j1.getPosX() * TAILLE_SPRITE, j1.getPosY() * TAILLE_SPRITE));
    m_window->draw(sp_Joueur1); // Affichage du sprite du Joueur 1

    // Afficher le sprite de Joueur2
    sp_Joueur2.setPosition(Vector2f(j2.getPosX() * TAILLE_SPRITE, j2.getPosY() * TAILLE_SPRITE));
    m_window->draw(sp_Joueur2); // Affichage du sprite du Joueur 1

    // Ecrire un titre par dessus
    // m_window->draw(cpt_rebours); // Pour le compte à rebours

    m_window->draw(player1Score);
    m_window->draw(player2Score);
    m_window->display(); // Affichage de la fenêtre
}

void sfmlJeu::sfmlBoucle()
{
    sf::Clock clock;
    // Joueur j1 = jeu.getJ1();
    // Joueur j2 = jeu.getJ2();
    MenuPrinc menuPrinc(1280, 720);

    if (numpage == 0)
    {
        while (running())
        {
            sf::Event event;
            while (m_window->pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    m_window->close();
                    break;
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
                {
                    menuPrinc.MoveUp();
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
                {
                    menuPrinc.MoveDown();
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
                {
                    if (menuPrinc.pressed() == 0)
                    {
                        numpage = 1;
                    }
                    if (menuPrinc.pressed() == 1)
                    {
                        numpage = 2;
                    }
                    if (menuPrinc.pressed() == 2)
                    {
                        numpage = -1;
                    }
                }
            }

            if (numpage != 0)
            {
                break;
            }
            m_window->clear();
            menuPrinc.draw(m_window);
            m_window->draw(m_textinit);
            m_window->draw(sp_upanddown);

            // Calcul FPS
            /* sf::Time elapsed1 = clock.getElapsedTime();
             std::cout << elapsed1.asSeconds() << std::endl;
             clock.restart();*/

            m_window->display();
        }
        if (numpage == -1)
        {
            m_window->close();
        }
        if (numpage == 1)
        {
            MenuJouer();
        }
        if (numpage == 2)
        {
            Apropos();
        }
    }
}

void sfmlJeu::Apropos()
{
    int volume = 40;
    Texture bg;
    bg.loadFromFile("data/img/apropos.jpg");
    Sprite sbg;
    sbg.setTexture(bg);
    Font police;
    police.loadFromFile("data/fonts/VCR_OSD_MONO_1.001.ttf");
    Text h1;
    Text h2;
    Text vol;
    h1.setFont(police);
    h1.setString("Guide du jeu :");
    h1.setCharacterSize(82);
    h1.setPosition(400, 20);
    h1.setFillColor(Color{255, 0, 0});

    vol.setFont(police);
    vol.setString("Volume : \n  " + to_string(volume));
    vol.setCharacterSize(74);
    vol.setPosition(900, 230);
    vol.setFillColor(Color{0, 255, 0});

    h2.setFont(police);
    h2.setCharacterSize(36);
    h2.setString(" Vous pouvez jouer a 2 ou meme seul si vous\n ne possedez pas d'amis !\n \n \n \n \n Vous n'aimez pas la croute ? Pas de probleme :)\n Optez pour le mode Sans Bordures !\n");
    h2.setPosition(15, 175);
    h2.setFillColor(Color{160, 60, 10});

    while (running())
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                m_window->close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                numpage = 0;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up && volume < 100)
            {
                music.setVolume(volume + 10);
                volume = volume + 10;
                vol.setString("Volume : \n  " + to_string(volume));
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down && volume > 0)
            {
                music.setVolume(volume - 10);
                volume = volume - 10;
                vol.setString("Volume : \n  " + to_string(volume));
            }
        }
        if (numpage != 2)
        {
            m_window->clear();
            sfmlBoucle();
        }
        m_window->clear();
        m_window->draw(sbg);
        m_window->draw(h1);
        m_window->draw(h2);
        m_window->draw(vol);
        m_window->draw(sp_upanddown);
        m_window->display();
    }
}

void sfmlJeu::MenuJouer()
{
    bool left = true;
    bool choixMode;
    bool choixTerr;

    MenuPickGamemode PickGM(1280, 720);
    MenuPickMap PickMap(1280, 720);

    Texture bg;
    bg.loadFromFile("data/img/Jouerbg.jpg");
    Sprite sbg(bg);

    Texture selectGM;
    selectGM.loadFromFile("data/img/selectGM.png");
    Texture selectMap;
    selectMap.loadFromFile("data/img/selectMap.png");

    RectangleShape rectangle(sf::Vector2f(290, 240));
    rectangle.setFillColor(Color::Transparent);
    rectangle.setOutlineColor(Color::Magenta);
    rectangle.setOutlineThickness(3);

    while (running())
    {
        Event event;
        while (m_window->pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                m_window->close();
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape)
                {
                    numpage = 0;
                }
                else if (event.key.code == Keyboard::Right)
                {
                    left = false;
                }
                else if (event.key.code == Keyboard::Left)
                {
                    left = true;
                }
                else if (event.key.code == Keyboard::Up)
                {
                    if (left == true)
                    {
                        PickGM.MoveUp();
                    }
                    else
                    {
                        PickMap.MoveUp();
                    }
                }
                else if (event.key.code == Keyboard::Down)
                {
                    if (left == true)
                    {
                        PickGM.MoveDown();
                    }
                    else
                    {
                        PickMap.MoveDown();
                    }
                }
                else if (event.key.code == Keyboard::Return)
                {
                    if ((PickGM.pressed() == 0) && (PickMap.pressed() == 0))
                    {
                        choixMode = false;
                        choixTerr = false;
                        numpage = 10;
                    }
                    else if ((PickGM.pressed() == 0) && (PickMap.pressed() == 1))
                    {
                        choixMode = false;
                        choixTerr = true;
                        numpage = 11;
                    }
                    else if ((PickGM.pressed() == 1) && (PickMap.pressed() == 0))
                    {
                        choixMode = true;
                        choixTerr = false;
                        numpage = 20;
                    }
                    else if ((PickGM.pressed() == 1) && (PickMap.pressed() == 1))
                    {
                        choixMode = true;
                        choixTerr = true;
                        numpage = 21;
                    }
                    InGame(choixMode, choixTerr);
                }
                break;
            default:
                break;
            }
        }

        m_window->clear();
        sfmlBoucle();
        m_window->draw(sbg);
        PickGM.draw(m_window);
        PickMap.draw(m_window);
        m_window->draw(sp_arrows);

        if (left == true)
        {
            rectangle.setPosition(350, 240);
            sbg.setTexture(selectGM);
        }
        else
        {
            rectangle.setPosition(640, 240);
            sbg.setTexture(selectMap);
        }

        m_text.setFont(m_font);
        m_text.setFillColor(sf::Color::White);
        m_text.setOutlineThickness(3);
        m_text.setOutlineColor(Color::Black);
        m_text.setString("Choix des parametres");
        m_text.setCharacterSize(50);
        m_text.setPosition(sf::Vector2f(300, 30));

        m_window->draw(rectangle);
        m_window->draw(m_text);
        m_window->display();
    }
}

void sfmlJeu::InGame(bool &choixMode, bool &choixTerr)
{
    Clock clock;
    sf::Time elapsed = sf::Time::Zero;
    jeu.multOS = 400;
    // Remise des scores à zéro
    jeu.getJ1().setScore(0);
    jeu.getJ2().setScore(0);

    // Définition de variables qui stockent la précédente valeur de score
    int prevScore1 = jeu.getConstJ1().getScore();
    int prevScore2 = jeu.getConstJ2().getScore();

    // initialisation de la premiere manche
    jeu.NouvelleManche(choixTerr);

    while (running())
    {
        Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == Event::Closed)
                m_window->close();

            if (event.key.code == Keyboard::Escape)
            {
                numpage = 0;
                sfmlBoucle();
            }

            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::Q:
                    jeu.actionClavier('q');
                    break;
                case Keyboard::D:
                    jeu.actionClavier('d');
                    break;
                case Keyboard::S:
                    jeu.actionClavier('s');
                    break;
                case Keyboard::Z:
                    jeu.actionClavier('z');
                    break;
                case Keyboard::M:
                    jeu.actionClavier('m');
                    break;
                case Keyboard::K:
                    jeu.actionClavier('k');
                    break;
                case Keyboard::O:
                    jeu.actionClavier('o');
                    break;
                case Keyboard::L:
                    jeu.actionClavier('l');
                    break;
                case Keyboard::Space:
                    break;
                default:
                    break;
                }
            }
        }

        // Gestion des collisions + bonus
        jeu.Interaction(choixTerr, jeu.getJ1(), jeu.getJ2());
        jeu.Interaction(choixTerr, jeu.getJ2(), jeu.getJ1());

        // Si le mode multi joueur à été choisis
        if (choixMode == true)
        {
            // Deux "vrais" joueurs
            elapsed += clock.restart();
            while (elapsed >= sf::seconds(0.5))
            {
                jeu.avance(choixTerr, jeu.getJ1());
                jeu.avance(choixTerr, jeu.getJ2());
                elapsed -= sf::seconds(0.1);
            }
        }
        // Si le mode solo (avec IA) à été choisis
        else
        {
            // Joueur + IA
            elapsed += clock.restart();
            while (elapsed >= sf::seconds(0.5))
            {
                jeu.avanceIA(choixTerr);
                elapsed -= sf::seconds(0.1);
            }
        }

        // Affiche le bonus sur le terrain
        jeu.AffBonus();
        jeu.afficheChronoBonus();

        // Mets à jour les scores
        player1Score.setString("Player 1 Score: " + to_string(jeu.getConstJ1().getScore()));
        player2Score.setString("Player 2 Score: " + to_string(jeu.getConstJ2().getScore()));

        // regarde si joueur 1 a gagné un point et joue un son
        if (jeu.getConstJ1().getScore() > prevScore1)
        {
            m_sound.play();
        }

        // regarde si joueur 2 a gagné un point et joue un son
        if (jeu.getConstJ2().getScore() > prevScore2)
        {
            m_sound.play();
        }

        // update des variables
        prevScore1 = jeu.getConstJ1().getScore();
        prevScore2 = jeu.getConstJ2().getScore();

        if (jeu.getConstJ1().getScore() == 5)
        {
            RenderWindow promptWindow(sf::VideoMode(600, 100), "Game Over");
            promptWindow.setPosition(Vector2i(400, 400));
            sf::Text promptText("Joueur 2 wins!\nAppuyez Echap pour revenir au menu", m_font, 20);
            promptText.setPosition(10, 10);
            while (promptWindow.isOpen())
            {
                sf::Event promptEvent;
                while (promptWindow.pollEvent(promptEvent))
                {
                    if (promptEvent.type == sf::Event::Closed)
                    {
                        promptWindow.close();
                    }
                    if (promptEvent.type == sf::Event::KeyPressed && promptEvent.key.code == sf::Keyboard::Escape)
                    {
                        promptWindow.close();
                        numpage = 0;
                        sfmlBoucle();
                    }
                }
                promptWindow.clear();
                promptWindow.draw(promptText);
                promptWindow.display();
            }
        }
        else if (jeu.getConstJ2().getScore() == 5)
        {
            RenderWindow promptWindow(sf::VideoMode(600, 100), "Game Over");
            promptWindow.setPosition(Vector2i(400, 400));
            Text promptText("Joueur 2 wins!\nAppuyez Echap pour revenir au menu", m_font, 20);
            promptText.setPosition(10, 10);
            while (promptWindow.isOpen())
            {
                sf::Event promptEvent;
                while (promptWindow.pollEvent(promptEvent))
                {
                    if (promptEvent.type == sf::Event::Closed)
                    {
                        promptWindow.close();
                    }
                    if (promptEvent.type == sf::Event::KeyPressed && promptEvent.key.code == sf::Keyboard::Escape)
                    {
                        promptWindow.close();
                        numpage = 0;
                        sfmlBoucle();
                    }
                }
                promptWindow.clear();
                promptWindow.draw(promptText);
                promptWindow.display();
            }
        }

        sfmlAff();
    }
}
