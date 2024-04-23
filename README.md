# C++ Projects Repository

This repository contains three distinct C++ projects, each demonstrating different applications and data structures. Below is a brief overview of each project.

## 1. JerryBoree - C

**JerryBoree** is a system that manages information about "Jerries" using various data structures:
- **MultiValueHashTable**: Uses physical characteristics as keys to map to linked lists of Jerries.
- **HashTable**: Maps Jerry IDs to their corresponding linked list entries.
- **LinkedList**: Stores information about planets and Jerries, serving as the primary data structure for managing Jerry data.

The system ensures integrity and synchronization between data structures through careful memory management and function assignments for operations like copy and delete.

## 2. CoordRobotsNavigator - C++

**CoordRobotsNavigator** simulates remote-controlled robots performing guard duties in a grid environment. It features:
- **Directional Movement**: Robots can move in four cardinal directions with movements restricted by predefined map boundaries.
- **Map Handling**: Utilizes a 7x7 grid where each cell is either passable ('0') or blocked ('1').
- **Dynamic Map Input**: While primarily operating with two maps, the system is designed to handle additional maps dynamically without persistent storage.

The application demonstrates handling of dynamic data and control of autonomous units in a simulated environment.

## 3. PoliticalElectionSimulator - C++

**PoliticalElectionSimulator** models a political election system with features such as:
- **Two-party System**: Supports multiple parties within two main political factions (e.g., Republicans and Democrats).
- **Election Cycles**: Conducts elections in two phases: primaries to choose party leaders and general elections to determine the governing party.
- **Observer Pattern**: Utilizes the observer design pattern to manage and propagate updates across the system effectively.

This project showcases the application of design patterns to solve complex problems involving state synchronization and event handling.

Each project is designed to be independent, focusing on specific programming challenges and solutions. Detailed documentation and setup instructions are available within each project's subdirectory.

