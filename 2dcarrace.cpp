#include<GL/glut.h>
#include<stdio.h>

#include<stdlib.h>
#include<math.h>
#define PI 3.14159/180
int i,q,n;
float xpos=0.5,ypos=0.5;
float score = 0.0;//for score counting
int screen = 0;
bool collide = false;//check if car collide to make game over
static int submenu_id,menu_id;
void *currentfont;
char buffer[10];
int s=0,p=0;
int count=0,night=0,pause_count=0;
int vehicleX = 200, vehicleY = 70;   
int ovehicleX[4], ovehicleY[4];
int divx = 250, divy = 4, movd;
typedef struct
{
	float x;
	float y;
	}circle;
circle c;

void drawText(char ch[],int xpos, int ypos)//draw the text for score and game over
{
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; ch[i]!='\0'; i++)
    {
    	glutBitmapCharacter(currentfont, ch[i]);//font used here, may use other font also
    }
}

void drawTextNum(char ch[],int numtext,int xpos, int ypos)//counting the score
{
    int len;
    int k;
    k = 0;
    i=0;
    while(ch[i]!='\0')
    {
    	i+=1;
    	len+=1;
    	
    }
    len=numtext-len;
    //len = numtext - strlen (ch);
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <=numtext - 1; i++)
    {
    if ( i < len )
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
    else
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
        k++;
    }
     
    }
}
 
 
 
void ovpos()
{

if(night==0){

    glClearColor(0,0,1,0);}
else{
    
    glClearColor(0.1,0.1,0.1,0);
}
  //  if(s==0){
	for(i = 0; i < 4; i++)
	{
	
    if(rand()%3 == 0)
    	ovehicleX[i] = 200;
    	
    else if(rand() % 2 == 0)
    {
        ovehicleX[i] = 300;
    }
    else
    {
        ovehicleX[i] = 250;
    }
    ovehicleY[i] = 1000 - i * 300;
    }
     
   // }
    /*else{
    for(i = 0; i < 8; i++){
    if(rand()%3 == 0)
    	ovehicleX[i] = 200;
    	
    else if(rand() % 2 == 0)
    {
        ovehicleX[i] = 400;
    }
    else
    {
        ovehicleX[i] = 300;
    }
    ovehicleY[i] = 1000 - i * 600;
    }
    
    
  
    }*/  
}


void drawRoad()
{
    glBegin(GL_QUADS); 
    if(night==0)
        glColor3f(0.5,0.5,0.5);
    else
    	glColor3f(0.3,0.3,0.3);
        glVertex2f(250 - 100, 500);
        glVertex2f(250 - 100, 0);
        glVertex2f(250 + 100, 0);
        glVertex2f(250 + 100, 500);
    glEnd();
    glPointSize(15);
    
    glBegin(GL_LINES);
    glColor3f(1,0.7,0.1);
    	glVertex2f(250 - 93, 500);
        glVertex2f(250 - 93, 0);
        glEnd();
 
	glBegin(GL_LINES);
    glColor3f(1,0.7,0.1);
    	glVertex2f(250 + 93, 500);
        glVertex2f(250 + 93, 0);
        glEnd();
    glBegin(GL_LINES);
    glColor3f(1,0.7,0.1);
    	glVertex2f(250 - 90, 500);
        glVertex2f(250 - 90, 0);
        glEnd();
 
	glBegin(GL_LINES);
    glColor3f(1,0.7,0.1);
    	glVertex2f(250 + 90, 500);
        glVertex2f(250 + 90, 0);
        glEnd();        
}
 
 
void drawDivider()//black patch drawn in middle of road
{
    glLoadIdentity();
    glTranslatef(0, movd, 0);
    for(i = 1; i <= 10; i++)
    {
    	if(night==0)
    glColor3f(0, 0, 0);
    else
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_QUADS);
        glVertex2f(divx  - 5, divy * 15 * i + 18);
        glVertex2f(divx  - 5, divy * 15 * i - 18);
        glVertex2f(divx  + 5, divy * 15 * i - 18);
        glVertex2f(divx  + 5, divy * 15 * i + 18);
    glEnd();
    }
    glLoadIdentity();
}

