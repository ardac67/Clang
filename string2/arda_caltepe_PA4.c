#include <stdio.h>
#include <string.h>
#define ROW 100
#define COLUMN 251

/* These functions prints the indexes if the functions finds the data
    * char *ch is the char that needs to be found in the 2d char array
    * char textCH[][COLUMN] the 2d array that contains the text to be searched
    * FILE * write is the file pointer for the managing write operations to file
    * int row is the row parameter that some functions need it because row count will be starting index when searching the data
*/
int SearchEast(char * ch,char textCH[][COLUMN],FILE* write);
int SearchSouth(char * ch,char textCH[][COLUMN],FILE* write);
int SearchSouthEast(char * ch,char textCH[][COLUMN],FILE* write);
int SearchWest(char * ch,char textCH[][COLUMN],int row,FILE* write);
int SearchNorth(char * ch,char textCH[][COLUMN],int row,FILE* write);
int SearchNorthWest(char * ch,char textCH[][COLUMN],int row,FILE* write);
int SearchNorthEast(char * ch,char textCH[][COLUMN],int row,FILE* write);
int SearchSouthWest(char * ch,char textCH[][COLUMN],FILE* write);


int main(){

    char ch[10];/*Defining char array for holding input1.txt words one by one*/
    char textCH[ROW][COLUMN]={'\0'};/*2d char array for hold the input2.txt file and initializing it all indexes with'\0'*/
    char temp[COLUMN] = {'\0'};/*Initializing temp char for indicate boundries*/

    int row=1;
    int lastRow;
    int max=0; /*defining max characters of 2darray line by line*/

    FILE *myFile;
    myFile=fopen("input2.txt","r");

    /*filling textCH with the input2.txt*/
    while( fscanf(myFile,"%s",temp) != EOF ) 
    {   

        for(int i=1;i<COLUMN;i++)
        {
            textCH[row][i]=temp[i-1];
        }
        if(max<strlen(temp))
        {
            max=strlen(temp); /*finding row that containes maximum number char in 2d array*/
        }        
        row++;
        for(int i=0;i<strlen(temp);i++)/*resetting char array to remove  residue inside it*/
        {
            temp[i]='\0';
        }
        memset(temp, '\0', sizeof(temp));/*resetting char array to remove  residue inside it*/

    }

    /*filing textCH with ' ' and '\0' */
    for(int i=1;i<row;i++)
    {
        for(int j=1;j<=max+1;j++)
        {   

            if(textCH[i][j]=='\0')
            {
                textCH[i][j]=' '; /* if textCH[i][j] is not a null characther  and number of char inside it smaller then the max number of char in any line then print ' ' after reading 
                                    to achieve the bonus part
                                  */
            }
        }
    }
 
 
    FILE *myFileInput,*myFileOutput;
    myFileInput=fopen("input1.txt","r");
    myFileOutput=fopen("output.txt","w");

    /*reading input1.txt one word at time and finding their position if it is found*/
    while( fscanf(myFileInput,"%s",ch) != EOF ) 
    {   
        SearchEast(ch,textCH,myFileOutput);
        SearchSouth(ch,textCH,myFileOutput);
        SearchSouthEast(ch,textCH,myFileOutput);
        SearchWest(ch,textCH,row,myFileOutput);
        SearchNorth(ch,textCH,row,myFileOutput);
        SearchNorthWest(ch,textCH,row,myFileOutput);
        SearchNorthEast(ch,textCH,row,myFileOutput);
        SearchSouthWest(ch,textCH,myFileOutput);   
        
        for(int i=0;i<strlen(ch);i++)/*resetting char array to remove  residue inside it*/
        {
            ch[i]='\0';
        }
       memset(ch, '\0', sizeof(ch)); /*resetting char array to remove  residue inside it*/


    }
    fclose(myFileInput);
    fclose(myFileOutput);  

  return 0;   
}


