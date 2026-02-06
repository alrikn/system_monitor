/*
** EPITECH PROJECT, 2026
** system_monitor
** File description:
** OsModule
*/

#include "OsModule.hpp"



void OsModule::update()
{ //https://www.ibm.com/docs/en/zvm/7.3.0?topic=descriptions-uname-display-current-operating-system-name
    struct utsname buf;
    uname(&buf);
    _osname = buf.sysname;
}