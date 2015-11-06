/***************************************************
* Laborator 3 -> Reuniunea & Intersectia 
			  -> Fuzificare
*			  -> fara eliminarea punctelor coliniare
*
*	"Versiunea noastra - a masteranzilor"  
*
* Versiune testata in laborator 
****************************************************/

#include<stdlib.h>
#include<conio.h>
#include<stdio.h>

#define N 6   //vezi??

#define min(a,b) ((a<b)?(a):(b))
#define max(a,b) ((a>b)?(a):(b))

#define nax1 4
#define nax2 5
#define nay 5
#define nX 4

float x1[nax1][4] = {{0,1,2,7},{3,4,5,6},{0,5,6,7}};
float miux[nX][4] = {{1,1,0,0},{0,1,1,0},{0,1,1,0},{0,0,1,1}};
int npx1 = 4;
float x2[nax2][3] = {{-30,-20,-10},{-20,-10,0},{-10,0,10},{0,10,20},{10,20,30}};
float miux2[nax2][3] = {{1,1,0},{0,1,0},{0,1,0},{0,1,1}};
int npx2 = 3;
float y[nay] = {0,10,20,30,40};
int reg[nax1][nax2] = {{4,4,3,2,2},{4,3,2,2,1},{3,2,2,1,0},{2,2,1,0,0}};


float fapart(float, float*, float*, int);
void intersectie(float*,float*,int,float*,float*,int,float*,float*);
void reuniune(float*,float*,int,float*,float*,int,float*,float*);
//float defuzifica(float*,float*,int);

void main(void)
{
float x1c,x2c, miux1c[nax1],miux2[nax2], miuy[nay];
float xI[N+1], miuI[N+1];
float xR[N+1], miuR[N+1];
float xA[]={0,2,4}, miuA[]={0,1,0}, xB[]={2,4,5,6}, miuB[]={0,1,1,0};
float xc;
int npA=3, npB=4;
	 clrscr();

 intersectie(xA,miuA,npA, xB,miuB,npB, xI,miuI);
 reuniune(xA,miuA,npA, xB,miuB,npB, xR,miuR);
// printf("Introduceti punctul:");
// scanf("%f",&xc);
// printf("apartenenta este: %f",fapart(xc,xA,miuA,npA));
 getch();
  }
  
float fapart(float xc, float x[], float miux[], int npx)
{
	if(xc<x[0])
		return miux[0];
	for(int i=0;i<=npx-2;i++)
		if(xc>=x[i]&&xc<=x[i+1])
		{
			if(miux[i]<miux[i+1])
				return	(xc-x[i])/(x[i+1]-x[i])*(miux[i+1]-miux[i])+miux[i];
			else if(miux[i]==miux[i+1])
				return miux[i];
			else
				return (x[i+1]-xc)/(x[i+1]-x[i])*(miux[i]-miux[i+1])+miux[i+1];
		}
		return miux[npx-1];
}
void intersectie(float xA[], float miuA[], int npA, float xB[], float miuB[], int npB, float xI[], float miuI[])
 {
   float xinf, xsup, step;
	xinf=min(xA[0], xB[0]);
	xsup=max(xA[npA-1], xB[npB-1]);
	step=(xsup-xinf)/N;
	printf("*************Intersectia*************\n\n");
   for(int i=0;i<=N;i++)
	 {
	   xI[i]=xinf+step*i;
	   miuI[i]=min(fapart(xI[i], xA, miuA, npA),fapart(xI[i], xB, miuB, npB));
	   printf("\tmiuI[%d] = %f \n",i, miuI[i]);
	  }

 }

 void reuniune(float xA[], float miuA[], int npA, float xB[], float miuB[], int npB, float xI[], float miuI[])
   {
	float xinf, xsup, step;
		xinf=min(xA[0], xB[0]);
		xsup=max(xA[npA-1], xB[npB-1]);
		step=(xsup-xinf)/N;
		printf("\n************Reuniune*****************\n\n");
	for(int i=0;i<=N;i++)
	  {
		xI[i]=xinf+step*i;
		miuI[i]=max(fapart(xI[i], xA, miuA, npA),fapart(xI[i], xB, miuB, npB));
		printf("\tmiuI[%d] = %f \n",i, miuI[i]);
	   }
	}

