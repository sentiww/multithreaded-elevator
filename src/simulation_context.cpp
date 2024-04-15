//
// Created by senti on 4/6/24.
//

#include "../include/simulation_context.h"
#include "../include/elevator.h"
#include <memory>

SimulationContext::SimulationContext(std::unique_ptr<SimulationOptions> options) {
    this->options = std::move(options);
    this->state = std::make_unique<SimulationState>();
    state->setElevatorPresent(false)
          .setElevatorX(20)
          .setElevatorY(0)
          .setPeopleThreadsJoined(false);
    this->window = std::make_shared<Window>(state);
}

void SimulationContext::run() {
    create_elevator_thread();
    create_people_threads();
    join_threads();
}

void SimulationContext::create_people_threads() {
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

void SimulationContext::create_elevator_thread() {
    elevator_thread = std::thread([this]() {
        Elevator elevator(shared_from_this());
        elevator.run();
    });
}

void SimulationContext::join_threads() {
    for (auto &thread : people_threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    state->setPeopleThreadsJoined(true);

    if (elevator_thread.joinable()) {
        elevator_thread.join();
    }
}