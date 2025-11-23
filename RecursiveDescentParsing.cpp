#include <bits/stdc++.h>
using namespace std;

string input;
int pos = 0;

// Function declarations
bool E();
bool Eprime();
bool T();
bool Tprime();
bool F();

// Utility: check and consume character
bool match(char c) {
    if (pos < input.size() && input[pos] == c) {
        pos++;
        return true;
    }
    return false;
}

// E → T E'
bool E() {
    return T() && Eprime();
}

// E' → + T E' | ε
bool Eprime() {
    if (match('+')) {
        if (T() && Eprime()) return true;
        return false;
    }
    return true; // ε
}

// T → F T'
bool T() {
    return F() && Tprime();
}

// T' → * F T' | ε
bool Tprime() {
    if (match('*')) {
        if (F() && Tprime()) return true;
        return false;
    }
    return true; // ε
}

// F → (E) | a
bool F() {
    if (match('a')) return true;

    if (match('(')) {
        if (E() && match(')')) return true;
        return false;
    }
    return false;
}

int main() {
    cout << "Enter input string: ";
    cin >> input;

    pos = 0;
    bool result = E();

    // String must be fully consumed
    if (result && pos == input.size())
        cout << "String is accepted\n";
    else
        cout << "String is not accepted\n";

    return 0;
}
