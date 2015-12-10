//============================================================================
// Name        : SugenoBun.cpp
// Author      : Eduard
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <math.h>

#define min(a,b)  ((a<b)?a:b)
#define max(a,b)  ((a<b)?b:a)
#define nmfx1 5
#define nmfx2 5
#define nmfy 5

/*********************************
 * De inlocuit cu valorile voastre
 * */
#define MIN_x1c 0
#define MAX_x1c 90
#define PAS_x1c 10

#define MIN_x2c 0
#define MAX_x2c 90
#define PAS_x2c 10

using namespace std;

// intrarea 1  --> senzorul stanga
float x1[5][4]={{0,10,20,30} ,
				{20,20,30,40},
				{30,30,40,50},
				{40,40,50,60},
				{50,60,70,80} };

float miux1[5][4]={ {1,1,1,0} ,
					{0,0,1,0} ,
					{0,0,1,0},
					{0,0,1,0},
					{0,1,1,1}};
int npx1=4;

// intrarea 2  --> senzorul dreapta
float x2[5][4]={{0,10,20,30} ,
				{20,20,30,40} ,
				{30,30,40,50},
				{40,40,50,60},
				{50,60,70,80} };

float miux2[5][4]={ {1,1,1,0} ,
					{0,0,1,0} ,
					{0,0,1,0},
					{0,0,1,0},
					{0,1,1,1}};
int npx2=4;


// singletonii de iesire
float y[nmfy]   = {	0.2,	// 0 grade		--> U1
					0.4, 	// 45 grade		--> U2
					0.5, 	// 90 grade		--> U3
					0.6, 	// 135 grade	--> U4
					0.8};	// 180 grade	--> U5

// Matricea de reguli s-a definit dupa indexul vectorului y (nmfy = 5)
/* unde:
 * 		U1   -> 0	|	U4	-> 3	|
		U2	 -> 1	|	U5	-> 4	|
		U3	 -> 2	|				|
*************************************************************/

int reg[nmfx1][nmfx2]={ {2,4,4,4,4},
						{0,2,3,3,3},
						{0,1,2,3,4},
						{0,1,1,2,3},
						{0,1,0,1,2}};


/************************************************************/

float grad_apartenenta(float, float*, float*, int);
float defuzifica(float*, float*);


int main()
{
	FILE *pf;
	float x1c, x2c, gax1[nmfx1], gax2[nmfx2], gay[nmfy], m;
	float  yc; // yinf=y[0][0]; ysup=[nmfy][3];
	int i, j;

//	printf("Valoare x1="); scanf("%f",&x1c);
//	printf("Valoare x2="); scanf("%f",&x2c);

	pf=fopen("test.csv","wt");

	for(x1c=MIN_x1c; x1c<MAX_x1c; x1c+= PAS_x1c)
		for(x2c = MIN_x2c; x2c < MAX_x2c; x2c+= PAS_x2c)
		{
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

		//Defuzificare
			yc=defuzifica(y,gay);
			printf("\nValoare iesire %.2f", yc);

			fprintf(pf,"%f,%f,%f\n",x1c,x2c,yc);
		}
	fclose(pf);

	return 0;
}

float grad_apartenenta(float xc, float x[], float miux[], int npx)
{
	if (xc<x[0]) return miux[0];
	for (int i=0; i<=npx-1; i++)
		if (xc>=x[i] && xc<=x[i+1])
		{

			return (xc - x[i + (miux[i]>miux[i+1]) ])/(x[i+1]-x[i])*(miux[i+1]-miux[i]) +
						 min(miux[i],miux[i+1]);
		}

	return miux[npx-1];
}

float defuzifica(float y[], float gay[])
{

	float  S1, S2;
	S1=0; S2=0;

	for (int i=0; i<nmfy; i++)
	{
		S1 += y[i]*gay[i];
		S2 += gay[i];
	}


	return S1/S2;

}
