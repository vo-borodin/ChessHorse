#include <utility.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "ChessHorse.h"

static int panelHandle;
char *p;

char* s; 
char* u;

typedef struct{
int x;
int y;
}cell;

int Par1[12][12];

const int Par[12][12]={{1,1,1,1,1,1,1,1,1,1,1,1},
				  	   {1,1,1,1,1,1,1,1,1,1,1,1},
				  	   {1,1,0,0,0,0,0,0,0,0,1,1},
				  	   {1,1,0,0,0,0,0,0,0,0,1,1},
				  	   {1,1,0,0,0,0,0,0,0,0,1,1},
				  	   {1,1,0,0,0,0,0,0,0,0,1,1},
				  	   {1,1,0,0,0,0,0,0,0,0,1,1},
				  	   {1,1,0,0,0,0,0,0,0,0,1,1},
				  	   {1,1,0,0,0,0,0,0,0,0,1,1},
				  	   {1,1,0,0,0,0,0,0,0,0,1,1},
				  	   {1,1,1,1,1,1,1,1,1,1,1,1},
				  	   {1,1,1,1,1,1,1,1,1,1,1,1}};
cell Par2[64];
int k;
int exit1=0;

cell Init();
int poryad(int);
char *itoa(int);
int NumSteps(cell);
cell MinStep(cell);
cell HorseStep(int, cell);

cell Init()
{
	int i,j,a,b;
	cell Pos;
	
	for(a=0;a<12;a++)
	{
		for(b=0;b<12;b++)
		{
			Par1[a][b]=Par[a][b];
		}
	}
	
	for(a=1;a<9;a++)
	{
		for(b=1;b<9;b++)
		{
			SetTableCellVal (panelHandle, PANEL_TABLE, MakePoint (a,b), "");
		}
	}
	
	GetCtrlVal(panelHandle, PANEL_NUMERIC_1, &i);
	GetCtrlVal(panelHandle, PANEL_NUMERIC_2, &j);
	
	Pos.x=(i-1);
	Pos.y=(j-1);
	//Par1[Pos]=1;
	return Pos;
}

int poryad(int n)
{
	int j=0;
	do{
		n/=10;
		j++;
	}
	while(n!=0);
	return j;
}

char *itoa(int n)
{
	int i, j;
	i=0;
	
	s=(char*)malloc((poryad(n)+1)*sizeof(char));
	u=(char*)malloc((poryad(n)+1)*sizeof(char));
	
	do {       
	    s[i++]=(char)(n%10+48);  
	    n-=n%10;
	}
	while((n/=10)>0); 

    for (j=0;j<i;j++) 
	u[i-1-j]=s[j]; 
	u[j]='\0';
	return u;
}

int NumSteps(cell P)
{
	int i,j,l;
	int Res;
	int Set1[8];
	i=P.x;
	j=P.y;
	
	if(i>9||i<2||j>9||j<2)
		{for(l=0;l<8;l++)Set1[l]=0;}
	else
	{
		if(Par1[(i+1)][(j+2)]==0) Set1[0]=1;
		else Set1[0]=0;
	
		if(Par1[(i+2)][(j+1)]==0) Set1[1]=1;
		else Set1[1]=0;
	
		if(Par1[(i-1)][(j+2)]==0) Set1[2]=1;
		else Set1[2]=0;
	
		if(Par1[(i-2)][(j+1)]==0) Set1[3]=1;
		else Set1[3]=0;
	
		if(Par1[(i+1)][(j-2)]==0) Set1[4]=1;
		else Set1[4]=0;
	
		if(Par1[(i+2)][(j-1)]==0) Set1[5]=1;
		else Set1[5]=0;
	
		if(Par1[(i-1)][(j-2)]==0) Set1[6]=1;
		else Set1[6]=0;
	
		if(Par1[(i-2)][(j-1)]==0) Set1[7]=1;
		else Set1[7]=0;
	}
	
	Res=0;
	for(l=0;l<8;l++)
	{
		Res+=Set1[l];
	}
	return Res;
}

