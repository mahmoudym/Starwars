#define _NO_CRT_STDIO_INLINE
#include "TextureBuilder.h"
#include <stdio.h>
#include <math.h>
#include <random>
#include <glut.h>
#include <string> 

#define GLUT_KEY_ESCAPE 27

GLuint texID;
GLuint ship;
GLuint blackhole;
GLuint red;
GLuint water;
GLuint meteor;
GLuint white;
void Display(void);
void Anim(void);
void Key(unsigned char key, int x, int y);
void drawRect(int x, int y, int w, int h);
int* bezier(float t, int* p0, int* p1, int* p2, int* p3);
void print(int x, int y, char *string);
void Timer(int value);
void Timer1(int value);
void drawCircle(int x, int y, float r);
int rep = 1;
float back = 0.0f;
float back2 = 0.0f;
float shipy = 0.0f;
int x = 0;
int y = 0;
int x2 = 0;
int y2 = 0;
float i2 =0.0f;
float obx = 0.0f;
float i = 0.0f;
int p0[2] = { 126, 43 };
int p1[2] = { 35, 169 };
int p2[2] = { 178, 172 };
int p3[2] = { 130, 135 };
int p10[2] = { 441, 306 };
int p11[2] = { 51, 449 };
int p12[2] = { 532, 454 };
int p13[2] = { 121, 320 };
float score = 0.0f;
bool win = false;
bool lose = false;
bool hit = false;
int hits = 0;
int acq = 0;
int meteorY = 0;
int bonusY = 0;
int met = 0;

void Display(void) {
	if (!lose && !win){
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	

		glTranslatef(back, 0.0f, 0.0);
		glBindTexture(GL_TEXTURE_2D, texID);
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);			glVertex3f(0, 0, 0);
		glTexCoord2f(rep, 0.0f);			glVertex3f(4600, 0, 0);
		glTexCoord2f(rep, rep);				 glVertex3f(4600, 1000, 0);
		glTexCoord2f(0.0f, rep);			 glVertex3f(0, 1000, 0);
		glEnd();
	
	
		
	glPopMatrix();


	/*glPushMatrix();
	glBegin(GL_QUADS); // GL_QUAD_STRIP
	glVertex3f(0.0f, 250.0f, 0.0f);
	glVertex3f(100.0f, 250.0f, 0.0f);
	glVertex3f(100.0f, 300.0f, 0.0f);
	glVertex3f(0.0f, 300.0f, 0.0f);
	glEnd();
	glPopMatrix();
	*/

	glPushMatrix();
	glTranslatef(0, shipy, 0);
	glBindTexture(GL_TEXTURE_2D, blackhole);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 275.0f, 0.0f);
	glVertex3f(0.0f, 325.0f, 0.0f);
	glVertex3f(50.0f, 310.0f, 0.0f);
	glVertex3f(50.0f, 290.0f, 0.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, ship);
	drawRect(50, 290, 150, 310);
	glBindTexture(GL_TEXTURE_2D, water);
	drawRect(60, 295, 70, 305);
	drawRect(80, 295, 90, 305);
	drawRect(100, 295, 110, 305);
	drawRect(120, 295, 130, 305);
	glBindTexture(GL_TEXTURE_2D, red);
	glBegin(GL_TRIANGLES); // GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN
	glVertex3f(150.0f, 290.0f, 0.0f);
	glVertex3f(150.0f, 310.0f, 0.0f);
	glVertex3f(175.0f, 300.0f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES); // GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN
	glVertex3f(90.0f, 310.0f, 0.0f);
	glVertex3f(140.0f, 310.0f, 0.0f);
	glVertex3f(90.0f, 340.0f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES); // GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN
	glVertex3f(90.0f, 290.0f, 0.0f);
	glVertex3f(140.0f, 290.0f, 0.0f);
	glVertex3f(90.0f, 260.0f, 0.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(obx, 0, 0);
	glBindTexture(GL_TEXTURE_2D, blackhole);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			glVertex3f(2200, 0, 0);
	glTexCoord2f(rep, 0.0f);			glVertex3f(2300, 0, 0);
	glTexCoord2f(rep, rep);				 glVertex3f(2300, 600, 0);
	glTexCoord2f(0.0f, rep);			 glVertex3f(2200, 600, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, y, 0);
	glBindTexture(GL_TEXTURE_2D, meteor);
	switch (met){
	case 0: 
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2200, meteorY - 30, 0);
		glTexCoord2f(rep, 0.0f);
		glVertex3f(2300, meteorY - 40, 0);
		glTexCoord2f(rep, rep);
		glVertex3f(2300, meteorY + 60, 0);

		glTexCoord2f(0.0f, rep);
		glVertex3f(2200, meteorY + 50, 0);
		glTexCoord2f(0.0f, rep);
		glVertex3f(2150, meteorY, 0);
		glEnd(); break;
	case 1:
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2200, meteorY - 40, 0);
		glTexCoord2f(rep, 0.0f);
		glVertex3f(2300, meteorY - 35, 0);
		glTexCoord2f(rep, rep);
		glVertex3f(2300, meteorY + 20, 0);

		glTexCoord2f(0.0f, rep);
		glVertex3f(2200, meteorY + 40, 0);
		glTexCoord2f(0.0f, rep);
		glVertex3f(2150, meteorY, 0);
		glEnd(); break;
	case 2:
		glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(2200, meteorY - 60, 0); 
		glTexCoord2f(rep, 0.0f);
		glVertex3f(2300, meteorY - 50, 0);
		glTexCoord2f(rep, rep);
		glVertex3f(2300, meteorY + 70, 0);

		glTexCoord2f(0.0f, rep);
		glVertex3f(2200, meteorY + 90, 0);
		glTexCoord2f(0.0f, rep);
		glVertex3f(2150, meteorY, 0);
		glEnd(); break;
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x2, y2, 0);
	glBindTexture(GL_TEXTURE_2D, water);
	drawCircle(2250, bonusY, 30);
	glPopMatrix();

	/*char* p2s[20];
	sprintf((char *)p2s, "%i",acq);
	print(490, 575, (char *)p2s);
	glFlush();*/
	}
	else
		if(lose &&!win){
			glClear(GL_COLOR_BUFFER_BIT);
			glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, white);
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);			glVertex3f(0, 0, 0);
		glTexCoord2f(rep, 0.0f);			glVertex3f(2300, 0, 0);
		glTexCoord2f(rep, rep);				 glVertex3f(2300, 600, 0);
		glTexCoord2f(0.0f, rep);			 glVertex3f(0, 600, 0);
		glEnd();
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, red);

		char* p2s[20];
		sprintf((char *)p2s, "You Lose");
		print(1150, 300, (char *)p2s);
		glFlush();
	}
