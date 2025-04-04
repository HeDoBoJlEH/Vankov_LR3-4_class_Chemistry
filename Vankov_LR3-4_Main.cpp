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
        {4, {"Show molecular mass of each molecule", ShowMoleculesMass}},
        {5, {"Execute \"+\" operation", SumMolecules}},
        {6, {"Execute \"-\" operation", MinusMolecules}},
        {7, {"Execute \"=\" operation", AssignMolecules}},
        {8, {"Prefix increment", Somecrement(prefixIncrement)}},
        {9, {"Postfix increment", Somecrement(postfixIncrement)}},
        {10, {"Prefix decrement", Somecrement(prefixDecrement)}},
        {11, {"Postfix decrement", Somecrement(postfixDecrement)}},
        {12, {"Is first bigger than second?", Comparision(bigger)}},
        {13, {"Is first less than second?", Comparision(lesser)}},
        {14, {"Is first bigger or equal second?", Comparision(biggerOrEqual)}},
        {15, {"Is first less or equal second?", Comparision(lessOrEqual)}},
        {16, {"Is first equal second?", Comparision(Equal)}},
        {17, {"Get simple molecule via index", Indexation}}
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