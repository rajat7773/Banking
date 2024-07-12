#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "userClass.cpp"
#include "accClass.cpp"
#include "transaction.cpp"
using namespace std;

string today;

Customer getCustomer(string id){
for(auto &u: users){
    if(u.userID==id) return u;
}

return Customer("","","",0);
}

void addSavingsAcc(string id, SavingsAcc savingsAcc) {
    for(auto &u: users){
        if(u.userID==id) {
            u.sa.push_back(savingsAcc);
            break;
        }
    }
}


void addCurrentAcc(string id, CurrentAcc curAcc) {
    for(auto &u: users){
        if(u.userID==id) {
            u.ca.push_back(curAcc);
            break;
        }
    }
}

void addLoanAcc(string id, LoanAcc loanAcc) {
    for(auto &u: users){
        if(u.userID==id) {
            u.la.push_back(loanAcc);
            break;
        }
    }
}

void addTransaction(string id, Transaction transObj) {
    for(auto &u: users){
        if(u.userID==id) {
            u.tr.push_back(transObj);
            break;
        }
    }
}

bool depSavAcc(string id,int accountNumber,int amount,int months,string accType){

    for(auto &u: users){
        if(u.userID==id) {
            for(auto &acc: u.sa){
                if(acc.accountNumber==accountNumber){ 
                    acc.amount=(acc.amount*(1+((0.06/12)*months)))+amount; 

                    Transaction transacObj(accountNumber,accType,amount,"dep",today);
                    addTransaction(id,transacObj);
                    return true;
                }
            }
            return false;
        }
    }
}

bool depCurAcc(string id,int accountNumber,int amount,string accType){

    for(auto &u: users){
        if(u.userID==id) {
            for(auto &acc: u.ca){
                if(acc.accountNumber==accountNumber){
                    int originalAmt=amount;
                    amount=500<(0.005*amount) ? (amount-500) : (0.995*amount);
                    acc.amount+=amount; 

                    Transaction transacObj(accountNumber,accType,originalAmt,"dep",today);
                    addTransaction(id,transacObj);
                    return true;
                }
            }
            return false;
        }
    }
}

bool depLoanAcc(string id,int accountNumber,int amount,int months,string accType){

    for(auto &u: users){
        if(u.userID==id) {
            for(auto &acc: u.la){
                if(acc.accountNumber==accountNumber){ 
                    if(amount>0.1*acc.amount){ cout<<"Cannot repay more that 10% of loan amount"<<endl; break;}
                    acc.amount-=amount;
                    acc.amount=acc.amount*double(pow(double((1+(double)(acc.interest)/(double)200)),(months/6)));

                    Transaction transacObj(accountNumber,accType,amount,"Loan Repay",today);
                    addTransaction(id,transacObj);
                    return true;
                }
            }
            return false;
        }
    }
}

bool withSavDirAcc(string id,int accountNumber,int amount,string accType){

    for(auto &u: users){
        if(u.userID==id) {
            for(auto &acc: u.sa){
                if(acc.accountNumber==accountNumber){ 
                    if(amount>acc.amount){ cout<<"Insufficient Balance"<<endl; break;}
                    acc.amount-=amount;

                    Transaction transacObj(accountNumber,accType,amount,"withd",today);
                    addTransaction(id,transacObj);
                    return true;
                }
            }
            return false;
        }
    }

}

bool withSavATMAcc(string id,int accountNumber,int amount,string accType){

    for(auto &u: users){
        if(u.userID==id) {
            for(auto &acc: u.sa){
                if(acc.accountNumber==accountNumber){ 
                    if(amount>acc.amount){ cout<<"Insufficient Balance"<<endl; break;}
                    
                    acc.amount-=amount;

                    Transaction transacObj(accountNumber,accType,amount,"atm",today);
                    addTransaction(id,transacObj);
                    return true;
                }
            } 
            return false;
        }
    }

}

bool withCurAcc(string id,int accountNumber,int amount,string accType){

    for(auto &u: users){
        if(u.userID==id) {
            for(auto &acc: u.ca){
                if(acc.accountNumber==accountNumber){ 
                    if(amount>acc.amount){ cout<<"Insufficient Balance"<<endl; break;}
                    
                    int origAmt=amount;
                    amount=500<(0.005*amount) ? (amount+500) : (1.005*amount);
                    acc.amount-=amount;

                    Transaction transacObj(accountNumber,accType,origAmt,"withd",today);
                    addTransaction(id,transacObj);
                    return true;
                }
            }
            return false;
        }
    }
}



