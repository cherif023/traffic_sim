#include <SFML/Graphics.hpp>
#include <iostream>
#include "Car.hpp"

int main()
{
    const int SCRWIDTH = 500;
    const int SCRHEIGHT = 500;
    sf::RenderWindow window(sf::VideoMode(SCRWIDTH, SCRHEIGHT), "Traffic Simulator 2024");
    sf::Image icon = sf::Image{};
    if (!icon.loadFromFile("nerds_logo.png")) {
        std::cout << "Error loading image" << std::endl;
        return 1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // colors
    sf::Color road_side(125, 125, 125);
    sf::Color grass(15,59,13);

    // roads
    sf::RectangleShape road(sf::Vector2f(500, 50));
    road.setFillColor(sf::Color::Black);
    road.setOutlineColor(road_side);
    road.setOutlineThickness(3);
    road.setOrigin(250, 25);
    road.setPosition(250, 250);

    sf::RectangleShape road2(sf::Vector2f(50,500));
    road2.setFillColor(sf::Color::Black);
    road2.setOutlineColor(road_side);
    road2.setOutlineThickness(3);
    road2.setOrigin(25, 250);
    road2.setPosition(250, 250);

    sf::RectangleShape square(sf::Vector2f(56,50));
    square.setOrigin(28,25);
    square.setPosition(250,250);
    square.setFillColor(sf::Color::Black);

    // lanes
    sf::RectangleShape lane(sf::Vector2f(1, 500));
    lane.setOrigin(-1, 250);
    lane.setPosition(sf::Vector2f(250,250));
    lane.setFillColor(sf::Color::Yellow);
    sf::RectangleShape lane2(sf::Vector2f(500, 1));
    lane2.setOrigin(250, -1);
    lane2.setPosition(sf::Vector2f(250,250));
    lane2.setFillColor(sf::Color::Yellow);
    sf::RectangleShape lane3(sf::Vector2f(1, 500));
    lane3.setOrigin(3, 250);
    lane3.setPosition(sf::Vector2f(250,250));
    lane3.setFillColor(sf::Color::Yellow);
    sf::RectangleShape lane4(sf::Vector2f(500, 1));
    lane4.setOrigin(250, 3);
    lane4.setPosition(sf::Vector2f(250,250));
    lane4.setFillColor(sf::Color::Yellow);

    // traffic lights
    sf::RectangleShape lights(sf::Vector2f(56,50));
    lights.setOrigin(28,25);
    lights.setPosition(250,250);
    lights.setOutlineColor(sf::Color::Red);
    lights.setOutlineThickness(3);
    lights.setFillColor(sf::Color::Transparent);

    // cars
    Car car(RIGHT_LEFT_STRAIGHT, sf::Color::Red);
    Car car2(LEFT_RIGHT_STRAIGHT, sf::Color::Green);
    Car car3(DOWN_UP_STRAIGHT, sf::Color::Blue);
    Car car4(UP_DOWN_STRAIGHT, sf::Color::Yellow);

    int speed = 0;
    const int MAX_SPEED = 20;
    int acc = 2;
    bool start_screen = true;
    bool playing = false;
    bool crashed = false;
    
    // lights
    bool green_light = false;

    sf::Font roboto;
    sf::Text text;
    sf::Text car_speed;
    sf::Text car_pos;
    sf::Text crash;
    roboto.loadFromFile("Roboto/Roboto-Regular.ttf");
    text.setFont(roboto);
    crash.setFont(roboto);
    crash.setString("Car Crash!!!");
    sf::FloatRect crashRect = crash.getLocalBounds();
    crash.setOrigin(crashRect.left + crashRect.width/2.0f, crashRect.top + crashRect.height/2.0f);
    crash.setCharacterSize(24);
    crash.setStyle(sf::Text::Regular);
    crash.setFillColor(sf::Color::White);
    crash.setPosition(sf::Vector2f(SCRWIDTH/2, SCRHEIGHT/2));
    car_speed.setFont(roboto);
    car_pos.setFont(roboto);

    while (window.isOpen())
    {
        sf::Event event;
        text.setString("Traffic Simulator 2024");
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
        text.setCharacterSize(24);
        text.setStyle(sf::Text::Regular);
        text.setFillColor(sf::Color::White);
        text.setPosition(sf::Vector2f(250,250));
        car_speed.setString("Speed: " + std::to_string(car2.velocity()));
        car_pos.setString("x_pos: " + std::to_string(car2.x_pos()));
        car_speed.setCharacterSize(24);
        car_speed.setFillColor(sf::Color::White);
        car_speed.setPosition(sf::Vector2f(250, 100));
        car_pos.setCharacterSize(24);
        car_pos.setFillColor(sf::Color::White);
        car_pos.setPosition(sf::Vector2f(250, 50));
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && start_screen) {
                start_screen = false;
                playing = true;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && !start_screen) {
                start_screen = true;
                playing = false;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G && !start_screen) {
                green_light = !green_light;
                if (green_light)
                    lights.setOutlineColor(sf::Color::Green);
                else
                    lights.setOutlineColor(sf::Color::Red);
            }
        }
        window.clear(grass);
        if (start_screen) {
            crashed = false;
            window.draw(text);
            car.reset();
            car2.reset();
            car3.reset();
            car4.reset();
            green_light = false;
            lights.setOutlineColor(sf::Color::Red);
        }
        if (playing) {
            if ((!car.isAtLight() || green_light) && !car.isOffScreen()) {
                car.drive();
                car2.drive();
                car3.drive();
                car4.drive();
            } if (car.isAtLight() && car.velocity() > 0 && !green_light) {
                car.brake();
                car2.brake();
                car3.brake();
                car4.brake();
            } if (car.isOffScreen()) {
                car.reset();
                car2.reset();
                car3.reset();
                car4.reset();
            }
            window.draw(road);
            window.draw(road2);
            window.draw(lane);
            window.draw(lane2);
            window.draw(lane3);
            window.draw(lane4);
            window.draw(square);
            window.draw(car_speed);
            window.draw(car_pos);
            window.draw(car.getShape());
            window.draw(car2.getShape());
            window.draw(car3.getShape());
            window.draw(car4.getShape());
            window.draw(lights);
            if (car.crashed(car2)) {
                crashed = true;
                playing = false;
            }
        } else if (crashed) {
            window.draw(crash);
        }
        window.display();
    }

    return 0;
}