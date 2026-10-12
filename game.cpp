#include <iostream>
using namespace std;

class Fighter
{
    const char* name;
    int health;
    int maxHealth;
    int damage;

public:
    Fighter(const char* n, int h, int d)
    {
        name = n;
        health = h;
        maxHealth = h;
        damage = d;
    }

    void TakeDamage(int amount)
    {
        health = health - amount;

        if (health < 0)
        {
            health = 0;
        }
    }

    void Attack(Fighter& target) const
    {
        target.TakeDamage(damage);
    }

    bool IsAlive() const
    {
        return health > 0;
    }

    void PrintStatus() const
    {
        cout << name << ": " << health << "/" << maxHealth << endl;
    }
};


void PrintFighter(const Fighter& fighter)
{
    fighter.PrintStatus();
}


class Game
{
    Fighter player;
    Fighter enemies[3];
    Fighter* currentTarget = nullptr;

public:
    Game() : player("Hero", 30, 8),
        enemies{{"Enemy 1", 12, 3},
                {"Enemy 2", 18, 4},
                {"Enemy 3", 24, 5}}
    {
    }

    bool TrySelectTarget(int number, Fighter*& outTarget)
    {
        outTarget = nullptr;

        if (number < 1 || number > 3)
        {
            return false;
        }

        if (!enemies[number - 1].IsAlive())
        {
            return false;
        }

        outTarget = &enemies[number - 1];
        return true;
    }

    bool AllEnemiesDefeated() const
    {
        for (int i = 0; i < 3; i++)
        {
            if (enemies[i].IsAlive())
            {
                return false;
            }
        }

        return true;
    }

    void Run()
    {
        int command;
        int number;

        while (true)
        {
            PrintFighter(player);

            for (int i = 0; i < 3; i++)
            {
                PrintFighter(enemies[i]);
            }

            if (currentTarget != nullptr)
            {
                cout << "Current target: ";
                currentTarget->PrintStatus();
            }
            else
            {
                cout << "No target" << endl;
            }

            cout << "1 - Select target" << endl;
            cout << "2 - Attack" << endl;
            cout << "0 - Exit" << endl;

            cin >> command;

            if (command == 0)
            {
                break;
            }

            if (command == 1)
            {
                cin >> number;

                if (!TrySelectTarget(number, currentTarget))
                {
                    cout << "Wrong target" << endl;
                }
            }

            if (command == 2)
            {
                if (currentTarget != nullptr)
                {
                    player.Attack(*currentTarget);

                    if (currentTarget->IsAlive())
                    {
                        currentTarget->Attack(player);
                    }
                    else
                    {
                        currentTarget = nullptr;
                    }

                    if (AllEnemiesDefeated())
                    {
                        cout << "You won" << endl;
                        break;
                    }

                    if (!player.IsAlive())
                    {
                        cout << "You lose" << endl;
                        break;
                    }
                }
            }
        }
    }
};


int main()
{
    Game game;
    game.Run();

    return 0;
}