int SearchEast(char * ch,char textCH[][COLUMN],FILE *output){

   int j=1;/*second index for for first loop*/
   int flag=1;/*to determine the indexes found or not*/
   int CharCounter=0;/*index of char which is searched in array*/
    for(int i=1;i<ROW && flag && textCH[i][j]!='\0';i++)
    {
       

        for(int j=1;j<COLUMN && flag && (textCH[i][j]!='\0'&& textCH[i][j]!=' ');j++)
        {   
            if(ch[CharCounter]==textCH[i][j])/*if first indexes matches increment char counter*/
            {
                CharCounter++;
                if(textCH[i][j+1]!=ch[CharCounter] && ch[CharCounter]!='\0')/*if second or more matches set flag one and iterate again*/
                {
                    flag=1;
                  
                } 
                if(CharCounter==strlen(ch))/*if sum of index of searched char counts equals string lenght then set flag zero and print the indexes */
                {
                    fprintf(output,"%s (%d %d) E\n",ch,i,j-CharCounter+1);
                    flag=0;
                   
                }
                
                
                
            }
            else 
            {
                CharCounter=0;
                flag=1;
                
            }   
        }

        
    } 

   

}

int SearchSouth(char * ch,char textCH[][COLUMN],FILE *output){

   int j=1;/*second index for for first loop*/
   int flag=1;/*to determine the indexes found or not*/
   int CharCounter=0;/*index of char which is searched in array*/


    for(int i=1;i<ROW  && flag && (textCH[i][j]!='\0');i++)/*start i=1 means start row 1 until see the null char*/
    {   
        for(int j=1;j<COLUMN && flag && (textCH[i][j]!='\0');j++)/*start from column 1 until see the null char*/
        {   
                CharCounter=0;    
                if(ch[CharCounter]==textCH[i][j]) /*if first indexes matches*/
                {
                    int n=i;/*swap indexes with new variables*/
                    int m=j; /*swap indexes with new variables*/
                    while((textCH[n][m]!='\0' )&& flag) /*iterate new loop until see the null character*/
                    {   
                        if(textCH[n][m]==' ')/*if you see empty char then move to the next row*/
                        {
                            n++;
                        }
                        else 
                        {
                            if(ch[CharCounter]==textCH[n][m])
                            {   
                                if(CharCounter==strlen(ch)-1)/*if counter equals the lenght of the string-1 then print it else move to the other index*/
                                {
                                    fprintf(output,"%s (%d %d) S\n",ch,i,j);
                                    flag=0;
                                }
                                else flag=1;
                                CharCounter++;
                            }
                            else if(ch[CharCounter]!=textCH[n][m])/*if it is not equal to each of it then break the inner loop , search with new indexes*/
                            {
                                break;
                            }
                            n++;
                        }
                            
                    }
                }
                else 
                {
                    CharCounter=0;
                    flag=1;
                }
               
        }   
         
    } 

   
}  

int SearchSouthEast(char * ch,char textCH[][COLUMN],FILE *output){

   int j=1;
   int flag=1;
   int CharCounter=0;
   int i=1;
    for(int i=1;i<ROW && flag && textCH[i][j]!='\0';i++)
    {
       

        for(int j=1;j<COLUMN && flag && (textCH[i][j]!='\0'&& textCH[i][j]!=' ');j++)
        {   
            CharCounter=0;
            if(ch[CharCounter]==textCH[i][j])/*if first indexes matches swap it*/
            {
               int k=i;
               int m=j; 
               
               while((textCH[k][m]!='\0')&& flag)
               {
                    if(textCH[k][m]==' ')/*if empty charecter found then move to the next indexes*/
                    {
                        k++;
                        m++;
                    }
                    else
                    {
                        if(ch[CharCounter]==textCH[k][m])
                        {   
                            if(CharCounter==strlen(ch)-1)
                            {
                                fprintf(output,"%s (%d %d) SE\n",ch,i,j);
                                flag=0;
                            }
                            else flag=1;
                            CharCounter++;
                           
                        }
                        else if(ch[CharCounter]!=textCH[k][m])
                        {
                            break;
                        }
                    
                        k++;
                        m++;   
                    }
                    
               }
            }
            else 
            {
                flag=1;
            } 
            /* printf("%d\n",CharCounter);
            printf("%d %d\n",i,j); */
            
        }

        
    } 
   
        
} 

