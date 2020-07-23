#include<stdio.h>
#include<stdlib.h>

int summation(int A[],int N)
{
	int i,sum=0;
	for(i=0;i<N;i++)
	{
		sum=sum+A[i];
	}
	return sum;
}

int mean(int A[],int N)
{
	int i,sum=0;
	double mean;
	for(i=0;i<N;i++)
	{
		sum=sum+A[i];
	}
	mean=(double)(sum/N);
	return mean;
}

int main()
{
	int t,k;
	printf("\n**********************Linear Regression**********************\n");
	printf("Enter the number of Test cases -");
	scanf("%d",&t);
	if(t<=0)
			{
				printf("error please enter a valid input");
				exit(0);
			}
	for(k=0;k<t;k++)
	{
        int i,sumxy,sumxx;
        int n;
		printf("Enter the number of programs in this test case %d ",k+1);
		scanf("%d",&n);
		if(n<=0)
			{
				printf("error please enter a valid input");
				exit(0);
			}
		int x[n],y[n];
        for(i=0; i<n; i++)
        {
            x[i]=0;
            y[i]=0;
        }
		for(i=0;i<n;i++)
		{
            printf("program no. - %d \n ",i);
			printf("x-");
			scanf("%d",&x[i]);
			if(x[i]<=0)
			{
				printf("error please enter a valid input");
				exit(0);
			}
			printf("y-");
			scanf("%d",&y[i]);
			if(x[i]<=0)
			{
				printf("error please enter a valid input");
				exit(0);
			}
		}
        for(i=0; i<n; i++)
        {
            printf("%d",x[i]);
        }
            printf("\n");
        for(i=0; i<n; i++)
        {
            printf("%d",y[i]);
        }
		int xy[n];
		int xx[n];
		for(i=0;i<n;i++)
		{
			xy[i]=x[i]*y[i];
		}
		sumxy=summation(xy,n);
		for(i=0;i<n;i++)
		{
			xx[i]=x[i]*x[i];
		}
		sumxx=summation(xx,n);
		double mx=mean(x,n);
		double my=mean(y,n);
		double b0,b1;
        double nu,de;
        nu=sumxy-((n)*(mx)*(my));
        de=sumxx-((n)*(mx)*(mx));
		b1=(nu/de);
		b0=my-(b1*mx);
        printf("Test case- %d \n",k+1);
        printf("B0- %lf ",b0);
        printf("B1- %lf ",b1);
	}
	//int x1={240,300,600,480,780,420,360,180,780,240,360,420,660};
	//int y1={241,328,480,493,767,400,417,171,900,279,318,470,757};
}
