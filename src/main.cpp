#include <iostream>
#include <string>
#include "config.h"
#include "runner.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        return 1; // need program name, mode and path
    }

    string mode = argv[1];
    string path = argv[2];

    Config cfg;
    
    if (!cfg.load(path))
    {
        return 1;
    }

    string simName = cfg.getString("simulation", "projectile");

    string csvPath = cfg.getString("output_csv", "run.csv");
    string repPath = cfg.getString("replay_file", "run.rep");

    if (mode == "run")
    {
        bool success = Runner::run(cfg, simName, csvPath);
        if (!success)
        {
            cout << "run failed\n";
            return 1;
        }

        if (!cfg.save(repPath))
        {
            cout << "warning: couldn't write replay file\n";
        }

        cout << "success\n";
        cout << "csv: " << csvPath << "\n";
        cout << "replay: " << repPath << "\n";
        return 0;
    }
    
    else if (mode == "replay")
    {
        string outReplay = cfg.getString("replay_csv", "replay.csv");

        bool success = Runner::run(cfg, simName, outReplay);
        if (!success)
        {
            cout << "replay failed\n";
            return 1;
        }

        cout << "replay success\n";
        cout << "csv: " << outReplay << "\n";
        return 0;
    }

    return 1;
}
