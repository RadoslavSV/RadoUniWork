/**
*
* Solution to course project # 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Radoslav Velkov
* @idnumber 62528
* @compiler GCC
*
*
*
*/



#include <iostream>
#include <fstream>             //use <fstream> library in order to be able to read and write in files
using namespace std;

int LengthOfString(char s[])                //implement a function that counts how many symbols are there in the string
{
    int idx;                                //define "idx" outside of the loop's scope, because we use it outside of that scope in the return statement
    for(idx=0;s[idx]!='\0';idx++);          //use "idx" as an index that will simply increase by one each iteration till the terminating zero is reached
    return idx;
}

bool CorrectInputData(char str[])         //write a function that will check if all symbols in the expression are legal (either a digit from 0 to 9 OR +, -, *, /, (, ), ^)
{
    for(int i=0;i<LengthOfString(str);i++)
        {
            if( (str[i]<'0' || str[i]>'9') &&  //if that's not fulfilled - then it's not a digit
                (str[i]!=' ' && str[i]!='+' && str[i]!='-' && str[i]!='*' && str[i]!='/' && str[i]!='(' && str[i]!=')' && str[i]!='^') )   //and if that's not as well - then it's neither an allowed math operation
            {
                return false;   //and this is enough to conclude that the read expression contains unallowed symbols
            }//when the function reaches a "return" statement, it terminates
        }
        return true;
}

int main()
{
    const int MAX_SIZE=10000;      //initialize a big enough constant variable that will serve as the maximum size of the read string from the file
    char str[MAX_SIZE];            //define a character sequence that will be read from the .txt file
    ifstream arithmeticalExpression;         //input stream class to operate on files - "arithmeticalExpression" so we can read the written arithmetical expression from a file
    arithmeticalExpression.open("test2.txt",ios::in);         ////open the .txt file
    if(!arithmeticalExpression)               //initially, check if the program was able to open the file
    {
        cout<<"NaN"<<endl;                    //if not - then print appropriate message for an error and do not continue below
    }

    while(arithmeticalExpression.getline(str,MAX_SIZE,'\n'))    //when start reading from the opened file:
    {
        if(not CorrectInputData(str)) cout<<"NaN"<<endl;       //firstly, use the aforeimplemented function to check for illegal symbols
        else      //if no such symbols are found:
        {

        }

    }

    arithmeticalExpression.close();           //at the end, close the file that has been read


    return 0;
}

