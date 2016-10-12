#include <GL/glut.h>

// Função callback chamada para fazer o desenho
void draw(void) {
	GLUquadricObj *body;
	body = gluNewQuadric();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  // gluLookAt(xC, yC, zC, xP, yP, zP, xU, yU, zU)
	// Se o vetor up é z então yC parece z e zC parece y
  gluLookAt(0.0, 4.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	glColor3f(0.0f, 1.0f, 0.0f);

	glPushMatrix();
	gluQuadricDrawStyle(body, GLU_FILL);
	gluQuadricNormals(body, GLU_SMOOTH);
	//gluQuadricOrientation(body, GLU_OUTSIDE);
	//gluQuadricDrawStyle(body, GLU_SILHOUETTE);
	//gluQuadricNormals(body, GLU_NONE);
	glTranslatef(0.0f, 0.0f, -0.8f);
	gluCylinder(body, 0.5, 0.5, 0.8, 200, 200);
	glPopMatrix();

	glPushMatrix();
	gluQuadricDrawStyle(body, GLU_FILL);
	gluQuadricNormals(body, GLU_SMOOTH);
	//gluQuadricOrientation(body, GLU_OUTSIDE);
	//gluQuadricDrawStyle(body, GLU_LINE);
	//gluQuadricNormals(body, GLU_NONE);
	//glTranslatef(0.0f, 0.0f, 0.5f);
	gluDisk(body, 0.2, 0.5, 30, 30);
	glPopMatrix();

	// Executa os comandos OpenGL
  glutSwapBuffers();
  glFinish();
}

void initialize(void) {
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

// void redraw() {
//   glutPostRedisplay();
// }

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
