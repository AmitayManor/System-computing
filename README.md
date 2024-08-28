
# Universal Manager for Space Travel

## Project Description

The Universal Manager project is a comprehensive system for managing interstellar travel across various companies. The system encompasses multiple galaxies, each containing solar systems with their own planets. Companies operating within this system have fleets of spacecraft and conduct interstellar travels. The Universal Manager provides functionalities to manage, display, and manipulate these cosmic entities and their associated travels.

## Features

- **Universal Manager**: A centralized system to manage galaxies, solar systems, planets, and companies.
- **Galaxy Management**: Functions to add, display, and manage galaxies and their solar systems.
- **Solar System Management**: Capabilities to handle solar systems, including adding planets and updating risk levels.
- **Planet Management**: Tools for adding, displaying, and managing planets within solar systems.
- **Company Management**: Features to manage companies, including their fleets of spacecraft and interstellar travels.
- **Data Import/Export**: Import and export data functionalities in both text and binary formats.
- **Search and Sort**: Advanced search and sort capabilities for companies and their elements.
- **Special Operations**: Special functions to find the longest travel and the most dangerous cosmic element.

## File Structure

- **company.c/h**: Contains definitions and implementations related to managing companies and their operations.
- **date.c/h**: Provides functions and structures for handling dates.
- **galaxy.c/h**: Manages galaxies, including adding and displaying solar systems.
- **interstellar_travel.c/h**: Handles interstellar travel operations for companies.
- **location.c/h**: Defines the location structure and related operations.
- **macros.h**: Contains macro definitions used throughout the project.
- **main.c**: The main entry point of the program, providing a menu for interacting with the Universal Manager.
- **permission.h**: Defines permission levels for different cosmic entities.
- **planet.c/h**: Manages planets, including adding and displaying planets within solar systems.
- **solar_system.c/h**: Handles solar system operations, including managing planets and updating risk levels.
- **spacecraft.c/h**: Defines spacecraft and their operations within companies.
- **universal_manager.c/h**: The core of the project, managing the entire system of galaxies, solar systems, planets, companies, and travels.
- **utility.c/h**: Utility functions used across the project for various common operations.

## About the Developer

I am a passionate computer science student with a strong interest in developing innovative applications that address niche areas within sports, development, and nutrition. This project, part of my portfolio, showcases my skills in C programming, system management, and software development. My objective is to create impactful software solutions that combine technical proficiency with creative problem-solving.

## Getting Started

### Prerequisites

- C compiler (e.g., GCC)
- Standard C libraries

### Building the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/universal-manager.git
   cd universal-manager
   ```

2. Compile the project:
   ```bash
   gcc -o universal_manager main.c company.c date.c galaxy.c interstellar_travel.c location.c planet.c solar_system.c spacecraft.c universal_manager.c utility.c -I.
   ```

### Running the Project

Execute the compiled binary:
```bash
./universal_manager
```

### Usage

Upon running the program, you will be presented with a menu to interact with the Universal Manager. Options include displaying the system, managing companies, sorting elements, searching elements, and performing special operations.


---
