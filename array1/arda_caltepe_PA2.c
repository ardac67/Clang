#include <stdio.h>
#define MAXNUMBER 100

int main() {

    int i,  index, isUnique,j,temp,tempforUnique;

    // List of distinct numbers
    int UniqueNumbers[MAXNUMBER];
    int reader;

    // Count of distinct numbers
    int  count[MAXNUMBER];

    FILE *myFile; 
	myFile= fopen("input.txt","r");

    // Initialize number count to 0
    for (i=0; i<MAXNUMBER; i++)
    count[i] = 0;
    
    
    index = 0;
    /*Reading and counting repetative numbers*/
    while (fscanf(myFile, "%d", &reader) != EOF)
    {
        isUnique = 1;
        /*deciding the number is in array or not for uniqueness*/
        for (i=0; i<index && isUnique; i++)
        {
            if (UniqueNumbers[i]==reader)
                isUnique = 0;
        }
        /* if it is unique then increment that index by one*/
        if (isUnique) 
        {
            UniqueNumbers[index]= reader;
            count[index]++;

            index++;
        }
        /*if it is not unique then increment 'i-1' index*/
        else
        {
            count[i - 1]++;
        }
    }
      
    
        
    /*For sorting the number of repetations*/    
    for(i=0; i<index; i++)
    {
    
        for(j=i+1; j<index; j++)
        {
            /* sorting count array then swapping the UniqeNumbers array with their indexes*/    
            if(count[i] > count[j])
            {   
                
                temp     = count[i];
                count[i] = count[j];
                count[j] = temp;
                tempforUnique=UniqueNumbers[i];
                UniqueNumbers[i]=UniqueNumbers[j];
                UniqueNumbers[j]=tempforUnique;

            }
           
        }
         
            
          
    }
    myFile = fopen ("output.txt", "w+");
    /*Printing sorted numbers*/
    for(i=0; i<index; i++)
    {
        
        fprintf(myFile, "%d%s%d\n",UniqueNumbers[i] ,":", count[i]);
    }
        
    

	fclose(myFile);	
}

