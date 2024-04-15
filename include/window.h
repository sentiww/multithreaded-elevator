//
// Created by senti on 4/6/24.
//

#ifndef ELEVATOR_WINDOW_H
#define ELEVATOR_WINDOW_H

#include <thread>
#include <memory>
#include "simulation_state.h"

class SimulationContext;
class SimulationState;

class Window {
private:
    const int CORRIDOR_WIDTH = 2;
    std::mutex mutex = std::mutex();
    std::shared_ptr<SimulationState> state;
    std::thread input_thread;

    void input_thread_work();

public:
    explicit Window(std::shared_ptr<SimulationState> state);

    void draw_corridor(int y, int x, int length) const;
    void draw_elevator_shaft(int y, int x, int height, Floor floor) const;
    void draw_elevator(int y, int x) const;
    static void draw_person(int y, int x, char symbol);

    void draw();
};

#endif //ELEVATOR_WINDOW_H
