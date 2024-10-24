#include <string>
#include <iostream>
using namespace std;

class ChessPiece {
protected:
    unsigned int positionX;
    unsigned int positionY;
    string name;
private:
    string color;
public:
    ChessPiece(unsigned int x, unsigned int y, string n, string c) : positionX(x), positionY(y), name(n), color(c) {}

    bool movePiece(unsigned int newX, unsigned int newY) {
        return false;
    }
};

class Bishop : public ChessPiece {
public:
    Bishop(unsigned int x, unsigned int y, string c) : ChessPiece(x, y, "Bishop", c) {}

    bool movePiece(unsigned int newX, unsigned int newY) {
        if (abs(static_cast<int>(newX - positionX)) == abs(static_cast<int>(newY - positionY))) {
            positionX = newX;
            positionY = newY;
            return true;
        }
        return false;
    }
};

class Rook : public ChessPiece {
public:
    Rook(unsigned int x, unsigned int y, string c) : ChessPiece(x, y, "Rook", c) {}

    bool movePiece(unsigned int newX, unsigned int newY) {
        if (newX == positionX || newY == positionY) {
            positionX = newX;
            positionY = newY;
            return true;
        }
        return false;
    }
};

class Pawn : public ChessPiece {
public:
    Pawn(unsigned int x, unsigned int y, string c) : ChessPiece(x, y, "Pawn", c) {}

    bool movePiece(unsigned int newX, unsigned int newY) {
        if (newX == positionX && newY == positionY + 1) {
            positionX = newX;
            positionY = newY;
            return true;
        }
        return false;
    }
};

class Queen : public ChessPiece {
public:
    Queen(unsigned int x, unsigned int y, string c) : ChessPiece(x, y, "Queen", c) {}

    bool movePiece(unsigned int newX, unsigned int newY) {
        if (newX == positionX || newY == positionY || abs(static_cast<int>(newX - positionX)) == abs(static_cast<int>(newY - positionY))) {
            positionX = newX;
            positionY = newY;
            return true;
        }
        return false;
    }
};

class King : public ChessPiece {
public:
    King(unsigned int x, unsigned int y, string c) : ChessPiece(x, y, "King", c) {}

    bool movePiece(unsigned int newX, unsigned int newY) {
        if (abs(static_cast<int>(newX - positionX)) <= 1 && abs(static_cast<int>(newY - positionY)) <= 1) {
            positionX = newX;
            positionY = newY;
            return true;
        }
        return false;
    }
};