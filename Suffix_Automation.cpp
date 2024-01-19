#include <iostream>
#include <vector>
#include <unordered_map>
class SuffixAutomaton {
private:
    struct State {
        std::unordered_map<char, int> transitions;
        int length;
        int link;
        State() : length(0), link(-1) {}
    };
    std::vector<State> states;
    int lastState;
public:
    SuffixAutomaton() {
        states.push_back(State());  
        lastState = 0;
    }
    void addString(const std::string& str) {
        for (char c : str) {
            extend(c);
        }
    }
    bool isSubstring(const std::string& str) {
        int currentState = 0;
        for (char c : str) {
            if (states[currentState].transitions.find(c) == states[currentState].transitions.end()) {
                return false; 
            }
            currentState = states[currentState].transitions[c];
        }
        return true;  
    }
private:
    void extend(char c) {
        int newStateIndex = states.size();
        states.push_back(State());
        int currentState = lastState;
        states[newStateIndex].length = states[currentState].length + 1;
        while (currentState != -1 && states[currentState].transitions.find(c) == states[currentState].transitions.end()) {
            states[currentState].transitions[c] = newStateIndex;
            currentState = states[currentState].link;
        }
        if (currentState == -1) {
            states[newStateIndex].link = 0;
        } else {
            int nextState = states[currentState].transitions[c];
            if (states[currentState].length + 1 == states[nextState].length) {
                states[newStateIndex].link = nextState;
            } else {
                int cloneStateIndex = states.size();
                states.push_back(states[nextState]); 
                states[cloneStateIndex].length = states[currentState].length + 1;
                while (currentState != -1 && states[currentState].transitions[c] == nextState) {
                    states[currentState].transitions[c] = cloneStateIndex;
                    currentState = states[currentState].link;
                }
                states[nextState].link = cloneStateIndex;
                states[newStateIndex].link = cloneStateIndex;
            }
        }
        lastState = newStateIndex;
    }
};
int main() {
    SuffixAutomaton automaton;
    automaton.addString("Football");
    automaton.addString("Boxing");
    automaton.addString("Weightlifting");
    std::string query;
    std::cout << "Enter a string to check if it is a substring: ";
    std::cin >> query;
    if (automaton.isSubstring(query)) {
        std::cout << "The entered string is a substring." << std::endl;
    } else {
        std::cout << "The entered string is not a substring." << std::endl;
    }
    return 0;
}
