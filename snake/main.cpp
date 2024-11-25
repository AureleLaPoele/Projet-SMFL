#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;


// FAIS LA BORDURE ROUGE DE LA GAME ET QUE LES GENS MEURENT SI IL LA TOUCHE
// FAIRE UNE FONCTION VOID POUR L'AFFICHAGE



int main() {
    std::cout << "Fait par Aurele le goat\n";
    RenderWindow window(VideoMode(800, 600), "Gestion des Entrées");
    int score = 0;
    const int MAX_TOP = 25;
    const int MAX_BOT = 550;
    const int MAX_RIGHT = 750;
    const int MAX_LEFT = 25;
    // Création bordure
    RectangleShape line_top(Vector2f(800, 13));
    RectangleShape line_bot(Vector2f(800, 13));
    line_bot.move(0, 588);
    RectangleShape line_left(Vector2f(13, 600));
    RectangleShape line_right(Vector2f(13, 600));
    line_right.move(788, 0);
    line_top.setFillColor(Color::Red);
    line_bot.setFillColor(Color::Red);
    line_left.setFillColor(Color::Red);
    line_right.setFillColor(Color::Red);
    // Création objets
    RectangleShape head(Vector2f(25, 25));
    head.setPosition(400 - 25 / 2, 300 - 25 / 2);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::A)
                    std::cout << "La touche A a été pressée!" << std::endl;
                if (event.key.code == Keyboard::Escape)
                    window.close(); // Fermer avec Échap
                if (event.key.code == Keyboard::Up) {
                    bool exit = false;
                    while (exit != true) {
                        if (head.getPosition().y > MAX_TOP) {
                            head.move(0, -25);
                            window.clear();
                            window.draw(head);
                            window.draw(line_top);
                            window.draw(line_bot);
                            window.draw(line_left);
                            window.draw(line_right);
                            window.display();
                            sleep(milliseconds(100));
                        }
                        if (head.getPosition().y < MAX_TOP) {
                            std::cout << "Perdu !\n";
                            return 0;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right)) {
                            exit = true;
                        }
                    }
                }
                if (event.key.code == Keyboard::Down) {
                    bool exit = false;
                    while (exit != true) {
                        if (head.getPosition().y < MAX_BOT) {
                            head.move(0, 25);
                            window.clear();
                            window.draw(head);
                            window.draw(line_top);
                            window.draw(line_bot);
                            window.draw(line_left);
                            window.draw(line_right);
                            window.display();
                            sleep(milliseconds(100));
                        }
                        if (head.getPosition().y > MAX_BOT) {
                            std::cout << "Perdu !\n";
                            return 0;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right)) {
                            exit = true;
                        }
                    }
                }
                if (event.key.code == Keyboard::Right) {
                    bool exit = false;
                    while (exit != true) {
                        if (head.getPosition().x < MAX_RIGHT) {
                            head.move(25, 0);
                            window.clear();
                            window.draw(head);
                            window.draw(line_top);
                            window.draw(line_bot);
                            window.draw(line_left);
                            window.draw(line_right);
                            window.display();
                            sleep(milliseconds(100));
                        }
                        if (head.getPosition().x > MAX_RIGHT) {
                            std::cout << "Perdu !\n";
                            return 0;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down)) {
                            exit = true;
                        }
                    }
                }
                if (event.key.code == Keyboard::Left) {
                    bool exit = false;
                    while (exit != true) {
                        if (head.getPosition().x > MAX_LEFT) {
                            head.move(-25, 0);
                            window.clear();
                            window.draw(head);
                            window.draw(line_top);
                            window.draw(line_bot);
                            window.draw(line_left);
                            window.draw(line_right);
                            window.display();
                            sleep(milliseconds(100));
                        }
                        if (head.getPosition().x < MAX_LEFT) {
                            std::cout << "Perdu !\n";
                            return 0;
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down)) {
                            exit = true;
                        }
                    }
                }
            }
        }
        window.clear();
        window.draw(line_top);
        window.draw(line_bot);
        window.draw(line_left);
        window.draw(line_right);
        window.draw(head);
        window.display();

    }
    return 0;
}