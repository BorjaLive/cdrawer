#ifndef CCOUNTINCG_H_INCLUDED
#define CCOUNTINCG_H_INCLUDED

#include <stdio.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>

void readBMPsize(char* filename, int &width, int &height){
    FILE* f = fopen(filename, "rb");
    if(!f) return;

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);

    width = *(int*)&info[18];
    height = *(int*)&info[22];

    fclose(f);
}

void ReadBMP(char* filename, COLORREF *imagen){

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
            imagen[(i*width)+(j/3)] = RGB(data[j],data[j+1],data[j+2]);
        }
    }
    fclose(f);
}

void dibujar(char* nombre,int x,int y,COLORREF bg,int anim = 0, int speed = 100){
    int width = 0, height = 0;

    readBMPsize(nombre, width, height);
    if(width == 0 || height == 0) return;

    COLORREF data[width*height];
    COLORREF imagen[height][width];
    ReadBMP(nombre, data);

    int j = height-1, k = 0;
    for(int i = 0; i < height*width; i++){
        imagen[j][k] = data[i];
        if(k == width-1){
            k = 0;
            j--;
        }else{
            k++;
        }
    }


    HWND myconsole = GetConsoleWindow();
    HDC mydc = GetDC(myconsole);

    switch(anim){
    case 0:
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                if(bg == 0 || bg != imagen[i][j])
                    SetPixel(mydc,j+x,i+y,imagen[i][j]);
        break;
    case 1:
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++)
                if(bg == 0 || bg != imagen[i][j])
                    SetPixel(mydc,j+x,i+y,imagen[i][j]);
            Sleep(1000/speed);
        }
        break;
    case 2:
        for(int i = height-1; i >= 0 ; i--){
            for(int j = 0; j < width; j++)
                if(bg == 0 || bg != imagen[i][j])
                    SetPixel(mydc,j+x,i+y,imagen[i][j]);
            Sleep(1000/speed);
        }
        break;
    case 3:
        for(int j = 0; j < width; j++){
            for(int i = 0; i < height; i++)
                if(bg == 0 || bg != imagen[i][j])
                    SetPixel(mydc,j+x,i+y,imagen[i][j]);
            Sleep(1000/speed);
        }
        break;
    case 4:
        for(int j = width-1; j >= 0; j--){
            for(int i = 0; i < height; i++)
                if(bg == 0 || bg != imagen[i][j])
                    SetPixel(mydc,j+x,i+y,imagen[i][j]);
            Sleep(1000/speed);
        }
        break;
    case 5:
        for(int i = 0; i < height; i++)
            for(int j = 0; j < width; j++)
                if(bg == 0 || bg != imagen[i][j]){
                    SetPixel(mydc,j+x,i+y,imagen[i][j]);
                    Sleep(1000/speed);
                }
        break;
    default:
        int res = anim-4;
        for(int i = 0; i < height*res; i++)
            for(int j = 0; j < width*res; j++)
                if(bg == 0 || bg != imagen[i/res][j/res])
                    SetPixel(mydc,j+x,i+y,imagen[i/res][j/res]);
        break;
    }


    ReleaseDC(myconsole, mydc);
}

int dibujarN(int n, int x = 0, int y = 0, int anim = 0, int speed = 500){
    int nO = n;
    int i = -1;
    char src[20] = "sources/X.bmp";
    do{
        n /= 10;
        i++;
    }while(n > 0);
    n = nO;
    do{
        src[8] = (n%10)+48;
        dibujar(src, x+(i*(anim>5?70*(anim-4):70)), y, RGB(255,0,255), anim, speed);
        n /= 10;
        i--;
    }while(n > 0);
}


#endif // CCOUNTINCG_H_INCLUDED
