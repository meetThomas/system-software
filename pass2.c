 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
FILE *intermediate,*optabfile,*symtabfile,*output,*prgmlength,*objectcode;
char opcode[20],operand[20],label[20],mnemonic[20],code[20],value[20],textRecord[70];
int locctr,start,prgmLength,length=0,textstartAddr;
optabfile=fopen("optabfile.txt","r");
intermediate=fopen("intermediate.txt","r");
symtabfile=fopen("symtabfile.txt","r");
prgmlength=fopen("prgmlength.txt","r");
objectcode=fopen("objectcode.txt","w");
output=fopen("output.txt","w");
if(!optabfile){
 printf("Error opening file optabfile!!\n");
   return;}
if(!intermediate){
 printf("Error opening file intermediate!!\n");
   return;}
if(!symtabfile){
 printf("Error opening file symtabfile!!\n");
   return;}
if(!output){
 printf("Error opening file output!!\n");
   return;}
if(!prgmlength){
   printf("Error opening file program!!\n");
   return;}
fscanf(intermediate,"%s%s%s",label,opcode,operand);
printf("First input line read: %s%s%s\n",label,opcode,operand);
fprintf(output,"    %-7s%-7s%-7s\n",label,opcode,operand);
if(strcmp(opcode,"START")==0){
   fscanf(prgmlength,"%d",&prgmLength);
   start=atoi(operand);
   fprintf(objectcode,"H^%s^%06d^%06d\n",label,start,prgmLength);}
 fscanf(intermediate,"%d%s%s%s",&locctr,label,opcode,operand);
 textstartAddr=locctr;
 strcpy(textRecord,"");
 while(strcmp(opcode,"END")!=0){
   char objectCode[10]="";
   printf("Processing Line:%d%s%s%s",locctr,label,opcode,operand);
   fprintf(output,"%d%-7s%-7s%-7s ",locctr,label,opcode,operand);
   if(strcmp(opcode,"BYTE")==0){
     if(operand[0]=='C'&& operand[1]=='\''){
        if(strcmp(operand,"C'EOF'")==0){
            strcpy(objectCode,"454F46");
            }
        else{
            for(int i=2;i<strlen(operand)-1;i++){
                sprintf(objectCode+strlen(objectCode),"%02X",operand[i]);
                }}}

}
else if(strcmp(opcode,"WORD")==0){
  sprintf(objectCode,"%06d",atoi(operand));
  }else if(strcmp(opcode,"RESB")==0){
  }
  else if(strcmp(opcode,"RESW")==0){
  }else{
  rewind(optabfile);
while(fscanf(optabfile,"%s%s",mnemonic,code)!=EOF){
  if(strcmp(opcode,mnemonic)==0){
     strcpy(objectCode,code);
     break;}}
    rewind(symtabfile);
while(fscanf(symtabfile,"%s%s",label,value)!=EOF){
  if(strcmp(operand,label)==0){
     sprintf(objectCode+strlen(objectCode),"%04d",atoi(value));
     break;}}}
    printf("Object code:%s\n",objectCode);
    fprintf(output,"%s\n",objectCode);
  if(length + strlen(objectCode)>60){
    fprintf(objectcode,"T^%06d^%02X^%s\n",textstartAddr,length/2,textRecord);
   strcpy(textRecord,"");
   textstartAddr=locctr;
   length=0;
   }
 if(strlen(objectCode)>0){
    strcat(textRecord,objectCode);
    strcat(textRecord,"^");
    length+=strlen(objectCode);
    }
 fscanf(intermediate,"%d%s%s%s",&locctr,label,opcode,operand);}
 if(length>0){
    textRecord[strlen(textRecord)-1]='\0';
    fprintf(objectcode,"T^%06d^%02X^%s\n",textstartAddr,length/2,textRecord);}
    fprintf(output,"    %-7s%-7s%-7s\n",label,opcode,operand);
  fprintf(objectcode,"E^%06d\n",start);
  fclose(intermediate);
  fclose(symtabfile);
  fclose(optabfile);
  fclose(output);
  fclose(prgmlength);
  printf("FINISHED EXECUTION!!");
  }                   