cell MinStep(cell Pos)
{
	int i,j,l,res,Min;
	int Set[8];
	cell R;
	cell t[8];

	i=Pos.x;
	j=Pos.y;
	
	//(t[l].x<=9 && t[l].x>=2 && t[l].y<=9 && t[l].y>=2)

	t[0].x=(i+1);t[0].y=(j+2);
	t[1].x=(i+2);t[1].y=(j+1);
	t[2].x=(i-1);t[2].y=(j+2);
	t[3].x=(i-2);t[3].y=(j+1);
	t[4].x=(i+1);t[4].y=(j-2);
	t[5].x=(i+2);t[5].y=(j-1);
	t[6].x=(i-1);t[6].y=(j-2);
	t[7].x=(i-2);t[7].y=(j-1);

	if(Par1[(i+1)][(j+2)]==0){
		if(t[0].x<=9 && t[0].x>=2){
			if(t[0].y<=9 && t[0].y>=2)Set[0]=NumSteps(t[0]);}}
	else{Set[0]=0;}
	
	if(Par1[(i+2)][(j+1)]==0){
		if(t[1].x<=9 && t[1].x>=2){
			if(t[1].y<=9 && t[1].y>=2)Set[1]=NumSteps(t[1]);}}
	else{Set[1]=0;}
	
	if(Par1[(i-1)][(j+2)]==0){
		if(t[2].x<=9 && t[2].x>=2){
			if(t[2].y<=9 && t[2].y>=2)Set[2]=NumSteps(t[2]);}}
	else{Set[2]=0;}
	
	if(Par1[(i-2)][(j+1)]==0){
		if(t[3].x<=9 && t[3].x>=2){
			if(t[3].y<=9 && t[3].y>=2)Set[3]=NumSteps(t[3]);}} 
	else{Set[3]=0;}
	
	if(Par1[(i+1)][(j-2)]==0){
		if(t[4].x<=9 && t[4].x>=2){
			if(t[4].y<=9 && t[4].y>=2)Set[4]=NumSteps(t[4]);}} 
	else{Set[4]=0;}
	
	if(Par1[(i+2)][(j-1)]==0){
		if(t[5].x<=9 && t[5].x>=2){
			if(t[5].y<=9 && t[5].y>=2)Set[5]=NumSteps(t[5]);}}
	else{Set[5]=0;}
	
	if(Par1[(i-1)][(j-2)]==0){
		if(t[6].x<=9 && t[6].x>=2){
			if(t[6].y<=9 && t[6].y>=2)Set[6]=NumSteps(t[6]);}}
	else{Set[6]=0;}
	
	if(Par1[(i-2)][(j-1)]==0){
		if(t[7].x<=9 && t[7].x>=2){
			if(t[7].y<=9 && t[7].y>=2)Set[7]=NumSteps(t[7]);}}
	else{Set[7]=0;}
	
	Min=0;
	for(l=0;l<8;l++)
	{
		if(Set[l]!=0){Min=Set[l];break;}
	}
	
	for(l=0;l<8;l++)
	{
		if((Min>abs(Set[l])) && (Set[l]!=0)) Min=Set[l];
	}
	
	for(l=0;l<8;l++)
	{
		if(Set[l]==Min){res=l;break;}
	}
	R=t[res];
	return R;
}

cell HorseStep(int k, cell I)
{
	if(k==0)
	{
		cell Pos1;
		Pos1.x=I.x+2;
		Pos1.y=I.y+2;
		Par1[Pos1.x][Pos1.y]=1;
		Par2[0]=Pos1;
		return Pos1;
	}
	else
	{
		cell Pos2,Pos3;
		
		Pos2=Par2[k-1];
		Pos3=MinStep(Pos2);
		
		Par1[Pos3.x][Pos3.y]=1;
		Par2[k]=Pos3;
		
		return Pos3;
	}
} 

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "ChessHorse.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK FUNC_PANEL (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
		}
	return 0;
}

int CVICALLBACK FUNC_BUTTON (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
cell I, J, K;
int i, j, a, b;
	switch (event)
		{
		case EVENT_COMMIT:
			
			I=Init();
			
			for(k=0;k<63;k++)
			{
				J=HorseStep(k,I);
			
				p=itoa(k+1);
				i=J.x+1-2;
				j=J.y+1-2;
				
				SetTableCellAttribute (panelHandle, PANEL_TABLE, MakePoint (i, j),
                       ATTR_TEXT_BGCOLOR, VAL_RED);
				SetTableCellVal (panelHandle, PANEL_TABLE, MakePoint (i,j), p);
				
				Delay(1);
				if((i+j)%2==1)SetTableCellAttribute (panelHandle, PANEL_TABLE, MakePoint (i, j),
                		ATTR_TEXT_BGCOLOR, VAL_BLACK);
                if((i+j)%2==0)SetTableCellAttribute (panelHandle, PANEL_TABLE, MakePoint (i, j),
                		ATTR_TEXT_BGCOLOR, VAL_WHITE);
			}
				
			for(a=2;a<9;a++)	
			{
				for(b=2;b<9;b++)
				{
					if(Par1[a][b]==0)
					{
						p=itoa(64);
						
						SetTableCellAttribute (panelHandle, PANEL_TABLE, MakePoint (a+1-2,b+1-2),
                       		   ATTR_TEXT_BGCOLOR, VAL_RED);
						SetTableCellVal (panelHandle, PANEL_TABLE, MakePoint (a+1-2,b+1-2), p);
						
						Delay(1);
						if((a+1-2+b+1-2)%2==1)SetTableCellAttribute (panelHandle, PANEL_TABLE, MakePoint (a+1-2,b+1-2),
                       			ATTR_TEXT_BGCOLOR, VAL_BLACK);
                		if((a+1-2+b+1-2)%2==0)SetTableCellAttribute (panelHandle, PANEL_TABLE, MakePoint (a+1-2,b+1-2),
                       			ATTR_TEXT_BGCOLOR, VAL_WHITE);
					}
				}
			}
			
			break;
		}
	return 0;
}

int CVICALLBACK QUIT_BUTTON (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
		}
	return 0;
}


