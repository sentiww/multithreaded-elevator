//
// Created by senti on 4/14/24.
//

#ifndef ELEVATOR_ELEVATOR_H
#define ELEVATOR_ELEVATOR_H

#include "simulation_context.h"

class Elevator {
private:
    std::shared_ptr<SimulationContext> context;
    std::shared_ptr<SimulationState> state;
    std::shared_ptr<SimulationOptions> options;
    Floor next_stop_floor;

    void moveElevator();
    void waitUntilPeopleEnter();
    void stopAtFloor(Floor floor);
    int getFloorPosition(Floor floor);
    void waitUntilPeopleLeave();
    static Floor getNextStopFloor();
    void updateCurrentFloor();

public:
    explicit Elevator(const std::shared_ptr<SimulationContext>& context) {
        this->context = context;
        this->state = context->getState();
        this->options = context->getOptions();
        this->next_stop_floor = getNextStopFloor();
    }

    void run();
};

#endif //ELEVATOR_ELEVATOR_H
