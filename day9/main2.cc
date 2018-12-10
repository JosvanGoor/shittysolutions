#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Game
{
    size_t num_players;
    size_t last_marble;
};

istream &operator>>(istream &in, Game &game)
{
    cin >> game.num_players;
    cin.ignore(31); // ignore ' players; last marble is worth '.
    cin >> game.last_marble;
    cin.ignore(8); // ignore '  points\n'

    return in;
}

struct List
{
    size_t marble;
    List *next;
    List *previous;

    List(size_t num)
    : marble(num), next(this), previous(this)
    { }

    List *rotate(int direction)
    {
        List *rval = this;

        if (direction > 0)
        {
            for (; direction--; )
                rval = rval->next;
        }
        else 
        {
            for (; direction++; )
                rval = rval->previous;
        }

        return rval;
    }

    void insert_after(List *entry) //assume single entry
    {
        List *curnext = next;

        next = entry;
        entry->next = curnext;
        entry->next->previous = entry; 
    }

    //returns next in list. or nullptr when list size == 1
    List* remove_current()
    {
        if (next == this)
        {
            delete this;
            return nullptr;
        }

        next->previous = previous;
        previous->next = next;

        List *rval = next;
        delete this;
        return rval;
    }

    void print_list()
    {
        List *current = next;
        cout << setw(5) << "(" + to_string(marble) + ")";

        while (current != this)
        {
            cout << setw(5) << current->marble;
            current = current->next;
        }
    }
};

int main()
{

    Game game;
    cin >> game;

    cout << "Num players: " << game.num_players << "\n";
    cout << "Last marble: " << game.last_marble << "\n";

    List *root = new List(0);
    List *main = root;

    size_t current_player;

    for (size_t idx = 0; idx < game.last_marble + 1; ++idx)
    {
        main = main->rotate(1);
        main->insert_after(new List(idx));

        cout << "[" << setw(2) << idx << "]: ";
        root->print_list();
        cout << "\n";
    }

}