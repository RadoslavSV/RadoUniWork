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

    while(arithmeticalExpression.getline(str,10000,'\n'))
    {
        cout<<str<<endl;
    }

    arithmeticalExpression.close();           //at the end, close the file that has been read


    return 0;
}

