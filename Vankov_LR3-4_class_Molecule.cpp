#ifndef MOLECULE_CPP
#define MOLECULE_CPP

#include "Vankov_LR3-4_Methods.h"

void Molecule::Print()
{
    string molecule = AtomsVectorToString(this->atoms);

    cout << name << ", " << molecule << endl;
}

Molecule* Molecule::CreateMolecule()
{
    Molecule *ob = new Molecule();

    string name, molecule;
    EnterString(name, "Enter molecule name: ");
    EnterString(molecule, "Enter molecule formula: ");
    
    ob->name = name;
    ob->atoms = SplitMolecule(molecule);

    return ob;
}

int Molecule::Mass()
{
    int mass = 0;

    for (auto atom : atoms)
    {
        if (table.find(atom) != table.end())
            mass += table[atom];
    }

    return mass;
}

#endif