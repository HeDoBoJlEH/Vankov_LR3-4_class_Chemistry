#include <iostream>
#include <functional>
#include <map>

using namespace std;

struct MenuItem
{
    string title;
    function<void()> func;
};

int main()
{
    map<int, MenuItem> menu = {
        { }
    };

    int choice;

    cout << "=== Menu ===" << endl;

    for (auto item : menu)
    {
        cout << item.first << ". " << item.second.title << endl;
    }
}