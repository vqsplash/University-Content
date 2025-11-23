#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> Grammar;
map<char, set<char>> FIRST, FOLLOW;

// Check if a character is non-terminal (A-Z)
bool isNonTerminal(char c) {
    return (c >= 'A' && c <= 'Z');
}

// Compute FIRST of a symbol
void computeFIRST(char symbol) {
    // Already computed
    if (!FIRST[symbol].empty()) return;

    for (string prod : Grammar[symbol]) {
        for (int i = 0; i < prod.size(); i++) {
            char c = prod[i];

            // Terminal
            if (!isNonTerminal(c)) {
                FIRST[symbol].insert(c);
                break;
            }

            // Non-terminal
            computeFIRST(c);

            // Add FIRST(c) to FIRST(symbol)
            for (char x : FIRST[c]) {
                FIRST[symbol].insert(x);
            }

            // No epsilon support needed here, so break
            break;
        }
    }
}

// Compute FOLLOW for a non-terminal
void computeFOLLOW(char symbol) {
    for (auto &g : Grammar) {
        char A = g.first;

        for (string prod : g.second) {
            for (int i = 0; i < prod.size(); i++) {
                if (prod[i] == symbol) {
                    // Case 1: Something follows symbol
                    if (i + 1 < prod.size()) {
                        char next = prod[i + 1];

                        // Terminal after symbol
                        if (!isNonTerminal(next)) {
                            FOLLOW[symbol].insert(next);
                        }
                        // Non-terminal after symbol
                        else {
                            for (char x : FIRST[next]) {
                                FOLLOW[symbol].insert(x);
                            }
                        }
                    }

                    // Case 2: symbol is at end, add FOLLOW(A)
                    if (i + 1 == prod.size() && symbol != A) {
                        for (char x : FOLLOW[A]) {
                            FOLLOW[symbol].insert(x);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (e.g., A->aB):\n";
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        char lhs = s[0];
        string rhs = s.substr(3);

        Grammar[lhs].push_back(rhs);
    }

    // Compute FIRST for all non-terminals
    for (auto &g : Grammar) {
        computeFIRST(g.first);
    }

    // Initialize FOLLOW of start symbol
    char start = Grammar.begin()->first;
    FOLLOW[start].insert('$');

    // Compute FOLLOW (multiple passes for correctness)
    for (int k = 0; k < 5; k++) {
        for (auto &g : Grammar) {
            computeFOLLOW(g.first);
        }
    }

    // Print FIRST sets
    cout << "\nFIRST sets:\n";
    for (auto &g : Grammar) {
        cout << "FIRST(" << g.first << ") = { ";
        for (char x : FIRST[g.first]) cout << x << " ";
        cout << "}\n";
    }

    // Print FOLLOW sets
    cout << "\nFOLLOW sets:\n";
    for (auto &g : Grammar) {
        cout << "FOLLOW(" << g.first << ") = { ";
        for (char x : FOLLOW[g.first]) cout << x << " ";
        cout << "}\n";
    }

    return 0;
}
