/* Arquivo: skate.cpp
   Autores: João Pedro Winckler Bernardi e Vladimir Belinski
   Descrição: o presente arquivo faz parte da resolução do Trabalho I do CCR Computação Gráfica, 2016-2, do curso de
              Ciência da Computação da Universidade Federal da Fronteira Sul - UFFS, o qual consiste em uma animação
              do símbolo do SO Android (robô) andando de skate.
              --> skate.cpp é o arquivo responsável pela definição das primitivas gráficas que comporão o skate, assim
              como a movimentação de suas rodas.
*/

// Inclusão das bibliotecas necessárias
#include <GL/glut.h>
#include <GL/glu.h>
#include "skate.h"

// Variável que será utilizada na movimentação das rodas do skate
GLfloat alpha_wheels = 0.0f;

// A função skate é responsável pelo desenho do skate na cena
void skate(GLUquadricObj *qobj) {
  // Especificação da cor da prancha e guias
  glColor3ub(192, 192, 192);

  // Prancha
  glPushMatrix();
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

  // Especificação da cor das rodas
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
