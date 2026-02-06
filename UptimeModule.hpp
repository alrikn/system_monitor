
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
        void update() override;
        std::string get_name() override {return "Uptime";}
        int get_height() override {return 1;}

        ModuleValue get_value() override {return uptime;}
        std::string get_string() override {return uptime;}
        bool is_percentage() override {return false;}
};
#endif
