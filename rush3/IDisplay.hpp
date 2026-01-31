/*
** EPITECH PROJECT, 2023
** rush 3
** File description:
** idisplay
*/

#ifndef IDISPLAY_HPP
#define IDISPLAY_HPP

#include "IModule.hpp"
#include <string>
#include <list>
#include <vector>
#include <memory>

namespace Krell {
    class IDisplay {
    public:
        virtual ~IDisplay() = default;
        virtual void loop() = 0;
        class IWindow {
        public:
            virtual ~IWindow() = default;
            virtual void create() = 0;
            virtual void destroy() = 0;
            virtual void percentage(double per, unsigned int offset) = 0;
        };
    };
    class ADisplay {
        protected:
            std::list<std::unique_ptr<IModule>> unused;
            std::list<std::unique_ptr<IModule>> used;
    };
}

#endif