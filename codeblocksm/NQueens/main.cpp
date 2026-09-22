#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

int N;
vector<int> col;        // col[row] = column of queen placed in that row (-1 if none)
vector<bool> colUsed;
vector<bool> diag1Used;  // row - col + (N-1)
vector<bool> diag2Used;  // row + col

bool solveNQueens(int row) {
    if (row == N) return true; // all queens placed successfully

    for (int c = 0; c < N; c++) {
        int d1 = row - c + (N - 1);
        int d2 = row + c;

        if (!colUsed[c] && !diag1Used[d1] && !diag2Used[d2]) {
            // place queen
            col[row] = c;
            colUsed[c] = true;
            diag1Used[d1] = true;
            diag2Used[d2] = true;

            if (solveNQueens(row + 1)) return true; // success, propagate up

            // backtrack
            colUsed[c] = false;
            diag1Used[d1] = false;
            diag2Used[d2] = false;
            col[row] = -1;
        }
    }

    return false; // no column worked for this row -> backtrack further
}

void printBoard() {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            cout << (col[r] == c ? "Q " : ". ");
        }
        cout << "\n";
    }
}

int main() {
    cout << "Enter N: ";
    cin >> N;

    if (N <= 0) {
        cout << "N must be a positive integer.\n";
        return 0;
    }

    col.assign(N, -1);
    colUsed.assign(N, false);
    diag1Used.assign(2 * N - 1, false);
    diag2Used.assign(2 * N - 1, false);

    auto start = high_resolution_clock::now();
    bool found = solveNQueens(0);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "N = " << N << "\n";
    cout << "Solution Exists: " << (found ? "Yes" : "No") << "\n";
    cout << "Execution Time: " << duration.count() << " microseconds\n";

    if (found) {
        cout << "Solution Board:\n";
        printBoard();
    } else {
        cout << "No solution exists for N = " << N << ".\n";
    }

    return 0;
}
