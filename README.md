# Particle Simulation

This repository contains a simple particle simulation implemented in C++. The simulation models the behavior of multiple point particles in a three-dimensional space under the influence of gravity and periodic boundary conditions.

## Features

- **Particle Class**: Represents a point particle with attributes such as position, velocity, and mass.
- **Simulation Class**: Manages the simulation environment, including particle initialization, time-stepping, and boundary conditions.
- **Visualization**: Provides a basic console-based visualization of particle positions.
- **Verlet Integration**: Utilizes Verlet integration for updating particle positions.

## How to Use

1. **Clone the Repository**:
   ```
   git clone https://github.com/SteveProkovas/Particle-Simulation.git
   ```

2. **Compile the Code**:
   ```
   g++ -std=c++11 -fopenmp main.cpp -o particle_simulation
   ```

3. **Run the Simulation**:
   ```
   ./particle_simulation
   ```

4. **Visualize the Simulation**:
   The simulation will run for a specified number of steps (default: 5) with a time step of 0.1 seconds. After each step, the particle positions will be visualized in a console-based grid.

## Customization

- **Number of Particles**: You can modify the number of particles in the simulation by changing the value passed to the `Simulation` constructor in the `main` function.
- **Simulation Parameters**: You can adjust the number of simulation steps and the time step (`dt`) in the `main` function as per your requirements.

## Dependencies

- **C++ Compiler**: The code is written in C++ and requires a compatible compiler (e.g., GCC, Clang).
- **OpenMP**: The code uses OpenMP for parallelization. Ensure that your compiler supports OpenMP.

## Contributing

Contributions are welcome! If you find any bugs or have suggestions for improvements, feel free to open an issue or submit a pull request.

## License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.
