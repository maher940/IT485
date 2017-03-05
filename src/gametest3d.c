/**
* gametest3d
* @license The MIT License (MIT)
*   @copyright Copyright (c) 2015 EngineerOfLies
*    Permission is hereby granted, free of charge, to any person obtaining a copy
*    of this software and associated documentation files (the "Software"), to deal
*    in the Software without restriction, including without limitation the rights
*    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*    copies of the Software, and to permit persons to whom the Software is
*    furnished to do so, subject to the following conditions:
*    The above copyright notice and this permission notice shall be included in all
*    copies or substantial portions of the Software.
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*    SOFTWARE.
*/
#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <glm\gtx\string_cast.hpp>
#include "loadobj.h"
#include "texture.h"
#include "UIPopup.h"
#include <GL\glut.h>
#include "btBulletDynamicsCommon.h"
#include <GLFW\glfw3.h>
#include <GL\freeglut.h>


static int os;
static int mainmenu;


static int health;
static int experience;
static int mana;



bool hudon = false;
int hudon2 = 0;
void ViewOrtho(int x, int y);
void ViewPerspective(void);
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	GLuint vao;
	GLuint triangleBufferObject;
	char bGameLoopRunning = 1;
	SDL_Event e;
	SDL_Event buttons;
	SDL_Event test;

	health = 100;
	mana = 100;
	experience = 0;
	init_logger("gametest3d.log");
	if (graphics3d_init(1024, 768, 1, "gametest3d", 33) != 0)
	{
		return -1;
	}

	//std::vector<glm::vec3> vertices;
	//std::vector<glm::vec2> uvs;
	//std::vector<glm::vec3> normals; // Won't be used at the moment.
	//bool res = objload("monkey.obj", vertices, uvs, normals);

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals; // Won't be used at the moment.
	bool res = objload("monkey.obj", vertices, uvs, normals);

	GLuint Texture = loadBMP_custom("uvtemplate.bmp");

	GLuint MatrixID = glGetUniformLocation(graphics3d_get_shader_program(), "MVP");
	GLuint TextureID = glGetUniformLocation(graphics3d_get_shader_program(), "myTextureSampler");

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f),4.0f/3.0f,0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 Model = glm::mat4(1.0f);

	glm::mat4 mvp = Projection * View * Model;

	




	/*
	glGenVertexArrays(1, &vao);//holds vertex information, makes vertex array in memory
	glBindVertexArray(vao); //make our vertex array object, we need it to restore state we set after binding it. Re-binding reloads the state associated with it. modify this vertex buffer

	glGenBuffers(1, &triangleBufferObject); //create the buffer
	glBindBuffer(GL_ARRAY_BUFFER, triangleBufferObject); //we're "using" this one now,binds the buffer as array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW); //formatting the data for the buffer, sets the data for buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind any buffers,clears context


	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	*/
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	/*
	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
	*/
	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	slog("glError: %d", glGetError());
	
	//glm::mat4x4 view;
	glm::vec3 campos = glm::vec3(0.0, 0.0, 3.0);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	GLfloat cameraSpeed = 0.05f;
	


	while (bGameLoopRunning)
	{
		//sdl function to get inputs
		//update stuff
		//CameraSetUp();
		if (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				bGameLoopRunning = 0;
			//keyup or escape key pressed
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				bGameLoopRunning = 0;
			
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_w)
			{
				//cameraPos += cameraSpeed * cameraFront;
				campos += cameraSpeed * cameraFront;

				//hudon = true;
				printf("w\n");
			}
			
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_s)
			{
				//cameraPos += cameraSpeed * cameraFront;
				campos -= cameraSpeed * cameraFront;
				//hudon = false;
				printf("s\n");
			}
			
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_a)
			{
				//cameraPos += cameraSpeed * cameraFront;
				campos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				printf("a\n");
				health = health - 10;
				mana = mana + 10;
				experience = experience + 100;
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_d)
			{
				//cameraPos += cameraSpeed * cameraFront;
				campos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				printf("d\n");
				//health = health - 10;
				//mana = mana + 10;
				//experience = experience + 100;
				//printf("%d", health);


				
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_p)
			{
				//cameraPos += cameraSpeed * cameraFront;
				//campos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				//std::cout << glm::to_string(view) << std::endl;
				printf("p\n");
				//drawstats(health, experience, mana);
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_o)
			{
				//cameraPos += cameraSpeed * cameraFront;
				//campos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
				//std::cout << glm::to_string(view) << std::endl;
				//std::cout << glm::to_string(vertices) << std::endl;
				//drawstats(100, 50, 100);
				//glorth
				
			}
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_TAB)
			{
				hudon2++;
				
			}
			
		}
		//draw stuff
		//background color
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		//if (SDL_PollEvent(&buttons))
		//{
		//drawstats(100, 50, 100);
		//}
		//view = glm::lookAt(campos, campos + cameraFront, cameraUp);
		//glm::mat4 projection;
		//projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

		//glm::mat4 View = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		View = glm::lookAt(campos, campos + cameraFront, cameraUp);
		glm::mat4 mvp = Projection * View * Model;


		//ViewOrtho(1024, 768);
		//ViewPerspective();
		/* drawing code in here! */
		glUseProgram(graphics3d_get_shader_program());
		//GLint viewLoc = glGetUniformLocation(graphics3d_get_shader_program(), "view");
		//GLint projLoc = glGetUniformLocation(graphics3d_get_shader_program(), "projection");
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);


		//Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		glEnableVertexAttribArray(0); //0 is our index, refer to "location = 0" in the vertex shader
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); //bind the buffer we're applying attributes to
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //tell gl (shader!) how to interpret our vertex data

		glEnableVertexAttribArray(1); //attribute 1 is for vertex color data
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0); //color data is 48 bytes in to the array
		//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);


		
		
		
		
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glUseProgram(0);
		/* drawing code above here! */

		


		if (hudon2 %2 != 0)
		{
			ViewOrtho(1024, 768);

			drawstats(health, experience, mana);
		}

		ViewOrtho(1024, 768);
		drawhud(health, mana);
		ViewPerspective();
		//glRasterPos2i(100, 120);
		////glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
		//glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"text to render");

		//glRasterPos3f(30.0f, 20.0f, 0.0f);
		//glDisable(GL_TEXTURE_2D);
		//glColor3fv(1,0,0);
		//glColor3f(1, 0, 0);
		//glLoadIdentity();
		//glRasterPos2i(100, 100);
		//glutBitmapString(GLUT_BITMAP_HELVETICA_12, (UCHAR*)"This is a simple text.");
		//glEnable(GL_TEXTURE_2D);
		//glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Hello World!");
		
		glColor3f(1, 0, 0);
		//glRasterPos2f(50, 50);
		//std::string text;
		//text = "This is a simple text.";
		//int len, i;
		//std::string healthstring = std::to_string(health);
		//std::string manastring = std::to_string(mana);
		//std::string expstring = std::to_string(experience);
