//
//  main.cpp
//  Proj4
//
//  Created by Joseph Picchi on 6/1/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <functional> // for hash function
#include <vector>
#include <utility>
#include <list>

using namespace std;

//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>

class Timer
{
public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {
        std::chrono::duration<double, std::milli> diff =
        std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
private:
    std::chrono::high_resolution_clock::time_point m_time;
};

struct BUCKET
{
    BUCKET(const string& nKey, const int& nOffset)
    {
        key = nKey;
        offsets.push_back(nOffset);
    }
    string key;
    vector<int> offsets;
};

// hash table with BST's at each element
class hashTable
{
public:
    void insert(const string& key, const int& offset)
    {
        // hash the key
        unsigned int bucket = hashFunction(key);
        
        // see if any items in the bucket match the key
        BUCKET* insertToThis = keyInBucket(key, bucket);
        
        // if none of the existing items match the key, add a new item
        if (insertToThis == nullptr)
        {
            m_buckets[bucket].push_back(BUCKET(key, offset));
            return;
        }
        // if there is a matching bucket, add the offset to its vector
        else
        {
            insertToThis->offsets.push_back(offset);
        }
    }
    
    BUCKET* search(const string& key)
    {
        // hash the key
        unsigned int bucket = hashFunction(key);
        
        // if the key is not in the table, return false
        if (m_buckets[bucket].empty())
            return nullptr;
        
        return keyInBucket(key, bucket);
    }
    
private:
    unsigned int hashFunction(const string& hashMe) const
    {
        //        unsigned long hashValue = str_hash(hashMe);
        unsigned long hashValue = hash<string>()(hashMe);
        
        // determine the bucket
        unsigned long bucket = hashValue%totalBuckets;
        return static_cast<unsigned int>(bucket);
    }
    BUCKET* keyInBucket(const string& key, const unsigned int& bucket)
    {
        for (auto iter = m_buckets[bucket].begin(); iter != m_buckets[bucket].end(); iter++)
        {
            if ((*iter).key == key)
                return &(*iter);
        }
        
        return nullptr;
    }
    
    static const int totalBuckets = 100017; // total number of buckets
    list<BUCKET> m_buckets[totalBuckets];
};

bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
    if (!inf.get(cmd))
    {
        cmd = 'x';  // signals end of file
        return true;
    }
    
    char ch;
    switch (cmd)
    {
        case 'A':
            return getInt(inf, length) && inf.get(ch) && ch == ':';
        case 'C':
            return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
        case '\r':
        case '\n':
            return true;
    }
    return false;
}

void writeCopyInstruction(const BUCKET* item, int& index, const string& oldFileString, const string& newFileString, string& addInstruction, ostream& fdiff)
{
    int optimalOffset = -1;
    int tempMatchLength = 0;
    int matchLength = -1;
    int indexNew = index;
    
    // find the offset that gives the greatest match length, based on all the offsets that match the key
    for (int i = 0; i < item->offsets.size() && i < 1000; i++)
    {
        int indexOld = item->offsets[i];
        
        // find how long this offset matches for
        while (oldFileString[indexOld] == newFileString[indexNew] && indexOld < oldFileString.size() && indexNew < newFileString.size())
        {
            tempMatchLength++;
            indexOld++;
            indexNew++;
        }
        
        if (tempMatchLength > matchLength)
        {
            matchLength = tempMatchLength;
            optimalOffset = item->offsets[i];
        }
        
        tempMatchLength = 0;
        indexNew = index;
    }
    
    // apply anything that needs to be added
    if (!addInstruction.empty())
    {
        // write an instruction to diff to add the current char
        fdiff << "A" << addInstruction.size() << ":" << addInstruction;
        addInstruction = "";
    }
    
    // write copy instruction to diff to copy L bytes from offset F from source file
    fdiff << "C" << matchLength << "," << optimalOffset;
    
    // continue the loop at offset j = j + L in new file's string
    index += matchLength-1;
}


