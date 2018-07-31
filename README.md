# SDLPong

The Pong game developed with C++ and SDL2 (Simple DirectMedia Layer) libraries.

Features:

- Single Player mode
- Local Multiplayer mode (two players in the same computer)
- LAN Multiplayer (can play through Internet by port-forwarding)

## In-game pictures

# ![menu](https://imgur.com/H0tTtw1.png)
# ![pong1](https://imgur.com/H2ne4mL.png)
# ![pong2](https://imgur.com/MhPoYu3.png)

## Download and play the game
 
If you want the game's build download for Windows, download just the zip file it from the *Releases* tab.

## Controls

**Player 1 (Left Pad)**

- W to move upwards
- S to move downwards

**Player 2 (Right) (Local multiplayer only)**

- Arrow Up to move upwards
- Arrow Down to move downwards

**Multiplayer**

While playing on multiplayer mode, Server will play as the left pad and Client as the right pad.
The controls are the same as Player 1 in either case.

## Build Requirments
 
In order to build or modify this source code you will need the following libraries:

- SDL2 (https://www.libsdl.org/download-2.0.php)
- SDL2 Image extension (https://www.libsdl.org/projects/SDL_image/)
- SDL2 Net (https://www.libsdl.org/projects/SDL_net/)

You will also need the following programs:

- CMake (https://cmake.org/)
- Git (Recommended)(https://git-scm.com/)

## Build steps

Once you have downloaded all the dependencies you can build the project by following these steps:

  1a. Clone this repository using git: git clone https://github.com/MartGon/SDLPong

  1b. Download the source code from the *Releases* tab

  2a. (Linux) Run CMake, CMake should find the libraries for you when running on Linux. You'll have to link the libraries manually otherwise

  2b. (Windows) You'll neeed to tell CMake where to look for each one of the SDL libraries that you have downloaded

  3a. You can now compile the project with your preferred IDE (or *make*, in case of Linux)
  
 ## About us

This game was made for learning and entertainment purposes. I always wanted to learn C++ and CMake and I think this was a really good way for achieving that goal.
 
