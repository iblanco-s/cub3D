# cub3D

cub3D is a 42 school project inspired by the world-famous Wolfenstein 3D game, which was the first FPS in history. Using the MiniLibX library, we must implement raycasting to create a dynamic view inside a 3D maze.

![cub3d](https://github.com/user-attachments/assets/6a3416dd-48f5-4a57-8e3e-11f787c6ef22)

## Installation

To run the cub3D project:

```bash
make
./cub3D maps/map.cub
```

## Controls

Controls for movement and rotation are:

- `W`: move forward
- `S`: move backward
- `A`: strafe left
- `D`: strafe right
- `left arrow`: rotate left
- `right arrow`: rotate right
- `mouse`: rotate by moving the mouse

## Norme

At 42 School, it is expected that all C projects are written according to the Norm, which is the school's coding standard.

```
- No for, do...while, switch, case, goto, ternary operators and variable-length arrays are allowed
- Each function must be a maximum of 25 lines, not counting the function's curly brackets
- Each line must be at most 80 columns wide, comments included
- A function can take 4 named parameters maximum
- No assigns and declarations in the same line (unless static)
- You can't declare more than 5 variables per function
- ...
```
