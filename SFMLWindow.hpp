#ifndef SFMLWINDOW_HPP
#define SFMLWINDOW_HPP

#include "IDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <string>

namespace Krell {

class SFMLWindow : public IDisplay
{
    private:
        sf::RenderWindow _window;
        sf::Font _font;
        const int _width = 500;
        int _totalHeight;
        std::string _title;
        sf::Vector2i _mousePos;
        bool _mousePressed = false;


        const sf::Color _bgColor = sf::Color(30,30,30);
        const sf::Color _textColor = sf::Color(45,45,45);
        const sf::Color _moduleBgColor = sf::Color(220,220,220);
        const sf::Color _titleColor = sf::Color(255,155,0);
        const sf::Color _percentageColor = sf::Color(100,200,255);

        //helpers
        void drawModule(const std::shared_ptr<IModule>& module, int yOffset);

        void drawPercentageBar(const std::shared_ptr<IModule>& module, int yPos, int width);

        sf::Color getProgressBarColor(float percentage) const;

        void updateWindowSize();

        bool isInside(const sf::Vector2i& mouse, const sf::FloatRect& rect);

    public:
        SFMLWindow();

        void create() override;
        void destroy() override;

        bool isRunning() const override;

        void clear() override;

        void display() override;

        void handleEvents() override;

        std::string getName() const override;

        void run(const std::vector<std::shared_ptr<IModule>>& modules) override;

        void calcHeight(const std::vector<std::shared_ptr<IModule>>& modules);

        void render(const std::vector<std::shared_ptr<IModule>>& modules);

        bool isOpen() const;
};

}

#endif