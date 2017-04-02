// stickman.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#define GLEW_STATIC
#include <stdio.h>    
#include <string.h>    
#include <stdlib.h>   
#include <math.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>


GLfloat swingLeft = 0;  //�ڶ��Ƕ�
GLfloat swingRight = 0;
GLint maxAngel;//���ڶ���
GLint swingspeed;//���Ȱڶ����ٶ�
GLfloat speed;//ǰ���ٶ�
GLfloat direction;
GLfloat moveX = 0, moveZ = 0;//��ǰλ��
bool isStand = true;
bool isSwing = false;  //�ڱ�
GLfloat swingSmall = 0;

/**
�����ڴ�С�ı�ʱ
**/
void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = 1.0f*w / h;
	//�����ӿ�Ϊ�������ڴ�С
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//���ÿ��ӿռ�
	gluPerspective(100, ratio, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -8.0);
}


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);   //������ɫģʽ

	//������
	glBegin(GL_QUADS);	
	//��glColor3b()��Ҫ�������byte���ͣ�������ֵ��Χ��-128-127��Ҳ�����з�������
	//����255������Խ���ˣ�255��������൱��-128���ѹֲ���찡��
	glColor3b(37, 37, 37);
	glVertex3f(-10.0f, -3.0f, 4.0f);
	glVertex3f(10.0f, -3.0f, 4.0f);
	glVertex3f(10.0f, -3.0f, -4.0f);
	glVertex3f(-10.0f, -3.0f, -4.0f);
	glEnd();

	//������
	glPushMatrix();
	glTranslatef(moveX, 0.0, moveZ); //ƽ��ԭ�㣨0��0��0��������
	glRotatef(180, 0.0, 1.0, 0.0);
	glTranslatef(0.325, 0.0, 0.0);
	glRotatef(swingRight, 1.0, 0.0, 0.0);
	//�µ�����ϵ���Ҵ���
	glTranslatef(0.0, -0.6, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	//���Ҵ���
	glPushMatrix();
	glScalef(0.4, 1.0, 0.4);  //ģ�����ţ������˵Ĵ�����һ��0.4*1*0.4��������
	glutSolidCube(1);
	glPopMatrix();

	glTranslatef(0.0, -0.5, 0.0);
	glRotatef(swingSmall, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	//����С��
	glPushMatrix();
	glScalef(0.3, 1.0, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();

	//������
	glPushMatrix();
	//������ϵƽ������ת
	glTranslatef(moveX, 0.0, moveZ);//ǰ��
	glRotatef(180, 0.0, 1.0, 0.0);//ת��
	//����
	glTranslatef(-0.325, 0.0, 0.0);
	glRotatef(swingLeft, 1.0, 0.0, 0.0); //swingLeft��ʾ�������ת�Ƕ�
	//��Ϊ��ת�ȵ�ʱ�������Ŵ��ȸ�����ת�������Ȱ�����ϵ���ƣ���ת
	glTranslatef(0.0, -0.5, 0.0);//�ٰ�����ϵ���Ƶ�����Ҫ��ԭ��
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(0.4, 1.0, 0.4);//������һ��0.4*1*0.4��������
	glutSolidCube(1.0);
	glPopMatrix();
	//��С��
	glTranslatef(0.0, -0.5, 0.0);
	glRotatef(swingSmall, 1.0, 0.0, 0.0); //С�Ȱڶ�swingsmall��
	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(0.3, 1.0, 0.3);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	//��ջ

	//������
	glPushMatrix();
	glTranslatef(moveX, 0.0, moveZ);
	glRotatef(180, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.35, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glutSolidSphere(0.9f, 20, 20);
	glPopMatrix();
	//ͷ��
	glTranslatef(0.0, 1.1, 0.0);
	glColor3f(0.9, 0.9, 0.9);
	glPushMatrix();
	glutSolidSphere(0.5f, 20, 20);
	glPopMatrix();

	//�۾�
	glTranslatef(0.12, 0.1, -0.25);//������
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glutSolidSphere(0.05f, 20, 20);
	glPopMatrix();

	glTranslatef(-0.24, 0.0, 0.0);//�����ۣ���������ƽ��0.24��
	glColor3f(0.2, 0.2, 0.2);
	glPushMatrix();
	glutSolidSphere(0.05f, 20, 20);
	glPopMatrix();

	//���
	glTranslatef(0.125, -0.25, 0.0);
	glColor3f(0.8, 0.2, 0.2);
	glPushMatrix();
	glScalef(0.3, 0.1, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();



	glPopMatrix();
	//��ջ

	//���ұ�
	glPushMatrix();
	glTranslatef(moveX, 0.0, moveZ);
	glRotatef(180, 0.0, 1.0, 0.0);
	
	glTranslatef(0.85, 0.3, 0.0);
	glRotatef(swingLeft, 1.0, 0.0, 0.0);  //�ұ۵İڶ��Ƕ���������ͬ
	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(1.0,1.0, 1.0);
	glPushMatrix();
	glScalef(0.25, 1.3, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();
	glPopMatrix();
	

	//�����
	glPushMatrix();
	glTranslatef(moveX, 0.0, moveZ);
	glRotatef(180, 0.0, 1.0, 0.0);
	
	glTranslatef(-0.85, 0.3, 0.0);
	glRotatef(swingRight, 1.0, 0.0, 0.0);  //��۵İڶ��Ƕ���������ͬ
	glTranslatef(0.0, -0.5, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(0.25, 1.3, 0.4);
	glutSolidCube(1.0);
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

//ʱ�亯��,��ʱˢ��
void timer(int value)
{
	moveX = moveX - speed*sin(direction / 360 * 3.14 * 2);
	moveZ = moveZ - speed*cos(direction / 360 * 3.14 * 2);
	if (!isSwing) {//�Ӿ�ֹ��ʼ��������ǰ
		swingLeft = (swingLeft + swingspeed);
		swingRight = (swingRight - swingspeed);
		if (swingLeft>0) {//�������ǰ��С�������� 
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
		isSwing = true;//����
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
	if (!isSwing) {//�Ӿ�ֹ��ʼ��������ǰ
		swingLeft = (swingLeft + swingspeed);
		swingRight = (swingRight - swingspeed);
		if (swingLeft>0) {//�������ǰ��С�������� 
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
		isSwing = true;//����
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
			glutTimerFunc(20, timer, 20);// glutTimerFunc(������, �ص�����ָ��, ����ֵ);
		isStand = false;
		break;
	case 'b':
		stop();
		maxAngel = 20;
		swingspeed = 1;
		speed = 0.01;
		if (isStand)
			glutTimerFunc(20, timer2, 20);// glutTimerFunc(������, �ص�����ָ��, ����ֵ);
		isStand = false;
		break;
	default:
		break;
	}
}

void init(void)
{
	glEnable(GL_CULL_FACE); // ��������
	glCullFace(GL_BACK); // �õ�����
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