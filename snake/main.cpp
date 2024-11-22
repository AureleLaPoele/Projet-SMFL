#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main() {
    std::cout << "Fait par Aurele le goat";
    RenderWindow window(VideoMode(800, 600), "Gestion des Entrées");
    const int MAX_TOP = 25;
    const int MAX_BOT = 550;
    const int MAX_RIGHT = 750;
    const int MAX_LEFT = 25;
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
                    if (head.getPosition().y > MAX_TOP) {
                        head.move(0, -25);
                    }
                }
                if (event.key.code == Keyboard::Down) {
                    if (head.getPosition().y < MAX_BOT) {
                        head.move(0, 25);
                    }
                }
                if (event.key.code == Keyboard::Right) {
                    if (head.getPosition().x < MAX_RIGHT) {
                        head.move(25, 0);
                    }
                }
                if (event.key.code == Keyboard::Left) {
                    if (head.getPosition().x > MAX_LEFT) {
                        head.move(-25, 0);
                    }
                }
            }
        }
        window.clear();
        window.draw(head);
        window.display();
    }
    return 0;
}