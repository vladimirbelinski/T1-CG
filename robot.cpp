/* Arquivo: robot.cpp
   Autores: João Pedro Winckler Bernardi e Vladimir Belinski
   Descrição: o presente arquivo faz parte da resolução do Trabalho I do CCR Computação Gráfica, 2016-2, do curso de
              Ciência da Computação da Universidade Federal da Fronteira Sul - UFFS, o qual consiste em uma animação
              do símbolo do SO Android (robô) andando de skate.
              --> robot.cpp é o arquivo responsável pela definição das primitivas gráficas que comporão o robô, assim
              como a movimentação da cabeça, pernas, tronco e braços do robô.
*/

// Inclusão das bibliotecas necessárias
#include "misc.h"
#include "robot.h"
#include <time.h>
#include <stdio.h>

// Variáveis que serão utilizadas na movimentação dos membros do robô
GLfloat alpha_flexAll = 0.0f;
GLfloat alpha_rotateHead = 0.0f;
GLfloat alpha_rotateLeftLeg = 0.0f;
GLfloat alpha_rotateLeftArm = 0.0f;
GLfloat alpha_rotateLeftArm2 = 0.0f;
GLfloat alpha_rotateRightArm = 0.0f;
GLint flexAllMov, headMov, leftLegMov, leftArmMov, leftArmMov2, rightArmMov;

int idle = 0;
time_t start;
GLfloat alpha_idleRobot, y_idlePosition;

// A função head é responsável pelo desenho da cabeça do robô na cena
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

// A função body é responsável pelo desenho do corpo do robô na cena
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

// A função rightArm é responsável pelo desenho do braço direito do robô na cena
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

// A função leftArm é responsável pelo desenho do braço esquerdo do robô na cena
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

// A função rightLeg é responsável pelo desenho da perna direita do robô na cena
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

// A função leftLeg é responsável pelo desenho da perna esquerda do robô na cena
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

// A função idleAndroid é responsável pelo movimento de girar sobre o skate e permanecer se equilibrando sobre ele
void idleAndroid(GLUquadricObj *qobj) {
  // Quanto maior o valor de 'vel', mais lenta é a transição (giro)
  int vel = 12;
  // Quanto tempo(segundos) o robo vai ficar parado sobre o skate
  int tempo = 7;
  //idle funciona como uma máquina de estados onde são realizadas as operações necessárias para a transição do posicionamento do robô
  if (idle == 4) { y_idlePosition = 0.0f; alpha_idleRobot = 0.0f; idle++; }
  if (idle == 5) {
    alpha_idleRobot -= 90.0 / vel;
    y_idlePosition -= 0.2 / vel;
    if (alpha_idleRobot <= -90.0f) idle++; //<= por causa da precisão....
  }
  if (idle == 6) { start = time(0); idle++; }
  if (idle == 7 && difftime(time(0), start) >= tempo) idle++;
  if (idle == 8) {
    alpha_idleRobot += 90.0 / vel;
    y_idlePosition += 0.2 / vel;
    if (alpha_idleRobot >= 0.0f) idle = 0; //>= por causa da precisão
  }
  // Depois de pegar impulso o android fica de lado no skate
  // [glRotatef(-90, 0.0f, 0.0f, 1.0f) para ficar de lado, glTranslatef(0.0f, -0.2f, 0.0f) para ficar no centro do skate]
  glRotatef(alpha_idleRobot, 0.0f, 0.0f, 1.0f);
  glTranslatef(0.0f, y_idlePosition, 0.0f);

  glPushMatrix();
   if (flexAllMov == 1 and alpha_flexAll > -0.08f)
    alpha_flexAll -= 0.00346153f;
  else
    flexAllMov = 2;

  if (flexAllMov == 2 and alpha_flexAll <= 0.0f)
    alpha_flexAll += 0.0034615f;
  else
   flexAllMov = 1;

  glTranslatef(0.0f, 0.0f, alpha_flexAll);

  glPushMatrix();
  if (headMov == 1 and alpha_rotateHead > -30.0f)
    alpha_rotateHead -= 2.076921f/2;
  else
    headMov = 2;

  if (headMov == 2 and alpha_rotateHead <= 0.0f)
    alpha_rotateHead += 2.076921f/2;
  else
    headMov = 1;

  glRotatef(alpha_rotateHead, 0.0f, 0.0f, 1.0f);
  head(qobj);
  glPopMatrix();

  body(qobj);

  // Movimentação do braço direito
  glPushMatrix();
  if (leftArmMov2 == 1 and alpha_rotateLeftArm2 < 5.0f)
    alpha_rotateLeftArm2 += 0.346152f;
  else
    leftArmMov2 = 2;

  if (leftArmMov2 == 2 and alpha_rotateLeftArm2 >= 0.0f)
    alpha_rotateLeftArm2 -= 0.346152f;
  else
    leftArmMov2 = 1;

  glRotatef(alpha_rotateLeftArm2, 0.0f, 1.0f, 0.0f);
  leftArm(qobj);
  glPopMatrix();

  // Movimentação do braço esquerdo
  glPushMatrix();
  if (rightArmMov == 1 and alpha_rotateRightArm < 5.0f)
    alpha_rotateRightArm += 0.346152f;
  else
    rightArmMov = 2;

  if (rightArmMov == 2 and alpha_rotateRightArm >= 0.0f)
    alpha_rotateRightArm -= 0.346152f;
  else
    rightArmMov = 1;

  glRotatef(alpha_rotateRightArm, 0.0f, 1.0f, 0.0f);
  rightArm(qobj);
  glPopMatrix();

  glPopMatrix();
  leftLeg(qobj);
  rightLeg(qobj);
}

