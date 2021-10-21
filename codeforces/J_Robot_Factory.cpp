#include <bits/stdc++.h>

using namespace std;

//  Tadeo Hepperle, 21.10.2021, Dortmund
//  https://codeforces.com/problemset/problem/1600/J

struct tile
{
    int num;
    vector<int> walls;
    bool checked;
    int roomnr;
};

vector<int> binarize(int n)
{
    auto bits = bitset<4>(n).to_string();
    vector<int> r;
    for (auto c : bits)
    {
        r.push_back(c - '0');
    }
    return r;
}

int main()
{
    int m, n;
    cin >> n;
    cin >> m;
    tile tiles[1000][1000];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> tiles[i][j].num;
            tiles[i][j].walls = binarize(tiles[i][j].num);
        }
    }

    int roomnr = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!tiles[i][j].checked)
            {
                queue<pair<int, int>> frontier;
                frontier.push({i, j});
                while (!frontier.empty())
                {

                    auto pos = frontier.front();
                    int ii = pos.first, jj = pos.second;
                    frontier.pop();
                    tiles[ii][jj].checked = true;
                    tiles[ii][jj]
                        .roomnr = roomnr;
                    // north
                    if (tiles[ii][jj].walls[0] == 0 && !tiles[ii - 1][jj].checked)
                    {
                        frontier.push({ii - 1, jj});
                    }
                    // east
                    if (tiles[ii][jj].walls[1] == 0 && !tiles[ii][jj + 1].checked)
                    {
                        frontier.push({ii, jj + 1});
                    }
                    // south
                    if (tiles[ii][jj].walls[2] == 0 && !tiles[ii + 1][jj].checked)
                    {
                        frontier.push({ii + 1, jj});
                    }
                    // west
                    if (tiles[ii][jj].walls[3] == 0 && !tiles[ii][jj - 1].checked)
                    {
                        frontier.push({ii, jj - 1});
                    }
                }
                roomnr++;
            }
        }
    }

    vector<int> roomsizes(roomnr, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            roomsizes[tiles[i][j].roomnr]++;
        }
    }
    sort(roomsizes.begin(), roomsizes.end());
    reverse(roomsizes.begin(), roomsizes.end());
    for (int size : roomsizes)
    {
        cout << size << " ";
    }

    return 0;
}
