//
//  testScoreList.cpp
//  HW 1: Q 1-3
//
//  Created by Joseph Picchi on 4/14/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#include "ScoreList.h"
#include "Sequence.h"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    //test the add function
    ScoreList s1;
    assert(s1.add(10.23) == true);
    assert(s1.size() == 1);
    assert(s1.add(101) == false);
    assert(s1.size() == 1);
    assert(s1.add(99.999) == true);
    assert(s1.size() == 2);
    for (int i = 0; i < DEFAULT_MAX_ITEMS - 2; i++)
    {
        assert(s1.add(23) == true);
    }
    assert(s1.size() == DEFAULT_MAX_ITEMS);
    assert(s1.add(23) == false);
    
    
    //test the remove function
    ScoreList s2;
    assert(s2.add(10) == true);
    assert(s2.add(20) == true);
    assert(s2.add(10) == true);
    assert(s2.size() == 3);
    assert(s2.remove(10) == true);
    assert(s2.size() == 2);
    assert(s2.remove(30) == false);
    assert(s2.size() == 2);
    assert(s2.remove(10) == true);
    assert(s2.size() == 1);
    
    
    //test the minimum function
    ScoreList s3;
    assert(s3.minimum() == NO_SCORE);
    assert(s3.add(10) == true);
    assert(s3.add(20) == true);
    assert(s3.add(40) == true);
    assert(s3.add(30) == true);
    assert(s3.minimum() == 10);
    assert(s3.remove(10) == true);
    assert(s3.minimum() == 20);
    
    
    //test the maximum function
    ScoreList s4;
    assert(s4.maximum() == NO_SCORE);
    assert(s4.add(1) == true);
    assert(s4.maximum() == 1);
    assert(s4.add(21) == true);
    assert(s4.maximum() == 21);
    assert(s4.add(20) == true);
    assert(s4.maximum() == 21);
    assert(s4.add(21) == true);
    assert(s4.maximum() == 21);
    
    
    
    //testing the assignment operator
    ScoreList s5;
    ScoreList s6;
    assert(s5.add(13) == true);
    assert(s5.add(12) == true);
    s6 = s5;
    assert(s6.maximum() == 13);
    assert(s6.minimum() == 12);
    
    cout << "all tests passed!" << endl;
    
    return 0;
}
