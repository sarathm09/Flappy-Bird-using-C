/*									
									FLAPPY BIRD
 *									^^^^^^^^^^^
 *	This is the source code for running flappy bird in C. It requires TurboC, dosbox and bird.txt (given along with this file) for running.
 *	Date	: 27 Feb 2014
 *	Thank You!!!
 *	Designed By by T90. Credits : Dong Nguyen, .GEARS studios
 */

#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>

int obsst[300][3],birdpos=0,birdcol,d=1;
int score=0,pindex,point[400][3];

union REGS in,o;

void start()
	{
	int i=0,j=0;
	void bird();
	void st_sc(int);
	while(j<20)
	{
	j++;
	while(i<20)
		{
		cleardevice();
		i+=5;
		birdpos+=2;
		bird();
		st_sc(j);
		delay(20);
		}
	while(i>0)
		{
		cleardevice();
		i-=5;
		birdpos-=2;
		bird();
		st_sc(j);
		delay(20);
		}
	}
	}

void mclick(int *x, int *y, int *click)
	{
	in.x.ax=1;
	int86(0x33,&in,&o);
	in.x.ax=3;
	int86(0x33,&in,&o);
	*click=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
	}


int replay()
	{
	int x,y,c;
	char s[20];
	while(1){
	delay(30);
	rectangle(170,200,270,300);
	rectangle(350,200,450,300);

	rectangle(180,190,260,310);
	rectangle(360,190,440,310);

	line(200,220,200,280);
	line(200,220,240,250);
	line(200,280,240,250);

	line(380,220,420,280);
	line(420,220,380,280);

	outtextxy(190,250,"RESTART");
	outtextxy(390,250,"EXIT");

	mclick(&x,&y,&c);

	if(c==1)
		{
		if(y>200&&y<300)
			{
			if(x>180&&x<260)
				{
				birdpos=0;
				cleardevice();
				return 1;
				}
			else if(x>360&&x<440)
				{
				cleardevice();
				return 0;
				}
			}
		}
	}
	}

void st_sc(int s)
	{
	int poly[8];
	char text[20];
	rectangle(300,150,500,350);
	poly[0]=305;
		poly[1]=155;
	poly[2]=495;
		poly[3]=155;
	poly[4]=495;
		poly[5]=345;
	poly[6]=305;
		poly[7]=345;
	setfillstyle(0,0);
	fillpoly(4,poly);
	setfillstyle(6,1);
	fillpoly(4,poly);
	outtextxy(310,170,"FLAPPY BIRD : C VERSION");
	outtextxy(332,200,"A Program by T90");
	outtextxy(347,220,"Version 1.0");
	outtextxy(337,270,"Loading Game...");
	s=(20-s)*5;
	rectangle(343,290,447,300);
	rectangle(345,292,445-s,298);
	}

void bird()
	{
	int i=0,k;
	while(i<pindex){
	setcolor(birdcol);
	if(point[i][2]==0&&point[i+1][2]==0)
		line(point[i][0]-50,point[i][1]+birdpos,point[i+1][0]-50,point[i+1][1]+birdpos);
		i++;
		}
	setcolor(15);
	 }

void movebird()
	{
	void obstacles();
	void points();
	if(kbhit())
		{
		getch();
		birdpos-=20;
		}
	else
		birdpos+=10;

	}

void obstacles()
	{
	int i,j;
	for(i=0;i<300;i++){
		rectangle(obsst[i][0],obsst[i][2],obsst[i][1],getmaxy()+2);
		rectangle(obsst[i][0],-5,obsst[i][1],obsst[i][2]-140);
		rectangle(obsst[i][0]-3,obsst[i][2],obsst[i][1]+3,obsst[i][2]-20);
		rectangle(obsst[i][0]-3,obsst[i][2]-140,obsst[i][1]+3,obsst[i][2]-120);
		obsst[i][0]-=4;
		obsst[i][1]-=4;
		}
	}

int block=0;

int out()
	{
	int i;
	for(i=0;i<300;i++){
		if(obsst[i][0]<233&&obsst[i][1]>190){
			block=i;
			if(birdpos+257>obsst[block][2]-20)
				return 1;
			if(birdpos+223<obsst[block][2]-130)
			return 1;
			break;

			}
		}
	if(birdpos+235>getmaxy()-20)
		return 1;
	else  return 0;
	}

