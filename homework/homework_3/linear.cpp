//
//  main.cpp
//  HW3 Q2
//
//  Created by Joseph Picchi on 5/7/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//



// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.

bool allTrue(const string a[], int n)
{
    if (n <= 0)
        return true;
    
    bool resultOfRest = allTrue(a+1, n-1);
    bool resultOfFirst = somePredicate(a[0]);
    
    return (resultOfRest && resultOfFirst);
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
    if (n <= 0)
        return 0;
    
    int count = countFalse(a+1, n-1);
    
    if (!somePredicate(a[0]))
        count++;
    
    return count;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)
{
    if (n <= 0)
        return -1;      // didn't find anything
    
    // check last to first:
    int everythingBefore = firstFalse(a, n-1);
    
    // if an earlier element returned false, return its subscript
    if (everythingBefore != -1)
        return everythingBefore;
    
    // if nothing was false before, see if this one is false
    if (!somePredicate(a[n-1]))
        return n-1;
    else    // nothing was false
        return -1;
}

// Return the subscript of the least string in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int indexOfLeast(const string a[], int n)
{
    if (n <= 0)     // told to examine no elements
        return -1;
    
    if (n == 1)
        return 0;
    
    // first to last approach
    int indexOfEverythingBefore = indexOfLeast(a, n-1);
    
    // compare min from before to the current element
    if (a[n-1] < a[indexOfEverythingBefore])
        return n-1;
    else
        return indexOfEverythingBefore;
}



// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"

bool includes(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0)        // we ran out of elements in a2 before the elements of a1 were used
        return true;
    
    if (n1 <= 0)        // didn't find everything
        return false;
    
    bool result;
    // first to last approach
    if (a1[0] == a2[0])
        result = includes(a1+1, n1-1, a2+1, n2-1);
    else
        result = includes(a1+1, n1-1, a2, n2);
    
    return result;
}
