#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main() {
    std::cout << "Fait par Aurele le goat";
    RenderWindow window(VideoMode(800, 600), "Gestion des Entr�es");

    // Cr�ation objets
    RectangleShape square(Vector2f(25, 25));
    square.setPosition(400 - 25 / 2, 0);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::A)
                    std::cout << "La touche A a �t� press�e!" << std::endl;
                if (event.key.code == Keyboard::Escape)
                    window.close(); // Fermer avec �chap
                if (event.key.code == Keyboard::D)
                    square.move(25, 0);
                if (event.key.code == Keyboard::Q)
                    square.move(-25, 0);

            }
        }
        if (square.getPosition().y != 550) {
            square.move(0, 25);
            sleep(milliseconds(250));
        }
        window.clear();
        window.draw(square);
        window.display();
    }
    return 0;
}