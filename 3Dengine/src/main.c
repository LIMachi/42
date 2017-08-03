#include "glad.c" //petite triche
#include "../glfw-3.2.1/include/GLFW/glfw3.h"
#include <stdlib.h>

#include <sys/stat.h> //stat
#include <fcntl.h> //open
#include <unistd.h> //read, close

//similar to MiniLibX, GLFW uses callback for keyboard input, mice input, etc...
void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	(void)scancode;
	(void)mode;
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

//read the file at "path" and return a static buffer to his content
//if NULL is passed to path, the function will clear is internal information
//the function will return the same content in the buffer if the file was not modified

#define IO6 0, 0, 0, 0, 0, 0
#define IBO2 {0, 0}
#define I4BO2 IBO2, IBO2, IBO2, IBO2

#define _SSTAT0 {0, IO6, I4BO2, IO6, IBO2}
#define SSTAT0 (struct stat)_SSTAT0

char	*read_file_s(const char *path)
{
	static char			*buffer = NULL;
	static long			size = 0;
	static struct stat	data = _SSTAT0;
	struct stat			tmp;
	int					fd;

	if (path == NULL)
	{
		if (buffer != NULL)
			free(buffer);
		size = 0;
		data = SSTAT0;
		return (buffer = NULL);
	}
	if (stat(path, &tmp))
		return (NULL);
	if (tmp.st_dev == data.st_dev && tmp.st_ino == data.st_ino)
		return (buffer);
	if (buffer == NULL || tmp.st_size + 1 > size)
		if ((buffer = realloc(buffer, size = tmp.st_size + 1)) == NULL)
			return (NULL);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (NULL);
	if (read(fd, buffer, tmp.st_size) == -1)
		return ((char*)(0l * close(fd)));
	buffer[tmp.st_size] = '\0';
	close(fd);
	return (buffer);
}

GLuint	prepare_shaders(const char *vertex_shader_path, const char *fragment_shader_path)
{
	GLuint		vertexShader;
	GLuint		fragmentShader;
	GLuint		shaderProgram;
	GLchar		*tmp;
	GLint		success;
	GLchar		infoLog[1024];

	if (vertex_shader_path == NULL || fragment_shader_path == NULL) //invalid input
		return (0);
	if (!(vertexShader = glCreateShader(GL_VERTEX_SHADER)) || //prepare a shader object of the type GL_VERTEX_SHADER
		!(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER)))
		return (0);
	if ((tmp = read_file_s(vertex_shader_path)) == NULL)
		return (0);
	glShaderSource(vertexShader, 1, (const GLchar**)&tmp, NULL); //load the source(s){tmp} in fragmentShader, 1 precise the number of sources to use and NULL could be a list of length of the sources (this function is similar to his OpenCL counter part that load kernel sources for compilation)
	if ((tmp = read_file_s(fragment_shader_path)) == NULL)
		return (0);
	glShaderSource(fragmentShader, 1, (const GLchar**)&tmp, NULL);

	glCompileShader(vertexShader); //self explanatory
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //retrieve some information of the compilation of vertexShader. The type of data is defined here by GL_COMPILE_STATUS and the result is stored in success
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog); //retrieve the log of the compilation of vertexShader, precising a max size of 512, NULL discard the length of infoLog that could have been returned and store the said log in infoLog in null terminated text format
		printf("shader vertex compilation failed: %s\n", infoLog);
	}

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
		printf("shader fragment compilation failed: %s\n", infoLog);
	}

	shaderProgram = glCreateProgram(); //prepare a program object
	glAttachShader(shaderProgram, vertexShader); //self explanatory, append the object to the executable
	glAttachShader(shaderProgram, fragmentShader); //same here
	glLinkProgram(shaderProgram); //link the final executable
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); //like glGetShaderiv, for programs
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog); //like glGetShaderInfoLog, for programs
		printf("shader program compilation failed: %s\n", infoLog);
	}
	glDeleteShader(vertexShader); //remove the shaders object that are no more usefull (imagine removing .o objects after succesfully building a static library or executable)
	glDeleteShader(fragmentShader);

	return (shaderProgram);
}

GLFWwindow	*window;

