#include <iostream>
#include <random>


using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist(1,2);
int main(){
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,100);

    int secretNumber = dist(gen);
    int guess = 0;
    int attempts = 0;

    cout << "=== Number guessing game==== " << endl;
    cout << "Im thiking of a number between 1-100" << endl;

    while(guess !=secretNumber){
        cout << "Enter your guess: ";
        cin>> guess;

        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a vaild number!" << endl;
            continue;

        }
        attempts++;

        if(guess < secretNumber){
            cout << "To low try again";
        }
        else if (guess > secretNumber){
            cout << "To high try again"; 
        }
        else{
            cout << "you win! " << attempts << " attempts to win";
        }
    }
    

    return 0;

}

