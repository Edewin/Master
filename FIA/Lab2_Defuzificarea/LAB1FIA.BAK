#include<stdio.h>
#include<conio.h>
#define nfx 3
#define npx 4

float x[nfx][4]={{0,0,3,5},{3,5,10,15},{10,15,50,50}};
float uc[nfx][4] = {{1,1,0,0},{0,1,1,0},{0,0,1,1}};



float z[]={0,2,5,6,8,9};
float miuz[]={0,0.5,0.5,0.8,0.8,0};
int npz=6;
float defuzificare(float *,float *, int);
float grad_apart(float,float *, float *,int);

void main()
{
	int i;
	float xc, miu;
	clrscr();
//	printf("introduceti x curent:");
//	scanf("%f",&xc);
//	miu=grad_apart(xc,x[1],uc[1],npx);
	miu = defuzificare(z, miuz,npz);
	printf("miu:%f \n",miu);
	getch();

}


float grad_apart(float xc, float x[], float y[], int np)
{
	if(xc<x[0]) return y[0];

	 for(int i=0 ; i<np-1 ; i++ )
		if (xc>=x[i] && xc<x[i+1])
		{
			if (y[i]<y[i+1])
				return (xc-x[i])/(x[i+1]-x[i])* (y[i+1]-y[i])+y[i];
			if (y[i]==y[i+1])
				return y[i];
			if (y[i] > y[i+1])
				return (x[i+1]-xc)/(x[i+1]-x[i]) * (y[i]-y[i+1]) + y[i+1];
		}
	return y[np-1];
	}

 float defuzificare(float z[], float miuz[],int npz)
 {
	float S1=0, S2=0, Ai,cgi;
	int i;
	for(i=0;i<npz-1;i++)
	 {
		if(miuz[i]==0||miuz[i+1]==0)
		  {
			Ai=(z[i+1]-z[i])*((miuz[i]>miuz[i+1])?(miuz[i]-miuz[i+1]):(miuz[i+1]-miuz[i]))/2;
			cgi=(z[i]+z[i+1]+((miuz[i]>miuz[i+1])?z[i]:z[i+1]))/3;
		  }
		else
		 if(miuz[i]==miuz[i+1])
		  {
			Ai=miuz[i]*(z[i+1]-z[i]);
			cgi=(z[i]+z[i+1])/2;
		  }
		else
		  {
			Ai=(z[i+1]-z[i])*((miuz[i]>miuz[i+1])?(miuz[i]-miuz[i+1]):(miuz[i+1]-miuz[i]))/2;
			cgi=(z[i]+z[i+1]+((miuz[i]>miuz[i+1])?z[i]:z[i+1]))/3;
			cgi=cgi*Ai+((miuz[i]<miuz[i+1])?miuz[i]:miuz[i+1])*(z[i+1]*z[i+1]-z[i]*z[i])/2;
			Ai=Ai+((miuz[i]<miuz[i+1])?miuz[i]:miuz[i+1])*(z[i+1]-z[i]);
			cgi=cgi/Ai;
		  }
		printf("%d cg: %f Aria:%f \n", i, cgi, Ai);
		S1=S1+cgi*Ai;
		S2+=Ai;
	 }
		return S1/S2;
 }