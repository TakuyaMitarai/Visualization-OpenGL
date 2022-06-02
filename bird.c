#include <stdlib.h>
#include <stdio.h>

//Macで動かしたい場合
#include <GLUT/glut.h>

//windowsで動かしたい場合
//#include <GL/glut.h> 
//#include <GL/gl.h>
//#include <GL/glu.h>

#include <math.h>
#define KEY_ESC 27

int count = 0;
double d = 0;
double x, y;
int Go=0;
double hanekakudo = 40;
int boo = 0;
float distance = 28., twist=0., elevation=3., azimuth=-180, distancez = 0;
float dif[]= {0, 1, 0, 1};
float shininess = 128.0;

//オウムの色
float diffuse[9][3] = {{1,1,1,},//白
					{0.929, 0.941, 0},//黄 
					{0.627, 1, 0}, //黄緑
					{0.761, 1, 1}, //水色
					{0.375, 0.375, 1}, //青
					{1, 0.628, 1}, //紫
					{1, 0.628, 0.628}, //桃
					{1, 0.429, 0.429}, //濃桃
					{1, 0, 0} //赤
					};

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
	int count2 = count / 3; //色の変化を遅らせる

	dif[0] = diffuse[count2][0];
	dif[1]= diffuse[count2][1];
	dif[2]= diffuse[count2][2];
	count++;
	if(count == 23){ 
		count = 0;
	}

	//円の媒介変数表示
	d += 0.4;
	x = cos(d);
	y = sin(d);

    glutPostRedisplay();

    glutTimerFunc(40, timer, 0);
}

void display(void)
{
	int i, j, min_line, max_line, min_column, max_column;
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
		polarview();

	if(boo == 0){
		min_line = 1;
		max_line = 2;
		min_column = 0;
		max_column = 0;
	}else{
		min_line = 0;
		max_line = 8;
		min_column = -8;
		max_column = 8;
	}
	for(j=max_line; j>min_line; j--){
		for(i=min_column; i<=max_column; i++){
			glPushMatrix();

			//交互に列をずらす処理
			if(j%2 == 0){
				glTranslatef(18*i,10*j-20,0);
			}else{
				glTranslatef(18*i+9,10*j-20,0);
			}

			//ライトEnable
			glEnable( GL_DEPTH_TEST );
			glMaterialfv( GL_FRONT, GL_DIFFUSE, dif );
			glMaterialf( GL_FRONT, GL_SHININESS, shininess );
			glEnable( GL_LIGHTING );
			glEnable(GL_LIGHT0);

			//左羽
			glPushMatrix();/*座標系の保存*/
	  	  		glTranslatef(1.9*x-5,2*y-7,0);
				glRotatef( -hanekakudo, 0.0, 0.0, 1.0);
				glScalef(0.3,1.6,0.6);
 				glutSolidSphere(4, 40, 10);
		 	glPopMatrix();/*座標系の復元*/

			//右羽
		  	glPushMatrix();/*座標系の保存*/
	  	  		glTranslatef(1.9*x+5,2*y-7,0);
				glRotatef( hanekakudo, 0.0, 0.0, 1.0);
				glScalef(0.3,1.6,0.6);
 				glutSolidSphere(4, 40, 10);
		 	glPopMatrix();/*座標系の復元*/

			//胴体
	  		glPushMatrix();/*座標系の保存*/
	    		glTranslatef(1.8*x,1.5*y-8,0);
				glScalef(1.3,1.6,1);
 				glutSolidSphere(4, 40, 10);
	 		glPopMatrix();/*座標系の復元*/

			//頭
	  		glPushMatrix();/*座標系の保存*/
	   			glTranslatef(2.5*x,2*y,0);
				glScalef(1,1.1,1);
 				glutSolidSphere(4, 40, 10);
	 		glPopMatrix();/*座標系の復元*/

			//ライトDisable
			glDisable(GL_LIGHT0);
			glDisable( GL_LIGHTING );
    		glDisable( GL_DEPTH_TEST );

			//右目
			glPushMatrix();/*座標系の保存*/
	  			glColor3f(0,0,0);
	    		glTranslatef(2*x-1.6,2*y+1,3.8);
				glScalef(1,1.4,1);
 				glutSolidSphere(0.5, 40, 10);
	 		glPopMatrix();/*座標系の復元*/

			//左目
	  		glPushMatrix();/*座標系の保存*/
	  			glColor3f(0,0,0);
	  			glTranslatef(2*x+1.6,2*y+1,3.8);
				glScalef(1,1.4,1);
				glutSolidSphere(0.5, 40, 10);
			glPopMatrix();/*座標系の復元*/

			//クチバシ
		 	glPushMatrix();/*座標系の保存*/
   	  	 		glColor3f(0.2,0.2,0.2);
   	  	 		glTranslatef(2*x,2*y-1,3.8);
	  			glScalef(1,2,1);
   	  	 		glutSolidSphere(0.8, 40, 10);
   	  	 		glPopMatrix();/*座標系の復元*/
			glPopMatrix();/*座標系の復元*/
		}
	}
	glPopMatrix();/*座標系の復元*/
	glFlush();
}

void myKbd(unsigned char key, int x, int y)
{
	if(key==KEY_ESC) exit(0); //エスケープキーで終了
}

void myInit(char *progname)
{	
	//画面サイズ
	int width=1920,height=1080;
	float aspect=(float)width/(float)height;

	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);
	glutInitDisplayMode(GLUT_RGBA);
	glutCreateWindow(progname);
	glClearColor(0.9,0.9,0.9,0.7);
	glutKeyboardFunc(myKbd);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0,aspect,1.0,1000);
	glMatrixMode(GL_MODELVIEW);
}

void mySkey(int key, int x , int y)
{
	//z軸の移動
	if( key == GLUT_KEY_UP){
		distancez += 0.5;
	} else if(key == GLUT_KEY_DOWN){
		distancez -= 0.5;
	} else {
		Go = 0;
		glutIdleFunc(NULL);
	}

	//羽の上下
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

	//オウムを増殖
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
