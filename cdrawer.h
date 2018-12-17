#ifndef CCOUNTINCG_H_INCLUDED
#define CCOUNTINCG_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <mmsystem.h>

#define FrameSkipping false


int _colorDiff(COLORREF color1, COLORREF color2);
int _aprox(float n);
void _getNombreArchivo(char * nombre, int n, char archivo[50]);
void _int2charArray(int n, char *cadena);
void _strinv(char * cadena);

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

    switch(anim){ //Distintos tipos de dibujado
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

void dibujarAnim(char* nombre,int x,int y,COLORREF bg, int n,int scale = 1, int wait = 50, int repeat = 5){
    char archivo[50];
    int width = 0, height = 0;

    _getNombreArchivo(nombre, 0, archivo);
    readBMPsize(archivo, width, height);
    if(width == 0 || height == 0) return;

    COLORREF data[width*height];
    COLORREF imagen[n][height][width];

    for(int l = 0; l < n; l++){
        _getNombreArchivo(nombre, l, archivo);

        ReadBMP(archivo, data);
        int j = height-1, k = 0;
        for(int i = 0; i < height*width; i++){
            imagen[l][j][k] = bg==data[i]?0:data[i];
            if(k == width-1){
                k = 0;
                j--;
            }else{
                k++;
            }
        }
    }


    HWND myconsole = GetConsoleWindow();
    HDC mydc = GetDC(myconsole);

    for(int m = 0; m < repeat; m++){
        for(int l = 0; l < n; l ++){
            for(int i = 0; i < height*scale; i++)
                for(int j = 0; j < width*scale; j++)
                    if(l == 0 || imagen[l-1][i/scale][j/scale] != imagen[l][i/scale][j/scale])
                        SetPixel(mydc,j+x,i+y,imagen[l][i/scale][j/scale]);
            Sleep(wait);
        }
    }

    ReleaseDC(myconsole, mydc);
}


void dibujarN(int n, int x = 0, int y = 0, int anim = 0, int speed = 500){
    char src[20] = "sources/cats/X.bmp";
    char numero[10];
    _int2charArray(n, numero);

    int i = 0;
    while(i < sizeof(numero)/sizeof(char) && numero[i] != '\0'){
        src[13] = numero[i];
        dibujar(src, x+(i*70), y, RGB(255,0,255), anim, speed);
        i++;
    }
}

void dibujarNanim(int n, int x = 0, int y = 0, int scale = 1, int wait = 150, int repeat = 5){
    int tamanos[10] = {10,9,9,12,10,8,9,9,6,8};
    COLORREF bg = RGB(255,0,255);
    char numero[10];
    _int2charArray(n, numero);
    int cifras = strlen(numero);

    int cifra[cifras];
    int k = 0;
    int i = -1;
    int nO = n;
    do{
        n /= 10;
        i++;
    }while(n > 0);
    n = nO;
    do{
        cifra[k] = (n%10);
        k++;
        n /= 10;
        i--;
    }while(n > 0);
    int tmp;
    for(int i = 0; i < cifras/2; i++){
        tmp = cifra[i];
        cifra[i] = cifra[cifras-i-1];
        cifra[cifras-i-1] = tmp;
    }


    int width, height;
    readBMPsize("sources/catsGif/0_0.bmp", width, height);
    if(width == 0 || height == 0) return;

    COLORREF data[width*height];
    COLORREF imagenes[cifras][12][height][width];
    char nombre[50] = "sources/catsGif/0_X.bmp";
    char archivo[50];

    for(int m = 0; m < cifras; m++){ //Recorrer cifras
        nombre[16] = cifra[m]+48;
        for(int l = 0; l < tamanos[cifra[m]]; l++){ //Recorrer animaciones
            _getNombreArchivo(nombre, l, archivo);

            ReadBMP(archivo, data);
            int j = height-1, k = 0;
            for(int i = 0; i < height*width; i++){
                imagenes[m][l][j][k] = bg==data[i]?0:data[i];
                if(k == width-1){
                    k = 0;
                    j--;
                }else{
                    k++;
                }
            }
        }
    }

    HWND myconsole = GetConsoleWindow();
    HDC mydc = GetDC(myconsole);

    int contador[cifras][2];
    for(int i = 0; i < cifras; i++){
        contador[i][0] = 0;
        contador[i][1] = -1; //Contador [i][1] tiene un desafase con [i][0]
    }
    for(int m = 0; m < repeat*12; m++){
        for(int p = 0; p < cifras; p++){
            for(int i = 0; i < height*scale; i++)
                for(int j = 0; j < width*scale; j++)
                    if(contador[p][1] == -1 || imagenes[p][contador[p][1]][i/scale][j/scale] != imagenes[p][contador[p][0]][i/scale][j/scale])
                        SetPixel(mydc,j+x+(50*p*scale),i+y,imagenes[p][contador[p][0]][i/scale][j/scale]);
        }
        Sleep(wait);
        for(int i = 0; i < cifras; i++){
            contador[i][1] = contador[i][0];
            if(tamanos[cifra[i]]-1 > contador[i][0])
                contador[i][0]++;
            else
                contador[i][0] = 0;
        }
    }

    ReleaseDC(myconsole, mydc);
}

void dibujarVideo(char* hubicacion, int fpsO, int fps, int frames, int tolerancia, int x, int y){
    int targetTime = 1000/fps; //tiempo que debe durar cada cuadro (ms)
    int nFotograms = ((float)frames/fpsO)*fps;
    COLORREF bg = RGB(255,0,255); //Color morado, fondo transparente por defecto

    char archivo[50];
    strcpy(archivo,hubicacion); //se usa temporalmente para guardar el nombre de un archivo concreto
    strcat(archivo,"0.bmp");

    int width, height;
    readBMPsize(archivo,width,height);

    strcpy(archivo,hubicacion);
    strcat(archivo,"audio.wav");
    HWND myconsole = GetConsoleWindow();
    HDC mydc = GetDC(myconsole);
    PlaySoundA((LPCSTR) archivo, NULL, SND_FILENAME | SND_ASYNC);
    clock_t Start;
    int Total;

    char numeros[10];
    int l = 0, j, k;
    int saltados = 0;

    COLORREF dataNEW[width*height];
    COLORREF dataOLD[width*height];
    while(l < nFotograms && frames >= l*((float)fpsO/fps)){
        Start = clock();

        strcpy(archivo,hubicacion);
        _int2charArray(l*((float)fpsO/fps),numeros);
        strcat(archivo,numeros);
        strcat(archivo,".bmp");
        //printf("%.0f, ",(l+m)*((float)24/10));
        ReadBMP(archivo, dataNEW);

        j = height-1; k = 0;
        for(int i = 0; i < height*width; i++){
            if(l == 0 || _colorDiff(dataNEW[i], dataOLD[i]) > tolerancia)
                SetPixel(mydc,k+x,j+y,dataNEW[i]);
            if(k == width-1){
                k = 0;
                j--;
            }else{
                k++;
            }
            dataOLD[i] = dataNEW[i];
        }

        Total = clock() - Start;
        if(Total >= targetTime){
            //printf("%d",_aprox((float)Total/targetTime)); //Mostrar cuantos frames se saltan
            l += _aprox((float)Total/targetTime);
            saltados += _aprox((float)Total/targetTime)-1;
        }else{
            Sleep(targetTime-Total);
            l++;
        }
    }
    printf("SALTADOS: %d",saltados);
    /*while(l < nFotograms){
        m = 0;
        Start = clock();
        while(m < MaxBuffer && frames >= (l+m)*((float)24/10)){
            strcpy(archivo,hubicacion);
            _int2charArray((l+m)*((float)24/10),numeros);
            strcat(archivo,numeros);
            strcat(archivo,".bmp");
            //printf("%.0f, ",(l+m)*((float)24/10));

            ReadBMP(archivo, data);
            cuadros[m] = data;
            //system("CLS");

            j = height-1; k = 0;
            for(int i = 0; i < height*width; i++){
                if(m == 0 || cuadros[m-1][i] != cuadros[m][i])
                    SetPixel(mydc,k+x,j+y,cuadros[m][i]);
                if(k == width-1){
                    k = 0;
                    j--;
                }else{
                    k++;
                }
            }

            m++;
        }
        desfaseLectura = clock() - Start;
        //printf("%d\n",desfaseLectura);
        m = 0;

        for(int m = 0; m < MaxBuffer; m++){

            printf("%d, ",m);
        }
        l += MaxBuffer;

        while(m < MaxBuffer){
            Start = clock();
            //printf("%d\n",m);
            j = height-1; k = 0;
            for(int i = 0; i < height*width; i++){
                if(m == 0 || cuadros[m-1][i] != cuadros[m][i])
                    SetPixel(mydc,k+x,j+y,cuadros[m][i]);
                if(k == width-1){
                    k = 0;
                    j--;
                }else{
                    k++;
                }
            }

            Total = (clock() - Start) + (desfaseLectura/5);

            if(FrameSkipping){
               if(Total >= targetTime){
                    m += (Total/targetTime);
                }else{
                    //Sleep(targetTime-Total-5);
                    m++;
                }
            }else{
                m++;
                if(Total < targetTime)
                    Sleep(targetTime-Total-5);
            }
        }
        l += m;
    }*/


    ReleaseDC(myconsole, mydc);
}


int _colorDiff(COLORREF color1, COLORREF color2){
    return abs(GetRValue(color1)-GetRValue(color2))+abs(GetGValue(color1)-GetGValue(color2))+abs(GetBValue(color1)-GetBValue(color2));
}
int _aprox(float n){
    int redondeado = 0;
    while(n >= 0.5){
        redondeado++;
        n--;
    }
    return redondeado;
}
void _getNombreArchivo(char * nombre, int n, char archivo[50]){
    char numeros[10];
    _int2charArray(n, numeros);

    int k = 0, i = 0, j = 0;
    while(k < 50 && nombre[i] != '\0'){
        if(nombre[i] == 'X'){
            while(numeros[j] != '\0'){
                archivo[k] = numeros[j];
                j++;
                k++;
            }
        }else{
            archivo[k] = nombre[i];
            k++;
        }
        i++;
    }
    archivo[k] = '\0';

}
void _int2charArray(int n, char *cadena){
    int k = 0;
    int i = -1;
    int nO = n;
    do{
        n /= 10;
        i++;
    }while(n > 0);
    n = nO;
    do{
        cadena[k] = (n%10)+48;
        k++;
        n /= 10;
        i--;
    }while(n > 0);
    cadena[k] = '\0';

    _strinv(cadena);
    //printf("%d  %s  \n",nO,cadena);
}

void _strinv(char * cadena){
    int tama = 0;
    int i = 0;
    while(i < sizeof(cadena)/sizeof(char) && cadena[i] != '\0'){
        tama++;
        i++;
    }

    char tmp;
    int pos = 0;
    for(int i = tama-1; i >= tama/2; i--){
        tmp = cadena[i];
        cadena[i] = cadena[pos];
        cadena[pos] = tmp;
        pos++;
    }
}
#endif // CCOUNTINCG_H_INCLUDED
