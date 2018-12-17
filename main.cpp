#include <iostream>
#include "cdrawer.h"


int main(){
    dibujar("sources/foto.bmp", 5, 5, RGB(255,0,255), 3, 500);
    dibujarN(1024,10,30,1);
    dibujarAnim("sources/catsGif/7_X.bmp", 350, 30, RGB(255,0,255), 9, 2, 125, 4);
    dibujarNanim(1546, 10, 50, 2, 150, 5);
    dibujarVideo("sources/Nyan/Nyan_",24,24,168,25,100,30);
    //dibujarVideo("sources/DerpSheIs/DerpSheIs_",24,12,960,25,100,30);
    //dibujarVideo("sources/AMV/AMV_",29,12,5730,25,100,30);


    std::cin.ignore();
    return 0;
}
