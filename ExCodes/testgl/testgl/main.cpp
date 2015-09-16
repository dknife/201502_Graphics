#pragma comment (lib, "freeglutd.lib")
#include <vector>
#include <gl/freeglut.h>
#include <glm\glm.hpp>
char *WindowName = "openGL TEST";
glm::vec2 Window_Pos = glm::vec2(100, 100);
glm::vec2 Window_Size = glm::vec2(512, 512);
glm::vec3 Red_Color = glm::vec3(1.f, 0.f, 0.f);
float Axis_Length = 5.f;
GLfloat Axis[] = {
 0.f, 0.f, 0.f, 
 1.f, 0.f, 0.f,
 0.f, 0.f, 0.f, 
 0.f, 1.f, 0.f,
 0.f, 0.f, 0.f, 
 0.f, 0.f, 1.f,
};
GLfloat Axis_Color[] = {
 1.f, 0.f, 0.f, 
 1.f, 0.f, 0.f,
 0.f, 1.f, 0.f, 
 0.f, 1.f, 0.f,
 0.f, 0.f, 1.f, 
 0.f, 0.f, 1.f,
};
GLfloat Poly_pos[] = {
 1.f, 0.f, 0.f,
 0.f, 1.f, 0.f,
 0.f, 0.f, 1.f
};
GLfloat Poly_color[] = {
 1.f, 0.f, 0.f,
 0.f, 1.f, 0.f,
 0.f, 0.f, 1.f
};
float zoom = 0.0;
float aspRatio = 1.0;
std::vector<glm::vec3> Polygon_Pos;
std::vector<glm::vec3> Polygon_Color;

void DrawAxes(void) {
 
 glVertexPointer(3, GL_FLOAT, 0, Axis);
 glColorPointer(3, GL_FLOAT, 0, Axis_Color);
 glEnableClientState(GL_VERTEX_ARRAY);
 glEnableClientState(GL_COLOR_ARRAY);
 // 그리는 형태, 시작위치 , 정점갯수
 glDrawArrays(GL_LINES, 0, 6);
 glDisableClientState(GL_VERTEX_ARRAY);
 glDisableClientState(GL_COLOR_ARRAY);
}
void DrawCircle(glm::vec3 pos, glm::vec3 color, float Poly_Size = 1.f, int nv = 30)
{
 float c, s, angle, angle_Step;
 
 float c_Step, s_Step;
 
 for(int i =0 ; i <nv ; i++)
 {
  angle = i * 2.0 * 3.141592 / float(nv);
  angle_Step = (i + 1) * 2.0 * 3.141592 / float(nv);
  c = cos(angle) ;
  s = sin(angle) ;
  c_Step = cos(angle_Step);
  s_Step = sin(angle_Step);
  Polygon_Pos.push_back(glm::vec3(0.0  * Poly_Size + pos.x, 0.0 * Poly_Size + pos.y, 0.0 + pos.z));
  Polygon_Pos.push_back(glm::vec3(c  * Poly_Size + pos.x, s  * Poly_Size + pos.y, 0.0 + pos.z));
  Polygon_Pos.push_back(glm::vec3(c_Step * Poly_Size + pos.x, s_Step * Poly_Size + pos.y, 0.0 + pos.z));
  
  Polygon_Color.push_back(glm::vec3(color.x, color.y, color.z));
  Polygon_Color.push_back(glm::vec3(color.x, color.y, color.z));
  Polygon_Color.push_back(glm::vec3(color.x, color.y, color.z));
  //Polygon_Color.push_back(glm::vec3(0, 0, 0));
  //Polygon_Color.push_back(glm::vec3(c, s, c * s));
  //Polygon_Color.push_back(glm::vec3(c_Step, s_Step, c_Step * s_Step));
 }
}
void DrawQuads(glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 color = glm::vec3(0.f, 0.f, 0.f), glm::vec3 size = glm::vec3(1.f, 1.f, 1.f))
{
 Polygon_Pos.push_back(glm::vec3(-0.5 * size.x + pos.x, -0.5 * size.y + pos.y, 0.0 * size.z + pos.z));
 Polygon_Pos.push_back(glm::vec3( 0.5 * size.x + pos.x, -0.5 * size.y + pos.y, 0.0 * size.z + pos.z));
 Polygon_Pos.push_back(glm::vec3( 0.5 * size.x + pos.x,  0.5 * size.y + pos.y, 0.0 * size.z + pos.z));
 Polygon_Pos.push_back(glm::vec3(-0.5 * size.x + pos.x, -0.5 * size.y + pos.y, 0.0 * size.z + pos.z));
 Polygon_Pos.push_back(glm::vec3( 0.5 * size.x + pos.x,  0.5 * size.y + pos.y, 0.0 * size.z + pos.z));
 Polygon_Pos.push_back(glm::vec3(-0.5 * size.x + pos.x,  0.5 * size.y + pos.y, 0.0 * size.z + pos.z));
 for(int i = 0; i < 6 ;i++)
  Polygon_Color.push_back(glm::vec3(color.x, color.y, color.z));
}
void DrawTriangle(glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::vec3 color = glm::vec3(0.f, 0.f, 0.f), glm::vec3 size = glm::vec3(1.f, 1.f, 1.f))
{

 Polygon_Pos.push_back(glm::vec3( 0.0 * size.x + pos.x,  1.0 * size.y + pos.y, 0.0 * size.z + pos.z));
 Polygon_Pos.push_back(glm::vec3(-0.5 * size.x + pos.x,  0.0 * size.y + pos.y, 0.0 * size.z + pos.z));
 Polygon_Pos.push_back(glm::vec3( 0.5 * size.x + pos.x,  0.0 * size.y + pos.y, 0.0 * size.z + pos.z));
 for(int i = 0; i < 6 ;i++)
  Polygon_Color.push_back(glm::vec3(color.x, color.y, color.z));
}

