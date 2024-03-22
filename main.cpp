#include <SFML/Graphics.hpp>
#include <iostream>
#include "Car.hpp"
#include <vector>
#include <map>
#include <cstdlib>

const int SCRWIDTH = 500;
const int SCRHEIGHT = 500;

// checks if the car is within a given distance behind another car in the same line
bool inTraffic(Car* car, std::vector<Car*> &cars) {
    bool in = false;
    for (Car * c : cars) {
        if (!(c == car)) {
            if ((car->getType() == RIGHT_LEFT_STRAIGHT || car->getType() == RIGHT_LEFT_TURN_RIGHT) && (car->x_pos() >= c->x_pos() && car->x_pos() - 17 <= c->x_pos() + 27)) {
                in = true;
                break;
            } else if (car->getType() == LEFT_RIGHT_STRAIGHT && (car->x_pos() <= c->x_pos() && car->x_pos() + 17 >= c->x_pos() - 27)) {
                in = true;
                break;
            } else if (car->getType() == UP_DOWN_STRAIGHT && (car->y_pos() <= c->y_pos() && car->y_pos() + 17 >= c->y_pos() - 27)) {
                in = true;
                break;
            } else if (car->getType() == DOWN_UP_STRAIGHT && (car->y_pos() >= c->y_pos() && car->y_pos() - 17 <= c->y_pos() + 27)) {
                in = true;
                break;
            }
        }
    }
    return in;
}

// beware
void Akash_epic_gamer_monkeyballs_function() {
    for (int j = 0; j < 9999; j++) {
        for (int i = 0; i < 9999; i++) {
            std::cout << i;
        }
    }
    std::cout << "\n\nDays until you grow a pair of balls.\n\n";
    std::string url = "https://youtu.be/Hl24v20vs5g";
    std::string command = "start " + url;
    system(command.c_str());
}

// checks to find how many cars in a given line haven't gone through the light yet
int backedUp(std::vector<Car*> cars) {
    int total = 0;
    for (auto car : cars) {
        if (car->getType() == RIGHT_LEFT_STRAIGHT || car->getType() == RIGHT_LEFT_TURN_RIGHT) {
            if (car->x_pos() > SCRWIDTH/2)
                total++;
        }
        else if (car->getType() == LEFT_RIGHT_STRAIGHT || car->getType() == LEFT_RIGHT_TURN_RIGHT) {
            if (car->x_pos() < SCRWIDTH/2)
                total++;
        }
        else if (car->getType() == UP_DOWN_STRAIGHT) {
            //std::cout << "UP DOWN STRAIGHT" << std::endl;
            if (car->y_pos() < SCRHEIGHT/2)
                total++;
        }
        else {
            if (car->y_pos() > SCRHEIGHT/2)
                total++;
        }
    }
    return total;
}

