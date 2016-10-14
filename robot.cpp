#include "misc.h"
#include "robot.h"

void head(GLUquadricObj *qobj){
  // Definindo a cor corrente como branco
  glColor3f(1.0f, 1.0f, 1.0f);

  // Cilindro que forma o pescoço do robô
  glPushMatrix();
  gluCylinder(qobj, 0.45, 0.45, 0.08, 200, 200);
  glPopMatrix();

  // Olho direito
  glPushMatrix();
  glTranslatef(-0.23f, 0.35f, 0.24f);
  gluSphere(qobj, 0.07, 100, 100);
  glPopMatrix();

  // Olho esquerdo
  glPushMatrix();
  glTranslatef(0.23f, 0.35f, 0.24f);
  gluSphere(qobj, 0.07, 100, 100);
  glPopMatrix();

  // Definindo a cor corrente como verde
  glColor3ub(164, 199, 57);

  // Antena direita do robô
  glPushMatrix();
  glTranslatef(-0.2f, 0.0f, 0.5f);
  glRotatef(-45, 0.0f, 1.0f, 0.0f);
  gluCylinder(qobj, 0.02, 0.02, 0.17, 100, 100);
  glPopMatrix();

  // Meia esfera que irá compor a topo da antena direita do robô
  glPushMatrix();
  glTranslatef(-0.32f, 0.0f, 0.62);
  glRotatef(-45, 0.0f, 1.0f, 0.0f);
  meiaEsfera(0.02, 100, 4);
  glPopMatrix();

  // Antena esquerda do robô
  glPushMatrix();
  glTranslatef(0.2f, 0.0f, 0.5f);
  glRotatef(45, 0.0f, 1.0f, 0.0f);
  gluCylinder(qobj, 0.02, 0.02, 0.17, 100, 100);
  glPopMatrix();

  // Meia esfera que irá compor a topo da antena esquerda do robô
  glPushMatrix();
  glTranslatef(0.32f, 0.0f, 0.62);
  glRotatef(45, 0.0f, 1.0f, 0.0f);
  meiaEsfera(0.02, 100, 4);
  glPopMatrix();

  // Meia esfera que irá compor a cabeça do robô
  glPushMatrix();
  glTranslatef (0.0f, 0.0f, 0.07f);
  meiaEsfera(0.5, 100, 4);
  glPopMatrix();

  // Disco que fecha a meia esfera que forma a cabeça do robô
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 0.07f);
  // Rotacionado para funcionar a iluminação (devido a posição do vetor normal)
  glRotatef(180, 1.0f, 0.0f, 0.0);
  gluDisk(qobj, 0.45, 0.503, 30, 30);
  glPopMatrix();
}

void body(GLUquadricObj *qobj){
  // Definindo a cor corrente como verde
  glColor3ub(164, 199, 57);

  // Disco que fecha a parte superior do cilindro que forma o tronco do robô
  glPushMatrix();
  gluDisk(qobj, 0.45, 0.503, 30, 30);
  glPopMatrix();

  // Cilindro que forma o tronco do robô
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -0.75f);
  gluCylinder(qobj, 0.5, 0.5, 0.75, 200, 200);
  glPopMatrix();

  // Meia esfera que fecha a parte inferior do cilindro que forma o tronco do robô
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -0.75f);
  glRotatef(180, 1.0f, 0.0f, 0.0f);
  meiaEsfera(0.5, 100, 27);
  glPopMatrix();

  // Disco que fecha a base do tronco
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -0.85f);
  // Rotacionado para funcionar a iluminação (devido a posição do vetor normal)
  glRotatef(180, 1.0f, 0.0f, 0.0);
  gluDisk(qobj, 0.0, 0.49, 30, 30);
  glPopMatrix();
}

void rightArm(GLUquadricObj *qobj){
  // Definindo a cor corrente como branco
  glColor3f(1.0f, 1.0f, 1.0f);

  // Cilindro que junta o braço direito do robô ao tronco
  glPushMatrix();
  glTranslatef(-0.65f, 0.0f, -0.1f);
  glRotatef(90, 0.0f, 1.0f, 0.0f);
  gluCylinder(qobj, 0.05, 0.05, 0.2, 100, 100);
  glPopMatrix();

  // Definindo a cor corrente como verde
  glColor3ub(164, 199, 57);

  // Braço direito do robô
  glPushMatrix();
  glTranslatef(-0.63f, 0.0f, -0.55f);
  gluCylinder(qobj, 0.09, 0.09, 0.45, 100, 100);
  glPopMatrix();

  // Meia esfera que irá compor a topo do braço direito do robô
  glPushMatrix();
  glTranslatef(-0.63f, 0.0f, -0.1f);
  meiaEsfera(0.09, 20, 4);
  glPopMatrix();

  // Meia esfera que irá compor a base do braço direito do robô
  glPushMatrix();
  glTranslatef(-0.63f, 0.0f, -0.55f);
  glRotatef(180, 1.0f, 0.0f, 0.0f);
  meiaEsfera(0.09, 100, 4);
  glPopMatrix();
}

