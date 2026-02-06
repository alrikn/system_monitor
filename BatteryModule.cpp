/*
** EPITECH PROJECT, 2026
** system_monitor
** File description:
** BatteryModule
*/



#include "BatteryModule.hpp"



void BatteryModule::update()
{
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
