#include "Car.hpp"

int Car::counter = 0;

Car::Car() {
    body.setSize(sf::Vector2f(40,20));
}
Car::Car(Type type, sf::Color color) {
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
    active = false;
    id = counter++;
}

sf::RectangleShape Car::getShape() {return body;}
float Car::x_pos() {return body.getPosition().x;}
float Car::y_pos() {return body.getPosition().y;}
float Car::velocity() {return speed;}
bool Car::isActive() {return active;}
int Car::getID() {return id;}

void Car::drive() {
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
    active = true;
}

void Car::brake() {
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

void Car::reset() {
    if (type == RIGHT_LEFT_STRAIGHT)
        body.setPosition(sf::Vector2f(SCRWIDTH + 19,235));
    else if (type == LEFT_RIGHT_STRAIGHT)
        body.setPosition(sf::Vector2f(-19, 265));
    else if (type == DOWN_UP_STRAIGHT)
        body.setPosition(sf::Vector2f(265, SCRHEIGHT + 19));
    else if (type == UP_DOWN_STRAIGHT)
        body.setPosition(sf::Vector2f(235, -19));
    speed = 0;
    //active = false;
}

bool Car::isAtLight() {
    if (type == RIGHT_LEFT_STRAIGHT)
        return body.getPosition().x <= SCRWIDTH/2 + 60 && body.getPosition().x >= SCRWIDTH/2 + 40;
    else if (type == LEFT_RIGHT_STRAIGHT)
        return body.getPosition().x >= SCRWIDTH/2 - 60 && body.getPosition().x <= SCRWIDTH/2 - 40;
    else if (type == DOWN_UP_STRAIGHT)
        return body.getPosition().y <= SCRHEIGHT/2 + 60 && body.getPosition().y >= SCRHEIGHT/2 + 40;
    else
        return body.getPosition().y >= SCRHEIGHT/2 - 60 && body.getPosition().y <= SCRWIDTH/2 - 40;
}

bool Car::isOffScreen() {
    return body.getPosition().x < -20 || body.getPosition().x > SCRWIDTH + 20
        || body.getPosition().y < -20 || body.getPosition().y > SCRHEIGHT + 20;
}

// collision detection
bool Car::crashed(Car car) {
    return (car.x_pos() + car.getWidth()/2 >= (body.getPosition().x - width/2)
        && car.x_pos() - car.getWidth()/2 <= body.getPosition().x + width/2
        && car.y_pos() + car.getHeight()/2 >= body.getPosition().y - height/2
        && car.y_pos() - car.getHeight()/2 <= body.getPosition().y + height/2);
}

bool Car::operator==(Car &lhs) {
    return id == lhs.getID();
}

int Car::getWidth() {return width;}
int Car::getHeight() {return height;}

Type Car::getType() {return type;}