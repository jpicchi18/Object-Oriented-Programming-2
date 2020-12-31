//
//  testSequence.cpp
//  HW 1: Q 1-3
//
//  Created by Joseph Picchi on 4/11/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

//INCOMPLETE TEST PROGRAM:

//#include "Sequence.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main()
//{
//    Sequence s;
//
//    //test the insert and empty functions
//    assert(s.empty());
//    assert(s.insert(0, "yee") == 0);
//    assert(s.insert(1, "nope") == 1);
//    assert(s.insert(2, "hello") == 2);
//    assert(s.size() == 3);
//    assert(s.insert(4, "hello") == -1);
//    assert(s.insert(2, "wassup") == 2);
//    assert(s.size() == 4);
//
//    s.dump();
//
//    //test the insert function w/ no args:
//    Sequence s2;
//    assert(s2.empty());
//    assert(s2.insert("yo") == 0);
//    assert(s2.size() == 1);
//    assert(s2.insert("no") == 0);
//    assert(s2.size() == 2);
//    assert(s2.insert("pope") == 1);
//    assert(s2.size() == 3);
//    assert(s2.insert("zoo") == 3);
//
//    //make sure it returns -1 if the array is already full
//    Sequence s3;
//    for (int i = 0; i <= DEFAULT_MAX_ITEMS; i++)
//    {
//        s3.insert("hello");
//    }
//    assert(s3.insert("hello") == -1);
//
//    //test the erase function:
//    Sequence s4;
//    for (int i = 0; i < DEFAULT_MAX_ITEMS ; i++)
//    {
//        assert(s4.insert(i, "s4") == i);
//    }
//
//    assert(s4.size() == 250);
//    assert(s4.erase(5) == true);
//    assert(s4.size() == DEFAULT_MAX_ITEMS - 1);
//
//    //test the remove function:
//    Sequence s5;
//    for (int i = 0; i < 5; i++)
//    {
//        assert(s5.insert(i, "hello") == i);
//    }
//
//    s5.dump();
//
//    assert(s5.size() == 5);
//    assert(s5.remove("hi") == 0);
//    assert(s5.size() == 5);
//    assert(s5.remove("hello") == 5);
//    assert(s5.size() == 0);
//    assert(s5.insert("zoo") == 0);
//    assert(s5.insert("yack") == 0);
//    assert(s5.insert("wherewolf") == 0);
//    assert(s5.size() == 3);
//    assert(s5.remove("yack") == 1);
//    assert(s5.size() == 2);
//    assert(s5.insert("yee") == 1);
//    assert(s5.remove("wherewolf") == 1);
//    assert(s5.remove("wherewolf") == 0);
//    assert(s5.remove("yee") == 1);
//    assert(s5.remove("zoo") == 1);
//    assert(s5.size() == 0);
//
//    //testing the get function
//    ItemType value;
//    assert(s5.insert("zoo") == 0);
//    assert(s5.size() == 1);
//    assert(s5.get(0, value) == true);
//    assert(value == "zoo");
//    assert(s5.insert("yee") == 0);
//    assert(s5.insert("zz") == 2);
//    assert(s5.size() == 3);
//    assert(s5.get(1, value) == true);
//    assert(value == "zoo");
//    assert(s5.get(4, value) == false);
//    assert(value == "zoo");
//
//    //testing the set function
//    assert(value == "zoo");
//    Sequence s6;
//    assert(s6.insert("zoo") == 0);
//    assert(s6.insert("yellow") == 0);
//    assert(s6.insert("marshmellow") == 0);
//    assert(s6.size() == 3);
//    assert(s6.set(3, value) == false);
//    assert(value == "zoo");
//    assert(s6.set(1, value) == true);
//    assert(value == "zoo");
//    assert(s6.get(1, value) == true);
//    assert(value == "zoo");
//
//    //test the find function
//    Sequence s7;
//    assert(s7.insert("alpha") == 0);
//    assert(s7.insert("beta") == 1);
//    assert(s7.insert("cat") == 2);
//    assert(s7.size() == 3);
//    assert(s7.find("alpha") == 0);
//    assert(s7.find("beta") == 1);
//    assert(s7.find("cat") == 2);
//    assert(s7.find("dog") == -1);
//
//    //test the swap function
//    Sequence s8;
//    Sequence s9;
//    assert(s8.insert("alpha") == 0);
//    assert(s8.insert("beta") == 1);
//    assert(s8.insert("cat") == 2);
//    assert(s9.insert("apple") == 0);
//    assert(s9.insert("banana") == 1);
//    assert(s9.size() == 2 && s8.size() == 3);
//
//    s8.swap(s9);
//    assert(s8.size() == 2 && s9.size() == 3);
//    assert(s8.find("apple") == 0 && s8.find("banana") == 1);
//    assert(s9.find("alpha") == 0 && s9.find("beta") == 1 && s9.find("cat") == 2);
//
//    Sequence s10;
//    Sequence s11;
//    assert(s10.insert("alpha") == 0);
//    assert(s10.insert("beta") == 1);
//    assert(s10.insert("cat") == 2);
//    assert(s11.insert("apple") == 0);
//    assert(s11.insert("banana") == 1);
//    assert(s11.size() == 2 && s10.size() == 3);
//
//    s11.swap(s10);
//    assert(s10.size() == 2 && s11.size() == 3);
//    assert(s10.find("apple") == 0 && s10.find("banana") == 1);
//    assert(s11.find("alpha") == 0 && s11.find("beta") == 1 && s11.find("cat") == 2);
//    cout << "Passed all tests" << endl;

//}

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);
    assert(s.size() == 1  &&  s.find(42) == 0);
    cout << "Passed all tests" << endl;
}

//#include "Sequence.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//int main()
//{
//    Sequence s;
//    assert(s.empty());
//    assert(s.find("laobing") == -1);
//    assert(s.insert("laobing") == 0);
//    assert(s.size() == 1  &&  s.find("laobing") == 0);
//    cout << "Passed all tests" << endl;
//}