else
if (!lose && win){
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, white);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);			glVertex3f(0, 0, 0);
	glTexCoord2f(rep, 0.0f);			glVertex3f(2300, 0, 0);
	glTexCoord2f(rep, rep);				 glVertex3f(2300, 600, 0);
	glTexCoord2f(0.0f, rep);			 glVertex3f(0, 600, 0);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, red);
	char* p2s[20];
	sprintf((char *)p2s, "You Win");
	print(1150, 300, (char *)p2s);
	glFlush();
}
}

void Anim(){
	back -= 0.03f;
	if (back < -2300){
		while (back < 0){
			back += 0.01;
		}
	}
	score += 0.001;
	obx -= 0.03;
	if (obx < -2100){
		win = true;
	}
	x -= 0.5;

	i += 0.001;
	int* res = bezier(i, p0, p1, p2, p3);
	x = res[0]; y = res[1];

	i2 += 0.0005;
	int* res2 = bezier(i2, p10, p11, p12, p13);
	x2 = res2[0]; y2 = res[1];
	if (shipy + 300 >= bonusY + y2 - 30 && shipy + 300 <= bonusY + y2 + 30 && x2 == -2095){
		acq++;
		if (acq == 3)
			win = true;
		else
			obx -= 0.03;
	}
	switch(met){
	case 0:
		if (shipy + 300 >= meteorY + y - 40 && shipy + 300 <= meteorY + y + 50 && x == -1925  ){
			hits++;
			if (hits == 3)
				lose = true;
			else
				obx += 0.03;
		}
		break;
	case 1:
		if (shipy + 300 >= meteorY + y - 35 && shipy + 300 <= meteorY + y + 40 && x == -1925 ){
			hits++;
			if (hits == 3)
				lose = true;
			else
				obx += 0.03;
		} break;
	case 2:
		if (shipy + 300 >= meteorY + y - 50 && shipy + 300 <= meteorY + y + 90 && x == -1925){
			hits++;
			if (hits == 3)
				lose = true;
			else
				obx += 0.03;
				
			
		} 
		break;
	}

	glutPostRedisplay();


}

int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	res[1] = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
	return res;
}



void Keyboard(unsigned char key, int x, int y) {
	if (key == GLUT_KEY_ESCAPE)
		exit(EXIT_SUCCESS);
}
void Key(unsigned char key, int x, int y) {
	if (key == 'w' && shipy < 260){
		shipy += 5;
	}
	if (key == 's' && shipy > -260){
		shipy -= 5;
	}
}
void print(int x, int y, char *string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void drawCircle(int i, int j, float r) {
	glTranslatef(i, j, 0);
	GLUquadric *quadObj = gluNewQuadric();
	gluDisk(quadObj, 0, r, 50, 50);
}
void Timer(int value) {
	// set the ball's Y coordinate to a random number between 10 and 780 (since the window's height is 800)
	meteorY = rand() % (500+1-230) + 230;
	met = rand() % 3;
	x = 0;  y = 0; i = 0.0;
	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	// recall the Timer function after 20 seconds (20,000 milliseconds)
	glutTimerFunc(9.5 * 1000, Timer, 0);
}

void Timer1(int value) {
	// set the ball's Y coordinate to a random number between 10 and 780 (since the window's height is 800)
	bonusY = rand() % (370 + 1 - 150) + 150;
	x2 = 0;  y2 = 0; i2 = 0.0; hit = false;
	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();

	// recall the Timer function after 20 seconds (20,000 milliseconds)
	glutTimerFunc(25 * 1000, Timer1, 0);
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);


	glutInitWindowSize(2300, 600);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Star Wars");
	glutDisplayFunc(Display);
	glutIdleFunc(Anim);
	glutKeyboardFunc(Key);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glutTimerFunc(0, Timer, 0);
	glutTimerFunc(0, Timer1, 0);

	glEnable(GL_TEXTURE_2D);

	gluOrtho2D(0, 2300, 0, 600);



	loadBMP(&texID, "textures/space.bmp", true);
	loadBMP(&ship, "textures/metal.bmp", true);
	loadBMP(&blackhole, "textures/blackhole.bmp", true);
	loadBMP(&red, "textures/red.bmp", true);
	loadBMP(&water, "textures/water.bmp", true);
	loadBMP(&meteor, "textures/meteor.bmp", true);
	loadBMP(&white, "textures/white.bmp", true);
	//loadPPM(&texID, "textures/clouds.ppm", 200, 200, true);

	glutMainLoop();
}
void drawRect(int x, int y, int w, int h) {
	glBegin(GL_QUADS);
	glVertex3f(x, y, 0.0f);
	glVertex3f(w, y, 0.0f);
	glVertex3f(w, h, 0.0f);
	glVertex3f(x, h, 0.0f);
	glEnd();
}