#ifndef MOLECULE_CPP
#define MOLECULE_CPP

#include "Vankov_LR3-4_class_Molecule.h"

void Molecule::Print()
{
    string molecule;
    int num = 1;

    for (auto iterator = atoms.begin(); iterator != atoms.end(); iterator++)
    {
        if (iterator != atoms.begin() && *(iterator - 1) == *iterator)
            num++;

        else if (iterator != atoms.begin() && *(iterator - 1) != *iterator && num > 1)
        {
            molecule += to_string(num);
            num = 1;
            molecule += *iterator;
        }

        else
            molecule += *iterator;
    }

    cout << name << ", " << molecule << endl;
}

#endif