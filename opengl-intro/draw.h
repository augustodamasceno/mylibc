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

#ifndef _DRAW_H
#define _DRAW_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


/* Material */ 
static const GLfloat cube_diffuse[] =  { 0.1, 0.9, 0.9, 1.0 };
static const GLfloat cube_shininess[] = { 5.0 };

/* Draw cube with transformations */
void cubeT(GLdouble sz, GLfloat tx,GLfloat ty,GLfloat tz,\
GLfloat * a,GLfloat rx,GLfloat ry,GLfloat rz);   

/* Draw teapot with transformations */
void niceteapot(GLdouble sz, GLfloat tx,GLfloat ty,GLfloat tz,\
GLfloat * a,GLfloat rx,GLfloat ry,GLfloat rz);


#endif /* _DRAW_H  */

