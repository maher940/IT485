#include "UIPopup.h"

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
#include "loadobj.h"
#include "texture.h"
#include "UIPopup.h"
#include <GL\glut.h>
#include "btBulletDynamicsCommon.h"
#include <GLFW\glfw3.h>
#include <GL\freeglut.h>

void drawstats(float health, float exp, float mana)
{

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(510, 135);
	glVertex2f(300, 135);
	glVertex2f(300, 285);
	glVertex2f(510, 285);
	glEnd();

	glColor3f(1, 0, 0);
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

	std::string expstring = "Total Exp: " + std::to_string(exp);
	glWindowPos2i(300, 500);
	int len3 = expstring.length();

	for (int i = 0; i < len3; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, expstring[i]);
	}


	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex2f(300, 135);
	glVertex2f(510, 135);
	glVertex2f(510, 185);
	glVertex2f(300, 185);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex2f(300, 185);
	glVertex2f(510, 185);
	glVertex2f(510, 235);
	glVertex2f(300, 235);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(1, 0, 0);
	glVertex2f(300, 235);
	glVertex2f(510, 235);
	glVertex2f(510, 285);
	glVertex2f(300, 285);
	glEnd();
}

void deletestats()
{

}


void drawhud(float health, float mana)
{


	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(health, 700);
	glVertex2f(0, 700);
	glVertex2f(0, 720);
	glVertex2f(health, 720);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex2f(mana, 730);
	glVertex2f(0, 730);
	glVertex2f(0, 750);
	glVertex2f(mana, 750);
	glEnd();

}