void drawVehicle()//car for racing
{
    
   
    glPointSize(10.0);
    if(night==1){
    glBegin(GL_QUADS);//headlights
        glColor3f(1,1,1);
        
        glVertex2f(vehicleX - 20, vehicleY + 58);
        glVertex2f(vehicleX - 26, vehicleY + 85);
        glVertex2f(vehicleX - 11, vehicleY + 85 );
        glVertex2f(vehicleX - 17, vehicleY + 58);
    glEnd();
    glBegin(GL_QUADS);//headlights
        glColor3f(1,1,1);
        
        glVertex2f(vehicleX + 20, vehicleY + 58);
        glVertex2f(vehicleX + 26, vehicleY + 85);
        glVertex2f(vehicleX + 11, vehicleY + 85 );
        glVertex2f(vehicleX + 17, vehicleY + 58);
    glEnd();
    }
    glBegin(GL_LINE_LOOP);//body
    if(night==1)
        glColor3f(0.0,0.0,0.0);
        else
        glColor3f(1,1,1);
        glVertex2f(vehicleX, vehicleY +63);
        glVertex2f(vehicleX - 20, vehicleY +58);
        
        glVertex2f(vehicleX - 20, vehicleY -46);
        glVertex2f(vehicleX -18, vehicleY - 60);
        glVertex2f(vehicleX + 18, vehicleY -60);
        glVertex2f(vehicleX + 20, vehicleY -46);
        glVertex2f(vehicleX + 20, vehicleY +58);
    glEnd();
    
    glBegin(GL_POLYGON);//body
    if(night==0)
        glColor3f(1.0,0.0,0.0);
        else
        glColor3f(0.15,0.15,0.15);
        glVertex2f(vehicleX, vehicleY +63);
        glVertex2f(vehicleX - 20, vehicleY +58);
        
        glVertex2f(vehicleX - 20, vehicleY -46);
        glVertex2f(vehicleX -18, vehicleY - 60);
        glVertex2f(vehicleX + 18, vehicleY -60);
        glVertex2f(vehicleX + 20, vehicleY -46);
        glVertex2f(vehicleX + 20, vehicleY +58);
    glEnd();
    
    
    glBegin(GL_QUADS);//middle
        if(night==0)
        glColor3f(1.0,0.0,0.0);
        else
        glColor3f(0.15,0.15,0.15);
        glVertex2f(vehicleX - 15, vehicleY + 20);
        glVertex2f(vehicleX - 15, vehicleY - 20);
        glVertex2f(vehicleX + 15, vehicleY - 20);
        glVertex2f(vehicleX + 15, vehicleY + 20);
        
    glEnd();
    
    glBegin(GL_POLYGON);//front glass
        glColor3f(0.0,0.0,0.0);
        glVertex2f(vehicleX - 13, vehicleY + 38);
        glVertex2f(vehicleX - 18, vehicleY + 35);
        glVertex2f(vehicleX - 15, vehicleY + 20);
        glVertex2f(vehicleX + 15, vehicleY + 20);
        glVertex2f(vehicleX + 18, vehicleY + 35);
        glVertex2f(vehicleX + 13, vehicleY + 38);
        
    glEnd();
    
    glBegin(GL_POLYGON);//back glass
        glColor3f(0.0,0.0,0.0);
        glVertex2f(vehicleX - 15, vehicleY - 20);
        glVertex2f(vehicleX - 18, vehicleY - 40);
        glVertex2f(vehicleX - 10, vehicleY -46);
        glVertex2f(vehicleX + 10, vehicleY - 46);
        glVertex2f(vehicleX + 18, vehicleY -40);
        glVertex2f(vehicleX + 15, vehicleY -20);
        
    glEnd();
    glBegin(GL_QUADS);//left side
        glColor3f(0.0,0.0,0.0);
        glVertex2f(vehicleX - 15, vehicleY + 20);
        glVertex2f(vehicleX - 18, vehicleY + 35);
        glVertex2f(vehicleX - 18, vehicleY - 40);
        glVertex2f(vehicleX - 15, vehicleY - 20);
        
    glEnd();
    
    glBegin(GL_QUADS);//right side
        glColor3f(0.0,0.0,0.0);
        glVertex2f(vehicleX + 15, vehicleY + 20);
        glVertex2f(vehicleX + 18, vehicleY + 35);
        glVertex2f(vehicleX + 18, vehicleY - 40);
        glVertex2f(vehicleX + 15, vehicleY - 20);
        
    glEnd();
    
    
    glBegin(GL_LINE_LOOP);//left side
        if(night==0)
        glColor3f(1.0,0.0,0.0);
        else
        glColor3f(1,1,1);
        glVertex2f(vehicleX - 15, vehicleY + 20);
        glVertex2f(vehicleX - 18, vehicleY + 35);
        glVertex2f(vehicleX - 18, vehicleY - 40);
        glVertex2f(vehicleX - 15, vehicleY - 20);
        
    glEnd();
    
    glBegin(GL_LINE_LOOP);//right side
        if(night==0)
        glColor3f(1.0,0.0,0.0);
        else
        glColor3f(1,1,1);
        glVertex2f(vehicleX + 15, vehicleY + 20);
        glVertex2f(vehicleX + 18, vehicleY + 35);
        glVertex2f(vehicleX + 18, vehicleY - 40);
        glVertex2f(vehicleX + 15, vehicleY - 20);
        
    glEnd();
    
    
    
    
    

 } 
  
