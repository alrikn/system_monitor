/*
** EPITECH PROJECT, 2026
** system_monitor
** File description:
** RamModule
*/

#include "RamModule.hpp"



void RamModule::update()
{ //RAM Usage (%) = (MemTotal - MemAvailable) / MemTotal * 100
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