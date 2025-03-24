#include "Vankov_LR3-4_class_Molecule.cpp"

using namespace std;

struct MenuItem
{
    string title;
    function<void()> func;
};

int main()
{
    map<int, MenuItem> menu = {
        {1, {"Create molecule vector from file", AddMoleculesFromFile(filename)}},
        {2, {"Show molecules vector", ShowMolecules}},
        {3, {"Add molecule to vector", AddMolecule}},
        {4, {"Show molecular mass of eaach molecule", ShowMoleculesMass}}
    };

    int choice;

    while (true)
    {
        cout << "===== Menu =====" << endl;

        for (auto item : menu)
        {
            cout << item.first << ". " << item.second.title << endl;
        }

        cout << "0. Exit" << endl << endl;

        EnterNumber(choice, "Choose menu option: ");

        if (choice == 0) break;

        cout << endl;

        if (menu.find(choice) != menu.end())
            menu[choice].func();

        cout << endl;
    }

    return 0;
}