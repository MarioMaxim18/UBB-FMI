#include <iostream>
#include "main2.h"

int main() {
    Mammal mammal("Dog", "Canis lupus", false, 63);
    Bird bird("Eagle", "Aquila", 220);
    Reptile reptile("Rattlesnake", "Crotalus", true);

    mammal.displayInfo();
    bird.displayInfo();
    reptile.displayInfo();

    return 0;
}