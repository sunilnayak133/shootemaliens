// including header files
#include<graphics.h>
#include<fstream.h>
#include<iomanip.h>
#include<math.h>
#include<process.h>
#include<conio.h>
#include<iostream.h>
#include<time.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
enum arrows{UP=72,LEFT=75,RIGHT=77,DOWN=80};
enum keys{ESC=27, ENTER=13};
enum screensize{X=80,Y=25};
char *pause[3]={"RESUME","MAIN MENU","EXIT GAME"};
char *lvls[5]={"LEVEL 1","LEVEL 2","LEVEL 3","LEVEL 4","LEVEL 5"};
char *sttngs[4]={"DIFFICULTY","INSTRUCTIONS","BACK TO MAIN MENU"};
char *diff[3]={"EASY","MEDIUM","HARD"};
char *Mmenu[4]={"NEW GAME","SETTINGS","ABOUT THE GAME","EXIT"};
int gdriver = DETECT,gmode;
int lgm=10;
int ti;
int ud=0;
int dfclty=0;
char *num[10]={"0","1","2","3","4","5","6","7","8","9"};

void helpdisp()
{ setcolor(GREEN);
  settextstyle(3,0,1);
  settextjustify(0,1);
  outtextxy( 10 , getmaxy() - 10 ,"ARROW KEYS - MOVE. ENTER - SELECT. ESC - BACK/EXIT" );
 }


void alien( int ax, int ay)
{ setcolor(GREEN);
  setfillstyle(1,GREEN);
  int sa,ea;
  if(ud==0)
  {sa=135; ea=45; }
  else
  {sa=315; ea=225; }
  ellipse(ax,ay,sa,ea,7,9);
  putpixel(ax-2, ay, RED);
  putpixel(ax+2, ay,RED);
  setcolor(WHITE);
  }
int shoot(int,int,int,int);
struct player
{ char name[20];
  long timetaken;
  int level;  };

void cls(int ax,int ay)
{ setbkcolor(BLACK);
  setcolor(BLACK);
  setfillstyle(SOLID_FILL,BLACK);
  circle(getmaxx()/2, getmaxy()/2,10);
  ellipse(ax,ay,0,360,7,9);
  putpixel(ax-2, ay,BLACK);
  putpixel(ax+2, ay,BLACK);
  setcolor(WHITE);
}

double selang(int en)
{ if(en>=315)
    { return -((45+en)-360);}
  if(en<=135)
    {return -(45+en);}
  if(en>135&&en<=180)
    {return 180-(45+en-180);}
  if((en>180)&&(en<270))
    {return 180-(45+(en-180));}
  if((en>=270)&&(en<315))
    {return -(45+en);}
  if((en>0)&&(en<=45))
    {return -(45+en);}
  else
     {return -(45-en);};
}

int hit(int ax,int ay)
{int a;
switch(dfclty)
 { case 0:
    a=5;
    break;
   case 1:
    a=3;
    break;
   case 2:
    a=2;
    break; }
 for(int j=ax-a;j<ax+a;j++)
 for(int i=ay-a;i<ay+a;i++)
   { if(getpixel((j+getmaxx()/2)/2,(i+getmaxy()/2)/2)==RED)
     {cls(ax,ay);
	return 1;}}
  return 0;
}

int shoot(int cx,int cy,int sta,int ena,int ax, int ay)
{ while(sta>=360)
   {sta-=360;}
  while(ena>=360)
   {ena-=360;}
  setcolor(RED);
  moveto(cx,cy);
  double max_d=pow((pow(getmaxx()/2,2))+(pow((getmaxy()-30)/2,2)),0.5);
  double ang=selang(ena);
  ang = (M_PI /180) *ang;
  double s=sin(ang);
  double c=cos(ang);
  double relx=max_d*c;
  double rely=max_d*s;
  setlinestyle(4,3,20);
  linerel(relx,rely);
  delay(50);
  cls(ax,ay);
  return (hit(ax,ay));
  }

  void chalcoor(int &ay,int level)
  {  if(ud==0)
	   {if(ay<getmaxy()-25)
	    {ay+=(level*(dfclty+1));}
	    else
	    {ay-=(level*(dfclty+1));
	     ud=1;}
	    }
     else
	   {if(ay>35)
	     {ay-=(level*(dfclty+1));}
	    else
	     {ud=0;
	      ay+=(level*(dfclty+1));}
	   }
	  }

