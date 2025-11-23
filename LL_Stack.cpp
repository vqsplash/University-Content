#include <bits/stdc++.h>
using namespace std;

string rev(const string &s) {
    string r = s;
    reverse(r.begin(), r.end());
    return r;
}

int main() {
    string input;
    cout << "Enter input string: ";
    cin >> input;

    input += "$";

    stack<char> st;
    st.push('$');
    st.push('A');

    int i = 0;

    cout << "Stack\t\tInput\n";

    while (!st.empty()) {

        // PRINT STACK CORRECTLY (top → bottom)
        stack<char> temp = st;
        string s = "";
        while (!temp.empty()) {
            s += temp.top();   // correct: show top first
            temp.pop();
        }

        cout << s << "\t" << input.substr(i) << "\n";

        char top = st.top();
        char a = input[i];

        if (!isupper(top)) {
            if (top == a) {
                st.pop();
                i++;
            } else {
                cout << "String is not accepted\n";
                return 0;
            }
        }
        else {
            if (top == 'A') {
                if (a == 'a') {
                    st.pop();
                    string rhs = rev("aCa");
                    for (char c : rhs) st.push(c);
                } else {
                    cout << "String is not accepted\n";
                    return 0;
                }
            }
            else if (top == 'C') {
                if (a == 'b') {
                    st.pop();
                    string rhs = rev("bC");
                    for (char c : rhs) st.push(c);
                }
                else if (a == 'a' || a == '$') {
                    st.pop(); // epsilon
                }
                else {
                    cout << "String is not accepted\n";
                    return 0;
                }
            }
        }
    }

    cout << "$\t$\n";
    cout << "String is accepted\n";

    return 0;
}
