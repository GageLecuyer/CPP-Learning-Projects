#include <iostream>
#include <random>
#include <limits>

using namespace std;

int randomNumber(int low, int high){
    static mt19937 generator(random_device{}());
    uniform_int_distribution<int> distribution(low,high);
    return distribution(generator);
}

void showStatus(int playerHP, int monsterHP, int potions){
    cout << "\nYour HP: " << playerHP 
        << " | Monster HP: " << monsterHP
        << " | Potions:  " << potions << endl;
}

int main(){
    int playerHP = 100;
    int monsterHP = 60;
    int potions = 3;
    bool escaped = false;

    cout << "==== DUNGEON BATTLE ====\n";

    while (playerHP >0 && monsterHP >0){
        showStatus(playerHP, monsterHP,potions);
        cout << "\n1. Attack\n2. Heal\n3. Run\nChoose: ";

        int choice;
        if(!(cin>>choice)){
            if(cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number.\n";
            continue;
        }
        if (choice==1){
            int damage = randomNumber(10,20);
            monsterHP -= damage;
            if (monsterHP <0) monsterHP=0;
            cout << "You attacked for "<< damage << "damage!\n";

        }else if(choice == 2){
            if(potions==0){
                cout << "You have no potions left!\n";
                continue;
            }
            int healing = randomNumber(15,25);
            playerHP += healing;
            if(playerHP >100)playerHP=100;
            potions--;
            cout << "You healed for " << healing << " HP!\n";

        }else if (choice==3){
            escaped = true;
            cout << "You have escaped the dungeon!\n";
            break;

        }else{
            cout << "Invalid choice please try again.\n";
            continue;
        }

        if(monsterHP > 0 ){
            int damage = randomNumber(5,15);
            playerHP -= damage;
            if(playerHP < 0 ) playerHP = 0;
            cout << "Monster attacked for " << damage << " damage!\n";

        }
    }

    if (monsterHP == 0 )
        cout << "\nYou win! The monster was defeated!\n";
    else if (playerHP ==0)
        cout << "\nGame over! The monster has defeated you!\n";
    else if (!escaped)
        cout << "\nGame endded.\n";

    return 0;   

}
