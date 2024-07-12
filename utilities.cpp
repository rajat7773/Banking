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

    long long id=0;
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

//string to integer
int sti(string str){
    int num = 0;
    for(char c : str){
        int x = c-'0';
        num *= 10;
        num += x;
    }
    return num;
}


//dates ddmmyyyy
int numberOfMonths(string from,string  to){
    int y1,y2,m1,m2;
    string a="",b="",c="",d="";
    a+=from[2]; a+=from[3];
    b+=to[2]; b+=to[3];
    c+=from[4]; c+=from[5]; c+=from[6]; c+=from[7];
    d+=to[4]; d+=to[5]; d+=to[6]; d+=to[7];
    
    m1=sti(a); m2=sti(b);
    y1=sti(c); y2=sti(d);

    return 12*(y2-y1)+(m2-m1);
}

bool validDate(string s){
    if(s.size()!=8) return 0;
    
    string a="",b="",c="";
    a+=s[0]; a+=s[1];
    b+=s[2]; b+=s[3];
    c+=s[4]; c+=s[5]; c+=s[6]; c+=s[7];
    
    int d,m,y;
    d=sti(a); m=sti(b);
    y=sti(c);

    return (d>0 && d<32)&&(m>0 && m<13)&&(y>2000 && y<2040);
}

bool validPh(string s){
    if(s.size()!=10) return 0;
    return (s[0]-'0')>=6;
}