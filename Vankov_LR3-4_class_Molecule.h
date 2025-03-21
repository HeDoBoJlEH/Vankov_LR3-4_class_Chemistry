#include <string>
#include <vector>
#include <map>

class Molecule
{
    std::string name;                // Название молекулы
    std::vector<std::string> atoms;  // Состав молекулы (атомы)

    public:
        Molecule() : name("") {}
        Molecule(std::string& name) : name(name) {}
        Molecule(const std::string& name, const std::vector<std::string>& atoms) : name(name), atoms(atoms) {}
        Molecule(const Molecule& ob) : Molecule(ob.name, ob.atoms) {} 
 
        std::string* GetName() { return &name; }
        std::vector<std::string>* GetAtoms() { return &atoms; }

        void SetName(std::string& name) { this->name = name; }
        void SetAtoms(std::vector<std::string>& atoms) { this->atoms = atoms; }

        ~Molecule() {}
};

std::map<std::string, int> mass;