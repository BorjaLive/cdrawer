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
#Animaciones
cdrawer solo admite imagenes en formato BMP de 24 bits, pero incluye dos funciones para tratar una serie de archivos con nombres estandarizados como si fueran fotogramas.
##Animaciones en general:
Todos los fotogramas deberán estar en la misma carpeta y tener el mismo nombre; excepto la numeración. Para numerarlos se comenzará desde el 0 y solo se escribirá el número en decimal. (Ej: "anim_5.bmp" Correcto, "anim_05.bmp" Mal)
```
dibujarAnim("sources/catsGif/7_X.bmp", 50, 30, RGB(255,0,255), 9, 2, 50, 5);
```
"sources/catsGif/7_X.bmp": el nombre del archivo estandar. Nótese que la 'X' será remplazada por el número de fotograma.<br />
50: Posicion en la x de la esquina superior izquierda.<br />
30: Posicion en la y de la esquina superior izquierda.<br />
RGB(255,0,255): Color de fondo a eliminar. NOTA: Al tratarse de una animación, el fondo debe dibujarse siempre, por ello se remplazará por negro.<br />
9: Numero de fotogramas que tiene la animacion.<br />
2: Escala a la que se dibujará la animación.<br />
50: Tiempo en milisegundos a esperar entre fotogramas.<br />
5: Dado que el dibujo es secuencial y no asincrono, la función no terminara de ejecutarse hasta que el bucle se repita; en este caso, 5 veces.<br />
## Numeros con animaciones:
Regresan los gatetes con carteles, esta vez animados.
```
dibujarNanim(1586, 10, 50, 2, 50, 5);
```
1586: Número a mostrar.<br />
10: Posicion en la x de la esquina superior izquierda.<br />
50: Posicion en la y de la esquina superior izquierda.<br />
2: escala de las imagenes.<br />
50: Tiempo en milisegundos a esperar entre fotogramas.<br />
5: Numero de veces que se repitirá la animacion.<br />
