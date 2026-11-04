#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    bool led = false;
    int cycles;

    cout << "=== C++ LED Simulator ===" << endl;
    cout << "How many times should the LED blink? ";
    cin >> cycles;

    if (cin.fail() || cycles <= 0) {
        cout << "Invalid number!" << endl;
        return 1;
    }

    for (int i = 0; i < cycles; i++) {
        led = true;
        cout << "LED: ON" << endl;


        this_thread::sleep_for(chrono::milliseconds(500));

        led = false;
        cout << "LED: OFF" << endl;

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout << "Simulation complete!" << endl;

    return 0;
}