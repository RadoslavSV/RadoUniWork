/**
*
* Solution to homework assignment 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Radoslav Velkov
* @idnumber 62528
* @task 1
* @compiler GCC
*
*/



#include <iostream>
using namespace std;
int main()
{
    int N=0;
    bool isTriangular=false;        //initialize a bool variable (equal to 0), which value we will use at the end to determine whether the input line is "triangular"
    const int SIZE=100;           //initialize a constant with value of the maximum numbers that can be input (100)
    cin>>N;

    while(N<3 || N>100)          //use a while loop to see if the input number N is between 3 and 100;
    {                            //if not - then input again till an N which belongs in [3;100] is entered
        cin>>N;
    }

    int line[SIZE];              //initialize an array ("line" as a line of natural numbers) with size the maximum size that can be input(using the constant we've defined)

    for(int i=0;i<N;i++)         //create a for loop to input every number we need in the first N places of the array (the others will remain unused)
    {
        cin>>line[i];
    }

    for(int i=0, j=N-1; i<N/2, j>N/2; i++, j--)      //we will use for loop to go through the whole array; using two variables "i" and "j"
    {   //"i" will count the first half of numbers, so it starts from 0, increases with 1 each time and has to get to the half of the line
        //"j" is used as index of the second half of numbers, starting from the last one and decreasing with 1 each iteration, until is reaches the half of the line
        if( max(line[i],line[i+1]) - min(line[i],line[i+1]) != max(line[j],line[j-1]) - min(line[j],line[j-1]) )
        { isTriangular=false; break; }         //use if operator to check whether the absolute values of the subtractions between two next numbers are mirrorly equal
        else isTriangular=true;                //if there is just ONE case where these subtractions are different then it terminates the whole checking (with break operator) and gives "false" value of the bool variable
    }      // with this else we are sure that there are no different subtractions and we can conclude that the "line" is triangular

    if(isTriangular) cout<<1<<endl;
    else cout<<0;

    return 0;
    }