void drawOVehicle()//other cars
{
    /*if(s==1){
    for(i=0;i<4;i++){
    if(ovehicleX[i]==250){
    ovehicleX[i]= 300;
    }
    n=8;
    }
    
    }
    else*/
    n=4;
   
    for(i = 0; i < n; i++)
    {
    glPointSize(10.0);
    if(night==1){
    glBegin(GL_QUADS);//headlights
        glColor3f(1,1,0.3);
        
        glVertex2f(ovehicleX[i] - 20, ovehicleY[i] - 58);
        glVertex2f(ovehicleX[i] - 26, ovehicleY[i] - 85);
        glVertex2f(ovehicleX[i] - 11, ovehicleY[i] - 85 );
        glVertex2f(ovehicleX[i] - 17, ovehicleY[i] - 58);
    glEnd();
    glBegin(GL_QUADS);//headlights
        glColor3f(1,1,0.3);
        
        glVertex2f(ovehicleX[i] + 20, ovehicleY[i] - 58);
        glVertex2f(ovehicleX[i] + 26, ovehicleY[i] - 85);
        glVertex2f(ovehicleX[i] + 11, ovehicleY[i] - 85 );
        glVertex2f(ovehicleX[i] + 17, ovehicleY[i] - 58);
    glEnd();
    
    }
    glBegin(GL_LINE_LOOP);//body
    if(night==0)
        glColor3f(0.0,0.0,0.0);
        else
        glColor3f(1,1,1);
        glVertex2f(ovehicleX[i], ovehicleY[i] -63);
        glVertex2f(ovehicleX[i] - 20, ovehicleY[i] -58);
        
        glVertex2f(ovehicleX[i] - 20, ovehicleY[i] +46);
        glVertex2f(ovehicleX[i] -18, ovehicleY[i] + 55);
        glVertex2f(ovehicleX[i] + 18, ovehicleY[i] +55);
        glVertex2f(ovehicleX[i] + 20, ovehicleY[i] +46);
        glVertex2f(ovehicleX[i] + 20, ovehicleY[i] -58);
    glEnd();
    
    glBegin(GL_POLYGON);//car
        if(night==0)
        glColor3f(0.5,0.2,0);
        else
        glColor3f(0.45,0.45,0.45);
        glVertex2f(ovehicleX[i], ovehicleY[i] -63);
        glVertex2f(ovehicleX[i] - 20, ovehicleY[i] -58);
        
        glVertex2f(ovehicleX[i] - 20, ovehicleY[i] +46);
        glVertex2f(ovehicleX[i] - 18, ovehicleY[i] +55);
        glVertex2f(ovehicleX[i] + 18, ovehicleY[i] +55);
        glVertex2f(ovehicleX[i] + 20, ovehicleY[i] +46);
        glVertex2f(ovehicleX[i] + 20, ovehicleY[i] -58);
    glEnd();
    
    
    glBegin(GL_QUADS);//middle
        if(night==0)
        glColor3f(0.5,0.2,0);
        else
        glColor3f(0.45,0.45,0.45);
        glVertex2f(ovehicleX[i] - 15, ovehicleY[i] + 20);
        glVertex2f(ovehicleX[i] - 15, ovehicleY[i] - 20);
        glVertex2f(ovehicleX[i] + 15, ovehicleY[i] - 20);
        glVertex2f(ovehicleX[i] + 15, ovehicleY[i] + 20);
        
    glEnd();
    
    glBegin(GL_POLYGON);//front glass
        glColor3f(0.0,0.0,0.0);
        glVertex2f(ovehicleX[i] + 13, ovehicleY[i] - 38);
        glVertex2f(ovehicleX[i] + 18, ovehicleY[i] - 35);
        glVertex2f(ovehicleX[i] + 15, ovehicleY[i] - 20);
        glVertex2f(ovehicleX[i] - 15, ovehicleY[i] - 20);
        glVertex2f(ovehicleX[i] - 18, ovehicleY[i] - 35);
        glVertex2f(ovehicleX[i] - 13, ovehicleY[i] - 38);
        
    glEnd();
    
    glBegin(GL_POLYGON);//back glass
        glColor3f(0.0,0.0,0.0);
        glVertex2f(ovehicleX[i] + 15, ovehicleY[i] + 20);
        glVertex2f(ovehicleX[i] + 18, ovehicleY[i] + 40);
        glVertex2f(ovehicleX[i] + 10, ovehicleY[i] +46);
        glVertex2f(ovehicleX[i] - 10, ovehicleY[i] + 46);
        glVertex2f(ovehicleX[i] - 18, ovehicleY[i] +40);
        glVertex2f(ovehicleX[i] - 15, ovehicleY[i] +20);
        
    glEnd();
    glBegin(GL_QUADS);//left side
        glColor3f(0.9,0.6,0.1);
        glVertex2f(ovehicleX[i] - 15, ovehicleY[i] + 20);
        glVertex2f(ovehicleX[i] - 18, ovehicleY[i] + 35);
        glVertex2f(ovehicleX[i] - 18, ovehicleY[i] - 40);
        glVertex2f(ovehicleX[i] - 15, ovehicleY[i] - 20);
       
    glEnd();
    
    glBegin(GL_QUADS);//right side
        glColor3f(0.9,0.6,0.1);
        glVertex2f(ovehicleX[i] + 15, ovehicleY[i] + 20);
        glVertex2f(ovehicleX[i] + 18, ovehicleY[i] + 35);
        glVertex2f(ovehicleX[i] + 18, ovehicleY[i] - 40);
        glVertex2f(ovehicleX[i] + 15, ovehicleY[i] - 20);
        
    glEnd();
    
    
    glBegin(GL_LINE_LOOP);//left side
        if(night==0)
        glColor3f(0,0,0);
        else
        glColor3f(1,1,1);
        glVertex2f(ovehicleX[i] - 15, ovehicleY[i] + 20);
        glVertex2f(ovehicleX[i] - 18, ovehicleY[i] + 35);
        glVertex2f(ovehicleX[i] - 18, ovehicleY[i] - 40);
        glVertex2f(ovehicleX[i] - 15, ovehicleY[i] - 20);
        
    glEnd();
    
    glBegin(GL_LINE_LOOP);//right side
        if(night==0)
        glColor3f(0,0,0);
        else
        glColor3f(1,1,1);
        glVertex2f(ovehicleX[i] + 15, ovehicleY[i] + 20);
        glVertex2f(ovehicleX[i] + 18, ovehicleY[i] + 35);
        glVertex2f(ovehicleX[i] + 18, ovehicleY[i] - 40);
        glVertex2f(ovehicleX[i] + 15, ovehicleY[i] - 20);
        
    glEnd();
    if(p==0){
    if(score>100){
    ovehicleY[i] = ovehicleY[i] - 12;
   
    }
    else if(score>300)
    ovehicleY[i] = ovehicleY[i] - 16;
    else if(score>500)
    ovehicleY[i] = ovehicleY[i] - 20;
    else 
    ovehicleY[i] = ovehicleY[i] - 8; 
    }
     if(s==0){
    if(ovehicleY[i] > (vehicleY - 40 - 60) && ovehicleY[i] < (vehicleY + 63 + 46) && ovehicleX[i] == vehicleX)
    {
        collide = true;
    }
    }
    else{
    
    if(vehicleX==200){
    if(ovehicleY[i] > (vehicleY - 40 - 60)*xpos && ovehicleY[i] < 80+(vehicleY + 63)*xpos && ovehicleX[i] == vehicleX)
    {
        collide = true;
    }
    }
    
    else if(vehicleX==300){
    if(ovehicleY[i] > (vehicleY - 40 - 60)*xpos && ovehicleY[i] < 80+(vehicleY + 63 )*xpos && ovehicleX[i] == vehicleX-50)
    {
        collide = true;
    }
    }
    else if(vehicleX==400){
    if(ovehicleY[i] > (vehicleY - 40 - 60)*xpos && ovehicleY[i] < 80+(vehicleY + 63)*xpos && ovehicleX[i] == vehicleX-100)
    {
        collide = true;
    }
    }
    
    /*if(ovehicleY[i] > (vehicleY - 40 - 60)*xpos && ovehicleY[i] < (vehicleY +80+ 63)*xpos && ovehicleX[i] == vehicleX)
    {
        collide = true;
    }*/
    }
    
    if(ovehicleY[i] < -75)
    { 
    //if(s==0){
        if(rand() % 2 == 0)
        {
            ovehicleX[i] = 200;
        }
        
        else if(rand() % 3 ==0)
        {
            ovehicleX[i] = 300;
        }
        else
            ovehicleX[i] = 250;
        
        
        if(score>150)
        	ovehicleY[i] = 700;
        else
        	ovehicleY[i] = 800;  
    //} 
    /*else{
    if(rand() % 2 == 0)
        {
            ovehicleX[i] = 200;
        }
        
        else if(rand() % 3 ==0)
        {
            ovehicleX[i] = 400;
        }
        else
            ovehicleX[i] = 300;
        
        
        if(score>150)
        	ovehicleY[i] = 700*2;
        else
        	ovehicleY[i] = 800*2;  
    
    
    }*/
    }
    }
    
}
 
