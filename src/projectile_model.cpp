#include "projectile_model.h"
#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

static void writeHeader(ofstream& out)
{
    out << "t,x,y,vx,vy\n";
}

static void initState(double* state, Config& cfg)
{
    // Launch defaults
    double launch_speed = 20.0;		// m/s
    double launch_angle_deg = 45.0;	

    cfg.getDouble("launch_speed", 20.0, launch_speed);
    cfg.getDouble("launch_angle_deg", 45.0, launch_angle_deg);

    double PI = 3.14159;
    double ang = launch_angle_deg * PI / 180.0;

    state[0] = 0.0;
    state[1] = 0.0;
    state[2] = launch_speed * cos(ang);
    state[3] = launch_speed * sin(ang);
}

static void stepState(double* state, double dt, Config& cfg)
{
    double g = 9.81;

    // Physical defaults
    // Default parameters are set to match a standard tennis ball
    double mass = 0.057;   // kg
    double rho  = 1.2;     // kg/m^3
    double cd   = 0.55;
    double area = 0.0035;  // m^2

    cfg.getDouble("g", 9.81, g);
    cfg.getDouble("mass", 0.057, mass);
    cfg.getDouble("rho", 1.2, rho);
    cfg.getDouble("cd", 0.55, cd);
    cfg.getDouble("area", 0.0035, area);

    string drag = cfg.getString("drag", "none");

    double x  = state[0];
    double y  = state[1];
    double vx = state[2];
    double vy = state[3];

    double ax = 0.0;
    double ay = -g;

    if (drag == "quadratic")
    {
        double speed = sqrt(vx * vx + vy * vy);

        if (speed > 1e-12 && mass > 0.0)
        {
            // k = 0.5 * rho * cd * area
            double k = 0.5 * rho * cd * area;

            // drag acceleration magnitude = (k * v^2)/m
            double aDrag = (k * speed * speed) / mass;

            // direction opposite velocity
            ax = ax - aDrag * (vx / speed);
            ay = ay - aDrag * (vy / speed);
        }
    }

    // semi-implicit Euler
    vx = vx + ax * dt;
    vy = vy + ay * dt;

    x = x + vx * dt;
    y = y + vy * dt;

    state[0] = x;
    state[1] = y;
    state[2] = vx;
    state[3] = vy;
}

static void writeRow(ofstream& out, double t, double* state)
{
    out << t << ","
        << state[0] << ","
        << state[1] << ","
        << state[2] << ","
        << state[3] << "\n";
}

bool runProjectile(Config& cfg, string csvPath)
{
    double dt = 0.01;
    double t_end = 5.0;

    if (!cfg.getDouble("dt", 0.01, dt)) return false;
    if (!cfg.getDouble("t_end", 5.0, t_end)) return false;

    if (dt <= 0) { cout << "dt must be > 0\n"; return false; }
    if (t_end <= 0) { cout << "t_end must be > 0\n"; return false; }

    ofstream out(csvPath);
    if (!out)
    {
        cout << "couldn't write csv: " << csvPath << "\n";
        return false;
    }

    out << setprecision(17);

    writeHeader(out);

    double state[4];
    initState(state, cfg);

    double t = 0.0;
    writeRow(out, t, state);

    while (t + dt <= t_end + 1e-12)
    {
        stepState(state, dt, cfg);
        t = t + dt;
        writeRow(out, t, state);
    }

    out.close();
    return true;
}
