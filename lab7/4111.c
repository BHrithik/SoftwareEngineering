#include<stdio.h>
#include<math.h>
#include<stdlib.h>
double mean(double arr[], int n)
{ 
double z=0;
int i;
double k;
for(i=0;i<n;i++)
{
z=z+arr[i];
}
k=z/(double)n;
return k;
}
double calcMeanDif(int n, double arr[n], double m)
{
int i;
double s=0;
for(i=0; i<n; i++)
s=s+(pow(arr[i]-m, 2));
return s;
}
double calcVar(int E,int n, double arr[n])
{
double m =mean(arr,n);
double mean_diff = calcMeanDif(n, arr, m);
return sqrt(1+(1/n)+((E-m)/mean_diff));
}

double b00(int n, double a[n],double b[n]){
int i;
double b1,b0,x,y,x1,y1,c=0,d=0,xy,xy1,e=0,f=0,g,h,l;
for(i=0;i<n;i++){
c=c+b[i];
}
for(i=0;i<n;i++){
d=d+a[i];
}
x1=((double)d)/n;
y1=((double)c)/n;
for(i=0;i<n;i++){
e=e+b[i]*a[i];
}
xy1=(double)e;
for(i=0;i<n;i++){
f=f+a[i]*a[i];
}
g=(n*(double)x1*(double)x1);
l=((double)(f-g));
if(l==0){
printf("same values should not be given");
}
else{
b1=((double)(((double)xy1)-(n*(double)x1*(double)y1))/(l));
b0=y1-((double)b1*(double)x1);
y=((double)b1*(double)x)+b0;
}
return b0;
}

double b01(int n, double a[n],double b[n]){
int i;
double b1,b0,x,y,x1,y1,c=0,d=0,xy,xy1,e=0,f=0,g,h,l;
for(i=0;i<n;i++){
c=c+b[i];
}
for(i=0;i<n;i++){
d=d+a[i];
}
x1=((double)d)/n;
y1=((double)c)/n;
for(i=0;i<n;i++){
e=e+b[i]*a[i];
}
xy1=(double)e;
for(i=0;i<n;i++){
f=f+a[i]*a[i];
}
g=(n*(double)x1*(double)x1);
l=((double)(f-g));
if(l==0){
printf("same values should not be given");
}
else{
b1=((double)(((double)xy1)-(n*(double)x1*(double)y1))/(l));
b0=y1-((double)b1*(double)x1);
y=((double)b1*(double)x)+b0;
}
return b1;
}
double calcSd(int n, double a[n], double b[n])
{
int i;
double s=0;
double b0=b00( n, a,b);
double b1=b01( n, a,b);
for(i=0; i<n; i++)
s+= pow((b[n]-(b1*a[n])-b0),2);
return(sqrt(s/n));
}

double gam(double x)
{
if(x<=0)
{
printf("only poitive values");
exit(0);
}
else if(x==1)
return 1;
else if(x==0.5)
return sqrt(3.141592);
else
return(((x-1)*gam(x-1)));
}

double fun(double t,int v)
{
double v1,v2,num,den,power;
v1=(v+1)/2.0;
v2=(v/2.0);
num=gam(v1);
den=(sqrt(v*3.141592)*gam(v2));
power=pow((1+((t*t)/v)), ((-1)*v1));
return(num/den)*power;
}

double simpson_add(int i,double a[i])
{
int j;
double s=0.0;
for(j=0;j<i;j++)
{
if(j==0 && j==i-1)
s=s+a[j];
else if(j%2==1.0 && j!=i-1)
s=s+4*a[j];
else
s=s+2*a[j];
}
return s;
}

double simpson_error(double t,int  v,int tails)
{
int i1=4;
int i2=2*i1,i;
double area,s1=0,s2=0;
while(1)
{
double a1[i1],a2[i2],h1,h2,x1=0,x2=0,error;
h1=t/(i1-1);
h2=t/(i2-1);
a1[0]=fun(0,v);
a2[0]=fun(0,v);
for(i=1;i<i1;i++)
{
x1=x1+h1;
a1[i]=fun(x1,v);
}
s1=(h1/3)*simpson_add(i1,a1);
for(i=1;i<i2;i++)
{
x2=x2+h2;
a2[i]=fun(x2,v);
}
s2 =(h2/3)*simpson_add(i2,a2);
if(s1>=s2)
error=s1-s2;	
else
error=s2-s1;
if(error<0.01)
break;
else
{
i1=i2;
i2=2*i1;
}
}
if(tails==1)
area=0.5+s2;
else if(tails==2)
area=2*s2;
return area;
}
double t_val(double area, double l, double u)
{
double m = l+(u-l)/2.0, temp;
if(simpson_error(m, 19, 2)>=area)
temp = simpson_error(m, 19, 2)-area;
else
temp = -1*(simpson_error(m, 19, 2)-area);
if(temp<=0.001) 
return m;
if (simpson_error(m, 19, 2)>area)
return t_val(area, l, m);
if(area-simpson_error(m, 19, 2)<area)
return t_val(area, m, u); 
return -1;
}
void calcRange(int n, double a[n], double b[n])
{
int loc=1, predLOC, range_70, range_90;
double sd = calcSd(n,a,b), var, t;
double b0=b00( n, a,b);
double b1=b01( n, a,b);
int new_loc[loc],i=0;
for(i=0; i<loc; i++)
{
printf("Raw LOC : ");
scanf("%d", &new_loc[i]);
}
for(i=0;i<loc;i++)
{
if(new_loc[i]>0)
{
predLOC = (int)((b1*new_loc[i])+b0);
var = calcVar(new_loc[i], n, a);
t = t_val(0.7, 0, 10);
range_70 = (int)(t*sd*var);
printf("\nt_70: %lf\n",t);
t = t_val(0.9, 0, 10);
printf("t_90: %lf\n",t);
range_90 = (int)(t*sd*var);
}
else
{
predLOC=0;
range_90=0;
range_70=0;
}
printf("Raw Loc:%d\npredicted_LOC:%d\n70:-\nLPI:%d\nUPI:%d\n90:-\nLPI:%d\nUPI:%d\n",(int)new_loc[i],(int)predLOC,(int)predLOC-range_70,(int)predLOC+range_70,(int)predLOC-range_90,(int)predLOC+range_90);
}
}
int main()
{	
int i,n = 20;
double b1,b0,x,y,x1,y1,c=0,d=0,xy,xy1,e=0,f=0,g,h,l;
double a[20]= {255,475,362,341,469,255,248,195,223,310,191,449,258,233,347,284,339,135,280,303};
double b[20] = {600,1440,300,780,1440,600,780,420,780,780,360,900,660,720,780,1020,960,300,660,420};	
calcRange(n, a, b);
}