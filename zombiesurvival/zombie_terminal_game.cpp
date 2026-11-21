#include <iostream>
#include <random>
#include <limits>
using namespace std;

struct Player{
    int health = 100;
    int ammo = 12;
    int medkits = 2;
    int kills = 0;
    int day = 1;

};

int randomNumber(int low, int high){
    static mt19937 generator(random_device{}());
    uniform_int_distribution<int> distribution(low,high);
    return distribution(generator);

}

int readChoice() {
    int choice;
    if (cin>>choice) return choice;
    if (cin.eof()) return -1;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}

void showStatus(const Player& player,int zombieHP){
    cout << "\n==== Day " << player.day << " ====\n";
    cout << "Health: " << player.health << "/100\n";
    cout << "Ammo: " << player.ammo << "/20\n";
    cout << "Medkits: " << player.medkits << "\n";
    cout << "Zombies defeated: " <<player.kills << "\n";
    cout << "Zombie HP: " << zombieHP << "\n";

}

void shootZombie(Player& player, int& zombieHP){
    if(player.ammo <= 0 ){
        cout << "Click! you have no ammo.\n";
        return;
    }
    player.ammo--;
    int damage = randomNumber(15,30);
    zombieHP -= damage;
    if(zombieHP<0 )zombieHP=0;
    cout << "You hit the zombie for " << damage << " damage!\n";

}
void searchSupplies(Player& player){
    if(randomNumber(1,2)==1){
        int found = randomNumber(3,7);
        int oldammo = player.ammo;
        player.ammo +=found;
        if(player.ammo > 20)player.ammo = 20;
        cout << "You found " << player.ammo - oldammo << " bullets\n";
    }else{
        player.medkits++;
        cout << "You found a medkit\n";
    }
}

bool useMedkit(Player& player){
    if (player.medkits<=0){
        cout << "You have no medkits left\n";
        return false;
    }
    if(player.health==100){
        cout << "Your health is alreay at 100\n";
        return false;
    }
    int oldhealth= player.health;
    player.health +=30;
    if(player.health >100)player.health = 100;
    player.medkits--;
    cout << "You recovered " << player.health -oldhealth << " HP\n";
    return true;
}

bool tryEscape(){
    bool success = randomNumber(1,10) <=6;
    if(success)
        cout << "You escaped the zombie\n";
    else
        cout << "Escape failed!\n";

    return success;
}
void zombieAttack(Player& player){
    int damage = randomNumber(5,15);
    player.health -= damage;
    if(player.health <0) player.health = 0;
    cout << "Zombie attacked for " << damage << " damage!\n";
}

int main(){
    Player player;
    int zombieHP=35;
    bool quit = false;

    cout << "==== Zombie Survival ====\n";
    cout << "Survive as many days as you can!\n";
    
    while(player.health > 0 && !quit){
        showStatus(player, zombieHP);
        cout << "\n1. Shoot zombie\n";
        cout << "2. Search for supplies\n";
        cout << "3. Use medkit\n";
        cout << "4. Try to escap\n";
        cout << "5. Exit\nChoose: ";

        int choice = readChoice();
        if(choice ==-1){
            cout << "input ended" << endl;
            break;
        }
        bool takeTurns = true;
        bool escaped = false;

        switch(choice){
            case 1:
                shootZombie(player,zombieHP);
                break;
            case 2: 
                searchSupplies(player);
            case 3: 
                takeTurns = useMedkit(player);
                break;
            case 4: 
                escaped = tryEscape();
                break;
            case 5: 
                quit = true;
                takeTurns = false;
                cout << "You ended your run\n";
                break;
            default: 
                takeTurns = false;
                cout << "Invalid choice Enter 1-5.\n";
                break;

        }
        if(quit || !takeTurns )continue;

        if(zombieHP==0|| escaped){
            if(zombieHP==0){
                player.kills++;
                cout << "Zombie defeated!\n";
            }
            player.day++;
            zombieHP = randomNumber(30,60);
            cout << "A new zombie appears!\n";

        }else{
            zombieAttack(player);
        }

    }

     if (player.health == 0)
        cout << "\nGAME OVER! You survived " << player.day << " days.\n";
    else
        cout << "\nFinal score: " << player.kills << " zombies defeated.\n";


    return 0;
}
