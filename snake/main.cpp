#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace sf;


int generate_x() {
    int x = rand() % (750 - 50 + 1) + 50;
    while (x % 25 != 0) {
        x = rand() % (750 - 50 + 1) + 50;
    }
    std::cout << "x : " << x << "\n";
    return x;
}

int generate_y() {
    int y = rand() % (550 - 50 + 1) + 50;
    while (y % 25 != 0) {
        y = rand() % (550 - 50 + 1) + 50;
    }
    std::cout << "y : " << y << "\n";
    return y;
}

void generate_tail();
void display(RenderWindow window, RectangleShape line_top, RectangleShape line_bot, RectangleShape line_left, RectangleShape line_right, RectangleShape head, RectangleShape apple);

int main() {
    std::cout << "Fait par Aurele le goat\n";
    RenderWindow window(VideoMode(800, 600), "Shnake");
    int score = 1;
    const int MAX_TOP = 24;
    const int MAX_BOT = 576;
    const int MAX_RIGHT = 776;
    const int MAX_LEFT = 24;

    // Ajout ressources
    SoundBuffer theme;
    if (!theme.loadFromFile("assets/song.wav")) {
        std::cout << "Erreur : Impossible de charger le fichier audio." << std::endl;
        return -1;
    }
    SoundBuffer money;
    if (!money.loadFromFile("assets/money.wav")) {
        std::cout << "Erreur : Impossible de charger le fichier audio." << std::endl;
        return -1;
    }
    SoundBuffer end;
    if (!end.loadFromFile("assets/gameover.wav")) {
        std::cout << "Erreur : Impossible de charger le fichier audio." << std::endl;
        return -1;
    }
    
    Sound sound;
    sound.setBuffer(money);

    Sound sound1;
    sound1.setBuffer(theme);
    sound1.play();

    Sound sound2;
    sound2.setBuffer(end);

    // Création bordure
    RectangleShape line_top(Vector2f(800, 25));
    RectangleShape line_bot(Vector2f(800, 25));
    line_bot.move(0, 575);
    RectangleShape line_left(Vector2f(25, 600));
    RectangleShape line_right(Vector2f(25, 600));
    line_right.move(775, 0);
    line_top.setFillColor(Color::Red);
    line_bot.setFillColor(Color::Red);
    line_left.setFillColor(Color::Red);
    line_right.setFillColor(Color::Red);

    // Création objets
    RectangleShape head(Vector2f(25, 25));
    head.setPosition(400 - 25, 300 - 25);
    int head_direction[2];
    RectangleShape apple(Vector2f(25, 25));
    apple.setPosition(generate_x(), generate_y());

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
                            head_direction[0] = 0;
                            head_direction[1] = -1;
                            window.clear();
                            window.draw(head);
                            window.draw(apple);
                            window.draw(line_top);
                            window.draw(line_bot);
                            window.draw(line_left);
                            window.draw(line_right);
                            window.display();
                            sleep(milliseconds(100));
                        }
                        if (head.getPosition().y <= MAX_TOP) {
                            std::cout << "Perdu !\n";
                            sound1.stop();
                            sound2.play();
                            while (sound2.getStatus() == Sound::Playing) {
                                sleep(milliseconds(100));
                            }
                            return 0;
                        }
                        else if (head.getPosition().x == apple.getPosition().x) {
                            if (head.getPosition().y == apple.getPosition().y) {
                                apple.setPosition(generate_x(), generate_y());
                                sound.play();
                                score++;
                                std::cout << "Votre score est de : " << score << "\n";
                            }
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
                            head_direction[0] = 0;
                            head_direction[1] = 1;
                            window.clear();
                            window.draw(head);
                            window.draw(apple);
                            window.draw(line_top);
                            window.draw(line_bot);
                            window.draw(line_left);
                            window.draw(line_right);
                            window.display();

                            sleep(milliseconds(100));
                        }
                        if (head.getPosition().y > MAX_BOT) {
                            std::cout << "Perdu !\n";
                            sound1.stop();
                            sound2.play();
                            while (sound2.getStatus() == Sound::Playing) {
                                sleep(milliseconds(100));
                            }
                            return 0;
                        }
                        else if (head.getPosition().x == apple.getPosition().x) {
                            if (head.getPosition().y == apple.getPosition().y) {
                                apple.setPosition(generate_x(), generate_y());
                                sound.play();
                                score++;
                                std::cout << "Votre score est de : " << score << "\n";
                            }
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
                            head_direction[0] = 1;
                            head_direction[1] = 0;
                            window.clear();
                            window.draw(head);
                            window.draw(apple);
                            window.draw(line_top);
                            window.draw(line_bot);
                            window.draw(line_left);
                            window.draw(line_right);
                            window.display();

                            sleep(milliseconds(100));
                        }
                        if (head.getPosition().x > MAX_RIGHT) {
                            std::cout << "Perdu !\n";
                            sound1.stop();
                            sound2.play();
                            while (sound2.getStatus() == Sound::Playing) {
                                sleep(milliseconds(100));
                            }
                            return 0;
                        }
                        else if (head.getPosition().x == apple.getPosition().x) {
                            if (head.getPosition().y == apple.getPosition().y) {
                                apple.setPosition(generate_x(), generate_y());
                                sound.play();
                                score++;
                                std::cout << "Votre score est de : " << score << "\n";
                            }
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
                            head_direction[0] = -1;
                            head_direction[1] = 0;
                            window.clear();
                            window.draw(head);
                            window.draw(apple);
                            window.draw(line_top);
                            window.draw(line_bot);
                            window.draw(line_left);
                            window.draw(line_right);
                            window.display();
                            sleep(milliseconds(100));
                        }
                        if (head.getPosition().x < MAX_LEFT) {
                            std::cout << "Perdu !\n";
                            sound1.stop();
                            sound2.play();
                            while (sound2.getStatus() == Sound::Playing) {
                                sleep(milliseconds(100));
                            }
                            return 0;
                        }
                        else if (head.getPosition().x == apple.getPosition().x) {
                            if (head.getPosition().y == apple.getPosition().y) {
                                apple.setPosition(generate_x(), generate_y());
                                sound.play();
                                score++;
                                std::cout << "Votre score est de : " << score << "\n";
                            }
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down)) {
                            exit = true;
                        }
                    }
                }
            }
        }
        display(window, line_top, line_bot, line_left, line_right, head, apple);
    }

    return 0;
}

void generate_tail() {
    std::cout << "zeub\n";
}

void display(RenderWindow window, RectangleShape line_top, RectangleShape line_bot, RectangleShape line_left, RectangleShape line_right, RectangleShape head, RectangleShape apple) {
    window.clear();
    window.draw(line_top);
    window.draw(line_bot);
    window.draw(line_left);
    window.draw(line_right);
    window.draw(apple);
    window.draw(head);
    window.display();
}