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

            if(str[i]=='+' || str[i]=='-' || str[i]=='*' || str[i]=='/' || str[i]=='^') i--;
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

void CalculateTheArithmeticalExpression(char str[])           //Biggest/Main function in our program that will calculate the whole arithmetical expression
{
    for(int i=0;i<LengthOfString(str);i++)                    //begin by going through the whole string (from the 0 index to the last one (LengthOfString-1))
    {
        if(str[i]=='*' || str[i]=='/' || str[i]=='^')         //the three operations that have priority are multiplication, division and exponentiation
        {//so whenever one of these three operations is found do the following:
            int j;           //use an index "j" that will move as many times as there are intervals between the operation and the right operand
            for(j=i+1;str[j]==' ';j++);

            int m=j;         //now, use an index "m" that will move as many times as there are digits in the right operand (starting from the place of "j", of course)
            if(str[j+1]>='0' && str[j+1]<='9')
            {
                for(m=j+1;str[m]>='0' && str[m]<='9';m++);
            }
            else m=j+1;      //if not, this means that the found number is only one digit, therefore "m" increases just once

            int rightBorder=m-1;     //use a variable for the right border here (used later in code), that is exactly where the right operand/number ends (where its last digit it situated)

            long long actualRightNumber=0;    //define a variable that will serve as the "actual" right operand
            int currentDigit=0;              //one variable for each current digit that we are processing
            int multiplier=1;               //and one multiplier which will serve to form the number as a whole just by its digits
            do                             //use a do-while operator, because we need at least one iteration
            {
                currentDigit = str[m-1] - '0';      //extract the last digit, beginning from the very last
                actualRightNumber += currentDigit * multiplier;   //add that digit to the new-forming number multiplied by 1, then 10, then 100 and so on...
                multiplier *= 10;        //the multiplier multiplies by 10 each iteration
                m--;                    //and "m" has to decrease once, since the last digit is already removed

            }while(m>j);               //the whole process continues, until the first digit of the found number is reached

    ///from here below the process is absolutely identical. It is just the mirrored counterpart of the situation above
            int l;
            for(l=i-1;str[l]==' ';l--);    //that index starts from the place of the operation and decreases instead of increase as long as there are intervals

            int n=l;
            if(str[l-1]>='0' && str[l-1]<='9')     //again, when a number is found it is counted how many digits it contains
            {
                for(n=l-1;str[n]>='0' && str[n]<='9';n--);
            }
            else n=l-1;

            int leftBorder=n+1;       //define the left border as well (again used later)

            long long actualLeftNumber=0;    //and with the same algorithm form the actual left operand here
            int currentDigitLeft=0;
            int multiplierLeft=1;
            do
            {
                currentDigitLeft = str[l] - '0';
                actualLeftNumber += currentDigitLeft * multiplierLeft;
                multiplierLeft *= 10;
                l--;

            }while(l>n);
    ///until here

         if(str[i]=='*')                 //now, if the found operation is multiplication:
            {
                int result=0;            //use a variable that will serve to show the final result of the operation
                result = actualLeftNumber*actualRightNumber;      //just multiply the left and the right operands

                for(int I=leftBorder;I<=rightBorder;I++)
                {//after the multiplication is done, make all spaces, that are occupied by the operation and the two operands, simply an interval (it's like they become empty)
                    str[I]=' ';
                }

                int numlen=LengthOfNumber(result);       //use the aforewritten function to give value of a new variable "numlen"
                while(numlen>0)                         //will decrease that variable each iteration, until it becomes zero
                {
                    str[rightBorder] = result%10 + '0';    //the rightmost container will receive the char of the corresponding digit (that's why we add '0' (or 48))
                    result /= 10;                         //the result number has its last digit removed
                    rightBorder--;                       //decrease the right border
                    numlen--;                           //and the length of the number
                }//now, the number is input into the original string, replacing the operation and the operands and all other spaces previously occupied by them have become intervals

            }

         if(str[i]=='^')        //if the operation is exponentitation
            {
                int result=0;
                result = pow((double)actualLeftNumber,(int)actualRightNumber);      //cast the base to double and the exponent to int

                for(int I=leftBorder;I<=rightBorder;I++)
                {
                    str[I]=' ';
                }

                if(rightBorder-leftBorder+1<LengthOfNumber(result))        //here, check to see if the needed space for the result number is actually bigger than the space provided (ex. 9^6 = 531441)
                {
                    int difference=LengthOfNumber(result)-(rightBorder-leftBorder);       //define a variable that calculates the difference which is how many more spaces we need
                    for(int q=LengthOfString(str)-1+difference;q>leftBorder;q--)
                    {//"shift" the whole string to the right exactly that much spaces
                        str[q]=str[q-difference];
                    }
                    rightBorder += difference;   //the right border changes as well

                    int numlen=LengthOfNumber(result);  //and then do the usual conversion into char and write it in the string
                    while(numlen>0)
                    {
                        str[rightBorder] = result%10 + '0';
                        result /= 10;
                        rightBorder--;
                        numlen--;
                    }
                }
                else       //if the space is enough just do the conversion without adding additional spaces
                {
                    int numlen=LengthOfNumber(result);
                    while(numlen>0)
                    {
                        str[rightBorder] = result%10 + '0';
                        result /= 10;
                        rightBorder--;
                        numlen--;
                    }
                }
            }

         if(str[i]=='/')      //if the operation is division
            {
                double result=0;
                result = (double)actualLeftNumber/(double)actualRightNumber;     //cast the two numbers to double,because the result could be a decimal number

                for(int I=leftBorder;I<=rightBorder;I++)       //again, make all spaces from the beginning of the left operant to the end of the right operand, empty
                {
                    str[I]=' ';
                }

                int decimalPointPosition=(leftBorder+rightBorder)/2;   //place the decimal point exactly at the middle of the whole occupied space from the two operands and the operation
                int decimalPointPositionSec = decimalPointPosition;
                str[decimalPointPosition]='.';

                int numlen=LengthOfNumber(result);     //initialize a variable that will serve as the length of the number(the number of digits is in)
                int wholePart=result;                 //take out the integer part (every digit before the decimal point)
                int multiplier=10;                   //use a multiplier variable, in order to move the decimal point to the right each iteration
                int currentLastDigit=0;             //and one more variable for the digit, we're currently on

                if(wholePart==0)
                {
                    str[decimalPointPosition-1]=wholePart%10+'0';
                }
                while(wholePart>0)                 //the integer part will get its last digit removed each iteration, so the condition is - while it it anything bigger than zero
                {
                    decimalPointPosition--;                  //we have to add those elements to the left of the decimal point (i.e. before the decimal point)
                    currentLastDigit = wholePart%10;         //take out the currently last digit
                    wholePart /= 10;
                    str[decimalPointPosition]=currentLastDigit + '0';     //and place that taken digit right to the decimal point (after that - right next to the previous last digit)
                }

                int countOfIntegerPartDigits;               //variables say enough by their names
                countOfIntegerPartDigits = LengthOfNumber((int)result);
                int countOfDigitsAfterDecimalPoint;         //that't the variable we're going to use to see how many digits are there after the decimal point
                countOfDigitsAfterDecimalPoint = numlen - countOfIntegerPartDigits; //when we subtract the count of the digits before the point from the count of all digits, we get the count of these that stand after the point

                double decimalWithRightShiftedPoint = result;      //use another variable that will initially begin as a real number
                int currentDigitOfDecimal;       //and declare other variable that will serve to operate with the digit we're currently on (equivalent variable to the "currentDigit" and "currentLastDigit" ones)

                if((int)result==result)          //before the process, just check if there are actually no digits after the decimal point (i.e. the decimal is an integer)
                {
                    str[decimalPointPositionSec+1]='0';   //and just put one 0 after the point (ex.: 15.0)
                }

                while(countOfDigitsAfterDecimalPoint>0)   //otherwise, when there are digits after the decimal point:
                {//do identical algorithm to the one that placed the digits before the decimal point, it's just mirrored
                    decimalPointPositionSec++;   //starting right after the place of the decimal point
                    decimalWithRightShiftedPoint *= 10;   //each iteration move the decimal point to the right once
                    currentDigitOfDecimal = (int)decimalWithRightShiftedPoint % 10;     //and extract the last digit of the newly-former decimal number (of course, cast it to type int in order to use "%" operation)
                    countOfDigitsAfterDecimalPoint--;     //and therefore the count of the actual digits after the decimal point decreases each iteration
                    str[decimalPointPositionSec]=currentDigitOfDecimal + '0';   //at the end, place that extracted number right after the decimal point (after the first iteration - place it right next to the previously last digit)
                }

            }


        }
    }
               cout<<str;//test
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
                CalculateTheArithmeticalExpression(str);
            }
        }

    }

    arithmeticalExpression.close();           //at the end, close the file that has been read


    return 0;
}

