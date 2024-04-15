//
// Created by senti on 4/15/24.
//

#include "../include/simulation_state.h"

SimulationState& SimulationState::setElevatorPresent(bool elevator_present) {
    this->elevator_present = elevator_present;
    return *this;
}
bool SimulationState::getElevatorPresent() const {
    return elevator_present;
}

SimulationState& SimulationState::setPeopleThreadsJoined(bool people_threads_joined) {
    this->people_threads_joined = people_threads_joined;
    return *this;
}
bool SimulationState::getPeopleThreadsJoined() const {
    return people_threads_joined;
}

SimulationState& SimulationState::setCurrentFloor(Floor current_floor) {
    this->current_floor = current_floor;
    return *this;
}
Floor SimulationState::getCurrentFloor() const {
    return current_floor;
}

SimulationState& SimulationState::setElevatorY(int y) {
    elevator_y = y;
    return *this;
}
int SimulationState::getElevatorY() const {
    return elevator_y;
}

SimulationState& SimulationState::setElevatorX(int x) {
    elevator_x = x;
    return *this;
}
int SimulationState::getElevatorX() const {
    return elevator_x;
}

SimulationState& SimulationState::addPerson(const std::shared_ptr<Person>& person) {
    people.push_back(person);
    return *this;
}
std::vector<std::shared_ptr<Person>> SimulationState::getPeople() const {
    return people;
}
void SimulationState::removePerson(const std::shared_ptr<Person>& person) {
    for (int i = 0; i < people.size(); i++) {
        if (people[i]->getIndex() == person->getIndex()) {
            people.erase(people.begin() + i);
            break;
        }
    }
}

SimulationState& SimulationState::addToElevator(const std::shared_ptr<Person>& person) {
    people_in_elevator.push_back(person);
    return *this;
}
std::vector<std::shared_ptr<Person>> SimulationState::getPeopleInElevator() const {
    return people_in_elevator;
}
void SimulationState::removeFromElevator(const std::shared_ptr<Person>& person) {
    for (int i = 0; i < people_in_elevator.size(); i++) {
        if (people_in_elevator[i]->getIndex() == person->getIndex()) {
            people_in_elevator.erase(people_in_elevator.begin() + i);
            break;
        }
    }
}

bool SimulationState::getStopRequested() {
    return stop_source.get_token()
                      .stop_requested();
}

void SimulationState::requestStop() {
    stop_source.request_stop();
}