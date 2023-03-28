#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int i=0;
union Person{
char name[50];
char adress[50];
int phone;
};
union Loan{
float amount;
float interestRate;
int period;
};
struct BankAccount{
union Person Customer;
union Loan Loans[3];
};
void addCustomer(struct BankAccount *per,char address[],int phone);
void listCustomers(struct BankAccount *per,int i);
void newLoan(struct BankAccount *per);
float calculateLoan(float amount, int period, float interestRate);
void getReport();
void flush();



void addCustomer(struct BankAccount *per,char address[],int phone){
if(i<50){//More than fifty customers cannot get a loan from the bank
printf("Customer ID = %d\n",i+1);
printf("\ncustomer name = ");
flush();
scanf("%[^\n]%*c",per->Customer.name);
printf("\ncustomer address = ");

flush();
scanf("%[^\n]%*c",address);
printf("\ncustomer phone =");
scanf("%d",&phone);
i++;
//add customer information to TXT
FILE *TXT;
TXT=fopen("customerlist.txt","a");
if(TXT != NULL){
fprintf(TXT,"customer name = %s\n",per->Customer.name);
fprintf(TXT,"customer address = %s\n",address);
fprintf(TXT,"customer phone = %d\n",phone);
fclose(TXT);}

}
else
printf("no more credits can be given to customers");
}






void listCustomers(struct BankAccount *per,int i){
int j;//list of customers who got a loan from the bank
for(j=0;j<i;j++){
printf("%d. customer name %s\n",j+1,per[j].Customer.name);
}}







void newLoan(struct BankAccount *per){
FILE *TXT;
float amount;
int period;
float interestRate;
int ID;
float result;
int flag=0;

printf("enter customer ID\n");
scanf("%d",&ID);
if(ID<=i){
TXT=fopen("interestRatelist.txt","r");//reading interest rates from file
if(TXT != NULL){
while(!feof(TXT)){
int txtId;
char txtName[50],txtAmount[50],txtPeriod[50],txtInterest[50],txtResult[50];
fscanf(TXT,"%d",&txtId);
fscanf(TXT,"\ncustomer %[^\n]%*c ",txtName);
fscanf(TXT,"\namount%[^\n]%*c  ",txtAmount);
fscanf(TXT,"\nperiod%[^\n]%*c ",txtPeriod);
fscanf(TXT,"\ninterestRate%[^\n]%*c ",txtInterest);
fscanf(TXT,"\ntotal debt payable %[^\n]%*c ",txtResult);
if(txtId==ID){//to see how many times the person got a loan
flag=flag+1;
}

}
fclose(TXT);
}
if(flag==3){
printf("1 person can only take 3 credits, you can't get more credits\n");

}else{

printf("amount of loan the customer wants\n");
scanf("%f",&amount);
printf("enter period\n");
scanf("%d",&period);
printf("enter interestRate\n");
scanf("%f",&interestRate);
result=calculateLoan(amount,period,interestRate);
printf("total loan debt that the customer will repay=%.4f\n",result);

TXT=fopen("interestRatelist.txt","a");//add interestrate list customer to file
if(TXT != NULL){
fprintf(TXT,"\n %d ",ID);
fprintf(TXT,"\ncustomer %s ",per[ID-1].Customer.name);
fprintf(TXT,"\namount %f ",amount);
fprintf(TXT,"\nperiod %d",period);
fprintf(TXT,"\ninterestRate %f ",interestRate);
fprintf(TXT,"\ntotal debt payable %f",result);
fclose(TXT);}
}
}else printf("there is not customer");
}







float calculateLoan(float amount, int period, float interestRate){
if(period==0){
return amount;
}
else 
return (1+interestRate)*calculateLoan(amount,period-1,interestRate);}








