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
        Car();
        Car(Type type, sf::Color color);
        sf::RectangleShape getShape();
        float x_pos();
        float y_pos();
        float velocity();
        void drive();
        void brake();
        void reset();
        bool isAtLight();
        bool isOffScreen();
        bool crashed(Car car);
        bool isActive();
        bool operator==(Car &lhs);
        int getID();
        int getWidth();
        int getHeight();
        Type getType();
    private:
        sf::RectangleShape body;
        Type type;
        float speed = 0;
        int width;
        int height;
        bool active;
        int id;

        // static variables
        static constexpr float MAX_SPEED = 0.5;
        static constexpr float ACC = 0.02;
        static const int SCRWIDTH = 500;
        static const int SCRHEIGHT = 500;
        static int counter;
};