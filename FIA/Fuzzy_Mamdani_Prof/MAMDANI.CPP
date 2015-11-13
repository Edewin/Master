/*****************
*	FIA -> Versiunea de la prof. (MAMDANI)
*
*****************/

#include <stdio.h>
#include <conio.h>
#include <math.h>
#define min(a,b)  ((a<b)?a:b)
#define max(a,b)  ((a<b)?b:a)
#define nmfx1 5
#define nmfx2 4
#define nmfy 5
#define npcteR 100

float x1[nmfx1][3]    = {{-2,-1,2},{-2,-1,0},{-1,0,1},{0,1,2},{-2,1,2}};
float miux1[nmfx1][3] = {{ 1, 0,0},{ 0, 1,0},{ 0,1,0},{0,1,0},{ 0,0,1}};
int npx1 = 3;
float x2[nmfx2][4]    = {{0,1,2,6},{1,2,3,4},{3,4,5,6},{0,0,5,6}};
float miux2[nmfx2][4] = {{1,1,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,1}};
int npx2 = 4;
float y[nmfy][3]    = {{0,2,10},{0,2,4},{2,4,6},{4,6,8},{6,8,10}};
float miuy[nmfy][3] = {{1,0, 0},{0,1,0},{0,1,0},{0,1,0},{0,1, 1}};
int npy = 3;
int reg[nmfx1][nmfx2]={{2,1,0,0},{2,2,1,0},{3,2,2,1},{4,3,2,2},{4,4,3,2}};

float grad_apartenenta(float, float*, float*, int);
float defuzifica(float*, float*, int);
int elimin_pcte(float*, float*, int, float*, float*);

int main(void)
{
	float x1c, x2c, gax1[nmfx1], gax2[nmfx2], gay[nmfy], m;
	float R[npcteR+1], miuR[npcteR+1], yinf=0, ysup=10, step, yc; // yinf=y[0][0]; ysup=[nmfy][3];
	float nR[20], nmiuR[20];
	int i, j, np;
 //   clrscr();
	printf("Valoare x1="); scanf("%f",&x1c);
	printf("Valoare x2="); scanf("%f",&x2c);
//Fuzificare intrari
	for(i=0; i<nmfx1; i++)
		gax1[i] = grad_apartenenta(x1c, x1[i], miux1[i], npx1);
	for(i=0; i<nmfx2; i++)
		gax2[i] = grad_apartenenta(x2c, x2[i], miux2[i], npx2);
	for(i=0; i<nmfy; i++)
		gay[i] = 0;
//Reguli fuzzy
	for(i=0; i<nmfx1; i++)
		for(j=0; j<nmfx2; j++)
			if (gax1[i]!=0 && gax2[j]!=0)
			{	m = min(gax1[i], gax2[j]);
				if (m > gay[reg[i][j]])
					gay[reg[i][j]]=m;
			}
//Reuniune
	step = (ysup-yinf)/npcteR;
	for(i=0; i<=npcteR; i++)
	{	m = 0;
    	yc = yinf+step*i;
		for(j=0; j<nmfy; j++)
			m = max(m, min(gay[j], grad_apartenenta(yc,y[j],miuy[j],npy)));
    	miuR[i]=m;
    	R[i]=yc;
//		printf("(%.2f %.2f)", yc,m);
	}
//Eliminare puncte coliniare
	np = elimin_pcte(R, miuR, npcteR+1, nR, nmiuR);

//Defuzificare
	yc=defuzifica(R,miuR,npcteR+1);
	printf("\nValoare iesire %.2f", yc);
	yc=defuzifica(nR,nmiuR,np);
	printf("\nValoare iesire (metoda 2)%.2f", yc);

	getch();
	return 0;
}

float grad_apartenenta(float xc, float x[], float miux[], int npx)
{
	if (xc<x[0]) return miux[0];
	for (int i=0; i<=npx-1; i++)
		if (xc>=x[i] && xc<=x[i+1])
		{   return (xc - x[i + (miux[i]>miux[i+1]) ])/(x[i+1]-x[i])*(miux[i+1]-miux[i]) +
						 min(miux[i],miux[i+1]);
		/*	if (miux[i+1]>miux[i])
				return (xc-x[i])/(x[i+1]-x[i])*(miux[i+1]-miux[i])+miux[i];
			if (miux[i+1]==miux[i])
                return miux[i];
			if (miux[i+1]<miux[i])
				return (x[i+1]-xc)/(x[i+1]-x[i])*(miux[i]-miux[i+1])+miux[i+1];
		 */
		}
	//if (xc>x[npx-1])
	return miux[npx-1];
}

int elimin_pcte(float R[], float miuR[], int p, float nR[], float nmiuR[])
{
	float x1, x2, x3, y1, y2, y3, m1, m2;
	int np;
	x1=R[0]; x2=R[1]; x3=R[2];
	y1=miuR[0]; y2=miuR[1]; y3=miuR[2];
    np=0;
	for (int i=3; i<p; i++)
	{
		m1 = (y2-y1)/(x2-x1);
		m2 = (y3-y2)/(x3-x2);
		if (fabs(m1-m2)<0.00001)
		{	x2=x3; y2=y3;	} //eliminarea punctului central (x2,y2)
		else //salvarea punctului (x1,y1)
		{   nR[np]= x1; nmiuR[np]= y1; np++;
			x1=x2; y1=y2; x2=x3; y2=y3;
		}
		x3 = R[i]; y3=miuR[i];
	}
	m1 = (y2-y1)/(x2-x1);
	m2 = (y3-y2)/(x3-x2);
	nR[np]=x1; nmiuR[np]=y1; np++;
	if (fabs(m1-m2)>0.00001)
	{	nR[np]=x2; nmiuR[np]=y2; np++; }
	nR[np]=x3; nmiuR[np]=y3; np++;

	for (int i=0; i<np; i++)
		printf("(%.2f %.2f)", nR[i],nmiuR[i]);
    return np;
}

float defuzifica(float y[], float miuy[], int npy)
{
	float cog, S1, S2, arie, cg, arie2, cg2;
    S1=0; S2=0;
	for (int i=1; i<npy; i++)
	{
		if (miuy[i]==miuy[i-1]) //dreptunghi
		{	cg = (y[i]+y[i-1])/2; arie = miuy[i]*(y[i]-y[i-1]);  }
		else if (miuy[i]==0 || miuy[i-1]==0) //triunghi
		{
            cg=(y[i-1]+y[i] + ((miuy[i]>miuy[i-1])?y[i]:y[i-1]) )/3;
			arie = ((y[i]-y[i-1])*(float)fabs((double)(miuy[i]-miuy[i-1])) )/2;
		} else // trapez
        {
			cg=(y[i-1]+y[i] + ((miuy[i]>miuy[i-1])?y[i]:y[i-1]) )/3;
			arie = ((y[i]-y[i-1])*(float)fabs((double)(miuy[i]-miuy[i-1])) )/2;
			cg2 = (y[i]+y[i-1])/2;
			arie2 = min(miuy[i],miuy[i-1])*(y[i]-y[i-1]);
			cg = (cg*arie+cg2*arie2)/(arie+arie2);
			arie += arie2;
		}
//		printf("Arie%d: %f, Cg%d: %f\n", i, arie, i, cg);
		S1 += arie*cg;
        S2 += arie;
	}
    return S1/S2;
}