void pausemenu();



  int levels(int x)
  {
  lgm=10;
  int u=lgm%10, t=(lgm%100)/10, h=(lgm%1000)/100;
  line(getmaxx(),getmaxy()-10, 0, getmaxy()-10);
  line(0,20,getmaxx(),20);
  outtextxy(getmaxx()-150,10,"Aliens left:");
  outtextxy(getmaxx()-55,10,num[h]);
  outtextxy(getmaxx()-45,10,num[t]);
  outtextxy(getmaxx()-35,10,num[u]);
  int i=getmaxx()/2,j=getmaxy()/2;
  outtextxy(i,2*j-4,"X - SHOOT, ARROW KEYS - ROTATE");
  int midx=i;
  time_t T;
  srand((unsigned)time(&T));
  int ax=rand()%600+11,ay=30;
  while(ax>midx-40&&ax<midx+40)
   {ax=rand()%600+11;}
  int sa=135,ea=45;
  int y=0;
  while(lgm>0 )
   {  cls(ax,ay);
      outtextxy(0,4,"Level:");
      outtextxy(45,4,num[x]);
      arc(i,j,sa,ea,10);
      alien(ax,ay);
      char ch;
      if(!kbhit())
      { cls(ax,ay);
	chalcoor(ay,x);
	alien(ax,ay);
	/*setcolor(BLACK);
	setfillstyle(SOLID_FILL,BLACK);
	rectangle(midx-200,0,midx+100,10);*/
	setcolor(WHITE);
	ti=y/100;
	int ux=ti%10, tx=(ti%100)/10, hx=(ti%1000)/100;
	 outtextxy(getmaxx()/2-100,5,num[hx]);
	 outtextxy(getmaxx()/2-90,5,num[tx]);
	 outtextxy(getmaxx()/2-80,5,num[ux]);
	arc(i,j,sa,ea,10);
	delay(18);
	setcolor(BLACK);
	outtextxy(getmaxx()/2-100,5,num[hx]);
	outtextxy(getmaxx()/2-90,5,num[tx]);
	outtextxy(getmaxx()/2-80,5,num[ux]);
	y+=2;
	setcolor(WHITE);
      }
      else
       { cls(ax,ay);
	 alien(ax,ay);

	 ch=getch();
	 if(ch==0)
	 { cls(ax,ay);
	   alien(ax,ay);
	   ch=getch();
	   switch(ch)
	     {
		case UP:
	       { cls(ax,ay);
		 ea=45;
		 sa=135;
		 break; }
	       case RIGHT:
	       { cls(ax,ay);
		 chalcoor(ay,x);
		 alien(ax,ay);
		if(ea>=5)
		  ea-=5;
		 else if(ea<5)
		 { ea+=360;
		   ea-=5;}
		 if(sa>=5)
		  sa-=5;
		 else if(sa<5)
		  {sa+=360;
		   sa-=5;}
		 break;
		 }
		 case LEFT:
		{ cls(ax,ay);
		  chalcoor(ay,x);
		  alien(ax,ay);
		  ea+=5;
		  sa+=5;
		  break;
		 }
	       case DOWN:
	       { cls(ax,ay);
		 ea=225;
		 sa=315;
		 break; }
	    }
	   }
	 else if(ch=='x')
	      {alien(ax,ay);
	       setlinestyle(USERBIT_LINE,1,20);
	       int res=shoot(i,j,sa,ea,ax,ay);
	       if(res==1)
	       {lgm=lgm-1;
	       cleardevice();
	       setcolor(WHITE);
	       u=lgm%10;
	       t=(lgm%100)/10;
	       h=(lgm%1000)/100;
	       line(getmaxx(),getmaxy()-10, 0, getmaxy()-10);
	       line(0,20,getmaxx(),20);
	       outtextxy(getmaxx()-150,10,"Aliens left:");
	       outtextxy(getmaxx()-55,10,num[h]);
	       outtextxy(getmaxx()-45,10,num[t]);
	       outtextxy(getmaxx()-35,10,num[u]);
	       outtextxy(midx,getmaxy()-5,"X - SHOOT, ARROW KEYS - ROTATE");
	       time_t s;
	       srand((unsigned)time(&s));
	       ax=(rand()%600)+11;
	       if(ax>midx-40&&ax<midx+40)
	       ax=(rand()%600)+11;
	       continue;}
	       else
	       {cleardevice();
	       setcolor(WHITE);
	       line(getmaxx(),getmaxy()-10, 0, getmaxy()-10);
	       line(0,20,getmaxx(),20);
	       outtextxy(getmaxx()-150,10,"Aliens left:");
	       outtextxy(getmaxx()-55,10,num[h]);
	       outtextxy(getmaxx()-45,10,num[t]);
	       outtextxy(getmaxx()-35,10,num[u]);
	       outtextxy(midx,getmaxy()-5,"X - SHOOT, ARROW KEYS - ROTATE");
	       cls(ax,ay);
	       }}
	 else if(ch==ESC)
	   { pausemenu();
	     cleardevice();
	     setcolor(WHITE);
	     line(getmaxx(),getmaxy()-10, 0, getmaxy()-10);
	     line(0,20,getmaxx(),20);
	     outtextxy(getmaxx()-150,10,"Aliens left:");
	     outtextxy(getmaxx()-55,10,num[h]);
	     outtextxy(getmaxx()-45,10,num[t]);
	     outtextxy(getmaxx()-35,10,num[u]);
	     outtextxy(midx,getmaxy()-5,"X - SHOOT, ARROW KEYS - ROTATE");
	     cls(ax,ay);
	     }
	  }


     }
      cls(ax,ay);
      return 1;

}

