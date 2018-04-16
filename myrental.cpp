

//#include <iostream>
//#include <time.h>
#include<bits/stdc++.h>
using namespace std;
struct CarStruct {
    char plateNumber[7];
    bool available;
    int userId;
   time_t rentalTime;
    time_t returnTime;
};

struct UserStruct {
    char name[10];
    int carRented;
};

struct timeHMS {
    int hour, minute, seconds;
};

CarStruct car_array[10];
UserStruct user_array[3];
int showMainMenu();
char * login();
void showName(int);
int rentCar();
void returnCar();
int timeChargePerUnit = 3600; 
int limitRentalSeconds = timeChargePerUnit * 24; 
float damageFineAmount = 50;
int toggleAvailability(int);
void checkCarAvailability(int);
void printTime();
double diffTime(time_t, time_t);
float lateCharges(double);
float getCharges(double);
void charge(double);
bool rentedCar = false;
int numberOfUsers = 3;
int currentUserIndex;
time_t currentTime;
time_t rentalTime, returnTime;
timeHMS duration(int);

//initialize cars
void initializeCar() {
    char plateNum[10][7] = {
        {'P', 'E', 'A', '1', '2', '3', '4'},
        {'P', 'F', 'Y', '4', '0', '4', '7'},
        {'P', 'J', 'G', ' ', '4', '4', '2'},
        {'P', 'C', 'A', '2', '0', '4', '3'},
        {'P', 'A', 'W', '6', '8', '2', '4'},
        {'A', 'B', 'C', '3', '3', '6', '5'},
        {'P', 'F', 'S', '2', '6', '4', '6'},
        {'P', 'C', 'A', '7', '0', '4', '7'},
        {'P', 'E', 'D', '1', '2', '4', '8'},
        {'P', 'B', 'G', '5', '7', '9', '9'}
    };

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 7; j++) {
            car_array[i].plateNumber[j] = plateNum[i][j];
        }
        car_array[i].available = true;
    }
}

void initializeUser() {
    char user[3][10] = {
        {'A', 'm', 'a', 'n', 'S', 'e', 't', 'h', ' ', ' '},
        {'V', 'a', 'i', 'b', 'h', 'a', 'v', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            user_array[i].name[j] = user[i][j];
        }
        user_array[i].carRented = -1;
    }
}
int main() {
	system ("color FC");

    initializeCar();
    initializeUser();
    int mainMenuSelection;

    char input;

    bool running = true;
    do {
        numberOfUsers = 3;
        cout << "Hi, are you a registered user?" << endl;
        for (int i = 0; i < 3; i++) {
            if (user_array[i].name[0] != ' ') {
                cout << i << " : ";
                for (int j = 0; j < 10; j++) {
                    cout << user_array[i].name[j];
                }
                cout << endl;
            } else {
                numberOfUsers = i;
                i = 4;
            }
        }
        if (numberOfUsers < 3) {
            cout << "3 : [New User]" << endl;
        }
        cout << "Your selection: ";
        cin >> currentUserIndex;

        if (currentUserIndex == 9)
        {
        
        }

        if (currentUserIndex == 3) {
            cout << "Please enter your name[of only first 10 characters of the name  without spaces]" << endl;

            for (int i = 0; i < 10; i++) {
                cin >> input;
                if (input == '.') {
                    i = 10;
                } else {
                    user_array[numberOfUsers].name[i] = input;
                }
            }
            user_array[numberOfUsers].carRented = -1;
            currentUserIndex = numberOfUsers;
        }

        cout << endl << "welcome ";
        showName(currentUserIndex);
        cout << endl;
        mainMenuSelection = showMainMenu();
        if (mainMenuSelection == 0) {
            running = false;
            cout << "==========thank you==========" << endl << endl;
        } else if (mainMenuSelection == 1) {
            if (user_array[currentUserIndex].carRented != -1) {
                returnCar();
                cout << "==========thank you==========" << endl << endl;
            } else {
                rentCar();
                cout << "==========thank you==========" << endl << endl;
            }
        }
    } while (running);

    return (0);
}

