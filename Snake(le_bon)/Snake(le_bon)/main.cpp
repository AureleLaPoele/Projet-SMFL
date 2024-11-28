#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace sf;



int score = 0;
const int MAX_TOP = 10;
const int MAX_BOT = 565;
const int MAX_RIGHT = 765;
const int MAX_LEFT = 10;
const int WIDTH = 800;
const int HEIGHT = 600;
const int UPPER_LEFT = 0;
const int UPPER_RIGHT = 1;
const int DOWN_LEFT = 2;
const int DOWN_RIGHT = 3;

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
    std::vector<Vector2f> direction;

    // Constructeur
    Snake(Vector2f size_head) {
        this->size_head = size_head;
        this->pos_head = Vector2f(WIDTH / 2 - this->size_head.x, HEIGHT / 2 - this->size_head.y);
        this->pos_apple = Vector2f(generate_x(), generate_y());
        this->head.setSize(Vector2f(size_head.x, size_head.y));
        this->head.setPosition(this->pos_head);
        this->apple.setSize(Vector2f(size_head.x, size_head.y));
        this->apple.setPosition(this->pos_apple);
        this->tail.push_back(head);
    }

    int mov(int add_x, int add_y, int direction_x, int direction_y) {
        bool exit = false;
        while (exit != true) {
            if (head.getPosition().y > MAX_TOP && head.getPosition().y < MAX_BOT && head.getPosition().x < MAX_RIGHT && head.getPosition().x > MAX_LEFT) {
                head.move(add_x, add_y);
                direction_head.x = direction_x;
                direction_head.y = direction_y;
                this->direction.insert(this->direction.begin(), this->direction_head);
                if (this->direction.size() > (score - 1)) {
                    this->direction.pop_back();
                }
                generate_tail();
                display(this->head, this->apple, this->tail);
                sleep(milliseconds(100));
                //if (is_touch()) {
                //    std::cout << "Perdu mauvais va !\n";
                //    return 0;
                if (this->head.getPosition().y <= MAX_TOP || this->head.getPosition().y >= MAX_BOT || this->head.getPosition().x >= MAX_RIGHT || this->head.getPosition().x <= MAX_LEFT) {
                    std::cout << "Perdu bahahaha la lose";
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

    Vector2f center(RectangleShape rect) {
        int ulx = rect.getPosition().x;
        int uly = rect.getPosition().y;
        return Vector2f(ulx + this->size_head.x / 2, uly + this->size_head.y / 2);
    }

    void generate_tail() {
        this->tail.clear();
        this->tail.push_back(head);
        for (int i = 0; i < score; i++) {
            RectangleShape tail(this->size_head);
            Vector2f pos = this->center(this->tail[i]);
            Vector2f pos_center_tail = Vector2f(pos.x + (this->size_head.x * -1 * (this->direction[i].x)), pos.y + (this->size_head.y * -1 * (this->direction[i].y)));
            Vector2f pos_ul = Vector2f(pos_center_tail.x - this->size_head.x / 2, pos_center_tail.y - this->size_head.y / 2);
            tail.setPosition(pos_ul);
            this->tail.push_back(tail);
        }
    }

    //bool is_touch() {
    //    bool touch = false;
    //    Vector2f head_center = center(this->tail[0]);
    //    Vector2f tail_i;
    //    for (int i = 1; i < score; i++) {
    //        tail_i = center(this->tail[i]);
    //        std::cout << head_center.x << " " << head_center.y << " " << tail_i.x << " " << tail_i.y << "\n";
    //        std::cout << i << std:: endl;
    //        touch = ((head_center.x > (tail[i].getPosition().x + this->size_head.x * 3/4)) && (head_center.y > (tail[i].getPosition().y + this->size_head.y * 3/4)) && (head_center.x > (tail[i].getPosition().x + this->size_head.x * 1/3)) && (head_center.y > (tail[i].getPosition().y + this->size_head.y * 1/3)));
    //    }
    //    return (this->head.getPosition().y <= MAX_TOP || this->head.getPosition().y >= MAX_BOT || this->head.getPosition().x >= MAX_RIGHT || this->head.getPosition().x <= MAX_LEFT || touch);
    //}
};

void display(RectangleShape head, RectangleShape apple, std::vector<RectangleShape> tail) {
    window.clear();
    window.draw(apple);
    for (int i = 0; i < tail.size(); i++) {
        window.draw(tail[i]);
    }
    window.display();
}

int main() {
    std::srand(time(NULL));
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