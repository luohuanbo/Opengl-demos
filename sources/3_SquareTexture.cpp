#include <GL/glew.h>
#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

#pragma comment(lib,"glew32.lib")

using namespace std;
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec2 aTexCoord;\n"
	"out vec2 TexCoord;\n"
	"void main()\n"
	"{\n"
	"	gl_Position =  vec4(aPos, 1.0f);\n"
	"	TexCoord =  aTexCoord;\n"
	"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"in vec2 TexCoord;\n"
	"uniform sampler2D ourTexture;\n"
	"void main()\n"
	"{\n"
	"   FragColor = texture(ourTexture, TexCoord);\n"
	"}\n\0";


void OnRender(){
	glClear(GL_COLOR_BUFFER_BIT);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
		// position            texture coords
		-0.5f, 0.5f, 0.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,	1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,	1.0f, 1.0f

	};

	unsigned int indices[] = {  // note that we start from 0!
	    0, 1, 3, // first front triangle
	    1, 3, 2, // second front triangle

	}; 

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data =stbi_load("materials/doge.jpg", &width, &height, &nrChannels, 0);

	//set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)          
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned int VBO, VAO, EBO, texture;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenTextures(1, &texture);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindTexture(GL_TEXTURE_2D, texture);


	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);  

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glUseProgram(shaderProgram);

	glutDisplayFunc(OnRender);
	glutMainLoop();


}