int SearchWest(char * ch,char textCH[][COLUMN],int row,FILE *output){

   int i=row-1;/*indicates last row of the input2.txt */
   int flag=1;
   int CharCounter=0;
   int LineCharCount=1;/*variable for countint the chars in all row*/
   int j=1;
    
    for(i;i>=1 && flag && textCH[i][j]!='\0';i--)/*start from last row*/
    {
        LineCharCount=1;
        for(int j=1;j<COLUMN && flag && (textCH[i][j]!='\0'&& textCH[i][j]!=' ');j++)/*calculating character of the line*/
        {
            LineCharCount++;
        }
        for(int k=LineCharCount-1;k>=1 && flag && (textCH[i][k]!='\0'&& textCH[i][k]!=' ');k--)/*start from last charecter of the line*/
        {   
            if(ch[CharCounter]==textCH[i][k])/*if first indexes matches move to other indexes and increment the CharCounter*/
            {
                CharCounter++;
                if(textCH[i][k+1]!=ch[CharCounter] && ch[CharCounter]!='\0')
                {
                    flag=1;
                } 
                if(CharCounter==strlen(ch))
                {
                    fprintf(output,"%s (%d %d) W\n",ch,i,k+CharCounter);
                    flag=0;
                }
                
                
                
            }
            else 
            {
                CharCounter=0;
                flag=1;
            }   
        }
        

        
    } 
    

   

} 

int SearchNorth(char * ch,char textCH[][COLUMN],int row,FILE *output){
    
   int j=1;/*second index for for first loop*/
   int flag=1;/*to determine the indexes found or not*/
   int CharCounter=0;/*index of char which is searched in array*/
   int i=1;


    for(int i=row-1;i>=1  && flag && (textCH[i][j]!='\0');i--)/*starts from last row*/
    {   
        for(int j=1;j<COLUMN && flag && (textCH[i][j]!='\0' && textCH[i][j]!=' ');j++)
        {   
            CharCounter=0;
            if(ch[CharCounter]==textCH[i][j])/*if first indexes matches swaps it*/
            {
               int n=i;
               int m=j; 
               while(textCH[n][m]!='\0' && flag)/*stop when you see null char*/
               {    
                    if(textCH[n][m]==' ')/*if empty char found decrement the row index*/
                    {
                        n--;

                    }
                    else
                    {

                        if(ch[CharCounter]==textCH[n][m])
                        {   
                        if(CharCounter==strlen(ch)-1)
                        {
                            fprintf(output,"%s (%d %d) N\n",ch,i,j);
                            flag=0;
                        }
                        else flag=1;
                        CharCounter++;
                         }
                        else if(ch[CharCounter]!=textCH[n][m])
                        {
                            break;
                        }
                        n--;
                    }
                   
               }
            }
            else 
            {
                CharCounter=0;
                flag=1;
            }    
        }   
         
    } 

 


}  
 

