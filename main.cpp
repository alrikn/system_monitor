#include <memory>
#include <vector>
#include <csignal>   // signal handling
#include <atomic>    // atomic flag

#include "BatteryModule.hpp"
#include "CpuModule.hpp"
#include "IDisplay.hpp"
#include "IModule.hpp"
#include "TimeModule.hpp"
#include "DateModule.hpp"
#include "HostModule.hpp"
#include "UserModule.hpp"
#include "OsModule.hpp"
#include "BasicNcurses.hpp"
#include "KernelModule.hpp"

using namespace Krell;

// flag for ctrl c
std::atomic<bool> g_shouldExit(false);

// sig handler for SIGINT ctrl c THIS IS NOT WORKING 
void signalHandler(int signum) {
    (void)signum; // suppress unused parameter warning
    g_shouldExit = true;
}

int runner(std::vector<std::shared_ptr<IModule>> modules, IDisplay *display_class )
{
    display_class->run(modules);
    return 0;
}

int main(int argc, char **argv)
{
    std::signal(SIGINT, signalHandler);

    // create modules
    std::vector<std::shared_ptr<IModule>> modules;
    modules.push_back(std::make_shared<HostModule>());
    modules.push_back(std::make_shared<UserModule>());
    modules.push_back(std::make_shared<OsModule>());
    modules.push_back(std::make_shared<KernelModule>());
    modules.push_back(std::make_shared<DateModule>());
    modules.push_back(std::make_shared<TimeModule>());
    modules.push_back(std::make_shared<CpuNumModule>());
    modules.push_back(std::make_shared<BatteryModule>());

    // create and run nCurses display
    BasicNcurses display;

    runner(modules, &display);
    display.run(modules);

    return 0;
}