void settings();
void mainmenu();
void game();

void mmsound()
{ sound(440);
  delay(100);
  nosound();
  delay(50);
  sound(440);
  delay(100);
  nosound();
  delay(50);
  sound(790);
  delay(100);
  nosound();
  delay(50);
  sound(790);
  delay(100);
  nosound();
  delay(50);
  sound(710);
  delay(100);
  nosound();
  delay(50);
  sound(710);
  delay(100);
  nosound();
  delay(50);
  sound(600);
  delay(100);
  nosound();
  delay(50);
  sound(600);
  delay(100);
  nosound();
  delay(50);
  sound(680);
  delay(100);
  nosound();
  delay(50);
  sound(680);
  delay(100);
  nosound();
  delay(50);
  sound(530);
  delay(100);
  nosound();
  delay(50);
  sound(530);
  delay(100);
  nosound();
  delay(50);
  sound(600);
  delay(100);
  nosound();
  delay(50);
  sound(600);
  delay(100);
  nosound();
  delay(50);
  sound(500);
  delay(100);
  nosound();
  delay(50);
  sound(500);
  delay(100);
  nosound();
  delay(50);
  sound(440);
  delay(300);
  nosound();






}




int menuv(char *list[10],int nitems,int ns=3,int ox=-1,int oy=-1)
{       setcolor(RED);
	char ch=0;
	int ar_cnt=1;
	if(ox==-1&&oy==-1)
	{
		int maxl=0;
		for(int i=0;i<nitems;i++)
		{
			int l=strlen(list[i]);
			if(maxl<l)
				maxl=l;
		}
		ox=(X-maxl)/2;
		oy=(Y-nitems*ns)/2;
	}
	for(int i=0;i<nitems;i++)
	{
		outtextxy(ox,oy+(i*ns),list[i]);

	}
	outtextxy(ox,oy,list[ar_cnt-1]);
	while(ch!=ESC)
	{
		ch=getch();
		if(ch==0)
		{
			ch=getch();
			switch(ch)
			{
				case UP:
					setcolor(RED);
					outtextxy(ox,oy+((ar_cnt-1)*ns),list[ar_cnt-1]);
					ar_cnt=--ar_cnt%(nitems+1);
					setcolor(GREEN);
					if(ar_cnt==0)
						ar_cnt=nitems;
					outtextxy(ox,oy+((ar_cnt-1)*ns),list[ar_cnt-1]);
					break;
				case DOWN:
					setcolor(RED);
					outtextxy(ox,oy+((ar_cnt-1)*ns),list[ar_cnt-1]);
					ar_cnt=++ar_cnt%(nitems+1);
					if(ar_cnt==0)
						ar_cnt=1;
					setcolor(GREEN);
					outtextxy(ox,oy+((ar_cnt-1)*ns),list[ar_cnt-1]);
					break;
				default:
					break;
			}
		}
		else if(ch==ENTER)
		{
			return (ar_cnt-1);
		}
	}
     return ESC;
}