void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
    const int sequenceSize1 = 8;
    const int sequenceSize2 = 16;
    
    // STEP 1
    char c;
    string oldFileString;
    string newFileString;
    
    // read contents of fold into a string
    while (fold.get(c))
        oldFileString += c;
    
    // read contents of fnew into a string
    while (fnew.get(c))
        newFileString += c;
    
    // STEP 2
    
    // create a hash table that maps char sequence to offsets
    hashTable smallTable;   // table for N = sequenceSize1
    hashTable largeTable;   // table for N = sequenceSize2
    
    // For all consecutive N-character sequences in the old file's string, insert that N-character sequence and the offset F where it was found in the old file's string, into a table
    int offset = 0;
    int index = 0;
    string charSequence1;
    string charSequence2;
    while (offset < oldFileString.size())
    {
        index = offset;
        
        // record the offset of first entered char
        int recordOffset = offset;
        
        // copy all necessary chars into charSequence1
        int i = 0;
        for (; index < oldFileString.size() && i < sequenceSize1; i++)
        {
            charSequence1 += oldFileString[index];
            charSequence2 += oldFileString[index];
            index++;
        }
        // copy any more into the larger charSequence2
        for (; index < oldFileString.size() && i < sequenceSize2; i++)
        {
            charSequence2 += oldFileString[index];
            index++;
        }
        
        // enter the sequences into the hash tables
        smallTable.insert(charSequence1, recordOffset);
        largeTable.insert(charSequence2, recordOffset);
        charSequence1 = "";
        charSequence2 = "";
        
        offset++;
    }
    
    // STEP 3
    
    // used to prevent comparisons of strings of size < N
    bool recordSequence2 = true;
    bool recordSequence1 = true;
    
    string addInstruction;
    // process fnew's string
    for (int j = 0; j < newFileString.size(); j++)
    {
        // STEP 3A
        
        // get the sequence from fnew
        string newSequence1;
        string newSequence2;
        if (j+sequenceSize2 >= newFileString.size())
        {
            if (j+sequenceSize1 >= newFileString.size())
            {
                if (recordSequence1)
                {
                    newSequence1 = newFileString.substr(j, newFileString.size()-j);
                    recordSequence1 = false;
                }
                if (recordSequence2)
                {
                    newSequence2 = newFileString.substr(j, newFileString.size()-j);
                    recordSequence2 = false;
                }
            }
            else
            {
                if (recordSequence2)
                {
                    newSequence2 = newFileString.substr(j, newFileString.size()-j);
                    recordSequence2 = false;
                }
                newSequence1 = newFileString.substr(j, sequenceSize1);
            }
        }
        else
        {
            newSequence1 = newFileString.substr(j, sequenceSize1);
            newSequence2 = newFileString.substr(j, sequenceSize2);
        }
        
        // look up the sequence in the largeTable first
        BUCKET* item = largeTable.search(newSequence2);
        
        // STEP 3B
        
        // if we found the sequence in the largeTable
        if (item != nullptr)
            writeCopyInstruction(item, j, oldFileString, newFileString, addInstruction, fdiff);
        
        // STEP 3C
        
        // if you don't find the current sequence
        if (item == nullptr)
        {
            // try the same procedure with the smallTable
            item = smallTable.search(newSequence1);
            
            // if we found the item in our smallTable, write a copy instruction
            if (item != nullptr)
                writeCopyInstruction(item, j, oldFileString, newFileString, addInstruction, fdiff);
            
            // if we didn't find the item in any table, add current char to the add instruction
            else if (item == nullptr)
                addInstruction += newFileString[j];
        }
    }
    // add anything else that needs to be added
    if (!addInstruction.empty())
    {
        // write an instruction to diff to add the current char
        fdiff << "A" << addInstruction.size() << ":" << addInstruction;
        addInstruction = "";
    }
}

bool applyDiff(istream& fold, istream& fdiff, ostream& fnew)
{
    // write the contents of old file to a string
    char c;
    string oldFileString;
    while (fold.get(c))
        oldFileString += c;
    
    char cmd = '\0';
    int length = -1;
    int offset = -1;
    
    // must start with a command
    while (getCommand(fdiff, cmd, length, offset))
    {
        // finished with the file
        if (cmd == 'x')
            return true;
        
        if (cmd == 'A')
        {
            // add the characters to the new file
            for (int i = 0; i < length; i++)
            {
                char c;
                if (!fdiff.get(c))
                    return false;
                fnew << c;
            }
        }
        
        if (cmd == 'C')
        {
            // check if there are enough characters to copy in old file
            if (offset + length > oldFileString.size())
                return false;
            
            // copy characters to the new file
            for (int i = offset; i < offset + length; i++)
                fnew << oldFileString[i];
        }
    }
    
    // didn't get a command when we expected one
    return false;
}

