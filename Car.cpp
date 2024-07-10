#include "Car.hpp"
#include <cmath>

int Car::counter = 0;
float Car::SCRWIDTH = 0;
float Car::SCRHEIGHT = 0;
float Car::real_width = 0;
float Car::scr_start = 0;
float Car::MAX_SPEED = 0.5;
float Car::ACC = 0.02;

float pi = atan(1)*4;

Car::Car() {
    body.setSize(sf::Vector2f(SCRWIDTH * 0.08,SCRHEIGHT * 0.04));
}
Car::Car(Type type, sf::Color color) {
    if (type == LEFT_RIGHT_STRAIGHT || type == RIGHT_LEFT_STRAIGHT 
        || type == RIGHT_LEFT_TURN_RIGHT || type == LEFT_RIGHT_TURN_RIGHT) {
        body.setSize(sf::Vector2f(SCRWIDTH*0.06,SCRHEIGHT*0.032));
        body.setOrigin(sf::Vector2f(SCRWIDTH*0.03,SCRHEIGHT*0.016));
        width = SCRWIDTH * 0.06;
        height = SCRHEIGHT * 0.032;
    } else {
        body.setSize(sf::Vector2f(SCRWIDTH * 0.032, SCRHEIGHT*0.06));
        body.setOrigin(sf::Vector2f(SCRWIDTH*0.016,SCRHEIGHT*0.03));
        width = SCRWIDTH*0.032;
        height = SCRHEIGHT*0.06;
    }
    this->type = type;
    body.setFillColor(color);
    if (type == RIGHT_LEFT_STRAIGHT || type == RIGHT_LEFT_TURN_RIGHT)
        body.setPosition(sf::Vector2f(real_width/2 + SCRWIDTH/2 + SCRWIDTH*0.038,SCRHEIGHT*0.47));
    else if (type == LEFT_RIGHT_STRAIGHT || type == LEFT_RIGHT_TURN_RIGHT)
        body.setPosition(sf::Vector2f(real_width/2 - SCRWIDTH/2 - SCRWIDTH*0.038,SCRHEIGHT*0.53));
    else if (type == DOWN_UP_STRAIGHT || type == DOWN_UP_TURN_RIGHT)
        body.setPosition(sf::Vector2f(real_width/2 - SCRWIDTH/2 + SCRWIDTH*0.53, SCRHEIGHT + SCRHEIGHT*0.038));
    else if (type == UP_DOWN_STRAIGHT || type == UP_DOWN_TURN_RIGHT)
        body.setPosition(sf::Vector2f(real_width/2 - SCRWIDTH/2 + SCRWIDTH*0.47, SCRHEIGHT*-0.038));
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
    if (type == RIGHT_LEFT_STRAIGHT || (type == RIGHT_LEFT_TURN_RIGHT && body.getPosition().x >= real_width/2 + getWidthResize(40))) {
        newPos -= speed;
        if (speed < MAX_SPEED)
            speed += ACC;
        body.setPosition(sf::Vector2f(body.getPosition().x + newPos, body.getPosition().y));
    } else if (type == LEFT_RIGHT_STRAIGHT || (type == LEFT_RIGHT_TURN_RIGHT && body.getPosition().x <= real_width/2 - getWidthResize(40))) {
        newPos += speed;
        if (speed < MAX_SPEED)
            speed += ACC;
        body.setPosition(sf::Vector2f(body.getPosition().x + newPos, body.getPosition().y));
    } else if (type == DOWN_UP_STRAIGHT || (type == DOWN_UP_TURN_RIGHT && body.getPosition().y >= SCRHEIGHT/2 + getWidthResize(40))) {
        newPos -= speed;
        if (speed < MAX_SPEED)
            speed += ACC;
        body.setPosition(sf::Vector2f(body.getPosition().x, body.getPosition().y + newPos));
    } else if (type == UP_DOWN_STRAIGHT || (type == UP_DOWN_TURN_RIGHT && body.getPosition().y <= SCRHEIGHT/2 - getWidthResize(40))) {
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
        body.setPosition(sf::Vector2f(scr_start + SCRWIDTH + getWidthResize(19),getHeightResize(235)));
    else if (type == LEFT_RIGHT_STRAIGHT)
        body.setPosition(sf::Vector2f(scr_start - getWidthResize(19), getHeightResize(265)));
    else if (type == DOWN_UP_STRAIGHT)
        body.setPosition(sf::Vector2f(scr_start + getWidthResize(265), SCRHEIGHT + getHeightResize(19)));
    else if (type == UP_DOWN_STRAIGHT)
        body.setPosition(sf::Vector2f(scr_start + getWidthResize(235), -getHeightResize(19)));
    speed = 0;
    //active = false;
}

// if the car is first at the light
bool Car::isAtLight() {
    if (type == RIGHT_LEFT_STRAIGHT || type == RIGHT_LEFT_TURN_RIGHT)
        return body.getPosition().x <= real_width/2 + getWidthResize(60) && body.getPosition().x >= real_width/2 + getWidthResize(40);
    else if (type == LEFT_RIGHT_STRAIGHT || type == LEFT_RIGHT_TURN_RIGHT)
        return body.getPosition().x >= real_width/2 - getWidthResize(60) && body.getPosition().x <= real_width/2 - getWidthResize(40);
    else if (type == DOWN_UP_STRAIGHT || type == DOWN_UP_TURN_RIGHT)
        return body.getPosition().y <= SCRHEIGHT/2 + getHeightResize(60) && body.getPosition().y >= SCRHEIGHT/2 + getHeightResize(40);
    else if (type == UP_DOWN_STRAIGHT || type == UP_DOWN_TURN_RIGHT)
        return body.getPosition().y >= SCRHEIGHT/2 - getHeightResize(60) && body.getPosition().y <= SCRHEIGHT/2 - getHeightResize(40);
    else
        return false;
}

// if the car is no longer relevant (real)
bool Car::isOffScreen() {
    return body.getPosition().x < scr_start - getWidthResize(20) || body.getPosition().x > scr_start + SCRWIDTH + getWidthResize(20)
        || body.getPosition().y < -getHeightResize(20) || body.getPosition().y > SCRHEIGHT + getHeightResize(20);
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
        return (body.getPosition().x == scr_start + SCRWIDTH + getWidthResize(19));
    else if (type == LEFT_RIGHT_STRAIGHT || type == LEFT_RIGHT_TURN_RIGHT)
        return (body.getPosition().x == scr_start - getWidthResize(19));
    else if (type == DOWN_UP_STRAIGHT || type == DOWN_UP_TURN_RIGHT)
        return body.getPosition().y == SCRHEIGHT + getHeightResize(19);
    else
        return body.getPosition().y == -getHeightResize(19);
}

// set the scrwidth and scrheight variables
// SCRWIDTH: playable width of the screen (doesnt include sidebars)
// SCRHEIGHT: height of the screen (this is all "playable," as there are no vertical sidebars)
// real_width: actual size of the entire window (including sidebars)
void Car::setWindowSize(std::pair<float, float> window, float rw) {
    SCRWIDTH = window.first;
    SCRHEIGHT = window.second;
    real_width = rw;
    scr_start = (real_width - SCRWIDTH)/2.0;
    ACC = getWidthResize(0.02) * OS_CONV_FACTOR;

    float SP_CONV_FACTOR = 0.25 * (SCRWIDTH/500) + 0.75; // adjusts the speed to match in resizing
    MAX_SPEED = getWidthResize(0.5) * OS_CONV_FACTOR * SP_CONV_FACTOR;
}

float Car::getWidthResize(float num) {
    return SCRWIDTH*(num/500);
}

float Car::getHeightResize(float num) {
    return SCRHEIGHT*(num/500);
}

bool Car::isTurning() {return turning;}
Type Car::getType() {return type;}
void Car::setType(Type t) {type = t;}
double Car::getAngle() {return angle;}
void Car::setTurn(bool t) {turning = t;}