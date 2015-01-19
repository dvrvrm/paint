#include "StdAfx.h"
#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include <sstream>
#include <math.h>
#include<iostream>
#include <fstream>
#define TOOLSWIDTH 100
using namespace std;
struct pixel {
	float red;
	float green;
	float blue;
};
void makePallete();
int mouseX1=0,mouseY1=0,mouseX2,mouseY2;
boolean selected=1;
int mouseClicked=0;
int design =-1;
int bpointsX[4],bpointsY[4],no_of_b=0;
int epointsX[2],epointsY[2],no_of_e=0;
int tpointsX[3],tpointsY[3],no_of_t=0;
int rpointsX[2],rpointsY[2],no_of_r,radius_in_rr=10;
int cpointsX[2],cpointsY[2],no_of_c=0;
float colorComponets[3]={1.0,0,0};
int windowWidth=1000,windowHeight=700;
GLuint fontOffset = glGenLists (128);

void display(void) {
	makePallete();
}

void printString(float x, float y, void *font, const char* str)
{  
  char *c;
  glColor3f(1.0f, 0.0f, 0.0f); 
  glRasterPos2f(x, y);
  for(int i=0;i<strlen(str);i++){
  glutBitmapCharacter(font, str[i]);
  }
  glColor3f(1.0f,1.0f,1.0f);
}