void instructions()
{ int x=20, y=40;
  cleardevice();
  setcolor(GREEN);
  setbkcolor(BLACK);
  int midx=getmaxx()/2;
  outtextxy( midx-50, 10, "INSTRUCTIONS");
  setcolor(RED);
  outtextxy( x, y, "THE ALIEN MENACE IS UPON US!");
  y+=20;
  outtextxy( x, y, "YOU'RE THE HUMAN WHO CAN SAVE US ALL.");
  y+=20;
  outtextxy( x, y, "THE ALIEN BUILDING HAS 5 LEVELS. EACH HAVING FASTER ALIENS");
  y+=20;
  outtextxy( x, y, "THAN THE LAST. YOU'RE ROLE IS TO SIT IN THE ROTATING TURRET");
  y+=20;
  outtextxy( x, y, "IN THE MIDDLE AND SHOOT THEM. USE THE ARROW KEYS TO ROTATE");
  y+=20;
  outtextxy( x, y, "THE TURRET AND HIT 'X' TO FIRE YOUR LASER ");
  y+=20;
  outtextxy( x, y,"ALSO NOTE. THE HIGHER THE DIFFICULTY, THE LESS VULNERABLE");
  y+=20;
  outtextxy( x, y,"THEY ARE. TRY TO GET THEM BANG IN THE MIDDLE. ALWAYS WORKS");
  y+=20;
  outtextxy( x, y, "MAY THE BEST RACE WIN");
  y+=160;
  setcolor(GREEN);
  outtextxy( x, y, "(DIFFICULTY CAN BE CHANGED IN THE SETTINGS MENU)");
  outtextxy( 10,getmaxy()-10,"ESC-BACK");
  char ch=getch();
  if(ch==ESC)
   settings();

}


void settings()
{cleardevice();
 setbkcolor(BLACK);
 setcolor(GREEN);
 helpdisp();
 outtextxy(getmaxx()/2-100,45,"SETTINGS");
 setcolor(RED);
 int s=menuv(sttngs,3,80,getmaxx()/2,175);
 if(s==ESC)
 mainmenu();
 switch(s)
 { case 0:
   cleardevice();
   setbkcolor(BLACK);
   setcolor(GREEN);
   helpdisp();
   outtextxy(getmaxx()/2-150,getmaxy()/2,"DIFFICULTY");
   dfclty=menuv(diff,3,20,getmaxx()/2,getmaxy()/2);
   if(dfclty==ESC)
   settings();
   getch();
   case 1:
   instructions();
   case 2:
   mainmenu();
  }

}


void load()
{ int midx=getmaxx()/2;
  int midy=getmaxy()/2;
  cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tAre you ready??\n\n\t\t\t\tPress Enter";
  getch();
  cleardevice();
  setbkcolor(BLACK);
  setcolor(RED);
  for(int r=0,en=0;en<360;en+=2)
       {setfillstyle(1,4);
	pieslice(midx,midy,r,en,100);
	setcolor(WHITE);
	settextstyle(1,0,0);
	settextjustify(1,1);
	outtextxy(midx+10,midy-25,"Loading");
	setcolor(RED);
	delay(20);
       }
  setfillstyle(1,4);
  pieslice(midx,midy,r,en,100);
  setcolor(WHITE);
  settextstyle(1,0,0);
  settextjustify(1,1);
  outtextxy(midx,midy,"Press a key");
  getch();
  cleardevice();
  setbkcolor(BLACK);
  setcolor(RED);
  settextstyle(3,0,0);
  settextjustify(1,1);
  outtextxy(midx,midy,"SHOOT 'EM");
  outtextxy(midx,midy+30,"ALIENS");
  mmsound();
  getch();
  cleardevice();
}

