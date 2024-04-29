# Particle Simulation

This C++ program simulates and visualizes particle movement in a 3D environment. It utilizes Verlet integration for accurate particle movement, supports various features such as gravity, boundary conditions, and parallel processing using OpenMP for faster execution. The simulation provides a basic console-based visualization of particle positions in real-time.

## Getting Started

To run the simulation locally, follow these steps:

1. Clone the repository to your local machine:

    ```sh
    git clone https://github.com/SteveProkovas/Particle-Simulation.git
    ```

2. Compile the code using a C++ compiler with OpenMP support:

    ```sh
    g++ -o particle_simulation particle_simulation.cpp -fopenmp
    ```

3. Run the executable:

    ```sh
    ./particle_simulation
    ```

4. Experiment with parameters in the code to customize the simulation as needed.

## Contributing

Contributions are welcome! If you'd like to contribute to the project, feel free to open an issue or submit a pull request.

## License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.
