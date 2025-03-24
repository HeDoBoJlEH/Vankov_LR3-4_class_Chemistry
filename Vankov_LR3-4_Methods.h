#ifndef METHODS_H
#define METHODS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include "Vankov_LR3-4_class_Molecule.h"

using namespace std;

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

// Глобальный вектор для хранения всех молекул
vector<Molecule*> molecules;

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

                Molecule* ob = new Molecule(name, atoms);

                molecules.push_back(ob);
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
string AtomsVectorToString(vector<string> atoms)
{
    string molecule = atoms[0];
    int num = 1;

    for (auto atom = atoms.begin() + 1; atom != atoms.end(); atom++)
    {
        if (*(atom - 1) == *atom)
        {
            num++;
            continue;
        }

        else if (*(atom - 1) != *atom && num > 1)
        {
            molecule += to_string(num);
            num = 1;
        }           
        
        molecule += *atom;
    }

    return molecule;
}

// Вычислить молекулярную массу каждой молекулы в векторе
void ShowMoleculesMass()
{
    for (auto molecule : molecules)
    {
        molecule->Print();
        cout << "Mass: " << molecule->Mass() << endl << endl;
    }
}

// Добавить молекулу в вектор
void AddMolecule()
{
    molecules.push_back(Molecule::CreateMolecule());

    cout << "Done." << endl;
}

// Показать все молекулы в векторе молекул
void ShowMolecules()
{
    for (auto iterator = molecules.begin(); iterator != molecules.end(); iterator++)
        (*iterator)->Print();
}

#endif