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
# Default configuration
# Properties of standard tennis ball

simulation = projectile

dt = 0.01
t_end = 20

launch_speed = 20        # m/s
launch_angle_deg = 45    # degrees
g = 9.81                 # m/s^2

drag = quadratic
mass = 0.057             # kg
rho = 1.2                # kg/m^3
cd = 0.55                # drag coefficient
area = 0.0035            # m^2

output_csv = run.csv
replay_file = run.rep
replay_csv = replay.csv
```

## Output

### Running a simulation

Run the simulator using a configuration file:

`run configs/projectile.cfg`

<img width="300" height="196" alt="Run parameters" src="https://github.com/user-attachments/assets/05317c15-f5b3-474e-975f-d2d565bfdbc6" />

The program reports success and creates both a CSV output file and a replay file.

<img width="522" height="157" alt="Run success output" src="https://github.com/user-attachments/assets/12fb752b-c09c-4706-bd20-92160603d23c" />

---

### Generated simulation data

The simulator writes results to a CSV file (`run.csv`) containing time, position, and velocity data.

Columns:

`t, x, y, vx, vy`

<img width="345" height="729" alt="Simulation CSV data" src="https://github.com/user-attachments/assets/0cec6e96-8325-4b38-a348-a3c13844a036" />

---

### Example trajectory

The trajectory can be visualized from the simulation output.

<img width="625" height="376" alt="Simulation output plot" src="https://github.com/user-attachments/assets/c0bf5c78-04d6-450a-b3d8-6729603703f9" />

---

### Replay mode

The simulator saves a replay file (`run.rep`) so the exact same experiment can be reproduced later.

Replay the run using:

`replay run.rep`

<img width="301" height="200" alt="Replay parameters" src="https://github.com/user-attachments/assets/97f4a728-9b7f-4d91-8ec1-f2025bc4528e" />

The program confirms the replay and generates a replay CSV.

<img width="523" height="134" alt="Replay success output" src="https://github.com/user-attachments/assets/f99d9351-eef7-4ff0-8f7c-8a19850f8b32" />

---

### Replay output

The replay produces the same results as the original run, demonstrating reproducibility.

<img width="345" height="727" alt="Replay CSV data" src="https://github.com/user-attachments/assets/ea929610-dc31-47c3-999c-dc10c3a0697e" />

## Project Structure
- `src/` - C++ source files
- `configs/` - configuration files

## License

MIT

