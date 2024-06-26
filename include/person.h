//
// Created by senti on 4/13/24.
//

#ifndef ELEVATOR_PERSON_H
#define ELEVATOR_PERSON_H

#include <memory>
#include "simulation_context.h"

class SimulationContext;
class SimulationState;

class Person : public std::enable_shared_from_this<Person> {
private:
    int y;
    int x;
    int speed;
    char symbol;
    bool is_ready_to_ride = false;
    std::shared_ptr<SimulationContext> context;
    std::shared_ptr<SimulationState> state;
    std::shared_ptr<SimulationOptions> options;
    int index;

    bool walkingToElevator() const;
    void walk();
    bool waitingForElevator();
    static void waitForElevator();
    bool isReadyToEnterElevator();
    void enterElevator();
    void waitForNextFloor();
    bool atZeroOrNoneFloor() const;
    bool walkingFromElevator() const;
    bool leftElevator() const;
    bool isAtServiceDesk() const;
    static void waitAtServiceDesk();
    Floor getFloor() const;

public:
    Person(int index, std::shared_ptr<SimulationContext> context);
    void run();

    Person& setY(int y);
    int getY() const;

    Person& setX(int x);
    int getX() const;

    Person& setSymbol(char symbol);
    char getSymbol() const;

    Person& setIsReadyToRide(bool is_ready_to_ride);
    bool getIsReadyToRide() const;

    int getIndex() const;
};

#endif //ELEVATOR_PERSON_H
