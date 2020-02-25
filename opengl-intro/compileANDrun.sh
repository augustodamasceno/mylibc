#!/bin/bash

echo ---OpenGL Intro-------------------
echo ---Remove Previous Compilation----
openglintro=$(pwd)/openglintro
if [ -e "$openglintro" ]
then
	echo Exist a previous compilation. Deleting...
	rm openglintro
fi
echo Compiling
gcc -Wall -pedantic opengl-intro.c draw.c control.c -o openglintro -lm -lGL -lGLU -lglut
echo Run
./openglintro
echo ---END----------------------------

