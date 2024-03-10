#include <SFML/Graphics.hpp>
#include <iostream>
#include "Car.hpp"
#include <vector>
#include <map>
#include <cstdlib>

bool inTraffic(Car* car, std::vector<Car*> &cars) {
    bool in = false;
    for (Car * c : cars) {
        if (!(c == car)) {
            if (car->getType() == RIGHT_LEFT_STRAIGHT && (car->x_pos() >= c->x_pos() && car->x_pos() - 15 <= c->x_pos() + 30)) {
                in = true;
                break;
            } else if (car->getType() == LEFT_RIGHT_STRAIGHT && (car->x_pos() <= c->x_pos() && car->x_pos() + 15 >= c->x_pos() - 30)) {
                in = true;
                break;
            } else if (car->getType() == UP_DOWN_STRAIGHT && (car->y_pos() <= c->y_pos() && car->y_pos() + 15 >= c->y_pos() - 30)) {
                in = true;
                break;
            } else if (car->getType() == DOWN_UP_STRAIGHT && (car->y_pos() >= c->y_pos() && car->y_pos() - 15 <= c->y_pos() + 30)) {
                in = true;
                break;
            }
        }
    }
    return in;
}

int main()
{
    const int SCRWIDTH = 500;
    const int SCRHEIGHT = 500;
    sf::RenderWindow window(sf::VideoMode(SCRWIDTH, SCRHEIGHT), "Traffic Simulator 2024");
    sf::Image icon = sf::Image{};
    if (!icon.loadFromFile("./content/nerds_logo.png")) {
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
    /*
    sf::RectangleShape lights(sf::Vector2f(56,50));
    lights.setOrigin(28,25);
    lights.setPosition(250,250);
    lights.setOutlineColor(sf::Color::Red);
    lights.setOutlineThickness(3);
    lights.setFillColor(sf::Color::Transparent);
    */
    std::map<std::string, sf::RectangleShape> lights;
    sf::RectangleShape RL_light(sf::Vector2f(3,50));
    RL_light.setOrigin(-23.5,25);
    RL_light.setPosition(250, 250);
    RL_light.setOutlineColor(sf::Color::Red);
    RL_light.setFillColor(sf::Color::Red);
    lights.insert({"RL",RL_light});
    sf::RectangleShape LR_light(sf::Vector2f(3,50));
    LR_light.setOrigin(25,25);
    LR_light.setPosition(250, 250);
    LR_light.setOutlineColor(sf::Color::Red);
    LR_light.setFillColor(sf::Color::Red);
    lights.insert({"LR",LR_light});
    sf::RectangleShape DU_light(sf::Vector2f(50,3));
    DU_light.setOrigin(25,-23.5);
    DU_light.setPosition(250, 250);
    DU_light.setOutlineColor(sf::Color::Red);
    DU_light.setFillColor(sf::Color::Red);
    lights.insert({"DU",DU_light});
    sf::RectangleShape UD_light(sf::Vector2f(50,3));
    UD_light.setOrigin(25,25);
    UD_light.setPosition(250, 250);
    UD_light.setOutlineColor(sf::Color::Red);
    UD_light.setFillColor(sf::Color::Red);
    lights.insert({"UD",UD_light});

    // cars
    std::vector<Car*> cars;
    std::vector<Car*> RL_cars;
    std::vector<Car*> LR_cars;
    std::vector<Car*> DU_cars;
    std::vector<Car*> UD_cars;

    /*
    Car car(RIGHT_LEFT_STRAIGHT, sf::Color::Red);
    Car car2(LEFT_RIGHT_STRAIGHT, sf::Color::Green);
    Car car3(DOWN_UP_STRAIGHT, sf::Color::Blue);
    Car car4(UP_DOWN_STRAIGHT, sf::Color::Yellow);
    Car car_next(RIGHT_LEFT_STRAIGHT, sf::Color::Red);
    */

    int speed = 0;
    const int MAX_SPEED = 20;
    int acc = 2;
    bool start_screen = true;
    bool playing = false;
    bool crashed = false;
    
    // lights
    std::map<std::string, bool> green_light;
    green_light.insert({"RL", false});
    green_light.insert({"LR", false});
    green_light.insert({"UD", false});
    green_light.insert({"DU", false});

    // clock
    sf::Clock clock;

    sf::Font roboto;
    sf::Text text;
    sf::Text crash;
    roboto.loadFromFile("./content/Roboto/Roboto-Regular.ttf");
    text.setFont(roboto);
    crash.setFont(roboto);
    crash.setString("Car Crash!!!");
    sf::FloatRect crashRect = crash.getLocalBounds();
    crash.setOrigin(crashRect.left + crashRect.width/2.0f, crashRect.top + crashRect.height/2.0f);
    crash.setCharacterSize(24);
    crash.setStyle(sf::Text::Regular);
    crash.setFillColor(sf::Color::White);
    crash.setPosition(sf::Vector2f(SCRWIDTH/2, SCRHEIGHT/2));

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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && !start_screen) {
                green_light["DU"] = !green_light["DU"];
                if (green_light["DU"]) 
                    lights["DU"].setFillColor(sf::Color::Green);
                else
                    lights["DU"].setFillColor(sf::Color::Red);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && !start_screen) {
                green_light["UD"] = !green_light["UD"];
                if (green_light["UD"]) 
                    lights["UD"].setFillColor(sf::Color::Green);
                else
                    lights["UD"].setFillColor(sf::Color::Red);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left && !start_screen) {
                green_light["RL"] = !green_light["RL"];
                if (green_light["RL"]) 
                    lights["RL"].setFillColor(sf::Color::Green);
                else
                    lights["RL"].setFillColor(sf::Color::Red);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right && !start_screen) {
                green_light["LR"] = !green_light["LR"];
                if (green_light["LR"]) 
                    lights["LR"].setFillColor(sf::Color::Green);
                else
                    lights["LR"].setFillColor(sf::Color::Red);
            }
        }
        window.clear(grass);
        if (start_screen) {
            crashed = false;
            for (Car * c : cars) {
                delete c;
            }
            cars.clear();
            RL_cars.clear();
            LR_cars.clear();
            UD_cars.clear();
            DU_cars.clear();
            window.draw(text);
            green_light["DU"] = false;
            lights["DU"].setFillColor(sf::Color::Red);
            green_light["UD"] = false;
            lights["UD"].setFillColor(sf::Color::Red);
            green_light["LR"] = false;
            lights["LR"].setFillColor(sf::Color::Red);
            green_light["RL"] = false;
            lights["RL"].setFillColor(sf::Color::Red);
        }
        if (!playing)
            clock.restart();
        if (playing && !crashed) {
            if (cars.size() == 0) {
                Car* c = new Car(LEFT_RIGHT_STRAIGHT, sf::Color::Red);
                LR_cars.push_back(c);
                cars.push_back(c);
                cars[0]->drive();
            } 
            if (clock.getElapsedTime().asSeconds() >= 1 && cars.size() < 20) {
                int numTimes = rand();
                Type last = RIGHT_LEFT_STRAIGHT;
                Type lastlast = RIGHT_LEFT_STRAIGHT;
                for (int i = 0; i <= numTimes % 3; i++) {
                    int rand_type = rand();
                    if (numTimes % 3 == 1)
                        while (rand_type % 4 == last)
                            rand_type = rand();
                    else if (numTimes % 3 == 2)
                        while (rand_type % 4 == last || rand_type % 4 == lastlast)
                            rand_type = rand();
                    std::cout << rand_type << std::endl;
                    std::cout << i << rand_type % 4 << last << lastlast << std::endl;
                    if (rand_type % 4 == 0) {
                        Car *c = new Car(RIGHT_LEFT_STRAIGHT, sf::Color::Red);
                        RL_cars.push_back(c);
                        cars.push_back(c);
                        if (i==0)
                            last = Type(rand_type % 4);
                        else if (i==1)
                            lastlast = Type(rand_type % 4);
                    } else if (rand_type % 4 == 1) {
                        Car *c = new Car(LEFT_RIGHT_STRAIGHT, sf::Color::Green);
                        LR_cars.push_back(c);
                        cars.push_back(c);
                        if (i==0)
                            last = Type(rand_type % 4);
                        else if (i==1)
                            lastlast = Type(rand_type % 4);
                    } else if (rand_type % 4 == 2) {
                        Car *c = new Car(UP_DOWN_STRAIGHT, sf::Color::Yellow);
                        UD_cars.push_back(c);
                        cars.push_back(c);
                        if (i==0)
                            last = Type(rand_type % 4);
                        else if (i==1)
                            lastlast = Type(rand_type % 4);
                    } else if (rand_type % 4 == 3) {
                        Car *c = new Car(DOWN_UP_STRAIGHT, sf::Color::Blue);
                        DU_cars.push_back(c);
                        cars.push_back(c);
                        if (i==0)
                            last = Type(rand_type % 4);
                        else if (i==1)
                            lastlast = Type(rand_type % 4);
                    }
                }
                clock.restart();
            }
            for (Car* car : cars) {
                // if the car is not at a red light, offscreen, or in traffic, drive.
                if (!car->isOffScreen()
                        && ((car->getType() == DOWN_UP_STRAIGHT && (!inTraffic(car, DU_cars) 
                            && (!car->isAtLight() || green_light["DU"])))
                        || (car->getType() == UP_DOWN_STRAIGHT && (!inTraffic(car, UD_cars) 
                            && (!car->isAtLight() || green_light["UD"])))
                        || (car->getType() == LEFT_RIGHT_STRAIGHT && (!inTraffic(car, LR_cars) 
                            && (!car->isAtLight() || green_light["LR"])))
                        || (car->getType() == RIGHT_LEFT_STRAIGHT && (!inTraffic(car, RL_cars) 
                            && (!car->isAtLight() || green_light["RL"]))))) {
                        car->drive();
                }
                // if the car is at a red light, offscreen or in traffic, brake.
                else if (car->isAtLight() || car->isOffScreen()
                        || (car->getType() == DOWN_UP_STRAIGHT && (inTraffic(car, DU_cars) || !green_light["DU"]))
                        || (car->getType() == UP_DOWN_STRAIGHT && (inTraffic(car, UD_cars) || !green_light["UD"]))
                        || (car->getType() == LEFT_RIGHT_STRAIGHT && (inTraffic(car, LR_cars) || !green_light["LR"]))
                        || (car->getType() == RIGHT_LEFT_STRAIGHT && (inTraffic(car, RL_cars) || !green_light["RL"]))) {
                        car->brake();
                }
                for (auto c:cars) {
                    if (!(c->getID() == car->getID()) && car->crashed(*c)) {
                        crashed = true;
                        c->getShape().setFillColor(sf::Color::White);
                        car->getShape().setFillColor(sf::Color::White);
                        std::cout << "Car crash!" << c->getType() << car->getType() << std::endl;
                        std::cout << c->x_pos() << c->y_pos() << car->x_pos() << car->y_pos() << c->getID() << car->getID() << std::endl;
                        break;
                    }
                }
            }
            for (size_t i = 0; i < cars.size(); i++) {
                if (cars[i]->isOffScreen()) {
                    if (cars[i]->getType() == RIGHT_LEFT_STRAIGHT) {
                        for (size_t j = 0; j < RL_cars.size(); j++) {
                            if (cars[i] == RL_cars[j])
                                RL_cars.erase(RL_cars.begin() + j);
                        }
                    } else if (cars[i]->getType() == LEFT_RIGHT_STRAIGHT) {
                        for (size_t j = 0; j < LR_cars.size(); j++) {
                            if (cars[i] == LR_cars[j])
                                LR_cars.erase(LR_cars.begin() + j);
                        }
                    } else if (cars[i]->getType() == UP_DOWN_STRAIGHT) {
                        for (size_t j = 0; j < UD_cars.size(); j++) {
                            if (cars[i] == UD_cars[j])
                                UD_cars.erase(UD_cars.begin() + j);
                        }
                    } else if (cars[i]->getType() == DOWN_UP_STRAIGHT) {
                        for (size_t j = 0; j < DU_cars.size(); j++) {
                            if (cars[i] == DU_cars[j])
                                DU_cars.erase(DU_cars.begin() + j);
                        }
                    }
                    delete cars[i];
                    cars.erase(cars.begin() + i);
                }
            }
            window.draw(road);
            window.draw(road2);
            window.draw(lane);
            window.draw(lane2);
            window.draw(lane3);
            window.draw(lane4);
            window.draw(square);
            for (Car* car : cars)
                window.draw(car->getShape());
            window.draw(lights["RL"]);
            window.draw(lights["LR"]);
            window.draw(lights["DU"]);
            window.draw(lights["UD"]);
        } else if (crashed) {
            window.draw(crash);
        }
        window.display();
    }

    return 0;
}