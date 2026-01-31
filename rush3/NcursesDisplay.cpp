/*
** EPITECH PROJECT, 2024
** rush03
** File description:
** NcursesDisplay.cpp
*/

#include "Data.hpp"
#include <ncurses.h>
#include <string>
#include "NcursesDisplay.hpp"

namespace Krell {

    NcursesDisplay::NcursesDisplay() = default;
    NcursesDisplay::~NcursesDisplay() = default;

    void NcursesDisplay::loop()
    {
        NcursesWindow window;
        window.create();
        Data data;

        auto drawWindows = [&]() {
            clear();
            box(stdscr, 0, 0);

            WINDOW *systemBox = subwin(stdscr, 9, COLS - 4, 1, 2);
            box(systemBox, 0, 0);
            attron(COLOR_PAIR(3));
            mvprintw(1, 4, " System Info ");
            attroff(COLOR_PAIR(3));

            WINDOW *cpuBox = subwin(stdscr, 4, COLS - 4, 11, 2);
            box(cpuBox, 0, 0);
            attron(COLOR_PAIR(3));
            mvprintw(11, 4, " CPU Info ");
            attroff(COLOR_PAIR(3));

            WINDOW *ramBox = subwin(stdscr, 5, COLS - 4, 16, 2);
            box(ramBox, 0, 0);
            attron(COLOR_PAIR(3));
            mvprintw(16, 4, " RAM Info ");
            attroff(COLOR_PAIR(3));

            WINDOW *batteryBox = subwin(stdscr, 5, COLS - 4, 22, 2);
            box(batteryBox, 0, 0);
            attron(COLOR_PAIR(3));
            mvprintw(22, 4, " Battery Info ");
            attroff(COLOR_PAIR(3));

            attron(COLOR_PAIR(2));
            mvprintw(3, 4, "Hostname: ");
            mvprintw(4, 4, "User: ");
            mvprintw(5, 4, "OS: ");
            mvprintw(6, 4, "Kernel: ");
            mvprintw(7, 4, "Date/Time: ");
            mvprintw(8, 4, "Uptime: ");
            attroff(COLOR_PAIR(2));

            attron(COLOR_PAIR(4));
            mvprintw(3, 14, "%s", data.getHost().c_str());
            mvprintw(4, 10, "%s", data.getUser().c_str());
            mvprintw(5, 8, "%s", data.getOs().c_str());
            mvprintw(6, 12, "%s", data.getKernel().c_str());
            mvprintw(7, 14, "%s", data.getDateTime().c_str());
            mvprintw(8, 12, "%s", data.getUptime().c_str());
            attroff(COLOR_PAIR(4));

            attron(COLOR_PAIR(2));
            mvprintw(13, 4, "CPU Usage:");
            attroff(COLOR_PAIR(2));
            window.percentage(data.getCpuPercentage(), 13);

            attron(COLOR_PAIR(2));
            mvprintw(18, 4, "RAM Usage:");
            mvprintw(19, 4, "RAM Space: ");
            attroff(COLOR_PAIR(2));

            attron(COLOR_PAIR(4));
            mvprintw(19, 15, "%lu MB", data.getRamSpace() / 1024 / 1024);
            attroff(COLOR_PAIR(4));
            window.percentage(data.getRamPercentage(), 18);

            attron(COLOR_PAIR(2));
            mvprintw(24, 4, "Battery: ");
            attroff(COLOR_PAIR(2));

            window.percentage(data.getBattery(), 24);

            refresh();
        };

        drawWindows();

        int ch;
        nodelay(stdscr, TRUE);

        while ((ch = getch()) != 'q') {
            if (ch == KEY_RESIZE) {
                drawWindows();
            }

            data.update();

            attron(COLOR_PAIR(4));
            mvprintw(7, 14, "%s", data.getDateTime().c_str());
            attroff(COLOR_PAIR(4));

            window.percentage(data.getCpuPercentage(), 13);
            window.percentage(data.getRamPercentage(), 18);
            window.percentage(data.getBattery(), 24);

            attron(COLOR_PAIR(4));
            mvprintw(19, 15, "%lu MiB", data.getRamSpace() / 1024 / 1024);
            attroff(COLOR_PAIR(4));

            refresh();
            napms(1000);
        }
        window.destroy();
    }

    NcursesDisplay::NcursesWindow::NcursesWindow()
        : currentLine(0)
    {
    }

    NcursesDisplay::NcursesWindow::~NcursesWindow() = default;

    void NcursesDisplay::NcursesWindow::create()
    {
        initscr();
        start_color();
        cbreak();
        noecho();
        keypad(stdscr, true);
        curs_set(0);

        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_RED, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);

        clear();
        box(stdscr, 0, 0);
        refresh();
    }

    void NcursesDisplay::NcursesWindow::destroy()
    {
        endwin();
    }

    void NcursesDisplay::NcursesWindow::text(std::string &str, unsigned int offset)
    {
        attron(COLOR_PAIR(1));
        mvprintw(offset, 2, "%s", str.c_str());
        attroff(COLOR_PAIR(1));
        refresh();
    }

    void NcursesDisplay::NcursesWindow::percentage(double per, unsigned int offset)
    {
        const int MAX_WIDTH = 50;
        int fill = static_cast<int>((per / 100.0) * MAX_WIDTH);

        mvprintw(offset, 15, "[");

        for (int i = 0; i < MAX_WIDTH; ++i) {
            if (i < fill) {
                attron(COLOR_PAIR(1));
                printw("|");
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
                printw(".");
                attroff(COLOR_PAIR(2));
            }
        }

        printw("] %d%%", static_cast<int>(per));
        refresh();
    }
}

int main()
{
    Krell::NcursesDisplay display;
    display.loop();
    return 0;
}