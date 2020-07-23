#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define pi 3.14159265358979323846
#define e 0.01

double gamma(double x)
{
	double res;
	if(x==1)
	{
		res=1.0;
	}
	else if(x==0.5)
	{
		res=sqrt(pi);
	}
	else
	{
		return (x-1)*gamma(x-1);
	}
}

double f(double t, int v)
{
	double a1=(v+1)/2.0; 
	double a2=v/2.0; 
	double nu= gamma(a1);
	double de = (sqrt(v*pi)*gamma(a2));
	double pow = pow((1+((t*t*1.0)/v)), (-1*a1));
	return (nu/de)*pow;
}



double simps(int t,int N,int x)
{
	int h=(t)/(N-1);
	int f0=f(0);
	int fn=f(t);
	double sum1=0;
	for(i=1;i<N;i+=2)
	{
		sum1=sum1+f(x)+i*h;
	}
	sum1=4*sum1;
	double sum2=0;
	for(i=2;i<N-1;i+=2)
	{
		sum2=sum2+f(x)+i*h;
	}
	sum2=2*sum2;
	double fs;
	fs=(h/3)*(f0+fn+sum1+sum2);
	return fs;
}




int main()
{
	double t;
	printf("enter the value of t-");
	scanf("%f\n",&t);
	int v;
	printf("enter the degrees of freedom-");
	scanf("%d\n",&v);
	int t;
	printf("enter the number of tails-");
	scanf("%d",&t);

}