int main()
{
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

    // setup variables
    int speed = 0;
    const int MAX_SPEED = 20;
    int acc = 2;
    bool start_screen = true;
    bool playing = false;
    bool rules = false;

    //string for rules
    std::string rls = "Welcome! Here are the rules.\n\n";
    rls += "Cars will spawn in 1 of 4 directions:\n1. up->down\n2. down->up\n3. left->right\n4. right->left.\n";
    rls += "Use the arrow keys to change light from green to red and back.\n";
    rls += "Pressing right will make the left->right cars move right, up will\nmake down->up cars go up, etc.\n";
    rls += "You have to make sure no line gets too full.\n";
    rls += "Your score also decreases every so often.\nEvery car that goes through the light gives you a point.\n";
    rls += "DO NOT LET YOUR SCORE GET TO 0!!\n";
    rls += "Also obviously don't let the cars crash.\n\n";
    rls += "Press [Escape] to return to the main menu.";

    // losing sequences
    std::map<std::string, sf::Text> loss;
    bool crashed = false;
    bool tooMany = false;
    int score = 20;
    
    // lights
    std::map<std::string, bool> green_light;
    green_light.insert({"RL", false});
    green_light.insert({"LR", false});
    green_light.insert({"UD", false});
    green_light.insert({"DU", false});

    // clocks
    sf::Clock clock;
    sf::Clock scoreClock;
    sf::Clock total;
    int totalTime;

    // texts
    sf::Font roboto;
    sf::Text text;
    sf::Text crash;
    sf::Text tooManyCars;
    sf::Text scoreText;
    sf::Text scoring;
    sf::Text timer;
    sf::Text rulesText;
    roboto.loadFromFile("./content/Roboto/Roboto-Regular.ttf");
    text.setFont(roboto);
    crash.setFont(roboto);
    tooManyCars.setFont(roboto);
    scoreText.setFont(roboto);
    scoring.setFont(roboto);
    timer.setFont(roboto);
    rulesText.setFont(roboto);
    crash.setString("Car Crash!!!");
    tooManyCars.setString("Too many cars in line!");
    scoring.setString("Too slow!");
    timer.setString("You lasted 00 seconds!");
    rulesText.setString(rls);
    sf::FloatRect crashRect = crash.getLocalBounds();
    sf::FloatRect tooManyCarsRect = tooManyCars.getLocalBounds();
    sf::FloatRect scoringRect = scoring.getLocalBounds();
    sf::FloatRect timerRect = timer.getLocalBounds();
    crash.setOrigin(crashRect.left + crashRect.width/2.0f, crashRect.top + crashRect.height/2.0f);
    crash.setCharacterSize(24);
    crash.setStyle(sf::Text::Regular);
    crash.setFillColor(sf::Color::White);
    crash.setPosition(sf::Vector2f(SCRWIDTH/2, SCRHEIGHT/2));
    tooManyCars.setOrigin(tooManyCarsRect.left + tooManyCarsRect.width/2.0f, tooManyCarsRect.top + tooManyCarsRect.height/2.0f);
    tooManyCars.setCharacterSize(24);
    tooManyCars.setStyle(sf::Text::Regular);
    tooManyCars.setFillColor(sf::Color::White);
    tooManyCars.setPosition(sf::Vector2f(SCRWIDTH/2, SCRHEIGHT/2));
    scoreText.setCharacterSize(24);
    scoreText.setStyle(sf::Text::Regular);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(300, 50));
    scoring.setOrigin(scoringRect.left + scoringRect.width/2.0f, scoringRect.top + scoringRect.height/2.0f);
    scoring.setCharacterSize(24);
    scoring.setStyle(sf::Text::Regular);
    scoring.setFillColor(sf::Color::White);
    scoring.setPosition(sf::Vector2f(SCRWIDTH/2, SCRHEIGHT/2));
    timer.setCharacterSize(24);
    timer.setStyle(sf::Text::Regular);
    timer.setFillColor(sf::Color::White);
    timer.setOrigin(timerRect.left + timerRect.width/2.0f, timerRect.top + timerRect.height/2.0f);
    timer.setPosition(sf::Vector2f(SCRWIDTH/2, SCRHEIGHT/2 + 50));
    rulesText.setCharacterSize(14);
    rulesText.setStyle(sf::Text::Regular);
    rulesText.setFillColor(sf::Color::White);
    loss.insert({"crash",crash});
    loss.insert({"too many cars", tooManyCars});
    loss.insert({"low score", scoring});

    while (window.isOpen())
    {
        sf::Event event;
        text.setString("Traffic Simulator 2024\n\n\tPress [R] for Rules\n\n\tPress [Enter] to play");
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
                rules = false;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && start_screen) {
                start_screen = false;
                rules = true;
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
            tooMany = false;
            score = 20;
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
        if (!playing) {
            clock.restart();
            scoreClock.restart();
            total.restart();
        }
        if (playing && !crashed && !tooMany && score > 0) {
            if (cars.size() == 0) {
                Car* c = new Car(RIGHT_LEFT_TURN_RIGHT, sf::Color::Red);
                RL_cars.push_back(c);
                cars.push_back(c);
                cars[0]->drive();
            } 
            if (clock.getElapsedTime().asSeconds() >= 0.5 && cars.size() <= 20) {
                int limit = 7;
                int numTimes = rand();
                Type last = RIGHT_LEFT_STRAIGHT;
                Type lastlast = RIGHT_LEFT_STRAIGHT;
                for (int i = 0; i <= numTimes % 3; i++) {
                    int rand_type = rand();
                    if (i == 1)
                        if (last == Type(0) || last == Type(4)) {
                            while (rand_type % 5 == 0 || rand_type % 5 == 4)
                                rand_type = rand();
                        } else
                            while (rand_type % 5 == last) {
                                rand_type = rand();
                            }
                    else if (i == 2)
                        if (last == Type(0) || last == Type(4) || lastlast == Type(0) || lastlast == Type(4)) {
                            while (rand_type % 5 == 0 || rand_type % 5 == 4 || rand_type % 5 == last || rand_type % 5 == lastlast)
                                rand_type = rand();
                        } else {
                            while (rand_type % 5 == last || rand_type % 5 == lastlast) {
                                rand_type = rand();
                            }
                        }
                    if (rand_type % 5 == 0 && (backedUp(RL_cars) <= limit)) {
                        if (backedUp(RL_cars) >= limit - 1 && !green_light["RL"]) {
                            tooMany = true;
                            std::cout << "RL " << RL_cars.size() << std::endl;
                            break;
                        }
                        Car *c = new Car(RIGHT_LEFT_STRAIGHT, sf::Color::Red);
                        RL_cars.push_back(c);
                        cars.push_back(c);
                        std::cout << "RL " << RL_cars.size() << std::endl;
                        std::cout << "Backed up: " << backedUp(RL_cars) << std::endl;
                        if (i==0)
                            last = Type(rand_type % 5);
                        else if (i==1)
                            lastlast = Type(rand_type % 5);
                    } else if (rand_type % 5 == 1 && (backedUp(LR_cars) <= limit)) {
                        if (backedUp(LR_cars) >= limit - 1 && !green_light["LR"]) {
                            tooMany = true;
                            std::cout << "LR " << LR_cars.size() << std::endl;
                            break;
                        }
                        Car *c = new Car(LEFT_RIGHT_STRAIGHT, sf::Color::Green);
                        LR_cars.push_back(c);
                        cars.push_back(c);
                        std::cout << "spawning LR " << LR_cars.size() << std::endl;
                        std::cout << "Backed up: " << backedUp(LR_cars) << std::endl;
                        if (i==0)
                            last = Type(rand_type % 5);
                        else if (i==1)
                            lastlast = Type(rand_type % 5);
                    } else if (rand_type % 5 == 2 && (backedUp(UD_cars) <= limit)) {
                        if (backedUp(UD_cars) >= limit - 1 && !green_light["UD"]) {
                            tooMany = true;
                            std::cout << "UD" << std::endl;
                            break;
                        }
                        Car *c = new Car(UP_DOWN_STRAIGHT, sf::Color::Yellow);
                        UD_cars.push_back(c);
                        cars.push_back(c);
                        std::cout << rand_type % 5 << " spawned UD " << UD_cars.size() << std::endl;
                        std::cout << "Backed up: " << backedUp(UD_cars) << std::endl;
                        if (i==0)
                            last = Type(rand_type % 5);
                        else if (i==1)
                            lastlast = Type(rand_type % 5);
                    } else if (rand_type % 5 == 3 && (backedUp(DU_cars) <= limit)) {
                        if (backedUp(DU_cars) >= limit - 1 && !green_light["DU"]) {
                            tooMany = true;
                            std::cout << "DU " << DU_cars.size() << std::endl;
                            break;
                        }
                        Car *c = new Car(DOWN_UP_STRAIGHT, sf::Color::Blue);
                        DU_cars.push_back(c);
                        cars.push_back(c);
                        std::cout << "DU " << DU_cars.size() << std::endl;
                        std::cout << "Backed up: " << backedUp(DU_cars) << std::endl;
                        if (i==0)
                            last = Type(rand_type % 5);
                        else if (i==1)
                            lastlast = Type(rand_type % 5);
                    } else if (rand_type % 5 == 4 && (backedUp(RL_cars) <= limit)) {
                        if (backedUp(RL_cars) >= limit - 1 && !green_light["RL"]) {
                            tooMany = true;
                            std::cout << "RL" << std::endl;
                            break;
                        }
                        Car *c = new Car(RIGHT_LEFT_TURN_RIGHT, sf::Color::Blue);
                        RL_cars.push_back(c);
                        cars.push_back(c);
                        std::cout << "RL " << RL_cars.size() << std::endl;
                        if (i==0)
                            last = Type(rand_type % 5);
                        else if (i==1)
                            lastlast = Type(rand_type % 5);
                    }
                }
                std::cout << cars.size() << " " << last << lastlast << std::endl;
                clock.restart();
            }//*/
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
                            && (!car->isAtLight() || green_light["RL"])))
                        || (car->getType() == RIGHT_LEFT_TURN_RIGHT && (!inTraffic(car, RL_cars)
                            && (!car->isAtLight() || green_light["RL"]) && car->x_pos() >= SCRWIDTH/2 + 40)))) {
                        car->drive();
                }
                // if the car is at a red light, offscreen or in traffic, brake.
                else if (car->isAtLight() || car->isOffScreen()
                        || (car->getType() == DOWN_UP_STRAIGHT && (inTraffic(car, DU_cars) || !green_light["DU"]))
                        || (car->getType() == UP_DOWN_STRAIGHT && (inTraffic(car, UD_cars) || !green_light["UD"]))
                        || (car->getType() == LEFT_RIGHT_STRAIGHT && (inTraffic(car, LR_cars) || !green_light["LR"]))
                        || ((car->getType() == RIGHT_LEFT_STRAIGHT || car->getType() == RIGHT_LEFT_TURN_RIGHT) && (inTraffic(car, RL_cars) || !green_light["RL"]))) {
                        car->brake();
                }
                // turn if car needs to turn
                else if (car->getType() == RIGHT_LEFT_TURN_RIGHT && car->x_pos() < SCRHEIGHT/2 + 40) {
                    car->turn(car->getType());
                    if (car->getShape().getRotation() == 90) {
                        car->setType(DOWN_UP_STRAIGHT);
                        DU_cars.push_back(car);
                        for (size_t i = 0; i < RL_cars.size(); i++) {
                            if (RL_cars[i] == car)
                                RL_cars.erase(RL_cars.begin() + i);
                        }
                    }
                }
                for (auto &c:cars) {
                    if (!(c == car) && car->crashed(*c)) {
                        crashed = true;
                        std::cout << "Car crash! " << car->getType() << c->getType() << std::endl;
                        std::cout << car->x_pos() << car->y_pos() << c->x_pos() << c->y_pos() << std::endl;
                        std::cout << car->isNew() << c->isNew() << std::endl;
                        break;
                    }
                }
            }
            for (size_t i = 0; i < cars.size(); i++) {
                if (cars[i]->isOffScreen()) {
                    score++;
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
                            if (*cars[i] == *DU_cars[j])
                                DU_cars.erase(DU_cars.begin() + j);
                        }
                    }
                    delete cars[i];
                    cars.erase(cars.begin() + i);
                }
            }
            if (scoreClock.getElapsedTime().asSeconds() >= 0.28) {
                score--;
                scoreClock.restart();
            }
            scoreText.setString("Score: " + std::to_string(score));
            window.draw(road);
            window.draw(road2);
            window.draw(lane);
            window.draw(lane2);
            window.draw(lane3);
            window.draw(lane4);
            window.draw(square);
            window.draw(scoreText);
            for (Car* car : cars)
                window.draw(car->getShape());
            window.draw(lights["RL"]);
            window.draw(lights["LR"]);
            window.draw(lights["DU"]);
            window.draw(lights["UD"]);
            totalTime = total.getElapsedTime().asSeconds();
            timer.setString("You lasted " + std::to_string(totalTime) + " seconds!");
        } else if (crashed) {
            window.draw(loss["crash"]);
            window.draw(timer);
        } else if (tooMany) {
            window.draw(loss["too many cars"]);
            window.draw(timer);
        } else if (score <= 0) {
            window.draw(loss["low score"]);
            window.draw(timer);
        } else if (rules)
            window.draw(rulesText);
        window.display();
    }

    // uncomment this at your own risk (may cause massive lag and increase exiting timeframe dramatically)
    //Akash_epic_gamer_monkeyballs_function();

    return 0;
}