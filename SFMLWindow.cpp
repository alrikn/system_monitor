#include "SFMLWindow.hpp"
#include <algorithm>
#include <sstream>
#include <cmath>


static const int MODULE_PADDING = 10;
static const int HEADER_HEIGHT = 30;
static const int TOGGLE_SIZE = 16;



namespace Krell {

SFMLWindow::SFMLWindow() : _totalHeight(0), _title("Krell System Monitor")
{
}

void SFMLWindow::create()
{
    _totalHeight = 600;
    _window.create(sf::VideoMode(_width, _totalHeight), _title);
    _window.setFramerateLimit(60);
    _font.loadFromFile("assets/medodica.otf");
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
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {//left click
                    _mousePressed = true;
                    _mousePos = sf::Mouse::getPosition(_window);
                }
                break;
            case sf::Event::MouseButtonReleased:
                _mousePressed = false;
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

void SFMLWindow::run(const std::vector<std::shared_ptr<IModule>>& modules)
{
    create();

    while (isOpen())
    {
        for (const auto& module : modules) {
            module->update();
        }
        handleEvents();
        render(modules);
    }

    destroy();
}

/*
I might have broken this check later
*/
void SFMLWindow::calcHeight(const std::vector<std::shared_ptr<IModule>>& modules)
{
    int newHeight = MODULE_PADDING;
    for (const auto& module : modules)
    {
        //newHeight += module->get_height() * 60;
        newHeight += HEADER_HEIGHT;

        if (module->get_display())
            newHeight += module->get_height() * 60;
    }
    if (newHeight < 200) {
        newHeight = 200;
    }
    _totalHeight = newHeight;

    updateWindowSize();
}

void SFMLWindow::updateWindowSize()
{
    if (_window.isOpen())
    {
        _window.setSize(sf::Vector2u(_width, _totalHeight));

        sf::View view = _window.getDefaultView();
        view.setSize(_width, _totalHeight);
        view.setCenter(_width / 2, _totalHeight / 2);
        _window.setView(view);
    }
}

void SFMLWindow::render(const std::vector<std::shared_ptr<IModule>>& modules)
{
    if (!_window.isOpen())
        return;

    calcHeight(modules);

    _window.clear(_bgColor);

    int yOffset = MODULE_PADDING;

    for (const auto& module : modules)
    {
        drawModule(module, yOffset);
        //yOffset += module->get_height() * 60;
        yOffset += HEADER_HEIGHT;
        if (module->get_display())
            yOffset += module->get_height() * 60;

    }

    _window.display();
}

bool SFMLWindow::isOpen() const
{
    return _window.isOpen();
}

void SFMLWindow::drawModule(const std::shared_ptr<IModule>& module, int yOffset)
{
    //the header with the new button
    sf::RectangleShape header(sf::Vector2f(_width - 20, HEADER_HEIGHT));
    header.setPosition(10, yOffset);
    header.setFillColor(sf::Color(40, 40, 40)); //gray black
    _window.draw(header);

    sf::Text nameText;
    nameText.setFont(_font);
    nameText.setString(module->get_name());
    nameText.setCharacterSize(20);
    nameText.setFillColor(_titleColor);
    nameText.setPosition(15, yOffset + 5);
    _window.draw(nameText);

    //button
    sf::RectangleShape toggle(sf::Vector2f(TOGGLE_SIZE, TOGGLE_SIZE));
    float toggleX = _width - 30;
    float toggleY = yOffset + 7;

    toggle.setPosition(toggleX, toggleY);
    toggle.setFillColor(module->get_display() ? sf::Color::Red : sf::Color(100, 0, 0));
    _window.draw(toggle);

    //handle click
    if (_mousePressed &&
        isInside(_mousePos, toggle.getGlobalBounds()))
    {
        module->set_display(!module->get_display());
        _mousePressed = false; //prevent double toggle
    }

    //contenet
    if (!module->get_display())
        return;

    int contentY = yOffset + HEADER_HEIGHT; //yoofset i da current pos, adding header cus we just did it
    int moduleHeight = module->get_height() * 60;

    sf::RectangleShape background( //basic background rectangle (looks better, hard to see red on white)
        sf::Vector2f(_width - 20, moduleHeight - 10)
    );
    background.setPosition(10, contentY);
    background.setFillColor(_moduleBgColor);
    background.setOutlineThickness(2);
    background.setOutlineColor(_textColor);
    _window.draw(background);

    sf::Text valueText;
    valueText.setFont(_font);
    valueText.setString(module->get_string());
    valueText.setCharacterSize(25);
    valueText.setFillColor(module->is_percentage() ? _percentageColor : _textColor);
    valueText.setPosition(15, contentY + 10);
    _window.draw(valueText);

    if (module->is_percentage())
    {
        try {
            drawPercentageBar(module, yOffset + 65, _width - 60);
        } catch (const std::bad_variant_access& e) {
        }
    }
}

void SFMLWindow::drawPercentageBar(const std::shared_ptr<IModule>& module, int yPos, int width)
{
    ModuleValue value = module->get_value();
    float percentage = 0.0f;

    try {
        percentage = std::get<float>(value);
    } catch (const std::bad_variant_access& e) {
        try {
            percentage = static_cast<float>(std::get<int>(value));
        } catch (const std::bad_variant_access& e2) {
            return;
        }
    }

    percentage = std::max(0.0f, std::min(100.0f, percentage));

    sf::RectangleShape barBackground(sf::Vector2f(width, 25));
    barBackground.setPosition(15, yPos);
    barBackground.setFillColor(sf::Color(50, 50, 50));
    barBackground.setOutlineThickness(1);
    barBackground.setOutlineColor(sf::Color(80, 80, 80));
    _window.draw(barBackground);

    float fillWidth = (percentage / 100.0f) * width;
    sf::RectangleShape barFill(sf::Vector2f(fillWidth, 23));
    barFill.setPosition(16, yPos + 1);
    barFill.setFillColor(getProgressBarColor(percentage));
    _window.draw(barFill);

    sf::Text percentText;
    percentText.setFont(_font);
    percentText.setString(module->get_string());
    percentText.setCharacterSize(14);
    percentText.setFillColor(sf::Color::White);
    percentText.setPosition(width - 200, yPos + 5);
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

bool SFMLWindow::isInside(const sf::Vector2i& mouse, const sf::FloatRect& rect)
{
    return rect.contains(static_cast<float>(mouse.x), static_cast<float>(mouse.y));
}


}