/*
** EPITECH PROJECT, 2026
** system_monitor
** File description:
** TimeModule
*/

#include "TimeModule.hpp"



void TimeModule::update()
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%H:%M:%S", std::localtime(&t));
    _time = buf;
}