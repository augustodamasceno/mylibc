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

#include "control.h"

GLfloat getTranslationX(void)
{
	return translationX;
}

GLfloat getTranslationY(void)
{
	return translationY;
}

GLfloat getTranslationZ(void)
{
	return translationZ;
}

GLfloat getRotationX(void)
{
	return rotationX;
}

GLfloat getRotationY(void)
{
	return rotationY;
}

void resetMoves(void)
{
	translationX = TRANSLATION_X_DEFAULT;
	translationY = TRANSLATION_Y_DEFAULT;
	translationZ = TRANSLATION_Z_DEFAULT;
	rotationX = ROTATION_X_DEFAULT;
	rotationY = ROTATION_Y_DEFAULT;
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				printf("Mouse Left.\n");
			}
			break;
		case GLUT_MIDDLE_BUTTON:
			if (state == GLUT_DOWN)
			{
				printf("Mouse Middle.\n");
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN)
			{
				printf("Mouse Right.\n");
			}
			break;
		default:
			break;
	}
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:   /* ESC */
			printf("Button ESC pressed: exit.\n");
			exit(0);
			break;
		case 82: /* Go to next case */
		case 114: /* 'R' and 'r': Reset Positions */
			printf("Button R pressed: reset positions.\n");
			translationX = TRANSLATION_X_DEFAULT;
			translationY = TRANSLATION_Y_DEFAULT;
			translationZ = TRANSLATION_Z_DEFAULT;
			rotationX = ROTATION_X_DEFAULT;
			rotationY = ROTATION_Y_DEFAULT;
			glutPostRedisplay();
			break;
		case 'z':
		case 'Z':
			translationZ -= translationStep; 
			printMove();
			glutPostRedisplay();
			break;
		case 'x':
		case 'X':
			translationZ = TRANSLATION_Z_DEFAULT;
			printMove();
			glutPostRedisplay();
			break;
		case 'c':
		case 'C':
			translationZ += translationStep*2;
			printMove();
			glutPostRedisplay();
			break;
		case 'a':
		case 'A':
			translationY -= translationStep; 
			printMove();
			glutPostRedisplay();
			break;
		case 's':
		case 'S':
			translationY = TRANSLATION_Y_DEFAULT;
			printMove();
			glutPostRedisplay();
			break;
		case 'd':
		case 'D':
			translationY += translationStep*2;
			printMove();
			glutPostRedisplay();
			break;
		case 'q':
		case 'Q':
			translationX = translationStep; 
			printMove();
			glutPostRedisplay();
			break;
		case 'w':
		case 'W':
			translationX = TRANSLATION_X_DEFAULT;
			printMove();
			glutPostRedisplay();
			break;
		case 'e':
		case 'E':
			translationX += translationStep*2;
			printMove();
			glutPostRedisplay();
			break;
		case 'm':
		case 'M':
			printf("Menu\n\n");
			printf("Translation\n");
			printf("z: z--\n");
			printf("x: z default\n");
			printf("c: z++\n");
			printf("a: y--\n");
			printf("s: y default\n");
			printf("d: y++\n");
			printf("q: x--\n");
			printf("w: x default\n");
			printf("e: x++\n\n");
			printf("Rotation\n");
			printf("Up/Down: Y\n");
			printf("Left/Right: X\n\n");
			printf("r/R: Reset Translation and Rotation\n");
			printf("Variables to Default\n");
			printf("r/M: Display this Menu");
			printf("ESC: Exit");
		default:
			break;
	}
}

void keyboardSpecials (int key, int x, int y)
{
	int move;
	switch (key)
	{
		case GLUT_KEY_RIGHT:
			move = rotationX;
			move = (move + rotationAngle) % 360;
			rotationX = (GLfloat) move;
			printMove();
			glutPostRedisplay();
			break;
		case GLUT_KEY_LEFT:
			move = rotationX;
			move = (move + (360-rotationAngle)) % 360;
			rotationX = (GLfloat) move;
			printMove();
			glutPostRedisplay();
			break;
		case GLUT_KEY_UP:
			move = rotationY;
			move = (move + rotationAngle) % 360;
			rotationY = (GLfloat) move;
			printMove();
			glutPostRedisplay();
			break;
		case GLUT_KEY_DOWN:
			move = rotationY;
			move = (move + (360-rotationAngle)) % 360;
			rotationY = (GLfloat) move;
			printMove();
			glutPostRedisplay();
			break; 
		default:
			break;
	}
}

void printMove(void)
{
	printf("Translation:\nX: %.2f\nY: %.2f\nZ: %.2f\n",\
	translationX,translationY,translationZ);
	printf("Rotation:\nX: %.2f\nY: %.2f\n\n",\ 
	rotationX,rotationY);
}

