#include <Windows.h>
#include <gl/GL.h>
#include <gl/glut.h>

#define TEXSIZE 16
GLubyte myTex[TEXSIZE][TEXSIZE][3];

void CreateTexture(void) {
	for (int i = 0; i < TEXSIZE; i++) {
		for (int j = 0; j < TEXSIZE; j++) {
			for (int k = 0; k < 3; k++) {
				myTex[i][j][k] = rand() % 256;
			}
		}
	}
}

void SetupTexture(void) {
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXSIZE, TEXSIZE, 0, GL_RGB,
				GL_UNSIGNED_BYTE, &myTex[0][0][0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_TEXTURE_2D);
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	static float angle = 0.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(angle, 1, 1, 0);
	//angle += 0.5;
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1.0, -1, 0);
	glTexCoord2f(2, 0);
	glVertex3f( 1, -1, 0);
	glTexCoord2f(2, 2);
	glVertex3f( 1,  1, 0);
	glTexCoord2f(0, 2);
	glVertex3f(-1,  1, 0);
	glEnd();
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(512, 512);
	glutCreateWindow("My Texture");

	glClearColor(1.0, 0.0, 0.0, 1.0);

	CreateTexture(); // create 2d image array
	SetupTexture(); // setup openGL texture

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMainLoop();

	return 0;
}