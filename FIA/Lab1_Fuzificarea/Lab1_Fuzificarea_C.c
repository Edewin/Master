/*
** Title: FIA --> Lab. 1
** Description: Fuzificarea
*/
#include<stdio.h>

#define NFX 3
#define NPX 4

#define PRIMUL_ELEMENT	0
#define ULTIMUL_ELEMENT (NPX-1)

#define EXPERIENTA_MICA 0
#define EXPERIENTA_MEDIE 1
#define EXPERIENTA_MARE 2


double grad_apart(double _xc, double* _x, double* _y, int np);

double    x[NFX][NPX]={ {0,3,5,5},{3,5,10,15},{10,10,15,50} };

double miux[NFX][NPX]={ {1,1,0,0}, {0,1,1,0}, {0,0,1,1} };

int main()
{
    double xc = 0.0;

    printf("Introduceti o valoare pentru xc si apoi apasati Enter\n");
    scanf("%lf",&xc);

	int tip_experienta = 0;

    if(xc > x[EXPERIENTA_MICA][PRIMUL_ELEMENT] && xc < x[EXPERIENTA_MICA][ULTIMUL_ELEMENT])
        {
			tip_experienta = EXPERIENTA_MICA;
		}
    else if(xc > x[EXPERIENTA_MEDIE][PRIMUL_ELEMENT] && xc < x[EXPERIENTA_MEDIE][ULTIMUL_ELEMENT])
        {
			tip_experienta = EXPERIENTA_MEDIE;
		}
    else if(xc > x[EXPERIENTA_MARE][PRIMUL_ELEMENT])
        {
			tip_experienta = EXPERIENTA_MARE;
		}
    else
        {
			printf("Numarul nu face parte din intervalul de date\n");
		}

    double miu_xc = grad_apart(xc, x[tip_experienta],miux[tip_experienta] , NPX );

    printf("miu_xc = %.2f\n",miu_xc);

    return 0;
}

double grad_apart(double _xc, double* _x, double* _y, int np)
{
    int i = 0;

    if(_xc < _x[0])
        return _y[0];

    for( i = 0; i < np-1; i++ )
		{
			if( _xc > _x[i] && _xc < _x[i+1] )
			{
				if( _y[i] < _y[i+1])
					return ( (_xc - _x[i]) / (_x[i+1] - _x[i]) * (_y[i+1] - _y[i]) + _y[i] );

				if( _y[i] == _y[i+1] )
					return _y[i];

				if( _y[i] > _y[i+1] )
					return ( (_x[i+1] - _xc)/(_x[i+1] - _x[i]) * (_y[i] - _y[i+1]) + _y[i+1] );
			}
		}
    return _y[np-1];

}


