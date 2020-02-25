/**
 *  Brief introduction to OpenGL - Educational
 *  Copyright (C) 2016, Augusto Damasceno
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CONTROL_H
#define _CONTROL_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define TRANSLATION_X_DEFAULT 0
#define TRANSLATION_Y_DEFAULT 0
#define TRANSLATION_Z_DEFAULT -5.0
#define ROTATION_X_DEFAULT 0
#define ROTATION_Y_DEFAULT 0

/* Control Variables */
static GLfloat translationX = 0.0;
static GLfloat translationY = 0.0;
static GLfloat translationZ = TRANSLATION_Z_DEFAULT;
static GLfloat translationStep = 0.25;
static GLfloat rotationX = 0.0;
static GLfloat rotationY = 0.0;
static int rotationAngle = 5;

/* Get Variables */
GLfloat getTranslationX(void);
GLfloat getTranslationY(void);
GLfloat getTranslationZ(void);
GLfloat getRotationX(void);
GLfloat getRotationY(void);

/* Set Moves */
void setTranslations(GLfloat * translations);
void setRotations(GLfloat * rotations);
void resetMoves(void);

/* Functions for OpenGL mouse and keyboard callbacks */
void mouse(int button, int state, int x, int y);
void keyboardSpecials (int key, int x, int y);
void keyboard (unsigned char key, int x, int y);

/* Print translations */
void printMove(void);

#endif /* _CONTROL_H  */

