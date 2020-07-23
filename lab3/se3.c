#include<string.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

// FUNCTION f_l
void f_l(char name[])
{
	FILE *f;
	char l[1000];
	int st=0;
	int i_c=0;
	int cm=0;
	int len,i;	
	f=fopen(name,"r");
	if(f==NULL){
		printf("No such file exists\n");
	}
	// hellooooo
	while(fgets(l,1000,f)!=NULL)
	{
		len=strlen(l)-1;
		int whitespace=0;
		for(i=0;i<len;i++)
		{
			if(isspace(l[i]))
			{
				whitespace=whitespace+1;
				}
			}
		if(whitespace==len)
		{
			len=0;
			}
		if(len!=0)
		{	
			l[len]='\0';
			if(st==1)
			{
				i_c=i_c+1;
				if(cm==1)
				{
					i_c=i_c-1;
					cm=0;
					}
				}	
			char *token=strtok(l," \t");
			if(strcmp(token,"//")==0)
			{
				cm=1;
				token=strtok(NULL," \t");
				if(strcmp(token,"FUNCTION")==0)
				{
					if(st==1){
						st=0;
						cm=0;
						i_c=i_c-1;
						printf("lines of code - %d\n",i_c);
						i_c=0;
						}
					else
					{
						st=1;
						cm=0;
						token=strtok(NULL," \t");
						printf("Name of the function present in the file :%s\n",token);
						printf("/////////////////////////////////// \n");
						}
					}
				}
			}		
		}
	}
// FUNCTION


// FUNCTION c_l
int c_l(char filename[])
{
	FILE *ptr;
	char l[1010];
	int i_c=0;
	int i;
	int w=0;
	ptr=fopen(filename,"r");
	if(ptr==NULL)
	{
		printf("No such file exists\n");
		exit(0);
	}
	while(fgets(l,1010,ptr)!=NULL)
	{
		w=0;
		if(strlen(l)>1000)
		{
			printf("Limit exceeded \n");
			exit(0);
		}
		int len=strlen(l)-1;		
		for(i=0;i<len;i++)
		{
			if(isspace(l[i]))
			{
				w=w+1;
			}
		}
		if(len!=0)
		{
			i_c=i_c+1;
			if(w==len)
			{
		 	 i_c=i_c-1;
			}	 	
		}
	}
	return i_c;
}
// FUNCTION

// FUNCTION main
int main()
{
	char file[100];
	int i;
	printf("Name of the file :");
	scanf("%s",file);
	printf("/////////////////////////////////// \n");
	printf("LOC =  %d ls \n",c_l(file));
	printf("/////////////////////////////////// \n");
	f_l(file);	
}					
// FUNCTION						
