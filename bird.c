#include <stdlib.h>
#include <stdio.h>
#include <GLUT/glut.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include "myShape.h"
#include <math.h>
#define KEY_ESC 27

int count = 0;
int c = 0;
double d = 0;
double x, y;
int COLOR = 0.0;
int Go=0;
double altitude = 0;
double hanekakudo = 40;

int boo = 0;

float distance = 28., twist=0., elevation=3., azimuth=-180, distancez = 0;

float dif[]= {0, 1, 0, 1};
float shininess = 128.0;

void polarview( void )
{
    glTranslatef( 0.0, 0.0, -distance);
    glRotatef( -twist, 0.0, 0.0, 1.0);
    glRotatef( -elevation, 1.0, 0.0, 0.0);
    glRotatef( -azimuth, 0.0, 1.0, 0.0);
	glTranslatef( 0.0, 0.0, 2*distancez);
}

void idle(void)
{
	glutPostRedisplay();
}

void timer(int value) {
    // アニメーションに使う時間を更新
	if(c == 0){
		COLOR = rand() % 8;
		c = 8;
	}else if(c <= 8 && c > 0){
		c--;
	}

	float diffuse[5][3];

	diffuse[0][0] = 1;//赤
	diffuse[0][1] = 0;
	diffuse[0][2] = 0;

	diffuse[1][0] = 1; //黄
	diffuse[1][1] = 1;
	diffuse[1][2] = 0;

	diffuse[2][0] = 0; //緑
	diffuse[2][1] = 1;
	diffuse[2][2] = 0;

	diffuse[3][0] = 1;  //橙
	diffuse[3][1] = 0.48;
	diffuse[3][2] = 0.10;

	diffuse[4][0] = 0; //青
	diffuse[4][1] = 0;
	diffuse[4][2] = 1;
	
	int count2 = count / 6;
	dif[0] = diffuse[count2][0];
	dif[1]= diffuse[count2][1];
	dif[2]= diffuse[count2][2];
	count++;

	if(count == 29){
		count = 0;
	}

	d += 0.4;
	x = cos(d);
	y = sin(d);

    // 再描画
    glutPostRedisplay();

    // 100ミリ秒後にtimer関数を引数0で自分自身を呼び出す
    glutTimerFunc(40, timer, 0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);


	glPushMatrix();
	  //glTranslatef(0.0,0.0,-40.0);

	polarview();

int i, j;
if(boo == 0){
		glEnable( GL_DEPTH_TEST );
		glMaterialfv( GL_FRONT, GL_DIFFUSE, dif );
		glMaterialf( GL_FRONT, GL_SHININESS, shininess );
		glEnable( GL_LIGHTING );
		glEnable(GL_LIGHT0);

		glPushMatrix();/*座標系の保存*/
	  	  	glTranslatef(1.65*x-5,2*y-7,0);
			glRotatef( -hanekakudo, 0.0, 0.0, 1.0);
			glScalef(0.3,1.6,0.6);
 			glutSolidSphere(4, 40, 10);
		 glPopMatrix();/*座標系の復元*/

		  glPushMatrix();/*座標系の保存*/
	  	  glTranslatef(1.65*x+5,2*y-7,0);
			glRotatef( hanekakudo, 0.0, 0.0, 1.0);
			glScalef(0.3,1.6,0.6);
 			glutSolidSphere(4, 40, 10);
		 glPopMatrix();/*座標系の復元*/

	  glPushMatrix();/*座標系の保存*/
	    glTranslatef(1.5*x,1.5*y-8,0);
		glScalef(1.3,1.6,1);
 		glutSolidSphere(4, 40, 10);
	 	glPopMatrix();/*座標系の復元*/

	  glPushMatrix();/*座標系の保存*/
	    glTranslatef(2*x,2*y,0);
		glScalef(1,1.1,1);
 		glutSolidSphere(4, 40, 10);
	 	glPopMatrix();/*座標系の復元*/


	glDisable(GL_LIGHT0);
	glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );

	glPushMatrix();/*座標系の保存*/
	  	glColor3f(0,0,0);
	    glTranslatef(2*x-1.6,2*y+1,3.8);
		glScalef(1,1.4,1);
 		glutSolidSphere(0.5, 40, 10);
	 	glPopMatrix();/*座標系の復元*/

	  glPushMatrix();/*座標系の保存*/
	  	glColor3f(0,0,0);
	  	glTranslatef(2*x+1.6,2*y+1,3.8);
		glScalef(1,1.4,1);
		glutSolidSphere(0.5, 40, 10);
		glPopMatrix();/*座標系の復元*/

		 glPushMatrix();/*座標系の保存*/
   	  	 glColor3f(0.2,0.2,0.2);
   	  	 glTranslatef(2*x,2*y-1,3.8);
	  	 glScalef(1,2,1);
   	  	 glutSolidSphere(0.8, 40, 10);
   	  	 glPopMatrix();/*座標系の復元*/
}else{
	for(j=8; j>0; j--){
		for(i=-8; i<=8; i++){
			glPushMatrix();
			if(j%2 == 0){
			glTranslatef(18*i,10*j-20,0);
			}else{
			glTranslatef(18*i+9,10*j-20,0);
			}

		glEnable( GL_DEPTH_TEST );
		glMaterialfv( GL_FRONT, GL_DIFFUSE, dif );
		glMaterialf( GL_FRONT, GL_SHININESS, shininess );
		glEnable( GL_LIGHTING );
		glEnable(GL_LIGHT0);

		glPushMatrix();/*座標系の保存*/
	  	  	glTranslatef(1.65*x-5,2*y-7,0);
			glRotatef( -hanekakudo, 0.0, 0.0, 1.0);
			glScalef(0.3,1.6,0.6);
 			glutSolidSphere(4, 40, 10);
		 glPopMatrix();/*座標系の復元*/

		  glPushMatrix();/*座標系の保存*/
	  	  glTranslatef(1.65*x+5,2*y-7,0);
			glRotatef( hanekakudo, 0.0, 0.0, 1.0);
			glScalef(0.3,1.6,0.6);
 			glutSolidSphere(4, 40, 10);
		 glPopMatrix();/*座標系の復元*/

	  glPushMatrix();/*座標系の保存*/
	    glTranslatef(1.5*x,1.5*y-8,0);
		glScalef(1.3,1.6,1);
 		glutSolidSphere(4, 40, 10);
	 	glPopMatrix();/*座標系の復元*/

	  glPushMatrix();/*座標系の保存*/
	    glTranslatef(2*x,2*y,0);
		glScalef(1,1.1,1);
 		glutSolidSphere(4, 40, 10);
	 	glPopMatrix();/*座標系の復元*/


	glDisable(GL_LIGHT0);
	glDisable( GL_LIGHTING );
    glDisable( GL_DEPTH_TEST );

	glPushMatrix();/*座標系の保存*/
	  	glColor3f(0,0,0);
	    glTranslatef(2*x-1.6,2*y+1,3.8);
		glScalef(1,1.4,1);
 		glutSolidSphere(0.5, 40, 10);
	 	glPopMatrix();/*座標系の復元*/

	  glPushMatrix();/*座標系の保存*/
	  	glColor3f(0,0,0);
	  	glTranslatef(2*x+1.6,2*y+1,3.8);
		glScalef(1,1.4,1);
		glutSolidSphere(0.5, 40, 10);
		glPopMatrix();/*座標系の復元*/

		 glPushMatrix();/*座標系の保存*/
   	  	 glColor3f(0.2,0.2,0.2);
   	  	 glTranslatef(2*x,2*y-1,3.8);
	  	 glScalef(1,2,1);
   	  	 glutSolidSphere(0.8, 40, 10);
   	  	 glPopMatrix();/*座標系の復元*/
		glPopMatrix();/*座標系の復元*/
		}
	}
}

	glPopMatrix();/*座標系の復元*/
	glFlush();
}
void myKbd(unsigned char key, int x, int y)
{
	if(key==KEY_ESC) exit(0);
}
void myInit(char *progname)
{
	int width=1920,height=1080;
	float aspect=(float)width/(float)height;

	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(progname);
	glClearColor(0.9,0.9,0.9,0.7);
	glutKeyboardFunc(myKbd);

	glMatrixMode(GL_PROJECTION);
	/*投影変換行列スタックを操作対象とする*/
	glLoadIdentity();/*行列スタックをクリア*/
	gluPerspective(30.0,aspect,1.0,1000);
	glMatrixMode(GL_MODELVIEW);/*幾何変換行列スタックを操作対象する*/
}

