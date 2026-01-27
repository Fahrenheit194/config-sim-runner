# config-sim-runner

This tool provides a simple, config-driven framework for running numerical simulation models.

Projectile motion with quadratic air drag is included as an example simulation.

## Features
- Simulation parameters are defined **externally via config files**
- **Pluggable simulation models** selected by name from the config file
- **Command-line interface** with run and replay modes
- **CSV output** for analysis in Excel, MATLAB, or Python
- **Replay support** by saving the previous configuration

## Usage
1. Build the program:
   g++ -std=c++17 -o sim_runner src/*.cpp
2. Run a simulation:
   ./sim_runner run configs/projectile.cfg
3. Open the generated CSV file to inspect or plot results
4. (Optional) Re-run a saved configuration:
   ./sim_runner replay run.rep

## Configuration
Simulation parameters are defined in config files using a simple format.

Example:
```ini
simulation = projectile

dt = 0.01
t_end = 20

launch_speed = 20
launch_angle_deg = 45
g = 9.81

drag = quadratic
mass = 0.057
rho = 1.2
cd = 0.55
area = 0.0035
```

## Output
For the projectile motion example, simulation results are written to a CSV file with the following columns:
t, x, y, vx, vy

## Project Structure
- `src/` - C++ source files
- `configs/` - configuration files

## License
MIT