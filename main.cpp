#include <memory>
#include <vector>
#include <csignal>   // signal handling
#include <atomic>    // atomic flag

//#include "CpuModule.hpp"
//#include "IModule.hpp"
//#include "TimeModule.hpp"
//#include "BasicNcurses.hpp"

// flag for ctrl c
std::atomic<bool> g_shouldExit(false);

// sig handler for SIGINT ctrl c
void signalHandler(int signum) {
    (void)signum; // suppress unused parameter warning
    g_shouldExit = true;
}

int main() {
    std::signal(SIGINT, signalHandler);

    // modules
    std::vector<std::shared_ptr<IModule>> modules;
    modules.push_back(std::make_shared<TimeModule>());
    modules.push_back(std::make_shared<CpuModule>());

    // create and run nCurses display
    BasicNcurses display;
    // run
    display.run(modules);

    return 0;
}
