#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <cmath>
#include <unordered_map>
#include <omp.h>

// Particle class representing a point particle in space
class Particle {
public:
    Particle(double x, double y, double z, double mass) : x_(x), y_(y), z_(z), mass_(mass), vx_(0.0), vy_(0.0), vz_(0.0) {}

    double getX() const { return x_; }
    double getY() const { return y_; }
    double getZ() const { return z_; }
    double getMass() const { return mass_; }
    double getVX() const { return vx_; }
    double getVY() const { return vy_; }
    double getVZ() const { return vz_; }

    void setVelocity(double vx, double vy, double vz) {
        vx_ = vx;
        vy_ = vy;
        vz_ = vz;
    }

    void updatePosition(double dt) {
        x_ += vx_ * dt;
        y_ += vy_ * dt;
        z_ += vz_ * dt;
    }

private:
    double x_;
    double y_;
    double z_;
    double mass_;
    double vx_;
    double vy_;
    double vz_;
};

// Simulation class representing the entire simulation environment
class Simulation {
public:
    Simulation(int numParticles) : numParticles_(numParticles) {
        // Initialize particles with random positions, velocities, and masses
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis_pos(-10.0, 10.0);
        std::uniform_real_distribution<double> dis_vel(-1.0, 1.0);
        std::uniform_real_distribution<double> dis_mass(1.0, 10.0);
        for (int i = 0; i < numParticles_; ++i) {
            particles_.push_back(std::make_unique<Particle>(dis_pos(gen), dis_pos(gen), dis_pos(gen), dis_mass(gen)));
            particles_.back()->setVelocity(dis_vel(gen), dis_vel(gen), dis_vel(gen));
        }
    }

    // Perform a single step of the simulation using Verlet integration
    void step(double dt) {
        // Update particle positions in parallel using OpenMP
#pragma omp parallel for
        for (int i = 0; i < numParticles_; ++i) {
            particles_[i]->updatePosition(dt);

            // Apply gravity
            applyGravity(particles_[i]);
            
            // Apply boundary conditions
            applyBoundaryConditions(particles_[i]);
        }
    }

    // Print the current state of the simulation
    void printState() const {
        std::cout << "Current state of the simulation:" << std::endl;
        for (const auto& particle : particles_) {
            std::cout << "Particle at (" << particle->getX() << ", " << particle->getY() << ", " << particle->getZ() << ") with mass " << particle->getMass() << std::endl;
        }
    }

private:
    int numParticles_;
    std::vector<std::unique_ptr<Particle>> particles_;

    // Apply gravity force to the given particle
    void applyGravity(const std::unique_ptr<Particle>& particle) {
        // Example: Applying constant downward gravity
        constexpr double gravity = 9.81; // m/s^2
        double force = particle->getMass() * gravity;
        particle->setVelocity(particle->getVX(), particle->getVY() - force, particle->getVZ());
    }

    // Apply boundary conditions to keep particles within the simulation space
    void applyBoundaryConditions(const std::unique_ptr<Particle>& particle) {
        // Example: Simple periodic boundary conditions
        constexpr double boundary = 10.0; // Size of the simulation space
        if (particle->getX() < -boundary || particle->getX() > boundary ||
            particle->getY() < -boundary || particle->getY() > boundary ||
            particle->getZ() < -boundary || particle->getZ() > boundary) {
            // Wrap particle position to the opposite side of the simulation space
            particle->setVelocity(-particle->getVX(), -particle->getVY(), -particle->getVZ());
        }
    }
};

// Function to visualize particle positions in the console
void visualize(const Simulation& sim) {
    std::vector<std::vector<char>> grid(21, std::vector<char>(21, '.')); // Grid size: 21x21
    for (const auto& particle : sim.getParticles()) {
        int x = static_cast<int>(particle->getX()) + 10; // Shift by 10 to center particles
        int y = static_cast<int>(particle->getY()) + 10; // Shift by 10 to center particles
        if (x >= 0 && x < 21 && y >= 0 && y < 21) {
            grid[y][x] = 'o'; // Mark particle position in the grid
        }
    }

    // Print the grid to visualize particle positions
    for (int i = 0; i < 21; ++i) {
        for (int j = 0; j < 21; ++j) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    // Create a simulation with 10 particles
    Simulation sim(10);

    // Run the simulation for 5 steps with a time step of 0.1 seconds
    constexpr double dt = 0.1;
    for (int i = 0; i < 5; ++i) {
        sim.step(dt);
        visualize(sim); // Visualize particle positions
    }

    return 0;
}
