#include <iostream>
#include "cdrawer.h"


int main(){
    //dibujar("sources/foto.bmp", 5, 5, RGB(255,0,255), 3, 500);
    //dibujarN(1024,10,30,1);
    dibujarAnim("sources/catsGif/7_X.bmp", 50, 30, RGB(255,0,255), 9, 2, 150, 20);

    std::cin.ignore();
    return 0;
}
