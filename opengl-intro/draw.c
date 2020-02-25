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

#include "draw.h"

void cubeT(GLdouble sz, GLfloat tx,GLfloat ty,GLfloat tz,\
GLfloat * a,GLfloat rx,GLfloat ry,GLfloat rz)
{
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, cube_shininess);

	glPushMatrix();     
		glTranslatef (tx,ty,tz);

		glRotatef (a[0],rx,0.0,0.0);
		glRotatef (a[1],0.0,ry,0.0);
		glRotatef (a[2],0.0,0.0,rz);

		glutSolidCube(sz);
	glPopMatrix();
}

void niceteapot(GLdouble sz, GLfloat tx,GLfloat ty,GLfloat tz,\
GLfloat * a,GLfloat rx,GLfloat ry,GLfloat rz)
{
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, cube_shininess);

	glPushMatrix();     
		glTranslatef (tx,ty,tz);

		glRotatef (a[0],rx,0.0,0.0);
		glRotatef (a[1],0.0,ry,0.0);
		glRotatef (a[2],0.0,0.0,rz);

		glutSolidTeapot(sz);

	glPopMatrix();
}