void leftArm(GLUquadricObj *qobj){
  // Definindo a cor corrente como branco
  glColor3f(1.0f, 1.0f, 1.0f);

  // Cilindro que junta o braço esquerdo do robô ao tronco
  glPushMatrix();
  glTranslatef(0.45f, 0.0f, -0.1f);
  glRotatef(90, 0.0f, 1.0f, 0.0f);
  gluCylinder(qobj, 0.05, 0.05, 0.2, 100, 100);
  glPopMatrix();

  // Definindo a cor corrente como verde
  glColor3ub(164, 199, 57);

  // Braço esquerdo do robô
  glPushMatrix();
  glTranslatef(0.63f, 0.0f, -0.55f);
  gluCylinder(qobj, 0.09, 0.09, 0.45, 100, 100);
  glPopMatrix();

  // Meia esfera que irá compor a topo do braço esquerdo do robô
  glPushMatrix();
  glTranslatef(0.63f, 0.0f, -0.1f);
  meiaEsfera(0.09, 100, 4);
  glPopMatrix();

  // Meia esfera que irá compor a base do braço esquerdo do robô
  glPushMatrix();
  glTranslatef(0.63f, 0.0f, -0.55f);
  glRotatef(180, 1.0f, 0.0f, 0.0f);
  meiaEsfera(0.09, 100, 4);
  glPopMatrix();
}

void rightLeg(GLUquadricObj *qobj){
  // Definindo a cor corrente como verde
  glColor3ub(164, 199, 57);

  // Perna direita do robô
  glPushMatrix();
  glScalef(1.0f, 1.5f, 1.0f);
  glTranslatef(-0.20f, 0.0f, -1.15f);
  gluCylinder(qobj, 0.1, 0.1, 0.8, 100, 100);
  glPopMatrix();

  // Meia esfera que irá compor a base da perna direita do robô
  glPushMatrix();
  glScalef(1.0f, 1.5f, 1.0f);
  glTranslatef(-0.20f, 0.0f, -1.15f);
  glRotatef(180, 1.0f, 0.0f, 0.0f);
  meiaEsfera(0.1, 100, 4);
  glPopMatrix();
}

void leftLeg(GLUquadricObj *qobj){
  // Definindo a cor corrente como verde
  glColor3ub(164, 199, 57);

  // Perna esquerda do robô
  glPushMatrix();
  glScalef(1.0f, 1.5f, 1.0f);
  glTranslatef(0.20f, 0.0f, -1.15f);
  gluCylinder(qobj, 0.1, 0.1, 0.8, 100, 100);
  glPopMatrix();

  // Meia esfera que irá compor a base da perna esquerda do robô
  glPushMatrix();
  glScalef(1.0f, 1.5f, 1.0f);
  glTranslatef(0.20f, 0.0f, -1.15f);
  glRotatef(180, 1.0f, 0.0f, 0.0f);
  meiaEsfera(0.1, 100, 4);
  glPopMatrix();
}

void android(GLUquadricObj *qobj) {
  glPushMatrix();
  // Depois de pegar impulso o android fica de lado no skate
  // [glRotatef(-90, 0.0f, 0.0f, 1.0f) para ficar de lado, glTranslatef(0.0f, -0.2f, 0.0f) para ficar no centro do skate]
  // glRotatef(-90, 0.0f, 0.0f, 1.0f);
  // glTranslatef(0.0f, -0.2f, 0.0f);

  // Quando está pegando impulso todo o corpo desce, exceto a perna direita que está sob o skate.
  // Isso simula o movimento de flexão do joelho [glTranslatef(0.0f, 0.0f, desloc) - desloc de 0 a -0.15]
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -0.15f);

  head(qobj);
  body(qobj);

  glPushMatrix();
  // Quando está pegando impulso:
  // O braço esquerdo vai para frente e volta à origem [glRotatef(angle, 1.0f, 0.0f, 0.0f) - angle de 0 a 45 graus];
  // O braço direito sobe e volta à origem [glRotatef(angle, 0.0f, 1.0f, 0.0f) - angle de 0 a 6 graus];
  // A perna esquerda vai para trás e volta à origem [glRotatef(angle, 1.0f, 0.0f, 0.0f) - angle de -13 a 0 graus].
  glRotatef(45, 1.0f, 0.0f, 0.0f);
  leftArm(qobj);
  glPopMatrix();

  glPushMatrix();
  glRotatef(6, 0.0f, 1.0f, 0.0f);
  rightArm(qobj);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-13, 1.0f, 0.0f, 0.0f);
  leftLeg(qobj);
  glPopMatrix();

  glPopMatrix();

  rightLeg(qobj);
  glPopMatrix();
}