void pausemenu()
{ int p = menuv(pause,3,40,getmaxx()/2,getmaxy()/2);
  if(p==ESC)
  mainmenu();
  switch(p)
    { case 0:
      break;
      case 1:
      mainmenu();
      case 2:
      exit(0);
     }
}


void about()
{ cleardevice();
  setbkcolor(BLACK);
  setcolor(GREEN);
  settextstyle(1,0,3);
  settextjustify(1,1);
  outtextxy( getmaxx()/2, 30 , "ABOUT");
  setcolor(RED);
  outtextxy( getmaxx()/2 - 50 , 70 , "VERSION - 2.0");
  outtextxy( getmaxx()/2 - 100, 100 , "PROGRAMMED BY - SUNIL.S.NAYAK");
  getch();
  mainmenu();
}

void mainmenu()
{ cleardevice();
  int midx=getmaxx()/2;
  int midy=getmaxy()/2;
  helpdisp();
  setcolor(GREEN);
  setbkcolor(BLACK);
  settextstyle(10,0,4);
  settextjustify(1,1);
  outtextxy(midx+50,midy-100,"SHOOT 'EM");
  outtextxy(midx+50,midy-50,"ALIENS");
  setbkcolor(BLACK);
  setcolor(WHITE);
  setfillstyle(1,WHITE);
  rectangle(0,240,300,280);
  rectangle(0,300,300,340);
  rectangle(0,360,300,400);
  rectangle(0,420,300,460);
  floodfill(1,241,WHITE);
  floodfill(1,301,WHITE);
  floodfill(1,361,WHITE);
  floodfill(1,421,WHITE);
  setcolor(WHITE);
  settextstyle(1,0,4);
  settextjustify(0,1);
  int ch=menuv(Mmenu,4,60,midx-300,midy+20);
  if(ch==ESC)
  exit(0);
  switch(ch)
  { case 0:
      game();
      break;
    case 1:
      settings();
      break;
    case 2:
      about();
      break;
    case 3:
      exit(0);
  }


  getch();
}

