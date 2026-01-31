
#ifndef INCLUDED_BASICNCURSES_HPP
    #define INCLUDED_BASICNCURSES_HPP

#include <ncurses.h>
#include <vector>
#include <memory>
#include <unistd.h>
#include "IDisplay.hpp"

namespace Krell {

class BasicNcurses : public Krell::IDisplay::Window {
    private:
        bool _running;

    public:
        BasicNcurses() : _running(true) {}

        virtual ~BasicNcurses() = default;

        // create/init ncurses
        void create() override {
            initscr();
            clear();
            noecho();
            curs_set(0);
        }

        // destroy/cleanup ncurses
        void destroy() override {
            endwin();
        }

        // check if window is running
        bool isRunning() const override {
            return _running;
        }

        // clear screen
        void clear() override {
            ::clear();  // Call ncurses clear
        }

        // render/display
        void display() override {
            refresh();
        }

        // update display with modules
        void update(const std::vector<std::shared_ptr<IModule>>& modules) {
            ::clear();
            printw("=== System Monitor ===\n\n");

            // render all modules
            for (const auto& module : modules) {
                printw("--- %s ---\n", module->get_name().c_str());
                printw("  %s\n", module->get_string().c_str());
                printw("\n");
            }

            printw("\nPress 'q' to quit | Ctrl+C to exit\n");
            refresh();
        }

        // input events
        void handleEvents() override {
            timeout(0);  // non blocking input
            int ch = getch();

            if (ch == 'q' || ch == 'Q') {
                _running = false;
            }
        }

        std::string getName() const override {
            return "BasicNcurses";
        }

        // main loop
        void run(const std::vector<std::shared_ptr<IModule>>& modules) override {
            create();

            while (isRunning()) {
                // update modules
                for (auto& module : modules) {
                    module->update();
                }

                // render and handle input
                update(modules);
                handleEvents();
                display();

                // short sleep to reduce CPU usage but allow quick exit
                usleep(100000);  // 100ms instead of 1s
            }

            destroy();
        }
};

}  // namespace Krell

#endif
