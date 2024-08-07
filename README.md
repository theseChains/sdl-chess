# sdl-chess
## Introduction
sdl-chess is a C++ application that implements a fully functional chess game using the SDL2 library.

## Installation
### Prerequisites
- C++20 compatible compiler
- CMake 3.20 or higher
- SDL2 library
- SDL2_image library

### Building from source
1. Clone the repository:
    ```sh
    git clone https://github.com/theseChains/sdl-chess.git
    cd sdl-chess
    ```

2. Install dependencies:
    - **Ubuntu**:
        ```sh
        sudo apt-get install libsdl2-dev libsdl2-image-dev
        ```
    - **macOS**:
        ```sh
        brew install sdl2 sdl2_image
        ```

3. Build the project:
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

### Usage

Example:
1. Navigate to the build directory:
    ```sh
    cd build
    ```

2. Run the executable:
    ```sh
    ./app
    ```

## Screenshots
<img src="screenshots/start-position.png?" alt="Start position" width="500" />
<img src="screenshots/some-moves.png?" alt="After some moves" width="500" />
<img src="screenshots/checkmate.png?" alt="Checkmate" width="500" />

## Contributions
Old piece textures by: [Ckyannahall2023](https://github.com/Ckyannahall2023)
