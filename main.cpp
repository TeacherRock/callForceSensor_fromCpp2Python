#include "ForceSensor.hpp"
#include <iostream>

int main() {
    unsigned short* data_main;

    printf("Press 'Esc' to end program.\n");
    printf("Press any key to start !\n");

    while (_kbhit() == 0);

    int sw = 0;
    addThread_ForceSensor(4);
    while (sw != 0x1b) {
        data_main = getForceData();
    }
    system("pause");
}