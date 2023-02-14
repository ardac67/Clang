#include <stdio.h>
#define EPSILON 0.001


  /* Defining input quantity*/
  int InputCount=6;
  int InputCounter=0;

   /*Defining Class1 and Class2 point summations*/ 
   double Class1XSum=0;
   double Class1YSum=0;
   double Class2XSum=0;
   double Class2YSum=0;

   /* Defining a variable to hold input values*/
   double TestInputXC1=0;
   double TestInputYC1=0;
   double TestInputXC2=0;
   double TestInputYC2=0;


   /* Finding average of X coordinates // Takes parameter as Summation of x values for each class  */ 
double FindAverageX(double X){

    double averageX=X/(InputCount/2);
    
    return averageX;

}
 /* Finding average of Y coordinates // Takes parameter as Summation of y values for each class*/ 
double FindAverageY(double Y){

    double averageY=Y/(InputCount/2);
    
    return averageY;
}

/* Finding Slope of two average point's line and takes parameter return values of FindAverageX and FindAverageY*/
double FindSlope(double X1C1,double X2C2,double Y1C1,double Y2C2){
    double Slope;
    if((X2C2-X1C1)==0){

        Slope=(Y2C2-Y1C1)/EPSILON;
    }
    else {Slope=(Y2C2-Y1C1)/(X2C2-X1C1);};
    
    return Slope;

}
/* This function is used to find midpoint of line and calculates the resulting normal line slope and defines the 
   equation of the normal line separetes two average points

// 
  Takes paremeters from two functions returns values which are FindAverage and FindSlope 
  also it takes paremeter from inputs for the defining the (x,y) points classes. 
*/  
double FindMidPointAndLineEquationAndResult(double X1C1,double X2C2,double Y1C1,double Y2C2,double Slope,double X,double Y){

    double MidPointX=(X2C2-X1C1)/2;
    double MidPointy=(Y2C2-Y1C1)/2;
    double ControlForClass1;
    double ControlForClass2;
    /*Normal line slope*/
    double SlopeVertical=-1*(1/Slope);

    
    /* Equations*/
    ControlForClass1=Y-MidPointy-SlopeVertical*(X-MidPointX);
    ControlForClass2=Y-MidPointy-SlopeVertical*(X-MidPointX);
    /*Control for the class types*/
    if(ControlForClass1>0){
      printf("class1\n");

    }
    else if(ControlForClass2<0){
      printf("class2\n");
    }
    else  return 0;
    


}


int main()
{   

 



  do {
    
    
    if(InputCounter<InputCount/2){

         /*if scanf returns 0 then exit*/
         if(scanf("%lf",&TestInputXC1)==0){ return 0;};
         if(scanf("%lf",&TestInputYC1)==0){return 0;};

         /*Summing inputs*/ 
         Class1XSum=Class1XSum+TestInputXC1;   
         Class1YSum=Class1YSum+TestInputYC1;   
         
         InputCounter=InputCounter+1;

    }

   

    if(InputCounter>=InputCount/2){
       
          /*if scanf returns 0 then exit*/
         if(scanf("%lf",&TestInputXC2)==0){return 0;};
         if(scanf("%lf",&TestInputYC2)==0){return 0;}; 
         /*Summing inputs*/ 
         Class2XSum=Class2XSum+TestInputXC2; 
         Class2YSum=Class2YSum+TestInputYC2;    
         
         InputCounter=InputCounter+1;

    }
     

  }
  while(InputCounter<InputCount);


  
  /*Check value for the validation*/
  int check =1;
  do {

    
    double inputX;
    double inputY;  
    if(scanf("%lf",&inputX)==0){check=0;};
    if(scanf("%lf",&inputY)==0){check=0;};

    if(check==1){

      
      FindMidPointAndLineEquationAndResult(FindAverageX(Class1XSum),FindAverageX(Class2XSum),FindAverageY(Class1YSum),FindAverageY(Class2YSum),FindSlope(FindAverageX(Class1XSum),FindAverageX(Class2XSum),FindAverageY(Class1YSum),FindAverageY(Class2YSum)),inputX,inputY);

    }
  }
  while(check);
  
}

