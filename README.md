# CS Project 1 - BitBoard Checkers

Zachary Derival

This project implements a checkers game using bitboards in C. Each piece on the 8x8 board is represented by a single bit in an integer, allowing  manipulation using bitwise operations.

- Moving pieces
- Capturing opponent pieces
- King promotion
- Detecting a win
- Two-player gameplay via console input


## Gameplay Instrusctions 
1. The board displays 8 rows and 8 columns. Only dark squares are playable.
2. Pieces are represented as:
   - `r` = Player 1 regular piece  
   - `R` = Player 1 king  
   - `b` = Player 2 regular piece  
   - `B` = Player 2 king  
   - `.` = Empty playable square
3. Players take turns. Player 1 moves first.
4. Enter moves in the format: from_row from_col to_row to_col moves a piece from row 2, column 1 to row 3, column 0.
- Only valid moves will be accepted; invalid or non-playable squares will return an error.
5. Pieces reaching the far edge are automatically promoted to kings.
6. Capture moves remove opponent pieces automatically.
7. The game ends when a player has no remaining pieces. The other player wins.

  
## Build Instructions (CLion)

1. Open CLion and select Open. Choose the project directory containing your source files main.c, bitops.c, etc.).
2. If CLion asks, create a simple CMakeLists.txt in the project root:

cmake_minimum_required(VERSION 4.0)
project(untitled3 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled3 main.c Phase1.c)

set(CMAKE_C_STANDARD 11)



A lot to learn about C programming 
