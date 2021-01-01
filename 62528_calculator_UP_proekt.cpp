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
#include <cmath>
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

bool CorrectSequenceOfSymbols(char str[])        //write a function that will check if the order of the symbols is correct
{
    if(str[0]=='+' || str[0]=='-' || str[0]=='*' || str[0]=='/' || str[0]==')' || str[0]=='^') return false;
    //the first symbol cannot be an operation (because every operation need two operands - one before it and one after it); '(' is an exception

    if(str[LengthOfString(str)-1]=='+' || str[LengthOfString(str)-1]=='-' || str[LengthOfString(str)-1]=='*' || str[LengthOfString(str)-1]=='/'
       || str[LengthOfString(str)-1]=='(' || str[LengthOfString(str)-1]=='^') return false;
    //and the last symbol of the string cannot be an operation as well; here ')' is the exception

    for(int i=0;i<LengthOfString(str);i++)
    {
        if(str[i]>='0' && str[i]<='9')
        {//if the symbol is a digit between 0 and 9, it could be followed either by an interval or an operation (+,-,...)

            int m=i;
            if(str[i+1]>='0' && str[i+1]<='9')   //here, check to see if a digit is followed by more digits
            {
                for(m=i+1;str[m]>='0' && str[m]<='9';m++);        //use another variable "m" which will increase the times a digit is found right next to the first one found
            }
            i=m;   //by doing this, it's like we just skip all digits that are next to one another (obviously, because they compose a multi-digit number)

            if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/' || str[i]=='*') i--;
            //in the case where the operation is right after the number, that index should be decreased once, in order not to count the symbol for operation as the last digit of the number

            int j;
            for(j=i+1;str[j]==' ';j++);     //when a symbol different than an interval is encountered:
            if(str[j]>='0' && str[j]<='9') return false;     //if that symbol is again a digit, this means the read data is unallowed
        }
    }

    for(int i=0;i<LengthOfString(str);i++)   //the same here, but with the operations
    {
        if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/' || str[i]=='^')
        {//if the symbol is an operation, it could be followed either by an interval or a digit (0-9)
            int j;
            for(j=i+1;str[j]==' ';j++);
            if(str[j]=='+' || str[j]=='-' || str[j]=='*' || str[j]=='/' || str[j]=='^')
            {
                return false;
            }
        }
    }

    return true;   //eventually, if nothing illegal is found, return true (thus the character sequence can be calculated)
}

int LengthOfNumber(double num)     //write a function that returns the number of digits in a number (both integer and double)
{
    int count = 0;               //set counter to zero
    if((int)num==0) count++;     //if the number is 0./something/, we add one for that 0
    double a=num;                //define a second main variable from type double that we use later
    while(int(num)!=0)           //convert the real variable to an integer (thus use only its digits before the decimal point)
    {
        num /= 10;              //remove the last digits each iteration
        count++;                //increase the counter
    }
    a -= int(a);                //after the integer counting is complete, we remove the whole integer part of the whole number and continue (if the whole number is integer, nothing else happens)
    while (a != 0)              //while it has not come to full zero
    {
        a = a * 10;             //move the decimal point once to the right
        count++;
        a = a - int(a);         //and again (each iteration) remove the newly-formed integer part
    }
    if(count>48) return 3;      //if the decimal is endless, it has three digits (a.bc or ab.c)
    else return count;          //in the general case, return the counter
}

void CalculateTheExpression(char str[])
{
    for(int i=0;i<LengthOfString(str);i++)
    {
        if(str[i]=='*' || str[i]=='/' || str[i]=='^')
        {
            int j;
            for(j=i+1;str[j]==' ';j++);

            int m=j;
            if(str[j+1]>='0' && str[j+1]<='9')
            {
                for(m=j+1;str[m]>='0' && str[m]<='9';m++);
            }
            else m=j+1;

            int rightBorder=m-1;

            long long actualRightNumber=0;
            int currentDigit=0;
            int multiplier=1;
            do
            {
                currentDigit = str[m-1] - '0';
                actualRightNumber += currentDigit * multiplier;
                multiplier *= 10;
                m--;

            }while(m>j);


            int l;
            for(l=i-1;str[l]==' ';l--);

            int n=l;
            if(str[l-1]>='0' && str[l-1]<='9')
            {
                for(n=l-1;str[n]>='0' && str[n]<='9';n--);
            }
            else n=l-1;

            int leftBorder=n+1;

            int lengthOfNumber=l-n;


            long long actualLeftNumber=0;
            int currentDigitLeft=0;
            int multiplierLeft=1;
            do
            {
                currentDigitLeft = str[l] - '0';
                actualLeftNumber += currentDigitLeft * multiplierLeft;
                multiplierLeft *= 10;
                l--;

            }while(l>n);

            if(str[i]=='*')
            {
                double result=0;
                result = (double)actualLeftNumber*(double)actualRightNumber;

                cout<<LengthOfNumber(result)<<endl;

            }
            if(str[i]=='/')
            {
                double result=0;
                result = (double)actualLeftNumber/(double)actualRightNumber;
                cout<<LengthOfNumber(result)<<endl;

            }
            if(str[i]=='^')
            {
                double result=0;
                result = pow((double)actualLeftNumber,(double)actualRightNumber);
                cout<<LengthOfNumber(result)<<endl;

            }

        }
    }
//cout<<str;
}

int main()
{
    const int MAX_SIZE=10000;      //initialize a big enough constant variable that will serve as the maximum size of the read string from the file
    char str[MAX_SIZE];            //define a character sequence that will be read from the .txt file
    ifstream arithmeticalExpression;         //input stream class to operate on files - "arithmeticalExpression" so we can read the written arithmetical expression from a file
    arithmeticalExpression.open("test2.txt",ios::in);         //open the .txt file
    if(!arithmeticalExpression)               //initially, check if the program was able to open the file
    {
        cout<<"NaN"<<endl;                    //if not - then print appropriate message for an error and do not continue below
    }

    while(arithmeticalExpression.getline(str,MAX_SIZE,'\n'))    //when start reading from the opened file:
    {
        if(not CorrectInputData(str)) cout<<"NaN"<<endl;       //firstly, use the aforeimplemented function to check for illegal symbols
        else      //if no such symbols are found:
        {
            if(not CorrectSequenceOfSymbols(str)) cout<<"NaN"<<endl;   //secondly, use the function that checks if the order of the read symbols is possible
            else
            {
                CalculateTheExpression(str);
            }
        }

    }

    arithmeticalExpression.close();           //at the end, close the file that has been read


    return 0;
}

