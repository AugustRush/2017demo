//
//  main.cpp
//
//  Created by Adrian Russell on 9/18/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include <iostream>

#include "PhysicsDemo.h"
#include "BlackHoleDemo.h"
#include "BallCollision.h"
#include "CirclePlink.h"
#include "PolygonPlink.h"
#include "HillRoll.h"
#include "Cloth.h"
#include "NewtonsCradle.h"
#include "Pyramid.h"
#include "MoveableSprite.h"
#include "SoftBody.h"
#include "WreckingBall.h"
#include "Restitution.h"
#include "Friction.h"
#include "Beam.h"
#include "Flag.h"
#include "ClothWithBalls.h"

#include "Drawing.h"

#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include <GLUT/glut.h>

#include "Physics_Utilities.h"

#define FPS 60
#define SLEEP_TICKS (1000 / FPS)

#define FRAME_WIDTH  (GLfloat)640.0
#define FRAME_HEIGHT (GLfloat)480.0

#define FRAME_TRANSLATE_X 0.5f
#define FRAME_TRANSLATE_Y 0.5f

static GLfloat scale       = 1.0;

static Vector2 screenMousePosition = Vector2();
static Vector2 worldMousePosition  = Vector2();

//static float squareRot = 0.0;

#define NUMBER_OF_DEMOS 15
static PhysicsDemo *demo = NULL;


static std::string location;

PhysicsDemo *demoForIndex(unsigned int index)
{
    PhysicsDemo *demo = NULL;
    if (index < NUMBER_OF_DEMOS) {
        switch (index) {
            case 0:
                demo = new BlackHoleDemo();
                break;
            case 1:
                demo = new Restitution();
                break;
            case 2:
                demo = new Friction();
                break;
            case 3:
                demo = new NewtonsCradle();
                break;
            case 4:
                demo = new WreckingBall();
                break;
            case 5:
                demo = new HillRoll();
                break;
            case 6:
                demo = new MoveableSprite();
                break;
            case 7:
                demo = new Cloth();
                break;
            case 8:
                demo = new Flag();
                break;
            case 9:
                demo = new SoftBody();
                break;
            case 10:
                demo = new Pyramid();
                break;
            case 11:
                demo = new BallCollision();
                break;
            case 12:
                demo = new CirclePlink();
                break;
            case 13:
                demo = new PolygonPlink();
                break;
            case 14:
                demo = new ClothWithBalls();
                break;
            default:
                break;
        }
    }
    return demo;
}



void timercall(int value)
{
	glutTimerFunc(SLEEP_TICKS, timercall, 0);
    
	glutPostRedisplay();
}

void reshape(int width, int height)
{
	printf("window resized to %d, %d\n", width, height);
    
    glViewport(0, 0, width, height);
	
	double scale = MIN((width / demo->world->getWidth()), (height / demo->world->getHeight()));
	double hw = width  * (0.5 / scale);
	double hh = height * (0.5 / scale);
	
    printf("hw = %f, hh = %f", hw, hh);
    
    
	glLineWidth(1);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glTranslated(-1.0, -1.0, 0.0);
	glOrtho(-hw, hw, -hh, hh, -1.0, 1.0);
}


Vector2 mousePointForWorld(int x, int y)
{
    GLdouble model[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	
	GLdouble proj[16];
	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	
	GLint view[4];
	glGetIntegerv(GL_VIEWPORT, view);
	
	GLdouble mx, my, mz;
	gluUnProject(x, glutGet(GLUT_WINDOW_HEIGHT) - y, 0.0f, model, proj, view, &mx, &my, &mz);
	
	return Vector2(mx, my);
}



void display(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glTranslatef(FRAME_TRANSLATE_X, FRAME_TRANSLATE_Y, 0.0);
    glScalef(scale, scale, 1.0);
    
    //playPopSound();
    
    demo->update(1.0 / 60.0);
    
    glPushMatrix();
    {
        demo->draw();
    }
    glPopMatrix();
    
    
    // draw text
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    glOrtho( 0, w, 0, h, -1, 1 );
        
    // draw string showing mouse co-ordinates
    char string[255];
    snprintf(string, 255, "world: {%.2f, %.2f}\nscreen: {%.2f, %.2f}", worldMousePosition.x, worldMousePosition.y, screenMousePosition.x, screenMousePosition.y);
    //drawString(10, 20, string);
    glPopMatrix();
    
	glutSwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);
}


void mouse(int x, int y)
{
	screenMousePosition = Vector2((float)x, (float)y);
    worldMousePosition = mousePointForWorld(x, y);
    
    if (demo) {
        demo->mouseMoved(worldMousePosition.x, worldMousePosition.y);
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key >= 'a' && key < ('a' + NUMBER_OF_DEMOS)) {
        
        if (demo) {
            delete demo;
            demo = NULL;
        }
        demo = demoForIndex(key - 'a');
        std::string title = "(a) " + demo->name();
        title[1] = key;
        glutSetWindowTitle(title.c_str());
        reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    } else {
        if (demo) {
            demo->keyPressed(key, x, y);
        }
    }
    
    std::cout << "key " << key << std::endl;
}

void keyboardSpecial(int key, int x, int y)
{
    if (demo) {
        demo->keyPressed(key, x, y);
    }
        std::cout << "key " << key << std::endl;
}


void mousePress(int button, int state, int x, int y)
{
    if (demo) {
        Vector2 worldPos = mousePointForWorld(x, y);
        demo->mouseEvent(button, state, (int)worldPos.x, (int)worldPos.y);
    }
}

void initGL(void)
{
	glClearColor(52.0/255.0, 62.0/255.0, 72.0/255.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
    
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

#if !defined(GLUT_WINDOW_SCALE)
#	define GLUT_WINDOW_SCALE 199
#endif


void glutStuff(int argc, const char *argv[])
{
	glutInit(&argc, (char**)argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
    
	glutInitWindowSize(FRAME_WIDTH, FRAME_HEIGHT);
    
    glutCreateWindow("ARPhysics Testing");
    
    initGL();
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(SLEEP_TICKS, timercall, 0);
	glutMotionFunc(mouse);
	glutPassiveMotionFunc(mouse);
    glutMouseFunc(mousePress);
    glutKeyboardFunc(keyboard);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_DEFAULT);
    glutSpecialFunc(keyboardSpecial);
}

int main(int argc, const char * argv[])
{
    demo = demoForIndex(6);
    
    glutStuff(argc, argv);
    
    glutSetWindowTitle(demo->name().c_str());
    
    glutMainLoop();
    
    return 0;
}



