#include <bits/stdc++.h>
using namespace std;

class Player {
private:
    int id;
    string name;
    int currentPosition;

public:
    Player(string name) {
        this->name = name;
        this->id = getUniqueId();
        this->currentPosition = 0;
    }

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    int getCurrentPosition() const {
        return currentPosition;
    }

    void setCurrentPosition(int position) {
        this->currentPosition = position;
    }

private:
    static int getUniqueId() {
        static int id = 1;
        return id++;
    }
};

class Snake {
private:
    int start;
    int end;

public:
    Snake(int start, int end) {
        this->start = start;
        this->end = end;
    }

    int getStart() const {
        return start;
    }

    int getEnd() const {
        return end;
    }
};

class Ladder {
private:
    int start;
    int end;

public:
    Ladder(int start, int end) {
        this->start = start;
        this->end = end;
    }

    int getStart() const {
        return start;
    }

    int getEnd() const {
        return end;
    }
};

class Game {
private:
    vector<Player> players;
    unordered_map<int, int> snakeAndLadder;
    int currentTurn;
    Player *winner;

public:
    Game(vector<Player> &players, vector<Snake> &snakes, vector<Ladder> &ladders) {
        this->players = players;

        for (auto it : snakes) {
            snakeAndLadder[it.getStart()] = it.getEnd();
        }

        for (auto it : ladders) {
            snakeAndLadder[it.getStart()] = it.getEnd();
        }

        this->currentTurn = 0;
        this->winner = nullptr;
    }
     const vector<Player> &getPlayers() const {
        return players;
    }

    void nextTurn() {
        currentTurn = (currentTurn + 1) % players.size();
    }

    bool roll(Player &player, int dice) {
        if (dice > 6 || dice < 1) {
            cout << "INVALID DICE!" << endl;
            return false;
        }

        if (winner != nullptr) {
            cout << "THE WINNER IS DECLARED!" << endl;
            return false;
        }

        if (player.getId() != players[currentTurn].getId()) {
            cout << "INVALID TURN OF PLAYER" << endl;
            return false;
        }

        int destination = players[currentTurn].getCurrentPosition() + dice;

        if (destination <= 100) {
            if (snakeAndLadder.find(destination) != snakeAndLadder.end()) {
                players[currentTurn].setCurrentPosition(snakeAndLadder[destination]);
            } else {
                players[currentTurn].setCurrentPosition(destination);
            }
        }

        if (destination == 100) {
            winner = &players[currentTurn];
        }
        nextTurn();
        return true;
    }

    Player *getWinner() const {
        return winner;
    }
};

int main() {
       cout << "************************************" << endl;
    cout << "        Snake and Ladder Game        " << endl;
    cout << "************************************" << endl;
    srand(time(NULL)); // Seed the random number generator

    Player p1("Robert");
    Player p2("Stannis");
    Player p3("Renly");

    Snake s1(17, 7);
    Snake s2(54, 34);
    Snake s3(62, 19);
    Snake s4(64, 60);
    Snake s5(87, 36);
    Snake s6(92, 73);
    Snake s7(95, 75);
    Snake s8(98, 79);

    Ladder l1(1, 38);
    Ladder l2(4, 14);
    Ladder l3(9, 31);
    Ladder l4(21, 42);
    Ladder l5(28, 84);
    Ladder l6(51, 67);
    Ladder l7(72, 91);
    Ladder l8(80, 99);

    vector<Snake> s = {s1, s2, s3, s4, s5, s6, s7, s8};
    vector<Ladder> l = {l1, l2, l3, l4, l5, l6, l7, l8};
    vector<Player> p = {p1, p2, p3};

    Game game(p, s, l);

    while (game.getWinner() == NULL) {
        int diceVal = (rand() % 6) + 1;
        game.roll(p1, diceVal);
        diceVal = (rand() % 6) + 1;
        game.roll(p2, diceVal);
        diceVal = (rand() % 6) + 1;
        game.roll(p3, diceVal);
    }

    cout << "The winner is: " << game.getWinner()->getName() << endl;

    cout << "All Scores: ";
    for (const Player &p : game.getPlayers())
        cout << p.getName() << ": " << p.getCurrentPosition() << " ";
    cout << endl;

    return 0;
}
