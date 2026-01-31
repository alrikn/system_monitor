
#ifndef INCLUDED_BASICNCURSES_HPP
    #define INCLUDED_BASICNCURSES_HPP

#include <iostream>
#include "IDisplay.hpp"
#include <ncurses.h>
#include <vector>
#include <memory>

class BasicNcurses : public IDisplay {
    private:
        bool _running;

    public:
        BasicNcurses() : _running(true) {}

        virtual ~BasicNcurses() = default;

        void init() override {
            //the default stuff copied from my_top
            initscr();
            clear();
            noecho();
            curs_set(0);

            printw("NCURSES DISPLAY\n");
            printw("Press 'q' to quit\n\n");
            refresh();
        }

        void cleanup() override {
            endwin();
        }

        void update(const std::vector<std::shared_ptr<Imodule>>& modules) override {
            clear();
            printw("=== System Monitor ===\n\n");

            //for all the modules
            for (const auto& module : modules) {
                //we print the name first
                printw("--- %s ---\n", module->name().c_str());

                //printing all the lines of the module
                for (const auto& line : module->lines()) {
                    printw("  %s\n", line.c_str());
                }

                printw("\n");
            }
            printw("\nPress 'q' to quit\n");
            refresh();
        }

        bool isRunning() const override {
            return _running;
        }

        std::string getName() const override {
            return "BasicNcurses";
        }

        //we just chekin for q key
        void handleEvents() override {
            // Check for 'q' key
            timeout(0);// Non-blocking check
            int ch = getch();

            if (ch == 'q' || ch == 'Q') {
                _running = false;
            }
            timeout(1000);
        }
};

#endif

