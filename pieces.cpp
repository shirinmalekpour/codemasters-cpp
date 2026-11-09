#include "pieces.h"

// Base class implementation
Piece::Piece(PieceType type, int health, int x, int y)
    : type(type), health(health), x(x), y(y), abilityUsed(false), shieldActive(false) {}

PieceType Piece::getType() const { return type; }
int Piece::getHealth() const { return health; }
void Piece::setHealth(int health) { this->health = health; }
int Piece::getX() const { return x; }
int Piece::getY() const { return y; }
void Piece::setPosition(int x, int y) { this->x = x; this->y = y; }
bool Piece::isShieldActive() const { return shieldActive; }
void Piece::setShieldActive(bool active) { shieldActive = active; }
bool Piece::isAbilityUsed() const { return abilityUsed; }
void Piece::setAbilityUsed(bool used) { abilityUsed = used; }

// Master class implementation
Master::Master(PieceType type, int health, int x, int y) : Piece(type, health, x, y) {}

bool Master::isValidMove(int x2, int y2) const {
    int dx = abs(x2 - x);
    int dy = abs(y2 - y);
    return (dx <= 1 && dy <= 1); // Move one square in any direction
}

void Master::attack(Piece& target, int& gameOver,Piece* board[BOARD_SIZE][BOARD_SIZE]) {
    std::cout << "Masters cannot attack.\n";
}

void Master::useAbility(Piece* board[BOARD_SIZE][BOARD_SIZE]) {
    std::cout << "Masters have no special ability.\n";
}

// Attacker class implementation
Attacker::Attacker(PieceType type, int health, int x, int y) : Piece(type, health, x, y) {}

bool Attacker::isValidMove(int x2, int y2) const {
    int dx = abs(x2 - x);
    int dy = abs(y2 - y);
    return (dx <= 2 && dy <= 2); // Move up to 2 squares in any direction
}

void Attacker::attack(Piece& target, int& gameOver, Piece* board[BOARD_SIZE][BOARD_SIZE]) {
    // Check if the target is on the same team
    if ((type >= WHITE_MASTER && type <= WHITE_RANGED && target.getType() >= WHITE_MASTER && target.getType() <= WHITE_RANGED) ||
        (type >= BLACK_MASTER && type <= BLACK_RANGED && target.getType() >= BLACK_MASTER && target.getType() <= BLACK_RANGED)) {
        std::cout << "Cannot attack your own team!\n";
        return;
    }

    if (target.getHealth() <= 0) {
        std::cout << "Target is already destroyed.\n";
        return;
    }

    int damage = 70;
    if (target.isShieldActive()) {
        damage /= 2;
        target.setShieldActive(false);
        std::cout << "Shield activated! Damage reduced by 50%.\n";
    }

    target.setHealth(target.getHealth() - damage);
    std::cout << "Attack executed. Target health: " << target.getHealth() << "\n";

    if (target.getHealth() <= 0) {
        std::cout << "Target destroyed!\n";
        if (target.getType() == WHITE_MASTER || target.getType() == BLACK_MASTER) {
            gameOver = (target.getType() == WHITE_MASTER) ? 2 : 1;
        }
        // Replace the target with an EMPTY piece (nullptr)
        delete &target; // Free the memory of the destroyed piece
        board[target.getX()][target.getY()] = nullptr; // Set the cell to nullptr
    }
}

void Attacker::useAbility(Piece* board[BOARD_SIZE][BOARD_SIZE]) {
    std::cout << "Attackers have no special ability.\n";
}

// Defender class implementation
Defender::Defender(PieceType type, int health, int x, int y) : Piece(type, health, x, y) {}

bool Defender::isValidMove(int x2, int y2) const {
    int dx = abs(x2 - x);
    int dy = abs(y2 - y);
    return (dx <= 1 && dy <= 1); // Move one square in any direction
}

void Defender::attack(Piece& target, int& gameOver,Piece* board[BOARD_SIZE][BOARD_SIZE]) {
    std::cout << "Defenders cannot attack.\n";
}

void Defender::useAbility(Piece* board[BOARD_SIZE][BOARD_SIZE]) {
    if (abilityUsed) {
        std::cout << "Ability already used.\n";
        return;
    }

    int protectX, protectY;
    std::cout << "Enter coordinates of the piece to protect (x y): ";
    std::cin >> protectX >> protectY;

    // Check if the target coordinates are within the board
    if (protectX < 0 || protectX >= BOARD_SIZE || protectY < 0 || protectY >= BOARD_SIZE) {
        std::cout << "Invalid coordinates. The piece must be within the board.\n";
        return;
    }

    // Check if the target piece is adjacent to the defender
    if (abs(protectX - x) <= 1 && abs(protectY - y) <= 1) {
        if (board[protectX][protectY] != nullptr) {
            board[protectX][protectY]->setShieldActive(true);
            std::cout << "Shield activated for piece at " << protectX << "," << protectY << "!\n";
            abilityUsed = true;
        } else {
            std::cout << "No piece at the specified coordinates.\n";
        }
    } else {
        std::cout << "Invalid coordinates. The piece must be adjacent to the defender.\n";
    }
}

// Ranged class implementation
Ranged::Ranged(PieceType type, int health, int x, int y) : Piece(type, health, x, y) {}

bool Ranged::isValidMove(int x2, int y2) const {
    int dx = abs(x2 - x);
    int dy = abs(y2 - y);
    return ((dx == 0 && dy <= 2) || (dy == 0 && dx <= 2)); // Move up to 2 squares vertically or horizontally
}

void Ranged::attack(Piece& target, int& gameOver, Piece* board[BOARD_SIZE][BOARD_SIZE]) {
    // Check if the target is on the same team
    if ((type >= WHITE_MASTER && type <= WHITE_RANGED && target.getType() >= WHITE_MASTER && target.getType() <= WHITE_RANGED) ||
        (type >= BLACK_MASTER && type <= BLACK_RANGED && target.getType() >= BLACK_MASTER && target.getType() <= BLACK_RANGED)) {
        std::cout << "Cannot attack your own team!\n";
        return;
    }

    if (target.getHealth() <= 0) {
        std::cout << "Target is already destroyed.\n";
        return;
    }

    int dx = abs(target.getX() - x);
    int dy = abs(target.getY() - y);
    if (!((dx == 0 && dy <= 3) || (dy == 0 && dx <= 3))) {
        std::cout << "Invalid attack. Ranged pieces can only attack up to 3 squares horizontally or vertically.\n";
        return;
    }

    int damage = 50;
    if (target.isShieldActive()) {
        damage /= 2;
        target.setShieldActive(false);
        std::cout << "Shield activated! Damage reduced by 50%.\n";
    }

    target.setHealth(target.getHealth() - damage);
    std::cout << "Attack executed. Target health: " << target.getHealth() << "\n";

    if (target.getHealth() <= 0) {
        std::cout << "Target destroyed!\n";
        if (target.getType() == WHITE_MASTER || target.getType() == BLACK_MASTER) {
            gameOver = (target.getType() == WHITE_MASTER) ? 2 : 1;
        }
        // Replace the target with an EMPTY piece (nullptr)
        delete &target; // Free the memory of the destroyed piece
        board[target.getX()][target.getY()] = nullptr; // Set the cell to nullptr
    }
}
void Ranged::useAbility(Piece* board[BOARD_SIZE][BOARD_SIZE]) {
    std::cout << "Ranged pieces have no special ability.\n";
}