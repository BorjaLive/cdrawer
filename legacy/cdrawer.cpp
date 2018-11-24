#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <C:\Users\Margaret\Desktop\ccountincg.h>

struct pixel{
    unsigned char R, G, B;
};

void readBMPsize(char* filename, int &width, int &height){
    FILE* f = fopen(filename, "rb");

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);

    width = *(int*)&info[18];
    height = *(int*)&info[22];

    fclose(f);
}

void ReadBMP(char* filename, pixel *imagen){

    int i;
    FILE* f = fopen(filename, "rb");

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);

    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    for(int i = 0; i < height; i++){
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width*3; j += 3){
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;
            imagen[(i*width)+(j/3)].R = data[j];
            imagen[(i*width)+(j/3)].G = data[j+1];
            imagen[(i*width)+(j/3)].B = data[j+2];
        }
    }
    fclose(f);
}

void dibujar(char* nombre,int x,int y,COLORREF bg){
    int width, height;
    readBMPsize(nombre, width, height);
    pixel data[width*height];
    pixel imagen[height][width];
    ReadBMP(nombre, data);

    int j = height-1, k = 0;
    for(int i = 0; i < height*width; i++){
        imagen[j][k].R = data[i].R;
        imagen[j][k].G = data[i].G;
        imagen[j][k].B = data[i].B;
        if(k == width-1){
            k = 0;
            j--;
        }else{
            k++;
        }
    }


    HWND myconsole = GetConsoleWindow();
    HDC mydc = GetDC(myconsole);

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            COLORREF color = RGB((int)imagen[i][j].R,(int)imagen[i][j].G,(int)imagen[i][j].B);
            if(bg != color)
                SetPixel(mydc,j+x,i+y,color);

        }
        Sleep(15);
    }

    ReleaseDC(myconsole, mydc);
}

int main(){
    //dibujar("sources/0.bmp", 10, 10, RGB(255,0,255));
    dibujar("sources/1.bmp", 30, 30, RGB(255,0,255));

    std::cin.ignore();
    return 0;
}
