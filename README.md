# Minesweeper

This is a from-scratch recreation of Minesweeper using SDL2 and C++. This project was mostly a learning exercise for myself as I was teaching myself to write code at the time. You'll notice in the source code that certain things, like the hash table, are not necessary for this application.

The reason for this is I used this project, which is one of the larger personal projects I've made, to test/learn some different concepts and structures. This version is feature-complete and bug free, with the exception of a win-state which I was too lazy to implement at the time.

## How to play

If you're unfamiliar with Minesweeper, the rules are very simple.

First, **the bomb counter is your friend.** In the top left, you'll notice a screen that displays a number. This is the number of _active_ bombs on the board, meaning bombs that potentially aren't flagged. This number becomes very important near the end of the board, as it could clue you into what tiles are safe and which might still have a bomb.

However, this number doesn't represent the **actual** number of bombs still in play. Whenever you put down a flag, this number will go down. If you pick up a flag, it goes back up. The counter keeps track of how many bombs are left if **all** your flags are correct.

Flagging is an important mechanic for two reasons:

1. It keeps you from mistakenly clicking the wrong tile
2. It helps you keep track of the state of the board.

It's entirely possible to flag a tile that isn't a bomb though, so pay attention.

Tile clearing is the largest chunk of the game. Just click tiles to reveal them. This has a few mechanics surrounding it, none of which are complicated:

1. Each tile is aware of it's neighbors in a 3x3 configuration. That means a tile can see neighbors to the top left/right and bottom left/right.
2. A tile is assigned a number based on how many of it's neighbors are bombs. If a tile has the number **2**, that means any 2 of the 8 tiles touching it are bombs.
3. If a tile has no number, that obviously means that none of it's neighbors are bombs. In the scenario where more than 1 non-numbered tile are connected, all the connected tiles will auto-clear. This is extremely useful at the start of the game as it gives you a starting point to go off of.
4. When a bomb is clicked, you lose.

The point of the game is to clear **ALL** non-bomb tiles. Usually you will have all of the bomb tiles flagged by the end, or at least 99% of them.

## Features

- **Flagging** - Flagging prevents a tile from being revealed when clicked. In the case of a bomb being clicked, all the flags that are on bombs (correctly placed) will remain the same. However, flags that are not on bombs (incorrectly placed) will turn bright red, indicating the incorrect placement.
- **Lose State** - In the event of a bomb being clicked and revealed, the game locks and you can no longer reveal any tiles. Also, all the bombs on the board will reveal themselves.
- **Recursive Clearing** - Connected non-numbered tiles will recursively clear themselves once one is clicked and revealed.
- **Difficulty Settings** - There are 3 difficulty settings, which scale the board to 3 different sizes. The amount of bombs scales based on the board size, and each board size will always have it's corresponding amount of bombs; It is not random.
- **Random Board State** - The board itself is completely random. This is achieved by an algorithm that first places the bombs across the array (board) using a mersenne twister random number generator, and a second pass is done to number the tiles. This can be observed by pressing the **E** key and repeatedly resetting the board. The **E** key toggles the tile states between in-play and all-revealed, allowing the user to see the random states of the board. This was mainly implemented for debug purposes and never removed.
- **Bomb Counter** - A bomb counter keeps track of the total number of bombs, and then minus 1 for every flag on the board. If a flag is removed, it adds 1 back to the counter.

## Dependencies

This project uses [SDL2](https://www.libsdl.org/) and [SDL_image](https://github.com/libsdl-org/SDL_image) for window creation and rendering.

### Installing SDL2

#### Windows

> [!NOTE]
> This project is set to link statically on Windows, so if you download the zip from SDL, make sure to change the linker flag. Otherwise, build SDL2 from source to get the static libraries.

Use the link to SDL2's webpage, and navigate to the Downloads/Releases tab. SDL recently released SDL3,
and I'm not sure on the backwards compatibility with SDL2, so it's safest to just fetch the SDL2 zip.

Alternatively, you may build it yourself if you want static libraries.

1. Navigate to [SDL](https://github.com/libsdl-org/SDL) on github
2. Run the commands below

```bash
git clone https://github.com/libsdl-org/SDL
cd SDL
git checkout SDL2
cd ..
mkdir build
cd build
cmake ../SDL
cmake --build .
```

This should build the static and dynamic versions of SDL in the `build` directory. Consult SDL's github page if any issues are encountered, or submit and issue.

Also be sure to adjust the `CMakeLists.txt` based on the path of your libraries/header files.

#### Linux

> [!NOTE]
> This project is set to dynamically link on Linux, so the easiest (and recommended) approach is just to get the SDL2 library from your package manager

<details>
    <summary>Arch</summary>

```bash
sudo pacman -S sdl2
```

</details>

<details>
    <summary>Void</summary>

```bash
sudo xbps-install -S SDL2-devel
```

</details>

<details>
    <summary>Debian</summary>

```bash
sudo apt install libsdl2-dev
```

</details>

### Installing SDL_image

#### Windows

[SDL_image](https://github.com/libsdl-org/SDL_image) can be found at the attached link. Compiled libaries are available, though if you wish to build it yourself,
simply follow the [INSTALL.md](https://github.com/libsdl-org/SDL_image/blob/main/INSTALL.md) on the github page.

> [!NOTE]
> Make sure you're on the correct branch!

#### Linux

SDL_image can be obtained through your package manager.

<details>
    <summary>Arch</summary>

```bash
sudo pacman -S sdl2_image
```

</details>

<details>
    <summary>Void</summary>

```bash
sudo xbps-install -S SDL2_image-devel
```

</details>

<details>
    <summary>Debian</summary>

```bash
sudo apt install libsdl2-image-dev
```

</details>

## Building

Once you have the dependencies, simply run the following commands:

```bash
cmake . -B build
cd build
make
```