void Specialkey(int key, int x, int y)//allow to use navigation key for movement of car
{
switch(key)
{
case GLUT_KEY_UP: 
	for(i = 0; i <4; i++)
             {
             
              ovehicleY[i] = ovehicleY[i] - 10;  
              //vehicleY = vehicleY + 10; 
             }
             movd = movd - 20;
             break;	
case GLUT_KEY_DOWN: 
	for(i = 0; i <4; i++)
             {
              ovehicleY[i] = ovehicleY[i] + 10; 
              //vehicleY = vehicleY - 10; 
               
             }
             movd = movd + 20;
             break;
case GLUT_KEY_LEFT: 
if(s==1){
vehicleX-=100;



}
else
vehicleX-=50;
			if(vehicleX<200)
			{
				collide=true;
				}

             break;
case GLUT_KEY_RIGHT: 

			if(s==1){
			vehicleX+=100;
			if(vehicleX>500)
			{
				collide=true;
				}
}
else{
			vehicleX+=50;
			if(vehicleX>300)
			{
				collide=true;
				}
}
             break;
      
			 
}

glutPostRedisplay();
}


void sc(int a)
{
	int i,j,k;
	i=a/100;
	j=a/10-i*10;
	k=a-j*10-i*100;
	glPushMatrix();

	glColor3f(0.0,0.0,0.0);

	glTranslated(10,300,0);
	glScaled(.5,.5,0);
    	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'S');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'c');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'o');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'r');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'e');
	glColor3f(1.0,0.0,1.0);
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)':');
	glColor3f(0.0,0.0,0.0);
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)i+48);
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)j+48);
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)k+48);
	glPopMatrix();
	drawText("Press s to start again",200,130);
	glutSwapBuffers();
}

 

