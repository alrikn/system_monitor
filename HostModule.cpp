/*
** EPITECH PROJECT, 2026
** system_monitor
** File description:
** HostModule
*/

#include "HostModule.hpp"



void HostModule::update()
 { //https://www.ibm.com/docs/en/zos/2.5.0?topic=calls-gethostname
    char buf[256];
    gethostname(buf, sizeof(buf));
    _hostname = buf;
}