void points()
	{
	int i;
	char sc[20];
	for(i=0;i<300;i++){
		if(obsst[i][1]<220)
			score=i+1;
		else break;
		}
	rectangle(5,3,100,30);
	rectangle(7,5,98,27);
	sprintf(sc,"SCORE : %d",score);
	if(score>29){
		setcolor(2);
		}
	else if(score>14){
		setcolor(12);
		}
	else if(score>4){
		setcolor(10);
		}
	else if(score>2){
		setcolor(9);
		}
	else {
		setcolor(7);
		}
	outtextxy(17,12,sc);
	setcolor(15);
	}

void end()
	{
	int i,poly[8],tp=0;
	char text[20],c;
	FILE *f;
	f=fopen("config","r");
	if(f)
		{
		fscanf(f,"set_autosave:%d",&tp);
		if(tp>score)
			{
			fclose(f);
			f=fopen("config","w");
			fprintf(f,"set_autosave:%d",tp);
			}
		}
	else {
		f=fopen("config","w");
		fprintf(f,"set_autosave:%d",score);
		}
	fclose(f);
	while(birdpos+235<getmaxy()-23)
		{
		cleardevice();
		points();
		if(block>1)
			i=block;
		else i=0;
		for(;i<block+2;i++){
		rectangle(obsst[i][0],obsst[i][2],obsst[i][1],getmaxy()+2);
		rectangle(obsst[i][0],-5,obsst[i][1],obsst[i][2]-150);
		rectangle(obsst[i][0]-3,obsst[i][2],obsst[i][1]+3,obsst[i][2]-20);
		rectangle(obsst[i][0]-3,obsst[i][2]-150,obsst[i][1]+3,obsst[i][2]-130);
		}
		birdpos++;
		bird();
		delay(1);
		}
	rectangle(300,150,500,350);
	poly[0]=305;
		poly[1]=155;
	poly[2]=495;
		poly[3]=155;
	poly[4]=495;
		poly[5]=345;
	poly[6]=305;
		poly[7]=345;
	setfillstyle(0,0);
	fillpoly(4,poly);
	setfillstyle(6,1);
	fillpoly(4,poly);
	points();
	outtextxy(310,170,"FLAPPY BIRD : C VERSION");
	outtextxy(332,200,"A Program by T90");
	outtextxy(357,240,"SCORECHART");
	sprintf(text,"Current Score : %d",score);
	outtextxy(332,270,text);
	tp=(tp>=score?tp:score);
	sprintf(text,"Highest Score : %d",tp);
	outtextxy(332,290,text);
	delay(3000);
	}

void main()
	{
	int gdriver = DETECT, gmode, errorcode;
	int i,randnum,k;
	FILE *f1;
	initgraph(&gdriver, &gmode, "c:\\turboc3\\BGI");
	birdcol=random(14)+1;
	f1=fopen("bird.txt","r");
	fscanf(f1,"%d\n",&pindex);
	for(k=0;k<pindex+1;k++)
		fscanf(f1,"%d : %d : %d\n",&point[k][0],&point[k][1],&point[k][2]);
	fclose(f1);
	do
	{
	cleardevice();
	start();
	randomize();
	obsst[0][0]=getmaxx();
	obsst[0][1]=getmaxx()+60;
	randnum=random(300)+50;
	obsst[0][2]=randnum;
	for(i=1;i<200;i++)
		{
		obsst[i][0]=obsst[i-1][0]+220;
		obsst[i][1]=obsst[i][0]+50;
		randnum=random(350)+100;
		obsst[i][2]=randnum;
		}
	score=0;
	while(!out())
		{
		if(score>50)
			delay(15);
		else if(score>25)
			delay(25);
		else if(score>15)
			delay(35);
		else if(score>10)
			delay(40);
		else if(score>5)
			delay(45);
		else
			delay(50);

		cleardevice();
		obstacles();
		movebird();
		bird();
		points();
		}
	end();
	cleardevice();
	birdpos=0;
	i=replay();
	}while(i);
	}