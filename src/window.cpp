//
// Created by senti on 4/6/24.
//

#include "../include/window.h"
#include <ncurses.h>

Window::Window(std::shared_ptr<SimulationState> state, std::shared_ptr<SimulationOptions> options) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    setlocale(LC_ALL, "");
    clear();

    this->state = std::move(state);
    this->options = std::move(options);
    this->input_thread = std::thread([this]() {
        inputThreadWork();
    });
}

void Window::inputThreadWork() {
    while (true) {
        int input = getch();
        if (input == ' ') {
            break;
        }
    }
    state->requestStop();
}

void Window::uiThreadWork() {
    while (!state->getStopRequested()) {
        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    if (input_thread.joinable()) {
        input_thread.join();
    }
    endwin();
}

void Window::drawCorridor(int y, int x, int length) const {
    for (int i = 0; i < length; i++) {
        mvaddch(y, x + i, '#');
        mvaddch(y + options->getCorridorWidth() + 1, x + i, '#');
    }
}

void Window::drawElevatorShaft(int y, int x, int height, Floor floor) const {
    int floor_position = -1;
    switch (floor) {
        case Floor::Zero:
            floor_position = 10;
            break;
        case Floor::First:
            floor_position = 20;
            break;
        case Floor::Second:
            floor_position = 30;
            break;
        case Floor::Third:
            floor_position = 40;
            break;
        case Floor::None:
            break;
    }

    int corridor_width = options->getCorridorWidth();
    for (int i = 0; i < height; i++) {
        if (floor == Floor::Zero && floor_position <= i - 1 && i <= floor_position + corridor_width) {
            mvaddch(y + i, x + corridor_width + 1, '#');
        }
        else if (floor != Floor::None && floor_position <= i - 1 && i <= floor_position + corridor_width) {
            mvaddch(y + i, x, '#');
        }
        else {
            mvaddch(y + i, x, '#');
            mvaddch(y + i, x + corridor_width + 1, '#');
        }
    }
}

void Window::drawElevator(int y, int x) const {
    int corridor_width = options->getCorridorWidth();
    for (int i = 1; i < corridor_width + 1; i++) {
        mvaddch(y, x + i, '#');
        mvaddch(y + corridor_width + 1, x + i, '#');
    }
}

void Window::drawPerson(int y, int x, char symbol) {
    mvaddch(y, x, symbol);
}

void Window::draw() {
    int corridor_width = options->getCorridorWidth();
    clear();
    drawCorridor(10, 0, options->getLeftCorridorLength());
    drawElevatorShaft(0, options->getLeftCorridorLength(), 50 + corridor_width + 2, state->getCurrentFloor());
    drawCorridor(20, options->getLeftCorridorLength() + corridor_width + 1, options->getRightCorridorLength());
    drawCorridor(30, options->getLeftCorridorLength() + corridor_width + 1, options->getRightCorridorLength());
    drawCorridor(40, options->getLeftCorridorLength() + corridor_width + 1, options->getRightCorridorLength());
    drawElevator(state->getElevatorY(), state->getElevatorX());
    for (const std::shared_ptr<Person>& person : state->getPeople()) {
        drawPerson(person->getY(), person->getX(), person->getSymbol());
    }
    refresh();
}

void Window::startUiThread() {
    if (ui_thread.joinable()) {
        return;
    }

    ui_thread = std::thread([this]() {
        uiThreadWork();
    });
}

void Window::joinUiThread() {
    if (ui_thread.joinable()) {
        ui_thread.join();
    }
}