char * login() {
    char in, username[10];
    int count = 0;
    cout << "Hi, please enter your name[of only 10 characters without space]" << endl;
    do {
        username[count] = in;
        in = getchar();
        count++;
    } while (in != '\n');

    return username;
}

void showName(int index) {
    for (int i = 0; i < 10; i++) {
        cout << user_array[index].name[i];
    }
}


//shows the main menu
int showMainMenu() {
    int mainMenuChoice = 0;
    printTime();
    cout << "Please select service" << endl;

    if (user_array[currentUserIndex].carRented != -1) {
        cout << "1: return a car" << endl;
    } else {
        cout << "1: rent a car" << endl;
    }
    cout << "0: exit" << endl;
    cin >> mainMenuChoice;
    return mainMenuChoice;
}
int rentCar() {
    int carSelection;
    cout << "please select a car to rent" << endl;
    for (int i = 0; i < 10; i++) {
        cout << i << ": ";
        for (int j = 0; j < 7; j++) {
            cout << car_array[i].plateNumber[j];
        }
        cout << " - ";
        if (car_array[i].available) {
            cout << "available";
        } else {
            cout << "unavailable";
        }
        cout << endl;
    }
    cin >> carSelection;

    if (car_array[carSelection].available == false) {
        cout << "please select another car, this car is not available" << endl;
        carSelection = -1;
    } else {
        car_array[carSelection].available = false;
        user_array[currentUserIndex].carRented = carSelection;
        car_array[carSelection].rentalTime = time(&rentalTime);
    }
    return carSelection;
}
void returnCar() {
    int rentedCarIndex = user_array[currentUserIndex].carRented;
   int _rentalTime = car_array[rentedCarIndex].rentalTime;
    int _returnTime = time(&currentTime);
    double rentalDuration = diffTime(_rentalTime, _returnTime);

    car_array[rentedCarIndex].available = true;
    user_array[currentUserIndex].carRented = -1;

    charge(rentalDuration);
}

void printTime() {
    time(&currentTime);
    cout << ctime(&currentTime);
}

double diffTime(time_t rentalTime, time_t returnTime) {
    double diff = difftime(returnTime, rentalTime);
    return diff;
}

void showPlateNumber(int carIndex) {
    int count = 0;
    while (count < 7) {
        cout << car_array[carIndex].plateNumber[count];
    }
}

void charge(double rentalDuration) {
    float charge;
    char damaged;
    timeHMS rentHMS = duration(rentalDuration);
    if (rentalDuration > limitRentalSeconds) {
        cout << "you are late " << (rentHMS.hour - 24 )<< " hours!";
       charge = lateCharges(rentalDuration);
   } else {
        cout << "please pay rental for duration of "
                << rentHMS.hour << ":"<<rentHMS.minute<<":"<<rentHMS.seconds<<"."<< endl;
       charge = getCharges(rentalDuration);
   }
       cout << "Car damaged? y/n:";
    cin >> damaged;
	    if (damaged == 'y') {
        cout << endl << "car damaged, " << damageFineAmount << " is charged" << endl;
        charge = damageFineAmount + charge;
   }
    cout << "total rental charge amount: " << charge << endl;
}

float getCharges(double rentalDuration) {
    int unitCharged = rentalDuration / timeChargePerUnit;
    return unitCharged * 5;
}

float lateCharges(double rentalDuration) {
    rentalDuration = rentalDuration - limitRentalSeconds;
    int unitCharged = rentalDuration / timeChargePerUnit;
    return (unitCharged * 10)+getCharges(limitRentalSeconds);
}

timeHMS duration(int total_seconds) {
   int hour = 3600;
    int minute = 60;    timeHMS returnDuration;
   returnDuration.hour = total_seconds / hour;
    total_seconds = total_seconds % hour;
	    returnDuration.minute = total_seconds / minute;
    total_seconds = total_seconds % minute;
    returnDuration.seconds = total_seconds;
    return returnDuration;
}

