#include <iostream>
#include <math.h>
#define L 4
#define D 0.1123687877
#define T0 100
#define T1 20
#define Tt 60
#define t 10
using namespace std;

double f(double x ,double y){
    return ( (L*L/(D*(M_PI*M_PI))) * log((T0 - T1)/(y - T1)) ) - x;
}
	
int main(int argc, char *argv[]) {
	double a=10,b=20,h=0.1,k1,k2,k3,k4;
	int n;

	n = (b-a)/h;
	cout << "\nn=" << n;
	double *x = (double *)malloc((n+1) * sizeof(double)); //con n+1 porq por ejemplo si tengo a y b y tengo 5 puntos, voy a necesitar el a,1,2,3,4,b
	double *y = (double *)malloc((n+1) * sizeof(double));
	cout << "\nIngresar el dato inicial y(x0)\ny0:";
	cin >> y[0];
	x[0] = a;
	cout << "x0=" << x[0];
	cout << "y0=" << y[0];
	
	for(int i = 0 ; i < n ; i++){
		
		x[i+1] = x[i] + h;
		
		
		k1 = f(x[i],y[i]);
		
		k2 = f(x[i] + h/2 , y[i]+ (h/2)*k1);
		
		k3 = f(x[i] + h/2 , y[i]+ (h/2)*k2);
		
		k4 = f(x[i] + h , y[i] + k3 * h);
		
		y[i+1] = y[i] + (h/6)*(k1+2*k2+2*k3+k4);
		if(i==0)
			cout << "\nX" << "| Y"<<endl ;
		cout << i+1 << " = " << x[i+1] << " | " << i+1 << " = " << y[i+1]<<endl;
	}
	return 0;
}

