/*
Nome: 9.cpp
Autor: Vladimir Belinski
Descrição: programa que desenha um chapéu de bruxa sobre uma esfera
*/

#include <GL/glut.h>

// Função callback chamada para fazer o desenho
void draw(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  // gluLookAt(xC, yC, zC, xP, yP, zP, xU, yU, zU)
  gluLookAt(5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  // Rotaciono para ver de lado, pois aparentemente o cone é mostrado como uma
  // esfera com centro no ponto 0.0 e uma extensão acima de altura igual a informada
	glColor3f(1.0f, 1.0f, 1.0f); // Branco
	glPushMatrix();
	// Rotate para ter uma visão de baixo
	//glRotatef(-50, 1.0f, 0.0f, 0.0f);
  glutWireCone(0.5, 1.0, 50, 50);
	glutWireTorus(0.05, 0.5, 30, 30);
	glPopMatrix();

	glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
	glPushMatrix();
	// Translado em z, pois se em gluLookAt uso 0.0 para o y da câmera tenho uma visão
	// do topo do cone. Assim, para dar a impressão de que a esfera está descendo ao
	// usar y == -4.0 tenho q transladar em z, não em y
	//glRotatef(-50, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -0.2f);
	glutWireSphere(0.4, 15, 15);
	glPopMatrix();

	// Executa os comandos OpenGL
  glutSwapBuffers();
  glFinish();
}

void initialize(void) {
	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // Habilita operação do teste do Z-buffer
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
  glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
  // GLUT_DEPTH para alocar Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600, 1200);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Android Robot");
  //glutIdleFunc(Redraw);
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);
	initialize();
	glutMainLoop();
}
