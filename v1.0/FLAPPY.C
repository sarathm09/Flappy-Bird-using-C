/*									
 *				FLAPPY BIRD
 *				^^^^^^^^^^^
 *	This is the source code for running flappy bird in C.
 *	It requires TurboC with dosbox.
 *	
 *	Versions
 *	<Initial Release>	: v1.0 	: 27 Feb 2014
 *						: v1.1 	: 27 Feb 2014
 *						: v1.2	: 4 Mar 2014
 *
 *	Thank You!!!
 *	Designed By by T90. Credits : Dong Nguyen, .GEARS studios
 */

#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>

int obsst[300][3],birdpos=0,birdcol,d=1;
int score=0,pindex,point[300][3];

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
	setcolor(12);
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
		birdpos-=25;
		}
	else
		birdpos+=10;

	}

void obstacles()
	{
	int i,j=0;
	for(i=0;i<300;i++){
		if((obsst[i][1]>0)&&j<3)
			{
			j++;
			rectangle(obsst[i][0],obsst[i][2],obsst[i][1],getmaxy()+2);
			rectangle(obsst[i][0],-5,obsst[i][1],obsst[i][2]-140);
			rectangle(obsst[i][0]-3,obsst[i][2],obsst[i][1]+3,obsst[i][2]-20);
			rectangle(obsst[i][0]-3,obsst[i][2]-140,obsst[i][1]+3,obsst[i][2]-120);
			obsst[i][0]-=4;
			obsst[i][1]-=4;
			}
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

void cleardevic()
	{
	int z;
	setcolor(0);
	for(z=0;z<getmaxy();z++)
		line(0,z,getmaxx(),z);
	}

void main()
	{
	int gdriver = DETECT, gmode, errorcode;
	int i,randnum;
	initgraph(&gdriver, &gmode, "c:\\turboc3\\BGI");
	randomize();
	birdcol=random(14)+1;
	pindex=272;
	point[0][0]=235; point[0][1]=235; point[0][2]=0; 
	point[1][0]=235; point[1][1]=235; point[1][2]=0; 
	point[2][0]=236; point[2][1]=235; point[2][2]=0; 
	point[3][0]=237; point[3][1]=235; point[3][2]=0; 
	point[4][0]=239; point[4][1]=235; point[4][2]=0; 
	point[5][0]=240; point[5][1]=236; point[5][2]=0; 
	point[6][0]=241; point[6][1]=236; point[6][2]=0; 
	point[7][0]=242; point[7][1]=236; point[7][2]=0; 
	point[8][0]=243; point[8][1]=236; point[8][2]=0; 
	point[9][0]=244; point[9][1]=237; point[9][2]=0; 
	point[10][0]=245; point[10][1]=237; point[10][2]=0; 
	point[11][0]=246; point[11][1]=238; point[11][2]=0; 
	point[12][0]=247; point[12][1]=238; point[12][2]=0; 
	point[13][0]=247; point[13][1]=239; point[13][2]=0; 
	point[14][0]=248; point[14][1]=239; point[14][2]=0; 
	point[15][0]=248; point[15][1]=240; point[15][2]=0; 
	point[16][0]=248; point[16][1]=241; point[16][2]=0; 
	point[17][0]=248; point[17][1]=242; point[17][2]=0; 
	point[18][0]=248; point[18][1]=242; point[18][2]=0; 
	point[19][0]=248; point[19][1]=243; point[19][2]=1; 
	point[20][0]=249; point[20][1]=240; point[20][2]=0; 
	point[21][0]=250; point[21][1]=240; point[21][2]=0; 
	point[22][0]=251; point[22][1]=240; point[22][2]=0; 
	point[23][0]=251; point[23][1]=241; point[23][2]=0; 
	point[24][0]=251; point[24][1]=242; point[24][2]=0; 
	point[25][0]=252; point[25][1]=242; point[25][2]=0; 
	point[26][0]=252; point[26][1]=242; point[26][2]=0; 
	point[27][0]=252; point[27][1]=243; point[27][2]=0; 
	point[28][0]=252; point[28][1]=243; point[28][2]=0; 
	point[29][0]=252; point[29][1]=244; point[29][2]=0; 
	point[30][0]=251; point[30][1]=244; point[30][2]=0; 
	point[31][0]=250; point[31][1]=245; point[31][2]=0; 
	point[32][0]=250; point[32][1]=245; point[32][2]=0; 
	point[33][0]=250; point[33][1]=245; point[33][2]=0; 
	point[34][0]=249; point[34][1]=245; point[34][2]=0; 
	point[35][0]=249; point[35][1]=245; point[35][2]=0; 
	point[36][0]=248; point[36][1]=245; point[36][2]=0; 
	point[37][0]=248; point[37][1]=245; point[37][2]=0; 
	point[38][0]=247; point[38][1]=245; point[38][2]=0; 
	point[39][0]=245; point[39][1]=245; point[39][2]=0; 
	point[40][0]=244; point[40][1]=245; point[40][2]=0; 
	point[41][0]=244; point[41][1]=245; point[41][2]=0; 
	point[42][0]=242; point[42][1]=244; point[42][2]=0; 
	point[43][0]=241; point[43][1]=244; point[43][2]=0; 
	point[44][0]=240; point[44][1]=244; point[44][2]=0; 
	point[45][0]=240; point[45][1]=243; point[45][2]=0; 
	point[46][0]=239; point[46][1]=243; point[46][2]=0; 
	point[47][0]=239; point[47][1]=242; point[47][2]=0; 
	point[48][0]=238; point[48][1]=241; point[48][2]=0; 
	point[49][0]=238; point[49][1]=240; point[49][2]=0; 
	point[50][0]=238; point[50][1]=239; point[50][2]=0; 
	point[51][0]=237; point[51][1]=238; point[51][2]=0; 
	point[52][0]=237; point[52][1]=237; point[52][2]=0; 
	point[53][0]=237; point[53][1]=236; point[53][2]=0; 
	point[54][0]=237; point[54][1]=236; point[54][2]=0; 
	point[55][0]=237; point[55][1]=236; point[55][2]=0; 
	point[56][0]=237; point[56][1]=235; point[56][2]=1; 
	point[57][0]=242; point[57][1]=234; point[57][2]=0; 
	point[58][0]=242; point[58][1]=234; point[58][2]=0; 
	point[59][0]=243; point[59][1]=234; point[59][2]=0; 
	point[60][0]=244; point[60][1]=233; point[60][2]=0; 
	point[61][0]=244; point[61][1]=232; point[61][2]=0; 
	point[62][0]=245; point[62][1]=232; point[62][2]=0; 
	point[63][0]=245; point[63][1]=231; point[63][2]=0; 
	point[64][0]=246; point[64][1]=231; point[64][2]=0; 
	point[65][0]=246; point[65][1]=230; point[65][2]=0; 
	point[66][0]=248; point[66][1]=230; point[66][2]=0; 
	point[67][0]=248; point[67][1]=229; point[67][2]=0; 
	point[68][0]=249; point[68][1]=229; point[68][2]=0; 
	point[69][0]=249; point[69][1]=229; point[69][2]=0; 
	point[70][0]=250; point[70][1]=229; point[70][2]=0; 
	point[71][0]=250; point[71][1]=228; point[71][2]=0; 
	point[72][0]=251; point[72][1]=228; point[72][2]=0; 
	point[73][0]=251; point[73][1]=228; point[73][2]=0; 
	point[74][0]=252; point[74][1]=228; point[74][2]=0; 
	point[75][0]=253; point[75][1]=228; point[75][2]=0; 
	point[76][0]=254; point[76][1]=227; point[76][2]=0; 
	point[77][0]=256; point[77][1]=227; point[77][2]=0; 
	point[78][0]=257; point[78][1]=227; point[78][2]=0; 
	point[79][0]=259; point[79][1]=227; point[79][2]=0; 
	point[80][0]=259; point[80][1]=227; point[80][2]=0; 
	point[81][0]=260; point[81][1]=227; point[81][2]=0; 
	point[82][0]=261; point[82][1]=227; point[82][2]=0; 
	point[83][0]=263; point[83][1]=227; point[83][2]=0; 
	point[84][0]=265; point[84][1]=227; point[84][2]=0; 
	point[85][0]=266; point[85][1]=228; point[85][2]=0; 
	point[86][0]=267; point[86][1]=228; point[86][2]=0; 
	point[87][0]=268; point[87][1]=229; point[87][2]=0; 
	point[88][0]=269; point[88][1]=229; point[88][2]=0; 
	point[89][0]=270; point[89][1]=230; point[89][2]=0; 
	point[90][0]=271; point[90][1]=231; point[90][2]=0; 
	point[91][0]=272; point[91][1]=231; point[91][2]=0; 
	point[92][0]=272; point[92][1]=232; point[92][2]=0; 
	point[93][0]=273; point[93][1]=232; point[93][2]=0; 
	point[94][0]=273; point[94][1]=232; point[94][2]=0; 
	point[95][0]=273; point[95][1]=233; point[95][2]=0; 
	point[96][0]=274; point[96][1]=233; point[96][2]=0; 
	point[97][0]=274; point[97][1]=234; point[97][2]=0; 
	point[98][0]=274; point[98][1]=235; point[98][2]=0; 
	point[99][0]=275; point[99][1]=235; point[99][2]=0; 
	point[100][0]=275; point[100][1]=235; point[100][2]=0; 
	point[101][0]=275; point[101][1]=235; point[101][2]=0; 
	point[102][0]=275; point[102][1]=236; point[102][2]=1; 
	point[103][0]=239; point[103][1]=242; point[103][2]=0; 
	point[104][0]=239; point[104][1]=242; point[104][2]=0; 
	point[105][0]=240; point[105][1]=243; point[105][2]=0; 
	point[106][0]=241; point[106][1]=244; point[106][2]=0; 
	point[107][0]=242; point[107][1]=244; point[107][2]=0; 
	point[108][0]=243; point[108][1]=245; point[108][2]=0; 
	point[109][0]=243; point[109][1]=246; point[109][2]=0; 
	point[110][0]=244; point[110][1]=246; point[110][2]=0; 
	point[111][0]=245; point[111][1]=246; point[111][2]=0; 
	point[112][0]=245; point[112][1]=247; point[112][2]=0; 
	point[113][0]=246; point[113][1]=247; point[113][2]=0; 
	point[114][0]=246; point[114][1]=248; point[114][2]=0; 
	point[115][0]=247; point[115][1]=248; point[115][2]=0; 
	point[116][0]=248; point[116][1]=249; point[116][2]=0; 
	point[117][0]=249; point[117][1]=249; point[117][2]=0; 
	point[118][0]=250; point[118][1]=250; point[118][2]=0; 
	point[119][0]=251; point[119][1]=251; point[119][2]=0; 
	point[120][0]=252; point[120][1]=251; point[120][2]=0; 
	point[121][0]=252; point[121][1]=251; point[121][2]=0; 
	point[122][0]=253; point[122][1]=251; point[122][2]=0; 
	point[123][0]=253; point[123][1]=251; point[123][2]=0; 
	point[124][0]=254; point[124][1]=252; point[124][2]=0; 
	point[125][0]=255; point[125][1]=252; point[125][2]=0; 
	point[126][0]=256; point[126][1]=252; point[126][2]=0; 
	point[127][0]=257; point[127][1]=252; point[127][2]=0; 
	point[128][0]=258; point[128][1]=252; point[128][2]=0; 
	point[129][0]=260; point[129][1]=252; point[129][2]=0; 
	point[130][0]=261; point[130][1]=252; point[130][2]=0; 
	point[131][0]=263; point[131][1]=252; point[131][2]=0; 
	point[132][0]=264; point[132][1]=252; point[132][2]=0; 
	point[133][0]=265; point[133][1]=252; point[133][2]=0; 
	point[134][0]=265; point[134][1]=252; point[134][2]=0; 
	point[135][0]=267; point[135][1]=252; point[135][2]=0; 
	point[136][0]=268; point[136][1]=252; point[136][2]=0; 
	point[137][0]=269; point[137][1]=251; point[137][2]=1; 
	point[138][0]=273; point[138][1]=234; point[138][2]=0; 
	point[139][0]=273; point[139][1]=234; point[139][2]=0; 
	point[140][0]=273; point[140][1]=234; point[140][2]=0; 
	point[141][0]=273; point[141][1]=235; point[141][2]=0; 
	point[142][0]=273; point[142][1]=236; point[142][2]=0; 
	point[143][0]=273; point[143][1]=237; point[143][2]=0; 
	point[144][0]=273; point[144][1]=238; point[144][2]=0; 
	point[145][0]=273; point[145][1]=239; point[145][2]=0; 
	point[146][0]=273; point[146][1]=239; point[146][2]=0; 
	point[147][0]=273; point[147][1]=239; point[147][2]=0; 
	point[148][0]=272; point[148][1]=240; point[148][2]=0; 
	point[149][0]=271; point[149][1]=240; point[149][2]=0; 
	point[150][0]=270; point[150][1]=240; point[150][2]=0; 
	point[151][0]=269; point[151][1]=241; point[151][2]=0; 
	point[152][0]=268; point[152][1]=241; point[152][2]=0; 
	point[153][0]=267; point[153][1]=241; point[153][2]=0; 
	point[154][0]=267; point[154][1]=242; point[154][2]=0; 
	point[155][0]=266; point[155][1]=242; point[155][2]=0; 
	point[156][0]=266; point[156][1]=243; point[156][2]=0; 
	point[157][0]=266; point[157][1]=243; point[157][2]=0; 
	point[158][0]=266; point[158][1]=243; point[158][2]=0; 
	point[159][0]=268; point[159][1]=243; point[159][2]=0; 
	point[160][0]=268; point[160][1]=243; point[160][2]=0; 
	point[161][0]=269; point[161][1]=244; point[161][2]=0; 
	point[162][0]=269; point[162][1]=244; point[162][2]=0; 
	point[163][0]=270; point[163][1]=245; point[163][2]=0; 
	point[164][0]=270; point[164][1]=246; point[164][2]=0; 
	point[165][0]=270; point[165][1]=247; point[165][2]=0; 
	point[166][0]=270; point[166][1]=247; point[166][2]=0; 
	point[167][0]=270; point[167][1]=248; point[167][2]=0; 
	point[168][0]=270; point[168][1]=249; point[168][2]=0; 
	point[169][0]=270; point[169][1]=249; point[169][2]=0; 
	point[170][0]=269; point[170][1]=249; point[170][2]=0; 
	point[171][0]=268; point[171][1]=249; point[171][2]=1; 
	point[172][0]=273; point[172][1]=236; point[172][2]=0; 
	point[173][0]=274; point[173][1]=236; point[173][2]=0; 
	point[174][0]=274; point[174][1]=237; point[174][2]=0; 
	point[175][0]=275; point[175][1]=238; point[175][2]=0; 
	point[176][0]=276; point[176][1]=238; point[176][2]=0; 
	point[177][0]=276; point[177][1]=239; point[177][2]=0; 
	point[178][0]=277; point[178][1]=240; point[178][2]=0; 
	point[179][0]=278; point[179][1]=240; point[179][2]=0; 
	point[180][0]=279; point[180][1]=241; point[180][2]=0; 
	point[181][0]=279; point[181][1]=241; point[181][2]=0; 
	point[182][0]=280; point[182][1]=241; point[182][2]=0; 
	point[183][0]=280; point[183][1]=242; point[183][2]=0; 
	point[184][0]=281; point[184][1]=242; point[184][2]=0; 
	point[185][0]=281; point[185][1]=242; point[185][2]=0; 
	point[186][0]=280; point[186][1]=242; point[186][2]=0; 
	point[187][0]=279; point[187][1]=243; point[187][2]=0; 
	point[188][0]=278; point[188][1]=244; point[188][2]=0; 
	point[189][0]=277; point[189][1]=244; point[189][2]=0; 
	point[190][0]=276; point[190][1]=245; point[190][2]=0; 
	point[191][0]=275; point[191][1]=245; point[191][2]=0; 
	point[192][0]=275; point[192][1]=246; point[192][2]=0; 
	point[193][0]=274; point[193][1]=246; point[193][2]=0; 
	point[194][0]=273; point[194][1]=247; point[194][2]=0; 
	point[195][0]=272; point[195][1]=247; point[195][2]=0; 
	point[196][0]=271; point[196][1]=247; point[196][2]=0; 
	point[197][0]=271; point[197][1]=248; point[197][2]=0; 
	point[198][0]=271; point[198][1]=248; point[198][2]=0; 
	point[199][0]=271; point[199][1]=249; point[199][2]=1; 
	point[200][0]=277; point[200][1]=243; point[200][2]=0; 
	point[201][0]=277; point[201][1]=243; point[201][2]=0; 
	point[202][0]=276; point[202][1]=243; point[202][2]=0; 
	point[203][0]=275; point[203][1]=243; point[203][2]=0; 
	point[204][0]=273; point[204][1]=243; point[204][2]=0; 
	point[205][0]=272; point[205][1]=243; point[205][2]=0; 
	point[206][0]=272; point[206][1]=243; point[206][2]=0; 
	point[207][0]=272; point[207][1]=243; point[207][2]=0; 
	point[208][0]=272; point[208][1]=242; point[208][2]=1; 
	point[209][0]=267; point[209][1]=228; point[209][2]=0; 
	point[210][0]=267; point[210][1]=228; point[210][2]=0; 
	point[211][0]=266; point[211][1]=228; point[211][2]=0; 
	point[212][0]=265; point[212][1]=228; point[212][2]=0; 
	point[213][0]=264; point[213][1]=228; point[213][2]=0; 
	point[214][0]=263; point[214][1]=228; point[214][2]=0; 
	point[215][0]=262; point[215][1]=229; point[215][2]=0; 
	point[216][0]=262; point[216][1]=230; point[216][2]=0; 
	point[217][0]=262; point[217][1]=231; point[217][2]=0; 
	point[218][0]=262; point[218][1]=232; point[218][2]=0; 
	point[219][0]=262; point[219][1]=233; point[219][2]=0; 
	point[220][0]=262; point[220][1]=234; point[220][2]=0; 
	point[221][0]=263; point[221][1]=234; point[221][2]=0; 
	point[222][0]=264; point[222][1]=235; point[222][2]=0; 
	point[223][0]=265; point[223][1]=235; point[223][2]=0; 
	point[224][0]=265; point[224][1]=236; point[224][2]=0; 
	point[225][0]=266; point[225][1]=236; point[225][2]=0; 
	point[226][0]=267; point[226][1]=237; point[226][2]=0; 
	point[227][0]=268; point[227][1]=237; point[227][2]=0; 
	point[228][0]=269; point[228][1]=238; point[228][2]=0; 
	point[229][0]=270; point[229][1]=238; point[229][2]=0; 
	point[230][0]=270; point[230][1]=238; point[230][2]=0; 
	point[231][0]=270; point[231][1]=238; point[231][2]=0; 
	point[232][0]=272; point[232][1]=237; point[232][2]=0; 
	point[233][0]=272; point[233][1]=237; point[233][2]=0; 
	point[234][0]=272; point[234][1]=237; point[234][2]=0; 
	point[235][0]=272; point[235][1]=237; point[235][2]=0; 
	point[236][0]=272; point[236][1]=237; point[236][2]=0; 
	point[237][0]=272; point[237][1]=236; point[237][2]=1; 
	point[238][0]=269; point[238][1]=231; point[238][2]=0; 
	point[239][0]=270; point[239][1]=231; point[239][2]=0; 
	point[240][0]=270; point[240][1]=232; point[240][2]=0; 
	point[241][0]=271; point[241][1]=233; point[241][2]=0; 
	point[242][0]=271; point[242][1]=234; point[242][2]=0; 
	point[243][0]=271; point[243][1]=234; point[243][2]=0; 
	point[244][0]=270; point[244][1]=233; point[244][2]=0; 
	point[245][0]=270; point[245][1]=232; point[245][2]=0; 
	point[246][0]=270; point[246][1]=232; point[246][2]=0; 
	point[247][0]=270; point[247][1]=232; point[247][2]=0; 
	point[248][0]=270; point[248][1]=234; point[248][2]=0; 
	point[249][0]=270; point[249][1]=234; point[249][2]=0; 
	point[250][0]=270; point[250][1]=234; point[250][2]=0; 
	point[251][0]=269; point[251][1]=233; point[251][2]=0; 
	point[252][0]=269; point[252][1]=233; point[252][2]=0; 
	point[253][0]=269; point[253][1]=236; point[253][2]=0; 
	point[254][0]=269; point[254][1]=236; point[254][2]=0; 
	point[255][0]=269; point[255][1]=235; point[255][2]=0; 
	point[256][0]=268; point[256][1]=233; point[256][2]=0; 
	point[257][0]=268; point[257][1]=232; point[257][2]=0; 
	point[258][0]=268; point[258][1]=233; point[258][2]=0; 
	point[259][0]=269; point[259][1]=234; point[259][2]=0; 
	point[260][0]=269; point[260][1]=235; point[260][2]=0; 
	point[261][0]=269; point[261][1]=235; point[261][2]=0; 
	point[262][0]=268; point[262][1]=233; point[262][2]=0; 
	point[263][0]=268; point[263][1]=232; point[263][2]=0; 
	point[264][0]=268; point[264][1]=232; point[264][2]=0; 
	point[265][0]=268; point[265][1]=234; point[265][2]=0; 
	point[266][0]=268; point[266][1]=235; point[266][2]=0; 
	point[267][0]=268; point[267][1]=236; point[267][2]=0; 
	point[268][0]=268; point[268][1]=236; point[268][2]=0; 
	point[269][0]=268; point[269][1]=235; point[269][2]=0; 
	point[270][0]=267; point[270][1]=235; point[270][2]=0; 
	point[271][0]=267; point[271][1]=234; point[271][2]=0; 
	point[272][0]=267; point[272][1]=234; point[272][2]=0; 
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
		if(score>20)
			delay(5);
		else if(score>10)
			delay(10);
		else if(score>5)
			delay(15);
		else if(score>3)
			delay(15);
		else
			delay(25);

		cleardevice();
		delay(15);
		obstacles();
		movebird();
		bird();
		points();
		}
	end();
	cleardevic();
	birdpos=0;
	i=replay();
	}while(i);
	}