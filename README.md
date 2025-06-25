# 🚗 Rush Hour — OOP City Driving Game

### This repository implements a city driving and delivery game in C++, utilizing core Object-Oriented Programming (OOP) principles and graphics rendering through OpenGL for a dynamic, interactive user experience.

## Project Overview

#### The project features:

1. **Procedurally generated city grid:** Randomized placement of buildings, obstacles, fuel stations, passengers, and delivery boxes.
2. **Two Game Modes:**

   * **Taxi Driver** — Pick up and drop off passengers at random locations.
   * **Delivery Driver** — Pick up and deliver packages across the city.
3. **NPC Traffic:** Multiple rule-based vehicles move through the map, creating dynamic obstacles.
4. **Resource & Score Management:** Players must manage fuel, wallet (money), and score while completing jobs.
5. **Event & Collision System:** Collisions with NPCs or obstacles lead to score deductions; successful tasks earn rewards.
6. **Simple Graphics Rendering:** Built using OpenGL for 2D grid-based visuals.

---

## Repository Structure

```
RushHour.cpp        # Main game code, including all classes, logic, rendering, and input handling.
util.h              # Utility header for custom OpenGL drawing functions.
```

> *All OOP logic is encapsulated in classes such as `Player`, `Board`, `Vehicle`, and their derivatives.*

---

## Setup Instructions

### 1. Dependencies

* **C++ Compiler** (g++)
* **OpenGL** & **freeglut** (or compatible GLUT implementation)
* Ensure `util.h` is present in the project directory.

### 2. Compilation

#### On Windows (MinGW/g++ with freeglut):

```bash
g++ -g3 -fmessage-length=0 -o game util.cpp RushHour.cpp -lfreeglut -lopengl32 -lglu32 -lfreeimage -pthread
```

#### On Linux:

```bash
g++ -g3 -fmessage-length=0 -o game util.cpp RushHour.cpp \
-L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib \
-lglut -lGLU -lGL -lX11 -lfreeimage -pthread
```

### 3. Running

```bash
./RushHour
```

---

## Gameplay & Controls

* **Objective:** Complete as many passenger pickups/deliveries as possible before time or fuel runs out.
* **Role Selection:**

  * Taxi Driver: Pick up passengers and drop them at random destinations.
  * Delivery Driver: Collect delivery boxes and deliver them across the city.
* **Resource Management:** Fuel can be bought using money earned from jobs. Score is increased for successful deliveries and decreased for crashes.
* **Game Over:** Occurs when fuel or time runs out, or score drops below zero.

### Controls

| Key / Input         | Action                                |
| ------------------- | ------------------------------------- |
| **Arrow Keys**      | Move car (Up, Down, Left, Right)      |
| **Spacebar**        | Pick up or drop off passenger/package |
| **R**               | Reset the game                        |
| **P**               | Switch role at garage                 |
| **B**               | Buy fuel at adjacent fuel station     |
| **Esc**             | Exit game                             |
| **Mouse** (on menu) | Select role from main menu            |

---

## Technologies Used & Implementation Challenges

### Technologies

* **C++**: Core programming language, demonstrating OOP design.
* **OpenGL/freeglut**: For 2D game rendering and user interaction.
* **Custom utility functions**: For simplified graphics.

### Implementation Challenges

* **OOP Design:** Ensuring all gameplay mechanics are handled via clean, modular class design.
* **Randomized Map Generation:** Procedurally generating a balanced city layout on each reset.
* **Collision/Event Handling:** Efficiently managing interactions between player, NPCs, and game objects.
* **Real-Time Rendering:** Smooth graphics using OpenGL and handling user input in real time.

---

## Credits

* **Aarab Malik**
  24i-2552 | DS-B | FAST NUCES

*This project was developed for the OOP course at FAST NUCES.*

---

> For issues or suggestions, open an issue or pull request on [this repo](https://github.com/aarab-malik/rush-hour).

---

Let me know if you want to add screenshots, a sample GIF, or make it even more concise for your submission!
