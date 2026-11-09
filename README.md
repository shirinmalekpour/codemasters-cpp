# codemasters-cpp
# Codemasters

A text-based, turn-based strategy game inspired by chess, written in C++ as an advanced programming course project. Two players each command a team of four pieces on an 8x8 board, and the goal is to destroy the opponent's Master piece. If nobody manages that within 30 turns, the game ends in a draw.

## Features

- 8x8 board stored as a 2D array of `Piece*`, printed to the terminal after every turn
- Four piece types, each with its own movement rules and behavior
- Three actions per turn: `move`, `attack`, `ability`
- Win condition (Master destroyed) and a 30-turn draw limit
- Input validation for invalid moves, attacks on teammates, and empty cells

## Pieces

| Piece | Board symbol | Movement | Behavior |
|---|---|---|---|
| Master | `wM` / `BM` | 1 cell in any direction | No attack or ability; losing it loses the game |
| Attacker | `wA` / `BA` | Up to 2 cells in any direction | Attack deals 70 damage |
| Defender | `wD` / `BD` | 1 cell in any direction | Shield ability: the next hit on a nearby piece does half damage |
| Ranged | `wR` / `BR` | Up to 2 cells horizontally or vertically | Attacks up to 3 cells away in a straight line, 50 damage |

Every piece starts with 100 HP. Lowercase `w` is Player 1 (white), uppercase `B` is Player 2 (black).

## How to play

Each turn, the program asks for an action, then for coordinates. Coordinates are `row column`, both from 0 to 7, matching the numbers printed around the board.

```
Enter action (move/attack/ability): move
Enter piece coordinates (x1 y1) and target coordinates (x2 y2): 0 4 2 4
```

## Code design

- **`pieces.h` / `pieces.cpp`**: an abstract base class `Piece` with pure virtual functions `isValidMove`, `attack` and `useAbility`, and four derived classes (`Master`, `Attacker`, `Defender`, `Ranged`) that each override them.
- **`main.cpp`**: board setup, display, the game loop, and cleanup.

Object-oriented concepts used:

- **Inheritance and abstraction:** `Piece` is an abstract class that defines the interface shared by all pieces.
- **Polymorphism:** the board holds `Piece*` pointers, and calls to `isValidMove`, `attack` and `useAbility` dispatch to the right piece type at runtime.
- **Encapsulation:** piece state (health, position, shield, ability flags) is protected and accessed through getters and setters.
- **Dynamic memory:** pieces are created with `new`, destroyed pieces are deleted when they die, and a virtual destructor plus a cleanup loop at the end of `main` free the rest.

## Build and run

```
g++ -std=c++17 main.cpp pieces.cpp -o codemasters
./codemasters
```

## Notes

Course project for Advanced Programming, University of Tehran.
