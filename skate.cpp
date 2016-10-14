#include <GL/glut.h>
#include <GL/glu.h>
#include "skate.h"

void skate(GLUquadricObj *qobj) {
  // Prancha
  glPushMatrix();
  //glRotatef(20, 1.0f, 0.0f, 0.0f);
  glTranslatef(0.0f, 0.0f, -1.25f);
  glScalef(0.7f, 1.9f, 0.07f);
  gluSphere(qobj, 0.5, 50, 50);
  glPopMatrix();
}
