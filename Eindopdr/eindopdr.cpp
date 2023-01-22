#include <GLUT/glut.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//variables for the verticis
const GLfloat X = .525731112119133606;
const GLfloat Z = .850650808352039932;
//variables for the camera
float cameraAngle = 0.0;
float lx = 0.0f, lz = -1.0f;
float x=0.0f, z=1.0f;
//verticis data
static GLfloat vdata[12][3] = {
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};
//triangle indices
static GLuint tindices[20][3] = {
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11}
};
//attempt at textures
static GLfloat textureCoords[3][2] = {
    {0.0f, 0.0f},  // lower-left corner  
    {1.0f, 0.0f},  // lower-right corner
    {0.5f, 1.0f}   // top-center corner
};
static GLfloat borderColor[4] = { 1.0f, 1.0f, 0.0f, 1.0f };

float angle = 0.0;

//function that rotates the icosahedron a random amount between 1 and 360 degrees
void keyPressed (unsigned char key, int x, int y){
    if (key == 'a')
    {
        for (int i = 0; i < rand() % 360 + 1; i++)
        {
            angle++;
        }
        
        // angle += rand() % 360 + 1;
    }
    
}

//function for moving the camera forward, backward, left and right.
void specialKeys(int key, int xx, int yy){
    float fraction = 0.1f;

    switch (key) {
        case GLUT_KEY_LEFT :
			cameraAngle -= 0.01f;
			lx = sin(cameraAngle);
			lz = -cos(cameraAngle);
			break;
		case GLUT_KEY_RIGHT :
			cameraAngle += 0.01f;
			lx = sin(cameraAngle);
			lz = -cos(cameraAngle);
			break;
		case GLUT_KEY_UP :
			x += lx * fraction;
			z += lz * fraction;
			break;
		case GLUT_KEY_DOWN :
			x -= lx * fraction;
			z -= lz * fraction;
			break;
	}
}

void spin() {
    angle += 1;
    glutPostRedisplay();
}

void input(unsigned char key, int x, int y){
    if(key == 37){
        angle += 10;
    }
    if(key == 39){
        angle -= 10;
    }
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);
    gluLookAt(
        x, 1.0f, z,
        x+lx, 1.0f, z+lz,
        0.0f, 1.0f, 0.0f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(30.0 + angle, 1.0, 1.0, 0.0); // rotate icosahedron by 30 degrees around the (1,1,0) axis
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 20; i++) {
        glColor3f(1,0,0);
        glNormal3fv(&vdata[tindices[i][0]][0]);
        glVertex3fv(&vdata[tindices[i][0]][0]);
        glColor3f(0,1,0);
        glNormal3fv(&vdata[tindices[i][1]][0]);
        glVertex3fv(&vdata[tindices[i][1]][0]);
        glColor3f(0,0,1);
        glNormal3fv(&vdata[tindices[i][2]][0]);
        glVertex3fv(&vdata[tindices[i][2]][0]);
        
    }
    glEnd();
    glPopMatrix();

    glFlush();
}

void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Icosahedron");
     glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressed);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(spin);
    glutMainLoop();
    
    return 0;
}
//TODO:
//point of view 
//pavement background
//rotate dice faster randomly and stop on a face after user input
//add numbers to dice faces
//g++ eindopdr.cpp -framework GLUT -framework OpenGL -Wno-deprecated --std=c++11