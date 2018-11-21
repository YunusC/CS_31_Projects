//
//  main.cpp
//  Project_5
//
//  Created by Yunus Chang on 11/8/18.
//  Copyright © 2018 Yunus Chang. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <cstring>
#include <cctype>

using namespace std;
const int MAX_WORD_LENGTH = 20;

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int seperation[], int nPatterns);
bool checkAlphaAndNull(char word1[MAX_WORD_LENGTH+1], char word2[MAX_WORD_LENGTH+1]);
void checkRepetition(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int seperation[], int nPatterns);
void toLower(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int nPatterns);
int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns);
int formatDocument(const char document[250], char newDocument[][250]);
int rateDocument(char newDocument[][250], int numOfWords, const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int seperation[], int nPatterns);
bool notRated(int rated[], int number, int nPatterns);
void resetArray(int rated[], int nPatterns);

int main()
{
    
    const int TEST1_NRULES = 4;
    char test11w1[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have"
    };
    char test11w2[TEST1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad"
    };
    int test11dist[TEST1_NRULES] = {
        1,           3,          0,           12
    };
    const int test2n = 10;
    char test2w1[test2n][MAX_WORD_LENGTH+1] = {"quick", "brown", "fox", "Brown", "FOX", "F^ox", "banana phon", "banana", "super", "woman"};
    char test2w2[test2n][MAX_WORD_LENGTH+1] = {"brown", "quick", "fox", "quick", "fox", "banana", "bad"," ", "man", "quick"};
    //checks for repeats, capital letters, special characters, multiple words in a pattern, and empty words
    int test2dist[test2n] = {3, 2, 4, 1, 1, 5, 3, 5, 9, 10};
    
    assert(makeProper(test2w1, test2w2, test2dist, test2n) == 4);
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.", test11w1, test11w2, test11dist, TEST1_NRULES) == 2);
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                test11w1, test11w2, test11dist, TEST1_NRULES) == 2);
    assert(rate("**** 2018 ****",
                test11w1, test11w2, test11dist, TEST1_NRULES) == 0);
    assert(rate("  That plot: NEFARIOUS!",
                test11w1, test11w2, test11dist, TEST1_NRULES) == 1);
    assert(rate("deranged deranged robot deranged robot robot",
                test11w1, test11w2, test11dist, TEST1_NRULES) == 1);
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                test11w1, test11w2, test11dist, TEST1_NRULES) == 0);
     assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
     test11w1, test11w2, test11dist, TEST1_NRULES) == 0);
    
    
    const int TEST6_NCRITERIA = 4;
    int test6dist[TEST6_NCRITERIA] = {
        12,               4,              1,               13
    };
    char test6w1[TEST6_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "half-witted", "nefari#$us", "have"
    };
    char test6w2[TEST6_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad", "guy",    "plot",      "mad"
    };
    
    assert(makeProper(test6w1,test6w2,test6dist,TEST6_NCRITERIA) == 2);
    
    const int TEST7_NCRITERIA = 4;
    int test7dist[TEST7_NCRITERIA] = {
        123455,               4,              1,               13
    };
    char test7w1[TEST7_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "asdfghjklmnbvcxzqwer", "nefari#$us", "have"
    };
    char test7w2[TEST7_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "guy",    "plot",      "chicken"
    };
    
    assert(makeProper(test7w1,test7w2,test7dist,TEST7_NCRITERIA) == 3);
    
    const int TEST1_NCRITERIA = 5;
    int test1dist[TEST1_NCRITERIA] = {
        2,           4,          1,           13 ,  3
    };
    char test1w1[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "have", "deranged"
    };
    char test1w2[TEST1_NCRITERIA][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "mad", "deranged"
    };
    
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.", test1w1, test1w2, test1dist, TEST1_NCRITERIA) == 2);//tests regular funciton
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",  test1w1, test1w2, test1dist, TEST1_NCRITERIA) == 2);//test wiht larger spaces
    assert(rate("**** 2014 ****" ,  test1w1, test1w2, test1dist, TEST1_NCRITERIA) == 0);//no alphabets
    assert(rate("  That plot: NEFARIOUS!" ,  test1w1, test1w2, test1dist, TEST1_NCRITERIA) == 1);//combination of special characters and charactesrs
    assert(rate("deranged deranged robot deranged robot robot" ,  test1w1, test1w2, test1dist,TEST1_NCRITERIA) == 2);//repeated words
    assert(rate("Two mad scientists suffer from deranged-robot fever." ,  test1w1, test1w2, test1dist, TEST1_NCRITERIA) == 0);
    assert(rate("" ,  test1w1, test1w2, test1dist, TEST1_NCRITERIA) == 0);//empty string
    assert(rate("deranged deranged deranged deranged deranged" ,  test1w1, test1w2, test1dist, TEST1_NCRITERIA) == 1);//repeated words
    assert(rate("The deranged robot." ,  test1w1, test1w2, test1dist, TEST1_NCRITERIA) == 1);
    assert(rate("that is a Very Nefarious:: plot!!" ,  test1w1, test1w2, test1dist,TEST1_NCRITERIA) == 1);
    assert(rate("The mad UCLA       $scientist unle@asheD a deranged robot." ,  test1w1, test1w2, test1dist,TEST1_NCRITERIA) == 2);//combination of letters and special characters
    char ashwinsFirstTestCaseArray1[6][MAX_WORD_LENGTH + 1] = {
        "eccentric",       "scientific", "hi", "baloney", "kpop", "esketit"
    };
    char ashwinsFirstTestCaseArray2[6][MAX_WORD_LENGTH + 1] = {
        "scientist", "robot",    "plot",      "mad", "sad","unfortunately"
    };
    int ashwinsFirsttestCaseSeparations[6] = {
        1,           3,          0,           7, 9, 3
    };
    assert (rate("  Honestly I just think that robot robot eccentric robot scientific exnobalbe baloney  hi().87 kpop plot esketit mad scientist sad, unfortunately",
                 ashwinsFirstTestCaseArray1, ashwinsFirstTestCaseArray2, ashwinsFirsttestCaseSeparations, 6)==4);
    
    cout << "All tests succeeded" << endl;
    return 0;
}

