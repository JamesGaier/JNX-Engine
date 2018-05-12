//OpenGL includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//C++ includes
#include <iostream>

/* Links to documentation
http://docs.gl/
http://www.glfw.org/docs/latest/
http://glew.sourceforge.net/basic.html
*/

//TODO: Add a shader
int main ( ) {

	/* Initialize the library */
	if ( !glfwInit ( ) )
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow ( 800, 600, "Hello World", NULL, NULL );
	if ( !window ) {
		glfwTerminate ( );
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent ( window );

	if ( glewInit ( ) != GLEW_OK ) {
		std::cout << "GLEW init failed!" << std::endl;
	}

	const unsigned int VERTEX_BUFFER_SIZE = 6;
	const float * const vertex_buffer = new float[VERTEX_BUFFER_SIZE] {
		   -0.5f, -0.5f,
			0.0f,  0.5f,
			0.5f, -0.5f
	};

	unsigned int vertex_buffer_id;
	glGenBuffers ( 1, &vertex_buffer_id );
	glBindBuffer ( GL_ARRAY_BUFFER, vertex_buffer_id );
	glBufferData ( GL_ARRAY_BUFFER, VERTEX_BUFFER_SIZE * sizeof ( float ), vertex_buffer, GL_STATIC_DRAW );

	glEnableVertexAttribArray ( 0 );
	glVertexAttribPointer ( 0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0 );

	glBindBuffer ( GL_ARRAY_BUFFER, 0 );

	/* Loop until the user closes the window */
	while ( !glfwWindowShouldClose ( window ) ) {
		/* Render here */
		glClear ( GL_COLOR_BUFFER_BIT );

		glDrawArrays ( GL_TRIANGLES, 0, VERTEX_BUFFER_SIZE / 2 );

		/* Swap front and back buffers */
		glfwSwapBuffers ( window );

		/* Poll for and process events */
		glfwPollEvents ( );
	}

	glfwTerminate ( );
	return 0;
}