void game()
{   cleardevice();
    int midx=getmaxx()/2;
    int midy=getmaxy()/2;
    setbkcolor(BLACK);
    helpdisp();
    outtextxy(midx , 25 , "CHOOSE YOUR DESTINY" );
    int z=menuv(lvls,5,60,midx,100)+1;
    if(z==ESC+1)
    mainmenu();
    setcolor(WHITE);
    settextstyle(2,0,1);
    if(z==1)
  { cleardevice();
    setbkcolor(WHITE);
    setcolor(BLUE);
    settextstyle(3,0,1);
    settextjustify(0,1);
    outtextxy(midx-75,midy,"WELCOME TO EARTH");
    getch();
    cleardevice();
    setbkcolor(WHITE);
    outtextxy(midx-100, midy,"ONCE A HUMAN CIVILIZATION");
    outtextxy(midx-200, midy+20,"NOW RUN BY HARSH ALIENS OF THE PLANET ZORK");
    outtextxy(midx-175, midy+40,"WHICH HAPPENS TO IRRITATE A CERTAIN HUMAN.");
    outtextxy(midx-2, midy+80,"YOU");
    getch();
    cleardevice();
    setbkcolor(WHITE);
    outtextxy(midx-100, midy,"YOUR JOB IS TO ERADICATE");
    outtextxy(midx-220, midy+20,"THE ALIENS ONE BY ONE IN THEIR BUILDING");
    outtextxy(midx-220, midy+40,"ON THE EARTH WHERE THEIR GOVERNMENT STAYS");
    outtextxy(midx-200, midy+60,"YOU'RE ALONE. BUT YOU HAVE NO CHOICE.");
    getch();
    cleardevice();
    setbkcolor(WHITE);
    outtextxy(midx-250, midy,"FOR THE SAKE OF THE REMNANTS OF THE HUMAN RACE,");
    outtextxy(midx-50, midy+40,"YOU MUST WIN!");
    getch();
    cleardevice();
    setbkcolor(WHITE);
    outtextxy(midx-100, midy,"NOW GO KILL SOME ALIENS!");
    getch();
    setcolor(WHITE);
  }
    cleardevice();
    setbkcolor(WHITE);
    settextstyle(0,0,1);
    setcolor(WHITE);
    clock_t start,end;
    cleardevice();
    for(;z<=5;z++)
  {
     start = clock();
     int l=levels(z);
     end = clock();
     clock_t time=end-start;
     char chk=getch();
     while(chk=='x'||chk==UP||chk==DOWN||chk==LEFT||chk==RIGHT)
     {chk=getch();}
     outtextxy(midx-75,midy,"Time u took was ");
     time=(end-start)/19.2;
     int T=(int)time;
     int h=T/100;
     int t=(T%100)/10;
     int u=T%10;
     outtextxy(midx+50,midy,num[h]);
     outtextxy(midx+58,midy,num[t]);
     outtextxy(midx+66,midy,num[u]);
     outtextxy(midx+74,midy," seconds");
     int tc=1;
     if(dfclty>1)
     {tc=2;}
     if(l==1 && time>(25*z*tc))
     {closegraph();
      cout<<"\n\n\nGame over. You maxed out on level "<<z;
      getch();
      getch();
      initgraph(&gdriver,&gmode,"c:/Dev-Cpp/lib/");
      mainmenu(); }
     else
     {if(z!=5)
     outtextxy(midx-75,midy+10,"Press a key for next level");
     getch();
     closegraph();
     cout<<"Enter name:";
     player p;
     gets(p.name);
     p.timetaken=T;
     p.level=z;
     fstream file;
     file.open("HighScore.bin",ios::in|ios::out|ios::binary|ios::app|ios::ate);
     file.write((char*)&p,sizeof(p));
     file.seekg(0,ios::beg);
      player pr[100];
      int i=0;
     for( i=0; file.eof()==0;i++)
      { file.read((char*)&pr[i],sizeof(pr[i])); }
     int n=i;
     player tmp;
     long small=pr[0].timetaken;
     int pos=0;
     for(i=0;i<n;i++)
       { small=pr[i].timetaken;
	 if(pr[i].level==z)
       { for(int j=i;j<n;j++)
	     { if(pr[j].timetaken<=small)
	       { small=pr[j].timetaken; pos=j; }
	     }
    tmp=pr[i];
    pr[i]=pr[pos];
    pr[pos]=tmp;} }

     cout<<"\n\nSCORES\n\n";
     cout<<"NAME |  "<<setw(7)<<"TIME     |"<<setw(7)<<"LVL"<<"    |\n";
    for(int o=0;o<(i-1);o++)
    { if(pr[o].timetaken!=0)
     { for(int q=0;q<3;q++)
	     { cout<<pr[o].name[q];}
	       cout<<"  |  "<<setw(7)<<pr[o].timetaken<<"  |"<<setw(7)<<pr[o].level<<"    |\n";
	     } }

     getch();
     initgraph(&gdriver,&gmode,"c:/Dev-Cpp/lib/");
     }
   }
 cleardevice();
 getch();
 getch();
 if(z==6)
   { outtextxy(midx-100,midy,"CONGRATULATIONS! YOU FINISHED THE GAME!!"); }
   randomize();
 while(!kbhit())
 {
  setbkcolor(BLACK);
  int x1=rand()%getmaxx();
  int y1=rand()%getmaxy();
  int color=rand();
  setcolor(color);
  delay(20);
  putpixel(x1,y1,color);


  }
  mainmenu();

 }




  void main()
  { initgraph(&gdriver,&gmode,"c:/Dev-Cpp/lib/");
    load();
    mainmenu();

  }
