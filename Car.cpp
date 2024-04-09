#include "Car.hpp"
#include <cmath>

int Car::counter = 0;

float pi = atan(1)*4;

Car::Car() {
    body.setSize(sf::Vector2f(40,20));
}
Car::Car(Type type, sf::Color color) {
    if (type == LEFT_RIGHT_STRAIGHT || type == RIGHT_LEFT_STRAIGHT 
        || type == RIGHT_LEFT_TURN_RIGHT || type == LEFT_RIGHT_TURN_RIGHT) {
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
    if (type == RIGHT_LEFT_STRAIGHT || type == RIGHT_LEFT_TURN_RIGHT)
        body.setPosition(sf::Vector2f(SCRWIDTH + 19,235));
    else if (type == LEFT_RIGHT_STRAIGHT || type == LEFT_RIGHT_TURN_RIGHT)
        body.setPosition(sf::Vector2f(-19, 265));
    else if (type == DOWN_UP_STRAIGHT || type == DOWN_UP_TURN_RIGHT)
        body.setPosition(sf::Vector2f(265, SCRHEIGHT + 19));
    else if (type == UP_DOWN_STRAIGHT || type == UP_DOWN_TURN_RIGHT)
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

// GOGOGO
void Car::drive() {
    float newPos = 0;
    if (type == RIGHT_LEFT_STRAIGHT || (type == RIGHT_LEFT_TURN_RIGHT && body.getPosition().x >= SCRWIDTH/2 + 40)) {
        newPos -= speed;
        if (speed < MAX_SPEED)
            speed += ACC;
        body.setPosition(sf::Vector2f(body.getPosition().x + newPos, body.getPosition().y));
    } else if (type == LEFT_RIGHT_STRAIGHT || (type == LEFT_RIGHT_TURN_RIGHT && body.getPosition().x <= SCRWIDTH/2 - 40)) {
        newPos += speed;
        if (speed < MAX_SPEED)
            speed += ACC;
        body.setPosition(sf::Vector2f(body.getPosition().x + newPos, body.getPosition().y));
    } else if (type == DOWN_UP_STRAIGHT || (type == DOWN_UP_TURN_RIGHT && body.getPosition().y >= SCRWIDTH/2 + 40)) {
        newPos -= speed;
        if (speed < MAX_SPEED)
            speed += ACC;
        body.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y + newPos));
    } else if (type == UP_DOWN_STRAIGHT || (type == UP_DOWN_TURN_RIGHT && body.getPosition().y <= SCRHEIGHT/2 - 40)) {
        newPos += speed;
        if (speed < MAX_SPEED)
            speed += ACC;
        body.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y + newPos));
    }
    active = true;
}

// brake the car
void Car::brake() {
    float newPos = 0;
    if (type == RIGHT_LEFT_STRAIGHT || type == RIGHT_LEFT_TURN_RIGHT) {
        newPos -= speed;
        if (speed > 0)
            speed -= ACC;
        body.setPosition(sf::Vector2f(body.getPosition().x + newPos, body.getPosition().y));
    } else if (type == LEFT_RIGHT_STRAIGHT || type == LEFT_RIGHT_TURN_RIGHT) {
        newPos += speed;
        if (speed > 0)
            speed -= ACC;
        body.setPosition(sf::Vector2f(body.getPosition().x + newPos, body.getPosition().y));
    } else if (type == DOWN_UP_STRAIGHT || type == DOWN_UP_TURN_RIGHT) {
        newPos -= speed;
        if (speed > 0)
            speed -= ACC;
        body.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y + newPos));
    } else if (type == UP_DOWN_STRAIGHT || type == UP_DOWN_TURN_RIGHT) {
        newPos += speed;
        if (speed > 0)
            speed -= ACC;
        body.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y + newPos));
    }
}

