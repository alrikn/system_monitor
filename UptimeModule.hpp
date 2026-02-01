
#ifndef INCLUDED_UPTIMEMODULE_HPP
    #define INCLUDED_UPTIMEMODULE_HPP

#include "IModule.hpp"
#include <string>
#include <unistd.h>
#include <pwd.h>
#include <fstream>
#include <sstream>

class UptimeModule : public Krell::IModule {
    private:
        std::string uptime = "Unknown";
    public:
        void update() override {
            std::ifstream file("/proc/uptime");

            if (!file.is_open()) {
                uptime = "Unknown";
                return;
            }

            double seconds;
            file >> seconds;

            int days = seconds / 86400;
            int hours = (int(seconds) % 86400) / 3600;
            int minutes = (int(seconds) % 3600) / 60;

            std::ostringstream oss;
            if (days > 0)
                oss << days << "d ";
            oss << hours << "h " << minutes << "m";

            uptime = oss.str();
        }
        std::string get_name() override {return "Uptime";}
        int get_height() override {return 1;}

        ModuleValue get_value() override {return uptime;}
        std::string get_string() override {return uptime;}
        bool is_percentage() override {return false;}
};
#endif
