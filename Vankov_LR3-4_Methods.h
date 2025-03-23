#ifndef METHODS_H
#define METHODS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Vankov_LR3-4_class_Molecule.cpp"

using namespace std;

string filename = "molecules.txt";

// Корректный ввод строки
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

// Корректный ввод числа
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

// Конвертировать строку в вектор атомов
vector<string> SplitMolecule(const string& molecule)
{
    vector<string> atoms;

    string atom;

    for (const char& ch : molecule)
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

// Запись молекул из файла в вектор молекул
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

                string name, molecule;
                getline(ss, name, ',');
                getline(ss, molecule);

                vector<string> atoms = SplitMolecule(molecule);

                molecules.emplace_back(name, atoms);
            }

            file.close();
        }
        else
        {
            cerr << "Something went wrong" << endl;
        }
    };
}

// Показать все молекулы в векторе молекул
void ShowMolecules()
{
    for (auto iterator = molecules.begin(); iterator != molecules.end(); iterator++)
        (*iterator).Print();
}

#endif