#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main() {
    std::cout << "Fait par Aurele le goat\n";
    RenderWindow window(VideoMode(800, 600), "Jeu de tir 2D");
    const int MAX_RIGHT = 750;
    const int MAX_LEFT = 25;
    const int MAX_TOP = 25;
    // Création objets
    RectangleShape head(Vector2f(25, 25));
    head.setPosition(400 - 25 / 2, 550);
    RectangleShape tir(Vector2f(1, 25));
    tir.setPosition(400, 550);

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
                if (event.key.code == Keyboard::Left) {
                    if (head.getPosition().x > MAX_LEFT) {
                        head.move(-25, 0);
                        tir.move(-25, 0);
                        window.clear();
                        window.draw(head);
                        window.display();
                        sleep(milliseconds(50));
                    }
                }
                if (event.key.code == Keyboard::Right) {
                    if (head.getPosition().x < MAX_RIGHT) {
                        head.move(25, 0);
                        tir.move(25, 0);
                        window.clear();
                        window.draw(head);
                        window.display();
                        sleep(milliseconds(50));
                    }
                }
                if (event.key.code == Keyboard::Up) {
                    bool exit = false;
                    while (exit != true) {
                        if (tir.getPosition().y > MAX_TOP) {
                            tir.move(0, -25);
                            window.clear();
                            window.draw(head);
                            window.draw(tir);
                            window.display();
                            sleep(milliseconds(50));
                        }
                        if (tir.getPosition().y <= MAX_TOP) {
                            std::cout << "test\n";
                            exit = true;
                        }
                    }
                    tir.move(head.getPosition().x-400+25/2, head.getPosition().y-25);
                }
                //if (event.key.code == Keyboard::Up) {
                //    bool exit = false;
                //    while (exit != true) {
                //        if (head.getPosition().y > MAX_TOP) {
                //            head.move(0, -25);
                //            window.clear();
                //            window.draw(head);
                //            window.display();
                //            sleep(milliseconds(100));
                //        }
                //        if (head.getPosition().y < MAX_TOP) {
                //            std::cout << "test\n";
                //            exit = true;
                //        }
                //        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right)) {
                //            exit = true;
                //        }
                //    }
                //}
            }
        }
        window.clear();
        window.draw(head);
        window.draw(tir);
        window.display();
    }
    return 0;
}