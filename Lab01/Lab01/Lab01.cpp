// Moska³a Damian

#include "stdafx.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

double F1(double x, int y)
{
	int i = 0;
	double a = 1;

	if (y == 0)
	{
		return 1;
	}
	else
	{
		while (i < y)
		{
			i++;
			a = a * x;
		}
	}

	return a;
}

double Div(double value, int x)
{
	if (x == 0)
	{
		return 1;
	}
	else
	{
		while (x > 1)
		{
			value = value / x--;
		}
	}

	return value;
}

double Sinus(double x)
{
	int i = 0, j = 1, sign = 1;
	double y1 = 0, d = 1000;

	if (x < 0.0)
	{
		x = -1 * x;
		sign = -1;
	}

	while (x > 360.0*3.1415926 / 180)
	{
		x = x - 360 * 3.1415926 / 180;
	}

	if (x > (270.0 * 3.1415926 / 180))
	{
		sign = sign * -1;
		x = 360.0*3.1415926 / 180 - x;
	}
	else if (x > (180.0 * 3.1415926 / 180))
	{
		sign = sign * -1;
		x = x - 180.0 *3.1415926 / 180;
	}
	else if (x > (90.0 * 3.1415926 / 180))
	{
		x = 180.0 *3.1415926 / 180 - x;
	}

	while (F1(d, 2) > 1.0E-16)
	{
		i++;
		d = j * Div(F1(x, (2 * i - 1)), (2 * i - 1));
		y1 = y1 + d;
		j = -1 * j;
	}
	return (sign * y1);
}

double Cosinus(double x)
{
	int i = 0, j = 1, sign = 1;
	double y1 = 0, d = 1000;

	if (x < 0)
	{
		x = -1 * x;
	}

	while (x > 360.0*3.1415926 / 180)
	{
		x = x - 360 * 3.1415926 / 180;
	}

	if (x > (270 * (3.1415926 / 180)))
	{
		x = 360 * (3.1415926 / 180) - x;
	}

	if (x > (180 * (3.1415926 / 180)))
	{
		sign = -1;
		x = x - 180 * (3.1415926 / 180);
	}

	if (x > (90 * (3.1415926 / 180)))
	{
		sign = -1;
		x = 180 * (3.1415926 / 180) - x;
	}

	while (F1(d, 2) > 1.0E-16)
	{
		i++;
		d = j * Div(F1(x, (2 * i - 2)), (2 * i - 2));
		y1 = y1 + d;
		j = -1 * j;
	}
	return (y1*sign);
}

GLsizei rsize = 25.f;
GLfloat x1 = 25.0f;
GLfloat y1 = 25.0f;
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
GLfloat windowWidth;
GLfloat windowHeight;
GLfloat angle = 0.0f;

void RenderScene(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	GLint trialangleAmount = 6;
	GLfloat twicePI = 2.f *3.14f;
	angle += 0.8f;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x1, y1, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-x1, -y1, 0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (GLint i = 0; i <= trialangleAmount; i++)
	{
		glVertex2f
		(
			x1 + ((6.0*Cosinus(i*twicePI / trialangleAmount)) * 4.0f),
			y1 + ((6.0*Sinus(i*twicePI / trialangleAmount)) * 4.0f)
		);
	}

	glEnd();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

GLfloat xsteptemp = 0;
GLfloat ysteptemp = 0;

void TimerFunction(int value)
{
	GLboolean x_bool = false, y_bool = false;
	x1 += xsteptemp;
	y1 += ysteptemp;

	if (x1 == windowWidth - rsize && y1 == rsize)
	{
		xsteptemp = 0.f;
		ysteptemp = ystep;
	}

	if (x1 == windowWidth - rsize && y1 == windowHeight - rsize)
	{
		xsteptemp = -xstep;
		ysteptemp = 0.f;
	}

	if (x1 == rsize && y1 == windowHeight - rsize)
	{
		xsteptemp = 0.f;
		ysteptemp = -ystep;
	}

	if (x1 == rsize && y1 == rsize)
	{
		xsteptemp = xstep;
		ysteptemp = 0.f;
	}

	if (x1 > windowWidth - rsize)
	{
		x1 = windowWidth - rsize - 1;
	}

	if (y1 > windowHeight - rsize)
	{
		y1 = windowHeight - rsize - 1;
	}

	if (x1 < rsize) 
	{
		x1 = rsize;
		xsteptemp = 0;
		ysteptemp = -1.0f;
	}

	if (y1 < rsize)
	{
		y1 = rsize;
	}

	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

void SetupRC(void) 
{
	glClearColor(0.60f, 0.4f, 0.12f, 1.0f);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	if (h == 0)
	{
		h = 1;
	}

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Zadanie 1 - Moska³a Damian");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}