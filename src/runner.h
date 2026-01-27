#ifndef RUNNER_H
#define RUNNER_H

#include <string>
#include "config.h"

class Runner
{
public:
    static bool run(Config& cfg, std::string simName, std::string csvPath);
};

#endif