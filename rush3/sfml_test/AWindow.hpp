#ifndef AWINDOW_HPP
#define AWINDOW_HPP

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

    public:
        AWindow(const std::vector<std::string>& names, const std::vector<std::string>& texts,
                const std::vector<int>& heights, const std::vector<bool>& displayPercent, const std::vector<float>& percents);
        void create();
        void destroy();
        void putText(const std::string& str, unsigned int offset);

    private:
        void calculateTotalHeight();

        void drawAll();
        void drawModules(int i, sf::Font textFont, sf::Font headerFont, int yOffset, int moduleHeight);
        void drawPercentages(int i, sf::Font textFont, int yOffset, int moduleHeight);

        void handleButtonClicks(const sf::Event& event);
        void swapModules(size_t index1, size_t index2);
    };
}

#endif