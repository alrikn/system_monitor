
#ifndef INCLUDED_IDISPLAY_HPP
    #define INCLUDED_IDISPLAY_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Imodule.hpp"

class IDisplay
{
    protected:
    public:
        virtual ~IDisplay() = default;

        //init display
        virtual void init() = 0;

        //clend display
        virtual void cleanup() = 0;

        //place to store all the Imodule pointer to update all at once
        virtual void update(const std::vector<std::shared_ptr<Imodule>>& modules) = 0;

        //seems self-explanatory
        virtual bool isRunning() const = 0;

        //da display name
        virtual std::string getName() const = 0;

        //handle events? (maybe), like to change displays
        virtual void handleEvents() = 0;
};

#endif
