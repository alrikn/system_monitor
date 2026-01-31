#include "AWindow.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

#include "Data.hpp"
#include <chrono>
#include <thread>

/*Krell::AWindow::AWindow(const std::vector<std::string>& names, const std::vector<std::string>& texts, const std::vector<int>& heights,
                        const std::vector<bool>& displayPercent, const std::vector<float>& percents)
                        : moduleNames(names), moduleTexts(texts), moduleHeights(heights), displayPercentage(displayPercent), percentages(percents) {
    calculateTotalHeight();
}*/

Krell::AWindow::AWindow(const std::vector<std::string>& names, const std::vector<int>& heights, const std::vector<bool>& displayPercent, std::string sys,
                        std::string date, std::string uptime, std::string ramSpace, double CPUper, double RAMper, double BATper)
                        : moduleNames(names), moduleHeights(heights), displayPercentage(displayPercent),
                        SystemInfo(sys), currDate(date), currUptime(uptime), CPUpercent(CPUper), RAMpercent(RAMper), batt(BATper){
    moduleTexts = {SystemInfo, currDate, currUptime, "Usage:", ramSpace, "Remaining Battery:"};
    percentages = {0.0f, 0.0f, 0.0f, CPUpercent, RAMpercent, batt};
    calculateTotalHeight();
}

void Krell::AWindow::calculateTotalHeight() {
    totalHeight = 0;
    for (int height : moduleHeights) {
        totalHeight += (100 * height) + 30;
    }
}

void Krell::AWindow::updateInfo(Krell::Data d) {

    d.update();

    std::ostringstream sysInfo;
    std::ostringstream date;
    std::ostringstream uptime;
    std::ostringstream ramSpace;


    sysInfo << "\nHOST:    " << d.getHost() << "\n\n" << "USER:    " << d.getUser() << "\n\n" << "Operating System:  " << d.getOs() << "\n\n" << "Kernel:    " << d.getKernel();
    date << "\n                            " << d.getDateTime();
    uptime << "\nContinuosly working for:\n                                      " << d.getUptime();

    SystemInfo = sysInfo.str();
    currDate = date.str();
    currUptime = uptime.str();

    CPUpercent = d.getCpuPercentage();
    RAMpercent = d.getRamPercentage();
    batt = d.getBattery();

    //moduleTexts = {sysInfo.str(), date.str(), uptime.str(), "Usage:", ramSpace.str(), "Remaining Battery:"};

    //percentages = {0.0f, 0.0f, 0.0f, d.getCpuPercentage(), d.getRamPercentage(), d.getBattery()};
}

void Krell::AWindow::create(Krell::Data d) {
    window.create(sf::VideoMode(width, totalHeight), "MyGKrellm", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            updateInfo(d);
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
    barFill.setFillColor(sf::Color(76, 132, 189));
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
        headerText.setPosition(210, yOffset + 10); // CHANGE POS!!!
        headerText.setFillColor(sf::Color(173, 201, 229));
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

    if (!headerFont.loadFromFile("assets/header.otf") || !textFont.loadFromFile("assets/medodica.otf")) {
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
        greenButton.setFillColor((i == 0) ? sf::Color(0, 100, 0) : sf::Color(0, 153, 0));
        window.draw(greenButton);

        // down
        sf::RectangleShape redButton(sf::Vector2f(buttonSize, buttonSize));
        redButton.setPosition(buttonX + buttonSize + buttonSpacing, buttonY);
        redButton.setFillColor((i == moduleNames.size() - 1) ? sf::Color(100, 0, 0) : sf::Color(204, 0, 0));
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


    std::ostringstream sysInfo;
    std::ostringstream date;
    std::ostringstream uptime;
    std::ostringstream ramSpace;



    /*while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        d.getOs();
        d.getUptime();
        d.getRamSpace();
        d.getRamPercentage();
        d.getBattery();
        d.getCpuPercentage();
        d.getDateTime();
        d.getKernel();
        d.getHost();
        d.getUser();
        sysInfo << "HOST:    " << d.getHost() << "\n" << "USER:    " << d.getUser() << "\n";

        d.update();
    }*/


    sysInfo << "\nHOST:    " << d.getHost() << "\n\n" << "USER:    " << d.getUser() << "\n\n" << "Operating System:  " << d.getOs() << "\n\n" << "Kernel:    " << d.getKernel();
    date << "\n                            " << d.getDateTime();
    uptime << "\nContinuosly working for:\n                                      " << d.getUptime();
    ramSpace << "Total RAM space:        " << (d.getRamSpace() / 1024 / 1024) << " MB" << "    (" << d.getRamSpace() << ")";


    std::vector<std::string> moduleNames = {"System Info", "Clock", "Uptime", "CPU", "RAM", "Battery"};
    //std::vector<std::string> moduleTexts = {sysInfo.str(), date.str(), uptime.str(), "Usage:", ramSpace.str(), "Remaining Battery:"};
    std::vector<int> moduleHeights = {2, 1, 1, 1, 1, 1};

    std::vector<bool> displayPercentage = {false, false, false, true, true, true};
    //std::vector<float> percentages = {0.0f, 0.0f, 0.0f, d.getCpuPercentage(), d.getRamPercentage(), d.getBattery()};

    Krell::AWindow window(moduleNames, moduleHeights, displayPercentage, sysInfo.str(), date.str(), uptime.str(), ramSpace.str(), d.getCpuPercentage(), d.getRamPercentage(), d.getBattery());
    window.create(d);

    return 0;
}

