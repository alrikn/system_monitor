/*
** EPITECH PROJECT, 2026
** system_monitor
** File description:
** UserModule
*/

#include "UserModule.hpp"



void UserModule::update()
{
    _username = getpwuid(geteuid())->pw_name;
}