void viewTransactions(string id){
    for(auto &u: users){
        if(u.userID==id) {
            for(auto &t : u.tr){
                cout<<t.accountNumber<<" "<<t.acctype<<" "<<t.amount<<" "<<t.transacType<<" "<<t.date<<endl;
            }
            return;
        }
    }
}

void viewDetails(string id){
    for(auto &u : users){
        if(u.userID==id){
            cout<<u.name<<" "<<u.age<<" "<<u.phno<<" "<<u.email<<endl;
            for(auto &acc: u.sa){
                cout<<acc.accountNumber<<" "<<"Rs "<<acc.amount<<" "<<acc.type<<" "<<acc.dateOfOpening<<endl;
                cout<<"ATM detaisl"<<acc.atmNum<<" "<<acc.expDate<<" "<<acc.cvv<<endl;
            }
            for(auto &acc: u.ca){
                cout<<acc.accountNumber<<" "<<"Rs "<<acc.amount<<" "<<acc.type<<" "<<acc.dateOfOpening<<endl; 
            }

            for(auto &acc: u.la){
                cout<<acc.accountNumber<<" "<<"Rs "<<acc.amount<<" "<<acc.type<<" "<<acc.dateOfOpening<<" loan-type "<<acc.loanType<<endl;
            }
            return;
        }
    }
}

int getPresentAmount(string id){

    for(auto &u: users){
        if(u.userID==id) {
            int presentAmt=0;
            for(auto acc: u.sa) presentAmt+=acc.amount;
            for(auto acc: u.ca) presentAmt+=acc.amount;
            return presentAmt;
        }
    }
}

string getPrevDate(string id){
    
    for(auto &u: users){
        if(u.userID==id) {
            return u.tr.back().date;
        }
    }
}

int getTodaysWithd(string id){
    for(auto &u: users){
        if(u.userID==id) {
            int todayAmt=0;
            for(int i=u.tr.size()-1;i>=0;i--){
                if(u.tr[i].transacType=="withd" || u.tr[i].transacType=="atm") todayAmt+=u.tr[i].amount;
                if(u.tr[i].date!=today) break;
            }
            return todayAmt;
        }
    }
}

bool existSCAcc(string id){
    for(auto &u: users){
        if(u.userID==id) {
            return !(u.sa.size()==0 && u.ca.size()==0);
        }
    }  
}

bool exceed5(string id){

    for(auto &u: users){
        if(u.userID==id) {
                int ct=0;
                string curMonth="";
                curMonth+=today[2];
                curMonth+=today[3];

                for(int i=u.tr.size()-1;i>=0;i--){
                    if(u.tr[i].transacType=="atm") ct++;

                    string month="";
                    month+=u.tr[i].date[2];
                    month+=u.tr[i].date[3];
                    if(curMonth!=month) break;
                }
                return ct>=5;
        }
    }   
}


