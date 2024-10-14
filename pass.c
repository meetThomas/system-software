#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
void main()
{
FILE *sourcefile,*optabfile,*intermediate,*symtabfile,*prgmlength;
int locctr,start,p_len;
bool symbol_found,opcode_found;
char operand[50],opcode[50],label[50],code[50],symtab_data[20],optab_data[20];

sourcefile=fopen("sourcefile.txt","r"); //source
optabfile=fopen("optabfile.txt","r");//optab
intermediate=fopen("intermediate.txt","w");//intermideate
symtabfile=fopen("symtabfile.txt","w+");//symtab
prgmlength=fopen("prgmlength.txt","w");

fscanf(sourcefile,"%s%s%s",label,opcode,operand);

if(strcmp(opcode,"START")==0)
{
start=atoi(operand);
locctr=start;
fprintf(intermediate,"%s\t%s\t%s\n",label,opcode,operand);

}
else
{
locctr=0;
}
fscanf(sourcefile,"%s%s%s",label,opcode,operand);
while(strcmp(opcode,"END")!=0)
{
if(strcmp(label,"**")!=0)
{
symbol_found=false;
rewind(symtabfile);
while(!feof(symtabfile))
{
fscanf(symtabfile,"%s",symtab_data);
if(strcmp(symtab_data,label)==0)
{
printf("Error:Label found in Symtab");
symbol_found=true;
}}
if(symbol_found==false)
{
fprintf(symtabfile,"%s\t%d\n",label,locctr);
}
}
opcode_found=false;
rewind(optabfile);
while(!feof(optabfile))
{
fscanf(optabfile,"%s",optab_data);
if(strcmp(optab_data,opcode)==0)
{
opcode_found=true;
}
}
 




 fprintf(intermediate,"%d\t",locctr);
 if(opcode_found==true)
 {
 locctr+=3;
 }
 else if(strcmp(opcode,"WORD")==0)
 { locctr +=3;}
 
 else if(strcmp(opcode,"RESW")==0)
 {
 locctr+=3*atoi(operand);
 }
 else if(strcmp(opcode,"RESB")==0)
 {
 locctr+=atoi(operand);
 }
 else if(strcmp(opcode,"BYTE")==0)
 {
 locctr=locctr+strlen(operand)-3;
 }
 else
 {
 printf("Error :invalid operation code");
 }
 fprintf(intermediate,"%s\t%s\t%s\n",label,opcode,operand);
 fscanf(sourcefile,"%s%s%s",label,opcode,operand);
 }
 fprintf(intermediate,"%d\t%s\t\t%s\t%s\n",locctr,label,opcode,operand);
 p_len=locctr-start;
 printf("\nProgram prgmlength : %d\n\n",p_len);
 fprintf(prgmlength ,"%d",p_len);
 fclose(prgmlength);
 fclose(intermediate);
 fclose( symtabfile);
 fclose(optabfile);
 fclose(sourcefile);
 }
