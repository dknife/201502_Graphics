#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glColor3f(0,0,0);
		glVertex3f(0,-1,0);
		glColor3f(0,1,0);
		glVertex3f(1,0,0);
		glColor3f(0,0,1);
		glVertex3f(0,1,0);
		glColor3f(1,1,1);
		glVertex3f(-1,0,0);
	glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("A New GL Window");

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}