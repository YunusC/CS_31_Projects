//
//  main.cpp
//  Project_4
//
//  Created by Yunus Chang on 10/31/18.
//  Copyright © 2018 Yunus Chang. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);
void print(string a[], int n, string name);

int main()
{
    string original[5] = {"0", "00", "000", "0000", "00000"};
    string original2[2] = {"0", "00"};
    
    string appendToAllTest[5] = {"0", "00", "000", "0000", "00000"};
    assert((appendToAll(appendToAllTest, 3, "!!!")) == 3);
    print(appendToAllTest, 5, "appendToAllTest");
    
    assert((lookup(original, 5, "00")) == 1);
    assert((positionOfMax(original, 5)) == 4);
    
    string rotateLeftTest[5] = {"0", "00", "000", "0000", "00000"};
    assert((rotateLeft(rotateLeftTest, 5, 2)) == 2);
    print(rotateLeftTest, 5, "rotateLeftTest");
    
    assert((countRuns(original, 5)) == 5);
    
    string flipTest[5] = {"0", "00", "000", "0000", "00000"};
    assert((flip(flipTest, 5)) == 5);
    print(flipTest, 5, "flipTest");
    
    assert((differ(original, 5, original2, 2)) == 2);
    assert((subsequence(original, 5, original2, 2)) == 0);
    assert((lookupAny(original, 5, original2, 2)) == 0);
    
    string divideTest[] = {"0000", "00000", "0", "00", "000"};
    assert((divide(divideTest, 5, "000")) == 2);
    print(divideTest, 5, "divideTest");
   
    
    cout << "pass" << endl;
    
    string hh[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
    assert(lookup(hh, 7, "eleni") == 5);
    assert(lookup(hh, 7, "ed") == 2);
    assert(lookup(hh, 2, "ed") == -1);
    assert(positionOfMax(hh, 7) == 3);
    
    string g[4] = { "greg", "gavin", "fiona", "kevin" };
    assert(differ(hh, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "greg?" && g[3] == "kevin?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "fiona?" && g[3] == "gavin?");
    
    string eeee[4] = { "ed", "xavier", "", "eleni" };
    assert(subsequence(hh, 7, eeee, 4) == 2);
    
    string d[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
    assert(countRuns(d, 5) == 2);
    
    string ff[3] = { "fiona", "ed", "john" };
    assert(lookupAny(hh, 7, ff, 3) == 2);
    assert(flip(ff, 3) == 3 && ff[0] == "john" && ff[2] == "fiona");
    
    assert(divide(hh, 7, "fiona") == 3);
    
    cout << "All tests succeeded" << endl;
}

int appendToAll(string a[], int n, string value)
{
    if(n < 0)
    {
        return -1;
    }
    for(int i=0;i<n;i++)
    {
        a[i] = a[i] + value;
    }
    return n;
}

int lookup(const string a[], int n, string target)
{
    if(n < 0)
    {
        return -1;
    }
    for(int i=0;i<n;i++)
    {
        if(a[i] == target)
        {
            return i;
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n)
{
    if(n <= 0)
    {
        return -1;
    }
    int maxPos = 0;
    for(int i=0;i<n;i++)
    {
        if(a[i] > a[maxPos])
        {
            maxPos = i;
        }
    }
    return maxPos;
}



int rotateLeft(string a[], int n, int pos)
{
    if(n <= 0 || pos >= n)
    {
        return -1;
    }
    if(pos == (n-1))
    {
        return pos;
    }
    string sub;
    string target = a[pos];
    for(int i = pos;i < (n-1); i++)
    {
        a[i] = a[i+1];
    }
    a[n-1] = target;
    return pos;
}

int countRuns(const string a[], int n)
{
    if(n < 0)
    {
        return -1;
    }
    if(n == 0)
    {
        return 0;
    }
    int counter = 1;
    for(int i = 1;i < n; i++)
    {
        if(a[i] != a[i-1])
        {
            counter++;
        }
    }
    return counter;
}

int flip(string a[], int n)
{
    if(n < 0)
    {
        return -1;
    }
    string sub;
    for(int i=0;i < (n/2);i++)
    {
        sub = a[i];
        a[i] = a[(n-1)-i];
        a[(n-1)-i] = sub;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0)
    {
        return -1;
    }
    int i = 0;
    while(i < n1 && i < n2)
    {
        if(a1[i] != a2[i])
        {
            return i;
        }
        i++;
    }
    if(n1 < n2)
    {
        return n1;
    }
    else
    {
        return n2;
    }
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0)
    {
        return -1;
    }
    if(n2 == 0)
    {
        return 0;
    }
    int pos = 0;
    for(int i=0;i<n1;i++)
    {
        if(a1[i] == a2[0])
        {
            pos = i;
            int j = 0;
            while(a1[i] == a2[j])
            {
                if(j == (n2 - 1))
                {
                    return pos;
                }
                i++;
                j++;
            }
        }
    }
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0)
    {
        return -1;
    }
    for(int i = 0;i < n1;i++)
    {
        for(int j = 0;j < n2;j++)
        {
            if(a1[i] == a2[j])
            {
                return i;
            }
        }
    }
    return -1;
}

int divide(string a[], int n, string divider)
{
    if(n < 0)
    {
        return -1;
    }
    string sub;
    for(int k = 0;k < n;k++)
    {
    for(int i = 0;i < n;i++)
    {
        if(a[i] >= divider)
        {
            sub = a[i];
            for(int j = i;j < (n-1);j++)
            {
                a[j] = a[j+1];
            }
            a[n-1] = sub;
        }
    }
    }
    for(int i = 0;i < n;i++)
    {
        if(a[i] >= divider)
        {
            return i;
        }
    }
    return n;
}

/*
int divideTest(vector<string> a, string divider, int firstPos, int arraySize)
{
    for(int i = 0;i < firstPos;i++)
    {
        if(a[i].size() >= )
        {
            return -1;
        }
    }
    for(int i = firstPos;i < arraySize;i++)
    {
        if(a[i] < divider)
        {
            return -1;
        }
    }
    return 0;
}
 */

void print(string a[], int n, string name)
{
    cout << "Array values for " << name << " are {" << a[0];;
    for(int i = 1;i < n;i++)
    {
        cout << ", " << a[i];
    }
    cout << "}" << endl;
}

/*
 struct originalString
 {
 vector<string> string;
 int size;
 };
 struct appendToAllTest
 {
 string value;
 int number;
 vector<string> expectedAppendToAll;
 vector<string> actualAppendToAll;
 int expectedReturnValue;
 int actualReturnValue;
 };
 struct lookUpTest
 {
 string target;
 int expectedReturnValue;
 int actualReturnValue;
 };
 struct positionOfMaxTest
 {
 int expectedReturnValue;
 int actualReturnValue;
 };
 struct rotateLeftTest
 {
 int pos;
 vector<string> expectedRotateLeft;
 vector<string> actualRotateLeft;
 int expectedReturnValue;
 int actualReturnValue;
 };
 struct countRunsTest
 {
 int expectedReturnValue;
 int actualReturnValue;
 };
 struct flipTest
 {
 int pos;
 vector<string> expectedFlip;
 vector<string> actualFlip;
 int expectedReturnValue;
 int actualReturnValue;
 };
 struct divideTest
 {
 string divider;
 vector<string> actualDivide;
 int expectedReturnValue;
 int actualReturnValue;
 };
 struct specialString
 {
 vector<string> string1;
 int string1size;
 vector<string> string2;
 int string2size;
 };
 struct differTest
 {
 int expectedReturnValue;
 int actualReturnValue;
 };
 struct subsequenceTest
 {
 int expectedReturnValue;
 int actualReturnValue;
 };
 struct lookUpAnyTest
 {
 int expectedReturnValue;
 int actualReturnValue;
 };
 
 int main()
 {
 int x = 3;
 originalString originalCase[x];
 originalCase[0] = {{"0", "00", "000", "0000", "00000"}, 5};
 originalCase[1] = {{"dianne", "eddie", "coolbeans", "fiona", "ed", "xavier", "john", "john", "betty", "betty", "sonic", ""}, 12};
 originalCase[2] = {{}, 0};
 
 appendToAllTest appendToAllCase[x];
 appendToAllCase[0] = {"!", 3, {"0!", "00!", "000!", "0000", "00000"}, {}, 3, 0};
 appendToAllCase[1] = {"!*&", 6, {"dianne!*&", "eddie!*&", "coolbeans!*&", "fiona!*&", "ed!*&", "xavier!*&", "john", "john", "betty", "betty", "sonic", ""}, {}, 6, 0};
 appendToAllCase[2] = {"123", 0, {}, {}, 0, 0};
 
 lookUpTest lookUpCase[x];
 lookUpCase[0] = {"000", 2, 0};
 lookUpCase[1] = {"john", 6, 0};
 lookUpCase[2] = {"john", -1, 0};
 
 positionOfMaxTest positionOfMaxCase[x];
 positionOfMaxCase[0] = {4, 200};
 positionOfMaxCase[1] = {2, 200};
 positionOfMaxCase[2] = {-1, 200};
 
 rotateLeftTest rotateLeftCase[x];
 rotateLeftCase[0] = {2, {"0", "00", "0000", "00000", "000"}, {}, 2, 0};
 rotateLeftCase[1] = {2, {"dianne", "eddie", "fiona", "ed", "xavier", "john", "john", "betty", "betty", "sonic", "", "coolbeans"}, {}, 2, 0};
 rotateLeftCase[2] = {0, {}, {}, -1, 22};
 
 countRunsTest countRunsCase[x];
 countRunsCase[0] = {5, -1};
 countRunsCase[1] = {10, -1};
 countRunsCase[2] = {1, -1};
 
 flipTest flipCase[x];
 flipCase[0] = {3, {"000", "00", "0", "0000", "00000"}, {}, 3, -1};
 flipCase[1] = {8, {"john", "john", "xavier", "ed", "fiona", "coolbeans", "eddie", "dianne", "betty", "betty", "sonic", ""}, {}, 8, -1};
 flipCase[2] = {0, {}, {}, 0, -1};
 
 struct divideTest divideCase[x];
 divideCase[0] = {"12", {}, 1, 0};
 divideCase[1] = {"12345", {}, 4, 0};
 divideCase[2] = {"12345", {}, 0, 0};
 
 specialString specialCase[x];
 specialCase[0] = {{"0", "00", "000", "0000", "00000"}, 5, {"0", "00"}, 2};
 specialCase[1] = {{"dianne", "eddie", "coolbeans", "fiona", "ed", "xavier", "john", "john", "betty", "betty", "sonic", ""}, 12, {"john", "john"}, 2};
 specialCase[2] = {{}, 0, {"0", "00"}, 2};
 
 differTest differCase[x];
 differCase[0] = {2, -1};
 differCase[1] = {0, -1};
 differCase[2] = {0, -1};
 
 subsequenceTest subsequenceCase[x];
 subsequenceCase[0] = {0, -1};
 subsequenceCase[1] = {6, -1};
 subsequenceCase[2] = {-1, 7};
 
 lookUpAnyTest lookUpAnyCase[x];
 lookUpAnyCase[0] = {0, -1};
 lookUpAnyCase[1] = {6, -1};
 lookUpAnyCase[2] = {-1, 7};
 
 for(int i = 0;i < x;i++)
 {
 int pass = 0;
 int divideTest1 = -1;
 appendToAllCase[i].actualAppendToAll = originalCase[i].string;
 rotateLeftCase[i].actualRotateLeft = originalCase[i].string;
 flipCase[i].actualFlip = originalCase[i].string;
 divideCase[i].actualDivide = originalCase[i].string;
 
 appendToAllCase[i].actualReturnValue = appendToAll(appendToAllCase[i].actualAppendToAll, appendToAllCase[i].number, appendToAllCase[i].value);
 lookUpCase[i].actualReturnValue = lookup(originalCase[i].string, originalCase[i].size, lookUpCase[i].target);
 positionOfMaxCase[i].actualReturnValue = positionOfMax(originalCase[i].string, originalCase[i].size);
 rotateLeftCase[i].actualReturnValue = rotateLeft(rotateLeftCase[i].actualRotateLeft, originalCase[i].size, rotateLeftCase[i].pos);
 countRunsCase[i].actualReturnValue = countRuns(originalCase[i].string, originalCase[i].size);
 flipCase[i].actualReturnValue = flip(flipCase[i].actualFlip, flipCase[i].pos);
 differCase[i].actualReturnValue = differ(specialCase[i].string1, specialCase[i].string1size, specialCase[i].string2, specialCase[i].string2size);
 subsequenceCase[i].actualReturnValue = subsequence(specialCase[i].string1, specialCase[i].string1size, specialCase[i].string2, specialCase[i].string2size);
 lookUpAnyCase[i].actualReturnValue = lookupAny(specialCase[i].string1, specialCase[i].string1size, specialCase[i].string2, specialCase[i].string2size);
 divideCase[i].actualReturnValue = divide(divideCase[i].actualDivide, originalCase[i].size, divideCase[i].divider);
 
 
 if(appendToAllCase[i].actualReturnValue != appendToAllCase[i].expectedReturnValue)
 {
 cerr << "appendToAll Test Case " << i << " expected return value was " << appendToAllCase[i].expectedReturnValue << " but actual return value was " << appendToAllCase[i].actualReturnValue << endl;
 pass = -1;
 }
 if(lookUpCase[i].actualReturnValue != lookUpCase[i].expectedReturnValue)
 {
 cerr << "lookUp Test Case " << i << " expected return value was " << lookUpCase[i].expectedReturnValue << " but actual return value was " << lookUpCase[i].actualReturnValue << endl;
 pass = -1;
 }
 if(positionOfMaxCase[i].actualReturnValue != positionOfMaxCase[i].expectedReturnValue)
 {
 cerr << "positionOfMax Test Case " << i << " expected return value was " << positionOfMaxCase[i].expectedReturnValue << " but actual return value was " << positionOfMaxCase[i].actualReturnValue << endl;
 pass = -1;
 }
 if(rotateLeftCase[i].actualReturnValue != rotateLeftCase[i].expectedReturnValue)
 {
 cerr << "rotateLeft Test Case " << i << " expected return value was " << rotateLeftCase[i].expectedReturnValue << " but actual return value was " << rotateLeftCase[i].actualReturnValue << endl;
 pass = -1;
 }
 if(countRunsCase[i].actualReturnValue != countRunsCase[i].expectedReturnValue)
 {
 cerr << "countRuns Test Case " << i << " expected return value was " << countRunsCase[i].expectedReturnValue << " but actual return value was " << countRunsCase[i].actualReturnValue << endl;
 pass = -1;
 }
 if(flipCase[i].actualReturnValue != flipCase[i].expectedReturnValue)
 {
 cerr << "flip Test Case " << i << " expected return value was " << flipCase[i].expectedReturnValue << " but actual return value was " << flipCase[i].actualReturnValue << endl;
 pass = -1;
 }
 if(differCase[i].actualReturnValue != differCase[i].expectedReturnValue)
 {
 cerr << "differ Test Case " << i << " expected return value was " << differCase[i].expectedReturnValue << " but actual return value was " << differCase[i].actualReturnValue << endl;
 pass = -1;
 }
 if(subsequenceCase[i].actualReturnValue != subsequenceCase[i].expectedReturnValue)
 {
 cerr << "subsequence Test Case " << i << " expected return value was " << subsequenceCase[i].expectedReturnValue << " but actual return value was " << subsequenceCase[i].actualReturnValue << endl;
 pass = -1;
 }
 if(lookUpAnyCase[i].actualReturnValue != lookUpAnyCase[i].expectedReturnValue)
 {
 cerr << "lookUpAny Test Case " << i << " expected return value was " << lookUpAnyCase[i].expectedReturnValue << " but actual return value was " << lookUpAnyCase[i].actualReturnValue << endl;
 pass = -1;
 }
 if(divideCase[i].actualReturnValue != divideCase[i].expectedReturnValue)
 {
 cerr << "divide Test Case " << i << " expected return value was " << divideCase[i].expectedReturnValue << " but actual return value was " << divideCase[i].actualReturnValue << endl;
 pass = -1;
 }
 int appendPass = 0;
 int rotatePass = 0;
 int flipPass = 0;
 divideTest1 = divideTest(divideCase[i].actualDivide, divideCase[i].divider, divideCase[i].actualReturnValue, originalCase[i].size);
 for(int y = 0;y < originalCase[i].size;y++)
 {
 if(appendToAllCase[i].actualAppendToAll[y] != appendToAllCase[i].expectedAppendToAll[y])
 appendPass = -1;
 if(rotateLeftCase[i].actualRotateLeft[y] != rotateLeftCase[i].expectedRotateLeft[y])
 rotatePass = -1;
 if(flipCase[i].actualFlip[y] != flipCase[i].expectedFlip[y])
 flipPass = -1;
 }
 if(appendPass == -1)
 {
 cerr << "actualAppendToAll Test Case " << i << " expeceted array values were " << endl;
 for(int z = 0;z < originalCase[i].size;z++)
 {
 cerr << appendToAllCase[i].expectedAppendToAll[z] << ", ";
 }
 cerr << endl;
 cerr << "but actual array values were " << endl;
 for(int z = 0;z < originalCase[i].size;z++)
 {
 cerr << appendToAllCase[i].actualAppendToAll[z] << ", ";
 }
 cerr << endl;
 }
 if(rotatePass == -1)
 {
 cerr << "rotateLeft Test Case " << i << " expeceted array values were " << endl;
 for(int z = 0;z < originalCase[i].size;z++)
 {
 cerr << rotateLeftCase[i].expectedRotateLeft[z] << ", ";
 }
 cerr << endl;
 cerr << "but actual array values were " << endl;
 for(int z = 0;z < originalCase[i].size;z++)
 {
 cerr << rotateLeftCase[i].actualRotateLeft[z] << ", ";
 }
 cerr << endl;
 }
 if(flipPass == -1)
 {
 cerr << "flip Test Case " << i << " expeceted array values were " << endl;
 for(int z = 0;z < originalCase[i].size;z++)
 {
 cerr << flipCase[i].expectedFlip[z] << ", ";
 }
 cerr << endl;
 cerr << "but actual array values were " << endl;
 for(int z = 0;z < originalCase[i].size;z++)
 {
 cerr << flipCase[i].actualFlip[z] << ", ";
 }
 cerr << endl;
 }
 if(divideTest1 == -1)
 {
 cerr << "Actual array values are " << endl;
 for(int z = 0;z < originalCase[i].size;z++)
 {
 cerr << divideCase[i].actualDivide[z] << ", ";
 }
 cerr << endl;
 }
 if(pass == -1)
 {
 cerr << "You failed test case " << i << endl;
 }
 else
 {
 cerr << "You passed test case " << i << endl;
 }
 }
 
 
 }
 */
