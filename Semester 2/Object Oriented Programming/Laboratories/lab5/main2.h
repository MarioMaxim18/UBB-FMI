#include <string>
#include <iostream>

using namespace std;

class Animal {
protected:
    string commonName;
    string scientificName;
public:
    Animal(string common, string scientific) {
        this->commonName = common;
        this->scientificName = scientific;
    }
    void displayInfo() {
        cout << "Common Name: " << commonName << endl;
        cout << "Scientific Name: " << scientificName << endl;
    }
};

class Mammal : public Animal {
private:
    bool isAquatic;
    unsigned char gestationPeriod;
public:
    Mammal(string common, string scientific, bool aquatic, unsigned char gestation) : Animal(common, scientific) {
        this->isAquatic = aquatic;
        this->gestationPeriod = gestation;
    }
    void displayInfo() {
        Animal::displayInfo();
        cout << "Is Aquatic: " << (isAquatic ? "Yes" : "No") << endl;
        cout << "Gestation Period: " << static_cast<int>(gestationPeriod) << endl;
    }
};

class Bird : public Animal {
private:
    unsigned int wingSpan;
public:
    Bird(string common, string scientific, unsigned int wingSpan) : Animal(common, scientific) {
        this->wingSpan = wingSpan;
    }

    void displayInfo() {
        Animal::displayInfo();
        cout << "Wing Span: " << wingSpan << endl;
    }
};

class Reptile : public Animal {
private:
    bool isVenomous;
public:
    Reptile(string common, string scientific, bool venomous) : Animal(common, scientific) {
        this->isVenomous = venomous;
    }

    void displayInfo() {
        Animal::displayInfo();
        cout << "Is Venomous: " << (isVenomous ? "Yes" : "No") << endl;
    }
};