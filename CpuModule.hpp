
#ifndef INCLUDED_CPUMODULE_HPP
    #define INCLUDED_CPUMODULE_HPP

#include "IModule.hpp"
#include <chrono>
#include <string>
#include <fstream>

class CpuNumModule : public Krell::IModule<int> { //we have to declare what the type T is for the get_value
    private:
        int _num = 0;
        bool _initialised = false; //the number of cores will not change in the middle of runtime, we can just get the info once
    public:
        void update() override {
            if (!_initialised) {
                std::ifstream file("/proc/stat");
                std::string line;

                while (std::getline(file, line)) {
                    if (line.rfind("cpu", 0) != 0)
                        break;
                    _num += 1;
                }
            }
        }

        std::string get_name() override { return "Time"; }
        int get_height() override { return 1; }

        int get_value() override {return _num;}
        std::string get_string() override {return std::to_string(_num);}
        bool is_percentage() override {return false;}

};


#endif