/*
		std::string healthstring = "Total Health: " + std::to_string(health);
		
		
		
		glWindowPos2i(300, 600);
		//len = (int)strlen(text);
		int len = healthstring.length();
		
		
		for (int i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, healthstring[i]);
		}
		
		std::string manastring = "Total Mana: " + std::to_string(mana);

		glWindowPos2i(300, 550);
		int len2 = manastring.length();


		for (int i = 0; i < len2; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, manastring[i]);
		}

		std::string expstring = "Total Exp: " + std::to_string(experience);
		glWindowPos2i(300, 500);
		int len3 = expstring.length();

		for (int i = 0; i < len3; i++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, expstring[i]);
		}



		*/

		// Send our transformation to the currently bound shader, 
		
		//glRasterPos2i(10, 10);
		//std::string s = "Some text";
		//std::string text;
		//text = "This is a simple text.";
		//for (int i = 0; i<text.size(); i++) {
		//	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]); // generation of characters in our text with 9 by 15 GLU font
		//}

		//void * font = GLUT_BITMAP_9_BY_15;
		/*void * font = GLUT_BITMAP_9_BY_15;
		for (std::string::iterator i = s.begin(); i != s.end(); ++i)
		{
			char c = *i;
			//this does nothing, color is fixed for Bitmaps when calling glRasterPos
			//glColor3f(1.0, 0.0, 1.0); 
			//glutBitmapCharacter(font, c);
			//glutSetColor(2, 2, 2, 2);
		}
		*/
		//glBegin
		
		//ViewOrtho(1024, 768);
		
		//ViewPerspective();
		
		graphics3d_next_frame();
	}
	return 0;
}




void ViewOrtho(int x, int y)							// Set Up An Ortho View
{
	glMatrixMode(GL_PROJECTION);					// Select Projection
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();						// Reset The Matrix
	glOrtho(0, x, y, 0, -1, 1);				// Select Ortho Mode
	glMatrixMode(GL_MODELVIEW);					// Select Modelview Matrix
	glPushMatrix();							// Push The Matrix
	glLoadIdentity();						// Reset The Matrix
}

void ViewPerspective(void)							// Set Up A Perspective View
{
	glMatrixMode(GL_PROJECTION);					// Select Projection
	glPopMatrix();							// Pop The Matrix
	glMatrixMode(GL_MODELVIEW);					// Select Modelview
	glPopMatrix();							// Pop The Matrix
}



/*eol@eof*/
