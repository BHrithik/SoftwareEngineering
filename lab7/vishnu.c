#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double calcMean(int len, int arr[len])
{
	int i;
	double s=0;
	for(i=0; i<len; i++)
		s += arr[i];

	return s/len;
}
double calcMeanDif(int len, int arr[len], double mean)
{
	int i;
	double s=0;
	for(i=0; i<len; i++)
		s += pow(arr[i]-mean, 2);
	return s;
}
double calcVar(int E,int len, int arr[len])
{
	double mean = calcMean(len, arr);
	double diff = calcMeanDif(len, arr, mean);
	return sqrt(1+(1/len)+((E-mean)/diff));
}
double calcSd(double b0, double b1, int len, int x[len], int y[len])
{
	int i;
	double s=0;
	for(i=0; i<len; i++)
		s+= pow((y[i]-(b1*x[i])-b0),2);
	return(sqrt(s/len));
}
double calcB1(int len, int x[len], int y[len])
{
	int i;
	double s1=0, s2=0;
	double xMean=calcMean(len,x), yMean = calcMean(len,y);
	for(i=0; i<len; i++)
	{
		s1+=(x[i]*y[i]);
		s2+=(x[i]*x[i]);
	}
	s1-=(len*xMean*yMean);
	s2-=(len*xMean*xMean);
	return(s1/s2);

}
double calcB0(int len, int x_array[len], int y_array[len])
{
	double x_mean = calcMean(len,x_array), y_mean = calcMean(len,y_array);
	double b1 = calcB1(len, x_array, y_array);

	return y_mean-(b1*x_mean);
}
double gammaF(double val)
{
	if(val<=0)
	{
		printf("wrong input\n");
		exit(0);
	}
	if(val == 1)
		return 1;
	else if(val == 0.5)
		return sqrt(M_PI);
	else
		return((val-1)*gammaF(val-1));
}
double calcT(double t, int dof)
{
	double val1=(dof+1)/2.0, val2=dof/2.0, num = gammaF(val1), denom = (sqrt(dof*M_PI)*gammaF(val2)), power = pow((1+((t*t*1.0)/dof)), (-1*val1));
	return(num/denom)*power;
}
double calcSum(int n, double arr[n])
{
	int i;
	double s=0.0;
	for(i=0; i<n; i++)
		{
			if(i==0)
				s+=arr[i];
			else if(i==n-1)
	  
	  			s+=arr[i];
			else if(i%2==1 && i!=n-1)
				s+=4*arr[i];
			else
				s+=2*arr[i];
		}

		return s;
}
double integration(double t, int dof, int tails)
{
	int int1=4, int2=8, i;
	double s1=0, s2=0;
	while(1)
	{
		double num1[int1], h1=t/(int1-1), x1=0, num2[int2], h2=t/(int2-1), x2=0, err=0;
		num1[0]=calcT(0,dof);
		num2[0]=calcT(0,dof);
		for(i=1; i<int1;i++)
		{
			x1=x1+h1;
			num1[i]=calcT(x1,dof);
		}
		s1 =(h1/3)*calcSum(int1,num1);
		for(i=1; i<int2;i++)
		{
			x2=x2+h2;
			num2[i]=calcT(x2,dof);
		}
		s2 =(h2/3)*calcSum(int2,num2);
		if(s1>=s2)
			err= s1-s2;	
		else
			err=s2-s1;
		if(err<0.01)
			break;
		else
		{
			int1=int2;
			int2=2*int1;
		}
	}
	if(tails==1)
		return 0.5+s2;
	else if(tails == 2)
		return 2*s2;
	else return -1;
}
double tSearch(double area, double l, double u)
{
	double m = l+(u-l)/2.0, temp;
	if(integration(m, 19, 2)>=area)
		temp = integration(m, 19, 2)-area;
	else
		temp = -1*(integration(m, 19, 2)-area);

	if(temp<=0.001) 
		return m;
	if (integration(m, 19, 2)>area)
		return tSearch(area, l, m);
	if(area-integration(m, 19, 2)<area)
    	return tSearch(area, m, u); 
    return -1;
}
void calcRange(int len, int LOCs[len], int Da[len])
{
	int rawLOCs, predLOC, r70, r90;
	double b0 = calcB0(len, LOCs, Da), b1 = calcB1(len, LOCs, Da), sd = calcSd(b0, b1, len, LOCs, Da), var, t;
	printf("Raw LOC count: ");
	scanf("%d", &rawLOCs);
	int rawLOC[rawLOCs];
	for(int i=0; i<rawLOCs; i++)
	{
		printf("Raw LOC %d: ", i+1);
		scanf("%d", &rawLOC[i]);
	}
	for(int i=0; i<rawLOCs;i++)
	{
		if(rawLOC[i]>0)
		{
			predLOC = (int)((b1*rawLOC[i])+b0);
			var = calcVar(rawLOC[i], len, LOCs);
			t = tSearch(0.35, 0, 10);
			r70 = (int)(t*sd*var);
			t = tSearch(0.45, 0, 10);
			r90 = (int)(t*sd*var);
		}
		else
		{
			predLOC=0;
			r90=0;
			r70=0;
		}
		printf("Raw LOC:%d\npredicted_LOC:%d\n70%% LPI:%d\n70%% UPI:%d\n90%% LPI:%d\n90%% UPI:%d\n", rawLOC[i],predLOC,predLOC-r70,predLOC+r70,predLOC-r90,predLOC+r90);
	}
}
int main()
{
	int LOCs[20] = {255,475,362,341,469,255,248,195,223,310,191,449,258,233,347,284,339,135,280,303};
	int Da[20] = {600,1440,300,780,1440,600,780,420,780,780,360,900,660,720,780,1020,960,300,660,420};
	int len = 20;
	calcRange(len, LOCs, Da);
	return 0;
}
