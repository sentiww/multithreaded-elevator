//
// Created by senti on 4/14/24.
//

#include "../include/person.h"
#include <memory>
#include <thread>

Person::Person(int index, std::shared_ptr<SimulationContext> context) {
    x = 0;
    y = 11 + (index % 2);
    symbol = ('A' + index) % 26 + 'A';
    speed = rand() % 20;
    this->context = std::move(context);
    this->index = index;
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
    return x < 19;
}

void Person::walk() {
    x++;
    std::this_thread::sleep_for(std::chrono::milliseconds(100 * speed));
}

bool Person::waitingForElevator() {
    return x == 19 && context->getState()->getCurrentFloor() != Floor::Zero;
}

void Person::waitForElevator() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

bool Person::isReadyToEnterElevator() {
    return x == 19 && context->getState()->getCurrentFloor() == Floor::Zero;
}

void Person::enterElevator() {
    context->getState()->addToElevator(shared_from_this());
    setIsReadyToRide(false);
    int initial_x = x;
    while (x < initial_x + 2 + rand() % 2 && !context->getState()->getStopRequested()) {
        walk();
    }
    setIsReadyToRide(true);
}

void Person::waitForNextFloor() {
    while (atZeroOrNoneFloor() && !context->getState()->getStopRequested()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

bool Person::atZeroOrNoneFloor() const {
    return context->getState()->getCurrentFloor() == Floor::Zero || context->getState()->getCurrentFloor() == Floor::None;
}

bool Person::walkingFromElevator() const {
    return x > 19 && x < 40;
}

bool Person::leftElevator() const {
    return x == 23;
}

bool Person::isAtServiceDesk() const {
    return x == 30;
}

void Person::waitAtServiceDesk() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void Person::run() {
    auto state = context->getState();
    while (!state->getStopRequested()) {
        context->getWindow()->draw();
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
