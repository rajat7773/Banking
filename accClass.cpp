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
    int accountNumber;
    
    Account(){}
 
    Account(string id, string ty, int amt,string date){
        userID=id;
        type=ty;
        amount=amt;
        dateOfOpening=date;
        accountNumber=rand();
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

    SavingsAcc(const SavingsAcc& sav){
        this->accountNumber=sav.accountNumber;
        this->amount=sav.amount;
        this->atmNum=sav.atmNum;
        this->cvv=sav.cvv;
        this->userID=sav.userID;
        this->dateOfOpening=sav.dateOfOpening;
        this->expDate=sav.expDate; 
        this->type=sav.type;
    }

};


class CurrentAcc : public Account{
    public: 
    CurrentAcc(string id,string ty,int amt,string date): Account(id,ty,amt,date){}

    CurrentAcc(const CurrentAcc& cur){
        this->accountNumber=cur.accountNumber;
        this->amount=cur.amount;
        this->userID=cur.userID;
        this->dateOfOpening=cur.dateOfOpening;
        this->type=cur.type;
    }

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

    LoanAcc(const LoanAcc& loanObj){
        this->accountNumber=loanObj.accountNumber;
        this->amount=loanObj.amount;
        this->loanType=loanObj.loanType;
        this->userID=loanObj.userID;
        this->dateOfOpening=loanObj.dateOfOpening;
        this->interest=loanObj.interest; 
        this->type=loanObj.type;
    }

};



