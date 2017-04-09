//
//  main.cpp
//  CSE418_Assnt04
//
//  Created by Piash on 3/22/17.
//  Copyright © 2017 Maacintush. All rights reserved.
//

#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
using namespace std;

struct Point { int x; int y; int z; };
struct Slope { int x; int y; int z; };

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void writePixel(Point P)
{
    glBegin(GL_POINTS);
    glVertex3i(P.x, P.y, P.z);
    glEnd();
}

/* GLUT callback Handlers */

int x1, y1, z1, x4, y4, z4, r1x, r1y, r1z, r4x, r4y, r4z;

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    glOrtho(-width/2, width/2, -height/2, height/2, -300, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static Point Q(double t)
{
    Point pt;
    
    pt.x = (int) ((2 * t * t * t - 3 * t *  t + 1) * x1 + (3 * t * t - 2 * t * t * t) * x4
    + (t * t * t - 2 * t * t + t) * r1x + (t * t * t - t * t) * r4x);
    
    pt.y = (int) ((2 * t * t * t - 3 * t *t + 1) * y1 + (3 * t * t - 2 * t * t * t) * y4
    + (t * t * t - 2 * t * t + t) * r1y + (t * t * t - t * t) * r4y);
    
    pt.z = (int) ((2 * t * t * t - 3 * t * t + 1) * z1 + (3 * t * t - 2 * t * t * t) * z4
    + (t * t * t - 2 * t * t + t) * r1z + (t * t * t - t * t) * r4z);
    
    return pt;
}

static void drawCurve()
{
    double t = 0;
    while (t <= 1)
    {
        writePixel(Q(t));
        glFlush();
        t += 0.01;
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(0,0,1);
    
    double seconds = glutGet(GLUT_ELAPSED_TIME) / 100;
    double dps = seconds * 1.5;
    
    glPushMatrix();
    
    glRotated(30, 1, 0, 0);
    glRotated(dps,0,0,1);
    drawCurve();
    glPopMatrix();
    
    glutSwapBuffers();
}



static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
    }
    
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
    cout << "Enter Point 1 (x1, y1, z1) : ";
    cin >> x1 >> y1 >> z1;
    cout << "Enter Point 4 (x4, y4, z4) : ";
    cin >> x4 >> y4 >> z4;
    cout << "Enter slope of Point 1 (r1x, r1y, r1z) : ";
    cin >> r1x >> r1y >> r1z;
    cout << "Enter slope of Point 4 (r4x, r4y, r4z) : ";
    cin >> r4x >> r4y >> r4z;
    
    
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    
    glutCreateWindow("GLUT Shapes");
    
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    
    glClearColor(0,0,0,0);
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}
