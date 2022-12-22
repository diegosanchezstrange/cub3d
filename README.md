# cub3d

My first RayCaster
---

This project aims to create a "game" using `raycasting`. This is the same technique used in games like [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D)

<img width="1912" alt="Screen Shot 2022-12-22 at 6 17 39 PM" src="https://user-images.githubusercontent.com/28633882/209190371-7b1483e0-bc94-4fbc-a58b-f4cf43a60e9d.png">

# Usage

The game only runs in Linux and MacOs

To execute the game first clone the repo:

```
git clone https://github.com/diegosanchezstrange/cub3d.git
```

Then inside the repo run `make`

When everything is finished compiling just run the game :

```
./cub3d <path/to/valid/map>
```

There are some examples of valid maps in the test_maps folder and some examples of textures in the textures map

# Map Format

The game needs a file containing the map to run. This file has the following format:

```
NO ./textures/wood.xpm
SO ./textures/wood.xpm
WE ./textures/wall3.xpm
EA ./textures/wood.xpm

F 10,10,0
C 30,0,255

        111111111111111111111111111
        100000000011000000000000001
        100000000011111000010000001
        100000N0001   1000010000001
        10010000001   1000010000001
11111111101100000111111000000000001
10000000001100000111000011111111111
10000000000000001100000010001
10101111111111011101010010001
10000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110011
11110111 1110101 101111010001
11111111 1111111 111111111111
```

The `NO SO WE EA` params refer to the different textures rendered depending on the cardinal direction you are looking at. This textures must be in valid xpm format

Next the `F` and `C` params refer to the colors of the floor and the cealing in `RGB` format

Finally the map itself. The maps consists of 4 types of characters.

- `1`: This are the walls of the map 
- `0`: This is playable area
- `N S W E`: Refers to the startin position of the player and the orientation of the camera when spawning
- ` `: spaces are also valid characters but is has to be impossible to access them, otherwise the map wont load and the game will throw and error.

The map has to be enclosed by `1`'s otherwise the game throws an error.

## Controls

- WASD to move
- Right and left arrows to rotate the camera
- ESC to quit
