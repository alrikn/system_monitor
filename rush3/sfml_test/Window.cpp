#include "AWindow.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "../Data.hpp"


Krell::AWindow::AWindow(const std::vector<std::string>& names, const std::vector<std::string>& texts, const std::vector<int>& heights,
                        const std::vector<bool>& displayPercent, const std::vector<float>& percents)
                        : moduleNames(names), moduleTexts(texts), moduleHeights(heights), displayPercentage(displayPercent), percentages(percents) {
    calculateTotalHeight();
}

void Krell::AWindow::calculateTotalHeight() {
    totalHeight = 0;
    for (int height : moduleHeights) {
        totalHeight += (100 * height) + 30;
    }
}

void Krell::AWindow::create() {
    window.create(sf::VideoMode(width, totalHeight), "Module Display", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                handleButtonClicks(event);
            }
        }
        window.clear(sf::Color(11, 34, 57));
        drawAll();
        window.display();
    }
}

void Krell::AWindow::destroy() {
    if (window.isOpen()) {
        window.close();
    }
}

//void Krell::AWindow::putText(const std::string& str, unsigned int offset) {
//    std::cout << "Text added to module at offset " << offset << ": " << str << std::endl;
//}

void Krell::AWindow::drawPercentages(int i, sf::Font textFont, int yOffset, int moduleHeight) {
    sf::RectangleShape barBackground(sf::Vector2f(width - 40, 40));
    barBackground.setPosition(20, yOffset + moduleHeight - 60);
    barBackground.setFillColor(sf::Color(200, 200, 200));
    window.draw(barBackground);

    float barWidth = (width - 40) * (percentages[i] / 100.0f);
    sf::RectangleShape barFill(sf::Vector2f(barWidth, 40));
    barFill.setPosition(20, yOffset + moduleHeight - 60);
    barFill.setFillColor(sf::Color(0, 128, 255));
    window.draw(barFill);

    std::ostringstream percentageStream;
    percentageStream << std::fixed << std::setprecision(2) << percentages[i] << "%";
    sf::Text percentageText(percentageStream.str(), textFont, 25);
    percentageText.setPosition(width / 2 - 30, yOffset + moduleHeight - 59);
    percentageText.setFillColor(sf::Color::White);
    window.draw(percentageText);
}

void Krell::AWindow::drawModules(int i, sf::Font textFont, sf::Font headerFont, int yOffset, int moduleHeight) {

        sf::RectangleShape moduleBorder(sf::Vector2f(width - 20, moduleHeight - 20));
        moduleBorder.setPosition(10, yOffset + 10);
        moduleBorder.setFillColor(sf::Color::Transparent);
        moduleBorder.setOutlineThickness(2);
        moduleBorder.setOutlineColor(sf::Color(30, 62, 94));
        window.draw(moduleBorder);

        sf::RectangleShape header(sf::Vector2f(width - 20, 30));
        header.setPosition(10, yOffset + 10);
        header.setFillColor(sf::Color(30, 62, 94));
        window.draw(header);

        sf::Text headerText(moduleNames[i], headerFont, 20);
        headerText.setPosition(210, yOffset + 10);
        headerText.setFillColor(sf::Color::White);
        window.draw(headerText);

        sf::Text moduleText(moduleTexts[i], textFont, 20);
        moduleText.setPosition(20, yOffset + 40);
        moduleText.setFillColor(sf::Color::White);
        window.draw(moduleText);
}

void Krell::AWindow::drawAll() {
    int moduleHeight;
    int yOffset = 0;
    sf::Font headerFont;
    sf::Font textFont;

    if (!headerFont.loadFromFile("../assets/header.otf") || !textFont.loadFromFile("../assets/medodica.otf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    for (size_t i = 0; i < moduleNames.size(); ++i) {

        moduleHeight = (100 * moduleHeights[i]) + 30;

        drawModules(i, textFont, headerFont, yOffset, moduleHeight);

        if (displayPercentage[i]) {

            drawPercentages(i, textFont, yOffset, moduleHeight);
        }

        int buttonX = width - 15 - 2 * (buttonSize + buttonSpacing);
        int buttonY = yOffset + 15;

        // up
        sf::RectangleShape greenButton(sf::Vector2f(buttonSize, buttonSize));
        greenButton.setPosition(buttonX, buttonY);
        greenButton.setFillColor((i == 0) ? sf::Color(0, 100, 0) : sf::Color::Green);
        window.draw(greenButton);

        // down
        sf::RectangleShape redButton(sf::Vector2f(buttonSize, buttonSize));
        redButton.setPosition(buttonX + buttonSize + buttonSpacing, buttonY);
        redButton.setFillColor((i == moduleNames.size() - 1) ? sf::Color(100, 0, 0) : sf::Color::Red);
        window.draw(redButton);

        yOffset += moduleHeight;
    }
}



void Krell::AWindow::handleButtonClicks(const sf::Event& event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        int mouseX = event.mouseButton.x;
        int mouseY = event.mouseButton.y;

        int yOffset = 0;

        for (size_t i = 0; i < moduleNames.size(); ++i) {
            int moduleHeight = (100 * moduleHeights[i]) + 30;

            int buttonX = width - 15 - 2 * (buttonSize + buttonSpacing);
            int buttonY = yOffset + 20;

            // up
            if (mouseX >= buttonX && mouseX <= buttonX + buttonSize &&
                mouseY >= buttonY && mouseY <= buttonY + buttonSize) {
                if (i > 0) {
                    swapModules(i, i - 1);
                }
            }

            // down
            if (mouseX >= buttonX + buttonSize + buttonSpacing && mouseX <= buttonX + 2 * (buttonSize + buttonSpacing) &&
                mouseY >= buttonY && mouseY <= buttonY + buttonSize) {
                if (i < moduleNames.size() - 1) {
                    swapModules(i, i + 1);
                }
            }

            yOffset += moduleHeight;
        }
    }
}


void Krell::AWindow::swapModules(size_t index1, size_t index2) {

    std::swap(moduleNames[index1], moduleNames[index2]);

    std::swap(moduleTexts[index1], moduleTexts[index2]);

    std::swap(moduleHeights[index1], moduleHeights[index2]);

    bool temp = displayPercentage[index1];
    displayPercentage[index1] = displayPercentage[index2];
    displayPercentage[index2] = temp;

    std::swap(percentages[index1], percentages[index2]);
}





int main() {

    Krell::Data d;

    std::string date = d.getDateTime();

    std::vector<std::string> moduleNames = {"System Info", "Clock", "Uptime", "CPU", "RAM", "Battery"};
    std::vector<std::string> moduleTexts = {"This is module 1.", date, "line1\nline2\nline3", "This is module 3.", "", ""};
    std::vector<int> moduleHeights = {2, 1, 1, 1, 1, 1};

    std::vector<bool> displayPercentage = {false, false, false, true, true, true};
    std::vector<float> percentages = {0.0f, 0.0f, 0.0f, 42.3f, 2.2f, 34.6f};

    Krell::AWindow window(moduleNames, moduleTexts, moduleHeights, displayPercentage, percentages);
    window.create();

    return 0;
}
