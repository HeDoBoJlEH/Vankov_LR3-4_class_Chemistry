#ifndef MOLECULE_H
#define MOLECULE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Molecule
{
    string name;           // Название молекулы
    vector<string> atoms;  // Состав молекулы (атомы)

    public:
        Molecule() : name("") {}
        Molecule(string& name) : name(name) {}
        Molecule(const string& name, const vector<string>& atoms) : name(name), atoms(atoms) {}
        Molecule(const Molecule& ob) : Molecule(ob.name, ob.atoms) {} 

        void Print(); // Вывод данных о молекуле
        void CreateMolecule(); // Ввод данных о молекуле с консоли
        void Mass();  // Подсчет молекулярной массы
 
        string* GetName() { return &name; }
        vector<string>* GetAtoms() { return &atoms; }

        void SetName(string& name) { this->name = name; }
        void SetAtoms(vector<string>& atoms) { this->atoms = atoms; }

        ~Molecule() {}
};

// Глобальный вектор для хранения всех молекул
vector<Molecule> molecules;

#endif