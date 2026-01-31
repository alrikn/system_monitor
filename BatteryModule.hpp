
#ifndef INCLUDED_BATTERYMODULE_HPP
    #define INCLUDED_BATTERYMODULE_HPP

#include <iostream>
#include <string>
#include "IModule.hpp"
#include <fstream>

class BatteryModule : public Krell::IModule { //we have to declare what the type T is for the get_value
    private:
        float _bat = 1;
    public:
        void update() override {
            std::ifstream batt_file;

            for (int i = 0; i <= 9; i++) {
                std::string path = "/sys/class/power_supply/BAT" + std::to_string(i) + "/capacity";
                batt_file.open(path);
                if (batt_file.is_open())
                    break;
            }
            if (batt_file.fail())
                return;
            batt_file >> _bat;
            _bat /= 100;
        }
        std::string get_name() override {return "Battery Percentage";}
        int get_height() override {return 2;}

        ModuleValue get_value() override {return _bat;}
        std::string get_string() override {return std::to_string(_bat * 100).append(" %");}
        bool is_percentage() override {return true;}
};


#endif
