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
    int multiplier {1};

    public:
        Molecule() : name("") {}
        Molecule(const string& name, const vector<string>& atoms) : name(name), atoms(atoms) {}
        Molecule(const string& name, const vector<string>& atoms, const int multiplier) : Molecule(name, atoms) { this->multiplier = multiplier; }
        Molecule(const Molecule& ob) : Molecule(ob.name, ob.atoms, ob.multiplier) {} 

        friend istream& operator>>(istream& is, Molecule& ob); // Ввод данных о молекуле с консоли
        friend ostream& operator<<(ostream &os, Molecule& ob);
        int Mass();  // Подсчет молекулярной массы
 
        string* GetName() { return &name; }
        vector<string>* GetAtoms() { return &atoms; }
        int GetMultiplier() { return multiplier; }

        void SetName(string& name) { this->name = name; }
        void SetAtoms(vector<string>& atoms) { this->atoms = atoms; }
        void SetMultiplier(int mult) { this->multiplier = mult; }

        ~Molecule() {}
};

class MoleculeCollection
{
    string name;
    vector<Molecule*> substance;
    int multiplier {1};

    public:
        MoleculeCollection(Molecule* mol) : name( *mol->GetName() ) { substance.push_back(mol); }
        MoleculeCollection(Molecule* mol1, Molecule* mol2) : MoleculeCollection(mol1) { substance.push_back(mol2); name += *mol2->GetName(); }
        MoleculeCollection(const MoleculeCollection& ob) { name = ob.name; substance = ob.substance; multiplier = ob.multiplier; }

        int Mass();
        
        string* GetName() { return &name; }
        vector<Molecule*>& GetSubstance() { return substance; }
        Molecule& GetSubstance(int idx) { return *substance.at(idx); }
        int GetMultiplier() { return multiplier; }

        void SetName(string& name) { this->name = name; }
        void AddMolecule(Molecule* mol) { substance.push_back(mol); }
        void SetMultiplier(int mult) { multiplier = mult; }

        MoleculeCollection& operator +(const MoleculeCollection&);
        void operator ++(int);
        void operator ++();
        MoleculeCollection& operator -(const MoleculeCollection&);
        void operator --(int);
        void operator --();
        void operator =(MoleculeCollection&);
        MoleculeCollection& operator *(const int);
        bool operator >(MoleculeCollection&);
        bool operator <(MoleculeCollection&);
        bool operator >=(MoleculeCollection&);
        bool operator <= (MoleculeCollection&);
        bool operator ==(MoleculeCollection&);
        Molecule& operator [](const int);

        friend ostream& operator<<(ostream &os, MoleculeCollection& ob);

        ~MoleculeCollection() {}
};



#endif