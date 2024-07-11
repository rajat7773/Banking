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

        //  sa={}; ca={}; la={}; tr={};
    }    

    Customer(const Customer& cust){
        // cout<<"Copy const called "<<cust.userID<<endl;
        // cout<<"Copy const called "<<cust.age<<endl;
        // cout<<"Copy const called "<<cust.email<<endl;
        // cout<<"Copy const called "<<cust.name<<endl;
        // cout<<"Copy const called "<<cust.sa.size()<<endl;

        this->userID=cust.userID;
        this->name=cust.name;
        this->email=cust.email;
        this->phno=cust.phno;
        this->age=cust.age;
        // this->sa=cust.sa; 
        this->ca=cust.ca; this->la=cust.la;
        this->tr=cust.tr;

        for(auto &x: cust.sa){
            this->sa.push_back(x);
        }
        for(auto &x: cust.tr){
            this->tr.push_back(x);
        }
        // cout<<"Size of sa here is"<<this->sa.size()<<endl;
    }

};
 vector<Customer> users;

