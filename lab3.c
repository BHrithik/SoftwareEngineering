#include<stdio.h>
#include<stdlib.h>
void print(char *c)
{
	while(*c)
	{
		printf("%c",*c);
		c++;
	}
	printf("\n");
}
void do_something(FILE *fp)
{
	int i;
	char buffer[200],c;
	c = getc(fp);
	while(c!= EOF)
	{
		while(c!='\n')
		{
			buffer[i]=c;
			i++;
			c = getc(fp);
		}
		buffer[i] = '\0';
		i=0;
		printf("//////////////////////\n");
		c = getc(fp);
	}
}
int main()
{
	FILE *fp;
	char fileName[30];
	printf("File name: ");
	scanf("%s",fileName);
	printf("jello");
	fp = fopen(fileName,"r");
	do_something(fp);
	printf("\n");
}