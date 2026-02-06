/*
** EPITECH PROJECT, 2026
** system_monitor
** File description:
** UptimeModule
*/

#include "UptimeModule.hpp"



void UptimeModule::update()
{
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