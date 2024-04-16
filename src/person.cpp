//
// Created by senti on 4/14/24.
//

#include "../include/person.h"
#include <memory>
#include <thread>

Person::Person(int index, std::shared_ptr<SimulationContext> context) {
    this->context = std::move(context);
    this->state = this->context->getState();
    this->options = this->context->getOptions();
    this->index = index;
    this->x = 0;
    this->y = 11 + (index % this->options->getCorridorWidth());
    this->symbol = ('A' + index) % 26 + 'A';
    this->speed = rand() % 20;
}

Person& Person::setY(int y) {
    this->y = y;
    return *this;
}
int Person::getY() const {
    return y;
}

Person& Person::setX(int x) {
    this->x = x;
    return *this;
}
int Person::getX() const {
    return x;
}

Person& Person::setSymbol(char symbol) {
    this->symbol = symbol;
    return *this;
}
char Person::getSymbol() const {
    return symbol;
}

Person& Person::setIsReadyToRide(bool is_ready_to_ride) {
    this->is_ready_to_ride = is_ready_to_ride;
    return *this;
}
bool Person::getIsReadyToRide() const {
    return is_ready_to_ride;
}

int Person::getIndex() const {
    return index;
}

bool Person::walkingToElevator() const {
    return x < options->getLeftCorridorLength() - 1;
}

void Person::walk() {
    x++;
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * speed));
}

bool Person::waitingForElevator() {
    return x == options->getLeftCorridorLength() - 1 && state->getCurrentFloor() != Floor::Zero;
}

void Person::waitForElevator() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

bool Person::isReadyToEnterElevator() {
    const int elevatorDoorWidth = 1;
    return x == options->getLeftCorridorLength() - elevatorDoorWidth && state->getCurrentFloor() == Floor::Zero;
}

void Person::enterElevator() {
    state->addToElevator(shared_from_this());
    setIsReadyToRide(false);
    int initial_x = x;
    while (x < initial_x + 2 + rand() % options->getCorridorWidth() && !state->getStopRequested()) {
        walk();
    }
    setIsReadyToRide(true);
}

void Person::waitForNextFloor() {
    while (atZeroOrNoneFloor() && !state->getStopRequested()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

bool Person::atZeroOrNoneFloor() const {
    return state->getCurrentFloor() == Floor::Zero || state->getCurrentFloor() == Floor::None;
}

bool Person::walkingFromElevator() const {
    const int elevatorDoorWidth = 1;
    return x > options->getLeftCorridorLength() - elevatorDoorWidth && x < options->getPersonDespawnX();
}

bool Person::leftElevator() const {
    const int elevatorDoorsWidth = 2;
    return x == options->getLeftCorridorLength() + elevatorDoorsWidth + options->getCorridorWidth();
}

bool Person::isAtServiceDesk() const {
    return x == options->getServiceDeskX();
}

void Person::waitAtServiceDesk() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Person::run() {
    while (!state->getStopRequested()) {
        if (walkingToElevator()) {
            walk();
        }
        else if (waitingForElevator()) {
            waitForElevator();
        }
        else if (isReadyToEnterElevator()) {
            enterElevator();
            waitForNextFloor();
        }
        else if (walkingFromElevator()) {
            walk();
            if (leftElevator()) {
                state->removeFromElevator(shared_from_this());
            }
        }
        else {
            state->removePerson(shared_from_this());
            break;
        }

        if (isAtServiceDesk()) {
            waitAtServiceDesk();
        }
    }
}
