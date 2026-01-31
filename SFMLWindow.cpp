#include "SFMLWindow.hpp"
#include <algorithm>
#include <sstream>
#include <cmath>

namespace Krell {

SFMLWindow::SFMLWindow() : _totalHeight(0), _title("Krell System Monitor")
{
}

void SFMLWindow::create()
{
    _window.create(sf::VideoMode(_width, _totalHeight), _title);
    _window.setFramerateLimit(60);
    _font.loadFromFile("assets/text.otf");
}

void SFMLWindow::destroy()
{
    if (_window.isOpen())
    {
        _window.close();
    }
}

bool SFMLWindow::isRunning() const
{
    return _window.isOpen();
}

void SFMLWindow::clear()
{
    if (_window.isOpen())
    {
        _window.clear(_bgColor);
    }
}

void SFMLWindow::display()
{
    if (_window.isOpen())
    {
        _window.display();
    }
}

void SFMLWindow::handleEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                _window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape ||
                    event.key.code == sf::Keyboard::Q)
                {
                    _window.close();
                }
                break;
            default:
                break;
        }
    }
}

std::string SFMLWindow::getName() const
{
    return "MyGKrellm";
}

void SFMLWindow::run(const std::vector<std::shared_ptr<IModule<std::string>>>& modules)
{
    calcHeight(modules);
    create();

    while (isOpen())
    {
        handleEvents();
        render(modules);
    }

    destroy();
}

void SFMLWindow::calcHeight(const std::vector<std::shared_ptr<IModule<std::string>>>& modules)
{
    _totalHeight = 0;
    for (const auto& module : modules)
    {
        _totalHeight += module->get_height() * 100;
    }
    _totalHeight += 20;

    if (_window.isOpen())
    {
        _window.setSize(sf::Vector2u(_width, _totalHeight));
    }
}

void SFMLWindow::render(const std::vector<std::shared_ptr<IModule<std::string>>>& modules)
{
    if (!_window.isOpen())
        return;

    _window.clear(_bgColor);

    int yOffset = 10;

    for (const auto& module : modules)
    {
        drawModule(module, yOffset);
        yOffset += module->get_height() * 100;
    }

    _window.display();
}

bool SFMLWindow::isOpen() const
{
    return _window.isOpen();
}

void SFMLWindow::drawModule(const std::shared_ptr<IModule<std::string>>& module, int yOffset)
{
    int moduleHeight = module->get_height() * 100;

    //module bg
    sf::RectangleShape background(sf::Vector2f(_width - 20, moduleHeight - 10));
    background.setPosition(10, yOffset);
    background.setFillColor(_moduleBgColor);
    background.setOutlineThickness(2);
    background.setOutlineColor(_textColor);
    _window.draw(background);

    // name
    sf::Text nameText;
    nameText.setFont(_font);
    nameText.setString(module->get_name());
    nameText.setCharacterSize(24);
    nameText.setFillColor(_titleColor);
    nameText.setPosition(20, yOffset + 10);
    _window.draw(nameText);

    // value
    sf::Text valueText;
    valueText.setFont(_font);
    valueText.setString(module->get_string());
    valueText.setCharacterSize(32);
    valueText.setFillColor(module->is_percentage() ? _percentageColor : _textColor);
    valueText.setPosition(20, yOffset + 50);
    _window.draw(valueText);

    //percentage bar
    if (module->is_percentage())
    {
        drawPercentageBar(module, yOffset + 90, _width - 60);
    }
}

void SFMLWindow::drawPercentageBar(const std::shared_ptr<IModule<std::string>>& module, int yPos, int width)
{
    float percentage = module->get_value();

    //0-100
    percentage = std::max(0.0f, std::min(100.0f, percentage));

    //bg bar
    sf::RectangleShape barBackground(sf::Vector2f(width, 20));
    barBackground.setPosition(20, yPos);
    barBackground.setFillColor(sf::Color(50, 50, 50));
    barBackground.setOutlineThickness(1);
    barBackground.setOutlineColor(sf::Color(80, 80, 80));
    _window.draw(barBackground);

    //fill
    float fillWidth = (percentage / 100.0f) * width;
    sf::RectangleShape barFill(sf::Vector2f(fillWidth, 18));
    barFill.setPosition(21, yPos + 1);
    barFill.setFillColor(getProgressBarColor(percentage));
    _window.draw(barFill);

    //text
    sf::Text percentText;
    percentText.setFont(_font);
    percentText.setString(module->get_string());
    percentText.setCharacterSize(16);
    percentText.setFillColor(sf::Color::White);
    percentText.setPosition(width - 60, yPos);
    _window.draw(percentText);
}

sf::Color SFMLWindow::getProgressBarColor(float percentage) const
{
    if (percentage < 30.0f)
        return sf::Color(255, 50, 0);
    else if (percentage < 70.0f)
        return sf::Color(255, 200, 0);
    else
        return sf::Color(0, 200, 0);
}

}
