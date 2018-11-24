#include <iostream>
#include <chrono>
#include <cctype>
#include <string>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

string typetut(const int);
int offsetCount(const string, const string);

int main()
{
    int points = 2000; //beginning score in game
    int offset; //offset of character
    const int maxLength = 5; //the generated question will be of size 5

    string randString; //string to hold rand generated
    string userString; //string to hold userEntry/attempt

    srand(time(0)); /*holds time so random numbers are continuously different*/
    long timechange;

    steady_clock::time_point go, stop;
    //intializing clock
     go = steady_clock::now(); //timer starts
     stop = steady_clock::now(); //timer ends

    do
    {
        randString = typetut(maxLength);
        cout<< "Your current points " << points << ", just type -> ";

        for(int i = 0; i < maxLength; i++)
        {
            if (isalpha(randString[i]))
                cout << randString[i];

            else if (isdigit(randString[i]))
                cout << "[0-9]";
            else
                cout << "[%-!]";
        }

        cout<< ':';
        go = steady_clock::now();
        cin >> userString;
        stop = steady_clock::now();

        timechange = duration_cast<std::chrono::milliseconds>(stop-go).count(); //represents time it took to answer

        offset = offsetCount(randString, userString);
        if(offset <= 10000)
        {
            cout<< timechange << " milliseconds, you made it within the interval of 10000..."<<endl;
        }
        else
        {
            cout<< timechange << "milliseconds, you *failed* it within the interval of 10000..."<<endl;
        }
        cout<<"Offset: "<<offset<<endl;

        if(!offset && timechange < 10000)
            points += 500;
        else if(offset && timechange > 10000)
            points -= 500;
        else if(offset)
            points -= offset;
        else
            points -= timechange - 10000;

    } while(points > 0 && points < 5000);
    cout << "Bye..";

    return 0;
}

string typetut(const int length)
{
    string question;
    char randUpLowLetter;
    for(int i=0; i<length; i++)
        /*rannge through random numbers 0-9
            with this method there's 4/10 ways
            to get upper and lowercase letter
          1/10 chance of digit and special char*/
    {
        int numb = rand()%10;
        int alpha = rand()%26;
        if(numb < 4)
        {
            randUpLowLetter = 'a' + alpha;
            question += randUpLowLetter;
        }
        else if(numb<8 && numb>3)
        {
            randUpLowLetter = 'A' + alpha;
            question += randUpLowLetter;
        }
        else if(numb == 8)
        {
            randUpLowLetter = '0';
            question += randUpLowLetter;
        }
        else
        {
            randUpLowLetter = '&';
            question += randUpLowLetter;
        }
    }
    return question;
}

int offsetCount(const string typegen, const string userEntry)
{
    // difference between correct entry and user entry

    int offset = 0; //
    long entrySize = userEntry.size();
    for(int i = 0; i < entrySize; i++)
    {
        offset += abs(typegen[i] - userEntry[i]);
    }
    if(entrySize < 5)
    {
        for (long i = entrySize; i < 5; i++) {
            offset += abs(typegen[i] - char(32));
        }
    }
    return offset;
}

