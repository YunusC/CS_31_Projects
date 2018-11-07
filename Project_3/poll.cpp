//
//  main.cpp
//  Project_3
//
//  Created by Yunus Chang on 10/23/18.
//  Copyright © 2018 Yunus Chang. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

bool isValidUppercaseStateCode(string stateCode);
bool hasProperSyntax(string pollData);
int tallySeats(string pollData, char party, int& seatTally);
string upperCase(string stateCode);
bool checkSpaces(string pollData);
size_t nextPartyCharacter(string pollData,char party);
int calculateSeats(string pollData, size_t nextPartyCharacterPos);
bool onlyTwoDigits(string pollData);
bool noRandomNumbers(string pollData);
bool noRandomCommas(string pollData);
bool noInvalidPartyResults(string pollData);
bool noRandomCharacters(string pollData);
struct testCases
{
    string pollData;
    char party;
    int expectedReturnValue;
    int expectedTallyAnswer;
    int seatTally;
    int returnValue;
};
//struct structure = {pollData,party,expectedReturnvalue,expectedTallyAnswer,seatTally,returnValue}

int main()
{
    testCases testCase[21] = {};
    testCase[0] = {"ca,ny,ma",'x',0,0,-999,0}; // state forecast with no poll results
    testCase[1] = {"ca,ny,ma",'1',2,0,0,0}; // char party is not a letter
    testCase[2] = {"ca,,ny,ma",'x',1,0,0,0}; //two or more consecutive commas
    testCase[3] = {"ca,ny,ma,",'x',1,0,0,0}; //comma at the end
    testCase[4] = {",ca,ny,ma",'x',1,0,0,0}; //comma at beginning
    testCase[5] = {"",'x',0,0,0,0}; //empty string
    testCase[6] = {"banana",'x',1,0,0,0}; //random string
    testCase[7] = {"california",'x',1,0,0,0}; //string that start with state codes
    testCase[8] = {"ca9li",'x',1,0,0,0}; //random party letters with no poll results
    testCase[9] = {"ca111r",'r',1,0,0,0}; //if pollData has more than 2 consecutive digts
    testCase[10] = {"cal",'r',1,0,0,0}; //checks if a single character after statecode with fail
    testCase[11] = {"ca10r17d,ny77r,nv22d,co,wa5r13d17i",'D',0,52,0,0}; //search for 'D' poll Results
    testCase[12] = {"ca10r17d,ny77r,nv22d,co,wa5r13d17i",'R',0,92,0,0}; //search for 'R' poll Results
    testCase[13] = {"ca10r17d,ny77r,nv22d,co,,wa5r13d17i",'R',1,100,100,0}; //faulty pollData in the middle of string
    testCase[14] = {"ct5d,ny9r17d1i",'x',0,0,-999,0}; //checks if seatTally is set to zero
    testCase[15] = {"ca,ny,ma",'x',0,0,-999,0}; //chekcs if seatTally is set to zero
    testCase[16] = {"ct5d,ny9r17+1i",'x',1,-999,-999,0}; //checks if "17+" will give correct return value
    testCase[17] = {"ct5d,ny9r17d1i",'d',0,22,-999,0}; //checks if proper number is given back for given input
    testCase[18] = {"ct5d,ny9r17d1i",'+',2,-999,-999,0}; //checks for return value of 2 if non-character is given
    testCase[19] = {"ct5d,ny9r17+1i",'d',1,-999,-999,0}; //checks if value of seatTally is changed if pollData is determined faulty in the program
    testCase[20] = {"ca+",'d',1,0,0,0}; //checks if non-character values will fail function "hasProperSyntax"
    
    for(int i=0;i < sizeof(testCase)/sizeof(testCase[0]); i++)
    {
        testCase[i].returnValue = 3;
        testCase[i].returnValue = tallySeats(testCase[i].pollData,testCase[i].party,testCase[i].seatTally);
        if(testCase[i].seatTally == testCase[i].expectedTallyAnswer && testCase[i].returnValue == testCase[i].expectedReturnValue)
        {
            cerr << "test case " << i << " passed!" << endl;
        }
        if(testCase[i].seatTally != testCase[i].expectedTallyAnswer)
        {
            cerr << "test case " << i << " failed! Expected seatTally result was " << testCase[i].expectedTallyAnswer << " but Actual result was " << testCase[i].seatTally << endl;
        }
        if(testCase[i].returnValue != testCase[i].expectedReturnValue)
        {
            cerr << "test case " << i << " failed! Expected returnValue result was " << testCase[i].expectedReturnValue << " but Actual result was " << testCase[i].returnValue << endl;
        }
    }
    return 0;
}

//Looks through string 'pollData' and finds the amount of predicted seats won by char 'party' and adds the value to int 'seatTally'
int tallySeats(string pollData, char party, int& seatTally)
{
    int pos = 0;
    int seats = 0;
    if(!isalpha(party))
    {
        return 2;
    }
    while(pos != pollData.size())
    {
        if(hasProperSyntax(pollData))
        {
            pollData = pollData.substr(2, pollData.size());
        }
        else
        {
            return 1;
        }
        size_t nextPartyCharacterPos = nextPartyCharacter(pollData,party);
        size_t nextComma = pollData.find(',');
        if(nextPartyCharacterPos > nextComma)
        {
            pollData = pollData.substr(nextComma+1);
            continue;
        }
        seats = calculateSeats(pollData,nextPartyCharacterPos) + seats;
        if(pollData.find(',') == string::npos)
        {
            break;
        }
        pollData = pollData.substr(nextComma+1);
    }
    seatTally = seats;
    return 0;
}

