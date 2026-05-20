# cub3D

> A raycasting engine inspired by the classic Wolfenstein 3D, built as part of the **42 Lisboa** common core curriculum.

![42](https://img.shields.io/badge/42-Lisboa-blue)
![Language](https://img.shields.io/badge/Language-C-00599C)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-red)

---

## 📖 About

**cub3D** is a 3D game engine that recreates the look and feel of early first-person shooters using a **raycasting** algorithm. The player navigates a 2D grid map that is rendered in real time as a 3D environment, with textured walls, configurable floor and ceiling colors, and interactive objects scattered around the level.

This implementation goes beyond the mandatory requirements by introducing original gameplay mechanics that make the world feel alive.

---

## ✨ Features

### 🔥 Fire & Hose System
The map can contain **flames** placed at arbitrary positions. The player is equipped with a **hose** that, when activated by pressing the `SPACE` key, sprays water and **extinguishes** any flame within range. This adds an interactive dimension to the otherwise static raycasted world.

### 🚪 Proximity-Based Automatic Doors
Doors behave **automatically**: they slide open as the player approaches and close again once the player has moved away. No key bindings needed — exploration feels smooth and immersive, much like in modern game engines.

### 🧭 Minimap
A compact **minimap** is always rendered in the corner of the screen, giving the player a quick overview of their surroundings and orientation. Pressing the `M` key toggles a **full-size version** of the map, useful for getting a clear view of the level layout, locating doors, and spotting remaining flames.

### 🗺️ Fully Customizable Map File
The `.cub` map file format allows full configuration of the level without touching the source code:
- **Map layout** — design any shape, as long as it is properly enclosed.
- **Wall textures** — set different textures for North, South, East, and West facing walls.
- **Floor and ceiling colors** — defined as RGB values.
- **Player spawn point and orientation** — chosen directly from the map.
- **Doors and flames** — placed anywhere on the grid.

---

## 🎮 Controls

| Key       | Action                            |
| --------- | --------------------------------- |
| `W`       | Move forward                      |
| `S`       | Move backward                     |
| `A`       | Strafe left                       |
| `D`       | Strafe right                      |
| `←` / `→` | Rotate the camera                 |
| `SPACE`   | Spray water from the hose         |
| `M`       | Toggle full-screen minimap        |
| `ESC`     | Quit the game                     |

Doors open and close on their own based on player proximity.

---

## 🛠️ Build & Run

### Requirements
- A Unix-like system (Linux or macOS)
- `gcc` or `clang`
- `make`
- MiniLibX dependencies (X11 on Linux, OpenGL on macOS)

### Compilation
```bash
git clone https://github.com/RoJa-Team/cub3d
cd cub3d
make
```

### Launching the game
```bash
./cub3D maps/map.cub
```

The program expects a single argument: the path to a valid `.cub` map file.

---

## 📄 Map File Format

A `.cub` file is structured in two sections: **configuration** and **map layout**.

### Configuration block
```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 220,100,0      # Floor color (R,G,B)
C 70,130,180     # Ceiling color (R,G,B)
```

### Map block
```
111111111111
1000000F0001
10000D00N001
100000000001
1000F000D001
111111111111
```

| Symbol | Meaning              |
| ------ | -------------------- |
| `1`    | Wall                 |
| `0`    | Empty (walkable)     |
| `D`    | Door                 |
| `F`    | Flame                |
| `N/S/E/W` | Player spawn + facing direction |

The map must be **fully enclosed by walls**, otherwise the parser will reject it.

---

## 🧠 How It Works

The engine casts one ray per screen column from the player's point of view. For each ray, it computes the distance to the nearest wall using the **DDA (Digital Differential Analyzer)** algorithm, then projects a vertical slice of the corresponding wall texture onto the screen. Floor and ceiling are filled with their configured colors.

Doors and flames are handled as special tiles inspected during the raycasting loop, with state updates tied to the player's position each frame.

---

## 📚 What I Learned

- Raycasting fundamentals and the math behind 3D projection
- Texture mapping and per-pixel rendering with MiniLibX
- Robust file parsing and validation in C
- Memory management in a real-time application
- Building interactive game state on top of a static engine

---

## 👤 Authors

- [@shishudy](https://github.com/shishudy) — `Rafael`
- [@joafern22](https://github.com/joafern22) — `João`

Developed at [42 Lisboa](https://www.42lisboa.com/).
