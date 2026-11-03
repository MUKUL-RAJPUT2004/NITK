
#include <bits/stdc++.h>
using namespace std;

int tileID = 0;

void tileBoard(vector<vector<int>>& board,
               int top, int left, int size,
               int missingR, int missingC) {
    if (size == 1) return;

    int half = size / 2;
    int midR = top + half;
    int midC = left + half;


    int quadrant = (missingR >= midR ? 2 : 0)
                 + (missingC >= midC ? 1 : 0);

    int row[4] = {midR-1, midR-1, midR, midR};
    int col[4] = {midC-1, midC, midC-1, midC};

    int id = ++tileID;

    for (int q = 0; q < 4; q++) {
        if (q != quadrant)
            board[row[q]][col[q]] = id;
    }

    // Recursively tile the four quadrants.
    tileBoard(board, top, left, half,
              quadrant == 0 ? missingR : row[0],
              quadrant == 0 ? missingC : col[0]);

    tileBoard(board, top, midC, half,
              quadrant == 1 ? missingR : row[1],
              quadrant == 1 ? missingC : col[1]);

    tileBoard(board, midR, left, half,
              quadrant == 2 ? missingR : row[2],
              quadrant == 2 ? missingC : col[2]);

    tileBoard(board, midR, midC, half,
              quadrant == 3 ? missingR : row[3],
              quadrant == 3 ? missingC : col[3]);
}

int main() {
    int n, missingR, missingC;

    cin >> n >> missingR >> missingC;

    if (n < 2 || (n & (n - 1)) != 0 ||
        missingR < 1 || missingR > n ||
        missingC < 1 || missingC > n) {
        cout << "Invalid input\n";
        return 0;
    }

    vector<vector<int>> board(n, vector<int>(n, 0));

    // -1 marks the defective square.
    board[missingR-1][missingC-1] = -1;
    tileID = 0;

    tileBoard(board, 0, 0, n, missingR-1, missingC-1);

    cout << "Tiled Chessboard:\n";

    for (const auto& row : board) {
        for (int x : row)
            cout << setw(4) << x;
        cout << '\n';
    }

    cout << "Number of triominoes: " << tileID << '\n';
    cout << "Expected number: " << (1LL*n*n - 1)/3 << '\n';

    return 0;
}