void init(void) {
 
 for(int i = 0; i<18; i++)
  Axis[i] *= Axis_Length;
 // 위치, 색깔, 사이즈
 DrawQuads(glm::vec3(1.0 ,0.4,0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.1, 0.8,0.5));
 DrawQuads(glm::vec3(-0.8,0.5,0.0), glm::vec3(1.0, 1.0, 0.0), glm::vec3(0.1, 1.0,0.5));
 // 위치, 색깔, 사이즈, 몇각형
 DrawCircle(glm::vec3(1.0, 0.8, 0.0), glm::vec3(1.f, 1.f, 0.f) , 0.2, 30);
 DrawCircle(glm::vec3(-0.8, 1.0, 0.0), glm::vec3(1.f, 1.f, 1.f),  0.25, 30);
 // 위치, 색깔, 사이즈
 DrawTriangle(glm::vec3(-0.3,0.0,0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.8, 1.0,0.0));
 DrawTriangle(glm::vec3( 0.3,0.0,0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 0.5,0.0));
 glClearColor(0.0, 0.0, 0.0, 0.0);
}
void ResetProjection(float aspRatio) {
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 //glOrtho(-aspRatio*zoom, aspRatio*zoom, -1*zoom, 1*zoom, -1, 1);
 
 gluPerspective(60, aspRatio, 0.001, 1000);

}
// reshape callback
void reshape(int w, int h) {
 aspRatio = float(w)/float(h);
 glViewport(0,0,w,h);
 ResetProjection(aspRatio);
 glutPostRedisplay();
}
void display(void) {
 
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 
 gluLookAt(3 + zoom, 3 + zoom, 3 + zoom, 0, 0, 0,  0, 1, 0);
 glClear(GL_COLOR_BUFFER_BIT);
 DrawAxes(); 
 // glm, vector 버전
 glVertexPointer(3, GL_FLOAT, 0, &Polygon_Pos.front()); 
 glColorPointer(3, GL_FLOAT, 0, &Polygon_Color.front());
 
 // float 배열 버전
 //glVertexPointer(3, GL_FLOAT, 0, Poly_pos); 
 //glColorPointer(3, GL_FLOAT, 0, Poly_color);
 glEnableClientState(GL_VERTEX_ARRAY);
 glEnableClientState(GL_COLOR_ARRAY);
 
 // 그릴 도형, 시작위치, 정점 갯수
 glDrawArrays(GL_TRIANGLES, 0, Polygon_Pos.size()); // glm, vector 버전
 //glDrawArrays(GL_POLYGON, 0, 3); // float 배열 버전
 
 glDisableClientState(GL_VERTEX_ARRAY);
 glDisableClientState(GL_COLOR_ARRAY);

 glutSwapBuffers();
}
void keyboard(unsigned char c, int x, int y) 
{
 switch(c) {
  case 27: exit(0);
  case 'z': zoom += 0.1; ResetProjection(aspRatio); break;
  case 'Z': zoom -= 0.1; ResetProjection(aspRatio); break;
 }
 
 glutPostRedisplay();
}
int main(int argc, char **argv) {
 
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
 glutInitWindowSize(Window_Size.x, Window_Size.y);
 glutInitWindowPosition(Window_Pos.x, Window_Pos.y);
 glutCreateWindow(WindowName);
 
 init(); // 초기화
 
 // 콜백 함수 등록 
 glutDisplayFunc(display);
 glutIdleFunc(display);
 glutReshapeFunc(reshape);
 glutKeyboardFunc(keyboard);
 
 
 // 무한루프
 glutMainLoop(); 
 return 0;
} 