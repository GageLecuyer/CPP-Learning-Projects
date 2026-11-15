#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_ACCOUNTS = 50;

class BankAccount {

    private: 
        string owner;
        int account_number;
        double account_balance;

    public:

        BankAccount(){
            owner =  "";
            account_number = 0;
           account_balance = 0;
        }

        void createaccount(string name, int number){
            owner = name;
            account_number =number;
        }

        int getAccountNumber() const{
            return account_number;
        }

        bool deposit(double ammount){
            if (ammount <=0)return false;

           account_balance += ammount;
           return true;
        }

        bool withdraw(double ammount){
            if(ammount <= 0 || ammount>account_balance)
                return false;

            account_balance -= ammount;
            return true;
        }

        bool transferto(BankAccount& other, double ammount){
            if(!withdraw(ammount))return false;

            other.deposit(ammount);
            return true;
        }

        void display()const{
            cout << "Name: " << owner <<'\n';
            cout << "Account: " << account_number <<'\n';
            cout << fixed << setprecision(2);
            cout << "Balance: $" << account_balance << '\n';
        }
};

class BankSys{

    private: 
        BankAccount accounts[MAX_ACCOUNTS];
        int accountCount;
        int findAccount(int number)const{
            for(int i = 0; i <accountCount; i++){
                if(accounts[i].getAccountNumber()==number)
                    return i;
            }
         }

    public: 
        BankSys(){
            accountCount = 0;
        }

        void addAccount(){
            if(accountCount >= MAX_ACCOUNTS){
                cout << "Bank is full.\n";
                return;
            }
            string name;
            cout << "Enter Name: ";
            getline(cin>> ws,name);
            int number = 1001 + accountCount;
            accounts[accountCount].createaccount(name,number);
            accountCount++;
            cout << "account create: " << number << '\n';

        }

        void changeBalance(bool isDeposit){
            int number;

            cout << "Account number: ";
            if(!(cin>>number))return;

            int index= findAccount(number);

            if (index == -1){
                cout << "account not found.'\n'";
                return;
            }
            double ammount;
            cout << "Amount: $";
            if(!(cin>>ammount))return;

            bool success;
            if (isDeposit)
                success = accounts[index].deposit(ammount);
            else
                success = accounts[index].withdraw(ammount);

            if(success)
                cout << "Transaction sucessful" << endl;
            else
                cout << "Invalid amount or not enough funds" << endl;

        }

        void transferMoney(){
            int from, to;

            cout << "From account: ";
            if (!(cin>> from))return;

            cout <<"To account: ";
            if(!(cin>>to))return;

            int a = findAccount(from);
            int b = findAccount(to);

            if (a==-1 || b == -1 || a==b){
                cout << "Invalid accounts " << endl;
                return;
            }
            double ammount;
            cout << "Amount: $ ";

            if(!(cin>>ammount))return;

            if (accounts[a].transferto(accounts[b],ammount))
                cout << "Transfer sucessful" << endl;
            else
                cout << "Invalid account or not enough funds" << endl;
        }

        void showallaccounts() const{
            if(accountCount ==0 )
                cout << "No accounts added yet'\n'";

            for (int i=0; i < accountCount; i++){
                accounts[i].display();
            }
        }

};

int main(){
    
    BankSys bank;
    int choice;

    do{
        cout << "\n==== Bank Management System ====\n"
            << "1. Create account\n"
            << "2. Deposit money\n"
            << "3. Withdraw money\n"
            << "4. Tranfer money\n"
            << "5. Display all accounts\n"
            << "6. Exit\n"
            << "choose: ";

        if (!(cin>>choice))break;

        switch(choice){
            case 1: bank.addAccount(); break;
            case 2: bank.changeBalance(true); break;
            case 3: bank.changeBalance(false); break;
            case 4: bank.transferMoney(); break;
            case 5: bank.showallaccounts(); break;
            case 6: cout << "goodbye!! " << endl; break;
            default: cout << "Invalid choice.\n";
        }
        if (!cin) break;
    }while (choice!=6);

    return 0 ;


}
