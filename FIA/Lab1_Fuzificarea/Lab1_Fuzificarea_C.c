/*
** Title: FIA --> Lab. 1
** Description: Fuzificarea
*/

#include<stdio.h>

#define nfx 3
#define npx 4

#define primul_element 0
#define ultimul_element npx-1

#define experienta_mica 0
#define experienta_medie 1
#define experienta_mare 2


float grad_apart(float _xc, float* _x, float* _y, int np);

float    x[nfx][npx]={ {0,3,5,5},{3,5,10,15},{0,10,15,50} };

float miux[nfx][npx]={ {1,1,0,0}, {0,1,1,0}, {0,0,1,1} };

int main()
{
    float xc, miu_xc;
    int tip_experienta = 0;

    printf("Introduceti o valoare pentru xc si apoi apasati Enter\r\n");
    scanf("%f",&xc);

    if(xc > x[experienta_mica][primul_element] && xc < x[experienta_mica][ultimul_element])
        tip_experienta = experienta_mica;
    else if(xc > x[experienta_medie][primul_element] && xc < x[experienta_medie][ultimul_element])
        tip_experienta = experienta_medie;
    else if(xc > x[experienta_mare][primul_element] && xc < x[experienta_mare][ultimul_element])
        tip_experienta = experienta_mare;
    else
        printf("numarul nu face parte din intervalul de date\r\n");

    miu_xc = grad_apart(xc, x[tip_experienta],miux[tip_experienta] , npx );

    printf("miu_xc = %f\r\n",miu_xc);

    return 0;
}

float grad_apart(float _xc, float* _x, float* _y, int np)
{
    int i = 0;

    if(_xc < _x[0])
        return _y[0];

    for( i = 0; i < np-1; i++ )
        if( _xc > _x[i] && _xc < _x[i+1] )
        {
            if( _y[i] < _y[i+1])
                return ( (_xc - _x[i]) / (_x[i+1] - _x[i]) * (_y[i+1] - _y[i]) + _y[i] );

            if( _y[i] == _y[i+1] )
                return _y[i];

            if( _y[i] > _y[i+1] )
                return ( (_x[i+1] - _xc)/(_x[i+1] - _x[i]) * (_y[i] - _y[i+1]) + _y[i+1] );
        }
    return _y[np-1];

}