int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int seperation[], int nPatterns)
{
    int properPatterns = 0;
    if(nPatterns <= 0)
    {
        return 0;
    }
    int* properElements = new int[nPatterns];//creates dynamically allocated array
    resetArray(properElements, nPatterns);//sets every element in the array to -1
    int x = 0;
    toLower(word1,word2,nPatterns);
    checkRepetition(word1,word2,seperation,nPatterns);
    for(int i=0;i < nPatterns;i++)//cycles through each pattern
    {
        if(checkAlphaAndNull(word1[i],word2[i]) && seperation[i] >= 0)
        {
            properElements[x] = i;
            x++;
            properPatterns++;
        }
    }
    for(int i = 0;i < properPatterns;i++)//takes valid strings and copies them over the original patterns starting from 0
    {
        strcpy(word1[i], word1[properElements[i]]);
        strcpy(word2[i], word2[properElements[i]]);
        seperation[i] = seperation[properElements[i]];
    }
    resetArray(properElements, nPatterns);
    delete[] properElements;//deletes dynamically allocated array
    return properPatterns;
}

void checkRepetition(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int seperation[], int nPatterns)//checks for repetition of word sets
{
    for(int i = 0;i < nPatterns;i++)
    {
        for(int j = 0;j < nPatterns;j++)//checks for repeats and deletes the values of repeated sets of data
        {
            if(((0 == strcmp(word1[i],word2[i])) && (0 == strcmp(word1[j],word2[j]))) || ((0 == strcmp(word1[i],word2[j]) && (0 == strcmp(word1[j],word2[i])))))
            {
                if(seperation[i] < seperation[j])
                {
                    strcpy(word1[j],"");
                    strcpy(word2[j],"");
                    seperation[j] = -1;
                }
                else if(seperation[j] < seperation[i])
                {
                    strcpy(word1[i],"");
                    strcpy(word2[i],"");
                    seperation[i] = -1;
                }
            }
        }
    }
}

