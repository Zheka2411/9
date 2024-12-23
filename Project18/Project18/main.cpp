#include <iostream>
#include <string>
#include <vector>

enum class Grade {
    Common,
    Rare,
    Epic,
    Legendary,
    Mythic
};

// Base Weapon class
class Weapon {
protected:
    Grade grade;
    std::string name;
    unsigned int damage;

public:
    // Constructors
    Weapon(Grade grade, const std::string& name, unsigned int damage)
        : grade(grade), name(name), damage(damage) {}
    Weapon(const std::string& name)
        : grade(Grade::Common), name(name), damage(10) {}

    // Virtual methods
    virtual Grade GetDamage() const { return grade; }
    virtual void Upgrade() {
        if (grade != Grade::Mythic)
            grade = static_cast<Grade>(static_cast<int>(grade) + 1);
    }

    // Virtual destructor
    virtual ~Weapon() = default;
};

// Stick class
class Stick : public Weapon {
private:
    unsigned int charges;

public:
    Stick(const std::string& name, unsigned int charges)
        : Weapon(name), charges(charges) {}

    Grade GetDamage() const override { return grade; }
    void Upgrade() override {
        Weapon::Upgrade();
        charges += 5;
    }
};

// Sword class
class Sword : public Weapon {
public:
    Sword(const std::string& name) : Weapon(name) {}

    Grade GetDamage() const override { return grade; }
    void Upgrade() override { Weapon::Upgrade(); }
};

// Bow class
class Bow : public Weapon {
private:
    unsigned int max_damage;

public:
    Bow(const std::string& name, unsigned int max_damage)
        : Weapon(name), max_damage(max_damage) {}

    Grade GetDamage() const override { return grade; }
    void Upgrade() override {
        Weapon::Upgrade();
        max_damage += 10;
    }
};

// Base Unit class
class Unit {
protected:
    unsigned int HP;
    Weapon* weapon;
    unsigned int speed;
    std::string name;

public:
    // Constructors
    Unit(const std::string& name, unsigned int HP)
        : name(name), HP(HP), weapon(nullptr), speed(10) {}

    Unit(unsigned int HP) : HP(HP), weapon(nullptr), speed(10) {}
    Unit(const std::string& name) : name(name), HP(100), weapon(nullptr), speed(10) {}

    // Methods
    virtual void Attack(Unit& target) {
        std::cout << name << " attacks " << target.name << "!" << std::endl;
    }
    virtual void Defense() {
        std::cout << name << " defends!" << std::endl;
    }

    // Destructor
    virtual ~Unit() = default;
};

// Swordman class
class Swordman : public Unit {
private:
    unsigned int power;

public:
    Swordman(const std::string& name, unsigned int HP, unsigned int power)
        : Unit(name, HP), power(power) {}

    void Attack(Unit& target) override {
        std::cout << name << " strikes with power " << power << "!" << std::endl;
        Unit::Attack(target);
    }

    void Defense() override {
        std::cout << name << " raises a shield!" << std::endl;
    }
};

// Archer class
class Archer : public Unit {
private:
    unsigned int arrows;

public:
    Archer(const std::string& name, unsigned int HP, unsigned int arrows)
        : Unit(name, HP), arrows(arrows) {}

    void Attack(Unit& target) override {
        if (arrows > 0) {
            std::cout << name << " shoots an arrow!" << std::endl;
            arrows--;
        }
        else {
            std::cout << name << " is out of arrows!" << std::endl;
        }
        Unit::Attack(target);
    }

    void Defense() override {
        std::cout << name << " dodges swiftly!" << std::endl;
    }
};

// Mage class
class Mage : public Unit {
private:
    unsigned int mana; // range: 0-100

public:
    Mage(const std::string& name, unsigned int HP, unsigned int mana)
        : Unit(name, HP), mana(mana) {}

    void Attack(Unit& target) override {
        if (mana >= 10) {
            std::cout << name << " casts a spell!" << std::endl;
            mana -= 10;
        }
        else {
            std::cout << name << " is out of mana!" << std::endl;
        }
        Unit::Attack(target);
    }

    void Defense() override {
        std::cout << name << " conjures a magical shield!" << std::endl;
    }
};

// Example usage
int main() {
    Swordman swordman("Arthur", 120, 50);
    Archer archer("Robin", 100, 20);
    Mage mage("Merlin", 80, 50);

    swordman.Attack(archer);
    archer.Attack(mage);
    mage.Attack(swordman);

    return 0;
}
