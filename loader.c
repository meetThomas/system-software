#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
FILE *Obj;
Obj =fopen("objectcode.txt","r");
char line[1000] , arr[1000];
fscanf(Obj,"%s",line);
int i,j,length;
printf("Program name : ");

for(i=2;i<=4;i++)
{
printf("%c",line[i]);
}
printf("\n");
do {
fscanf(Obj,"%s",line);
if (line[0]=='T')
{
for( i=0;i<=6;i++)
{
arr[i]=line[i+2];
}
arr[i]='\0';
length=atoi(arr);
i=12;
while(line[i]!='\0')
{
if(line[i]!='^')
{
printf("%d\t%c%c\n",length,line[i],line[i+1]);
length++;
i=i+=2;
}
else{
i++;
}}}
else if(line[0]=='E'){
break;
}}
while(!feof(Obj));
fclose(Obj);
}

