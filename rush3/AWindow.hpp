/*
** EPITECH PROJECT, 2023
** rush 3
** File description:
** window
*/


#ifndef AWINDOW_HPP
#define AWINDOW_HPP

#include "IDisplay.hpp"
#include "Data.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace Krell {
    class AWindow {
    private:
        int width = 500;
        int totalHeight;

        std::vector<std::string> moduleNames;
        std::vector<std::string> moduleTexts;
        std::vector<int> moduleHeights;
        std::vector<bool> displayPercentage;
        std::vector<float> percentages;
        sf::RenderWindow window;

        const int buttonSize = 20;
        const int buttonSpacing = 5;

        std::string SystemInfo;
        std::string currDate;
        std::string currUptime;

        double CPUpercent;
        double RAMpercent;
        double batt;

    public:

        AWindow(const std::vector<std::string>& names, const std::vector<int>& heights, const std::vector<bool>& displayPercent, std::string sys,
                        std::string date, std::string uptime, std::string ramSpace, double CPUper, double RAMper, double BATper);
        //AWindow(const std::vector<std::string>& names, const std::vector<std::string>& texts,
        //        const std::vector<int>& heights, const std::vector<bool>& displayPercent, const std::vector<float>& percents);
        void create(Krell::Data d);
        void destroy();

    private:
        void calculateTotalHeight();

        void updateInfo(Krell::Data d);

        void drawAll();
        void drawModules(int i, sf::Font textFont, sf::Font headerFont, int yOffset, int moduleHeight);
        void drawPercentages(int i, sf::Font textFont, int yOffset, int moduleHeight);

        void handleButtonClicks(const sf::Event& event);
        void swapModules(size_t index1, size_t index2);
    };
}

#endif