void mySkey(int key, int x , int y)
{
	if( key == GLUT_KEY_UP){
		distancez += 0.5;
		printf(" mySkey\n");
		printf("x,y = %d %d\n",x, y);
		printf("key = %d\n", key);
	} else if(key == GLUT_KEY_DOWN){
		distancez += -0.5;
		printf(" mySkey\n");
		printf("x,y = %d %d\n",x, y);
		printf("key = %d\n", key);
	} else {
		Go = 0;
		glutIdleFunc(NULL);
	}

	if( key == GLUT_KEY_LEFT){
		if(hanekakudo == 40){
			hanekakudo = 130;
		}else{
			hanekakudo = 40;
		}
	} else {
		Go = 0;
		glutIdleFunc(NULL);
	}

	if( key == GLUT_KEY_RIGHT){
		if(boo == 0){
			boo=1;
		}else{
			boo =0;
		}
	} else {
		Go = 0;
		glutIdleFunc(NULL);
	}
/*	printf(" mySkey\n");
	printf("x,y = %d %d\n",x, y);
	printf("key = %d\n", key);
	glutPostRedisplay();   */
}

int main(int argc, char *argv[])
{
	glutInit(&argc,argv);
	myInit(argv[0]);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutDisplayFunc(display);
	glutSpecialFunc(mySkey);
	glutTimerFunc(100, timer, 0);
	glutMainLoop();
	return(0);
}
