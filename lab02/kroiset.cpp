#include <iostream>

using namespace std;
typedef long long ll;

int  N;
int a;
ll b,c;
int coef[10001];
ll C[10001];
ll sum[10001];

int main()
{
    int i, j;
    cin >> N;
    cin >> a;
    cin >> b;
    cin >> c;
    coef[0] = 0;
    C[0] = 0;
    sum[0] = 0;
    for (i=1; i<N+1; i++) {
        cin >> coef[i];
    }
    ll summary = 0;
    for (i=1; i<N+1; i++) {
        sum[i] = coef[i] + summary;
        summary = sum[i];
    }
    ll maxC, newC;
    for (i=1; i<N+1; i++) {
        for (j=1; j<i+1; j++) {
            if (j == 1) {
                maxC = C[j-1] + a*(sum[i] - sum[j-1])*(sum[i] - sum[j-1]) + b*(sum[i] - sum[j-1]) + c;
            }
            else {
                newC = C[j-1] + a*(sum[i] - sum[j-1])*(sum[i] - sum[j-1]) + b*(sum[i] - sum[j-1]) + c;
                if (newC > maxC) {
                    maxC = newC;
                }
            }
        }
        C[i] = maxC;
    }
    cout << C[N] << endl;
}
