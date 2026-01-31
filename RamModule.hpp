
#ifndef INCLUDED_RAMMODULE_HPP
    #define INCLUDED_RAMMODULE_HPP

#include "IModule.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>

class RamModule : public Krell::IModule<float> { //we have to declare what the type T is for the get_value
    private:
        float _usage = 0.0f;
    public:
        void update() override { //RAM Usage (%) = (MemTotal - MemAvailable) / MemTotal * 100
            std::ifstream File("/proc/meminfo");
            std::string line;
            long total_memory = 0;
            long available_memory = 0;

            while (std::getline(File, line)) {
                if (line.find("MemTotal:") == 0) {
                    std::string key;
                    std::stringstream ss(line);
                    std::getline(ss, key, ':');
                    ss >> total_memory;
                }
                if (line.find("MemAvailable:") == 0) {
                    std::string key;
                    std::stringstream ss(line);
                    std::getline(ss, key, ':');
                    ss >> available_memory;
                }
                if (total_memory > 0 && available_memory > 0)
                    break;
            }
            _usage = ((total_memory - available_memory) / (float)total_memory) * 100.0f;
        }
        std::string get_name() override {return "Ram Usage";}
        int get_height() override {return 1;}

        float get_value() override {return _usage;}
        std::string get_string() override {return std::to_string(_usage).append(" %");}
        bool is_percentage() override {return true;}
};

#endif
