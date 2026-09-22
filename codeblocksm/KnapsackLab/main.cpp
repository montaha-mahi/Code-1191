#include <bits/stdc++.h>
using namespace std;

struct Item {
    int id;
    double weight;
    double profit;
    double ratio;
};

// ---------- Fractional Knapsack (Greedy) ----------
void fractionalKnapsack(vector<Item> items, double capacity) {
    sort(items.begin(), items.end(), [](Item a, Item b){ return a.ratio > b.ratio; });

    double totalProfit = 0, totalWeight = 0, remaining = capacity;

    cout << "\n--- Fractional Knapsack (Greedy) ---\n";
    cout << "Order considered (by ratio desc): ";
    for (auto &it : items) cout << "I" << it.id << " ";
    cout << "\n";

    for (auto &it : items) {
        if (remaining <= 0) break;
        if (it.weight <= remaining) {
            totalWeight += it.weight;
            totalProfit += it.profit;
            remaining -= it.weight;
            cout << "Take FULL Item " << it.id << " (w=" << it.weight
                 << ", p=" << it.profit << ")\n";
        } else {
            double fraction = remaining / it.weight;
            totalWeight += remaining;
            totalProfit += it.profit * fraction;
            cout << "Take FRACTION " << fraction << " of Item " << it.id
                 << " (w=" << it.weight << ", p=" << it.profit << ")\n";
            remaining = 0;
        }
    }

    cout << "Total Weight Used = " << totalWeight << "\n";
    cout << "Total Profit = " << totalProfit << "\n";
}

// ---------- 0/1 Knapsack using Greedy (ratio-based, not guaranteed optimal) ----------
void knapsack01Greedy(vector<Item> items, double capacity) {
    sort(items.begin(), items.end(), [](Item a, Item b){ return a.ratio > b.ratio; });

    double totalProfit = 0, totalWeight = 0, remaining = capacity;
    vector<int> selected;

    cout << "\n--- 0/1 Knapsack (Greedy, ratio-based) ---\n";
    cout << "Order considered (by ratio desc): ";
    for (auto &it : items) cout << "I" << it.id << " ";
    cout << "\n";

    for (auto &it : items) {
        if (it.weight <= remaining) {
            totalWeight += it.weight;
            totalProfit += it.profit;
            remaining -= it.weight;
            selected.push_back(it.id);
            cout << "SELECT Item " << it.id << " (w=" << it.weight
                 << ", p=" << it.profit << ")\n";
        } else {
            cout << "SKIP Item " << it.id << " (w=" << it.weight
                 << ", p=" << it.profit << ") - does not fit\n";
        }
    }

    cout << "Selected Items: ";
    for (int id : selected) cout << "I" << id << " ";
    cout << "\nTotal Weight = " << totalWeight << "\n";
    cout << "Total Profit (Greedy) = " << totalProfit << "\n";
}

// ---------- 0/1 Knapsack using Dynamic Programming (optimal) ----------
void knapsack01DP(vector<Item> items, int capacity) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        int w = (int)items[i-1].weight;
        int p = (int)items[i-1].profit;
        for (int c = 0; c <= capacity; c++) {
            dp[i][c] = dp[i-1][c];
            if (w <= c) {
                dp[i][c] = max(dp[i][c], dp[i-1][c-w] + p);
            }
        }
    }

    // Backtrack to find selected items
    vector<int> selected;
    int c = capacity;
    int totalWeight = 0;
    for (int i = n; i >= 1; i--) {
        if (dp[i][c] != dp[i-1][c]) {
            selected.push_back(items[i-1].id);
            c -= (int)items[i-1].weight;
            totalWeight += (int)items[i-1].weight;
        }
    }
    reverse(selected.begin(), selected.end());

    cout << "\n--- 0/1 Knapsack (Dynamic Programming) ---\n";
    cout << "Selected Items: ";
    for (int id : selected) cout << "I" << id << " ";
    cout << "\nTotal Weight = " << totalWeight << "\n";
    cout << "Total Profit (DP, Optimal) = " << dp[n][capacity] << "\n";
}

void computeRatios(vector<Item> &items) {
    cout << "\nItem | Weight | Profit | Ratio(P/W)\n";
    for (auto &it : items) {
        it.ratio = it.profit / it.weight;
        cout << "I" << it.id << " | " << it.weight << " | " << it.profit
             << " | " << it.ratio << "\n";
    }
}

int main() {
    cout << "=================================================\n";
    cout << "TEST CASE 1: Fractional Knapsack (Greedy optimal)\n";
    cout << "=================================================\n";
    {
        vector<Item> items = {
            {1, 10, 60}, {2, 20, 100}, {3, 30, 120}
        };
        double capacity = 50;
        computeRatios(items);
        fractionalKnapsack(items, capacity);
    }

    cout << "\n=================================================\n";
    cout << "TEST CASE 2: 0/1 Knapsack where Greedy WORKS\n";
    cout << "=================================================\n";
    {
        vector<Item> items = {
            {1, 2, 10}, {2, 3, 5}, {3, 5, 15}
        };
        int capacity = 5;
        vector<Item> itemsCopy = items;
        computeRatios(itemsCopy);
        knapsack01Greedy(itemsCopy, capacity);
        knapsack01DP(items, capacity);
    }

    cout << "\n=================================================\n";
    cout << "TEST CASE 3: 0/1 Knapsack where Greedy FAILS\n";
    cout << "=================================================\n";
    {
        vector<Item> items = {
            {1, 10, 60}, {2, 20, 100}, {3, 30, 120}
        };
        int capacity = 50;
        vector<Item> itemsCopy = items;
        computeRatios(itemsCopy);
        knapsack01Greedy(itemsCopy, capacity);
        knapsack01DP(items, capacity);
    }

    return 0;
}
