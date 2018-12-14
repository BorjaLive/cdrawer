# cdrawer
Un pequeño header para dibujar BMPs en la consola.
# Descipción:
Permite mostrar pixel por pixel los colores (24bits) de un archivo bmp.<br />
Entre las opciones extra se incluyen pequeñas transiciones para dinamizar la aparicion de imagenes y la opción de rescalar xN veces cada pixel.
## Implementacion:
Necesitaras agregar el archivo libgdi32.a al linker e incluir cdrawer.h
## Imagenes en general:
Cualquier BMP de 24 bits puede ser mostrado con la siguiente función.
```
dibujar("sources/foto.bmp", 10, 15, RGB(255,0,255), 3, 500);
```
foto.bmp: el archivo a mostrar.<br />
10, 15: la posición en pixeles de la esquina superior izquierda en el eje x e y.<br />
RGB(255,0,255): el color de fondo. Los pixeles con este color no se mostraran, para dibujar imagenes con transparencia. Si no quieres eliminar el fondo, puedes pasar un 0.<br />
3: animación selecionada, no es necesario.<br />
500: velocidad de la animación. Cada franja se mostrará en 1000/500 milisegundos. No es necesaria, la velocidad por defecto es 1000/200 milisegundos.
### Tabla de animaciones y opciones de dibujado:
0: sin animaciones, por defecto.<br />
1: Barrido de arriba a abajo.<br />
2: Barrido de abajo a arriba.<br />
3: Barrido de izquierda a derecha.<br />
4: Barrido de derecha a izquierda.<br />
5: Barrido de izquierda a derecha y arriba a abajo.<br />
6: Rescala a x2.<br />
4+n: Rescala a n veces. A partir de n = 2.
## Numeros:
Simplifica la tarea de mostrar por pantalla números enteros positivos.
```
dibujarN(972, 10, 15, 6, 700);
```

972: el numero a mosrar.<br />
10, 15: la posición en pixeles de la esquina superior izquierda en el eje x e y. No es necesario<br />
6: animación selecionada, no es necesario.<br />
700: velocidad de la animación. Cada franja se mostrará en 1000/700 milisegundos. No es necesaria, la velocidad por defecto es 1000/500 milisegundos.
