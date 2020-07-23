#include<stdio.h>
#include<stdlib.h>
#include<math.h>



double mean(int l, int ar[l])
{
	int i;
	double s=0;
	for(i=0; i<l; i++)
		s += ar[i];

	return s/l;
}

double meand(int l, int ar[l], double m)
{
	int i;
	double s=0;
	for(i=0; i<l; i++)
		s += pow(ar[i]-m, 2);
	return s;
}

double c_b1(int l, int x[l], int y[l])
{
	int i;
	double s1=0, s2=0;
	double xm=mean(l,x);
	double ym= mean(l,y);
	for(i=0; i<l; i++)
	{
		s1+=(x[i]*y[i]);
		s2+=(x[i]*x[i]);
	}
	s1-=(l)*(xm)*(ym);
	s2-=(l)*(xm)*(xm);
	return(s1/s2);

}

double c_b0(int l, int x_a[l], int y_a[l])
{
	double x_m = mean(l,x_a);
	double y_m = mean(l,y_a);
	double b1 = c_b1(l, x_a, y_a);

	return y_m-(b1*x_m);
}


double c_sd(double b0, double b1, int l, int x[l], int y[l])
{
	int i;
	double s=0;
	for(i=0; i<l; i++)
		s+= pow((y[i]-(b1*x[i])-b0),2);
	return(sqrt(s/l));
}

double g_f(double v)
{
	if(v<=0)
	{
		printf("Please provide a proper input. \n");
		exit(0);
	}
	if(v == 1)
		return 1;
	else if(v == 0.5)
		return sqrt(M_PI);
	else
		return((v-1)*g_f(v-1));
}

double c_T(double t, int dof)
{
	double v1=(dof+1)/2.0; 
	double v2=dof/2.0;
	double n = g_f(v1);
	double d = (sqrt(dof*M_PI)*g_f(v2));
	double p = pow((1+((t*t*1.0)/dof)), (-1*v1));
	return(n/d)*p;
}

double c_sum(int n, double ar[n])
{
	int i;
	double s=0.0;
	for(i=0; i<n; i++)
		{
			if(i==0)
				s+=ar[i];
			else if(i==n-1)
	  			s+=ar[i];
			else if(i%2==1 && i!=n-1)
				s+=4*ar[i];
			else
				s+=2*ar[i];
		}
		return s;
}

double c_v(int e,int l, int ar[l])
{
	double m = mean(l, ar);
	double d = meand(l, ar, m);
	return sqrt(1+(1/l)+((e-m)/d));
}


double integ(double t, int dof, int tails)
{
	int i1=4, i2=8, i;
	double s1=0, s2=0;
	while(1)
	{
		double n1[i1];
		double n2[i2];
		double h1=t/(i1-1); 
		double x1=0;
		double h2=t/(i2-1); 
		double x2=0; 
		double er=0;
		n1[0]=c_T(0,dof);
		n2[0]=c_T(0,dof);
		for(i=1; i<i1;i++)
		{
			x1=x1+h1;
			n1[i]=c_T(x1,dof);
		}
		s1 =(h1/3)*c_sum(i1,n1);
		for(i=1; i<i2;i++)
		{
			x2=x2+h2;
			n2[i]=c_T(x2,dof);
		}
		s2 =(h2/3)*c_sum(i2,n2);
		if(s1>=s2)
			er= s1-s2;	
		else
			er=s2-s1;
		if(er<0.01)
			break;
		else
		{
			i1=i2;
			i2=2*i1;
		}
	}
	if(tails==1)
		return 0.5+s2;
	else if(tails == 2)
		return 2*s2;
	else return -1;
}

double ts(double A, double l, double u)
{
	double m = l+(u-l)/2.0;
	double temp;
	if (integ(m, 19, 2)>=A)
		temp = integ(m, 19, 2)-A;
	else
		temp = -1* (integ(m, 19, 2)-A);

	if(temp<=0.001) 
		return m;
	if  (integ(m, 19, 2)>A)
		return ts(A, l, m);
	if(A-integ(m, 19, 2)<A)
    	return ts(A, m, u); 
    return -1;
}

void	Calculate(int l, int locs[l], int d[l])
{
	int rls, pl, r70, r90;
	double b0 = c_b0(l, locs, d);
	double b1 = c_b1(l, locs, d);
	double sd = c_sd(b0, b1, l, locs, d);
	double v;
	double t;
	printf("Raw LOC count: ");
	scanf("%d", &rls);
	int rl[rls];
	for(int i=0; i<rls; i++)
	{
		printf("\n#####################################\n");
		printf("Raw Lines of Code  %d  :- ", i+1);
		scanf("%d", &rl[i]);
	}
	for(int i=0; i<rls;i++)
	{
		if(rl[i]>0)
		{
			pl  = (int)((b1*rl[i])+b0);
			v   = c_v(rl[i], l,locs);
			t   = ts(0.70, 0, 10);
			r70 = (int)(t*sd*v);
			t   = ts(0.90, 0, 10);
			r90 = (int)(t*sd*v);
		}
		else
		{
			pl=0;
			r90=0;
			r70=0;
		}
		printf("\n#####################################\n");
		printf("Raw Lines of Code  :- %d\n ##################################### \n predicted Lines of Code  :-%d70%% LPI:%d\n70%% UPI:%d\n90%% LPI:%d\n90%% UPI:%d\n \n ##################################### \n ", rl[i],pl,pl-r70,pl+r70,pl-r90,pl+r90);
	}
}

int main()
{
	printf("\n###############17XJ1A0508###############\n");
	int locs[20] = {255,475,362,341,469,255,248,195,223,310,191,449,258,233,347,284,339,135,280,303};
	int d[20] = {600,1440,300,780,1440,600,780,420,780,780,360,900,660,720,780,1020,960,300,660,420};
	int l = 20;
	Calculate(l, locs, d);
	return 0;
}
