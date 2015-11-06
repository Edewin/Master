/***************************************************
* Laborator 5	-> Reguli Fuzzy  -- Mandani --
*				-> Intersectia + elim_pcte_coliniare 
*			 
*	"Versiunea de la tabla"
*  
* Versiune NETESTATA!!! (scrisa in Notepad++)
****************************************************/

#include<stdio.h>
#include<conio.h>
#include<math.h>

#define min(x,y) ((x>y)?(y):(x))
#define max(x,y) ((x>y)?(x):(y))
#define N 71

/********************
*	Lab 5
********************/
#define nfx1 5
#define nfx2 5
#define nfy 7

// x1 <=> E
float x1[nfx1][3] = {{-100,-15,-5},{-15,-5,0},{-5,0,5},{0,5,15},{5,15,100}};
float miux1[nfx1][3] = {{1,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,1}};
int npx1 = 3;

// x2 <=> vE (variatia lui E)
float x2[nfx2][3] = {{-5,-3,-1},{-3,-1,0},{-1,0,1},{0,1,3},{1,3,5}};
float miux2[nfx2][3] = {{1,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,1}};
int npx2 = 3;

// y <=> acc (acceleratia)
float y[nfy][3] = {{-30,-20,-10},{-20,-10,-5},{-10,-5,0},{-5,0,5},{0,5,10},{5,10,20},{10,20,30}};
float miuy[nfy][3] = {{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0}};
int npy = 3;

// Matricea de reguli s-a definit dupa indexul vectorului y (nfy = 7)
/* unde: 	NM   -> 0	|	Z   -> 3	|	PM -> 6		|
			Nmed -> 1	|	Pmed-> 4	|				|
			Nm   -> 2	|	Pm  -> 5	|				|
*************************************************************/
int reg[nfx1][nfx2] = { {0,1,1,2,2},{1,2,2,3,3},{2,3,3,3,5},{3,3,5,5,4},{5,5,4,4,6}};

// functia Mandani
float mandani(float Ec, float vEc)
{
	float gaE[nfx1],gavE[nfx2],gty[nfy];  // gty = grad trunchiere y
	int i, j;
	
	for(i=0; i<nfy; i++)
	{
		//initializarea vectorului gty
		gty[i] = 0;
	}
	for(i=0; i < nfx1; i++)
	{
		gaE[i] = grad_apart( Ec, x1[i], miux1[i], npx1 );
	}
	for(i=0;i < nfx2;i++)
	{
		gavE[i] = grad_apart( vEc, x2[i], miux2[i], npx2 );
	}
	for( i=0; i < nfx1; i++)
		for( j=0; j < nfx2; j++)
		{
			if(gaE[i] != 0 && gavE[i] != 0)
			{
				gty[reg[i][j]] = max( min(gaE[i], gavE[j]), gty[reg[i][j]]); 
			}
		}
	for(i=0; i < nfy; i++)
	{
		if(gty[i] != 0)
		{
			/*
			* Trebuie definit: 	-> R
			*					-> reuniune
			*					-> trunchiere
			*					-> yc
			*/
			R = reuniune(R,trunchiere(gty[i], y[i], miuy[i]);  														
		}
	}
	
	elim_pcte_coliniare( .. );
	yc = defazifica();
	
	return yc;
}
/*********************/


float a[]={0,2,4};
float b[]={2,4,6,7};
float ua[]={0,1,0};
float ub[]={0,1,1,0};
int npa=3, npb=4;
float xinf=0, xsup=7;



int elim_pcte_coliniare(float I[], float uI[], float F[], float uF[])
{

	float px1, py1, px2, py2, px3, py3, m1, m2; int npct=0;
	px1 = I[0]; py1=uI[0];
	px2 = I[1]; py2-uI[1];
	for(int i=2;i<N; i++)
	{ 
		px3=I[i]; py3=uI[i];
		m1 = (py2-py1)/(px2-px1); m2=(py3-py2)/(px3-px2);
		if(fabs(m1-m2)<0.00001)   //pct coliniare
		{ 
			px2=px3; py2=py3;
		}
		else
		{  
			F[npct]=px1; uF[npct]=py1; npct++;
			px1=px2; py1=py2;
			px2=px3; py2=py3;
		}
	}
	
	F[npct]=px1; uF[npct]=py1; npct++;
	F[npct]=px2; uF[npct]=py2; npct++;
	return npct;

}



float grad_apart(float ac, float a[], float ua[], int npa)
{
  if(ac<a[0]) return ua[0];
  for(int i=0;i<npa-1 ;i++)
  if(ac>=a[i]&&ac<a[i+1])
  {
	  if(ua[i]<ua[i+1])
		 return (ac-a[i])/(a[i+1]-a[i])*(ua[i+1]-ua[i])+ua[i];
	  if(ua[i]==ua[i+1])
		 return ua[i];
	  if(ua[i]>ua[i+1])
		 return (a[i+1]-ac)/(a[i+1]-a[i])*(ua[i]-ua[i+1])+ua[i+1];

  }
  return ua[npa-1];
}


void intersectie( float a[],float b[], float ua[], float ub[],int npa, int npb, float xinf, float xsup, float I[], float uI[])
{
	float xc, step = (xsup-xinf)/(N-1);
	for(int i=0; i<N; i++)
	{
	  xc = xinf + step*i;
	  I[i]=xc;
	  uI[i]=min(grad_apart(xc,a,ua,npa), grad_apart(xc,b,ub,npb));
	}
}
 void main()

{
	float I[N], uI[N],F[30],uF[30];
	intersectie(a, b, ua, ub, npa, npb, xinf, xsup, I, uI);
	int npct=elim_pcte_coliniare(I,uI,F,uF);
	getch();
}
