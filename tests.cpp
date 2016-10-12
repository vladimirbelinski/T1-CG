#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

const double pi = 3.1415926;
GLdouble p[3] = { 0,0,0 };

void meia_esfera(GLdouble *centro, GLdouble radius, GLfloat num) {
	GLdouble c, c2, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
	GLdouble phi, theta, phi1, theta1, phi2, theta2;
	GLdouble senphi1, cosphi1, senphi2, cosphi2,
	         sentheta1, costheta1, sentheta2, costheta2,
	         passo;

	glVertex3d(centro[0], centro[1] + radius, centro[2]);

	c = pi / 180;
	passo = 90 / num * c;
	glBegin(GL_TRIANGLES);
	phi1 = 0;
	senphi1 = sin(phi1);
	cosphi1 = cos(phi1);
	int i,j;
	for (i=0; i < num; i++) {
		phi2 = phi1 + passo;
		senphi2 = sin(phi2);
		cosphi2 = cos(phi2);
		theta1 = 0;
		sentheta1 = sin(theta1);
		costheta1 = cos(theta1);
		for (j=0; j < 2 * num; j++) {
			theta2 = theta1 + passo;
			sentheta2 = sin(theta2);
			costheta2 = cos(theta2);
			x1 = centro[0] + radius * senphi1 * costheta1;
			y1 = centro[1] + radius * senphi1 * sentheta1;
			z1 = centro[2] + radius * cosphi1;
			glVertex3d(x1, y1, z1);
			x2 = centro[0] + radius * senphi2 * costheta1;
			y2 = centro[1] + radius * senphi2 * sentheta1;
			z2 = centro[2] + radius * cosphi2;
			glVertex3d(x2, y2, z2);
			x3 = centro[0] + radius * senphi2 * costheta2;
			y3 = centro[1] + radius * senphi2 * sentheta2;
			z3 = centro[2] + radius * cosphi2;
			glVertex3d(x3, y3, z3);
			glVertex3d(x1, y1, z1);
			glVertex3d(x3, y3, z3);
			x4 = centro[0] + radius * senphi1 * costheta2;
			y4 = centro[1] + radius * senphi1 * sentheta2;
			z4 = centro[2] + radius * cosphi1;
			glVertex3d(x4, y4, z4);
			theta1 = theta2;
			sentheta1 = sentheta2;
			costheta1 = costheta2;
		}
		phi1 = phi2;
		senphi1 = senphi2;
		cosphi1 = cosphi2;
	}
	glEnd();
}

// Função callback chamada para fazer o desenho
void draw(void) {
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // gluLookAt(xC, yC, zC, xP, yP, zP, xU, yU, zU)
	// Se o vetor up é z então yC parece z e zC parece y
  gluLookAt(0.0, 4.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	// Definindo a cor corrente como verde
	glColor3f(0.0f, 1.0f, 0.0f);

	// Meia esfera que irá compor a cabeça do robô
	glPushMatrix();
	glTranslatef (0.0f, 0.0f, 0.07f);
	meia_esfera(p, 0.5, 20);
	glPopMatrix();

	// Disco sob a meia esfera para fechá-la
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	glTranslatef(0.0f, 0.0f, 0.07f);
	gluDisk(qobj, 0.2, 0.5, 30, 30);
	glPopMatrix();

	// Cilindro que forma o pescoço do robô
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	//gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
	//gluQuadricNormals(qobj, GLU_NONE);
	gluCylinder(qobj, 0.2, 0.2, 0.07, 200, 200);
	glPopMatrix();

	// Disco que fecha a parte superior do cilindro que forma o tronco do robô
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	//gluQuadricDrawStyle(qobj, GLU_LINE);
	//gluQuadricNormals(qobj, GLU_NONE);
	gluDisk(qobj, 0.2, 0.5, 30, 30);
	glPopMatrix();

	// Cilindro que forma o tronco do robô
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	//gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
	//gluQuadricNormals(qobj, GLU_NONE);
	glTranslatef(0.0f, 0.0f, -0.8f);
	gluCylinder(qobj, 0.5, 0.5, 0.8, 200, 200);
	glPopMatrix();

	// Esfera que fecha a parte inferior do cilindro que forma o tronco do robô
	// glPushMatrix();
	// gluQuadricDrawStyle(qobj, GLU_FILL);
	// gluQuadricNormals(qobj, GLU_SMOOTH);
	// gluQuadricOrientation(qobj, GLU_OUTSIDE);
	// //gluQuadricDrawStyle(qobj, GLU_SILHOUETTE);
	// //gluQuadricNormals(qobj, GLU_NONE);
	// glScalef(1.7f, 1.0f, 1.0f);
	// glTranslatef(0.0f, 0.0f, -0.78f);
	// gluSphere(qobj, 0.3, 30, 30);
	// glPopMatrix();

	// Executa os comandos OpenGL
  glutSwapBuffers();
  glFinish();
}

void initialize(void) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_SMOOTH);

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
