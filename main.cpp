#include "include/simulation_context.h"

int main() {
    std::unique_ptr<SimulationOptions> options = std::make_unique<SimulationOptions>();
    options->setMinElevatorSpeed(1.0)
            .setMaxElevatorSpeed(2.0)
            .setMinPersonSpeed(1.0)
            .setMaxPersonSpeed(2.0)
            .setLeftCorridorLength(20)
            .setRightCorridorLength(10)
            .setElevatorHeight(10);

    std::shared_ptr<SimulationContext> context = std::make_shared<SimulationContext>(std::move(options));
    context->run();

    return 0;
}