#include <iostream>
#include <GLUT/GLUT.h>

#include "parser.h"
#include "particle.h"
#include "spring.h"
#include "cloth.h"

Scene* scene;

Gel* gel;
Gel* fallGel;
Gel* fallGel2;

vector<Particle*> particles;

double xPos = 1;
double zPos = 2;

void keypressed(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            zPos -= 0.05;
            break;
        case 's':
            zPos += 0.05;
            break;
        case 'a':
            xPos += 0.05;
            break;
        case 'd':
            xPos -= 0.05;
            break;
        case 'e':
            break;
            
        default:
            break;
    }
}

void simulate() {
    fallGel->clearState();
    fallGel2->clearState();
    gel->clearState();
    
    for (Particle* p : gel->particles) {
        for (Particle* q : fallGel->particles) {
            Vec3 dis = p->pos - q->pos;
            if (dis.length() < 0.1) { // two particles close enough
                p->addForce(dis * dis.length() * 20);
                q->addForce(dis * dis.length() * -20);
            }
        }
    }
    
    for (Particle* p : gel->particles) {
        for (Particle* q : fallGel2->particles) {
            Vec3 dis = p->pos - q->pos;
            if (dis.length() < 0.1) { // two particles close enough
                p->addForce(dis * dis.length() * 20);
                q->addForce(dis * dis.length() * -20);
            }
        }
    }
    
    gel->simulate();
    fallGel->simulate();
    fallGel2->simulate();
}

void display() {
    simulate();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, 1.33, 0.1, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xPos, 3.0, zPos,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    
    glLineWidth(1);
    glPointSize(3);
    
    glColor3d(1, 1, 0);
    glBegin(GL_POINTS);
    glVertex3d(0, 2, 1);
    glEnd();
    
    
    GLfloat diffuseMat3[] = { 0.8f, 0.3f, 0.6f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat3);
    gel->draw();
    
    // glColor3d(0, 1, 1);
    GLfloat diffuseMat1[] = { 0.0f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat1);
    fallGel->draw();
    
    GLfloat diffuseMat2[] = { 0.5f, 0.8f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat2);
    fallGel2->draw();

    
    glutSwapBuffers();
    glutPostRedisplay();

}

int main(int argc, char * argv[]) {
    // Parser* parser = new Parser;
    // scene = parser->parseFile("/Users/guanlunzhao/Workspace/Models/cube.obj");
    
    gel = new Gel(10, 1, Vec3(0, 0, 0));
    gel->still = true;
    fallGel = new Gel(5, 0.5, Vec3(0.5, 2, 0.5));
    fallGel2 = new Gel(5, 0.5, Vec3(-0.5, 1, 0));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Hello World");
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    
    glShadeModel(GL_FLAT);
    
    GLfloat lightPos[] = { 0.0f, 2.0f, 1.0f, 10.0f };
    GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseColor[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    // glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);

    glutDisplayFunc(display);
    glutKeyboardFunc(keypressed);
    
    glutMainLoop();
    
    return 0;
}

