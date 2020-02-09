#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#pragma comment(lib,"glew32.lib")

using namespace std;
using namespace glm;
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"uniform mat4 MVP;\n"
	"void main()\n"
	"{\n"
	"	gl_Position =  MVP * vec4(aPos, 1.0f);\n"
	"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 1.f, 1.0f, 1.0f);\n"
	"}\n\0";


void OnRender(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glutSwapBuffers();

}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("hello");

	glewInit();

	glClearColor(0, 0, 0, 0); 

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, -1.0f,
		-0.5f, -0.5f, -1.0f,
		0.5f, -0.5f, -1.0f,
		0.5f, 0.5f, -1.0f

	};

	unsigned int indices[] = {  // note that we start from 0!
	    0, 1, 3, // first front triangle
	    1, 3, 2, // second front triangle
	    0, 3, 4, // first top triangle
	    3, 4, 7, // second top triangle
	    0, 1, 4, // first left triangle
	    1, 4, 5, // second left triangle
	    3, 2, 7, // first right triangle
	    2, 7, 6, // second right triangle
	    1, 2, 5, // first bottom triangle
	    2, 5, 6, // second bottom triangle
	    4, 5, 7, // first back triangle
	    5, 7, 6  // second back triangle

	}; 


	mat4 model = translate(mat4(1.0f), vec3(0.0f,0.0f,0.1f));
    //mat4 projection = perspective(radians(45.0f), (float)1 / (float)1, 0.1f, 100.0f);
    mat4 projection = ortho(-3.0f, 3.0f, -3.0f, 3.0f, 0.1f, 100.0f);
    mat4 view = lookAt(vec3(-2.0f, -5.0f, -5.0f), 	// position
     				   vec3(0.0f, 0.0f, 0.0f),	// target
     				   vec3(0.0f, 1.0f, 0.0f)); // up
    mat4 MVP = projection * view * model;
	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "MVP"), 1, GL_FALSE, value_ptr(MVP));

	glutDisplayFunc(OnRender);
	glutMainLoop();


}
