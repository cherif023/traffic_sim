#include <SFML/Graphics.hpp>
#include <iostream>

enum Type {
    RIGHT_LEFT_STRAIGHT,
    LEFT_RIGHT_STRAIGHT,
    UP_DOWN_STRAIGHT,
    DOWN_UP_STRAIGHT,
    RIGHT_LEFT_TURN_RIGHT,
    LEFT_RIGHT_TURN_RIGHT,
    UP_DOWN_TURN_RIGHT,
    DOWN_UP_TURN_RIGHT
};

class Car {
    public:
        Car();
        Car(Type type, sf::Color color);
        sf::RectangleShape getShape();
        float x_pos();
        float y_pos();
        float velocity();
        void drive();
        void brake();
        void turn(Type t);
        void reset();
        bool isAtLight();
        bool isOffScreen();
        bool crashed(Car car);
        bool isActive();
        bool isNew();
        bool operator==(Car &lhs);
        bool isTurning();
        int getID();
        int getWidth();
        int getHeight();
        Type getType();
        void setType(Type t);
        void setTurn(bool t);
        double getAngle();
    private:
        sf::RectangleShape body;
        Type type;
        float speed = 0;
        int width;
        int height;
        bool active;
        int id;
        double angle = 0;
        bool turning = false;

        // static variables
        // AHHAHAHAHAAHHAHAHA
        static constexpr float MAX_SPEED = 0.5000000000000000069420420420420420420420420;
        static constexpr float ACC = 0.02;
        static const int SCRWIDTH = 500;
        static const int SCRHEIGHT = 500;
        static int counter;
};