#ifndef METHODS_H
#define METHODS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include "Vankov_LR3-4_class_Molecule.h"

using namespace std;

// Масса каждого атома
map<string, int> table = {
    { "H", 1 },
    { "He", 4 },
    { "Li", 7 },
    { "Be", 9 },
    { "B", 11 },
    { "C", 12 },
    { "N", 14 },
    { "O", 16 },
    { "F", 19 },
    { "Ne", 20 },
    { "Na", 23 },
    { "Mg", 24 },
    { "Al", 27 },
    { "Si", 28 },
    { "P", 31 },
    { "S", 32 },
    { "Cl", 36 },
    { "Ar", 40 },
    { "K", 39 },
    { "Ca", 40 },
    { "Sc", 45 },
    { "Ti", 48 },
    { "V", 51 },
    { "Cr", 52 },
    { "Mn", 55 },
    { "Fe", 56 },
    { "Co", 59 },
    { "Ni", 59 },
    { "Cu", 64 },
    { "Zn", 65 },
    { "Ga", 70 },
    { "Ge", 73 },
    { "As", 75 },
    { "Se", 79 },
    { "Br", 80 },
    { "Kr", 84 },
    { "Rb", 86 },
    { "Sr", 88 },
    { "Y", 89 },
    { "Zr", 91 },
    { "Nb", 93 },
    { "Mo", 96 },
    { "Tc", 98 },
    { "Ru", 101 },
    { "Rh", 103 },
    { "Pd", 106 },
    { "Ag", 108 },
    { "Cd", 112 },
    { "In", 115 },
    { "Sn", 119 },
    { "Sb", 122 },
    { "Te", 128 },
    { "I", 127 },
    { "Xe", 131 },
    { "Cs", 133 },
    { "Ba", 137 },
    { "La", 139 },
    { "Ce", 140 },
    { "Pr", 141 },
    { "Nd", 144 },
    { "Pm", 145 },
    { "Sm", 150 },
    { "Eu", 152 },
    { "Gd", 157 },
    { "Tb", 159 },
    { "Dy", 163 },
    { "Ho", 165 },
    { "Er", 167 },
    { "Tm", 169 },
    { "Yb", 173 },
    { "Lu", 175 },
    { "Hf", 178 },
    { "Ta", 181 },
    { "W", 184 },
    { "Re", 186 },
    { "Os", 190 },
    { "Ir", 192 },
    { "Pt", 195 },
    { "Au", 197 },
    { "Hg", 201 },
    { "Tl", 204 },
    { "Pb", 207 },
    { "Bi", 209 },
    { "Po", 209 },
    { "At", 210 },
    { "Rn", 222 },
    { "Fr", 223 },
    { "Ra", 226 },
    { "Ac", 227 },
    { "Th", 232 },
    { "Pa", 231 },
    { "U", 238 },
    { "Np", 237 },
    { "Pu", 244 },
    { "Am", 243 },
    { "Cm", 247 },
    { "Bk", 247 },
    { "Cf", 251 },
    { "Es", 252 },
    { "Fm", 257 },
    { "Md", 258 },
    { "No", 259 },
    { "Lr", 266 },
    { "Rf", 267 },
    { "Db", 268 },
    { "Sg", 269 },
    { "Bh", 270 },
    { "Hs", 277 },
    { "Mt", 278 },
    { "Ds", 281 },
    { "Rg", 282 },
    { "Cn", 285 },
    { "Nh", 286 },
    { "Fl", 289 },
    { "Mc", 290 },
    { "Lv", 293 },
    { "Ts", 294 },
    { "Og", 294 }
};

// Глобальный вектор для хранения всех существующих молекул
vector<MoleculeCollection*> molecules;

// Файл с исходной базой данных молекул { НАЗВАНИЕ,ФОРМУЛА }
string filename = "molecules.txt";

// Ожидание корректного ввода строки
void EnterString(string& str, string message)
{
    string input;

    cout << message;

    getline(cin, input);

    while (input.empty())
    {
        cout << message;
        getline(cin, input);
    }

    str = input;
}

// Можно конвертировать строку в число
bool CanStoi(string input)
{
    if (input.empty()) return false;

    try
    {
        int num = stoi(input);
    } catch (...) { return false; }

    return true;
}

// Ожидание корректного ввода числа
void EnterNumber(int& num, string message)
{
    string input;

    cout << message;

    getline(cin, input);

    while(!CanStoi(input))
    {
        cout << message;
        getline(cin, input);
    }

    num = stoi(input);
}

