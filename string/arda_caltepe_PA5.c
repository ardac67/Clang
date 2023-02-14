#include <stdio.h>

/*
* char*Language is the name of the file
*int LanguageArray for storing bigram packages
*/
void ReadFileAndStoreBigrams(char *Language,int LanguageArray[][27]);/*reading txt files without store all chars and Store bigram packages/*/

/*
* int TargetLanguage is the language will be compared and it is constant file
* int SourceLanguage is the language that will be as source language
*/
void Dissimilarity(int TargetLanguage[][27],int SourceLanguage[][27]);/*Finding dissimilarity between two text*/

/*Do work is a function that handles all work and containes all function*/
/*Just takes language file name*/
void DoWork(char * languageFile);

int main()
{   
    char *languages [5]={"language_1.txt","language_2.txt","language_3.txt","language_4.txt","language_5.txt"};/*storing language file name*/

    for(int i=0;i<5;i++) 
    {
        DoWork(languages[i]);/*looping file name into do work function*/
    }    


	return 0; 
}

void DoWork(char * languageFile)
{
    int Language[27][27]={0};/*storage for source language bigrams*/

    int LanguageUnk[27][27]={0};/*storage for unknown language bigrams*/

    ReadFileAndStoreBigrams(languageFile,Language);
    ReadFileAndStoreBigrams("language_x.txt",LanguageUnk);
    Dissimilarity(LanguageUnk,Language);
}

void ReadFileAndStoreBigrams(char *Language,int LanguageArray[][27])
{

    FILE *myFile;
    myFile=fopen(Language,"r");

    int FirstChar=0;/*creating a int variable that holds respective char asci numbers for first char*/
    int SecondChar=0;/*creating a int variable that holds respective char asci numbers for second char*/
    int flag=1;/*just control for getting out of the loop*/

    FirstChar=fgetc(myFile);/* getting first char*/

    if (FirstChar==32) FirstChar=123;/*if first char equals empty then assing 123 because 123-97 is 26 and it is last index (i am storing empty char  at index 26)*/

    while(flag)
    {   
        SecondChar=fgetc(myFile);/*getting second char*/
		if( SecondChar==EOF ){/*if char is EOF than set flag zero and get out of the loop*/
			
            if( FirstChar!=123 ) LanguageArray[FirstChar-97][26]++; /*if first char not empty char increment that index */
            
			flag=0;/*set flag zero because it is end of file*/
		}
        if(flag==1)
        {
            if (SecondChar==32 || SecondChar==10) SecondChar=123;/*if chars are empty or new line than assing as the empty char*/

		    if (FirstChar==123 && SecondChar==123) continue; /*if two of them empty skip that step*/
			
		    LanguageArray[FirstChar-97][SecondChar-97]++;  /*increment that specific index according to asci values ex: 97-97=0 index which is a*/

		    FirstChar=SecondChar;	/*assing second to first to move to another char*/
        }
		
    }
    fclose(myFile);  
}
60 90 70 150 60 /**/

void Dissimilarity(int TargetLanguage[][27],int SourceLanguage[][27])
{
    double Total1=0;/*Storage for TargetLanguage bigrams*/
    double Total2=0;/*storage for sorucelangueage bigrams*/
    double FreqSummation=0;/*summation of their frequencies*/
    double diss=0;/*total dissmilarity storage*/
    
    for(int i=0;i<27;i++)/*looping through in two language array*/
    {
        for(int j=0;j<27;j++)
        {
            Total1+=TargetLanguage[i][j];/*summation of bigrams of target language*/
            Total2+=SourceLanguage[i][j];/*summation of bigrams of source language*/
        }
    }
    for(int i=0;i<27;i++)/*looping through for calculating dissimilarity and summation of frequencies*/
    {
        for(int j=0;j<27;j++)
        {
            FreqSummation=(TargetLanguage[i][j]/Total1)-(SourceLanguage[i][j]/Total2);/*divisin of specific index and total bigrams and substracting from each other*/
            if(FreqSummation<0) diss=diss+(-1*FreqSummation);/*adding to frequency if it is bigger than 1 else multiplying with -1 because we need absolute value*/
            else diss=diss+FreqSummation;

        }
        
    }
   
   printf("%lf\n",diss);/*printing dissmilarities*/

}
