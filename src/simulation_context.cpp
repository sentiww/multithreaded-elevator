//
// Created by senti on 4/6/24.
//

#include "../include/simulation_context.h"
#include "../include/elevator.h"
#include <memory>
#include <utility>
#include <mutex>

SimulationContext::SimulationContext(std::shared_ptr<SimulationOptions> options) {
    this->options = std::move(options);
    this->state = std::make_shared<SimulationState>();
    this->state->setElevatorX(this->options->getLeftCorridorLength())
          .setElevatorY(this->options->getElevatorStartY())
          .setPeopleThreadsJoined(false)
          .setFloorPosition(Floor::Zero, 10)
          .setFloorPosition(Floor::First, 20)
          .setFloorPosition(Floor::Second, 30)
          .setFloorPosition(Floor::Third, 40);
    for (auto floor = 1; floor <= 3; floor++) {
        this->service_desk_mutexes[static_cast<Floor>(floor)] = std::map<int, std::shared_ptr<std::mutex>>();
        for (auto lane = 0; lane < this->options->getCorridorWidth(); lane++) {
            this->service_desk_mutexes[static_cast<Floor>(floor)][lane] = std::make_shared<std::mutex>();
        }
    }
    this->window = std::make_shared<Window>(this->state, this->options);
    this->window->startUiThread();
}

void SimulationContext::run() {
    createElevatorThread();
    createPeopleThreads();
    joinThreads();
}

void SimulationContext::createPeopleThreads() {
    for (int i = 0; !this->state->getStopRequested(); i++) {
        std::shared_ptr<Person> person = std::make_shared<Person>(i, shared_from_this());
        state->addPerson(person);
        std::thread thread([person]() {
            person->run();
        });
        people_threads.push_back(std::move(thread));
        std::this_thread::sleep_for(std::chrono::milliseconds (rand() % 5000));
    }
}

void SimulationContext::createElevatorThread() {
    elevator_thread = std::thread([this]() {
        Elevator elevator(shared_from_this());
        elevator.run();
    });
}

void SimulationContext::joinThreads() {
    for (auto &thread : people_threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    state->setPeopleThreadsJoined(true);

    if (elevator_thread.joinable()) {
        elevator_thread.join();
    }

    window->joinUiThread();
}