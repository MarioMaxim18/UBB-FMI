#include <iostream>
#include "main3.h"
using namespace std;


int main() {
    Bishop bishop(1, 1, "white");
    Rook rook(1, 2, "white");
    Pawn pawn(2, 1, "white");
    Queen queen(3, 1, "white");
    King king(4, 1, "white");

    while (true) {
        cout << "1. Move Bishop\n2. Move Rook\n3. Move Pawn\n4. Move Queen\n5. Move King\n6. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 6) {
            break;
        }

        cout << "Enter new X and Y coordinates: ";
        unsigned int newX, newY;
        cin >> newX >> newY;

        bool result;
        switch (choice) {
            case 1:
                result = bishop.movePiece(newX, newY);
                break;
            case 2:
                result = rook.movePiece(newX, newY);
                break;
            case 3:
                result = pawn.movePiece(newX, newY);
                break;
            case 4:
                result = queen.movePiece(newX, newY);
                break;
            case 5:
                result = king.movePiece(newX, newY);
                break;
        }

        if (result) {
            cout << "Move successful.\n";
        } else {
            cout << "Invalid move.\n";
        }
    }

    return 0;
}