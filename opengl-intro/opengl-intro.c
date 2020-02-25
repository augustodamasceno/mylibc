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

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

/* Lib Draw - Cube and Teapot with Transformations */
#include "draw.h"

/* Lib Control - Mouse and Keyboard */
#include "control.h"

/* Global Variables */
static GLfloat light0_position[] = { 0.0, 0.00, 1.5, 1.0 }; 

/* Rotation Vector */
static GLfloat rot[] = { 0.0, 0.0, 0.0};

/* Inital Routine*/
void init()
{
	/* Color when Clear Window*/
	glClearColor (1.0,1.0,1.0,0.0);

	/* Light Properties */
	GLfloat shine[] = {100.0};
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	/* Smooth Shading */
	glShadeModel (GL_SMOOTH);
	
	/* Enable Light and LIGHT0 */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	/* Z-Buffer */
	glEnable(GL_DEPTH_TEST); 
}

void display(void)
{
	/* Clear Window */
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Light */
    glLightfv (GL_LIGHT0, GL_POSITION, light0_position); 

	/* Get Rotation Angles */
	rot[0] = getRotationX();
	rot[1] = getRotationY();
	rot[2] = 0.0;

	/* Draw a Teapot */
	/* Size,Tx,Ty,Tz,Rotations,Rx Scale, Ry Scale, Rz Scale */
	niceteapot(0.5,getTranslationX(),getTranslationY()\
	,getTranslationZ(),rot,1.0,1.0,1.0);
	
	/* Flush */
    glFlush ();
}

void reshape (int w, int h)
{
	/* Set the Viewport */
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	/* Applies Subsequent Matrix Operations */
	/* to the Projection Matrix Stack */
	glMatrixMode (GL_PROJECTION);
	/* Replace the Current Matrix with the Identity Matrix */
	glLoadIdentity();
	/* Set up a Perspective Projection Matrix */
	gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	/* Specify which Matrix is the Current Matrix */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char ** argv)
{
    /* Initialize the GLUT library */
    glutInit(&argc, argv);
	/* Sets the initial display mode */
	/* Single buffered window */
	/* RGBA mode window */
	/* Window with a depth buffer */        
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	/* Window Size */
    glutInitWindowSize(500,500);
	/* Window Initial Position */
    glutInitWindowPosition(50,50);
	/* Create the Window */
    glutCreateWindow("OpenGL Intro");
	/* Initial Routine */
    init();
	/* Draw the Window when Something Updates */
    glutDisplayFunc(display);
	/* Reorder when Reshape Window */
    glutReshapeFunc(reshape);
	/* Callback for Mouse */
    glutMouseFunc(mouse);
	/* Callback for Keyboard */
    glutKeyboardFunc(keyboard);
	/* Callback for Keyboard Especials */
	/* F1 - F12 */
	/* Directional Keys*/
    glutSpecialFunc(keyboardSpecials);
	/* Enters the GLUT event processing loop */
    glutMainLoop();
    
    return 0;
}

