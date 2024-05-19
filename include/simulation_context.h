//
// Created by senti on 4/6/24.
//

#ifndef ELEVATOR_SIMULATION_CONTEXT_H
#define ELEVATOR_SIMULATION_CONTEXT_H

#include "simulation_options.h"
#include "simulation_state.h"
#include "window.h"
#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <map>

class SimulationState;
class Window;

class SimulationContext : public std::enable_shared_from_this<SimulationContext> {
private:
    std::shared_ptr<SimulationOptions> options;
    std::shared_ptr<SimulationState> state;
    std::shared_ptr<Window> window;

    std::vector<std::thread> people_threads;
    std::thread elevator_thread;
    std::map<Floor, std::map<int, std::shared_ptr<std::mutex>>> service_desk_mutexes;

    void createPeopleThreads();
    void createElevatorThread();
    void joinThreads();

public:
    explicit SimulationContext(std::shared_ptr<SimulationOptions> options);

    void run();

    std::shared_ptr<SimulationState> getState() {
        return state;
    }

    std::shared_ptr<SimulationOptions> getOptions() {
        return options;
    }

    std::shared_ptr<std::mutex> getServiceDeskMutex(Floor floor, int lane) {
        return service_desk_mutexes[floor][lane];
    }
};

#endif //ELEVATOR_SIMULATION_CONTEXT_H
