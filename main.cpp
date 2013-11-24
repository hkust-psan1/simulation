#include <iostream>
#include <GLUT/GLUT.h>

#include "parser.h"
#include "cloth.h"

Scene* scene;

Cloth* cloth;
Gel* gel;

double xPos = 1;
double zPos = 5;

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
    for (Object* obj : scene->getObjects()) {
        
    }
}

void display() {
    // cloth->simulate();
    // gel->simulate();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, 1.33, 0.1, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xPos, 1.0, zPos,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    
    glColor3d(1, 0.3, 0.7);
    glLineWidth(1);
    
    Object* obj = scene->getObjects()[0];
    
    glBegin(GL_POINTS);
    for (Particle* p : obj->particles) {
        // glColor3d(p->pos.x, p->pos.y, p->pos.z);
        glVertex3d(p->pos.x, p->pos.y, p->pos.z);
    }
    glEnd();
    
    /*
    for (int i = 0; i < gel->size - 1; i++) {
        for (int j = 0; j < gel->size - 1; j++) {
            for (int k = 0; k < gel->size - 1; k++) {
                Vec3 v1 = gel->vertices[i][j][k];
                Vec3 v2 = gel->vertices[i][j + 1][k];
                Vec3 v3 = gel->vertices[i + 1][j + 1][k];
                Vec3 v4 = gel->vertices[i + 1][j][k];
                Vec3 v5 = gel->vertices[i][j][k + 1];
                Vec3 v6 = gel->vertices[i][j + 1][k + 1];
                Vec3 v7 = gel->vertices[i + 1][j + 1][k + 1];
                Vec3 v8 = gel->vertices[i + 1][j][k + 1];
                glBegin(GL_LINES);
                glVertex3d(v1.x, v1.y, v1.z);
                glVertex3d(v2.x, v2.y, v2.z);
                
                glVertex3d(v1.x, v1.y, v1.z);
                glVertex3d(v4.x, v4.y, v4.z);
                
                glVertex3d(v3.x, v3.y, v3.z);
                glVertex3d(v2.x, v2.y, v2.z);
                
                glVertex3d(v3.x, v3.y, v3.z);
                glVertex3d(v4.x, v4.y, v4.z);
                
                glVertex3d(v1.x, v1.y, v1.z);
                glVertex3d(v5.x, v5.y, v5.z);
                
                glVertex3d(v2.x, v2.y, v2.z);
                glVertex3d(v6.x, v6.y, v6.z);
                
                glVertex3d(v3.x, v3.y, v3.z);
                glVertex3d(v7.x, v7.y, v7.z);
                
                glVertex3d(v4.x, v4.y, v4.z);
                glVertex3d(v8.x, v8.y, v8.z);
                
                glVertex3d(v6.x, v6.y, v6.z);
                glVertex3d(v5.x, v5.y, v5.z);
                
                glVertex3d(v7.x, v7.y, v7.z);
                glVertex3d(v6.x, v6.y, v6.z);
                
                glVertex3d(v8.x, v8.y, v8.z);
                glVertex3d(v7.x, v7.y, v7.z);
                
                glVertex3d(v5.x, v5.y, v5.z);
                glVertex3d(v8.x, v8.y, v8.z);
                
                glEnd();
            }
        }
    }
    */
    
    /*
    for (int i = 0; i < cloth->size - 1; i++) {
        for (int j = 0; j < cloth->size - 1; j++) {
            Vec3 v1 = cloth->vertices[i][j];
            Vec3 v2 = cloth->vertices[i][j + 1];
            Vec3 v3 = cloth->vertices[i + 1][j + 1];
            Vec3 v4 = cloth->vertices[i + 1][j];
            glBegin(GL_LINE_LOOP);
            glVertex3d(v1.x, v1.y, v1.z);
            glVertex3d(v2.x, v2.y, v2.z);
            glVertex3d(v3.x, v3.y, v3.z);
            glVertex3d(v4.x, v4.y, v4.z);
            glEnd();
        }
    }
     */
    
    /*
    for (Object* obj : scene->getObjects()) {
        glColor3d(obj->mat->kd[0], obj->mat->kd[1], obj->mat->kd[2]);
        for (Face* f : obj->getFaces()) {
            glBegin(GL_TRIANGLES);
            glVertex3d(f->vertices[0]->pos.x, f->vertices[0]->pos.y, f->vertices[0]->pos.z);
            glVertex3d(f->vertices[1]->pos.x, f->vertices[1]->pos.y, f->vertices[1]->pos.z);
            glVertex3d(f->vertices[2]->pos.x, f->vertices[2]->pos.y, f->vertices[2]->pos.z);
            glEnd();
        }
    }
    */
    
    glutSwapBuffers();
    glutPostRedisplay();

}

int main(int argc, char * argv[]) {
    Parser* parser = new Parser;
    scene = parser->parseFile("/Users/guanlunzhao/Workspace/Models/cube.obj");
    
    // cloth = new Cloth(30);
    gel = new Gel(10);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Hello World");

    glutDisplayFunc(display);
    glutKeyboardFunc(keypressed);
    
    glutMainLoop();
    
    return 0;
}

