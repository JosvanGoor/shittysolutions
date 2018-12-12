#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Rule
{
    string rule;
    char result;
};

Rule read_rule()
{
    Rule rule;

    cin >> rule.rule;
    cin.ignore(4); //ignore ' => '
    cin >> rule.result;
    cin.ignore(1); //ignore '\n'
    return rule;
}

vector<char> initial_state()
{
    cin.ignore(15); // ignore 'initial state: '
    string buf;
    getline(cin, buf);

    return vector<char>(buf.begin(), buf.end());
}

string get_signature(vector<char> const &plants, size_t idx)
{
    string sig;
    
    switch(idx)
    {
        case 0:
            sig += "..";
            sig += string(plants.begin(), plants.begin() + 3);
            return sig;
        
        case 1:

            sig += ".";
            sig += string(plants.begin(), plants.begin() + 4);
            return sig;

        default:
            return string(plants.begin() + (idx - 2), plants.begin() + (idx + 2));
    }
}

int main()
{
    int first = 0;
    vector<char> plants = initial_state();
    vector<Rule> rules;

    cout << string(plants.begin(), plants.end()) << "\n";

    while(!cin.eof())
    {
        rules.push_back(read_rule());

        cout << "Rule: ";
        cout << rules.back().rule;
        cout << " => " << rules.back().result << "\n";
    }


}