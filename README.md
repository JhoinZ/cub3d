# Cub3D (42 cursus)

![Cub3D](https://img.shields.io/badge/42-Telefónica-blue?style=for-the-badge)
![Language](https://img.shields.io/badge/C-100%25-success?style=for-the-badge)
<!-- ![Mark](https://img.shields.io/badge/Mark-125%2F100-brightgreen?style=for-the-badge) -->

A stunning 3D maze exploration game built from scratch using raycasting technology. This project brings the classic Wolfenstein 3D experience to life with modern features and smooth gameplay.

## 🎮 Features

- **Real-time 3D Rendering** using custom raycasting algorithm
- **Dynamic Texture Mapping** for immersive wall visuals
- **Smooth Player Movement** with collision detection
- **Intuitive Controls** (WASD + Mouse look)
- **Custom Map Parser** supporting `.cub` format
- **Multiple Resolution Support**
- **Efficient Rendering** with MiniLibX
- **Memory Leak Free** with proper cleanup

## 🚀 Quick Start

### Prerequisites
- GCC compiler
- MiniLibX library
- Make

### Installation & Compilation

```bash
# Clone the repository
git clone https://github.com/JhoinZ/cub3d.git
cd cub3d

# Compile the project
make

# Run with a map file
./cub3d maps/level1.cub
```

## 🎯 Controls

| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move player |
| `←` `→` | Rotate camera |
| `ESC` | Exit game |
| `Mouse` | Look around |

## 🗺️ Map Format

Create your own maps using the `.cub` format:

```cub
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm
F 220,100,0
C 135,206,235

111111
100001
1010N1
100001
111111
```


## 🧠 Technical Highlights

- **Custom Raycasting Engine** inspired by Wolfenstein 3D
- **Digital Differential Analysis (DDA)** algorithm for efficient wall detection
- **Texture Buffering** for optimal performance
- **Bresenham's Line Algorithm** for clean rendering
- **Modular Architecture** for easy maintenance

## 👥 Team

This project was developed as part of the 42 Telefónica curriculum by:

- **Fernando** - [@fog-3](https://github.com/fog-3)
- **Filippo** - [@JhoinZ](https://github.com/JhoinZ)

## 📋 Requirements

- ✅ No memory leaks
- ✅ Clean window management
- ✅ Smooth 60+ FPS performance
- ✅ Full error handling
- ✅ Norm-compliant code
- ✅ Multi-platform compatibility

## 🎨 Screenshots

*Gameplay screenshots will be added here*

---

<div align="center">

**"From 2D arrays to immersive 3D worlds"**

*42 Telefónica - 2025*

</div>
