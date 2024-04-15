//
// Created by senti on 4/6/24.
//

#ifndef ELEVATOR_SIMULATION_OPTIONS_H
#define ELEVATOR_SIMULATION_OPTIONS_H

class SimulationOptions {
private:
    double minElevatorSpeed;
    double maxElevatorSpeed;
    double minPersonSpeed;
    double maxPersonSpeed;
    int leftCorridorLength;
    int rightCorridorLength;
    int elevatorHeight;

public:
    SimulationOptions& setMinElevatorSpeed(double speed){
        minElevatorSpeed = speed;
        return *this;
    }
    [[nodiscard]] double getMinElevatorSpeed() const {
        return minElevatorSpeed;
    }

    SimulationOptions& setMaxElevatorSpeed(double speed) {
        maxElevatorSpeed = speed;
        return *this;
    }
    [[nodiscard]] double getMaxElevatorSpeed() const {
        return maxElevatorSpeed;
    }

    SimulationOptions& setMinPersonSpeed(double speed) {
        minPersonSpeed = speed;
        return *this;
    }
    [[nodiscard]] double getMinPersonSpeed() const {
        return minPersonSpeed;
    }

    SimulationOptions& setMaxPersonSpeed(double speed) {
        maxPersonSpeed = speed;
        return *this;
    }
    [[nodiscard]] double getMaxPersonSpeed() const {
        return maxPersonSpeed;
    }

    SimulationOptions& setLeftCorridorLength(int length) {
        leftCorridorLength = length;
        return *this;
    }
    [[nodiscard]] int getLeftCorridorLength() const {
        return leftCorridorLength;
    }

    SimulationOptions& setRightCorridorLength(int length) {
        rightCorridorLength = length;
        return *this;
    }
    [[nodiscard]] int getRightCorridorLength() const {
        return rightCorridorLength;
    }

    SimulationOptions& setElevatorHeight(int height) {
        elevatorHeight = height;
        return *this;
    }
    [[nodiscard]] int getElevatorHeight() const {
        return elevatorHeight;
    }
};

#endif //ELEVATOR_SIMULATION_OPTIONS_H
