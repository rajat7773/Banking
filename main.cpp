#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "userClass.cpp"
#include "accClass.cpp"
#include "transaction.cpp"
using namespace std;

string today;

int main(){
    
    while(1){
        cout<<"Welcome to Inito Bank"<<endl;
        cout<<"Enter today's date in ddmmyyyy"<<endl;
        cin>>today;

        string id;
        cout<<"Enter your User ID"<<endl;
        cout<<"If you are a new user type -1"<<endl;
        cin>>id;

        Customer user("","","",0);

        if(id=="-1"){
            string name,email,phno;
            int age;

            cout<<"Enter your Name"<<endl;
            cin.ignore();
            getline(cin,name);

            cout<<"Enter your age"<<endl;
            cin>>age;
            cout<<"Enter your email"<<endl;
            cin>>email;
            cout<<"Enter your Phone Number"<<endl;
            cin>>phno;

            Customer u(name,email,phno,age);
            users.push_back(u);
            cout<<" Welcome New User | User Id :"<<u.userID<<endl;
            cout<<"Save the User Id for future"<<endl;
            id=u.userID;

            user=u;
        }

        else{
            for(auto &u : users){
                if(u.userID==id){ user=u; break;}
            }
            cout<<" Welcome Existing User | User Id :"<<id<<endl;
        } 

        bool end=false;

        while(1){
            cout<<"Please choose the operation you want to perform"<<endl<<endl;
            cout<<"Type 1 to open an Account"<<endl;
            cout<<"Type 2 to view details of your accounts"<<endl;
            cout<<"Type 3 to make a deposit"<<endl;
            cout<<"Type 4 to make a withdrawal or repay loan"<<endl;
            cout<<"Type 5 for viewing your transactions"<<endl;
            cout<<"All other entries end your session"<<endl;

            int oper;
            cin>>oper;

            switch(oper){
                
                //Opening Account
                case 1 : {
                    cout<<"Enter your age"<<endl;
                    int age; 
                    cin>>age;

                    cout<<"Please select the type account you want to open"<<endl<<"Type s for Savings, c for Current and l for loan account"<<endl;
                    string ty; cin>>ty;
                    
                    cout<<"Enter amount"<<endl;
                    int amount; cin>>amount;

                    if(ty=="s"){
                        if(amount<10000) cout<<"Minimum amount is 10,000"<<endl;
                        else {
                            SavingsAcc savObj(id,ty,amount,today);
                            savObj.amount=amount;
                            user.sa.push_back(savObj);
                            cout<<"Savings account created with Acc No. "<<savObj.accountNumber<<endl;

                            Transaction transacObj(savObj.accountNumber,"s",amount,"Acc open",today);
                            user.tr.push_back(transacObj);
                        }

                    }
                    else if(ty=="c"){
                        if(amount<100000) cout<<"Minimum amount is 1,00,000"<<endl;
                        else if(age<18) cout<<"Minimum age required is 18 years"<<endl;
                        else {
                            CurrentAcc curObj(id,ty,amount,today);
                            curObj.amount=amount;
                            user.ca.push_back(curObj);
                            cout<<"Current account created with Acc No. "<<curObj.accountNumber<<endl;

                            Transaction transacObj(curObj.accountNumber,"c",amount,"Acc open",today);
                            user.tr.push_back(transacObj);
                        }

                    }
                    else if(ty=="l"){

                        int presentAmt=0;
                        for(auto acc:user.sa) presentAmt+=acc.amount;
                        for(auto acc:user.ca) presentAmt+=acc.amount;
                        
                        if(user.sa.size()==0 && user.ca.size()==0) cout<<"You should have a Savings or Current a/c prior to loan"<<endl;
                        else if(age<25) cout<<"Minimum age required is 25 years"<<endl;
                        else if(amount>0.4*presentAmt) cout<<"Loan above 40 percent deposits not granted"<<endl;
                        else if(amount<500000) cout<<"Minimum loan amount is 5,00,000"<<endl;
                        else{
                            string loanType;
                            cout<<"Enter the initial alphabet for Home/Car/Personal/Business loan in smallcase"<<endl;
                            cin>>loanType;

                            LoanAcc loanObj(id,ty,amount,today,loanType);
                            loanObj.amount=amount;
                            user.la.push_back(loanObj);
                            
                            cout<<"Loan account created with Acc No. "<<loanObj.accountNumber<<endl;

                            Transaction transacObj(loanObj.accountNumber,"l",amount,"Acc open",today);
                            user.tr.push_back(transacObj);
                        }
                    }
                    else cout<<"Invalid Entry"<<endl;

                    break;
                }

                //Viewing details
                case 2 : {
                    for(auto &usr : users){
                        if(usr.userID==id){
                            cout<<usr.name<<" "<<usr.age<<" "<<usr.phno<<" "<<usr.email<<endl;
                            break;
                        }
                    }

                    for(auto &acc: user.sa){
                        cout<<acc.accountNumber<<" "<<"Rs "<<acc.amount<<" "<<acc.type<<" "<<acc.dateOfOpening<<endl;
                        cout<<"ATM detaisl"<<acc.atmNum<<" "<<acc.expDate<<" "<<acc.cvv<<endl;
                    }
                    for(auto &acc: user.ca){
                        cout<<acc.accountNumber<<" "<<"Rs "<<acc.amount<<" "<<acc.type<<" "<<acc.dateOfOpening<<endl; 
                    }

                    for(auto &acc: user.la){
                        cout<<acc.accountNumber<<" "<<"Rs "<<acc.amount<<" "<<acc.type<<" "<<acc.dateOfOpening<<" loan-type "<<acc.loanType<<endl;
                    }
                    
                    break;
                }

                //Deposit
                case 3 : {
                    int accountNumber,amount;
                    string accType;
                    
                    cout<<"Enter Acc Number"<<endl;  
                    cin>>accountNumber;
                    cout<<"Enter amount to be deposited"<<endl;
                    cin>>amount;
                    cout<<"Type of account-> s/c/l"<<endl;
                    cin>>accType;

                    if(accType=="s"){

                        string prevDate=user.tr.back().date;
                        int months=numberOfMonths(prevDate,today);
                        
                        for(auto &acc:user.sa){
                            if(acc.accountNumber==accountNumber){ 
                                acc.amount=(acc.amount*(1+(0.06/12*months)))+amount; 

                                cout<<"Money Deposited"<<endl;

                                Transaction transacObj(accountNumber,accType,amount,"dep",today);
                                user.tr.push_back(transacObj);
                        
                                break;
                            }
                        }
                    }
                    else if(accType=="c"){
                        int originalAmt=amount;
                        amount=500<(0.005*amount) ? (amount-500) : (0.995*amount);

                        for(auto &acc:user.ca){
                            if(acc.accountNumber==accountNumber){
                                acc.amount+=amount; 

                                cout<<"Money Deposited"<<endl;

                                Transaction transacObj(accountNumber,accType,originalAmt,"dep",today);
                                user.tr.push_back(transacObj);
                                break;
                            }
                        }
                    }

                    //Loan Repayment
                    else if(accType=="l"){
                        string prevDate=user.tr.back().date;
                        int months=numberOfMonths(prevDate,today);

                        for(auto &acc:user.la){
                            if(acc.accountNumber==accountNumber){
                                if(amount>0.1*acc.amount){ cout<<"Cannot repay more that 10% of loan amount"<<endl; break;}
                                acc.amount-=amount;
                                acc.amount=acc.amount*pow((1+(acc.interest/200)),(months/6));

                                cout<<"Loan installment deposited"<<endl;

                                Transaction transacObj(accountNumber,accType,amount,"Loan Repay",today);
                                user.tr.push_back(transacObj);
                                break;
                            }
                        }
                    }

                    else cout<<"Invalid decision"<<endl;
                    break;
                }
                
                //Withdrawal
                case 4 : {

                    int accountNumber,amount;
                    string accType;
                    
                    cout<<"Enter Acc Number"<<endl;  
                    cin>>accountNumber;
                    cout<<"Enter amount to be withdrawn"<<endl;
                    cin>>amount;
                    cout<<"Type of account-> s/c"<<endl;
                    cin>>accType;
                    
                    if(accType=="s"){
                        //check today's transactions
                        int todayAmt=0;
                        for(int i=user.tr.size()-1;i>=0;i--){
                            if(user.tr[i].transacType=="withd" || user.tr[i].transacType=="atm") todayAmt+=user.tr[i].amount;
                            if(user.tr[i].date!=today) break;
                        }

                        if(todayAmt+amount>50000){
                            cout<<"Maximum limit for the day (Rs 50000) reached"<<endl;
                            continue;
                        }

                        cout<<"Enter d for direct withdrawal and atm for ATM withdrawal"<<endl;
                        string input;
                        cin>>input;

                        if(input=="atm") {
                            if(amount>20000) cout<<"You cannot withdraw amount more than 20,000 using ATM"<<endl; 
                            else{
                                //5 times in a month
                                int ct=0;
                                string curMonth;
                                curMonth+=today[2]+today[3];

                                for(int i=user.tr.size()-1;i>=0;i--){
                                    if(user.tr[i].transacType=="atm") ct++;

                                    string month;
                                    month+=user.tr[i].date[2]+user.tr[i].date[3];
                                    if(curMonth!=month) break;
                                }

                                if(ct>=5){
                                    amount+=500;
                                    cout<<"500 extra charged for exceeding 5 times a month ATM withdrawal"<<endl;
                                } 
                                
                                for(auto &acc:user.sa){
                                    if(acc.accountNumber==accountNumber){ 
                                        if(amount>acc.amount){ cout<<"Insufficient Balance"<<endl; break;}
                                        
                                        acc.amount-=amount;
                                        
                                        cout<<"Amount withdrawn"<<endl;

                                        Transaction transacObj(accountNumber,accType,amount,"atm",today);
                                        user.tr.push_back(transacObj);
                                        break;
                                    }
                                }
                                
                            }

                        }
                        else if(input=="d"){
                            for(auto &acc:user.sa){
                                if(acc.accountNumber==accountNumber){ 
                                    if(amount>acc.amount){ cout<<"Insufficient Balance"<<endl; break;}
                                    acc.amount-=amount;
                                    
                                    cout<<"Amount withdrawn"<<endl;

                                    Transaction transacObj(accountNumber,accType,amount,"withd",today);
                                    user.tr.push_back(transacObj);
                                    break;
                                }
                            }
                        }

                    }
                    else if(accType=="c"){
                        for(auto &acc:user.ca){
                            if(acc.accountNumber==accountNumber){ 
                                if(amount>acc.amount){ cout<<"Insufficient Balance"<<endl; break;}
                                
                                amount=500<(0.005*amount) ? (amount+500) : (1.005*amount);
                                acc.amount-=amount;

                                cout<<"Amount withdrawn"<<endl;
                                Transaction transacObj(accountNumber,accType,amount,"withd",today);
                                user.tr.push_back(transacObj);
                                break;
                            }
                        }

                        
                    }

                    else cout<<"Invalid decision"<<endl;
                    break;
                }
                
                //View Transactions
                case 5 : {
                    for(auto &t : user.tr){
                        cout<<t.accountNumber<<" "<<t.acctype<<" "<<t.amount<<" "<<t.transacType<<" "<<t.date<<endl;
                    }
                    break;
                }

                default : end=true;
            }

            if(end) break;
        }
    }



    return 0;
}