//Checks if the first two letters in a string given match any of the two letters in the const string 'codes'.
bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

//Checks to see if string 'pollData' has proper syntax
bool hasProperSyntax(string pollData)
{
    string stateCode = upperCase(pollData); //changes the first letters to capital letters
    if(pollData == "")//empty strings count as poll data
        return true;
    if(!isValidUppercaseStateCode(stateCode)) //checks if the first 2 letters are a valid state code
    {
        return false;
    }
    if(!checkSpaces(pollData))//checks for spaces in the pollData string
    {
        return false;
    }
    if(!onlyTwoDigits(pollData))
    {
        return false;
    }
    if(!noRandomNumbers(pollData))
    {
        return false;
    }
    if(!noRandomCommas(pollData))
    {
        return false;
    }
    if(!noInvalidPartyResults(pollData))
    {
        return false;
    }
    if(!noRandomCharacters(pollData))
    {
        return false;
    }
    return true;//passes true if every test is passed
}

//Changes first two letters to upper case letters and cuts off the rest of the string
string upperCase(string pollData)
{
    int counter = 0;
    while(isalpha(pollData[counter]))
    {
        pollData[counter] = toupper(pollData[counter]);
        counter++;
    }
    pollData = pollData.substr(0,2);
    return pollData;
}

//Checks for spaces in the string
bool checkSpaces(string pollData)
{
    for(int i=0;i<pollData.size();i++)
    {
        if(pollData[i] == ' ')
        {
            return false;
        }
    }
    return true;
}

//Finds the next party character in the string
size_t nextPartyCharacter(string pollData,char party)
{
    char lowerParty = tolower(party);
    char upperParty = toupper(party);
    size_t nextPartyCharacter = 0;
    size_t nextPartyLowerCharacter = 0;
    size_t nextPartyUpperCharacter = 0;
    if(pollData.find(lowerParty))
    {
        nextPartyLowerCharacter = pollData.find(lowerParty);
    }
    if(pollData.find(upperParty))
    {
        nextPartyUpperCharacter = pollData.find(upperParty);
    }
    if ((nextPartyLowerCharacter < nextPartyUpperCharacter) && nextPartyLowerCharacter != 0)
    {
        nextPartyCharacter = nextPartyLowerCharacter;
    }
    else if (nextPartyUpperCharacter !=0)
    {
        nextPartyCharacter = nextPartyUpperCharacter;
    }
    return nextPartyCharacter;
}

//Calculates the amount of seats based on the digits before the party character
int calculateSeats(string pollData,size_t nextPartyCharacterPos)
{
    size_t x = 1;
    int seats;
    int firstDigit = 0;
    int secondDigit = 0;
    while(((nextPartyCharacterPos - x) < (nextPartyCharacterPos)) && (isdigit(pollData[nextPartyCharacterPos-x])))
    {
        if (x == 1)
        {
            firstDigit = pollData[nextPartyCharacterPos-x] - 48;
        }
        if (x == 2)
        {
            secondDigit = 10*(pollData[nextPartyCharacterPos-x] - 48);
        }
        x++;
    }
    seats = firstDigit + secondDigit;
    return seats;
}

//Makes sure the max consecutive amount of digits in the string is two
bool onlyTwoDigits(string pollData)
{
    int x = 0;
    for(int i=0;i<pollData.size();i++)
    {
        if(isdigit(pollData[i]))
        {
            x++;
        }
        if(isalpha(pollData[i]))
        {
            x = 0;
        }
        if(x == 3)
        {
            return false;
        }
    }
    return true;
}

//Checks for numbers that do not precede a party
bool noRandomNumbers(string pollData)
{
    for(int i=0;i<pollData.size();i++)
    {
        if(isdigit(pollData[i]))
        {
            while(isdigit(pollData[i]))
            {
                i++;
            }
            if(!isalpha(pollData[i]))
            {
                return false;
            }
        }
    }
    return true;
}

//Checks for random commas at the start, middle, or end of the program (a little redundant because isValidUpperCase indirectly checks for this as well)
bool noRandomCommas(string pollData)
{
    if(pollData[0] == ',')
    {
        return false;
    }
    if(pollData[pollData.size()-1] == ',')
    {
        return false;
    }
    if(pollData[pollData.find(',') + 1] == ',')
    {
        return false;
    }
    return true;
}

//Checks for valid party results (makes sure every letter besides the state codes is preceded by a digit)
bool noInvalidPartyResults(string pollData)
{
    if(pollData.find(',') != string::npos)//if there's a comma left in the string (meaning there are multiple state forecasts left
    {
        for(int i=2;i<pollData.find(',');i++)
        {
            if(isalpha(pollData[i]) == true)
            {
                if(isdigit(pollData[i-1]) == false)
                {
                    return false;
                }
            }
            
        }
    }
    else if(pollData.find(',') == string::npos)//if there's no comma left in the string (meaning this is the last state forecast)
    {
        for(int i=2;i<pollData.size();i++)
        {
            if(isalpha(pollData[i]) == true)
            {
                if(isdigit(pollData[i-1]) == false)
                {
                    return false;
                }
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

//Checks for non alphabet and non digit characters
bool noRandomCharacters(string pollData)
{
    for(int i = 0;i < pollData.size();i++)
    {
        if(!isdigit(pollData[i]) && !isalpha(pollData[i]) && !(pollData[i] == ','))
        {
            return false;
        }
    }
    return true;
}