// turn the car
void Car::turn(Type t) {
    speed = MAX_SPEED;
    if (t == RIGHT_LEFT_TURN_RIGHT) {
        if (body.getRotation() < 90) {
            body.setRotation(angle*(180/pi));
            if (angle >= pi/2) {
                body.setRotation(90);
            } else {
                body.setPosition(sf::Vector2f(body.getPosition().x - speed*cos(angle), body.getPosition().y - speed*sin(angle)));
                angle += (pi/150) * OS_CONV_FACTOR;
            }
        }
    } else if (t == LEFT_RIGHT_TURN_RIGHT) {
        if (body.getRotation() > -90) {
            body.setRotation(-angle*(180/pi));
            if (angle <= -pi/2) {
                body.setRotation(-90);
            } else {
                body.setPosition(sf::Vector2f(body.getPosition().x + speed*cos(angle), body.getPosition().y - speed*sin(angle)));
                angle -= (pi/150) * OS_CONV_FACTOR;
            }
        }
    } else if (t == DOWN_UP_TURN_RIGHT) {
        if (body.getRotation() < 90) {
            body.setRotation(angle*(180/pi));
            if (angle >= pi/2) {
                body.setRotation(90);
            } else {
                body.setPosition(sf::Vector2f(body.getPosition().x + speed*sin(angle), body.getPosition().y - speed*cos(angle)));
                angle += (pi/150) * OS_CONV_FACTOR;
            }
        }
    } else if (t == UP_DOWN_TURN_RIGHT) {
        if (body.getRotation() < 90) {
            body.setRotation(angle*(180/pi));
            if (angle >= pi/2) {
                body.setRotation(-90);
            } else {
                body.setPosition(sf::Vector2f(body.getPosition().x - speed*sin(angle), body.getPosition().y + speed*cos(angle)));
                angle += (pi/150) * OS_CONV_FACTOR;
            }
        }
    }
}

// mainly used for testing, just respawns the car where it started
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

// if the car is first at the light
bool Car::isAtLight() {
    if (type == RIGHT_LEFT_STRAIGHT || type == RIGHT_LEFT_TURN_RIGHT)
        return body.getPosition().x <= SCRWIDTH/2 + 60 && body.getPosition().x >= SCRWIDTH/2 + 40;
    else if (type == LEFT_RIGHT_STRAIGHT || type == LEFT_RIGHT_TURN_RIGHT)
        return body.getPosition().x >= SCRWIDTH/2 - 60 && body.getPosition().x <= SCRWIDTH/2 - 40;
    else if (type == DOWN_UP_STRAIGHT || type == DOWN_UP_TURN_RIGHT)
        return body.getPosition().y <= SCRHEIGHT/2 + 60 && body.getPosition().y >= SCRHEIGHT/2 + 40;
    else if (type == UP_DOWN_STRAIGHT || type == UP_DOWN_TURN_RIGHT)
        return body.getPosition().y >= SCRHEIGHT/2 - 60 && body.getPosition().y <= SCRWIDTH/2 - 40;
    else
        return false;
}

// if the car is no longer relevant (real)
bool Car::isOffScreen() {
    return body.getPosition().x < -20 || body.getPosition().x > SCRWIDTH + 20
        || body.getPosition().y < -20 || body.getPosition().y > SCRHEIGHT + 20;
}

// collision detection
bool Car::crashed(Car car) {
    return (!car.isNew() && !this->isNew() && this != &car
        && car.x_pos() + car.getWidth()/2 >= (body.getPosition().x - width/2)
        && car.x_pos() - car.getWidth()/2 <= body.getPosition().x + width/2
        && car.y_pos() + car.getHeight()/2 >= body.getPosition().y - height/2
        && car.y_pos() - car.getHeight()/2 <= body.getPosition().y + height/2);
}

bool Car::operator==(Car &lhs) {
    return id == lhs.getID();
}

int Car::getWidth() {return width;}
int Car::getHeight() {return height;}
bool Car::isNew() {
    if (type == RIGHT_LEFT_STRAIGHT || type == RIGHT_LEFT_TURN_RIGHT)
        return (body.getPosition().x == SCRWIDTH + 19);
    else if (type == LEFT_RIGHT_STRAIGHT || type == LEFT_RIGHT_TURN_RIGHT)
        return (body.getPosition().x == -19);
    else if (type == DOWN_UP_STRAIGHT || type == DOWN_UP_TURN_RIGHT)
        return body.getPosition().y == SCRHEIGHT + 19;
    else
        return body.getPosition().y == -19;
}
bool Car::isTurning() {return turning;}
Type Car::getType() {return type;}
void Car::setType(Type t) {type = t;}
double Car::getAngle() {return angle;}
void Car::setTurn(bool t) {turning = t;}