int main(){
    // Customer user("","","",0);
    
    while(1){
        cout<<"Welcome to Inito Bank"<<endl;
        cout<<"Enter today's date in ddmmyyyy"<<endl;
        cin>>today;

        if(!validDate(today)){cout<<"Enter Valid date"<<endl; continue;}

        string id;
        cout<<"Enter your User ID"<<endl;
        cout<<"If you are a new user type -1"<<endl;
        cin>>id;

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
            // u.sa.push_back(SavingsAcc("as", "ad", 1, "ak"));
            users.push_back(u);
            cout<<" Welcome New User | User Id :"<<u.userID<<endl;
            cout<<"Save the User Id for future"<<endl;
            id=u.userID;

            // user=users.back();
            // user=u;
            //cout<<"Checking"<<user.sa.size()<<endl;
        }

        else{
            bool exist=false;
            for(auto &u : users){
                if(u.userID==id){ 
                    // cout<<"Hey  "<<u.sa.size()<<endl;
                    // Customer user(u);
                    // user=u;
                    // cout<<user.name<<endl;
                    cout<<" Welcome Existing User | User Id :"<<id<<endl;
                    exist=true;
                    break;
                }
            }

            if(!exist){ cout<<"User does not exist"<<endl; continue;}
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
                            // savObj.amount=amount;
                            addSavingsAcc(id, savObj);
                            // cout<<"Hey hello outside "<<getCustomers(id).sa.size()<<endl;

                            //  for(auto &u : users){
                            //     cout<<"Hey hello outside if "<<user.sa.size()<<endl;
                            //     cout<<u.userID<<" "<<id<<endl;
                            //     if(u.userID==id){ 
                            //         cout<<"Hey hello "<<u.sa.size()<<endl;
                            //         // cout<<(u==user)<<endl;
                            //         // user=u;
                            //         // cout<<user.name<<endl;
                            //     break;}
                            // }
                            
                            cout<<"Savings account created with Acc No. "<<savObj.accountNumber<<endl;

                            Transaction transacObj(savObj.accountNumber,"s",amount,"Acc open",today);
                            addTransaction(id,transacObj);
                            // getCustomer(id).tr.push_back(transacObj);
                        }

                    }
                    else if(ty=="c"){
                        if(amount<100000) cout<<"Minimum amount is 1,00,000"<<endl;
                        else if(age<18) cout<<"Minimum age required is 18 years"<<endl;
                        else {
                            CurrentAcc curObj(id,ty,amount,today);
                            curObj.amount=amount;
                            // getCustomer(id).ca.push_back(curObj);
                            addCurrentAcc(id,curObj);

                            cout<<"Current account created with Acc No. "<<curObj.accountNumber<<endl;

                            Transaction transacObj(curObj.accountNumber,"c",amount,"Acc open",today);
                            addTransaction(id,transacObj);
                        }

                    }
                    else if(ty=="l"){

                        if(!existSCAcc(id)) cout<<"You should have a Savings or Current a/c prior to loan"<<endl;
                        else if(age<25) cout<<"Minimum age required is 25 years"<<endl;
                        else if(amount>0.4*getPresentAmount(id)) cout<<"Loan above 40 percent deposits not granted"<<endl;
                        else if(amount<500000) cout<<"Minimum loan amount is 5,00,000"<<endl;
                        else{
                            string loanType;
                            cout<<"Enter the initial alphabet for Home/Car/Personal/Business loan in smallcase"<<endl;
                            cin>>loanType;

                            LoanAcc loanObj(id,ty,amount,today,loanType);
                            loanObj.amount=amount;
                            // getCustomer(id).la.push_back(loanObj);
                            addLoanAcc(id,loanObj);
                            
                            cout<<"Loan account created with Acc No. "<<loanObj.accountNumber<<endl;

                            Transaction transacObj(loanObj.accountNumber,"l",amount,"Acc open",today);
                            addTransaction(id,transacObj);
                        }
                    }
                    else cout<<"Invalid Entry"<<endl;

                    break;
                }

                //Viewing details
                case 2 : {
                    viewDetails(id);
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
                    
                    bool exist=false;
                    if(accType=="s"){
                        string prevDate=getPrevDate(id);
                        int months=numberOfMonths(prevDate,today);

                        if(depSavAcc(id,accountNumber,amount,months,accType)) cout<<"Money deposited"<<endl;
                        else cout<<"Account doesn't exist"<<endl;
                    }
                    else if(accType=="c"){
                        
                        if(depCurAcc(id,accountNumber,amount,accType)) cout<<"Money deposited"<<endl;
                        else cout<<"Account doesn't exist"<<endl;
                    }

                    //Loan Repayment
                    else if(accType=="l"){
                        string prevDate=getPrevDate(id);
                        int months=numberOfMonths(prevDate,today);

                        if(depLoanAcc(id,accountNumber,amount,months,accType)) cout<<"Loan installment deposited"<<endl;
                        else cout<<"Account doesn't exist"<<endl;
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
                    
                    bool exist=false;

                    if(accType=="s"){
                        //check today's transactions
                        if(getTodaysWithd(id)+amount>50000){
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
                                if(exceed5(id)){ amount+=500; cout<<"500 extra charged for exceeding 5 times a month ATM withdrawal"<<endl;}

                                if(withSavATMAcc(id,accountNumber,amount,accType)) cout<<"Amount withdrawn"<<endl;
                                else cout<<"Account doesn't exist"<<endl;
                                
                            }

                        }
                        else if(input=="d"){
                            if(withSavDirAcc(id,accountNumber,amount,accType)) cout<<"Amount withdrawn"<<endl;
                            else cout<<"Account doesn't exist"<<endl;
                        }

                    }
                    else if(accType=="c"){
                        if(withCurAcc(id,accountNumber,amount,accType)) cout<<"Amount withdrawn"<<endl;
                        else cout<<"Account doesn't exist"<<endl;
                    }

                    else cout<<"Invalid decision"<<endl;
                    break;
                }
                
                //View Transactions
                case 5 : {
                    viewTransactions(id);
                    break;
                }

                default : end=true;
            }

            if(end) break;
        }
    }
    return 0;
}