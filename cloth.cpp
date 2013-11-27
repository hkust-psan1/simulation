#include <GLUT/GLUT.h>

#include "cloth.h"

const Vec3 Particle::gravity = Vec3(0, -0.01, 0);

Particle::Particle(const Vec3& p, double r, Gel* c)
: pos(p), radius(r), parent(c), mass(1), atBottom(false) {
}

void Particle::updateForce() {
    force += gravity;
    
    force += speed * -0.1;
}

void Particle::updatePos(double deltaT) {
    speed += force / mass * deltaT;
    
    if (parent->still && atBottom) {
        speed.y = 0;
    }
    
    pos += speed * deltaT;
}

Spring::Spring(Particle* p1, Particle* p2) {
    this->p1 = p1;
    this->p2 = p2;
    
    p1->addSpring(this);
    p2->addSpring(this);
    
    origLength = (p1->pos - p2->pos).length();
    
    broken = false;
}

Spring::~Spring() {
}

void Spring::update() {
    double lengthDiff = (p1->pos - p2->pos).length() - origLength;
    
    /*
    if (lengthDiff > 0.05) {
        broken = true;
    }
    */
    
    if (!broken) {
        p1->addForce(k * lengthDiff * (p2->pos - p1->pos));
        p2->addForce(k * lengthDiff * (p1->pos - p2->pos));
    }
}

vector<Particle*> Gel::allParticles;

Gel::Gel(int s, double sc, double l, const Vec3& c) : size(s), springCoeff(sc), length(l), center(c), still(false) {
    gridLength = l / size;
    
    displayParticles = new Particle***[size];
    
    for (int i = 0; i < size; i++) {
        displayParticles[i] = new Particle**[size];
        
        for (int j = 0; j < size; j++) {
            displayParticles[i][j] = new Particle*[size];
            
            for (int k = 0; k < size; k++) {
                Particle* p = new Particle(Vec3(c.x - 0.5 * length + gridLength * i,
                                                c.y - 0.5 * length + gridLength * j,
                                                c.z - 0.5 * length + gridLength * k), 0.01, this);
                
                // indexParticleMap.insert(pair<IndexTri, Particle*>(IndexTri(i, j, k), p));
                
                if (j == 0) {
                    p->atBottom = true;
                }
                
                displayParticles[i][j][k] = p;
                
                particles.push_back(p);
                allParticles.push_back(p);
                /*
                if (i == 0 && j < size - 1 && k < size - 1) {
                    GelFace* face = new GelFace;
                    face->addParticle(p);
                }
                */
            }
        }
    }
    
    for (Particle* p : particles) {
        for (Particle* q : particles) {
            if (p != q && (p->pos - q->pos).length() < 2.1 * gridLength) {
                Spring* s = new Spring(p, q);
                s->k = springCoeff;
                springs.push_back(s);
            }
        }
    }
}

Gel::~Gel() {
    
}

void Gel::simulate() {
    for (Particle* p : particles) {
        p->updateForce();
    }
    
    for (Spring* s : springs) {
        s->update();
    }
    
    for (Particle* p : particles) {
        p->updatePos(0.05);
    }
}

void Gel::clearState() {
    for (Particle* p : particles) {
        p->force.x = 0;
        p->force.y = 0;
        p->force.z = 0;
    }
}

void Gel::draw() {
    glBegin(GL_QUADS);
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            Vec3 p0 = displayParticles[0][i][j]->pos;
            Vec3 p1 = displayParticles[0][i + 1][j]->pos;
            Vec3 p2 = displayParticles[0][i + 1][j + 1]->pos;
            Vec3 p3 = displayParticles[0][i][j + 1]->pos;
            glVertex3d(p3.x, p3.y, p3.z);
            glVertex3d(p2.x, p2.y, p2.z);
            glVertex3d(p1.x, p1.y, p1.z);
            glVertex3d(p0.x, p0.y, p0.z);
        }
    }
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            Vec3 p0 = displayParticles[size - 1][i][j]->pos;
            Vec3 p1 = displayParticles[size - 1][i + 1][j]->pos;
            Vec3 p2 = displayParticles[size - 1][i + 1][j + 1]->pos;
            Vec3 p3 = displayParticles[size - 1][i][j + 1]->pos;
            glVertex3d(p0.x, p0.y, p0.z);
            glVertex3d(p1.x, p1.y, p1.z);
            glVertex3d(p2.x, p2.y, p2.z);
            glVertex3d(p3.x, p3.y, p3.z);
        }
    }
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            Vec3 p0 = displayParticles[i][0][j]->pos;
            Vec3 p1 = displayParticles[i + 1][0][j]->pos;
            Vec3 p2 = displayParticles[i + 1][0][j + 1]->pos;
            Vec3 p3 = displayParticles[i][0][j + 1]->pos;
            glVertex3d(p0.x, p0.y, p0.z);
            glVertex3d(p1.x, p1.y, p1.z);
            glVertex3d(p2.x, p2.y, p2.z);
            glVertex3d(p3.x, p3.y, p3.z);
        }
    }
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            Vec3 p0 = displayParticles[i][size - 1][j]->pos;
            Vec3 p1 = displayParticles[i + 1][size - 1][j]->pos;
            Vec3 p2 = displayParticles[i + 1][size - 1][j + 1]->pos;
            Vec3 p3 = displayParticles[i][size - 1][j + 1]->pos;
            glVertex3d(p3.x, p3.y, p3.z);
            glVertex3d(p2.x, p2.y, p2.z);
            glVertex3d(p1.x, p1.y, p1.z);
            glVertex3d(p0.x, p0.y, p0.z);
        }
    }
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            Vec3 p0 = displayParticles[i][j][0]->pos;
            Vec3 p1 = displayParticles[i + 1][j][0]->pos;
            Vec3 p2 = displayParticles[i + 1][j + 1][0]->pos;
            Vec3 p3 = displayParticles[i][j + 1][0]->pos;
            glVertex3d(p3.x, p3.y, p3.z);
            glVertex3d(p2.x, p2.y, p2.z);
            glVertex3d(p1.x, p1.y, p1.z);
            glVertex3d(p0.x, p0.y, p0.z);
        }
    }
    
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            Vec3 p0 = displayParticles[i][j][size - 1]->pos;
            Vec3 p1 = displayParticles[i + 1][j][size - 1]->pos;
            Vec3 p2 = displayParticles[i + 1][j + 1][size - 1]->pos;
            Vec3 p3 = displayParticles[i][j + 1][size - 1]->pos;
            glVertex3d(p0.x, p0.y, p0.z);
            glVertex3d(p1.x, p1.y, p1.z);
            glVertex3d(p2.x, p2.y, p2.z);
            glVertex3d(p3.x, p3.y, p3.z);
        }
    }
    glEnd();

}

vector<IndexTri> Gel::getNeighbors(int i, int j, int k) {
    vector<IndexTri> neighbors;
    
    for (int ii = i - 2; ii <= i + 2; ii++) {
        for (int jj = j - 2; jj <= j + 2; jj++) {
            for (int kk = k - 2; kk <= k + 2; kk++) {
                if (ii >= 0 && ii < size && jj >= 0 && jj < size && kk >= 0 && kk < size &&
                        (ii != i || jj != j || kk != k)) {
                    neighbors.push_back({ ii, jj, kk });
                }
            }
        }
    }
    return neighbors;
}