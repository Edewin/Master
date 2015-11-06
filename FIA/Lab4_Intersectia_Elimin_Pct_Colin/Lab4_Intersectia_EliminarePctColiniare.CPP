/***************************************************
* Laborator 4 -> Intersectia + elim_pcte_coliniare 
*			 
*	"Versiunea de la tabla"
*  
* Nu stiu daca versiunea a fost testata!!! 
****************************************************/

#include<stdio.h>
#include<conio.h>
#include<math.h>
#define min(x,y) ((x>y)?(y):(x))
#define max(x,y) ((x>y)?(x):(y))
#define N 71


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
