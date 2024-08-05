#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class Dice
{
public:
    void setRoll()
    {
        random_device rd;
        uniform_int_distribution<int> dist(1, 6);

        cRoll = dist(rd);
    }
    int getRoll()
    {
        return cRoll;
    }
    void setVisibility()
    {
        random_device rd;
        uniform_int_distribution<int> dist(1, 3);

        if (dist(rd) == 1)
        {
            visibility = true;
        }
        else
        {
            visibility = false;
        }
    }
    bool getVisibility()
    {
        return visibility;
    }
    void reveal()
    {
        visibility = true;
    }

private:
    int cRoll;
    bool visibility;
};

class Bag
{
public:
    vector<Dice> createBag()
    {
        bag.push_back(red);
        bag.push_back(green);
        bag.push_back(blue);

        return bag;
    }
    void roll()
    {
        for (int i = 0; i < bag.size(); i++)
        {
            bag[i].setRoll();
            bag[i].setVisibility();
        }
    }
    void rollResults()
    {
        for (int i = 0; i < 3; i++)
        {
            if (bag[i].getVisibility())
            {
                cout << "dice " << i + 1 << ": " << bag[i].getRoll() << "\n";
            }
            else
            {
                cout << "dice " << i + 1 << ":\n";
            }
        }

        cout << "\n";
    }
    int getSum()
    {
        sum = 0;

        for (int i = 0; i < bag.size(); i++)
        {
            bag[i].reveal();
            sum += bag[i].getRoll();
        }

        return sum;
    }
    int getBid()
    {
        bid = 0;
        numVisible = 0;

        random_device rd;

        for (int i = 0; i < bag.size(); i++)
        {
            if (bag[i].getVisibility())
            {
                bid += bag[i].getRoll();
                numVisible += 1;
            }
        }

        if (numVisible == 0)
        {
            uniform_int_distribution<int> dist(4, 10);
            bid += dist(rd);
        }
        else if (numVisible == 1)
        {
            uniform_int_distribution<int> dist(3, 7);
            bid += dist(rd);
        }
        else if (numVisible == 2)
        {
            uniform_int_distribution<int> dist(2, 4);
            bid += dist(rd);
        }

        return bid;
    }
    int getAsk()
    {
        ask = bid;

        random_device rd;
        uniform_int_distribution<int> dist(1, 2);

        for (int i = 0; i < bag.size(); i++)
        {
            if (not bag[i].getVisibility())
            {
                ask += dist(rd);
            }
        }

        return ask;
    }
    int getProfit(int bid, int ask, string call, int quantity)
    {
        profit = 0;

        if (call == "short")
        {
            profit = ask - getSum();
        }
        else
        {
            profit = getSum() - bid;
        }

        return profit * quantity;
    }

private:
    vector<Dice> bag;
    Dice red, green, blue;
    int bid, ask, numVisible, profit, sum;
};

void play(int balance)
{
    // initialize variables
    string call;
    int quantity;
    int bid = 0, ask = 0;
    int tProfit, cProfit;
    int counter;

    // create new bag and add R, G, and B dice to it
    Bag bag;
    bag.createBag();

    {
        quantity = 0;

        // roll dice in bag and set visibility
        bag.roll();

        // get results of visible dice from roll
        bag.rollResults();

        // print bid and ask quotes
        bid = bag.getBid();
        ask = bag.getAsk();
        cout << "the market maker quotes " << bid << " at " << ask << "\n";
        cout << "balance: $" << balance << "\n\n";

        // get player's call
        while (call != "short" and call != "buy" and call != "skip")
        {
            cout << "short, buy, or skip?: ";
            cin >> call;
        }

        // skip turn
        if (call == "skip")
        {
            cout << "you skip this turn.\n";
            play(balance);
        }

        // get plater's quantity
        cout << "quantity?: ";
        cin >> quantity;
        cout << "\n";

        // check if player's quantity is valid and state transaction
        if (call == "short")
        {
            if ((18 - ask) * quantity > balance)
            {
                cout << "you do not have enough balance to do that, -$50\n\n";
                balance -= 50;

                this_thread::sleep_for(chrono::seconds(3));

                system("clear");

                play(balance);
            }

            cout << "you " << call << " " << quantity << " shares at " << ask << ".\n\n";
        }
        else
        {
            if (quantity > balance / bid)
            {
                cout << "you do not have enough balance to do that, -$50\n\n";
                balance -= 50;

                this_thread::sleep_for(chrono::seconds(3));

                system("clear");

                play(balance);
            }

            cout << "you " << call << " " << quantity << " shares at " << bid << ".\n\n";
        }

        // calculate true profit
        tProfit = bag.getProfit(bid, ask, call, quantity);

        // display dice results
        bag.rollResults();

        // ask player to calculate profit
        cout << "how much profit did you make?: ";

        cin >> cProfit;
        cout << "\n";

        // compare calculated profit to true profit
        if (cProfit != tProfit)
        {
            cout << "you calculated profit incorrectly, -$50\n\n";
            balance -= 50;

            this_thread::sleep_for(chrono::seconds(3));

            system("clear");

            play(balance);
        }
        else
        {
            cout << "correct\n\n";
            balance += tProfit;

            this_thread::sleep_for(chrono::seconds(3));

            system("clear");

            play(balance);
        }
    }
}

int main()
{
    play(500);

    return 0;
}