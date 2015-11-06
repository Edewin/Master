/***************************************************
* Laborator 3 -> Reuniunea & Intersectia 
			  -> Fuzificare + Defuzificare
*			  -> fara eliminarea punctelor coliniare
*
*	"Versiune necunoscuta"  
*
* Nu stiu daca versiunea a fost testata!!!!
****************************************************/

#include<stdlib.h>
#include<conio.h>
#include<stdio.h>
#define N 20
#define min(a,b) ((a<b)?(a):(b))
#define max(a,b) ((a>b)?(a):(b))


float fapart(float, float*, float*, int);
void intersectie(float*,float*,int,float*,float*,int,float*,float*);
void reuniune(float*,float*,int,float*,float*,int,float*,float*);
float defuzifica(float*,float*,int);

void main(void)
{
	 float xI[N+1], miuI[N+1];
	 float xR[N+1], miuR[N+1];
	 float xA[]={0,2,4}, miuA[]={0,1,0}, xB[]={2,4,5,6}, miuB[]={0,1,1,0};
	 float xc;
	 int npA=3, npB=4;

	 clrscr();

	 intersectie(xA,miuA,npA, xB,miuB,npB, xI,miuI);
	 reuniune(xA,miuA,npA, xB,miuB,npB, xR,miuR);
	 printf("Introduceti pretul:");

	 scanf("%f",&xc);
	 printf("apartenenta este: %f",fapart(xc,xA,miuA,npA));
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
			else
			if(miux[i]==miux[i+1])
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
	   for(int i=0;i<=N;i++)
	   {  xI[i]=xinf+step*i;
		  miuI[i]=min(fapart(xI[i], xA, miuA, npA),fapart(xI[i], xB, miuB, npB));
	   }

}

void reuniune(float xA[], float miuA[], int npA, float xB[], float miuB[], int npB, float xI[], float miuI[])
{
	   float xinf, xsup, step;
	   xinf=min(xA[0], xB[0]);
	   xsup=max(xA[npA-1], xB[npB-1]);
	   step=(xsup-xinf)/N;
	   for(int i=0;i<=N;i++)
	   {  xI[i]=xinf+step*i;
		  miuI[i]=max(fapart(xI[i], xA, miuA, npA),fapart(xI[i], xB, miuB, npB));
	   }



}

float defuzifica(float y[],float miuy[],int npy)
{
	
	float A1,Cg1,A2,Cg2,S1=0,S2=0;
	for(int i=0;i<npy-1;i++)
	{
		A1=	(y[i+1]-y[i]) * min(miuy[i],miuy[i+1]);
		Cg1= (y[i]+y[i+1]) / 2;
		A2= (miuy[i]-miuy[i+1]) * ((miuy[i]>miuy[i+1])?(1):(-1)) * (y[i+1]-y[i]) / 2;
		Cg2= (y[i]+y[i+1]+((miuy[i]>miuy[i+1])?y[i]:y[i+1]))/3;
	
		S1+=(A1*Cg1+A2*Cg2)/(A1+A2);
		S2+=A1+A2;	
	
		printf("A[%d]=%f, Cg[%d]=%f\n",i,A1+A2,i,(A1*Cg1+A2*Cg2)/(A1+A2));
	}
	return S1/S2;
}
