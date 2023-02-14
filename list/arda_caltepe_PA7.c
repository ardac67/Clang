#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 20

typedef struct gate
{
    int type; 
    char name[SIZE];
    struct gate** inputs;/*adress of input gatees*/
    int output;
    int former_out;
    struct gate **values;/*adress of adrees of releated connections*/
    int  icounter;/*count of connections of gate*/
} gate; 



typedef enum{
    INPUT, 
    OUTPUT,
    AND,
    OR,
    NOT,
    FLIPFLOP
} types;


/*determining enum values*/
int returnType(char* str);

/*returning adress of gates and filling with necessary infos*/
gate* GetAdress(FILE* fptr, int counter);

/*reading connections from input.txt and connecting neccessary gates*/
void ConnectNodes(FILE* fptr,gate myGate,int counter);
/*Filling output part of input gates*/
void GetInput(char* str,gate myGate,int inputGateCounter);

/*doing calculations recursively*/
int DoWork(gate *g);

int main(){

    gate myGate;
    int counter = 0;
    int counterforDynamic=1;
    int counterForConnection=1;
    char strTest[SIZE];
    FILE  * fptrFC;
    fptrFC=fopen("circuit.txt","r");

    while(fscanf(fptrFC,"%s",strTest)!=EOF)/*finding connection and gate counts to allocate memory*/
    {
        if(strTest[0]=='G') counterforDynamic++;
        else if(strTest[0]=='C') counterForConnection++;
    }
    

    myGate.inputs = (gate**) calloc(counterforDynamic, sizeof(gate**)); /*allocating memory for gate part*/

    FILE* fptr;
    fptr = fopen("circuit.txt", "r");
    char str[SIZE];
    int inputGateCounter=0;

    while(fscanf(fptr, "%s", str) != EOF){
        if(strcmp(str, "GATE") == 0){
            myGate.inputs[counter] = GetAdress(fptr, counter);/*storing gate adresses*/
            counter++;
        }
    }
    fclose(fptr);
    
    for(int i = counter-1; i>= 0; i--){
        myGate.inputs[i]->icounter=0;
        if(myGate.inputs[i]->type==5) myGate.inputs[i]->former_out=0;/*setting former_out for 0*/
    }  

    for(int i = counter-1; i>= 0; i--){
        myGate.inputs[i]->values=(gate**) calloc(counterForConnection, sizeof(gate**));/*allocating memory for adresses of connections*/
    }   

    for(int i = counter-1; i>= 0; i--){
        if(myGate.inputs[i]->type==0) inputGateCounter++;
    }

    FILE* fptr2;
    fptr2 = fopen("circuit.txt", "r");

    int decider=0;
    while(fscanf(fptr2, "%s", str) != EOF){
        if(strcmp(str, "CONNECTION") == 0){
            ConnectNodes(fptr,myGate,counter);/*connectting nodes according to adresses*/
        }
    } 
    fclose(fptr2);   


    int lastgate=counter-1;
    FILE* fptr3;

    fptr3=fopen("input.txt","r");

    int result;

    char str1[20];

    while(fscanf(fptr3,"%s",str1)!=EOF)
    {   
        GetInput(str1,myGate,inputGateCounter);
        for(int i=0;i<counter;i++) 
        {
            if(myGate.inputs[i]->type==1) 
            {
                result=DoWork(myGate.inputs[i]);/*reading input file and printing result*/
                printf("%d\n",result); 
            }
        }
        
    }  
    fclose(fptr3); 
    free(myGate.inputs);/*free memory*/
    
    for(int i=1;i<counter-1;i++) free(myGate.inputs[i]->values);/*free memory*/
    
    
    return 0;
}
/*returning gate type*/
int returnType(char* str){
    if(strcmp(str, "INPUT") == 0) return INPUT;
    else if(strcmp(str, "OUTPUT") == 0) return OUTPUT;
    else if(strcmp(str, "AND") == 0) return AND;
    else if(strcmp(str, "OR") == 0) return OR;
    else if(strcmp(str, "NOT") == 0) return NOT;
    else return FLIPFLOP;
}

