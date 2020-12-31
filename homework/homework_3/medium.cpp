//
//  main.cpp
//  HW3 Q1
//
//  Created by Joseph Picchi on 5/3/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//



// base class
class Medium
{
public:
    Medium(string id) : m_id(id) {}
    virtual string connect() const = 0; // returns method of connection (tweet, call, email, etc)
    string id() const { return m_id; }
    virtual string transmit(string msg) const
    {
        return ("text: " + msg);
    }
    virtual ~Medium() { cout << m_id << "." << endl; }
    
private:
    string m_id;    // cannot be empty
    
};


class TwitterAccount : public Medium
{
public:
    TwitterAccount(string id) : Medium(id) {}
    virtual string connect() const { return "Tweet"; }
    virtual ~TwitterAccount() { cout << "Destroying the Twitter account "; }
};


class Phone : public Medium
{
public:
    Phone(string id, CallType msgType) : Medium(id), m_messageType(msgType) {}
    virtual string connect() const { return "Call"; }
    virtual string transmit(string msg) const
    {
        string type;
        if (m_messageType == VOICE)
            type = "voice: ";
        else if (m_messageType == TEXT)
            type = "text: ";
        
        return (type + msg);
    }
    virtual ~Phone() { cout << "Destroying the Phone "; }
    
private:
    CallType m_messageType;
};


class EmailAccount : public Medium
{
public:
    EmailAccount(string id) : Medium(id) {}
    virtual string connect() const { return "Email"; }
    virtual ~EmailAccount() { cout << "Destroying the email account "; }
};
