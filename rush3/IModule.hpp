/*
** EPITECH PROJECT, 2023
** rush 3
** File description:
** imodule
*/

#ifndef IMODULE_HPP
#define IMODULE_HPP

#include <string>
#include <vector>
#include "Data.hpp"

namespace Krell {
    class IDisplay;
    class IModule {
    public:
        virtual ~IModule() = default;

        virtual void update(IDisplay &display) = 0;
        virtual std::string getName() const = 0;
        virtual unsigned int getHeight() const = 0;
        virtual void setData(Data &data) = 0;
    };
}

#endif