void makePallete()
{
	glBegin(GL_LINES);		// glBegin accepts a single argument that specifies in which of ten ways the vertices are interpreted
	glVertex3f (TOOLSWIDTH,0,0);
	glVertex3f (TOOLSWIDTH,windowHeight,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,50,0);
	glVertex3f (TOOLSWIDTH,50,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,100,0);
	glVertex3f (TOOLSWIDTH,100,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,150,0);
	glVertex3f (TOOLSWIDTH,150,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,200,0);
	glVertex3f (TOOLSWIDTH,200,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,250,0);
	glVertex3f (TOOLSWIDTH,250,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,300,0);
	glVertex3f (TOOLSWIDTH,300,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,350,0);
	glVertex3f (TOOLSWIDTH,350,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,400,0);
	glVertex3f (TOOLSWIDTH,400,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,450,0);
	glVertex3f (TOOLSWIDTH,450,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,500,0);
	glVertex3f (TOOLSWIDTH,500,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,550,0);
	glVertex3f (TOOLSWIDTH,550,0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f (0,600,0);
	glVertex3f (TOOLSWIDTH,600,0);
	glEnd();
	//for new pallete
	printString(3.0f, 10.0f, GLUT_BITMAP_TIMES_ROMAN_24, "New");
	//for line
	printString(3.0f, 60.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Line");
	// for curve
	printString(3.0f, 110.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Curve");
	//for ellipse
	printString(3.0f, 160.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Elipse");
	//for triangle
	printString(3.0f, 210.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Triangle");
	//for hexagon
	printString(3.0f, 260.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Hexagon");
	//for rounded rectangle
	printString(3.0f, 310.0f, GLUT_BITMAP_TIMES_ROMAN_24, "RRect");
	// for crop
	printString(3.0f, 360.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Crop");
	//for erase
	printString(3.0f, 410.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Erase");
	//for save
	printString(3.0f, 460.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Save");
	//for open
	printString(3.0f, 510.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Open");
	glFlush();
}

void moveMouse(int x,int y)
{	
	static int moveX1=0,moveY1=0;
	//cout << "move";
	if(mouseClicked==1)
	{
		if(design==1)
		{
			glColor3f (0,0,0);
			glBegin(GL_LINES);
			glVertex3f (mouseX1,windowHeight-mouseY1,0);
			glVertex3f (moveX1,windowHeight-moveY1,0);
			glEnd();
			glFlush();
			glColor3f (1.0,1.0,1.0);
			glBegin(GL_LINES);
			glVertex3f (mouseX1,windowHeight-mouseY1,0);
			glVertex3f (x,windowHeight-y,0);
			glEnd();
			glFlush();
			moveX1=x;
			moveY1=y;
		}
	}
}

void floodFill(int x,int y)
{
	//cout << ".................";
	unsigned char pixel[3];
	glReadPixels(x,y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
	float r = (float)pixel[0]/255;
	float g = (float)pixel[0]/255;
	float b = (float)pixel[0]/255;
	//cout << "\nR = "<<r<<" G= "<<g<<" B = "<<b<<"\n";
	//cout << "\nCR = "<<colorComponets[0]<<"\n";
	if(colorComponets[0]==r && colorComponets[1]==g && colorComponets[2]==b)
	{
		return;
	}
	else if(!(r==0 && g==0 && b==0))
	{
		return ;
	}
	glColor3f(colorComponets[0],colorComponets[1],colorComponets[2]);
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
	glFlush();
	floodFill(x+1,y);
	floodFill(x,y+1);
	floodFill(x,y-1);
	floodFill(x-1,y);
	//cout << ".................";
	return ;
}
void mouseclick(int button, int state,int x, int y)
{
if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && selected==1)
{
	mouseClicked=1;
	mouseX1=x;
	mouseY1=y;
}
else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP && selected==1 && mouseClicked==1)
{
	mouseX2=x;
	mouseY2=y;
	if(mouseX1<TOOLSWIDTH)
	{
		if((windowHeight-mouseY1)<50)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f );				// for cANVAS
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			mouseClicked=0;
			makePallete();
		}
		else if((windowHeight-mouseY1)>50 && (windowHeight-mouseY1)<100)
		{
			design=1;			// for line
		}
		else if((windowHeight-mouseY1)>100 && (windowHeight-mouseY1)<150)
		{
			design=2;			// for bezier curve
		}
		else if((windowHeight-mouseY1)>150 && (windowHeight-mouseY1)<200)
		{
			design=3;			// for ellipse
		}
		else if((windowHeight-mouseY1)>200 && (windowHeight-mouseY1)<250)
		{
			design=4;			// for triangle
		}
		else if((windowHeight-mouseY1)>250 && (windowHeight-mouseY1)<300)
		{
			design=5;			// for hexagon
		}
		else if((windowHeight-mouseY1)>300 && (windowHeight-mouseY1)<350)
		{
			design=6;			// for rounded rectangle
		}
		else if((windowHeight-mouseY1)>350 && (windowHeight-mouseY1)<400)
		{
			design=7;			// for crop
		}
		else if((windowHeight-mouseY1)>400 && (windowHeight-mouseY1)<450)
		{
			design=8;			// for erase
		}
		else if((windowHeight-mouseY1)>450 && (windowHeight-mouseY1)<500)
		{
			design=9;			// for save
			FILE *fp;
			char fname[10];
			cout << "Enter the name of file u want to save ;-\n";
			cin >> fname;
			std::ofstream outfile (fname);
		    unsigned char pixel[3];
			for(int i=TOOLSWIDTH;i<windowWidth;i++)
			{
				for(int j=0;j<windowHeight;j++)
				{
					string r,g,b;
					string lines;
				    glReadPixels(i,j, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
					ostringstream convert;   // stream used for the conversion
					convert << (int)pixel[0];
					r = convert.str();
					ostringstream convert2;
					convert2 << (int)pixel[1];
					g = convert2.str();
					ostringstream convert3;
					convert3 << (int)pixel[2];
					b = convert3.str();
						lines = r+" "+g+" "+b+"\n";
						outfile << lines;
					
				}
			}
			outfile.close();
			cout << "\nsaving done\n";
		}
		else if((windowHeight-mouseY1)>500 && (windowHeight-mouseY1)<550)
		{
			design=10;			// for open
			string fname,line;
			cout << "Enter the name of the file u want to open:-\n";
			getline(cin,fname);
			ifstream myfile (fname);
			
			//glClearColor(0.0f, 0.0f, 0.0f, 1.0f );				// for 
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			int xc=TOOLSWIDTH,yc=0;
			string r,g,b;
			while ( getline (myfile,line) )
		    {
				int i=0,start=0;
				while(line[i]!=' ' && line[i]!='\n')
					i++;
			  r= line.substr(0,i);
			  start=i+1;
			  i=0;
			  while(line[i]!=' ' && line[i]!='\n')
					i++;
			  g= line.substr(start,i);
			  start=start+i+1;
			  i=0;
			  while(line[i]!=' ' && line[i]!='\n')
					i++;
			  b= line.substr(start,i);
			  float red,green,blue;
			  red = (stof(r))/255;
			  green = (stof(g))/255;
			  blue = (stof(b))/255;
			   glColor3f(red,green,blue);
			  glBegin(GL_POINTS);
			  glVertex2f(xc,yc);
			  glEnd();
			  glFlush();
			  yc++;
			  //cout << xc <<" ";
			  if(yc==700)
			  {
				  xc++;
				  yc=0;
				 // cout << yc<< " ";
			  }
			}
			cout << "completed";
			myfile.close();
		}
		else if((windowHeight-mouseY1)>550 && (windowHeight-mouseY1)<600)
		{
			design=10;			// for color
			
		}
	}
	else
	{
		mouseClicked=0;
		if(design==2)
		{
			if(no_of_b<4)
			{
				no_of_e=0;
				no_of_r=0;
				no_of_t=0;
				no_of_c=0;

				bpointsX[no_of_b]=mouseX1;
				bpointsY[no_of_b]=windowHeight-mouseY1;
				glBegin(GL_POINTS);
				glVertex2i(mouseX1,windowHeight-mouseY1);
				glEnd();
				glFlush();
				no_of_b++;
			}
			if(no_of_b==4)
			{
				no_of_b=0;
				int ax,bx,cx,ay,by,cy;
				cx = 3*(bpointsX[1] - bpointsX[0]);
				bx = 3*(bpointsX[2] - bpointsX[1]) - cx;
				ax = bpointsX[3] - bpointsX[0] - cx - bx;

				cy = 3 *(bpointsY[1] - bpointsY[0]);
				by = 3 *(bpointsY[2] - bpointsY[1]) - cy;
				ay = bpointsY[3] - bpointsY[0] - cy - by;
				for(float t=0;t<1;t=t+0.001)
				{
					float xval =  ax*t*t*t + bx*t*t + cx*t + bpointsX[0];
					float yval = ay*t*t*t + by*t*t + cy*t + bpointsY[0];
					glBegin(GL_POINTS);
						glVertex2f(xval,yval);
					glEnd();
					glFlush();
				}
			}
		}
		if(design==3)
		{
			if(no_of_e<2)
			{
								no_of_c=0;
				no_of_r=0;
				no_of_t=0;
				no_of_b=0;

				epointsX[no_of_e]=mouseX1;
				epointsY[no_of_e]=windowHeight-mouseY1;
				glBegin(GL_POINTS);
				glVertex2f(epointsX[no_of_e],epointsY[no_of_e]);
				glEnd();
				glFlush();
				no_of_e++;
			}
			if(no_of_e==2)
			{
				no_of_e=0;
				int a = abs(epointsX[1]-epointsX[0])/2;
				int b = abs(epointsY[1]-epointsY[0])/2;
				int centX = (epointsX[0]+epointsX[1])/2;
				int centY = (epointsY[0]+epointsY[1])/2;
				for(float t=0;t<2*3.14;t=t+0.001)
				{
					float xval = centX + a*cos(t);
					float yval = centY + b* sin(t);
					glBegin(GL_POINTS);
						glVertex2f(xval,yval);
					glEnd();
					glFlush();
				}

			}
		}
		if(design==4)
		{
			if(no_of_t<3)
			{
								no_of_e=0;
				no_of_r=0;
				no_of_c=0;
				no_of_b=0;

				tpointsX[no_of_t]=x;
				tpointsY[no_of_t]=windowHeight-y;
				no_of_t++;
				glBegin(GL_POINTS);
				glVertex2f(x,windowHeight-y);
				glEnd();
				glFlush();
			}
			if(no_of_t==3)
			{
				no_of_t=0;
				glBegin(GL_LINE_LOOP);
				glVertex2f(tpointsX[0],tpointsY[0]);
				glVertex2f(tpointsX[1],tpointsY[1]);
				glVertex2f(tpointsX[2],tpointsY[2]);
				glEnd();
				glFlush();
			}
		}
		if(design==5)
		{
			if(no_of_t<6)
			{
				no_of_e=0;
				no_of_r=0;
				no_of_c=0;
				no_of_b=0;

				tpointsX[no_of_t]=x;
				tpointsY[no_of_t]=windowHeight-y;
				no_of_t++;
				glBegin(GL_POINTS);
				glVertex2f(x,windowHeight-y);
				glEnd();
				glFlush();
			}
			if(no_of_t==6)
			{
				no_of_t=0;
				glBegin(GL_LINE_LOOP);
				glVertex2f(tpointsX[0],tpointsY[0]);
				glVertex2f(tpointsX[1],tpointsY[1]);
				glVertex2f(tpointsX[2],tpointsY[2]);
				glVertex2f(tpointsX[3],tpointsY[3]);
				glVertex2f(tpointsX[4],tpointsY[4]);
				glVertex2f(tpointsX[5],tpointsY[5]);
				glEnd();
				glFlush();
			}
		}
		if(design==6)
		{
			if(no_of_r<2)
			{
				no_of_e=0;
				no_of_c=0;
				no_of_t=0;
				no_of_b=0;

				rpointsX[no_of_r]=x;
				rpointsY[no_of_r]=windowHeight-y;
				glBegin(GL_POINTS);
				glVertex2f(rpointsX[no_of_r],rpointsY[no_of_r]);
				glEnd();
				glFlush();
				no_of_r++;
			}
			if(no_of_r==2)
			{
				no_of_r=0;
				int minX,minY,maxX,maxY;
				if(rpointsX[0]<rpointsX[1])
				{
					minX=rpointsX[0];
					maxX=rpointsX[1];
				}
				else
				{
					minX=rpointsX[1];
					maxX=rpointsX[0];
				}
				if(rpointsY[0]<rpointsY[1])
				{
					minY=rpointsY[0];
					maxY=rpointsY[1];
				}
				else
				{
					minY=rpointsY[1];
					maxY=rpointsY[0];
				}
				glBegin(GL_LINES);
				glVertex2f(minX+radius_in_rr,minY);
				glVertex2f(maxX-radius_in_rr,minY);
				glEnd();
				glBegin(GL_LINES);
				glVertex2f(maxX,minY+radius_in_rr);
				glVertex2f(maxX,maxY-radius_in_rr);
				glEnd();
				glBegin(GL_LINES);
				glVertex2f(maxX-radius_in_rr,maxY);
				glVertex2f(minX+radius_in_rr,maxY);
				glEnd();
				glBegin(GL_LINES);
				glVertex2f(minX,maxY-radius_in_rr);
				glVertex2f(minX,minY+radius_in_rr);
				glEnd();
				glFlush();
				for(float t=0;t<3.14/2;t=t+0.0001)
				{
					float xval = maxX-radius_in_rr + radius_in_rr*cos(t);
					float yval = maxY-radius_in_rr + radius_in_rr*sin(t);
					glBegin(GL_POINTS);
					glVertex2f(xval,yval);
					glEnd();
				}
				for(float t=3.14/2;t<3.14;t=t+0.0001)
				{
					float xval = minX+radius_in_rr + radius_in_rr*cos(t);
					float yval = maxY-radius_in_rr + radius_in_rr*sin(t);
					glBegin(GL_POINTS);
					glVertex2f(xval,yval);
					glEnd();
				}
				for(float t=3.14;t<3*3.14/2;t=t+0.0001)
				{
					float xval = minX+radius_in_rr + radius_in_rr*cos(t);
					float yval = minY+radius_in_rr + radius_in_rr*sin(t);
					glBegin(GL_POINTS);
					glVertex2f(xval,yval);
					glEnd();
				}
				for(float t=3*3.14/2;t<2*3.14;t=t+0.0001)
				{
					float xval = maxX-radius_in_rr + radius_in_rr*cos(t);
					float yval = minY+radius_in_rr + radius_in_rr*sin(t);
					glBegin(GL_POINTS);
					glVertex2f(xval,yval);
					glEnd();
				}
				glFlush();
			}
		}
		if(design==7)
		{
			if(no_of_c<2)
			{
				no_of_e=0;
				no_of_r=0;
				no_of_t=0;
				no_of_b=0;

				cpointsX[no_of_c]=x;
				cpointsY[no_of_c]=windowHeight-y;
				glBegin(GL_POINTS);
				glVertex2f(x,windowHeight-y);
				glEnd();
				glFlush();
				no_of_c++;
			}
			if(no_of_c==2)
			{
				no_of_c=0;
				int minX,minY,maxX,maxY;
				if(cpointsX[0]<cpointsX[1])
				{
					minX=cpointsX[0];
					maxX=cpointsX[1];
				}
				else
				{
					minX=cpointsX[1];
					maxX=cpointsX[0];
				}
				if(cpointsY[0]<cpointsY[1])
				{
					minY=cpointsY[0];
					maxY=cpointsY[1];
				}
				else
				{
					minY=cpointsY[1];
					maxY=cpointsY[0];
				}
				for(int h=TOOLSWIDTH;h<minX;h++)
				{
					for(int k=0;k<windowHeight;k++)
					{
						glColor3f(0,0,0);
						glBegin(GL_POINTS);
						glVertex2f(h,k);
						glEnd();
					}
				}
				for(int h=maxX;h<windowWidth;h++)
				{
					for(int k=0;k<windowHeight;k++)
					{
						glColor3f(0,0,0);
						glBegin(GL_POINTS);
						glVertex2f(h,k);
						glEnd();
					}
				}
				for(int k=0;k<minY;k++)
				{
					for(int h=minX;h<maxX;h++)
					{
						glColor3f(0,0,0);
						glBegin(GL_POINTS);
						glVertex2f(h,k);
						glEnd();
					}
				}
				for(int k=maxY;k<windowHeight;k++)
				{
					for(int h=minX;h<maxX;h++)
					{
						glColor3f(0,0,0);
						glBegin(GL_POINTS);
						glVertex2f(h,k);
						glEnd();
					}
				}
				glFlush();
				glColor3f(1,1,1);
			}
		}
		if(design==8)
		{
			int minX=x;
			int minY=windowHeight-y;
			for(int h=minX;h<minX+50;h++)
			{
				for(int k=minY;k<minY+50;k++)
				{
						glColor3f(0,0,0);
						glBegin(GL_POINTS);
						glVertex2f(h,k);
						glEnd();
				}
			}
			glFlush();
			glColor3f(1,1,1);
		}
		if(design==10)
		{
			floodFill(x,windowHeight-y);
		}
	}
}

//glutPostRedisplay();
}


void init (void) {
glClearColor (0.0, 0.0, 0.0, 0.0);
/* select clearing color */
glMatrixMode(GL_PROJECTION);
/* initialize viewing values */
glLoadIdentity();
glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 0.0);		//windowWidth and windowHeight are global variables
}
/* Declare initial window size, position, and display mode. Open window with
"hello in its title bar. Call initialization routines. Register callback function
to display graphics. Enter main loop and process events. */
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize (windowWidth, windowHeight);
glutInitWindowPosition (50, 0);
glutCreateWindow ("Paint");
init ();
glutDisplayFunc(display);
glutMouseFunc(mouseclick);

glutMotionFunc(moveMouse);
glutMainLoop();
return 0; /* ANSI C requires main to return int. */
}
