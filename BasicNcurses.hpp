
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
        void create() override;

        // destroy/cleanup ncurses
        void destroy() override;

        // check if window is running
        bool isRunning() const override;
        // clear screen
        void clear() override;
        // render/display
        void display() override;

        // update display with modules
        void update(const std::vector<std::shared_ptr<IModule>>& modules);

        // input events
        void handleEvents() override;

        std::string getName() const override;

        // main loop
        void run(const std::vector<std::shared_ptr<IModule>>& modules) override;
};

}  // namespace Krell

#endif
