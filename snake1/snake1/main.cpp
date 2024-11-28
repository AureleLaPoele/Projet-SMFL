#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace sf;

int score = 0;
const int MAX_TOP = 25;
const int MAX_BOT = 550;
const int MAX_RIGHT = 750;
const int MAX_LEFT = 25;
const int WIDTH = 800;
const int HEIGHT = 600;

RenderWindow window(VideoMode(WIDTH, HEIGHT), "Shnaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaake");

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

void display(RectangleShape head, RectangleShape apple, std::vector<RectangleShape> tail);

class Snake {
    public:
        Vector2f size_head;
        Vector2f pos_head;
        Vector2f pos_apple;
        RectangleShape head;
        RectangleShape apple;
        Vector2f direction_head;
        std::vector<RectangleShape> tail;

        // Constructeur
        Snake(Vector2f size_head) {
            this->size_head = size_head;
            this->pos_head = Vector2f(WIDTH / 2 - this->size_head.x, HEIGHT / 2 - this->size_head.y);
            this->pos_apple = Vector2f(generate_x(), generate_y());
            this->head.setSize(Vector2f(size_head.x, size_head.y));
            this->head.setPosition(this->pos_head);
            this->apple.setSize(Vector2f(size_head.x, size_head.y));
            this->apple.setPosition(this->pos_apple);
        }

        int mov(int add_x, int add_y, int direction_x, int direction_y) {
            bool exit = false;
            while (exit != true) {
                if (head.getPosition().y > MAX_TOP && head.getPosition().y < MAX_BOT && head.getPosition().x < MAX_RIGHT && head.getPosition().x > MAX_LEFT) {
                    head.move(add_x, add_y);
                    direction_head.x = direction_x;
                    direction_head.y = direction_y;
                    generate_tail();
                    display(this->head, this->apple, this->tail);
                    sleep(milliseconds(100));
                    if (head.getPosition().y <= MAX_TOP || head.getPosition().y >= MAX_BOT || head.getPosition().x >= MAX_RIGHT || head.getPosition().x <= MAX_LEFT) {
                        std::cout << "Perdu grosse merde que t'y es\n";
                        return 0;
                    }
                    else if (head.getPosition().x == apple.getPosition().x) {
                        if (head.getPosition().y == apple.getPosition().y) {
                            apple.setPosition(generate_x(), generate_y());
                            score++;
                            std::cout << "Votre score est de : " << score << "\n";
                        }
                    }
                }
                if ((direction_x == 0 && direction_y == 1) || (direction_x == 0 && direction_y == -1)) {
                    exit = (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right));
                }
                if ((direction_x == 1 && direction_y == 0) || (direction_x == -1 && direction_y == 0)) {
                    exit = (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down));
                }
            }
            return 69;
        }

        Vector2f center() {
            int ulx = this->head.getPosition().x;
            int uly = this->head.getPosition().y;
            return Vector2f(ulx + this->size_head.x / 2, uly + this->size_head.y / 2);
        }

        void generate_tail() {
            this->tail.clear();
            for (int i = 0; i < score; i++) {
                //je fais caca dans les raviolis
                RectangleShape tail(this->size_head);
                Vector2f pos = this->center();
                Vector2f pos_center_tail = Vector2f(pos.x + (this->size_head.x * -1 * (this->direction_head.x))*(i+1), pos.y + (this->size_head.y * -1 * (this->direction_head.y))*(i+1));
                Vector2f pos_ul = Vector2f(pos_center_tail.x - this->size_head.x / 2, pos_center_tail.y - this->size_head.y / 2);
                tail.setPosition(pos_ul);
                this->tail.push_back(tail);
            }
        }
};

void display(RectangleShape head, RectangleShape apple, std::vector<RectangleShape> tail) {
    window.clear();
    window.draw(head);
    window.draw(apple);
    for (int i = 0; i < tail.size(); i++) {
        window.draw(tail[i]);
    }
    window.display();
}

int main() {
    Snake snake(Vector2f(25, 25));
    while (window.isOpen()) {
       Event event;
       while (window.pollEvent(event)) {
           if (event.type == Event::Closed)
               window.close();
           if (event.type == Event::KeyPressed) {
               if (event.key.code == Keyboard::A)
                   std::cout << "La touche A a ete pressee!" << std::endl;
               if (event.key.code == Keyboard::Escape)
                   window.close();
               if (event.key.code == Keyboard::Up) {
                   if (snake.mov(0, -25, 0, -1) == 0) {
                       return 0;
                   }
               }
               if (event.key.code == Keyboard::Down) {
                   if (snake.mov(0, 25, 0, 1) == 0) {
                       return 0;
                   }
               }
               if (event.key.code == Keyboard::Left) {
                   if (snake.mov(-25, 0, -1, 0) == 0) {
                       return 0;
                   }
               }
               if (event.key.code == Keyboard::Right) {
                   if (snake.mov(25, 0, 1, 0) == 0) {
                       return 0;
                   }
               }
           }
       }
       display(snake.head, snake.apple, snake.tail);
       sleep(milliseconds(100));
    }
}