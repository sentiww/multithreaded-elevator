//
// Created by senti on 4/14/24.
//

#include "../include/elevator.h"

void Elevator::move_elevator() {
    state->setElevatorY(state->getElevatorY() + 1);
    for (const std::shared_ptr<Person>& person : state->getPeopleInElevator()) {
        person->setY(person->getY() + 1);
    }
}

void Elevator::wait_until_people_enter() {
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

void Elevator::stop_at_floor(Floor floor) {
    int floor_position = get_floor_position(floor);
    if (state->getElevatorY() == floor_position) {
        state->setCurrentFloor(floor);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int Elevator::get_floor_position(Floor floor) {
    switch (floor) {
        case Floor::Zero:
            return floor_positions[0];
        case Floor::First:
            return floor_positions[1];
        case Floor::Second:
            return floor_positions[2];
        case Floor::Third:
            return floor_positions[3];
        case Floor::None:
            break;
    }
    return -1;
}

void Elevator::wait_until_people_leave() {
    while (!state->getPeopleInElevator().empty() && !state->getStopRequested()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

Floor Elevator::get_next_stop_floor() {
    return static_cast<Floor>(rand() % 2 + 1);
}

void Elevator::update_current_floor() {
    int elevator_y = context->getState()->getElevatorY();
    if (elevator_y == floor_positions[0]) {
        state->setCurrentFloor(Floor::Zero);
    }
    else if (elevator_y == floor_positions[1]) {
        state->setCurrentFloor(Floor::First);
    }
    else if (elevator_y == floor_positions[2]) {
        state->setCurrentFloor(Floor::Second);
    }
    else if (elevator_y == floor_positions[3]) {
        state->setCurrentFloor(Floor::Third);
    }
    else {
        state->setCurrentFloor(Floor::None);
    }
}

void Elevator::run() {
    std::shared_ptr<Window> window = context->getWindow();
    while (!state->getPeopleThreadsJoined() && !state->getStopRequested()) {
        window->draw();

        move_elevator();
        update_current_floor();

        Floor current_floor = state->getCurrentFloor();

        if (current_floor == Floor::Zero) {
            stop_at_floor(Floor::Zero);
            state->setCurrentFloor(Floor::None);
            wait_until_people_enter();
        }
        else if (current_floor == next_stop_floor) {
            stop_at_floor(next_stop_floor);
            wait_until_people_leave();
        }

        state->setCurrentFloor(Floor::None);

        if (state->getElevatorY() > 50) {
            state->setElevatorY(0);
            next_stop_floor = get_next_stop_floor();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds (250));
    }
}