*This project has been created as part of the 42 curriculum by ramarti2 and dperez-p.*

# cub3D

## Description

cub3D is a 42 school project inspired by the legendary game **Wolfenstein 3D**.  
The objective of the project is to build a simple 3D game engine using the **raycasting** technique with the **MiniLibX** graphical library.

The program renders a first-person perspective inside a maze described by a `.cub` configuration file. The player can move through the map, rotate the camera, and interact with the environment while the engine dynamically calculates walls and textures in real time.

This project focuses on:
- Computer graphics fundamentals
- Raycasting mathematics
- Event handling and real-time rendering
- Parsing and validation of configuration files
- Memory management in C
- Optimization and clean architecture

---

## Features

- First-person 3D rendering using raycasting
- Wall collision detection (technically part of bonus)
- Smooth player movement and camera rotation
- Textured walls
- Custom `.cub` map parsing
- Floor and ceiling colors
- Keyboard controls
- Error handling and map validation

### Bonus Features

- Minimap
- Mouse rotation
- Doors that open and close

---

## Technologies

- Language: **C**
- Graphics Library: **MiniLibX**
- Compilation: **Makefile**
- Operating System: **Linux**

---

## Instructions

### Clone the Repository

```bash
git clone <repository_url>
cd cub3D
```

### Compile the Project

```bash
make
```

### Compile Bonus Version

```bash
make bonus
```

### Clean Object Files

```bash
make clean
```

### Full Clean

```bash
make fclean
```

### Recompile Everything

```bash
make re
```

---

## Usage

Run the program with a valid `.cub` map:

```bash
./cub3D map/example.cub
```

### Controls

| Key       | Action         |
| --------- | ---------------|
| `W`       | Move forward   |
| `S`       | Move backward  |
| `A`       | Move left      |
| `D`       | Move right     |
| `←` / `→` | Rotate camera  |
| mouse     | Rotate camera* |
| `E`       | Open door*     |
| `M`       | Open minimap*  |
| `ESC`     | Exit game      |

\* bonus feature

---

## Map Format

The `.cub` file contains:

* Texture paths
* Floor and ceiling colors
* The game map layout

Example:

```txt
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm

DOOR bonus_assets/door.xpm (bonus)

F 220,100,0
C 225,30,0

1111111111
1000000001
100N000001
1111111111
```

### Map Rules

* The map must be closed/surrounded by walls
* Valid characters:

  * `0` → empty space
  * `1` → wall
  * `N/S/E/W` → player spawn position and direction
  * `D` → closed door (bonus)
  * `O` → open door (bonus) 
* Only one player starting position is allowed

---

## Raycasting Overview

The rendering engine uses **raycasting** to simulate a 3D environment from a 2D map.

For every vertical stripe on the screen:

1. A ray is cast from the player position
2. The engine detects wall intersections
3. The distance is calculated
4. The height of a wall slice is calculated and projected onto the screen
5. Textures are applied to the rendered walls

This technique creates the illusion of depth while remaining computationally efficient.

---

## Challenges

Some of the main challenges encountered during development included:

* Correctly implementing the DDA algorithm
* Preventing fish-eye distortion
* Parsing malformed maps safely
* Managing textures and image buffers
* Handling memory leaks and segmentation faults
* Handling map parsing logic
* Understanding the math behind raycasting

---

## Resources

### Documentation & Tutorials

* MiniLibX Documentation
* [Lode Vandevenne’s Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
* [Medium Article on Cub3D by Abdilah CH](https://devabdilah.medium.com/3d-ray-casting-game-with-cub3d-7a116376056a)
* 42 Subject PDF

### AI Usage

AI tools were used during the development of this project for:

* Clarifying raycasting concepts and mathematical formulas
* Debugging specific issues and segmentation faults
* Improving code organization ideas
* Generating documentation structure and README formatting
* Reviewing Makefile and parsing logic approaches

All implementation, debugging validation, architecture decisions, and final code integration were completed manually by the authors.
