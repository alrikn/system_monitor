#include <memory>
#include <vector>
#include <csignal>   // signal handling
#include <atomic>    // atomic flag

#include "BatteryModule.hpp"
#include "CpuModule.hpp"
#include "IDisplay.hpp"
#include "IModule.hpp"
#include "SFMLWindow.hpp"
#include "TimeModule.hpp"
#include "DateModule.hpp"
#include "HostModule.hpp"
#include "UptimeModule.hpp"
#include "UserModule.hpp"
#include "OsModule.hpp"
#include "BasicNcurses.hpp"
#include "KernelModule.hpp"
#include "RamModule.hpp"

using namespace Krell;

// flag for ctrl c
std::atomic<bool> g_shouldExit(false);

// sig handler for SIGINT ctrl c THIS IS NOT WORKING 
void signalHandler(int signum) {
    (void)signum; // suppress unused parameter warning
    g_shouldExit = true;
}

void runner(std::vector<std::shared_ptr<IModule>> modules, IDisplay *display_class )
{
    display_class->run(modules);
    delete display_class;
}

IDisplay *argv_reader(int argc, char **argv)
{
    std::vector<std::string> args(argv, argv + argc);
    if (argc != 2) {
        std::cout << "Defaulting to ncurses display" << std::endl;
        return new BasicNcurses;
    }
    if (args[1] == "-n") {
        std::cout << "Starting ncurses display..." << std::endl;
        return new BasicNcurses;
    }
    if (args[1] == "-s") {
        std::cout << "Starting SFML display..." << std::endl;
        return new SFMLWindow();
    }

    std::cout << "USAGE:\n\t-n : ncurses display\n\t-s : SFML display" << std::endl;
    return nullptr;
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
    modules.push_back(std::make_shared<RamModule>());
    modules.push_back(std::make_shared<BatteryModule>());
    modules.push_back(std::make_shared<CpuNumModule>());
    modules.push_back(std::make_shared<CpuUseModule>());
    modules.push_back(std::make_shared<CpuNameModule>());
    modules.push_back(std::make_shared<UptimeModule>());

    // create and run nCurses display
    IDisplay *display = argv_reader(argc, argv);
    if (!display)
        return 84;

    runner(modules, display);

    return 0;
}
