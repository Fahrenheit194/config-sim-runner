#include "runner.h"
#include "projectile_model.h"
#include <iostream>

bool Runner::run(Config& cfg, std::string simName, std::string csvPath)
{
    if (simName == "projectile")
    {
        return runProjectile(cfg, csvPath);
    }

    std::cout << "unknown simulation: " << simName << "\n";
    std::cout << "try: simulation = projectile\n";
    return false;
}
