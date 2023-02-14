#include <stdio.h>

#define p1 0.5
#define p2 20
#define size 1000


/*Reading input.txt file to NumberArray*/
int ReadFile(int index,double reader,double *NumberArray);


/*
This function is calculating averages of each chunk 
NumberArray->Storage for the number from input.txt
a-> is the average before adding the number
b-> is the average after adding the number
ChunkCount-> holds the count of number in each Chunks
AverageChunk-> holds the averages of each chunk
AverageIndex-> holds the size of AverageChunk and ChunkCount
n-> is used for holding the number from file
*/
int CalculateAverages(int index,double *NumberArray,double a,double b,int *ChunkCount,double *AverageChunk,int AverageIndex,double n);


/*
This function initialize 2d array (ChunkNumberStorage) with the numbers of each chunk includes.
AverageIndex->holds the size of AverageChunk and ChunkCount
ChunkNumberStorage->holds the each chunk numbers
NumberArray->Storage for the number from input.txt
ChunkCount-> holds the count of number in each Chunks
*/
void Initialize2DArray(int AverageIndex,double ChunkNumberStorage[][size],double *NumberArray,int *ChunkCount);

/*
This function prints every number according to chunks
AverageIndex->holds the size of AverageChunk and ChunkCount
ChunkCount-> holds the count of number in each Chunks
ChunkNumberStorage->holds the each chunk numbers
*/

/*Prints 2D array*/
void Print2DArray(int AverageIndex,int *ChunkCount,double ChunkNumberStorage[][size]);

/*Sorts 2D Array*/
void SortArray(int AverageIndex,int *ChunkCount,double ChunkNumberStorage[][size],double *AverageChunk);





int main()
{   
    
    double NumberArray[size];/*holds the numbers from input.txt file*/
    int index=0;/*Holds the number counts in file*/
    int ChunkCount[size];/*holds the count of number in each Chunks*/
    double AverageChunk[size];/*holds the averages of each chunk*/
    double reader,n,a,b;/*reader for the input.txt file && a for average before add the new number && b for average after add the new number*/
    double ChunkNumberStorage[100][size]={0,0};/*holds the each chunk numbers*/
    int AverageIndex;/*holds the size of AverageChunk and ChunkCount*/


    index=ReadFile(index,reader,NumberArray);/*storing the index for the calculating average and stores the numbers from file to an NumberArray*/

    AverageIndex=CalculateAverages(index,NumberArray,a,b,ChunkCount,AverageChunk,AverageIndex,n);/*Calculating averages and storing AverageIndex from return value from the function for the further usage*/

    Initialize2DArray(AverageIndex,ChunkNumberStorage,NumberArray,ChunkCount);/*Just initialize 2d array from chunk values*/

    SortArray(AverageIndex,ChunkCount,ChunkNumberStorage,AverageChunk);/*sorting ChunkNumber storage in ascending order according to ChunkAverage values*/
    
    Print2DArray(AverageIndex,ChunkCount,ChunkNumberStorage);/*printing into output.txt file*/
}


int ReadFile(int index,double reader,double *NumberArray)
{
    FILE * myFile;
    myFile=fopen("input.txt","r");
    while(fscanf(myFile,"%lf",&reader)!=EOF)
    {
        NumberArray[index]=reader;
        index++;

    }
    return index;
}