void dispscore(int score)
{
	glLineWidth(5);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	sc(score);

	
	glPushMatrix();
	
	glColor3f(0,0,0);
	glTranslated(10,200,0);
	glScaled(.5,.5,0);
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'G');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'A');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'M');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'E');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'O');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'V');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'E');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'R');
	glPopMatrix();
	
	glutSwapBuffers();
	
	}
 void menufunc(int n){
 switch(n)
 {
 	case 10: night=1;
 	glLoadIdentity();
 	screen=2;
 	break;
 	
 	case 11: night=0;
 	screen=2;
 	break;
 	case 16: s=1;
 	break;
 	case 17: s=0;
 	break;
 	case 12: exit(0);
 	break;
 	case 100: break;
 }
 }
  void Normalkey(unsigned char key, int x, int y)
{
int xv;
    switch(key)
    {
    case '1':if(screen == 0)
             screen=1;
             break;
    case '2':if(screen == 1)
    
             screen=2;
             break;
    case 'q':
    exit(0);
    break;
    case 'b' : if(screen ==3)
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    		screen=1;
    		score=0;
    		ovpos();
    		ovpos();
    		ovpos();
    		vehicleX=200;
    		
    		collide=false;
    		glutSwapBuffers();
    		
    		break;
    	case 'p' :if(pause_count==0){
    	p=1;
    	
    	pause_count=1;
    	}
    	else{
    	p=0;
    	pause_count=0;
    	}
    	
    	break;
    	case 's': if(screen==3){
    		//glClear(GL_COLOR_BUFFER_BIT);
    		//glLoadIdentity();
    		ovpos();
    		ovpos();
    		ovpos();
    		screen=2;
    		score=0;
    		
    		vehicleX=200;
    		
    		collide=false;
    		//glutSwapBuffers();
    		glutPostRedisplay();
    		}
    		break;
    case 27:exit(0);
    break;
    case 13:screen=1;
    break;
    
    }
} 
 void setfont(void *font)
{
	currentfont=font;
}
 void frontscreen(void)
{
glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	setfont(GLUT_BITMAP_TIMES_ROMAN_24);
	drawText(" COMPUTER GRAPHICS AND VISUALIZATION MINI PROJECT",125,450);
	glColor3f(0.5,0.5,0.5);
	setfont(GLUT_BITMAP_HELVETICA_18);
	//drawText("---------------------------------------------------- ",135,440);
	glColor3f(0.5,0.7,0.7);
	drawText("GRAPHICAL IMPLEMENTATION OF TWO-D CAR RACING GAME ",150,420);
	setfont(GLUT_BITMAP_TIMES_ROMAN_24);
	drawText("------------------------------------",160,410);
	drawText("---------------------------------------------- ",135,440);

	glColor3f(0.5,0.7,0.5);
	setfont(GLUT_BITMAP_HELVETICA_18);
	drawText("PROJECT ASSOCIATES",200,350);
//	text(250,355,"_____________________");
	
	glColor3f(0.9,0.3,0.7);
	setfont(GLUT_BITMAP_TIMES_ROMAN_24);
	drawText("CHANDRASHEKAR G",50,310);
	drawText("CHANDRASHEKARMURTHY M",352,310);
	glColor3f(1.0,1.0,1.0);
	drawText("(1BI15CS039)",50,290);
	drawText("(1BI15CS040)",352,290);
	
	glColor3f(0.5,0.7,0.5);
	setfont(GLUT_BITMAP_HELVETICA_18);
	drawText("UNDER THE GUIDANCE OF",200,250);
//	text(250,265,"_____________________");

	glColor3f(0.9,0.3,0.7);
	setfont(GLUT_BITMAP_TIMES_ROMAN_24);
	drawText("D R NAGAMANI",352,200);
	drawText("Dr M. KEMPANNA",50,200);
	
	glColor3f(0.0,1.0,0.0);
	drawText("ASST.PROF",50,180);
	drawText("CSE DEPT.",50,160);
	drawText("ASST.PROF",352,180);
	drawText("CSE DEPT ",352,160);
	
	glColor3f(0.0,0.5,0.5);
	drawText("COMPUTER SCIENCE AND ENGINEERING",175,40);

	drawText("BANGALORE INSTITUTE OF TECHNOLOGY,VVPURAM",150,60);
	
	glColor3f(1,1,0);
	drawText("Press ENTER to begin",200,130);
	glFlush();
	glutSwapBuffers();
	 
glutKeyboardFunc(Normalkey);

//glFlush();
}
void display()
{
	
    if(screen == 0)
    {
    glClear(GL_COLOR_BUFFER_BIT);
    frontscreen();
    glutSwapBuffers();
    }
    else if(screen == 1)
    {
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1,1,1);
    drawText("Press 2 to continue", 170, 100);

    
    
    glutSwapBuffers();
    
    }
    else if(screen==3)
    {
    	
    	dispscore(int(score));
    	
    }
    else
    {
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    
    if(night==0)
    glClearColor(0.0,0.0,1.0,0.0);
    else
    glClearColor(0.2,0.2,0.2,0.0);
    if(count==0){
    
    ovpos();
    
    count=1;
    }
    drawRoad(); 
    drawDivider();
    drawOVehicle();
    if(s==1){
    glTranslated(0,0,0);
    glScalef(xpos,ypos,0);
    glTranslated(200,70,0);
    
    drawVehicle();
    
    //drawOVehicle();
    
    
    }
    else{
    drawVehicle();
    //drawOVehicle();
    }
    if(p==0){
    movd = movd - 16;
    if(movd < - 60)
    {
        movd = 0;
    }
     
    score = score +0.20;
    }
    glColor3f(1,1,1);
    drawText("Score:", 360,455);
    if(p==1)
    drawText("--------PAUSE--------", 180,250);
    int sco;
    sco=int(score);
    snprintf(buffer,10,"%d", sco);
    
    drawTextNum(buffer, 6, 420,455);
    glutSwapBuffers(); 
    for(q = 0; q<= 10000000; q++){;}
    if(collide == true)
    {
    	
        
        glutSwapBuffers();
        
        glLoadIdentity();
        collide=false;
        screen=3;
       
        
        glutPostRedisplay();
    }
    
    }
    
}
 void init()
{
glClearColor(0.0,0.0,1.0,0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0, 500, 0, 500);
glMatrixMode(GL_MODELVIEW);
}
int submenu_id1;
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,500);
    glutCreateWindow("2D Car Racing game");
    init();
    submenu_id=glutCreateMenu(menufunc);
    glutAddMenuEntry("Small car",16);
    glutAddMenuEntry("Normal",17);
    submenu_id1=glutCreateMenu(menufunc);
    glutAddMenuEntry("Press p to pause and resume",100);
    glutAddMenuEntry("Use UP key to accelerate",100);
    glutAddMenuEntry("Use LEFT key to move left",100);
    glutAddMenuEntry("Use RIGHT key to move left",100);
    
    glutAddMenuEntry("Press q to quit anytime",100);
    menu_id=glutCreateMenu(menufunc);
    glutAddMenuEntry("Night mode",10);
    glutAddMenuEntry("Day mode",11);
    glutAddSubMenu("Scale Your car",submenu_id);
    glutAddSubMenu("Instructions",submenu_id1);
    glutAddMenuEntry("Exit",12);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    setfont(GLUT_BITMAP_HELVETICA_18);
    glutDisplayFunc(display);
    glutSpecialFunc(Specialkey);
    glutKeyboardFunc(Normalkey);
    
    glutIdleFunc(display);
    glutMainLoop();
    glFlush();
    return 0;
}

