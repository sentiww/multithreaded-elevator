//
// Created by senti on 4/6/24.
//

#ifndef ELEVATOR_SIMULATION_OPTIONS_H
#define ELEVATOR_SIMULATION_OPTIONS_H

class SimulationOptions {
private:
    int elevatorSpeed;
    int elevatorStartY;
    int elevatorEndY;
    int elevatorStopTime;
    int personDespawnX;
    int serviceDeskX;
    int leftCorridorLength;
    int rightCorridorLength;
    int corridorWidth;

public:
    SimulationOptions& setElevatorSpeed(int speed) {
        elevatorSpeed = speed;
        return *this;
    }
    [[nodiscard]] int getElevatorSpeed() const {
        return elevatorSpeed;
    }

    SimulationOptions& setElevatorStartY(int y) {
        elevatorStartY = y;
        return *this;
    }
    [[nodiscard]] int getElevatorStartY() const {
        return elevatorStartY;
    }

    SimulationOptions& setElevatorEndY(int y) {
        elevatorEndY = y;
        return *this;
    }
    [[nodiscard]] int getElevatorEndY() const {
        return elevatorEndY;
    }

    SimulationOptions& setElevatorStopTime(int time) {
        elevatorStopTime = time;
        return *this;
    }
    [[nodiscard]] int getElevatorStopTime() const {
        return elevatorStopTime;
    }

    SimulationOptions& setPersonDespawnX(int x) {
        personDespawnX = x;
        return *this;
    }
    [[nodiscard]] int getPersonDespawnX() const {
        return personDespawnX;
    }

    SimulationOptions& setServiceDeskX(int x) {
        serviceDeskX = x;
        return *this;
    }
    [[nodiscard]] int getServiceDeskX() const {
        return serviceDeskX;
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

    SimulationOptions& setCorridorWidth(int width) {
        corridorWidth = width;
        return *this;
    }
    [[nodiscard]] int getCorridorWidth() const {
        return corridorWidth;
    }
};

#endif //ELEVATOR_SIMULATION_OPTIONS_H