bool runtest(string oldName, string newName, string diffName, string newName2)
{
    cerr << "========================= runtest 1" << endl;
    if (diffName == oldName  ||  diffName == newName  ||
        newName2 == oldName  ||  newName2 == diffName  ||
        newName2 == newName)
    {
        cerr << "Files used for output must have names distinct from other files" << endl;
        return false;
    }
    ifstream oldFile(oldName, ios::binary);
    if (!oldFile)
    {
        cerr << "Cannot open " << oldName << endl;
        return false;
    }
    ifstream newFile(newName, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName << endl;
        return false;
    }
    ofstream diffFile(diffName, ios::binary);
    if (!diffFile)
    {
        cerr << "Cannot create " << diffName << endl;
        return false;
    }
    
    Timer t;
    
    createDiff(oldFile, newFile, diffFile);
    
    cerr << "took createDiff " << t.elapsed()/1000 << " seconds" << endl;
    
    diffFile.close();
    
    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the file
    ifstream diffFile2(diffName, ios::binary);
    if (!diffFile2)
    {
        cerr << "Cannot read the " << diffName << " that was just created!" << endl;
        return false;
    }
    ofstream newFile2(newName2, ios::binary);
    if (!newFile2)
    {
        cerr << "Cannot create " << newName2 << endl;
        return false;
    }
    t.start();
    assert(applyDiff(oldFile, diffFile2, newFile2));
    cerr << "took applyDiff " << t.elapsed()/1000 << " seconds" << endl;
    newFile2.close();
    
    newFile.clear();
    newFile.seekg(0);
    ifstream newFile3(newName2, ios::binary);
    if (!newFile)
    {
        cerr << "Cannot open " << newName2 << endl;
        return false;
    }
    if ( ! equal(istreambuf_iterator<char>(newFile), istreambuf_iterator<char>(),
                 istreambuf_iterator<char>(newFile3), istreambuf_iterator<char>()))
    {
        
        cerr << newName2 << " is not identical to " << newName
        << "; test FAILED" << endl;
        return false;
    }
    
    cerr << "===========================" << endl;
    
    return true;
}

void runtest2(string oldtext, string newtext)
{
    cerr << "=========================" << "runtest 2" << endl;
    istringstream oldFile(oldtext);
    istringstream newFile(newtext);
    ostringstream diffFile;
    Timer t;
    createDiff(oldFile, newFile, diffFile);
    cerr << "took createDiff " << t.elapsed()/1000 << " seconds" << endl;
    string result = diffFile.str();
    cerr << "The diff file length is " << result.size() << endl;
    //    cerr << result << endl;
    
    oldFile.clear();   // clear the end of file condition
    oldFile.seekg(0);  // reset back to beginning of the stream
    istringstream diffFile2(result);
    ostringstream newFile2;
    t.start();
    assert(applyDiff(oldFile, diffFile2, newFile2));
    cerr << "took applyDiff " << t.elapsed()/1000 << " seconds" << endl;
    assert(newtext == newFile2.str());
    cerr << "New file length is " << newtext.size() << endl;
    cerr << "=======================" << endl;
}


int main()
{
    string oldFileName = "/Users/josephpicchi/Desktop/proj4Files/p4test/strange1.txt";
    string newFileName = "/Users/josephpicchi/Desktop/proj4Files/p4test/strange2.txt";
    string diffFileName = "/Users/josephpicchi/Desktop/proj4Files/diff.txt";
    string createdFileName = "/Users/josephpicchi/Desktop/proj4Files/dummy.txt";
    
    
    // copy contents of files into strings
    string oldString, newString;
    char ch;
    ifstream oldFile(oldFileName);
    ifstream newFile(newFileName);
    if (!oldFile || !newFile)
        cerr << "can't open file";
    while (oldFile.get(ch))
        oldString += ch;
    while (newFile.get(ch))
        newString += ch;
    
    // perform analysis on the strings
    runtest2(oldString, newString);
    
    // see if we can convert the files
    assert(runtest(oldFileName, newFileName, diffFileName, createdFileName));
    
    cerr << "All tests passed" << endl;
}



// FILE DIRECTORY:
//  "/Users/josephpicchi/Desktop/proj4Files/fileName.txt"
