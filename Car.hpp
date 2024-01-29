#include <SFML/Graphics.hpp>
#include <iostream>

enum Type {
    LEFT_RIGHT_STRAIGHT,
    RIGHT_LEFT_STRAIGHT,
    DOWN_UP_STRAIGHT,
    UP_DOWN_STRAIGHT,
};

class Car {
    public:
        Car() {
            body.setSize(sf::Vector2f(40,20));
        }
        Car(Type type, sf::Color color) {
            if (type == LEFT_RIGHT_STRAIGHT || type == RIGHT_LEFT_STRAIGHT) {
                body.setSize(sf::Vector2f(30,16));
                body.setOrigin(sf::Vector2f(15,8));
                width = 30;
                height = 16;
            } else {
                body.setSize(sf::Vector2f(16, 30));
                body.setOrigin(sf::Vector2f(8,15));
                width = 16;
                height = 30;
            }
            this->type = type;
            body.setFillColor(color);
            if (type == RIGHT_LEFT_STRAIGHT)
                body.setPosition(sf::Vector2f(SCRWIDTH + 19,235));
            else if (type == LEFT_RIGHT_STRAIGHT)
                body.setPosition(sf::Vector2f(-19, 265));
            else if (type == DOWN_UP_STRAIGHT)
                body.setPosition(sf::Vector2f(265, SCRHEIGHT + 19));
            else if (type == UP_DOWN_STRAIGHT)
                body.setPosition(sf::Vector2f(235, -19));
            speed = 0;
        }
        sf::RectangleShape getShape() {return body;}
        float x_pos() {return body.getPosition().x;}
        float y_pos() {return body.getPosition().y;}
        float velocity() {return speed;}

        void drive() {
            float newPos = 0;
            if (type == RIGHT_LEFT_STRAIGHT) {
                newPos -= speed;
                if (speed < MAX_SPEED)
                    speed += ACC;
                body.setPosition(sf::Vector2f(body.getPosition().x + newPos, body.getPosition().y));
            } else if (type == LEFT_RIGHT_STRAIGHT) {
                newPos += speed;
                if (speed < MAX_SPEED)
                    speed += ACC;
                body.setPosition(sf::Vector2f(body.getPosition().x + newPos, body.getPosition().y));
            } else if (type == DOWN_UP_STRAIGHT) {
                newPos -= speed;
                if (speed < MAX_SPEED)
                    speed += ACC;
                body.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y + newPos));
            } else if (type == UP_DOWN_STRAIGHT) {
                newPos += speed;
                if (speed < MAX_SPEED)
                    speed += ACC;
                body.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y + newPos));
            }
        }

        void brake() {
            float newPos = 0;
            if (type == RIGHT_LEFT_STRAIGHT) {
                newPos -= speed;
                if (speed > 0)
                    speed -= ACC;
                body.setPosition(sf::Vector2f(body.getPosition().x + newPos, body.getPosition().y));
            } else if (type == LEFT_RIGHT_STRAIGHT) {
                newPos += speed;
                if (speed > 0)
                    speed -= ACC;
                body.setPosition(sf::Vector2f(body.getPosition().x + newPos, body.getPosition().y));
            } else if (type == DOWN_UP_STRAIGHT) {
                newPos -= speed;
                if (speed > 0)
                    speed -= ACC;
                body.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y + newPos));
            } else if (type == DOWN_UP_STRAIGHT) {
                newPos += speed;
                if (speed > 0)
                    speed -= ACC;
                body.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y + newPos));
            }
        }

        void reset() {
            if (type == RIGHT_LEFT_STRAIGHT)
                body.setPosition(sf::Vector2f(SCRWIDTH + 19,235));
            else if (type == LEFT_RIGHT_STRAIGHT)
                body.setPosition(sf::Vector2f(-19, 265));
            else if (type == DOWN_UP_STRAIGHT)
                body.setPosition(sf::Vector2f(265, SCRHEIGHT + 19));
            else if (type == UP_DOWN_STRAIGHT)
                body.setPosition(sf::Vector2f(235, -19));
            speed = 0;
        }

        bool isAtLight() {
            if (type == RIGHT_LEFT_STRAIGHT)
                return body.getPosition().x <= SCRWIDTH/2 + 60 && body.getPosition().x >= SCRWIDTH/2 - 60;
            else if (type == LEFT_RIGHT_STRAIGHT)
                return body.getPosition().x >= SCRWIDTH/2 - 60 && body.getPosition().x <= SCRWIDTH/2 + 60;
            else if (type == DOWN_UP_STRAIGHT)
                return body.getPosition().y <= SCRHEIGHT/2 + 60 && body.getPosition().y <= SCRHEIGHT/2 - 60;
            else
                return body.getPosition().y >= SCRWIDTH/2 - 60 && body.getPosition().y <= SCRWIDTH/2 + 60;
        }

        bool isOffScreen() {
            return body.getPosition().x < -20 || body.getPosition().x > SCRWIDTH + 20
                || body.getPosition().y < -20 || body.getPosition().y > SCRHEIGHT + 20;
                
        }

        // collision detection
        // holy jeez chick mcnuggs this ain't easy
        bool crashed(Car car) {
            return (car.x_pos() >= (body.getPosition().x - width/2)
                && car.x_pos() <= body.getPosition().x + width/2
                && car.y_pos() >= body.getPosition().y - width/2
                && car.y_pos() <= body.getPosition().y + width/2);
        }
    private:
        sf::RectangleShape body;
        Type type;
        float speed = 0;
        int width;
        int height;

        // static variables
        static constexpr float MAX_SPEED = 0.5;
        static constexpr float ACC = 0.02;
        static const int SCRWIDTH = 500;
        static const int SCRHEIGHT = 500;
};