

class Character
{
public:
    Character(string name)
    :m_name(name)
    {
    }
    virtual ~Character()
    {
        
    }
    virtual string attackAction() const
    {
        string sound = "rushes toward the enemy";
        return sound;
    }
    virtual void printWeapon() const = 0;
    string name() const
    {
        return m_name;
    }
    
private:
    string m_name;
    string weapon;
    
    
};

class Elf: public Character
{
public:
    Elf(string name, int numOfArrows)
    :Character(name), arrowSupply(numOfArrows)
    {
    }
    virtual ~Elf()
    {
        cout << "Destroying " << name() << " the elf" << endl;
    }
    void printWeapon() const
    {
        cout << "a bow and quiver of " << arrowSupply << " arrows";
    }
    
private:
    int arrowSupply;
    
    
};

class Dwarf: public Character
{
public:
    Dwarf(string name)
    :Character(name)
    {
    }
    virtual ~Dwarf()
    {
        cout << "Destroying " << name() << " the dwarf" << endl;
    }
    void printWeapon() const
    {
        cout << "an axe";
    }
    
};

class Boggie: public Character
{
public:
    Boggie(string name)
    :Character(name)
    {
    }
    virtual ~Boggie()
    {
        cout << "Destroying " << name() << " the boggie" << endl;
    }
    virtual string attackAction() const
    {
        string sound = "whimpers";
        return sound;
    }
    void printWeapon() const
    {
        cout << "a short sword";
    }
    
};