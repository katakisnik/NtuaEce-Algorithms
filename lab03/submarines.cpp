#include <iostream>

using namespace std;

using namespace std;

typedef long long int ll;

ll ModN = 1000000103;

struct gridrect {
    ll numofpaths;
    bool isentrance;
    int outx;
    int outy;
};

struct pilot {
    int entrancex;
    int entrancey;
    int exitx;
    int exity;
};

gridrect grid[180][180][100];
int N, M, K, X;
pilot pilotarray[100];

int main()
{
    int i, j, k, s;
    ll result = 0;
    cin >> N;
    cin >> M;
    cin >> K;
    cin >> X;
    for (i=0; i<M; i++) {
        for (j=0; j<N; j++) {
            for (k=0; k<X; k++) {
                grid[i][j][k].isentrance = false;
                grid[i][j][k].numofpaths = 0;
                grid[i][j][k].outx = -1;
                grid[i][j][k].outy = -1;
            }
        }
    }

    for (i=0; i<K; i++) {
        cin >> s;
        pilotarray[i].entrancex = s/M;
        pilotarray[i].entrancey = s%M;
        for (k=0; k<X+1; k++) {
            grid[pilotarray[i].entrancey][pilotarray[i].entrancex][k].isentrance = true;
        }
        cin >> s;
        pilotarray[i].exitx = s/M;
        pilotarray[i].exity = s%M;
        for (k=0; k<X+1; k++) {
            grid[pilotarray[i].entrancey][pilotarray[i].entrancex][k].outx = pilotarray[i].exity;
            grid[pilotarray[i].entrancey][pilotarray[i].entrancex][k].outy = pilotarray[i].exitx;
        }
    }
    int rows = M;
    int collumns = N;
    grid[rows-1][collumns-1][0].numofpaths = 1;
    for (k=0; k<X+1; k++) {
        for (j=collumns-1; j>=0; j--) {
            for (i=rows-1; i>=0; i--) {
                if (i+1>rows-1) {
                    if (j+1>collumns-1) {}
                    else {
                        if (grid[i][j+1][k].isentrance == false) {
                            grid[i][j][k].numofpaths = (grid[i][j][k].numofpaths + grid[i][j+1][k].numofpaths)%ModN;
                        }
                    }
                }
                else {
                    if (j+1>collumns-1) {
                        if (grid[i+1][j][k].isentrance == false) {
                            grid[i][j][k].numofpaths = (grid[i][j][k].numofpaths + grid[i+1][j][k].numofpaths)%ModN;
                        }
                    }
                    else {
                        if (grid[i+1][j][k].isentrance == true) {
                            if (grid[i][j+1][k].isentrance == true) {}
                            else {
                                grid[i][j][k].numofpaths = (grid[i][j][k].numofpaths + grid[i][j+1][k].numofpaths)%ModN;
                            }
                        }
                        else {
                            if (grid[i][j+1][k].isentrance == true) {
                                grid[i][j][k].numofpaths = (grid[i][j][k].numofpaths + grid[i+1][j][k].numofpaths)%ModN;
                            }
                            else {
                                grid[i][j][k].numofpaths = (grid[i][j][k].numofpaths + grid[i][j+1][k].numofpaths + grid[i+1][j][k].numofpaths)%ModN;
                            }
                        }
                    }
                }

            }
        }
        for(i=0; i<rows; i++) {
            for(j=0; j<collumns; j++) {
                if (grid[i][j][k].isentrance == true) {
                    grid[grid[i][j][k].outx][grid[i][j][k].outy][k+1].numofpaths = (grid[grid[i][j][k].outx][grid[i][j][k].outy][k+1].numofpaths + grid[i][j][k].numofpaths)%ModN;
                }
            }
        }
        result += grid[0][0][k].numofpaths%ModN;
    }
    cout << result%ModN << endl;
}
