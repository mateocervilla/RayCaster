#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "RayCaster.hpp"

int main() {
    RayCaster rayCaster;

    while (rayCaster.running())
    {
        rayCaster.update();


        rayCaster.render();
    }

    return 0;
}