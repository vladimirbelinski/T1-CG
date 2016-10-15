#include <GL/glut.h>
#include <GL/glu.h>
#include "skate.h"

GLfloat alpha_wheels = 0.0f;

void skate(GLUquadricObj *qobj) {
  // Prancha
  glPushMatrix();
  glColor3ub(192, 192, 192);
  glTranslatef(-0.20f, 0.0f, -1.26f);
  glScalef(0.5f, 1.5f, 0.07f);
  gluSphere(qobj, 0.5, 50, 50);
  glPopMatrix();

  // Guia dianteira
  glPushMatrix();
  glTranslatef(-0.36f, 0.3f, -1.35f);
  glRotatef(90, 0.0f, 1.0f, 0.0f);
  gluCylinder(qobj, 0.03, 0.03, 0.32, 200, 200);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.26f, 0.3f, -1.33f);
  glRotatef(90, 0.0f, 1.0f, 0.0f);
  gluCylinder(qobj, 0.03, 0.03, 0.11, 200, 200);
  glPopMatrix();

  // Guia traseira
  glPushMatrix();
  glTranslatef(-0.36f, -0.3f, -1.35f);
  glRotatef(90, 0.0f, 1.0f, 0.0f);
  gluCylinder(qobj, 0.03, 0.03, 0.32, 200, 200);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.26f, -0.3f, -1.33f);
  glRotatef(90, 0.0f, 1.0f, 0.0f);
  gluCylinder(qobj, 0.03, 0.03, 0.11, 200, 200);
  glPopMatrix();

  glColor3ub(42, 42, 42);

  // Roda esquerda dianteira
  glPushMatrix();
  glTranslatef(-0.08f, 0.3f, -1.35f);
  glRotatef(alpha_wheels += 3.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(90, 0.0f, 1.0f, 0.0f);
  glutSolidTorus(0.03, 0.04, 30, 30);
  glPopMatrix();

  // Roda direita dianteira
  glPushMatrix();
  glTranslatef(-0.32f, 0.3f, -1.35f);
  glRotatef(alpha_wheels += 3.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(90, 0.0f, 1.0f, 0.0f);
  glutSolidTorus(0.03, 0.04, 30, 30);
  glPopMatrix();

  // Roda esquerda traseira
  glPushMatrix();
  glTranslatef(-0.08f, -0.3f, -1.35f);
  glRotatef(alpha_wheels += 3.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(90, 0.0f, 1.0f, 0.0f);
  glutSolidTorus(0.03, 0.04, 30, 30);
  glPopMatrix();

  // Roda direita traseira
  glPushMatrix();
  glTranslatef(-0.32f, -0.3f, -1.35f);
  glRotatef(alpha_wheels += 3.0f, 1.0f, 0.0f, 0.0f);
  glRotatef(90, 0.0f, 1.0f, 0.0f);
  glutSolidTorus(0.03, 0.04, 30, 30);
  glPopMatrix();
}
