// stickman.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#define GLEW_STATIC
#include <stdio.h>    
#include <string.h>    
#include <stdlib.h>   
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>


GLfloat swingLeft = 0;  //摆动角度
GLfloat swingRight = 0;
GLint maxAngel;//最大摆动角
GLint swingspeed;//大腿摆动角速度
GLfloat speed;//前进速度
GLfloat direction;
GLfloat moveX = 0, moveZ = 0;//当前位移
bool isStand = true;
bool isSwing = false;  //摆臂
GLfloat swingSmall = 0;

/**
当窗口大小改变时
**/
void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = 1.0f*w / h;
	//设置视口为整个窗口大小
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//设置可视空间
	gluPerspective(100, ratio, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -8.0);
}


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);   //设置着色模式

	//画地面
	glBegin(GL_QUADS);	
	//而glColor3b()需要传入的是byte类型，它的数值范围是-128-127，也就是有符号数，
	//传入255，由于越界了，255这个数就相当于-128，难怪不变红啊。
	glColor3b(37, 37, 37);
	glVertex3f(-10.0f, -3.0f, 4.0f);
	glVertex3f(10.0f, -3.0f, 4.0f);
	glVertex3f(10.0f, -3.0f, -4.0f);
	glVertex3f(-10.0f, -3.0f, -4.0f);
	glEnd();

	//画右腿
	glPushMatrix();
	glTranslatef(moveX, 0.0, moveZ); //平移原点（0，0，0）个距离
	glRotatef(180, 0.0, 1.0, 0.0);
	glTranslatef(0.325, 0.0, 0.0);
	glRotatef(swingRight, 1.0, 0.0, 0.0);
	//下调坐标系画右大腿
	glTranslatef(0.0, -0.6, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	//画右大腿
	glPushMatrix();
	glScalef(0.4, 1.0, 0.4);  //模型缩放，机器人的大腿是一个0.4*1*0.4的立方体
	glutSolidCube(1);
	glPopMatrix();

	glTranslatef(0.0, -0.5, 0.0);
	glRotatef(swingSmall, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	//画右小腿
	glPushMatrix();
	glScalef(0.3, 1.0, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();

	//画左腿
	glPushMatrix();
	//对坐标系平移与旋转
	glTranslatef(moveX, 0.0, moveZ);//前进
	glRotatef(180, 0.0, 1.0, 0.0);//转向
	//大腿
	glTranslatef(-0.325, 0.0, 0.0);
	glRotatef(swingLeft, 1.0, 0.0, 0.0); //swingLeft表示左大腿旋转角度
	//因为旋转腿的时候是绕着大腿根部旋转，所以先把坐标系左移，旋转
	glTranslatef(0.0, -0.5, 0.0);//再把坐标系下移到我们要的原点
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(0.4, 1.0, 0.4);//大腿是一个0.4*1*0.4的立方体
	glutSolidCube(1.0);
	glPopMatrix();
	//左小腿
	glTranslatef(0.0, -0.5, 0.0);
	glRotatef(swingSmall, 1.0, 0.0, 0.0); //小腿摆动swingsmall度
	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(0.3, 1.0, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	//出栈

	//画身体
	glPushMatrix();
	glTranslatef(moveX, 0.0, moveZ);
	glRotatef(180, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.35, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glutSolidSphere(0.9f, 20, 20);
	glPopMatrix();
	//头部
	glTranslatef(0.0, 1.1, 0.0);
	glColor3f(0.9, 0.9, 0.9);
	glPushMatrix();
	glutSolidSphere(0.5f, 20, 20);
	glPopMatrix();

	//眼睛
	glTranslatef(0.12, 0.1, -0.25);//画右眼
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glutSolidSphere(0.05f, 20, 20);
	glPopMatrix();

	glTranslatef(-0.24, 0.0, 0.0);//画左眼（右眼向左平移0.24）
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glutSolidSphere(0.05f, 20, 20);
	glPopMatrix();

	//嘴巴
	glTranslatef(0.125, -0.25, 0.0);
	glColor3f(0.8, 0.2, 0.2);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();



	glPopMatrix();
	//出栈

	//画右臂
	glPushMatrix();
	glTranslatef(moveX, 0.0, moveZ);
	glRotatef(180, 0.0, 1.0, 0.0);
	
	glTranslatef(0.85, 0.3, 0.0);
	glRotatef(swingLeft, 1.0, 0.0, 0.0);  //右臂的摆动角度与左腿相同
	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(1.0,1.0, 1.0);
	glPushMatrix();
	glScalef(0.25, 1.3, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	

	//画左臂
	glPushMatrix();
	glTranslatef(moveX, 0.0, moveZ);
	glRotatef(180, 0.0, 1.0, 0.0);
	
	glTranslatef(-0.85, 0.3, 0.0);
	glRotatef(swingRight, 1.0, 0.0, 0.0);  //左臂的摆动角度与右腿相同
	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(0.25, 1.3, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

//时间函数,定时刷新
void timer(int value)
{
	moveX = moveX - speed*sin(direction / 360 * 3.14 * 2);
	moveZ = moveZ - speed*cos(direction / 360 * 3.14 * 2);
	if (!isSwing) {//从静止开始，左腿在前
		swingLeft = (swingLeft + swingspeed);
		swingRight = (swingRight - swingspeed);
		if (swingLeft>0) {//左大腿向前，小腿向内弯 
			swingSmall = swingSmall - swingspeed*1.5; 
		}
		else { 
			swingSmall = swingSmall + swingspeed*1.5; 
		}
	}
	else
	{
		swingLeft = swingLeft - swingspeed;
		swingRight = swingRight + swingspeed;
		if (swingLeft<0) {
			swingSmall = swingSmall - swingspeed*1.5;
		}
		else { 
			swingSmall = swingSmall + swingspeed*1.5; 
		}
	}
	if (swingLeft>maxAngel) {
		isSwing = true;//换腿
	}
	if (swingLeft<maxAngel*-1) {
		isSwing = false;
	}
	RenderScene();
	glutPostRedisplay();
	if (!isStand) glutTimerFunc(value, timer, value);
}


void timer2(int value)
{
	moveX = moveX - speed*sin(-180 / 360 * 3.14 * 2);
	moveZ = moveZ - speed*cos(-180 / 360 * 3.14 * 2);
	if (!isSwing) {//从静止开始，左腿在前
		swingLeft = (swingLeft + swingspeed);
		swingRight = (swingRight - swingspeed);
		if (swingLeft>0) {//左大腿向前，小腿向内弯 
			swingSmall = swingSmall - swingspeed*1.5;
		}
		else {
			swingSmall = swingSmall + swingspeed*1.5;
		}
	}
	else
	{
		swingLeft = swingLeft - swingspeed;
		swingRight = swingRight + swingspeed;
		if (swingLeft<0) {
			swingSmall = swingSmall - swingspeed*1.5;
		}
		else {
			swingSmall = swingSmall + swingspeed*1.5;
		}
	}
	if (swingLeft>maxAngel) {
		isSwing = true;//换腿
	}
	if (swingLeft<maxAngel*-1) {
		isSwing = false;
	}
	RenderScene();
	glutPostRedisplay();
	if (!isStand) glutTimerFunc(value, timer, value);
}

void stop() {
	swingLeft = 0;
	swingRight = 0;
	isSwing = false;
	swingSmall = 0;
}

void keyEvent(unsigned char key, int x, int y)
{
	switch (key) {
	case 's':
		isStand = true;
		stop();
		break;
	case 'w':
		stop();
		direction = 180;
		maxAngel = 20;
		swingspeed = 1;
		speed = 0.01;
		if (isStand) 
			glutTimerFunc(20, timer, 20);// glutTimerFunc(毫秒数, 回调函数指针, 区别值);
		isStand = false;
		break;
	case 'b':
		stop();
		maxAngel = 20;
		swingspeed = 1;
		speed = 0.01;
		if (isStand)
			glutTimerFunc(20, timer2, 20);// glutTimerFunc(毫秒数, 回调函数指针, 区别值);
		isStand = false;
		break;
	default:
		break;
	}
}

void init(void)
{
	glEnable(GL_CULL_FACE); // 开启剪裁
	glCullFace(GL_BACK); // 裁掉背景
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 320);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Stickman");
	init();
	glutDisplayFunc(RenderScene);

	glutReshapeFunc(changeSize);

	glutKeyboardFunc(keyEvent);

	glutMainLoop();
	return 0;
}