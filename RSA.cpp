#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

long int p, q, n, y, e, d, i, j, m, c, flag;
char oMsg[100];  // Original Message
char eMsg[100];  // Encrypted Message
char dMsg[100];  // Decrypted Message

bool prime(long int num) {
    if (num < 2) return false;
    for (i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

long int calculateD(long int e) {
    long int k = 1;
    while (true) {
        k = k + y;
        if (k % e == 0) {
            return (k / e);
        }
    }
}

void calculateE() {
    for (j = 2; j < y; j++) {  // Start from 2, as 1 is not considered valid
        if (y % j == 0) continue;
        if (prime(j) && j != p && j != q) {
            e = j;
            d = calculateD(e);
            if (d > 0) {
                break;
            }
        }
    }
}

void clearScreen() {
    #if defined(_WIN32)
        system("cls");  // Clear console for Windows
    #else
        system("clear");
    #endif
}

void encryptMessage() {
    cout << "Input Message to Encrypt\t: ";
    cin >> oMsg;

    int a;
    for (a = 0; oMsg[a] != '\0'; a++) {
        // Encryption
        m = oMsg[a];  // Convert char to ASCII
        long int k = 1;
        for (i = 0; i < e; i++) {
            k = k * m;
            k = k % n;
        }
        c = k;
        eMsg[a] = (char)c;  // Store encrypted character
    }

    eMsg[a] = '\0';

    cout << "\nThe Encrypted Message is: ";
    for (i = 0; eMsg[i] != '\0'; i++) {
        cout << eMsg[i];
    }
    cout << endl;
}

void decryptMessage() {
    cout << "Input Encrypted Message to Decrypt\t: ";
    cin >> eMsg;

    int a;
    for (a = 0; eMsg[a] != '\0'; a++) {
        // Decryption
        c = eMsg[a];  // Convert encrypted char to int
        long int k = 1;
        for (i = 0; i < d; i++) {
            k = k * c;
            k = k % n;
        }
        m = k;
        dMsg[a] = (char)m;  // Store decrypted character
    }

    dMsg[a] = '\0';

    cout << "\nThe Decrypted Message is: ";
    for (i = 0; dMsg[i] != '\0'; i++) {
        cout << dMsg[i];
    }
    cout << endl;
}

int main() {
    char choice;
    while (true) {
        clearScreen();  // Clear the screen each time the user starts over

        cout << "\t**--- RSA (Rivest-Shamir-Adleman) Encryption / Decryption Demonstration ---**" << endl;

        cout << "\nINSTRUCTION: Enter 'p' and 'q' (both must be prime numbers)." << endl;

        // Input p and check if it's prime
        cout << "Input p\t\t: ";
        cin >> p;
        if (!prime(p)) {
            cout << "P is not a prime number.\n";
            cout << "Press any key to retry.\n";
            cin.ignore();  // Ignore leftover newline from previous input
            cin.get();  // Wait for user input to clear screen
            continue;  // Retry by going back to the start of the loop
        }

        // Input q and check if it's prime
        cout << "Input q\t\t: ";
        cin >> q;
        if (!prime(q)) {
            cout << "Q is not a prime number.\n";
            cout << "Press any key to retry.\n";
            cin.ignore();
            cin.get();
            continue;  // Retry by going back to the start of the loop
        }

        // Both p and q are prime, continue with the program
        n = p * q;
        y = (p - 1) * (q - 1);
        calculateE();

        cout << "\np\tq\tn\ttot(n)" << endl;
        cout << p << "\t" << q << "\t" << n << "\t" << y << "\n" << endl;
        cout << "e = " << e << endl;
        cout << "d = " << d << endl;

        // Add this code to wait for user input before clearing the screen
        cout << "\nPress any key to continue...\n";
        cin.ignore();  // Ignore leftover newline from previous input
        cin.get();  // Wait for user input to clear screen

        // Main menu with 3 options
        while (true) {
            clearScreen();  // Clear the screen before showing the main menu
            cout << "\t**--- RSA (Rivest-Shamir-Adleman) Encryption / Decryption Demonstration ---**\n" << endl;
            cout << "\nMain Menu:" << endl;
            cout << "1. Encrypt Message" << endl;
            cout << "2. Decrypt Message" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == '1') {
                encryptMessage();
            } else if (choice == '2') {
                decryptMessage();
            } else if (choice == '3') {
                cout << "Exiting program.\n";
                exit(0);
            } else {
                cout << "Invalid choice. Please try again.\n";
            }

            // Ask the user if they want to go back to the main menu
            cout << "\nDo you want to return to the main menu? (Y/N): ";
            cin >> choice;

            if (choice == 'N' || choice == 'n') {
                cout << "Exiting program.\n";
                exit(0);  // Exit the program
            }
        }
    }

    return 0;
}
