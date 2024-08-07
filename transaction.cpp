#include <iostream>
#pragma once
#include <string>
using namespace std;

class Transaction{
    public:
    int amount,accountNumber;
    string date,acctype;
    string transacType;  //dep //withd //Loan Repay //atm //Acc open
    
    Transaction(int accountNumber,string acctype,int amount,string transacType,string date){
        this->accountNumber=accountNumber;
        this->acctype=acctype;
        this->amount=amount;
        this->transacType=transacType;
        this->date=date;
    }

    Transaction(const Transaction& trans){
        this->accountNumber=trans.accountNumber;
        this->amount=trans.amount;
        this->date=trans.date;
        this->acctype=trans.acctype;
        this->transacType=trans.transacType;
    }
};
