/*
** EPITECH PROJECT, 2024
** rush03
** File description:
** NcursesDisplay.hpp
*/

#ifndef NCURSESDISPLAY_HPP
#define NCURSESDISPLAY_HPP

#include "IDisplay.hpp"
#include <string>

namespace Krell {
    class NcursesDisplay : public IDisplay {
    public:
        NcursesDisplay();
        ~NcursesDisplay() override;

        void loop() override;

        class NcursesWindow : public IWindow {
        public:
            NcursesWindow();
            ~NcursesWindow() override;

            void create() override;
            void destroy() override;
            void text(std::string &str, unsigned int offset) override;
            void percentage(double per, unsigned int offset) override;

        private:
            unsigned int currentLine;
        };
    };
}

#endif