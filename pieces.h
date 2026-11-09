#ifndef PIECES_H
#define PIECES_H

#include <iostream>
#include <string>

// Define the board size
const int BOARD_SIZE = 8;

// Forward declaration of the Piece class
class Piece;

// Define piece types
enum PieceType {
    WHITE_MASTER, WHITE_ATTACKER, WHITE_DEFENDER, WHITE_RANGED,
    BLACK_MASTER, BLACK_ATTACKER, BLACK_DEFENDER, BLACK_RANGED,
    EMPTY
};

// Base class for all pieces
class Piece {
protected:
    PieceType type;
    int health;
    int x, y;
    bool abilityUsed;
    bool shieldActive;

public:
    Piece(PieceType type, int health, int x, int y);
    virtual ~Piece() = default;

    // Pure virtual functions (must be implemented by derived classes)
    virtual bool isValidMove(int x2, int y2) const = 0;
    virtual void attack(Piece& target, int& gameOver, Piece* board[BOARD_SIZE][BOARD_SIZE]) = 0; // Updated to accept board
    virtual void useAbility(Piece* board[BOARD_SIZE][BOARD_SIZE]) = 0;

    // Getters and setters
    PieceType getType() const;
    int getHealth() const;
    void setHealth(int health);
    int getX() const;
    int getY() const;
    void setPosition(int x, int y);
    bool isShieldActive() const;
    void setShieldActive(bool active);
    bool isAbilityUsed() const;
    void setAbilityUsed(bool used);
};

// Derived classes for specific piece types
class Master : public Piece {
public:
    Master(PieceType type, int health, int x, int y);
    bool isValidMove(int x2, int y2) const override;
    void attack(Piece& target, int& gameOver, Piece* board[BOARD_SIZE][BOARD_SIZE]) override;
    void useAbility(Piece* board[BOARD_SIZE][BOARD_SIZE]) override;
};

class Attacker : public Piece {
public:
    Attacker(PieceType type, int health, int x, int y);
    bool isValidMove(int x2, int y2) const override;
    void attack(Piece& target, int& gameOver, Piece* board[BOARD_SIZE][BOARD_SIZE]) override;
    void useAbility(Piece* board[BOARD_SIZE][BOARD_SIZE]) override;
};

class Defender : public Piece {
public:
    Defender(PieceType type, int health, int x, int y);
    bool isValidMove(int x2, int y2) const override;
    void attack(Piece& target, int& gameOver, Piece* board[BOARD_SIZE][BOARD_SIZE]) override;
    void useAbility(Piece* board[BOARD_SIZE][BOARD_SIZE]) override;
};

class Ranged : public Piece {
public:
    Ranged(PieceType type, int health, int x, int y);
    bool isValidMove(int x2, int y2) const override;
    void attack(Piece& target, int& gameOver, Piece* board[BOARD_SIZE][BOARD_SIZE]) override;
    void useAbility(Piece* board[BOARD_SIZE][BOARD_SIZE]) override;
};

#endif // PIECES_H