#include <stdio.h>
#include <stdlib.h>
#include "genlib.h"
#include "simpio.h"
#include <strlib.h>
#define N 3


bool StringEqual(string s1, string s2);

int main()
{

    int i, j;
    double c[N], A[N][N], b[N], Aw[N][N], temp;
    string Improving, MRL[N], MRV[N], MRLw[N], MRVw[N];

    printf("This program executes the duality process \n");
    printf("turning a primary linear problem to its contradicting form \n");
    printf("NOTE: This version solves square sized problems: No of Variables = No of Limitations \n");
    printf("NOTE: Set the size of the squared problem by defining the constant N within the code. Default size: 3 \n \n");
    printf("Set the direction of the improving process \n");
    printf("Proper inputs: min , max \n");


    /*Security loop used for countering wrong improving direction given by the user */

    Improving = GetLine();
    while (!((StringEqual(Improving, "min"))||(StringEqual(Improving, "max"))))
    {
       printf("Wrong input, please enter a valid input \n");
          Improving = GetLine();
    }




    /*Repeating process used to register user inputs in table (c) , which holds the constants of the objective function */
    /*C already provides a security loop for non numerical inputs in numerical variables, we are using double variable type to save the inputs
    therefore using a security loop here is redundant */

    printf("Set the constants of your objective Function \n ");
    for (i = 0; i < N; i++)
    {
        printf("Set the constant %d of your objective Function \n ", i+1);
        c[i] = GetReal();
    }




    /* Nested Repetition, used to register user inputs in table A which holds the constants of the variables of each limitational function */
    /*                    used to register user inputs in table MRL which holds the mathematical relations between tables A and b */
    /*                    used to register user inputs in table b which holds the value b of each limitational function */
    /* Nested Repetition is used because table A is two-dimensional, while tables MRL and b are one-dimensional, therefore table A is being
    formed within the Nested Repetition while tables MRL and b are formed within the initial repeating process */
    /* Tables A and b are set as double type variables, therefore there is no need to include a false-input countering loop, table MRL is a string type variable
    therefore a false-input countering loop is included*/

    for(i=0;i<N;i++)
    {
       for(j=0;j<N;j++)
       {
          printf("Set the constant %d of your no. %d Limitational function \n",j+1, i+1);
          A[i][j] = GetReal();
       }
       printf("Set the mathematical relation between A and b of your No%d limitation \n", i+1);
       printf("Valid inputs( <= , >= , = ) \n");
       MRL[i] = GetLine();
       while(!((StringEqual(MRL[i], "<="))||(StringEqual(MRL[i], ">="))||(StringEqual(MRL[i], "="))))
            {
               printf("Wrong input, please enter a valid input ( <= , >= , = ) \n");
               MRL[i] = GetLine();
            }

       printf("Set the b value of the No. %d limitational function \n", i+1);
       b[i] = GetReal();
     }





    /* Repeating process used to register user inputs in table MRV , which holds the mathematical relations of the variables */

    for(i=0;i<N;i++)
    {
        printf("Set the mathematical relation of the No%d variable \n", i+1);
        printf("Valid inputs ( >=0 , <=0 , free ) \n");

          MRV[i] = GetLine();

        while(!((StringEqual(MRV[i], ">=0"))||(StringEqual(MRV[i], "<=0"))||(StringEqual(MRV[i], "free"))))
        {
            printf("Invalid input, please enter a valid input( >=0 , <=0 , free ) \n");
            MRV[i] = GetLine();
        }

    }


    /* FROM THIS POINT THE CODE EXECUTES THE DUALITY PROCESS AND RETURNS THE RESULTS ON SCREEN */
    /* FROM THIS POINT THE CODE EXECUTES THE DUALITY PROCESS AND RETURNS THE RESULTS ON SCREEN */
    /* FROM THIS POINT THE CODE EXECUTES THE DUALITY PROCESS AND RETURNS THE RESULTS ON SCREEN */



    /*Repeating process that prints the final form of the (c) table of the primary problem */

    printf("Primary Function: %s \n \n", Improving);

    for(i=0;i<N;i++)
    {
        printf("%g x%d ", c[i], i+1);
    }

    printf(" \n \n");




    /*Repeating process that prints the final form of the (A),(b) and (MRL) Tables of the primary problem */
    /*Nested repetition is used to print the two=dimensional table (A) */

    for(i=0;i<N;i++)
    {
        for (j=0;j<N;j++)
        {
            printf("%g x%d ", A[i][j], j+1);
        }
        printf(" %s %g \n", MRL[i], b[i]);
    }
    printf(" \n");




    /*Repeating process that prints the final form of the (MRV) Table of the primary problem */

    for(i=0;i<N;i++)
    {
        printf(" x%d %s ", i+1, MRV[i]);
    }
    printf(" \n");
    printf("-------------------- \n");



    /*  --------------------------------- */
    /*Calculating the form of tables c and b of the dual problem */

    for(i=0;i<N;i++)
    {
        temp = c[i];
        c[i] = b[i];
        b[i] = temp;
    }


    /*Calculating the form of the two-dimensional table A of the dual problem, Nested repetition required*/

    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            Aw[i][j] = A[j][i];
        }
    }


    /*Calculating tables MRLw and MRVw which host the mathematical relations of the limitations and the variables of the dual problem */
    /*The way that these tables are formed depends on the improving direction therefore the repeating process is used twice*/

    if( StringEqual(Improving, "max"))
    {

       for(i=0;i<N;i++)
       {

          if(StringEqual (MRV[i], "free"))
          {
            MRLw[i] = "=";
          }
          else if(StringEqual(MRV[i], ">=0"))
          {
            MRLw[i] = ">=";
          }
          else
          {
            MRLw[i] = "<=";
          }


          if(StringEqual(MRL[i], "="))
          {
            MRVw[i] = "free";
          }
          else if(StringEqual(MRL[i], "<="))
          {
            MRVw[i] = ">=0";
          }
          else
          {
            MRVw[i] = "<=0";
          }
       }
    }


    if (StringEqual(Improving, "min"))
    {

        for(i=0;i<N;i++)
        {

           if(StringEqual(MRV[i], "free"))
           {
              MRLw[i] = "=";
           }
           else if(StringEqual(MRV[i], ">=0"))
           {
              MRLw[i] = "<=";
           }
           else
           {
              MRLw[i] = ">=";
           }


           if(StringEqual(MRL[i], "="))
           {
              MRVw[i] = "free";
           }
           else if(StringEqual(MRL[i], ">="))
           {
              MRVw[i] = ">=0";
           }
           else
           {
              MRVw[i] = "<=0";
           }
       }

   }

/*Setting the opposite improving direction for the dual problem */

if( StringEqual(Improving, "max"))
{
    Improving = "min";
}
else
{
    Improving = "max";
}


  /*Repeating processes that print the final form of the dual problem */

      printf("Dual Function: %s \n", Improving);
      printf(" \n");



    for(i=0;i<N;i++)
    {
        printf("%g w%d ", c[i], i+1);
    }


    printf(" \n \n");


    for(i=0;i<N;i++)
    {
        for (j=0;j<N;j++)
        {
            printf("%g w%d ", Aw[i][j], j+1);
        }
        printf(" %s %g \n", MRLw[i], b[i]);
        }
    printf(" \n");



    for(i=0; i<N; i++)
    {
        printf(" w%d %s ", i+1, MRVw[i]);
    }
    printf(" \n");

    }


