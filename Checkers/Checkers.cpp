#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

enum Piece { EMPTY, NORMAL, PROMOTED };
enum Color { BLACK, WHITE, NONE };

struct Square {
    Piece piece;
    Color color;
};

void initBoard(vector<vector<Square>>& board) {
    board.resize(8, vector<Square>(8, { EMPTY, NONE }));

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 1) {
                if (i < 3) {
                    board[i][j] = { NORMAL, BLACK }; // Black pieces on top 3 rows
                }
                else if (i > 4) {
                    board[i][j] = { NORMAL, WHITE }; // White pieces on bottom 3 rows
                }
            }
        }
    }
}

void printBoard(const vector<vector<Square>>& board) {
    cout << "  a b c d e f g h\n";
    int size = 8;
    for (int i = 0; i < size; i++) {
        cout << 8 - i << " ";
        for (int j = 0; j < size; j++) {
            const Square& square = board[i][j];
            if (square.piece == EMPTY) {
                cout << ". "; // Empty square
            }
            else {
                char pieceChar = ' ';
                if (square.color == BLACK) {
                    pieceChar = (square.piece == NORMAL) ? 'o' : 'O';
                }
                else {
                    pieceChar = (square.piece == NORMAL) ? 'x' : 'X';
                }
                cout << pieceChar << " ";
            }
        }
        cout << 8 - i << endl;
    }
    cout << "  a b c d e f g h\n";
}

bool isValidMove(const vector<vector<Square>>& board, int startX, int startY, int endX, int endY) {
    // Check if coordinates are within bounds
    if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 ||
        endX < 0 || endX >= 8 || endY < 0 || endY >= 8) {
        return false;
    }

    const Square& startSquare = board[startX][startY];
    const Square& endSquare = board[endX][endY];

    // The starting square must contain a piece
    if (startSquare.piece == EMPTY) {
        return false;
    }

    // Determine the direction of movement
    int direction = (startSquare.color == WHITE) ? -1 : 1;

    // Basic forward movement (non-capturing)
    if (abs(startY - endY) == 1 && endX == startX + direction && endSquare.piece == EMPTY) {
        return true;
    }

    // Additional logic could be added here for other types of valid moves, like capturing

    return false; // If none of the conditions are met, the move is invalid
}

bool parseMove(const string& move, int& startX, int& startY, int& endX, int& endY) {
    if (move.size() != 5 || move[2] != '-') {
        return false;
    }

    char startCol = tolower(move[0]);
    char startRow = move[1];
    char endCol = tolower(move[3]);
    char endRow = move[4];

    if (startCol < 'a' || startCol > 'h' || endCol < 'a' || endCol > 'h' ||
        startRow < '1' || startRow > '8' || endRow < '1' || endRow > '8') {
        return false;
    }

    startX = 8 - (startRow - '0');
    startY = startCol - 'a';
    endX = 8 - (endRow - '0');
    endY = endCol - 'a';

    return true;
}

int main() {
    vector<vector<Square>> board;
    initBoard(board);

    while (true) {
        printBoard(board);

        string move;
        cout << "Enter your move (e.g., a3-b4): ";
        getline(cin, move);

        int startX, startY, endX, endY;
        if (!parseMove(move, startX, startY, endX, endY)) {
            cout << "Invalid move format! Try again.\n";
            continue;
        }

        if (!isValidMove(board, startX, startY, endX, endY)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        // Execute the move (logic to be implemented)
        // For now, we'll just output the parsed coordinates
        cout << "Piece: " << (board[5][0].piece == EMPTY ? "EMPTY" : (board[5][0].piece == NORMAL ? "NORMAL" : "PROMOTED"))
            << ", Color: " << (board[5][0].color == NONE ? "NONE" : (board[5][0].color == BLACK ? "BLACK" : "WHITE"))
            << endl;
        board[endX][endY] = board[startX][startY];
        board[startX][startY] = { EMPTY, NONE };
        cout << "Move from (" << startX << ", " << startY << ") to (" << endX << ", " << endY << ")\n";
      
    }

    return 0;
}
