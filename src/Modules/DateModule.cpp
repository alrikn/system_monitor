/*
** EPITECH PROJECT, 2026
** system_monitor
** File description:
** DateModule
*/

#include "DateModule.hpp"



void DateModule::update()
 {
    const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%d/%m/%Y", localtime(&t));
    _date = s;
}