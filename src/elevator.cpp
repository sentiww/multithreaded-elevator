//
// Created by senti on 4/14/24.
//

#include "../include/elevator.h"

void Elevator::moveElevator() {
    state->setElevatorY(state->getElevatorY() + 1);
    for (const std::shared_ptr<Person>& person : state->getPeopleInElevator()) {
        person->setY(person->getY() + 1);
    }
}

void Elevator::waitUntilPeopleEnter() {
    while (!state->getPeopleThreadsJoined() && !state->getStopRequested()) {
        std::vector<std::shared_ptr<Person>> people = state->getPeopleInElevator();
        bool ready = true;
        for (const std::shared_ptr<Person>& person : people) {
            if (!person->getIsReadyToRide()) {
                ready = false;
                break;
            }
        }
        if (ready) {
            break;
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

void Elevator::stopAtFloor(Floor floor) {
    int floor_position = getFloorPosition(floor);
    if (state->getElevatorY() == floor_position) {
        state->setCurrentFloor(floor);
        std::this_thread::sleep_for(std::chrono::seconds(options->getElevatorStopTime()));
    }
}

int Elevator::getFloorPosition(Floor floor) {
    switch (floor) {
        case Floor::Zero:
            return state->getFloorPosition(Floor::Zero);
        case Floor::First:
            return state->getFloorPosition(Floor::First);
        case Floor::Second:
            return state->getFloorPosition(Floor::Second);
        case Floor::Third:
            return state->getFloorPosition(Floor::Third);
        case Floor::None:
            break;
    }
    return -1;
}

void Elevator::waitUntilPeopleLeave() {
    while (!state->getPeopleInElevator().empty() && !state->getStopRequested()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

Floor Elevator::getNextStopFloor() {
    return static_cast<Floor>(rand() % 3 + 1);
}

void Elevator::updateCurrentFloor() {
    int elevator_y = state->getElevatorY();
    if (elevator_y == state->getFloorPosition(Floor::Zero)) {
        state->setCurrentFloor(Floor::Zero);
    }
    else if (elevator_y == state->getFloorPosition(Floor::First)) {
        state->setCurrentFloor(Floor::First);
    }
    else if (elevator_y == state->getFloorPosition(Floor::Second)) {
        state->setCurrentFloor(Floor::Second);
    }
    else if (elevator_y == state->getFloorPosition(Floor::Third)) {
        state->setCurrentFloor(Floor::Third);
    }
    else {
        state->setCurrentFloor(Floor::None);
    }
}

void Elevator::run() {
    while (!state->getPeopleThreadsJoined() && !state->getStopRequested()) {
        moveElevator();
        updateCurrentFloor();

        Floor current_floor = state->getCurrentFloor();

        if (current_floor == Floor::Zero) {
            stopAtFloor(Floor::Zero);
            state->setCurrentFloor(Floor::None);
            waitUntilPeopleEnter();
        }
        else if (current_floor == next_stop_floor) {
            stopAtFloor(next_stop_floor);
            waitUntilPeopleLeave();
        }

        state->setCurrentFloor(Floor::None);

        if (state->getElevatorY() > options->getElevatorEndY()) {
            state->setElevatorY(options->getElevatorStartY());
            next_stop_floor = getNextStopFloor();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds (options->getElevatorSpeed()));
    }
}