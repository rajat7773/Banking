#include <iostream>
#include <string>
#pragma once
using namespace std;
#include "utilities.cpp"

long long prevATM=1e16;

class Account{ 
    public:
    string userID,dateOfOpening;
    int amount=0;
    string type;
    int accountNumber=rand();


    Account(string id, string ty, int amt,string date){
        userID=id;
        type=ty;
        amount=amt;
        dateOfOpening=date;
    }

};

class SavingsAcc : public Account{
    public:

    int atmNum=prevATM;  
    string cvv,expDate="20122030"; 

    SavingsAcc(string id,string ty,int amt,string date) : Account(id,ty,amt,date){
        prevATM++;
        cvv=generateCVV();
    }

};


class CurrentAcc : public Account{
    public: 
    CurrentAcc(string id,string ty,int amt,string date): Account(id,ty,amt,date){}

};


class LoanAcc : public Account{
    public:
    string loanType;
    int interest;

    LoanAcc(string id,string ty,int amt,string date,string ln) : Account(id,ty,amt,date){
        // setAcc(id,ty,amt,date);
        loanType=ln;
        if(ln=="h") interest=7;
        else if(ln=="c") interest=8;
        else if(ln=="p") interest=12;
        else if(ln=="b") interest=15;
    }

};