int SearchNorthWest(char * ch,char textCH[][COLUMN],int row,FILE *output){

   int i=row-1;/*indicates last row*/
   int flag=1;
   int CharCounter=0;
   int LineCharCount=1;/*indicates character counts in line*/
   int j=1;

    for(i;i>=1 && flag && textCH[i][j]!='\0';i--)/*starts from last row*/
    {
        LineCharCount=1;
        for(int j=1;j<COLUMN && flag && (textCH[i][j]!='\0'&& textCH[i][j]!=' ');j++)/*finding  row character count*/
        {
            LineCharCount++;
        }

        for(int k=LineCharCount-1;k>=1 && flag && (textCH[i][k]!='\0'&& textCH[i][k]!=' ');k--)/*start from character count and stop when you see null character or empty character*/
        {   
            CharCounter=0;
            
            if(ch[CharCounter]==textCH[i][k])
            {
               int n=i;
               int m=k; 
               
               while(textCH[n][m]!='\0' && flag)/*until null character*/
               {    
                    if(textCH[n][m]==' ') /*if you see empty character decrement the indexes*/
                    {
                        n--;
                        m--;
                    }
                    else
                    {
                              if(ch[CharCounter]==textCH[n][m])
                                {   
                                    if(CharCounter==strlen(ch)-1)
                                    {
                                        fprintf(output,"%s (%d %d) NW\n",ch,i,k);
                                        flag=0;
                                    }
                                    else flag=1;
                                    CharCounter++;
                                }
                                else if(ch[CharCounter]!=textCH[n][m])
                                {
                                    break;
                                }
                                n--;
                                m--;
                    }
                  
               }
            }
            else 
            {
                flag=1;
            }
            
        }

        
    } 


} 


int SearchNorthEast(char * ch,char textCH[][COLUMN],int row,FILE *output){

   int i=row-1;
   int flag=1;
   int CharCounter=0;
   int LineCharCount=1;
   int j=1;

    for(i;i>=1 && flag && textCH[i][j]!='\0';i--)/*start from last row*/
    {
       

        for(int k=1;k<COLUMN && flag && (textCH[i][k]!='\0'&& textCH[i][k]!=' ');k++)/*start from 1 to null or empty char*/
        {   
            CharCounter=0;
           
            if(ch[CharCounter]==textCH[i][k])/*if first indexes matches then*/
            {
               int n=i;/* swap indexes with new variables*/
               int m=k; 
               
               while((textCH[n][m]!='\0' )&& flag)
               {    
                    if(textCH[n][m]==' ') /*if you see empty character decrement the row increment column*/
                    {
                        n--;
                        m++;
                    }
                    else
                    {
                        if(ch[CharCounter]==textCH[n][m])
                        {   
                            if(CharCounter==strlen(ch)-1)
                            {
                                fprintf(output,"%s (%d %d) NE\n",ch,i,k);
                                flag=0;
                            }
                            else flag=1;
                            CharCounter++;
                        }
                        else if(ch[CharCounter]!=textCH[n][m])
                        {
                            break;
                        }
                        n--;
                        m++;
                    }
                   
               }
            }
            else 
            {
                flag=1;
            }
            
        }

        
    } 


} 


int SearchSouthWest(char * ch,char textCH[][COLUMN],FILE * output){

   int flag=1;
   int CharCounter=0;
   int LineCharCount=1;
   int j=1;

    for(int i=1;i<ROW && flag && textCH[i][j]!='\0';i++)/*starts from first row*/
    {
        LineCharCount=1;
        for(int j=1;j<COLUMN && flag && (textCH[i][j]!='\0'&& textCH[i][j]!=' ');j++)/*count the row char*/
        {
            LineCharCount++;
        }

        for(int k=LineCharCount-1;k>=1 && flag && (textCH[i][k]!='\0'&& textCH[i][k]!=' ');k--)/*start from Charecter count of the row to null or empty char*/
        {   
            CharCounter=0;
            
            if(ch[CharCounter]==textCH[i][k])
            {
               int n=i;
               int m=k; 
               
               while((textCH[n][m]!='\0')&& flag)
               {    
                    if(textCH[n][m]==' ')/*if you see empty character increment the row decrement column*/
                    {
                        n++;
                        m--;
                    }
                    else
                    {
                        if(ch[CharCounter]==textCH[n][m])
                        {   
                        if(CharCounter==strlen(ch)-1)
                        {
                            fprintf(output,"%s (%d %d) SW\n",ch,i,k);
                            flag=0;
                        }
                        else flag=1;
                        CharCounter++;
                        }
                        else if(ch[CharCounter]!=textCH[n][m])
                        {
                            break;
                        }
                        n++;
                        m--;
                    }
                    
               }
            }
            else 
            {
                flag=1;
            }
            
        }
  
    } 
} 