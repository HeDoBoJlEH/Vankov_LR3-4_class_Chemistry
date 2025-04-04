#ifndef MOLECULE_CPP
#define MOLECULE_CPP

#include "Vankov_LR3-4_Methods.h"

MoleculeCollection& MoleculeCollection::operator +(const MoleculeCollection& molecule2)
{
    MoleculeCollection* molecule = new MoleculeCollection(*this);

    if (&molecule2 == this)
    {
        molecule->multiplier *= 2;
        return *molecule;
    }

    for (auto item : molecule2.substance)
    {
        Molecule* mol = new Molecule(*item);

        mol->SetMultiplier(item->GetMultiplier() * molecule2.multiplier);

        molecule->AddMolecule(mol);

        molecule->name += " + " + *item->GetName();
    }

    return *molecule;
}

void MoleculeCollection::operator ++(int)
{
    multiplier++;
}

void MoleculeCollection::operator ++()
{
    multiplier++;
}

MoleculeCollection& MoleculeCollection::operator -(const MoleculeCollection& molecule2)
{
    MoleculeCollection* molecule = new MoleculeCollection(*this);

    if (&molecule2 == this)
    {
        molecule->name = "";
        molecule->multiplier = 0;
        molecule->substance.clear();

        return *molecule;
    }

    bool find = false;
    vector<Molecule*> newSubstance;

    for (auto mol = substance.begin(); mol != substance.end(); mol++)
    {
        find = false;

        Molecule* newMol = new Molecule(*(*mol)->GetName(), *(*mol)->GetAtoms(), (*mol)->GetMultiplier() * multiplier);

        for (auto item : molecule2.substance)
        {
            if (*(*mol)->GetAtoms() == *item->GetAtoms())
            {
                find = true;

                newMol->SetMultiplier(newMol->GetMultiplier() - item->GetMultiplier());

                if (newMol->GetMultiplier() > 0)
                    newSubstance.push_back(newMol);
                
                else
                    break;
            }
        }

        if (!find)
            newSubstance.push_back(newMol);
    }

    if (newSubstance.empty())
    {
        molecule->name = "";
        molecule->substance = newSubstance;
        molecule->multiplier = 0;
    }
    else
    {
        string name = *newSubstance.at(0)->GetName();
        
        if (newSubstance.size() > 1)
        {
            for (int i = 1; i < newSubstance.size(); i++)
                name += " + " + *newSubstance.at(i)->GetName();
        }

        molecule->name = name;
        molecule->substance = newSubstance;
        molecule->multiplier = 1;

    }
    
    return *molecule;
}

void MoleculeCollection::operator --(int)
{
    multiplier--;
}

void MoleculeCollection::operator --()
{
    multiplier--;
}

MoleculeCollection& MoleculeCollection::operator *(const int mult)
{
    MoleculeCollection* mol = new MoleculeCollection(*this);

    mol->multiplier *= mult;

    return *mol;
}

bool MoleculeCollection::operator >(MoleculeCollection& right)
{
    return Mass() > right.Mass();
}

bool MoleculeCollection::operator <(MoleculeCollection& right)
{
    return Mass() < right.Mass();
}

bool MoleculeCollection::operator >=(MoleculeCollection& right)
{
    return Mass() >= right.Mass();
}

bool MoleculeCollection::operator <=(MoleculeCollection& right)
{
    return Mass() <= right.Mass();
}

bool MoleculeCollection::operator ==(MoleculeCollection& right)
{
    return Mass() == right.Mass();
}

void MoleculeCollection::operator =(MoleculeCollection& refMol)
{
    name = *refMol.GetName();
    multiplier = refMol.GetMultiplier();

    substance.clear();
    for (auto mol : refMol.GetSubstance())
        substance.push_back(mol);
}

Molecule& MoleculeCollection::operator [](const int idx)
{
    if (idx < substance.size())
        return *substance.at(idx);

    else 
    {
        Molecule* mol = new Molecule();
        return *mol;
    }
}

ostream& operator<<(ostream& os, MoleculeCollection& ob)
{
    if (ob.multiplier < 1) return os;

    string formula = AtomsVectorToString(ob.GetSubstance(0));

    if (ob.GetSubstance().size() > 1)
    {
        for (int i = 1; i < ob.GetSubstance().size(); i++)
            formula += " + " + AtomsVectorToString(ob.GetSubstance(i));
    }

    if (ob.GetMultiplier() > 1)
        formula = to_string(ob.GetMultiplier()) + "(" + formula + ")";

    return os << *ob.GetName() << ", " << formula;
}

istream& operator>>(istream& is, Molecule& ob)
{
    string name, formula;

    is >> name >> formula;
    
    ob.name = name;
    ob.atoms = SplitMolecule(formula);
    ob.multiplier = PopMultiplier(formula);

    return is;
}

ostream& operator<<(ostream& os, Molecule& ob)
{
    if (ob.multiplier < 1) return os;

    string formula = AtomsVectorToString(ob);

    return os << *ob.GetName() << ", " << formula;
}

int Molecule::Mass()
{
    int mass = 0;

    for (auto atom : atoms)
    {
        if (table.find(atom) != table.end())
            mass += table[atom];
    }

    return mass * multiplier;
}

int MoleculeCollection::Mass()
{
    int mass = 0;

    for (auto molecule : substance)
    {
        mass += (*molecule).Mass();
    }

    return mass * multiplier;
}

#endif