// Характеристика символа согласно ASCII
inline bool IsUpper(const char& ch) { return ch >= 65 && ch <= 90; }
inline bool IsLower(const char& ch) { return ch >= 97 && ch <= 122; }
inline bool IsNum(const char& ch) { return ch >= 49 && ch <= 57; }

// Конвертировать формулу в вектор атомов Molecule::atoms ( Mg2O => {"Mg", "Mg", "O"} )
vector<string> SplitMolecule(const string& formula)
{
    vector<string> atoms;

    string atom;

    for (const char& ch : formula)
    {
        if (atom.empty() && IsUpper(ch)) atom += ch;

        else if (atom.empty() && !IsUpper(ch)) continue;      

        else if (!atom.empty() && IsLower(ch)) atom += ch;

        else if (!atom.empty() && IsUpper(ch))
        {
            atoms.push_back(atom);           
            atom = ch;
        }

        else if (!atom.empty() && IsNum(ch))
        {
            for (int i = 0; i < atoi(&ch); i++)
                atoms.push_back(atom);

            atom.clear();
        }

        else continue;
    }

    atoms.push_back(atom);

    return atoms;
}

// Достать множитель из формулы (3H2O => 3)
int PopMultiplier(string& formula)
{
    string mult = "";
    for (char ch : formula)
    {
        if (atoi(&ch)) mult += ch;
        else if (ch == '0') mult += ch;
        else break;
    }

    return mult == "" ? 1 : stoi(mult);
}

// Запись молекул из файла в вектор молекул (molecules)
function<void()> AddMoleculesFromFile(string& filename)
{
    return [filename]()
    {
        molecules.clear();

        ifstream file(filename);

        if (file.is_open())
        {
            string line, str;

            while (getline(file, line))
            {
                stringstream ss(line);      

                string name, formula;
                int mult;

                getline(ss, name, ',');
                getline(ss, formula);

                vector<string> atoms = SplitMolecule(formula);
                mult = PopMultiplier(formula);

                Molecule* ob = new Molecule(name, atoms, mult);
                MoleculeCollection* molecule = new MoleculeCollection(ob);

                molecules.push_back(molecule);
            }

            file.close();

            cout << "Done." << endl;
        }
        else
        {
            cerr << "Something went wrong" << endl;
        }
    };
}

// Конвертировать вектор атомов в читаемую строку ( {"Mg", "Mg", "O"} => Mg2O )
string AtomsVectorToString(Molecule& molecule)
{
    vector<string> *atoms = molecule.GetAtoms();
    string str = (*atoms).at(0);
    int num = 1;

    for (auto atom = (*atoms).begin() + 1; atom != (*atoms).end(); atom++)
    {
        if (*(atom - 1) == *atom)
        {
            num++;
            continue;
        }

        else if (*(atom - 1) != *atom && num > 1)
        {
            str += to_string(num);
            num = 1;
        }              
        
        str += *atom;
    }

    if (molecule.GetMultiplier() > 1) 
        str = to_string(molecule.GetMultiplier()) + "(" + str + ")";

    return str;
}

// Вычислить молекулярную массу каждой молекулы в векторе
void ShowMoleculesMass()
{
    int sumMass = 0;

    for (auto mol : molecules)
    {
        cout << *mol << '\n' << "Mass: " << (*mol).Mass() << endl;
        sumMass += (*mol).Mass();
    }

    cout << "\nMass of vector: " << sumMass << endl;
        
}

// Добавить молекулу в вектор molecules (Ввод с клавиатуры)
void AddMolecule()
{
    Molecule* ob = new Molecule;

    cout << "Enter molecule name and formula: " << endl;
    
    cin >> *ob;

    MoleculeCollection* obj = new MoleculeCollection(ob);

    molecules.push_back(obj);

    cout << "Done." << endl;
}

// Попробовать получить ссылку на молекулу из вектора molecules. (True, если ссылка присвоена; False, если не найдена)
bool GetMoleculeRef(MoleculeCollection*& ob, string& name)
{
    for (auto molecule : molecules)
    {
        if (*molecule->GetName() == name)
        {
            ob = molecule;

            cout << "Find!" << endl;

            return true;
        }
    }

    cout << "Molecule doesn't exist." << endl;

    return false;
}

// Получить две ссылки на молекулы для дальнейших операций
void GetRefsForOperation(MoleculeCollection*& ob1, MoleculeCollection*& ob2)
{
    string molecule1, molecule2;

    do
    {
        EnterString(molecule1, "Enter name of 1 molecule: ");
    } while (!GetMoleculeRef(ob1, molecule1));

    do
    {
        EnterString(molecule2, "Enter name of 2 molecule: ");
    } while (!GetMoleculeRef(ob2, molecule2));
}

