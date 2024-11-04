# Simulador-de-Reserva-Natural

# Project Overview

This project is a Natural Reserve Simulator developed in C++ using Object-Oriented Programming (OOP) principles. The simulation models a natural reserve populated with various animals that exhibit autonomous behaviors such as movement, feeding, reproduction, and interaction with their environment. Users interact with the simulator via text commands, influencing the animals and the reserve's state.

# Features

Polymorphic Animal System: Multiple species of animals with unique behaviors, such as rabbits, wolves, sheep, and kangaroos.
Food System: Different types of food (e.g., grass, carcass, vegetables) with varying nutritional and toxic properties.
Simulation of Time: The simulation progresses in discrete time steps, with animals reacting to their environment and changing states.
User Interaction: Users can create animals, feed them, or remove elements using simple text commands. The simulation state updates after every user command.
Text-based Interface: The interface operates in text mode, with the reserve and its elements visually represented on the console.

# Requirements
C++ Standard: The project uses C++11 or later. Ensure that your compiler supports this standard.
Development Environment: The project can be compiled and run using any C++ development environment (e.g., CLion, Visual Studio, or GCC/Clang).

# Usage
Once the simulator is running, you can interact with it through text-based commands. Some of the available commands are:

Create Animal:

animal <species> <row> <col>: Create a specific animal at the given coordinates.
Example: animal c 3 5 creates a rabbit at row 3, column 5.

Feed Animal:

feed <row> <col> <nutritional points> <toxicity points>: Feed the animal at the given position.
Example: feed 3 5 5 0 feeds the animal at position (3,5) with 5 nutritional points and 0 toxicity.

Remove Food:

nofood <row> <col>: Remove food from the given coordinates.

Advance Time:

n <N>: Advance the simulation by N time steps.
View Information:

see <row> <col>: Display detailed information about a specific position in the reserve.
For a full list of commands, refer to the project documentation.

# Key Concepts
Polymorphism: The project makes extensive use of polymorphism to manage different species of animals and types of food, allowing for varied behaviors within a unified interface.

Memory Management: The simulator dynamically creates and deletes animals and food during runtime, ensuring proper memory management and avoiding memory leaks.
