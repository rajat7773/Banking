#include <iostream>
#include <string>
#pragma once
using namespace std;

string generateID(string &name,string &phno){

    int values[26]={0};
    values[0]=1;
    for(int i=1;i<26;i++){
        values[i]=(values[i-1]*2)+i+1;
    }

    int id=0;
    for(int i=0;i<name.size();i++){
        int index=name[i]-'A';
        id+=values[index];
    }

    string userID=to_string(id);
    userID+="."+phno;
    return userID;
}

string generateCVV(){
    string cvv;
    for(int i=0;i<3;i++){
        cvv+=to_string(rand()%10);
    }
    return cvv;
}


//dates ddmmyyyy
int numberOfMonths(string from,string  to){
    int y1,y2,m1,m2;
    string a,b,c,d;
    a+=from[2]+from[3];
    b+=to[2]+to[3];
    c+=from[4]+from[5]+from[6]+from[7];
    d+=to[4]+to[5]+to[6]+to[7];

    m1=stoi(a); m2=stoi(b);
    y1=stoi(c); y2=stoi(d);

    return 12*(y2-y1)+(m2-m1);
}


//  for(auto &usr: users){
//         if(usr.userID==id){
//             user=usr;
//         }
//     }