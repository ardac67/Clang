#include<stdio.h>
#include <stdlib.h>
#include<string.h>

#define SIZE 600
#define CARB_CAL_1G   4
#define PROTEIN_CAL_1G   4
#define FAT_CAL_1G   9
#define WATER_CAL_1G   0

typedef struct /*Defining a struct to hold results coming from strings*/
{  
    double TotalGram;
    double TotalCarbonGrams;
    double TotalProteinGrams;
    double TotalFatGrams;

} _Calculations;
/*_Ingredients comes from user input , calc is the struct instance*/
void TrimAndCalculate(char*_Ingredients,_Calculations *calc);/*Parsing strings and running recursive functions inside to make calculations */

/*flag decides the question type,NewString is the parsed result of the string that comes from user,calc is the struct instance*/
void Recursive(int flag,char * NewString,_Calculations *calc);/*Decides question type and if question includes grams then extract grams from that string*/
/*Just takes str variable to parse their grams*/
double ExtractGrams(char  *str);/*extracting grams from str*/

/*Takes calc instances and mealname for printing*/
void FinalCalculation(_Calculations *calc,char *MealName);/*works for just calculating final result*/




int main()
{   
    /*Allocating memory for _Calculations*/
    _Calculations *calc=(_Calculations*)malloc(sizeof(_Calculations*));

    /*Defining variable for meal name*/
    char *Meal;

    printf("What is the meal?\n");

    scanf(" %[^\n]s",Meal);

    printf("What is %s?\n",Meal);

    char* Ingredients=(char*)malloc(sizeof(char)*SIZE);/*allocating memory for response*/

    scanf(" %[^\n]s",Ingredients);/*taking response until newline*/

    TrimAndCalculate(Ingredients,calc);/*parsing Ingredients*/

    FinalCalculation(calc,Meal);/*calculating final result*/

    free(Ingredients);/*deallocating memory*/

    free(calc);/*deallocating memory*/
    

  return 0;  
}

void TrimAndCalculate(char*_Ingredients,_Calculations *calc)
{   
    int i,counter,flag;
    counter=0;
    flag=0;/*determines the question type*/

    char *NewString=(char*)malloc(sizeof(char)*30);/*NewString holds the parsed result then run another function*/
	for(i=0;_Ingredients[i]!='\0';i++){
        if(_Ingredients[i]!=' ' && _Ingredients[i]!=',')/*If char is not empty and comma pass the values because it is the main question includes another question*/
        {
            NewString[counter]=_Ingredients[i];
            counter++;
		}
        if(_Ingredients[i]==' ')/*if it is empty string then move to another index*/
        {  
            continue;
        }
        if(_Ingredients[i]==',' || _Ingredients[i+1]=='\0')
        {
            int j=0;
            while(NewString[j]!='\0')
            {
                if(NewString[j]=='(' || NewString[j]==')')/*if we faced these chars we can understand it includes gram values*/
                {
                    flag=1; /*if it includes gram values set it 1*/
                    break;/*then break from inner loop and continue*/
                }
                else flag=0;/*if it is not then this is main question*/
                j++;
            }
            if(flag==0)
            {
                Recursive(flag,NewString,calc);/*if flag is 0 then pass that values into recursive func*/
            }
            else if(flag==1)
            {
                Recursive(flag,NewString,calc);/*if flag is 1 then pass that values into recursive func*/
            }
            memset(NewString, '\0',30);
            counter=0;
            continue;/*then continue with other strings*/
        }
	}
    free(NewString);/*dealloacte memory*/
}

