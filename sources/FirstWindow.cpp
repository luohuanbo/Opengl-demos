#include <GL/glew.h>
#include <GL/freeglut.h>

#pragma comment(lib,"glew32.lib")

void OnRender(){
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();

}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("hello");

	glewInit();

	glClearColor(1, 0, 0, 0); // set the initial color, here is red

	glutDisplayFunc(OnRender);
	glutMainLoop();


}
