#include "include/simulation_context.h"

int main() {
    std::shared_ptr<SimulationOptions> options = std::make_shared<SimulationOptions>();
    options->setElevatorSpeed(150)
            .setElevatorStartY(0)
            .setElevatorEndY(50)
            .setElevatorStopTime(1)
            .setPersonDespawnX(50)
            .setServiceDeskX(45)
            .setLeftCorridorLength(20)
            .setRightCorridorLength(30)
            .setCorridorWidth(3);

    std::shared_ptr<SimulationContext> context = std::make_shared<SimulationContext>(std::move(options));
    context->run();

    return 0;
}