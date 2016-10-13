#include <GL/glut.h>
#include <GL/glu.h>

double angle;

void drawSkate(GLUquadricObj *qobj) {

  glColor3f(0.8549f, 0.64706f, 0.12549f);
  //roda1
  glPushMatrix();
  glRotated(90, 0, 1, 0);
  glRotated(90, 1, 0, 0);
  glutSolidTorus(0.03, 0.05, 50, 50);
  glPopMatrix();

  //roda2
  glPushMatrix();
  glTranslated(-1, 0, 0);
  glRotated(90, 0, 1, 0);
  glRotated(90, 1, 0, 0);
  glutSolidTorus(0.03, 0.05, 50, 50);
  glPopMatrix();

  //roda3
  glPushMatrix();
  glTranslated(0, -0.8, 0);
  glRotated(90, 0, 1, 0);
  glRotated(90, 1, 0, 0);
  glutSolidTorus(0.03, 0.05, 50, 50);
  glPopMatrix();

  //roda4
  glPushMatrix();
  glTranslated(0, -0.8, 0);
  glTranslated(-1, 0, 0);
  glRotated(90, 0, 1, 0);
  glRotated(90, 1, 0, 0);
  glutSolidTorus(0.03, 0.05, 50, 50);
  glPopMatrix();

  //base
  glPushMatrix();
  glColor3f(0.75294f, 0.75294f, 0.75294f);
  glScaled(12, 9.5, 1.0);
  glTranslated(0, 0, 0.12);
  glTranslated(-0.04, 0, 0);
  glTranslated(0, -0.04, 0);
  glutSolidCube(0.1);
  glPopMatrix();

  //tras
  glPushMatrix();
  glTranslated(0, 0, 0.15);
  glTranslated(0.15, 0, 0);
  glRotated(-15, 0, 1, 0);
  glTranslated(0, -0.38, 0);
  glScaled(3, 9.5, 1.0);
  glutSolidCube(0.1);
  glPopMatrix();

  //Arredondar frente da base
  glPushMatrix();
  //glColor3f(0.5f, 0.5f, 0.5f);
  //glColor3f(1.0f, 0.0f, 0.0f);
  glTranslated(-1.08, 0, 0);
  glTranslated(0, 0, 0.12);
  glTranslated(0, -0.375, 0);
  glScaled(1, 4.7, 0.7);
  gluSphere(qobj, 0.1, 100, 100);
  //gluCylinder(qobj, 0.05, 0.05, 0.3, 200, 200);
  glPopMatrix();
}

// Função callback chamada para fazer o desenho
void draw(void) {
  GLUquadricObj *qobj;
  qobj = gluNewQuadric();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Limpa a janela de visualização com a cor de fundo especificada
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  gluQuadricDrawStyle(qobj, GLU_FILL);
  gluQuadricNormals(qobj, GLU_SMOOTH);
  gluQuadricOrientation(qobj, GLU_OUTSIDE);

  // gluLookAt(xC, yC, zC, xP, yP, zP, xU, yU, zU)
  // Se o vetor up é z então yC parece z e zC parece y
  // gluLookAt(12.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  gluLookAt(0.0, 1.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  //gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  //gluLookAt(-5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  drawSkate(qobj);

  glutSwapBuffers();
  glFinish();
}

void initialize(void) {
  angle = 0;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);

		GLfloat luzAmbiente[4] = { 0.3,0.3,0.3,1.0 };
		GLfloat luzDifusa[4] = { 0.2,0.2,0.2,1.0 };	   // "cor"
		GLfloat luzEspecular[4] = { 0.7,0.7,0.7, 1.0 };// "brilho"
		GLfloat posicaoLuz[4] = { 0.0, 20.0, 20.0, 1.0 };
		// Capacidade de brilho do material
		GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
		GLint especMaterial = 10;

		// Define a cor de fundo da janela de visualização como preta
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Habilita o modelo de colorização de Gouraud
		glShadeModel(GL_SMOOTH);

		// Define a refletância do material
		glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
		// Define a concentração do brilho
		glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

		// Ativa o uso da luz ambiente
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

		// Define os parâmetros da luz de número 0
		glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
		glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
		glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

		// Habilita a definição da cor do material a partir da cor corrente
		glEnable(GL_COLOR_MATERIAL);
		//Habilita o uso de iluminação
		glEnable(GL_LIGHTING);
		// Habilita a luz de número 0
		glEnable(GL_LIGHT0);
		// Habilita o depth-buffering
		glEnable(GL_DEPTH_TEST);
	  // Indica a função de teste
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

void redraw() {
  angle += 0.1;
  glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
  // GLUT_DEPTH para alocar Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600, 1200);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Android Robot");
    glutIdleFunc(redraw);
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	initialize();
	glutMainLoop();
}
