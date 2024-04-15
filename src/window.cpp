//
// Created by senti on 4/6/24.
//

#include "../include/window.h"
#include <ncurses.h>

Window::Window(std::shared_ptr<SimulationState> state) {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    setlocale(LC_ALL, "");
    clear();

    this->state = std::move(state);
    this->input_thread = std::thread([this]() {
        input_thread_work();
    });
    this->input_thread.detach();
}

void Window::input_thread_work() {
    while (true) {
        int input = getch();
        if (input == ' ') {
            break;
        }
    }
    state->requestStop();
    curs_set(1);
    clear();
    endwin();
    refresh();
}

void Window::draw_corridor(int y, int x, int length) const {
    for (int i = 0; i < length; i++) {
        mvaddch(y, x + i, '#');
        mvaddch(y + CORRIDOR_WIDTH + 1, x + i, '#');
    }
}

void Window::draw_elevator_shaft(int y, int x, int height, Floor floor) const {
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

    for (int i = 0; i < height; i++) {
        if (floor == Floor::Zero && floor_position <= i - 1 && i <= floor_position + CORRIDOR_WIDTH) {
            mvaddch(y + i, x + CORRIDOR_WIDTH + 1, '#');
        }
        else if (floor != Floor::None && floor_position <= i - 1 && i <= floor_position + CORRIDOR_WIDTH) {
            mvaddch(y + i, x, '#');
        }
        else {
            mvaddch(y + i, x, '#');
            mvaddch(y + i, x + CORRIDOR_WIDTH + 1, '#');
        }
    }
}

void Window::draw_elevator(int y, int x) const {
    for (int i = 1; i < CORRIDOR_WIDTH + 1; i++) {
        mvaddch(y, x + i, '#');
        mvaddch(y + CORRIDOR_WIDTH + 1, x + i, '#');
    }
}

void Window::draw_person(int y, int x, char symbol) {
    mvaddch(y, x, symbol);
}

void Window::draw() {
    mutex.lock();

    clear();
    draw_corridor(10, 0, 20);
    draw_elevator_shaft(0, 20, 50 + CORRIDOR_WIDTH + 2, state->getCurrentFloor());
    draw_corridor(20, 20 + CORRIDOR_WIDTH + 1, 20);
    draw_corridor(30, 20 + CORRIDOR_WIDTH + 1, 20);
    draw_corridor(40, 20 + CORRIDOR_WIDTH + 1, 20);
    draw_elevator(state->getElevatorY(), state->getElevatorX());
    for (const std::shared_ptr<Person>& person : state->getPeople()) {
        draw_person(person->getY(), person->getX(), person->getSymbol());
    }
    refresh();

    mutex.unlock();
}
