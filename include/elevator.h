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
    Floor next_stop_floor;
    int floor_positions[4] = { 10, 20, 30, 40 };

    void move_elevator();
    void wait_until_people_enter();
    void stop_at_floor(Floor floor);
    int get_floor_position(Floor floor);
    void wait_until_people_leave();
    static Floor get_next_stop_floor();
    void update_current_floor();

public:
    explicit Elevator(const std::shared_ptr<SimulationContext>& context) {
        this->context = context;
        this->state = context->getState();
        this->next_stop_floor = get_next_stop_floor();
    }

    void run();
};

#endif //ELEVATOR_ELEVATOR_H
