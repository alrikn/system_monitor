#include <memory>
#include <vector>
#include <unistd.h>  // For sleep
#include <csignal>   //  signal handling
#include <atomic>    // atomic flag

#include "CpuModule.hpp"
#include "Imodule.hpp"
#include "TimeModule.hpp"
#include "BasicNcurses.hpp"

// flag for ctrl c
std::atomic<bool> g_shouldExit(false);

// sig handler for SIGINT ctrl c
void signalHandler(int signum) {
    (void)signum; // suppress unused parameter warning
    g_shouldExit = true;
}

/*
this func is for testing purposes. feel free to remove it afterward.
also the quit is broken, and i can't be bothered to figure out why

*/
void diplay()
{
    // register signal handler for ctrl c
    std::signal(SIGINT, signalHandler);

    //we make all the modules taht we are going to use in our displays
    //everything is a shered pointer in case we need to pass stuff to a 
    std::vector<std::shared_ptr<Imodule>> modules;
    modules.push_back(std::make_shared<TimeModule>());
    modules.push_back(std::make_shared<CpuModule>());

    //make the display (rn is the basic one, but we'll have to add custom stuff later on)
    BasicNcurses display;

    display.init();
    
    //the main loop (this should run for every func)
    while (display.isRunning() && !g_shouldExit) {
        //go throu modules and update
        for (auto& module : modules) {
            module->update();
        }
        //handle events (keyboard input)
        display.handleEvents();
        //update the display
        display.update(modules);
        sleep(1);
    }
    display.cleanup();
}

int main() {
    diplay();
    return 0;
}