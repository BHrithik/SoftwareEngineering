//////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define ERROR 0.01
int counter;
//////////////////////////////////////////////////////////////////////////////////
int inputChecker(char *string)
{
	int number = 0;
	while(*string)
	{
		if(*string > 57 || *string <48)
			return -1;							
		number = number*10 +(*string%48);      
		string++;
	}
	return number;
}
//////////////////////////////////////////////////////////////////////////////////
double gamma_function(double value)
{
	if(value<=0)
	{
		printf("INVALID INPUT\n");
		exit(0);
	}
	if(value == 1)
		return 1;
	else if(value == 0.5)
		return sqrt(M_PI);
	else
		return((value-1)*gamma_function(value-1));
}
//////////////////////////////////////////////////////////////////////////////////
double t_function(double t, int dof)
{
	double value1=(dof+1)/2.0, value2=dof/2.0, numerator = gamma_function(value1), denomenator = (sqrt(dof*M_PI)*gamma_function(value2)), power = pow((1+((t*t*1.0)/dof)), (-1*value1));
	return(numerator/denomenator)*power;
}
//////////////////////////////////////////////////////////////////////////////////
double find_sum(int intervals, double array[intervals])
{
	int iterator;
	double sum=0.0;
	for(iterator=0; iterator<intervals;iterator++)
		{
			if(iterator==0)
				sum+=array[iterator];
			else if(iterator==intervals-1)
	  
	  			sum+=array[iterator];
			else if(iterator%2==1 && iterator!=intervals-1)
				sum+=4*array[iterator];
			else
				sum+=2*array[iterator];
		}
		return sum;
}
//////////////////////////////////////////////////////////////////////////////////
void integrate(double t, int dof, int tails)
{
	int interval1=4, interval2=2*interval1, iterator;
	double sum1=0, sum2=0;
	while(1)
	{
		double array1[interval1], h1=t/(interval1-1), x1=0;
		double array2[interval2], h2=t/(interval2-1), x2=0;
		double error=0;
		array1[0]=t_function(0,dof);
		array2[0]=t_function(0,dof);
		for(iterator=1; iterator<interval1;iterator++)
		{
			x1=x1+h1;
			array1[iterator]=t_function(x1,dof);
		}
		sum1 =(h1/3)*find_sum(interval1,array1);
		for(iterator=1; iterator<interval2;iterator++)
		{
			x2=x2+h2;
			array2[iterator]=t_function(x2,dof);
		}
		sum2 =(h2/3)*find_sum(interval2,array2);
		if(sum1>=sum2)
			error= sum1-sum2;	
		else
			error=sum2-sum1;
		if(error<ERROR)
			break;
		else
		{
			interval1=interval2;
			interval2=2*interval1;
		}
	}
	if(tails==1)
		printf("  %d\t\t%lf\t\t%d\t\t\t  %d\t\t  %lf\n",counter++,t,dof,tails,0.5+sum2);
	else if(tails == 2)
		printf("  %d\t\t%lf\t\t%d\t\t\t  %d\t\t  %lf\n",counter++,t,dof,tails,2*sum2);
	else
		printf("  --------------------------------INVALID INPUT DETECTED----------------------------------\n");
}
//////////////////////////////////////////////////////////////////////////////////
void processData(int size, double xArray[size], int yArray[size], int zArray[size])
{
	int iterator;
	for(iterator=0;iterator<size;iterator++)
		integrate(xArray[iterator],yArray[iterator],zArray[iterator]);
}
//////////////////////////////////////////////////////////////////////////////////
int countNumberOfInputs(FILE* fp)//reused
{
	int counter=0;
	char pointer = fgetc(fp);
	while(pointer!= EOF)
	{
		if(pointer == '\n' || pointer == EOF)
			counter++;
		pointer = fgetc(fp);
	}
	return counter+1;
}
//////////////////////////////////////////////////////////////////////////////////
void fillArrays(FILE *fp, int size, double xArray[size],int yArray[size], int zArray[size])
{
	int counter=0,flag=0, c=0;
	double number=0, decimal=1, left=0;
	char pointer = fgetc(fp);
	while(pointer!=EOF)
	{
		if(pointer == '\t')// filling x and y
		{
			if(flag == 1)// filling x with doubles
			{
				xArray[counter] = (number+left);
				flag = 0;
				left=0;
				number=0;
				decimal = 1;
				c=1;
			}
			else if(c == 1)// filling y with an int 
			{
				yArray[counter]=number;
				number=0;
				c=0;
			}
		}
		else if(pointer == '\n')// filling z
		{
			zArray[counter]=number;
			number=0;
			counter++;
		}
		else
		{
			if(flag == 0)
			{
				if(pointer>=48 && pointer<=57)
					number = (number*10)+(pointer%48);
				else if(pointer == '.')
					flag=1;
			}
			else if(flag == 1)
			{
				if(pointer>=48 && pointer<=57)
					decimal = (decimal/10);
					left = left+(decimal*(pointer%48));
			}
			else
			{
				printf("ERROR: INPUT FILE HAS AN INVALID ENTRY\n");
				exit(0);
			}
		}
		pointer = fgetc(fp);
	} 
	zArray[counter] = number;
}
//////////////////////////////////////////////////////////////////////////////////
void textFileInput()//resued
{
	int numberOfInputs,iterator;
	char fileName[50];
	FILE *fp;
	printf("FILE NAME: ");
	scanf("%[^\n]",fileName);

	fp = fopen(fileName, "r");
	if(fp == NULL)
	{
		printf("ERROR\nFILE: %s NOT FOUND\n", fileName);
	    return;
	}

	else
	{
		numberOfInputs =countNumberOfInputs(fp);
		double xArray[numberOfInputs];
		int yArray[numberOfInputs],zArray[numberOfInputs];
		for(iterator=0; iterator<numberOfInputs; xArray[iterator]=0,yArray[iterator]=0,zArray[iterator]=0,iterator++);
		fp = fopen(fileName, "r");
		fillArrays(fp,numberOfInputs,xArray,yArray,zArray);
		printf("---------------------------------------------------------------------------------------------\n");
		printf("TESTS\t\t   t\t\tDEGREES OF FREEDOM\t\tTAILS\t\tPROBABILITIES\n");
		printf("---------------------------------------------------------------------------------------------\n");
		processData(numberOfInputs, xArray, yArray, zArray);
	}	
}
//////////////////////////////////////////////////////////////////////////////////
void manualInput()
{
	int numberOfInputs, iterator;
	printf("MESSAGE: PLEASE ENTER THE T VALUE, DOF AND TAILS SEPERATED BY SPACES\n");
	printf("--------------------------------------------------------------------\n");
	printf("NUMBER OF INPUTS: ");
	scanf("%d", & numberOfInputs);
	printf("-------------------\n");
	int yArray[numberOfInputs], zArray[numberOfInputs];
	double xArray[numberOfInputs];
	for(iterator=0; iterator<numberOfInputs; iterator++)
	{
		printf("INPUT NUMBER %d: ", iterator+1);
		scanf("%lf %d %d", &xArray[iterator], &yArray[iterator], &zArray[iterator]);
		printf("--------------------------------\n");
	}
	printf("---------------------------------------------------------------------------------------------\n");
	printf("TESTS\t\t   t\t\tDEGREES OF FREEDOM\t\tTAILS\t\tPROBABILITY\n");
	printf("---------------------------------------------------------------------------------------------\n");
	processData(numberOfInputs, xArray, yArray, zArray);

}
//////////////////////////////////////////////////////////////////////////////////
int main()
{
	int value;
	char response[2];
	counter=1;
	printf("//////////////////////////////////////////////////////////////////////////////////////////////\n");
	printf("INSTRUCTIONS AND DESCRIPTION:\n-----------------------------------\n");
    printf("-THE PROGRAM CALCULATES THE PROBABLITY VALUE OF A T-DISTRIBUTION GIVEN THE NUMBER OF TAILS AND DEGREES OF FREEDOM\n");
    printf("-THE INPUT CAN BE GIVEN IN 2 WAYS:\n\t-MANUAL INPUT\n\t-INPUT FROM A TEXT FILE\n");
    printf("-IN THE INPUT FILE, DO NOT LEAVE EMPTY LINES, IT WILL LEAD TO INVALID AN OUTPUT\n");
    printf("//////////////////////////////////////////////////////////////////////////////////////////////\n");
	printf("1 FOR MANUAL INPUT\n2 FOR TEXT FILE INPUT\n");
	printf("-----------------------\n");
	while(1)
	{
		printf("RESPONSE: ");
		scanf("%[^\n]",response);
		value = inputChecker(response);
		if(value == -1)
		{
			printf("WRONG RESPONSE, PLEASE ENTER A CORRECT ONE\n");
			getchar();
			continue;
		}
		else
		{
			if(strcmp(response,"1") == 0)
			{	
				printf("-----------\n");
				manualInput();
				break;
			}
			else if(strcmp(response,"2") == 0)
			{
				printf("------------------------\n");
				getchar();
				textFileInput();
				break;
			}
			else
				printf("WRONG RESPNOSE, PLEASE ENTER A CORRECT ONE\n");
				getchar();		
		}
	}
	printf("---------------------------------------------------------------------------------------------\n");
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////
