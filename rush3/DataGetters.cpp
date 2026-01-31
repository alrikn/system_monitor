#include "Data.hpp"

std::string Krell::Data::getHost()
{
    return (host);
}

std::string Krell::Data::getUser()
{
    return (user);
}

std::string Krell::Data::getOs()
{
    return (os);
}

std::string Krell::Data::getKernel()
{
    return (kernel);
}

std::string Krell::Data::getDateTime()
{
    return (dateTime);
}

std::string Krell::Data::getUptime()
{
    return (uptime);
}

double Krell::Data::getCpuPercentage()
{
    return (cpuPercentage);
}

double Krell::Data::getRamPercentage()
{
    return (ramPercentage);
}

std::size_t Krell::Data::getRamSpace()
{
    return (ramSpace);
}

double Krell::Data::getBattery()
{
    return (battery);
}
