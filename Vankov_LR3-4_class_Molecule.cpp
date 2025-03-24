#ifndef MOLECULE_CPP
#define MOLECULE_CPP

#include "Vankov_LR3-4_Methods.h"

void Molecule::Print()
{
    string molecule = AtomsVectorToString(this->atoms);

    cout << name << ", " << molecule << endl;
}

void Molecule::CreateMolecule()
{
    Molecule ob;

    string name, molecule;
    EnterString(name, "Enter molecule name: ");
    EnterString(molecule, "Enter molecule formula: ");
    
    ob.name = name;
    ob.atoms = SplitMolecule(molecule);

    molecules.push_back(ob);
}

#endif