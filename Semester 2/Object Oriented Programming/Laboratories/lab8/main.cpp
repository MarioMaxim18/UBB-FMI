#include <iostream>

using namespace std;

class Array100 {
public:
    int& at(int pos) {
        if (pos < 0) {
            throw - 1;
        }
        if (pos >= 100) {
            throw - 2;
        }
        return data[pos];
    }
private:
    int data[100];
    unsigned int capacity;
};

int main() {
    Array100 myArray;
    try {
        int value = myArray.at(150);
    }
    catch (float e) {
        cout << "Float exception caught." << endl;
    }
    catch (double e) {
        cout << "Double exception caught." << endl;
    }
    catch (int e) {
        if (e == -1) {
            cout << "Error:Negative index provided." << endl;
        }
        else if (e == -2) {
            cout << "Error:Index out of bounds." << endl;
        }
    }
    return 0;
}
//
//class BaseException {
//public:
//    virtual const char* what() const{
//        return "BaseException";
//    }
//};
//
//class DerivedException : public BaseException {
//public:
//    const char* what() const{
//        return "DerivedException";
//    }
//};
//
//void oops() {
//    throw DerivedException();
//}
//
//int main() {
//    try {
//        oops();
//    } catch (BaseException& e) {
//        std::cout << e.what() << std::endl;
//    }
//    return 0;
//}