/*if flag is 1 then calculates the gram  of given input and carbohydrate and protein and fat grams or if flag is 0 asks the main question*/
void Recursive(int flag,char * NewString,_Calculations *calc)
{       
    double Gram=0;

    if(flag==0)
    {   
        char* InnerIngredients=(char*)malloc(sizeof(char)*SIZE);

        printf("What is %s?\n",NewString);

        scanf(" %[^\n]s",InnerIngredients);/*asks the ingredients*/

        TrimAndCalculate(InnerIngredients,calc);/*calls function again*/

        free(InnerIngredients); 
    }
    else if(flag==1)
    {   
        char* WithoutGram=(char*)malloc(sizeof(char)*30);
        int f=0;
        while(NewString[f]!='(')/*Removing (45G) and display in new string*/
        {   
            WithoutGram[f]=NewString[f];
            f++;
        } 
        
        printf("List of the amount macro nutrients in %s\n",WithoutGram);
        free(WithoutGram);

        char* Calculator=(char*)malloc(sizeof(char)*SIZE);

        scanf(" %[^\n]s",Calculator);/*takes the list of macro nutritients*/

        Gram=ExtractGrams(NewString);/*extractes the gram from given input and assinging it to Gram variable*/

        calc->TotalGram+=Gram;/*add that given gram in calc struct*/

        int Counter=0;

        char *Extracted=(char*)malloc(sizeof(char)*30);/*hold the percantages*/

        /* this part extracts the percantages input*/
        double C=0;/*holds the percantage*/
        int k;
        int Decide=1;/*decides whether it is fat or protein or carbohydrate*/
        for(int i=0;Calculator[i]!='\0';i++)
        {   

            if(Calculator[i]=='%')/*if encount percantage char then take that value inside it*/
             {    
                k=i+1;
               
                while(Calculator[k]!=',' && Calculator[k]!='\0')/*until encount the comma or null char*/
                {   
                    if(Calculator[k]!=' ')/*if faced with empty string then continue*/
                    {
                        Extracted[Counter]=Calculator[k];
                        Counter++;
                        k++;
                    }
                    else k++;
                }
                Counter=0;
                sscanf(Extracted, "%lf", &C);/*take percantage values from extracted string and assing it to double C*/
                memset(Extracted, '\0',30);
                if(Decide==1)/*if decide is one this means it is carbohydrate*/
                {   
                    calc->TotalCarbonGrams+=Gram*(C/100);/*Summ variables that found*/
                }
                if(Decide==2)/*if decide is two this means it is protein*/
                {
                    calc->TotalProteinGrams+=Gram*(C/100);/*Summ variables that found*/
                }
                if(Decide==3)/*if decide is three this means it is fat*/
                {
                    calc->TotalFatGrams+=Gram*(C/100);   /*Summ variables that found*/                 
                } 
                C=0;/*set value to zero for further summation*/
                i=k;/*swap values because we did that part and need to skip that part*/
                Decide++;
             }
	    } 
       
        free(Calculator);

        free(Extracted);
    }

}

/*returns double of grams and taking str input which is parsed in trimandcalculate function*/
double ExtractGrams(char  *str)
{
   char *Extracted=(char*)malloc(sizeof(char)*30);
   int Counter=0;
   int i;
   double Gram=0;
   for(i=0;str[i]!='\0';i++)
   {
       if(str[i]=='(')/*if we faced with this char this means after this we will get the gram*/
       {    
            while(str[i+1]!='g' && str[i+1]!=')')/*until faced with these chars get the value from string assing it to extracted*/
            {
                Extracted[Counter]=str[i+1];
                Counter++;
                i++;
            }
            
       }
	}
    sscanf(Extracted, "%lf", &Gram);/*assing grams from Extracted to gram */
    free(Extracted);
    return Gram;
}

void FinalCalculation(_Calculations *calc,char *MealName)
{   
    double CP,PP,FP,Total;/*defining variable for percantages*/
    Total=(calc->TotalCarbonGrams*CARB_CAL_1G)+(calc->TotalProteinGrams*PROTEIN_CAL_1G)+(calc->TotalFatGrams*FAT_CAL_1G);/*calculating total calories*/
    CP=((calc->TotalCarbonGrams*CARB_CAL_1G)/Total)*100;/*calculating carbohydrate percantages*/
    PP=((calc->TotalProteinGrams*PROTEIN_CAL_1G)/Total)*100;/*calculating protein percantages*/
    FP=((calc->TotalFatGrams*FAT_CAL_1G)/Total)*100;/*calculating fat percantage*/

    /*printing final result*/
    printf("Total calories is %.2lf in %.2lfg %s. %%%.2lf calories from carbs, %%%.2lf from proteins, %%%.2lf from fats\n",Total,calc->TotalGram,MealName,CP,PP,FP); 

}


