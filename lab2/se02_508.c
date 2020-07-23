#include<stdio.h>
#include<stdlib.h>

// FUNCTION PRINT
void print(char *c)
{
	while(*c)
	{
		printf("%c",*c);
		c++;
	}
	printf("\n");
}
// FUNCTION

// FUNCTION THING
void thing(FILE *fp)
{
	int i=0,j;
	int loc=0;
	char buffer[200],c;
	c = getc(fp);
	int sp=0;
	int cm=0;
	char fn[100];
	while(c!= EOF)
	{
		if(c=='/')
		{
			cm=cm+1;
		}
		while(c!='\n')
		{
			buffer[i]=c;
			i++;
			c = getc(fp);
		}
		if(getc(fp)=='\n')
			sp=sp+1;
		buffer[i] = '\0';
		for (j=0;j<i;j++)
		{
			
		}
		i=0;
		loc++;
		c = getc(fp);
	}
	loc=loc-sp-cm;
	printf("no. of lines of code is %d ",++loc);
}
// FUNCTION

// FUNCTION MAIN
int main()
{
	FILE *fp;
	char fileName[30];
	printf("File name: ");
	scanf("%s",fileName);
	fp = fopen(fileName,"r");
	thing(fp);
	printf("\n");
}
// FUNCTION