#include <GL/glut.h>
#include <GL/glu.h>
#include "skate.h"

void skate(GLUquadricObj *qobj) {
  // Prancha
  glPushMatrix();
  glColor3ub(192, 192, 192);
  //glRotatef(20, 1.0f, 0.0f, 0.0f);
  glTranslatef(-0.20f, 0.0f, -1.26f);
  glScalef(0.5f, 1.5f, 0.07f);
  gluSphere(qobj, 0.5, 50, 50);
  glPopMatrix();
}
