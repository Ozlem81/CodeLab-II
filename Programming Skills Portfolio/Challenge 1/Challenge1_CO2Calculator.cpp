
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// Get the journey distance from the user
double getDistance() {
    double distance;

    while (true) {
        cout << "Enter journey distance in miles: ";

        if (cin >> distance && distance > 0) {
            return distance;
        }

        cout << "Invalid distance. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Get the fuel type from the user
int getFuelType() {
    int fuel;

    while (true) {
        cout << "\nSelect fuel type:\n";
        cout << "1. Diesel\n";
        cout << "2. Petrol\n";
        cout << "Enter your choice: ";

        if (cin >> fuel && (fuel == 1 || fuel == 2)) {
            return fuel;
        }

        cout << "Invalid selection. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Calculate the estimated CO2 emissions
double calculateEmissions(double distance, int fuel) {
    const double fuelConsumption = 9.66;
    const double dieselFactor = 2.68;
    const double petrolFactor = 2.31;

    double litresUsed = (distance / 100.0) * fuelConsumption;

    if (fuel == 1) {
        return litresUsed * dieselFactor;
    }

    return litresUsed * petrolFactor;
}

int main() {
    cout << "=== CO2 Emissions Calculator ===\n";

    double distance = getDistance();
    int fuel = getFuelType();

    double emissions = calculateEmissions(distance, fuel);

    cout << fixed << setprecision(2);
    cout << "\nEstimated CO2 emissions: "
         << emissions << " kg\n";

    return 0;
}