int CalculateAverages(int index,double *NumberArray,double a,double b,int *ChunkCount,double *AverageChunk,int AverageIndex,double n)
{
    int i=0;/*indexing*/
    int counter=0;/*for the counting the number of each chunk*/
    while(index>i)
    {   
        /*hold the first input as first Chunk Number*/
        if(i==0)
        {
            n=NumberArray[0];
           // printf("%lf",NumberArray[0]);
            a=n;
            b=n;
            counter++;
            ChunkCount[0]=counter;
            AverageChunk[0]=a;
            i++;
            AverageIndex=0;
        }
        else /*if it is not first number moves with this else part*/
        {
            counter++;
            n=NumberArray[i];/*new number assigging to n*/
            a=AverageChunk[AverageIndex];/*old average assigning to a*/
            b=((AverageChunk[AverageIndex]*ChunkCount[AverageIndex])+n)/(ChunkCount[AverageIndex]+1);/*new average calculated*/
            if(!(b > a*(1+p1) || b < a*(1-p1) || a > n*p2 || a < n/p2))/*checking the condition*/
            {
                AverageChunk[AverageIndex]=b;/*Assingn the new average to averagechunk*/
                ChunkCount[AverageIndex]=counter;/*increment the chunk counter*/
                i++;


            }
            else /*if condition is not satisfied then move this part and create new chunk*/
            {   
                
                counter=1;/* set counter one because new chunk created*/
                AverageIndex++; /*increment averageindex for the new chunk*/
                AverageChunk[AverageIndex]=n;/*assign new value to AverageChunk array*/
                ChunkCount[AverageIndex]=counter;/*assing the number of numbers to ChunkCount*/
                a=n;/*assing new values for a and b*/
                b=n;
                i++;/*increment i then move new numbers in NumbersArray*/
            }
        }
       
    }
    return AverageIndex;/*Return the averageindex which is used for holding the ChunkCount and AverageChunk size for further usage*/
}

void Initialize2DArray(int AverageIndex,double ChunkNumberStorage[][size],double *NumberArray,int *ChunkCount)
{   
    
   int Stopper=0;/*Variable for size of number in each chunk*/
   int CounterForInitialize=0;/*is used for if this number equals the ChunkCount[i] size then get out of the while loop*/
   int Waiter=0;/*Just index for determine the Numbers in NumberArray in each chunk*/
   for(int i=0;i<=AverageIndex;i++)
   {    

        Stopper = 0;
        CounterForInitialize=0;
        while(CounterForInitialize != ChunkCount[i])
        {   
            ChunkNumberStorage[i][Stopper]=NumberArray[Waiter];/*Assing the numberarray numbers to ChunkNumberStorage according it's index*/
            Stopper++;/*Determines the column value in ChunkNumberStorage*/
            CounterForInitialize++;
            Waiter++;
        }
   }
}



void Print2DArray(int AverageIndex,int *ChunkCount,double ChunkNumberStorage[][size])
{
   FILE * myFile;
   myFile=fopen("output.txt","w");
    for(int i=0;i<=AverageIndex;i++)/*printing all values from 2dArray according the counts in the ChunkCounts*/
   {    
       for(int j = 0; j < ChunkCount[i]; j++){
        fprintf(myFile, "%.4lf ", ChunkNumberStorage[i][j]);
       }
       fprintf(myFile, "\n");
   } 
}


void SortArray(int AverageIndex,int *ChunkCount,double ChunkNumberStorage[][size],double *AverageChunk)
{
   
   double av_temp , storage_temp, count_temp;
   int max;


   for(int i = 0; i < AverageIndex; i++){
    for(int j = i+1; j <= AverageIndex; j++){
        if(AverageChunk[i] > AverageChunk[j]){ /*if so swap those values in  AverageChunk  and ChunkCounter arrays*/
            av_temp = AverageChunk[i];
            AverageChunk[i] = AverageChunk[j];
            AverageChunk[j] = av_temp;

            count_temp = ChunkCount[i];
            ChunkCount[i] = ChunkCount[j];
            ChunkCount[j] = count_temp;

            max = (ChunkCount[i] > ChunkCount[j]) ? ChunkCount[i] : ChunkCount[j];/*determine the max number of chunk*/

            for(int m = 0; m < max; m++){ /* swaps ChunkNumberStorage values ascending order according to Average of chunks*/
                storage_temp = ChunkNumberStorage[i][m];
                ChunkNumberStorage[i][m] = ChunkNumberStorage[j][m];
                ChunkNumberStorage[j][m] = storage_temp;
            }
        }
    }
   }

  
}


