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
    std::shared_ptr<SimulationState> state;
    std::shared_ptr<SimulationOptions> options;
    std::thread input_thread;
    std::thread ui_thread;

    void inputThreadWork();
    void uiThreadWork();

    void drawCorridor(int y, int x, int length) const;
    void drawElevatorShaft(int y, int x, int height, Floor floor) const;
    void drawElevator(int y, int x) const;
    static void drawPerson(int y, int x, char symbol);

    void draw();

public:
    explicit Window(std::shared_ptr<SimulationState> state, std::shared_ptr<SimulationOptions> options);

    void startUiThread();
    void joinUiThread();
};

#endif //ELEVATOR_WINDOW_H
