//
//  main.cpp
//  Project_2
//
//  Created by Yunus Chang on 10/10/18.
//  Copyright © 2018 Yunus Chang. All rights reserved.
//

#include <iostream>
using namespace std;

int main()
{
    //declaration of useful constants
    const int LUX_CAR_RATE = 61;
    const int REG_CAR_RATE = 33;
    const double ONE_MILE_REG_RATE = .27;
    const double THREE_MILE_REG_RATE = .21;
    const double THREE_MILE_WINTER_RATE = .27;
    const double FOUR_MILE_RATE = .19;
    
    cout << "Odometer at start: ";
    int odometerStart;
    cin >> odometerStart;
    
    cout << "Odometer at end: ";
    int odometerEnd;
    cin >> odometerEnd;
    
    //calculations for mileCharge later on
    int miles = odometerEnd - odometerStart;
    int firstHundred = 0;
    int nextThreeHundred = 0;
    int overFourHundred = 0;
    if (miles >= 100)
    {
        firstHundred = 100;
    }
    else
    {
        firstHundred = miles;
    }
    if (firstHundred == 100)
    {
        nextThreeHundred = miles - 100;
    }
    if(nextThreeHundred > 300)
    {
        nextThreeHundred = 300;
        overFourHundred = miles - 400;
    }
    
    cout << "Rental Days: ";
    int rentalDays;
    cin >> rentalDays;
    cin.ignore(1000, '\n');
    
    cout << "Customer Name: ";
    string personName;
    getline(cin, personName);

    cout << "Luxury car? (y/n): ";
    char luxCar;
    cin >> luxCar;
   
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    int month;
    cin >> month;
    
    int baseCharge = 0;
    if (luxCar == 'y')
    {
        baseCharge = rentalDays * LUX_CAR_RATE;
    }
    if (luxCar == 'n')
    {
        baseCharge = rentalDays * REG_CAR_RATE;
    }
    
    double mileCharge;
    mileCharge = firstHundred * ONE_MILE_REG_RATE;
    if (month == 12 || month < 4)
    {
        mileCharge = nextThreeHundred*THREE_MILE_WINTER_RATE + mileCharge;
    }
    else
    {
        mileCharge = nextThreeHundred*THREE_MILE_REG_RATE + mileCharge;
    }
    mileCharge = overFourHundred*FOUR_MILE_RATE + mileCharge;
    
    double finalPayment;
    finalPayment = mileCharge + baseCharge;
    
    cout << "---" << "\n";
    
    if(odometerStart < 0)
    {
        cout << "The starting odometer reading must be nonnegative." << endl;
        return 0;
    }
    
    if(odometerStart > odometerEnd)
    {
        cout << "The final odometer reading must be at least as large as the starting reading." << endl;
        return 0;
    }
    
    if(rentalDays < 1)
    {
        cout << "The number of rental days must be positive." << endl;
        return 0;
    }
    
    if(personName == "")
    {
        cout << "You must enter a customer name." << endl;
        return 0;
    }
    
    if(luxCar != 'y' && luxCar != 'n')
    {
        cout << "You must enter y or n." << endl;
        return 0;
    }
    
    if(month < 1 || month > 12)
    {
        cout << "The month number must be in the range 1 through 12." << endl;
        return 0;
    }
    
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "The rental charge for " << personName << " is $" << finalPayment;
    return 0;

}
