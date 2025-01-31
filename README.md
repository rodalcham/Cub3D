# 2D Raycaster Game

A simple 2D raycasting engine inspired by classic games like **Wolfenstein 3D**. The game features dynamic lighting, texture rendering, and player movement in a 2D world.

## Features

- **Raycasting** for 2D rendering.
- Textures for walls, floors, and ceilings.
- Interactive elements such as a **minimap** and **dynamic player movement**.
- Smooth gameplay with **keyboard controls** for movement and direction changes.

## Requirements

To build and run the game, you need:

- **C Compiler** (e.g., `gcc`)
- **MLX Library** (MinilibX)
- A Unix-based system (Linux or macOS)
- Libraries: `pthread` and `math`

## Installation and Setup

Ensure the **MinilibX library** is installed. You can install it using your system's package manager or by downloading it from [MinilibX](https://github.com/42Paris/minilibx-linux).

Modify the `Makefile` if necessary to point to your MinilibX installation.

## Compilation

To compile the project, run:

```bash
make
```

This will produce an executable named `cub3D`.

## Running the Game

To start the game, provide a `.cub` file as input, which defines the map and textures:

```bash
./cub3D <map_file>.cub
```

- `<map_file>.cub`: The path to a `.cub` file that contains map details and texture paths.

### Example:

```bash
./cub3D maps/sample_map.cub
```

## Controls

- **W/A/S/D**: Move forward, backward, left, and right.
- **Arrow Keys**: Rotate the player view.
- **M**: Toggle the minimap.
- **ESC**: Exit the game.

## Notes

- The `.cub` file should specify textures for north, south, east, and west walls, along with colors for the ceiling and floor.
- Player starting position is defined in the map with characters like `N`, `S`, `E`, or `W`.

## License

This project is open-source and available under the MIT License. Contributions are welcome!

---

Enjoy exploring your 2D world!
![](https://private-user-images.githubusercontent.com/142218652/408624709-1f36b085-deb6-4193-9b19-d40a05a0131e.mp4?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MzgzMzgzNTYsIm5iZiI6MTczODMzODA1NiwicGF0aCI6Ii8xNDIyMTg2NTIvNDA4NjI0NzA5LTFmMzZiMDg1LWRlYjYtNDE5My05YjE5LWQ0MGEwNWEwMTMxZS5tcDQ_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjUwMTMxJTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI1MDEzMVQxNTQwNTZaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT01MGYxYmU2MGVlODA4OWZjNmI3NDM2ZDZjMzEzZGE5YmEwMDYwNzkzNWFjZmEzMTFiNjVjNDM3M2U3YjFlODdlJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCJ9.KXnA8gPYN91BO3OkLFJdBDlzHDyBXjsQvYsH8DtWfmg)