// A função android é responsável pelo desenho do robô como um todo na cena e seu efeitos de movimentação
void android(GLUquadricObj *qobj) {
  glPushMatrix();
  // Verificação realizada para determinar qual dos movimentos será realizado: impulso ou virada sobre o skate
  if (idle >= 4) { idleAndroid(qobj); glPopMatrix(); alpha_rotateLeftArm = 0.0f; alpha_rotateLeftLeg = 0.0f; return; }

  // Quando está pegando impulso todo o corpo desce, exceto a perna direita que está sob o skate.
  // Isso simula o movimento de flexão do joelho [glTranslatef(0.0f, 0.0f, desloc) - desloc de 0 a -0.15]
  glPushMatrix();
  if (flexAllMov == 1 and alpha_flexAll > -0.15f)
    alpha_flexAll -= 0.01038459f;
  else
    flexAllMov = 2;

  if (flexAllMov == 2 and alpha_flexAll <= 0.0f)
    alpha_flexAll += 0.01038459f;
  else
    // Sempre cai nesse else quando flexAllMov != 2. Queremos incrementar o idle somente na primeira vez que entrar aqui
    { idle += flexAllMov == 2; flexAllMov = 1; }

  glTranslatef(0.0f, 0.0f, alpha_flexAll);

  // Quando está pegando impulso:
  // A cabeça vira à esquerda e volta à origem [glRotatef(angle, 0.0f, 0.0f, 1.0f) - angle de 0 a -30 graus]
  // O braço esquerdo vai para frente e volta à origem [glRotatef(angle, 1.0f, 0.0f, 0.0f) - angle de 0 a 45 graus];
  // O braço direito sobe e volta à origem [glRotatef(angle, 0.0f, 1.0f, 0.0f) - angle de 0 a 6 graus];
  // A perna esquerda vai para trás e volta à origem [glRotatef(angle, 1.0f, 0.0f, 0.0f) - angle de -13 a 0 graus].

  // Movimentação da cabeça
  glPushMatrix();
  if (headMov == 1 and alpha_rotateHead > -30.0f)
    alpha_rotateHead -= 2.076921f;
  else
    headMov = 2;

  if (headMov == 2 and alpha_rotateHead <= 0.0f)
    alpha_rotateHead += 2.076921f;
  else
    headMov = 1;

  glRotatef(alpha_rotateHead, 0.0f, 0.0f, 1.0f);
  head(qobj);
  glPopMatrix();

  body(qobj);

  // Movimentação do braço esquerdo
  glPushMatrix();
  if (leftArmMov == 1 and alpha_rotateLeftArm < 45.0f)
    alpha_rotateLeftArm += 3.115383f;
  else
    leftArmMov = 2;

  if (leftArmMov == 2 and alpha_rotateLeftArm >= 0.0f)
    alpha_rotateLeftArm -= 3.115383f;
  else
    leftArmMov = 1;

  glRotatef(alpha_rotateLeftArm, 1.0f, 0.0f, 0.0f);
  leftArm(qobj);
  glPopMatrix();

  // Movimentação do braço direito
  glPushMatrix();
  if (rightArmMov == 1 and alpha_rotateRightArm < 6.0f)
    alpha_rotateRightArm += 0.415383f;
  else
    rightArmMov = 2;

  if (rightArmMov == 2 and alpha_rotateRightArm >= 0.0f)
    alpha_rotateRightArm -= 0.415383f;
  else
    rightArmMov = 1;

  glRotatef(alpha_rotateRightArm, 0.0f, 1.0f, 0.0f);
  rightArm(qobj);
  glPopMatrix();

  // Movimentação da perna esquerda
  glPushMatrix();
  if (leftLegMov == 1 and alpha_rotateLeftLeg > -13.0f)
    alpha_rotateLeftLeg -= 0.75f;
  else
    leftLegMov = 2;

  if (leftLegMov == 2 and alpha_rotateLeftLeg <= 0.0f)
    alpha_rotateLeftLeg += 0.75f;
  else
    leftLegMov = 1;

  glRotatef(alpha_rotateLeftLeg, 1.0f, 0.0f, 0.0f);
  leftLeg(qobj);
  glPopMatrix();

  glPopMatrix();

  rightLeg(qobj);
  glPopMatrix();
}
