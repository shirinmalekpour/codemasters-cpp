#include "pieces.h"
#include <vector>

// Declare the board array
Piece* board[BOARD_SIZE][BOARD_SIZE];

void initializeBoard() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = nullptr;
        }
    }
}

void placePieces() {
    // Player 1 (White) pieces
    board[0][0] = new Master(WHITE_MASTER, 100, 0, 0);
    board[0][4] = new Attacker(WHITE_ATTACKER, 100, 0, 4);
    board[0][3] = new Defender(WHITE_DEFENDER, 100, 0, 3);
    board[0][7] = new Ranged(WHITE_RANGED, 100, 0, 7);

    // Player 2 (Black) pieces
    board[7][0] = new Master(BLACK_MASTER, 100, 7, 0);
    board[7][4] = new Attacker(BLACK_ATTACKER, 100, 7, 4);
    board[7][3] = new Defender(BLACK_DEFENDER, 100, 7, 3);
    board[7][7] = new Ranged(BLACK_RANGED, 100, 7, 7);
}

void displayBoard() {
    std::cout << "Current Board:\n";
    std::cout << "   ";
    for (int j = 0; j < BOARD_SIZE; j++) {
        std::cout << j << "  "; // Column numbers
    }
    std::cout << "\n";

    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i << " "; // Row numbers
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == nullptr) {
                std::cout << " . ";
            } else {
                switch (board[i][j]->getType()) {
                    case WHITE_MASTER: std::cout << "wM "; break;
                    case WHITE_ATTACKER: std::cout << "wA "; break;
                    case WHITE_DEFENDER: std::cout << "wD "; break;
                    case WHITE_RANGED: std::cout << "wR "; break;
                    case BLACK_MASTER: std::cout << "BM "; break;
                    case BLACK_ATTACKER: std::cout << "BA "; break;
                    case BLACK_DEFENDER: std::cout << "BD "; break;
                    case BLACK_RANGED: std::cout << "BR "; break;
                    default: std::cout << " . "; break;
                }
            }
        }
        std::cout << "\n";
    }
}

void movePiece(int x1, int y1, int x2, int y2) {
    if (board[x1][y1] != nullptr && board[x2][y2] == nullptr && board[x1][y1]->isValidMove(x2, y2)) {
        board[x2][y2] = board[x1][y1];
        board[x1][y1] = nullptr;
        board[x2][y2]->setPosition(x2, y2);
        std::cout << "Move confirmed.\n";
    } else {
        std::cout << "Invalid move. Please try again.\n";
    }
}

int main() {
    initializeBoard();
    placePieces();
    displayBoard();

    int turn = 0;
    int gameOver = 0;
    while (true) {
        int currentPlayer = (turn % 2) + 1;
        std::cout << "\nPlayer " << currentPlayer << "'s turn.\n";

        std::string action;
        std::cout << "Enter action (move/attack/ability): ";
        std::cin >> action;

        if (action == "move") {
            int x1, y1, x2, y2;
            std::cout << "Enter piece coordinates (x1 y1) and target coordinates (x2 y2): ";
            std::cin >> x1 >> y1 >> x2 >> y2;
            movePiece(x1, y1, x2, y2);
        } else if (action == "attack") {
            int x1, y1, x2, y2;
            std::cout << "Enter attacker coordinates (x1 y1) and target coordinates (x2 y2): ";
            std::cin >> x1 >> y1 >> x2 >> y2;
            if (board[x1][y1] != nullptr && board[x2][y2] != nullptr) {
                board[x1][y1]->attack(*board[x2][y2], gameOver, board); // Pass the board array
            } else {
                std::cout << "Invalid attack. No target at the specified coordinates.\n";
            }
        } else if (action == "ability") {
            int x, y;
            std::cout << "Enter defender coordinates (x y) to use ability: ";
            std::cin >> x >> y;
            if (board[x][y] != nullptr) {
                board[x][y]->useAbility(board); // Pass the board array
            } else {
                std::cout << "Invalid coordinates.\n";
            }
        } else {
            std::cout << "Invalid action.\n";
        }

        displayBoard();
        turn++;

        if (gameOver != 0) {
            std::cout << "Game over! Player " << gameOver << " wins!\n";
            break;
        }

        if (turn >= 30) {
            std::cout << "Draw! Maximum turns reached.\n";
            break;
        }
    }

    // Clean memory
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            delete board[i][j];
        }
    }

    return 0;
}