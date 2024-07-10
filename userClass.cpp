#include <iostream>
#include <string>
#include "accClass.cpp"
#include "transaction.cpp"
#include <vector>
#pragma once
#include "utilities.cpp"
using namespace std;

class Customer{

    public:
    string name,email,phno,userID;
    int age;

    vector<SavingsAcc> sa;
    vector<CurrentAcc> ca;
    vector<LoanAcc> la;

    vector<Transaction> tr;

    Customer(string name,string email,string phno,int age){
        this->name=name;
        this->email=email;
        this->phno=phno;
        this->age=age;

        this->userID=generateID(name,phno);
    }    

};

vector<Customer> users;