void toLower(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int nPatterns)//changes every alphabet in a string to lower case
{
    for(int i = 0;i < nPatterns;i++)//cycles through every C-string
    {
        for(int j = 0;j < MAX_WORD_LENGTH;j++)//changes every character in given C-string to lower case
        {
            word1[i][j] = tolower(word1[i][j]);
            word2[i][j] = tolower(word2[i][j]);
        }
    }
}

bool checkAlphaAndNull(char word1[MAX_WORD_LENGTH+1], char word2[MAX_WORD_LENGTH+1])//checks if every character in string is an alphabet and not an empty string
{
    if((0 == strcmp(word1,"")) || (0 == strcmp(word2, "")))//returns false if there is an empty string
    {
        return false;
    }
    for(int i = 0;i < strlen(word1);i++)//returns false if every character isn't a letter
    {
        if(!isalpha(word1[i]))
        {
            return false;
        }
    }
    for(int i = 0;i < strlen(word2);i++)//returns false if every character isn't a letter
    {
        if(!isalpha(word2[i]))
        {
            return false;
        }
    }
    return true;
}

int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns)
{
    int rate = 0;
    if(nPatterns <= 0)
    {
        return 0;
    }
    char newDocument[250][250] = {{}};//declares a new 2-D array
    int numOfWords = 0;
    numOfWords = formatDocument(document,newDocument);
    rate = rateDocument(newDocument, numOfWords, word1, word2, separation, nPatterns);
    return rate;
}

int formatDocument(const char document[250], char newDocument[][250])//takes every word in c string and organizes it in a 2-d array
{
    int x = 0;
    int y = 0;
    for(int i = 0;i < strlen(document);i++)
    {
        if(isalpha(document[i]))//sets words into array
        {
            newDocument[x][y] = tolower(document[i]);
            y++;
            continue;
        }
        if(isspace(document[i]))//shifts to next row if a space is encountered
        {
            while(isspace(document[i]))
            {
                i++;
                if(isalpha(document[i]))
                {
                    break;
                }
            }
            i--;
            newDocument[x][y] = '\0';
            x++;
            y = 0;
            continue;
        }
    }
    return (x+1);
}

int rateDocument(char newDocument[][250], int numOfWords, const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int seperation[], int nPatterns)
{
    int rate = 0;
    int* rated = new int[nPatterns];//dynamic memory allocation of rated array
    resetArray(rated, nPatterns);
    for(int i = 0;i < numOfWords;i++)//cycles through every word
    {
        for(int j = 0;j < nPatterns;j++)//compares words to words found in the patterns given
        {
            if(0 == strcmp(newDocument[i], word1[j]) && notRated(rated, j, nPatterns))//if there is a match and the pattern hasn't already been counted
            {
                //cerr << word1[j] << endl;
                for(int k = 0;k <= seperation[j];k++)
                {
                    if(k+i+1 >= numOfWords)
                        break;
                    if(0 == strcmp(newDocument[k+i+1], word2[j]))
                    {
                        //cerr << word2[j] << endl;
                        rated[rate] = j;
                        rate++;
                        break;
                    }
                }
            }
            if(0 == strcmp(newDocument[i], word2[j]) && notRated(rated, j, nPatterns))//if there is a match and the pattern hasn't already been counted
            {
                //cerr << word2[j] << endl;
                for(int k = 0;k <= seperation[j];k++)
                {
                    if(k+i+1 >= numOfWords)
                        break;
                    if(0 == strcmp(newDocument[k+i+1], word1[j]))
                    {
                        //cerr << word1[j] << endl;
                        rated[rate] = j;
                        rate++;
                        break;
                    }
                }
            }
        }
    }
    resetArray(rated, nPatterns);
    delete[] rated;
    return rate;
}

bool notRated(int rated[], int number, int nPatterns)
{
    for(int i = 0;i < nPatterns;i++)
    {
        if(rated[i] == number)
        {
            return false;
        }
    }
    return true;
}

void resetArray(int rated[], int nPatterns)
{
    for(int i = 0;i < nPatterns;i++)
    {
        rated[i] = -1;
    }
}

