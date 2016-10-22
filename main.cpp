#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include "skate.h"
#include "robot.h"
#include <math.h>

#define RADIUS 8
#define DEFAULT_VIEW 0
#define UP_VIEW 1
#define DOWN_VIEW 2

GLfloat alpha_rotateAll = 0.0f;
GLUquadricObj *qobj;
double x, y;
int xflag = 0, yflag = 0, camView = DEFAULT_VIEW;

// Função callback chamada para fazer o desenho
void draw(void) {
  qobj = gluNewQuadric();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Limpa a janela de visualização com a cor de fundo especificada
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // gluLookAt(xC, yC, zC, xP, yP, zP, xU, yU, zU)
  // Se o vetor up é z então yC parece z e zC parece y
  // gluLookAt(12.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  // gluLookAt(0.0, 5.0, -2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    //gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  switch (camView) {
    case DEFAULT_VIEW: gluLookAt(x, y, 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f); break;
    case UP_VIEW: gluLookAt(0.0f, 0.0f, RADIUS, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f); break;
    case DOWN_VIEW: gluLookAt(0.0f, 0.0f, -RADIUS, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f, 0.0f); break;
  }

  glPushMatrix();
  glRotatef(alpha_rotateAll += 1.0f, 0.0f, 0.0f, 1.0f);
  glTranslatef(2.0f, 0.0f, 0.0f);
  // Rotinas que definem os atributos das quádricas
  gluQuadricDrawStyle(qobj, GLU_FILL);
  gluQuadricNormals(qobj, GLU_SMOOTH);
  gluQuadricOrientation(qobj, GLU_OUTSIDE);
  gluQuadricTexture(qobj, GLU_FALSE);
  android(qobj);
  skate(qobj);
  glPopMatrix();

  // Executa os comandos OpenGL
  glutSwapBuffers();
  glFinish();
}

void initialize(void) {
  x = RADIUS; y = 0; y = 0;
  GLfloat model_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
  GLfloat mat_specular[] = {0.8, 0.8, 0.8, 1.0};          // capacidade de brilho do material
  GLfloat mat_shininess[] = { 90.0 };

  GLfloat light0_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat light0_diffuse[] = { 0.9, 0.9, 0.9, 1.0 };	    // "cor"
  GLfloat light0_specular[] = { 0.8, 0.8, 0.8, 1.0 };     // "brilho"
  GLfloat light0_position[] = { -20.0, 20.0, 40.0, 1.0 };

  GLfloat light1_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
  GLfloat light1_diffuse[] = { 0.2, 0.2, 0.2, 1.0 };
  GLfloat light1_specular[] = { 0.7, 0.7, 0.7, 1.0 };
  GLfloat light1_position[] = { 0.0, 1.0, -30.0, 1.0 };

  // Definição da cor de fundo da janela de visualização como preta
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Habilitação do modelo de colorização de Gouraud
  glShadeModel(GL_SMOOTH);

  // Definição da refletância  e concentração do brilho do material
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

  // Ativação do uso da luz ambiente
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

  // Definição dos parâmetros da luz de número 0
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

  // Definição dos parâmetros da luz de número 1
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

  // Habilitação da definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  // Habilitação do uso de iluminação e das luzes
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  // Habilitação da normalização
  glEnable(GL_NORMALIZE);
  glEnable(GL_RESCALE_NORMAL);

  // Habilitação do depth-buffering e indicação da função de teste
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void reshape(GLsizei w, GLsizei h) {
  // Evita a divisão por zero
  if (h == 0) h = 1;
  // Especifica as dimensões da Viewport
  glViewport(0, 0, w, h);
  // Inicializa o sistema de coordenadas
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // gluPerspective(GLdouble fov, GLdouble aspect, GLdouble near, GLdouble far)
  gluPerspective(45, w/h, 1, 100);
}

void redraw(int) {
// void redraw() {
  glutPostRedisplay();
  draw();
  glutTimerFunc(10,redraw,1);
}

void keyboard(unsigned char key, int a, int b) {
  double vel = 0.2, tmp;
  switch (key) {
  //printf("Esquerda\n");
  case 'a':
    camView = DEFAULT_VIEW;
    if (xflag == 0) x -= vel;
    else x += vel;
    if (fabs(x) >= 8) { x = x < 0 ? -8 : 8; xflag = !xflag; yflag = !yflag; }
    tmp = RADIUS * RADIUS - x * x;
    y = sqrt(tmp < 0 ? 0 : tmp) * (yflag ? 1 : -1);
    printf("%lf %lf\n", x, y);
    break;
  case 'd':
    camView = DEFAULT_VIEW;
    if (xflag == 0) x += vel;
    else x -= vel;
    if (fabs(x) >= 8) { x = x < 0 ? -8 : 8; xflag = !xflag; yflag = !yflag; }
    tmp = RADIUS * RADIUS - x * x;
    y = sqrt(tmp < 0 ? 0 : tmp) * (yflag ? 1 : -1);
    printf("%lf %lf\n", x, y);
    break;
  case 'w': camView = UP_VIEW; break;
  case 's': camView = DOWN_VIEW; break;
  }

}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  // GLUT_DEPTH para alocar Z-buffer
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 720);
  glutInitWindowPosition(10, 10);
  glutCreateWindow("Android Robot");
  // glutIdleFunc(redraw);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(10,redraw,1);
  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  initialize();
  glutMainLoop();
}
