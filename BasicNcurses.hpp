
#ifndef INCLUDED_BASICNCURSES_HPP
    #define INCLUDED_BASICNCURSES_HPP

#include <ncurses.h>
#include <vector>
#include <memory>
#include <unistd.h>
#include <atomic>
#include "IDisplay.hpp"

extern std::atomic<bool> g_shouldExit;

namespace Krell {

class BasicNcurses : public Krell::IDisplay {
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
            
            int max_y, max_x;
            getmaxyx(stdscr, max_y, max_x);
            
            int title_y = 0;
            int content_y = 2;
            int modules_per_row = 2;
            int module_width = (max_x - 3) / modules_per_row;
            int module_height = 4;
            
            // title
            attron(A_BOLD);
            mvprintw(title_y, (max_x - 20) / 2, "=== SYSTEM MONITOR ===");
            attroff(A_BOLD);
            
            // modules in grid
            for (size_t i = 0; i < modules.size(); ++i) {
                int row = i / modules_per_row;
                int col = i % modules_per_row;
                
                int start_x = col * module_width + 1;
                int start_y = content_y + (row * (module_height + 1));
                
                // stop if we're running out of space
                if (start_y + module_height > max_y - 3) break;
                
                const auto& module = modules[i];
                std::string name = module->get_name();
                std::string data = module->get_string();
                
                // box border
                mvprintw(start_y, start_x, "+");
                mvprintw(start_y, start_x + module_width - 2, "+");
                mvprintw(start_y + module_height - 1, start_x, "+");
                mvprintw(start_y + module_height - 1, start_x + module_width - 2, "+");
                
                // top and bottom lines
                for (int x = start_x + 1; x < start_x + module_width - 2; ++x) {
                    mvprintw(start_y, x, "-");
                    mvprintw(start_y + module_height - 1, x, "-");
                }
                
                // side lines
                for (int y = start_y + 1; y < start_y + module_height - 1; ++y) {
                    mvprintw(y, start_x, "|");
                    mvprintw(y, start_x + module_width - 2, "|");
                }
                
                // module name in bold
                attron(A_BOLD);
                mvprintw(start_y + 1, start_x + 2, "%s", name.c_str());
                attroff(A_BOLD);
                
                // module data
                int data_x = start_x + 2;
                int data_y = start_y + 2;
                
                // wrap text if needed
                std::string truncated_data = data;
                if (truncated_data.length() > static_cast<size_t>(module_width - 5)) {
                    truncated_data = truncated_data.substr(0, module_width - 8) + "...";
                }
                
                mvprintw(data_y, data_x, "%s", truncated_data.c_str());
            }
            
            // tail
            attron(A_DIM);
            mvprintw(max_y - 2, 1, "Press 'q' to quit | Ctrl+C to exit");
            attroff(A_DIM);
            
            refresh();
        }

        // input events
        void handleEvents() override {
            timeout(0);  // non blocking input
            int ch = getch();

            if (ch == 'q' || ch == 'Q') {
                _running = false;
            }
            
            if (g_shouldExit) {
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
