/*
** EPITECH PROJECT, 2026
** system_monitor
** File description:
** KernelModule
*/

#include "KernelModule.hpp"



void KernelModule::update()
 { //https://lindevs.com/get-linux-kernel-version-using-cpp
    struct utsname buf;
    uname(&buf);
    _release = buf.release;
}