void	terminal_function()
{
	printf("terminating\n");
	read_file_s(NULL);
	if (window != NULL)
		glfwDestroyWindow(window);
	glfwTerminate();
}

/*
GLfloat face[] = //with GL_TRIANGLE mode, each group of 3 points is concidered a triangle, it's the simples mode
{
	-0.5f, -0.5f, 0.f, //bottom left	-triangle 1
	 0.5f, -0.5f, 0.f, //bottom right	-triangle 1
	-0.5f,  0.5f, 0.f, //top left		-triangle 1
	 0.5f, -0.5f, 0.f, //bottom right	-triangle 2
	-0.5f,  0.5f, 0.f, //top left		-triangle 2
	 0.5f,  0.5f, 0.f  //top right		-triangle 2
};
*/

/*
GLfloat face[] = //with GL_TRIANGLE_STRIP mode, it connect all triangles together, first it store the 3 points of a triangle, then it discards one and get another to make a new triangle, points are in a FIFO
//it's usually the harder to figure out, but also the best for most uses
{
	-0.5f, -0.5f, 0.f, //bottom left	-triangle 1
	 0.5f, -0.5f, 0.f, //bottom right	-triangle 1 2
	-0.5f,  0.5f, 0.f, //top left		-triangle 1 2 3
	 0.5f,  0.5f, 0.f  //top right		-triangle 2 3 4
};
*/

//cube:
//2---3---6---7
//| / | \ | / |
//1---4---5---8
//        2---3---6---7
//        | / | \ | / |
//        1---4---5---8


GLfloat face[] = //with GL_TRIANGLE_FAN mode, the first point is used has a pivot to make triangles, usefull for faces with more than 3 vertices, like and hexagon
{
	-0.5f, -0.5f, 0.f, //bottom left	-triangle pivot (1 2 3 4 5...)
	 0.5f, -0.5f, 0.f, //bottom right	-triangle 1
	 0.5f,  0.5f, 0.f, //top right		-triangle 1 2
	-0.5f,  0.5f, 0.f  //top left		-triangle 2 3
};

int main()
{
	int			width, height;
	int			vwidth = 400, vheight = 400;
	GLuint		program;
	GLint		position_attribute;

	if(!glfwInit())
		return(-1);
	atexit(terminal_function);
	window = glfwCreateWindow(400, 400, "NAME", NULL, NULL);
	if (window == NULL)
		return(-1);
	glfwMakeContextCurrent(window); //set window has the main target
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress); //prepare OpenGL functions
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height); //rectangular viewport, here identical to the window
	glfwSetKeyCallback(window, key_callback);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //set the RGBA color to be used has clearing color

	GLuint VBO;
	glGenBuffers(1, &VBO); //1 = number of buffer needed, VBO = id
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //set VBO has target buffer for array buffer operations
	glBufferData(GL_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW); //populate VBO with face,GL_STATIC_DRAW tell how frequent the changes on the buffer might be

	program = prepare_shaders("shaders/default.vs", "shaders/default.frag");

	position_attribute = glGetAttribLocation(program, "position"); //get the position of "position" attribute in the program
	glEnableVertexAttribArray(position_attribute); //activate the accesibility of "position"
	glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, NULL); //modify/set "position" from the CPU using 3 blocks of GL_FLOAT, GL_FALSE disable normalisation, sizeof(float) * 3 set the stride ("pas" in french), and NULL the offset ((void*)0)

	while (!glfwWindowShouldClose(window)) //acces the static variable "window should close"
	{
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(width / 2 - vwidth / 2, height / 2 - vheight / 2, vwidth, vheight); //reposition the view port if width or height changed, should be activated by a flag turned on by a callback on window change
		glClear(GL_COLOR_BUFFER_BIT); //clear the current color buffer
		glUseProgram(program); //call the shader program
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4); //call the rendering of the first 3 ellements in the set arrays has a triangle
		glfwSwapBuffers(window); //swap video buffer and screen buffer aka refresh the window
		glfwPollEvents(); //call all pending callback for all pending event, put after glfwSwapBuffers so at least one image is visible before the first callback
	}
	return (0);
}
