#include <dos.h>
#include <math.h>
#include <iostream.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

float c=479/2,m=0.2,radius=5;
float x=30,y=(m*x)+c ;
float top1= (479/2)-50,bottom1=(479/2)+50;
float top2=top1, bottom2=bottom1;
float rad1, rad2, mid1, l1, mid2, l2;
char scoreP1[5],scoreP2[5];
int score_p1=0,score_p2=0;

char dir='+';

void score_screen()
{
    //ball maker//
     circle(x,y,radius);
     floodfill(x,y,15);
     line(getmaxx()/2,0,getmaxx()/2,getmaxy());  //court separeter//

     //player 1//
     bar(0,top1,15,bottom1);
     settextstyle(1,0,7);
     itoa(score_p1,scoreP1,10);
     outtextxy(getmaxx()/2-20,10,scoreP1);

     //player 2//
     bar(getmaxx()-15,top2,getmaxx(),bottom2);
     settextstyle(1,0,7);
     itoa(score_p2,scoreP2,10);
     outtextxy(getmaxx()/2+20,10,scoreP2);

     getch();
}
void oncollision()
{
     //direction analyzer and slope changer and constant changer//

 //player 1 collision checker//
     if(x-radius<=0+15 && y>=top1 && y<=bottom1)
      {
       mid1=(top1+bottom1)/2;
       if(y>mid1)
	{
	 l1=mid1-y;
	 rad1=(l1*(9/8))*(3.14/180);
	 m=tan(rad1);
	}
       else if(y<mid1)
	{
	 l1=mid1-y;
	 rad1=(l1*(9/8))*(3.14/180);
	 m=tan(rad1);
	}
       else
	m=0;

       dir='+';
       m*=-1; c=y-(m*x);
      }
   else if(x+radius<0)
    {
      x=639/2; y=479/2; m=0.2; c=y-(m*x);
      score_p2++;
      score_screen();
      cleardevice();
    }

 //player 2 collision checking//
     if(x+radius>=639-15 && y>=top2 && y<=bottom2)
      {
       mid2=(top2+bottom2)/2;
       if(y>mid2)
	{
	 l2=y-mid2;
	 rad2=(l2*(9/8))*(3.14/180);
	 m=tan(rad2);
	}
       else if(y<mid2)
	{
	 l2=y-mid2;
	 rad2=(l2*(9/8))*(3.14/180);
	 m=tan(rad2);
	}
       else
	m=0;

       dir='-';
       m*=-1; c=y-(m*x);
      }
   else if(x+radius>639)
    {
      x=639/2; y=479/2; m=0.2; c=y-(m*x);
      score_p1++;
      score_screen();
      cleardevice();
    }

// side collision checking //
     if(y+radius>=479)
      {
	m*=-1;	c=y-(m*x);
      }
     else if(y-radius<=0)
      {
	m*=-1; c=y-(m*x);
      }

}
void player_moove(char ch1,char ch2)
{
 // player 1 movement//
 if(ch1=='9'|| ch1=='w' && top1>=0)
  {
   top1-=21; bottom1-=21;
   if(top1<0)
   {
    top1=0; bottom1=100;
   }
  }
 else if(ch1=='3' || ch1=='s' && bottom1<=479)
  {
   top1+=21; bottom1+=21;
   if(bottom1>479)
    {
     bottom1=479; top1=bottom1-100;
    }

  }

 //player 2 moovement//
 if(ch2=='H' && top2>=0)     //up=H ,, down=p//
  {
   top2-=21; bottom2-=21;
   if(top2<0)
   {
    top2=0; bottom2=100;
   }
  }
 else if(ch2=='P' && bottom2<=479)
  {
   top2+=21; bottom2+=21;
   if(bottom2>479)
    {
     bottom2=479; top2=bottom2-100;
    }
  }
}

void moove_ball()
{
     char ch1,ch2;

     //players moover//
     if(kbhit())
     {
       ch1=getch();
       if(kbhit())
	ch2=getch();

       player_moove(ch1,ch2);
       ch1=NULL;ch2=NULL;

     }

     //ball maker//
     circle(x,y,radius);
     floodfill(x,y,15);
     line(getmaxx()/2,0,getmaxx()/2,getmaxy());  //court separeter//

     //player 1//
     bar(0,top1,15,bottom1);
     settextstyle(1,0,7);
     itoa(score_p1,scoreP1,10);
     outtextxy(getmaxx()/2-20,10,scoreP1);

     //player 2//
     bar(getmaxx()-15,top2,getmaxx(),bottom2);
     settextstyle(1,0,7);
     itoa(score_p2,scoreP2,10);
     outtextxy(getmaxx()/2+20,10,scoreP2);

     delay(30);
     cleardevice();

     //collision checker//
     oncollision();

     //distance increaser or ball moover//
     if(dir=='+')
      {
       x+=8; y=(m*x)+c;
      }
     else if(dir=='-')
      {
       x-=8; y=(m*x)+c;
      }

}
void load_graph()
{
 /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "");

   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1); /* terminate with an error code */
   }

}
void loadgame()
{
	rectangle(10,80,630,200);
	settextstyle(1,0,4);
	outtextxy(290,10,"INSTRUCTIONS");
      //	setbkcolor(LIGHTBLUE);
	settextstyle(1,0,5);
	outtextxy(40,100,"1. PLAYER 1 CONTROLS - MOVE UP AND DOWN USING UP AND DOWN ARROWS.");
	outtextxy(40,130,"2. PLAYER 2 CONTROLS - MOVE UP AND DOWN USING 'W'OR'9' AND 'S'OR'9' KEYS.");
	outtextxy(40,160,"3. PLAYER WHO MAKE SCORE -11 WILL WIN !!! ");

	settextstyle(7,0,6);
	outtextxy(150,430,"PRESS ANY KEY TO CONITINUE");

	getch(); cleardevice();

}
void endgame()
{
 if(score_p1>score_p2)
 {
   settextstyle(1,0,6);
	outtextxy(319,479/2," congratulation ... PLAYER 1 WON !!!");  }

else
 {
   settextstyle(1,0,6);
	outtextxy(319,479/2," congratulation ... PLAYER 2 WON !!!");  }

}

void main()
{
   //getmaxx()=639  ,getmaxy=479  //

   load_graph();  loadgame();

   while(score_p1<2 && score_p2<2)
   {
     moove_ball();
   }
   /* clean up */
   endgame();

   getch();
   closegraph();
}
