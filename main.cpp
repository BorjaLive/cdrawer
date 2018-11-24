#include <iostream>
#include "cdrawer.h"


int main(){
    dibujar("sources/foto.bmp", 5, 5, RGB(255,0,255), 3, 500);
    dibujarN(1024,10,30,1);

    std::cin.ignore();
    return 0;
}
