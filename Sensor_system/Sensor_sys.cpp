#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <random>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

// generate random readings for now soon to be a stm32 set up for this code
double generateRandom(double minimum, double maximum){
    static mt19937 generator(random_device{}());
    uniform_real_distribution<double> range(minimum,maximum);

    return range(generator);
}

//base class
class Sensor{
    protected:
        string name;
        string unit;
        double value;
        double minThreshhold;
        double maxThreshold;

        vector<double> history;

    public:

        Sensor(string n, string u, double min, double max)
            : name(n), unit(u), value(0),
              minThreshhold(min), maxThreshold(max){}

        virtual ~Sensor() =default;
        virtual void read() = 0;

        string getName() const {return name;}
        string getUnit() const {return unit;}
        double getValue()const {return value;}

        const vector<double>& getHistory() const {return history;}

        bool hasAlert() const {
            return !history.empty() && (value<minThreshhold || value > maxThreshold);

        }

        void display() const {
            cout << fixed << setprecision(2);
            cout << name << ": ";
            if(history.empty()){
                cout << "No readings yet. \n";
                return;
            }
            cout << value << " " << unit;
            cout  << (hasAlert() ? " [Warning]" : " [NORMAL]");
            cout << '\n';
        }

        void displayStats() const{
            if(history.empty()){
                cout<< name << ": No readings available.\n";
                return;
            }
            double minimum = *min_element(history.begin(), history.end());
            double maximum = *max_element(history.begin(), history.end());
            double average = accumulate(history.begin(), history.end(),0.0)
                / history.size();

              cout << fixed << setprecision(2);
              cout << "\nSensor: " << name << '\n';
              cout << "Samples: " << history.size() << '\n';
              cout << "Minimum: " << minimum << " " << unit << '\n';
              cout << "Maximum: " << maximum << " " << unit << '\n';
              cout << "Average: " << average << " " << unit << '\n';
        }
};

class TempSensor : public Sensor{

    public: 
        TempSensor() : Sensor ("Temperature","C", 15, 35){}
        void read() override{
            value =generateRandom(10,45);
            history.push_back(value);
        }
};

class HumiditySensor: public Sensor {
    public:
        HumiditySensor() : Sensor("Humidity","%",30,70){}
        void read() override {
            value = generateRandom(20,90);
            history.push_back(value);
        }
};

class PressureSensor : public Sensor{
    public:
        PressureSensor() : Sensor("Pressure", "hPa",980,1040){}
        void read() override {
            value = generateRandom(950,1060);
            history.push_back(value);
        }
};

class SensorManager {
    private: 
        vector<unique_ptr<Sensor>> sensors;

    public:

        void addSensor(){
            int choice;

            cout << "\n==== ADD SENSOR ====\n" 
                << "1. Temperature\n"
                << "2. Humitity\n"
                << "3. Pressure\n"
                << "Choose: ";
            if (!(cin>>choice))return;

            switch(choice){
                case 1:
                    sensors.push_back(make_unique<TempSensor>());
                    break;
                case 2: 
                    sensors.push_back(make_unique<HumiditySensor>());
                    break;
                case 3 : 
                    sensors.push_back(make_unique<PressureSensor>());
                    break;
                default: 
                    cout << "Invalid sensor type,\n";
                    return;

            }
            cout << "Sensor added successfully.\n";

        }
        void generateReadings() {
            if(sensors.empty()){
                cout << "No sensors available.\n";
                return;
            }
            cout << "\nGenerating sensor readings...\n";
            for(auto& sensor : sensors){
                sensor-> read();
                sensor-> display();
            }
        }

        void displayAll() const {
            if(sensors.empty()){
                cout << "No sensors available.\n";
                return;

            }
            cout << "\n==== CURRENT READINGS ====\n";
            for(const auto& sensor: sensors)
                sensor->display();
        }

        void showStats() const{
             if (sensors.empty()) {
            cout << "No sensors available.\n";
            return;
        }
             cout << "\n==== SENSOR STATS ====\n";
             for (const auto& sensor: sensors)
                 sensor->displayStats();
        }

        void checkAlerts() const {
             if (sensors.empty()) {
            cout << "No sensors available.\n";
            return;
            }
             bool alertFound = false;
             cout << "\n==== SENSOR ALERTS ====\n";
             for (const auto& sensor: sensors){
                 if(sensor->hasAlert()){
                     sensor->display();
                     alertFound = true;
                 }
             }
            if (!alertFound) cout << "No active alerts.\n";

        }
        void saveToFile() const{
            ofstream file("sensor_date.csv");
            if(!file.is_open()){
                cout << "Unable to open file\n";
                return;
            }
            file << "SensorID,Sensor,Sample,Value,Unit\n";
            file << fixed << setprecision(2);
            for(size_t id=0; id < sensors.size(); ++id){
                const auto& sensor = sensors[id];
                const auto& history = sensor->getHistory();
                for (size_t i =0; i<history.size(); ++i){
                    file << id +1 << ","
                        << sensor ->getName() << ","
                        << i+1 << ","
                        << history[i] << ","
                        << sensor -> getUnit() << '\n';
                }
            }
            file.close();
            if (file.fail()){
                cout << "Error saving sensor data,\n";
                return;

            }
            cout << "Data saved to sensor_data.csv\n";
        }

};

int main(){
    SensorManager manager;
    int choice =0;

    do {
        cout << "\n===== SENSOR MONITORING SYSTEM =====\n"
             << "1. Add sensor\n"
             << "2. Generate sensor readings\n"
             << "3. Display all sensors\n"
             << "4. View sensor statistics\n"
             << "5. Check sensor alerts\n"
             << "6. Save data to file\n"
             << "7. Exit\n"
             << "Choose: ";

        if (!(cin>> choice)){
            if(cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
            continue;

        }
        switch(choice){
             case 1: manager.addSensor(); break;
            case 2: manager.generateReadings(); break;
            case 3: manager.displayAll(); break;
            case 4: manager.showStats(); break;
            case 5: manager.checkAlerts(); break;
            case 6: manager.saveToFile(); break;
            case 7: cout << "Shutting down system...\n"; break;
            default: cout << "Invalid choice.\n";
        }   
        if (!cin){
            if(cin.eof())break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }while (choice !=7);
    return 0 ;
}