void getReport(){
int choice;
do{
printf("\nselect 1 to see customer information\n");
printf("\nselect 2 to see loan\n");
scanf("%d",&choice);
char address[50];
char name[50];
char phone[50];
int ID;
int flag = 0;
int whichLoan;
float result;
int period;
int txtId;
char txtName[50],txtAmount[50],txtPeriod[50],txtInterest[50],txtResult[50];
float totalresult;
FILE *TXT;
switch(choice){
case 1://reporting customer information
printf("\nenter customer ID\n");
scanf("%d",&ID);
if(ID<=i){
TXT=fopen("customerlist.txt","r");
if(TXT != NULL){
for(i=1;i<=ID;i++){
fscanf(TXT,"%[^\n]%*c ",name);
fscanf(TXT,"%[^\n]%*c",address);
fscanf(TXT,"%[^\n]%*c",phone);
}
fclose(TXT);}
printf("\n%s\n",name);
printf("%s\n",address);
printf("%s\n",phone);
printf("Loans = [");
TXT=fopen("interestRatelist.txt","r");// reading date in file
totalresult=0;
int a=0;
int x=0;
if(TXT != NULL){
while(!feof(TXT)){
fscanf(TXT,"%d",&txtId);
fscanf(TXT,"\ncustomer %[^\n]%*c ",txtName);
fscanf(TXT,"\namount%[^\n]%*c  ",txtAmount);
fscanf(TXT,"\n%s %d",txtPeriod,&period);
fscanf(TXT,"\ninterestRate%[^\n]%*c ",txtInterest);
fscanf(TXT,"\ntotal debt payable %f",&result);
if(a<x){printf(" + "); a++;}
if(txtId==ID){
x=x+1;
printf("%f ",result);
totalresult=totalresult+result;}
}
printf("]=> %f ",totalresult);
fclose(TXT);}

}
else("there is no customer with this ID\n");

break;

case 2://reporting loan
printf("enter customer ID\n");
scanf("%d",&ID);//which customer's information
printf("\nwhichLoan\n");
scanf("%d",&whichLoan);//information of which loan of the customer
TXT=fopen("interestRatelist.txt","r");// reading date in file
if(TXT != NULL){
while(!feof(TXT) && flag != whichLoan){

fscanf(TXT,"%d",&txtId);
fscanf(TXT,"\ncustomer %[^\n]%*c ",txtName);
fscanf(TXT,"\namount%[^\n]%*c  ",txtAmount);
fscanf(TXT,"\n%s %d",txtPeriod,&period);
fscanf(TXT,"\ninterestRate%[^\n]%*c ",txtInterest);
fscanf(TXT,"\ntotal debt payable %f",&result);

if(txtId==ID){
flag=flag+1;//to determine the number of loan
}
}
fclose(TXT);
if(flag == whichLoan){
printf("%f",result);
for(int i = 0;i < period;i++) printf("\n%d. month %f\n",i + 1,result/period);//amount of money to be paid each month
}
else printf("\nThis customer does not have a %d. loan",whichLoan);
}

break;
}
}while(choice==1 || choice==2);
}











int main(){
struct BankAccount *per;
per=(struct BankAccount *)calloc(50,sizeof(struct BankAccount));//up to 50 customers
char address[50];
int phone;
char txtname[50],txtaddress[50],txtphone[50];
int choice;
FILE *TXT;
TXT=fopen("customerlist.txt","r");
if(TXT != NULL){
while(!feof(TXT)){
fscanf(TXT,"%[^\n]%*c ",txtname);
fscanf(TXT,"%[^\n]%*c",txtaddress);
fscanf(TXT,"%[^\n]%*c",txtphone);
i++;}fclose(TXT);}




do{
printf("\n=====================================\n");
printf("WELCOME TO THE BANK MANAGEMENT SYSTEM\n");
printf("=====================================\n");
printf("        1.List All Customers\n");
printf("        2.Add New Customer\n");
printf("        3.New Loan Application\n");
printf("        4.Report Menu\n");
printf("        5.Exit System\n");
scanf("%d",&choice);

switch(choice)
{
case 1:
listCustomers(per,i);//listing of customers
break;
case 2:
addCustomer(&per[i],address,phone);//add of customers
break;
case 3:
newLoan(per);//loan
break;
case 4:
getReport();//raporting
break;
case 5://exit
break;
}}while(choice==1 || choice==2 || choice==3 || choice==4);
return 0;
}







void flush(){
    char c;
    while(c != EOF && c != '\n'){
        c = getchar();
    }
}




