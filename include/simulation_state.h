//
// Created by senti on 4/14/24.
//

#ifndef ELEVATOR_SIMULATION_STATE_H
#define ELEVATOR_SIMULATION_STATE_H

#include "floor.h"
#include "person.h"
#include <vector>
#include <memory>
#include <thread>

class Person;

class SimulationState {
private:
    bool people_threads_joined = false;
    Floor current_floor = Floor::None;
    int floor_positions[4];
    int elevator_y;
    int elevator_x;
    std::vector<std::shared_ptr<Person>> people = std::vector<std::shared_ptr<Person>>();
    std::vector<std::shared_ptr<Person>> people_in_elevator = std::vector<std::shared_ptr<Person>>();
    std::stop_source stop_source = std::stop_source();

public:
    SimulationState& setPeopleThreadsJoined(bool people_threads_joined);
    [[nodiscard]] bool getPeopleThreadsJoined() const;

    SimulationState& setCurrentFloor(Floor current_floor);
    [[nodiscard]] Floor getCurrentFloor() const;

    SimulationState& setFloorPosition(Floor floor, int position);
    [[nodiscard]] int getFloorPosition(Floor floor) const;

    SimulationState& setElevatorY(int y);
    [[nodiscard]] int getElevatorY() const;

    SimulationState& setElevatorX(int x);
    [[nodiscard]] int getElevatorX() const;

    SimulationState& addPerson(const std::shared_ptr<Person>& person);
    [[nodiscard]] std::vector<std::shared_ptr<Person>> getPeople() const;
    void removePerson(const std::shared_ptr<Person>& person);

    SimulationState& addToElevator(const std::shared_ptr<Person>& person);
    [[nodiscard]] std::vector<std::shared_ptr<Person>> getPeopleInElevator() const;
    void removeFromElevator(const std::shared_ptr<Person>& person);

    bool getStopRequested();
    void requestStop();
};

#endif //ELEVATOR_SIMULATION_STATE_H