// Сложить две молекулы и добавить результат в вектор molecules
void SumMolecules()
{
    MoleculeCollection* ob1;
    MoleculeCollection* ob2;

    GetRefsForOperation(ob1, ob2);

    MoleculeCollection* mol = new MoleculeCollection(*ob1 + *ob2);
    
    molecules.push_back(mol);

    cout << "=== Result ===" << endl;
    cout << *mol << endl;
}

// Вычесть молекулу и добавить результат в molecules
void MinusMolecules()
{
    MoleculeCollection* ob1;
    MoleculeCollection* ob2;

    cout << "(Rule: new mol = mol1 - mol2)" << endl;

    GetRefsForOperation(ob1, ob2);

    MoleculeCollection* mol = new MoleculeCollection(*ob1 - *ob2);

    if (mol->GetMultiplier() > 0)
    {
        molecules.push_back(mol);

        cout << "=== Result ===" << endl;
        cout << *mol << endl;
    }
    else
    {
        cout << "It's empty!" << endl;
    }
}

// Выполнить операцию присваивания 
void AssignMolecules()
{
    MoleculeCollection* ob1;
    MoleculeCollection* ob2;

    cout << "(Rule: mol1 = mol2)" << endl;

    GetRefsForOperation(ob1, ob2);

    *ob1 = *ob2;

    cout << "\nDone." << endl;
}

// Функции для различных инкрементов/декрементов
inline auto prefixIncrement = [](MoleculeCollection*& ob){ ++(*ob); };
inline auto postfixIncrement = [](MoleculeCollection*& ob){ (*ob)++; };
inline auto prefixDecrement = [](MoleculeCollection*& ob){ --(*ob); };
inline auto postfixDecrement = [](MoleculeCollection*& ob){ (*ob)--; };

// Выполнить операцию инкремента/декремента
function<void()> Somecrement(function<void(MoleculeCollection*&)> func)
{
    return [func]()
    {
        MoleculeCollection* ob;
        string name;

        do
        {
            EnterString(name, "Enter name of molecule: ");
        }
        while (!GetMoleculeRef(ob, name));

        func(ob);

        cout << "\nDone." << endl;
    };
}

// Выполнить операцию умножения и записать результат в вектор molecules
void Multiply()
{
    MoleculeCollection* ob;
    string name;
    int mult;

    do
    {
        EnterString(name, "Enter name of molecule: ");
    }
    while (!GetMoleculeRef(ob, name));

    EnterNumber(mult, "Enter multiplier: ");

    MoleculeCollection* mol = &(*ob * mult);

    molecules.push_back(mol);

    cout << "=== Result ===" << endl;
    cout << *mol;
}

// Функции для сравнения двух молекул
inline auto bigger = [](MoleculeCollection*& ob1, MoleculeCollection*& ob2){ return *ob1 > *ob2; };
inline auto lesser = [](MoleculeCollection*& ob1, MoleculeCollection*& ob2){ return *ob1 < *ob2; };
inline auto biggerOrEqual = [](MoleculeCollection*& ob1, MoleculeCollection*& ob2){ return *ob1 >= *ob2; };
inline auto lessOrEqual = [](MoleculeCollection*& ob1, MoleculeCollection*& ob2){ return *ob1 <= *ob2; };
inline auto Equal = [](MoleculeCollection*& ob1, MoleculeCollection*& ob2){ return *ob1 == *ob2; };

// Сравнить две молекулы по молекулярной массе
function<void()> Comparision(function<bool(MoleculeCollection*&,MoleculeCollection*&)> func)
{
    return [func]()
    {
        MoleculeCollection* ob1;
        MoleculeCollection* ob2;

        GetRefsForOperation(ob1, ob2);

        cout << "Mass: " << ob1->Mass() << ", " << ob2->Mass() << endl;

        if (func(ob1, ob2))
            cout << "True." << endl;

        else
            cout << "False." << endl;
    };
}

// Получение по индексу простой молекулы из составной молекулы
void Indexation()
{
    MoleculeCollection* ob;
    string name;
    int idx;

    do
    {
        EnterString(name, "Enter molecule name: ");
    }
    while (!GetMoleculeRef(ob, name));

    EnterNumber(idx, "Enter index of simple molecule: ");

    if ((*(*ob)[idx].GetName()).empty())
        cout << "Not correct index" << endl;
    
    else
        cout << (*ob)[idx] << endl;
}

// Показать все молекулы в векторе молекул
void ShowMolecules()
{
    for (auto iterator = molecules.begin(); iterator != molecules.end(); iterator++)
        cout << **iterator << endl;
}

#endif