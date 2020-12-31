//
//  main.cpp
//  HW3 Q4
//
//  Created by Joseph Picchi on 5/9/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//


int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
    int result = 0;
    
    if (n2 <= 0)        // base case
        return 1;
    else if (n1 <= 0)
        return 0;
    
    // every time a match is found, call the function on the rest
    if (a1[0] == a2[0])
        result += countIncludes(a1+1, n1-1, a2+1, n2-1);
    
    // after the count, initiate a count for the rest of the string
    result += countIncludes(a1+1, n1-1, a2, n2);
    
    return result;
}



// Exchange two strings
void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}



void separate(string a[], int n, string separator,
              int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
    //  Every element earlier than position firstNotLess is < separator
    //  Every element from position firstNotLess to firstUnknown-1 is
    //    == separator
    //  Every element from firstUnknown to firstGreater-1 is not known yet
    //  Every element at position firstGreater or later is > separator
    
    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > separator)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < separator)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}



void order(string a[], int n)
{
    if (n <= 1)
        return;
    
    // last to first
    int firstNotLess, firstGreater;
    
    // split the array into groups less than and greater than the separator
    separate(a, n, a[0], firstNotLess, firstGreater);
    
    // order the rest of the array
    order(a, firstNotLess);
    order(a+firstGreater, n-firstGreater);
}
