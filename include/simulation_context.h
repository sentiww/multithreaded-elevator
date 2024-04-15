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

class SimulationState;
class Window;

class SimulationContext : public std::enable_shared_from_this<SimulationContext> {
private:
    std::unique_ptr<SimulationOptions> options;
    std::shared_ptr<SimulationState> state;
    std::shared_ptr<Window> window;

    std::vector<std::thread> people_threads;
    std::thread elevator_thread;

    void create_people_threads();
    void create_elevator_thread();
    void join_threads();

public:
    SimulationContext(std::unique_ptr<SimulationOptions> options);

    void run();

    std::shared_ptr<SimulationState> getState() {
        return state;
    }

    std::shared_ptr<Window> getWindow() {
        return window;
    }
};

#endif //ELEVATOR_SIMULATION_CONTEXT_H