/*returning adress of gates and storing these adressses in inputs pointer array */
gate * GetAdress(FILE* fptr, int counter){

    char str[SIZE];
    gate* temp = (gate*) malloc(sizeof(gate));

    fscanf(fptr, "%s", str);
    temp->type = returnType(str);
    fscanf(fptr, "%s", str);
    strcpy(temp->name, str);

    return temp;
}

/*reading connections and connecting necessary nodes with adresses!*/
void ConnectNodes(FILE* fptr,gate myGate,int counter){

    char str[SIZE];
    char str1[SIZE];
    
    fscanf(fptr, "%s", str);
    fscanf(fptr, "%s", str1);

     for(int i = 0; i < counter; i++){
        
        if(strcmp(myGate.inputs[i]->name,str1)==0)
        {   
            for(int j = 0; j < counter; j++){
                
                if(strcmp(myGate.inputs[j]->name,str)==0)
                {   

                    if(myGate.inputs[i]->type==1)
                    {
                       myGate.inputs[i]->values[myGate.inputs[i]->icounter]=myGate.inputs[j];
                       myGate.inputs[i]->icounter++;
                    }
                    else if(myGate.inputs[i]->type==2)
                    {    
                       myGate.inputs[i]->values[myGate.inputs[i]->icounter]=myGate.inputs[j];
                       myGate.inputs[i]->icounter++;

                    }
                    else if(myGate.inputs[i]->type==3)
                    {
                       myGate.inputs[i]->values[myGate.inputs[i]->icounter]=myGate.inputs[j];
                       myGate.inputs[i]->icounter++;   
                    }
                    else if(myGate.inputs[i]->type==4)
                    {  
                       myGate.inputs[i]->values[myGate.inputs[i]->icounter]=myGate.inputs[j];
                       myGate.inputs[i]->icounter++;
                    }
                    else if(myGate.inputs[i]->type==5)
                    {
                       myGate.inputs[i]->values[myGate.inputs[i]->icounter]=myGate.inputs[j];
                       myGate.inputs[i]->icounter++;  
                    }

                }
            }
        } 
    }  
}
/*filing input gates with input txt*/
void GetInput(char* str,gate myGate,int inputGateCounter)
{   
    int input;
    char *Extracted=(char*)malloc(sizeof(char)*1);

    for(int i=0;i<inputGateCounter;i++)
    {
        Extracted[0]=str[i];
        sscanf(Extracted, "%d", &input);
        myGate.inputs[i]->output=input;
    }
    free(Extracted);
} 
 

/*recursively doing calculations*/
int DoWork(gate *g)
{
   
    if(g->type==0) /*if type zero which means input return its value*/
    {   
        return g->output; 
    }
    else if(g->type==1)/*output gate which calls the releated node inside of it*/
    {   
        DoWork(g->values[0]);
    }
    else if(g->type==2)/*and gate calls related nodes and doing calculations and returns the obtained value*/
    {
        int x;
        for(int i=0;i<g->icounter;i++)
        {
            if(i==0) x=DoWork(g->values[i]);
            else x=(x && DoWork(g->values[i]));
        }

        return x;
    }
    else if(g->type==3)/*or gate calls related nodes and doing calculations and returns the obtained value*/
    {
        int x;
        for(int i=0;i<g->icounter;i++)
        {
            if(i==0) x=DoWork(g->values[i]);
            else x=(x || DoWork(g->values[i]));
        }

        return x;
    }
    else if(g->type==4)/*not gate calls related nodes and doing calculations and returns the obtained value*/
    {
        int x;
        x=(DoWork(g->values[0]));

        return !x;
    }
    else if(g->type==5)/*FLIPFLOP gate calls related nodes and doing calculations and returns the obtained value*/
    {
        int x;
        x=DoWork(g->values[0]);

        int fo=g->former_out;
        if(x==0)
        {
            if(fo==0) 
            {
                g->former_out=0;
                return 0;
            }
            else if(fo==1)
            {
                g->former_out=1;
                return 1;
            }
        }
        else if(x==1)
        {
            if(fo==0)
            {
                g->former_out=1;
                return 1;
            }
            else if(fo==1)
            {
                g->former_out=0;
                return 0;
            }
        }

        return fo;
    }
}  
 