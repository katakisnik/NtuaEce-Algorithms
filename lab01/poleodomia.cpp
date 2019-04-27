#include <iostream>

using namespace std;
typedef unsigned long long int ll;

ll buildings[1000001];
ll N;
int b[1000001];
int c[1000001];
ll result;

ll readint() {
ll n = 0;
char c = getchar_unlocked();
while ( !( '0' <= c && c <= '9' ) ) {
c = getchar_unlocked();
}
while ( '0' <= c && c <= '9' ) {
n = n * 10 + c - '0';
c = getchar_unlocked();
}
return n;
}

ll rightcosts(int pos, ll sum) {
    if(c[pos] == -1) {
        sum = sum + buildings[pos]*(N-pos);
        return sum;
    }
    else {
        sum = sum + buildings[pos]*(c[pos]-pos-1) + buildings[c[pos]] + rightcosts(c[pos], sum);
        return sum;
    }
}

ll leftcosts(int pos, ll sum) {
    if(b[pos] == -1) {
        sum = sum + buildings[pos]*(pos-1);
        return sum;
    }
    else {
        sum = sum + buildings[pos]*(pos-b[pos]-1) + buildings[b[pos]] + leftcosts(b[pos], sum);
        return sum;
    }
}

int main()
{
    N = readint();
    int i;
    buildings[0] = 0;
    for (i=1; i<N+1; i++) {
        buildings[i] = readint();
    }
    int j;
    bool flag = false;
    b[0]=0;
    b[1]=-1;
    for (i=2; i<N+1; i++){
        j = i-1;
        while (j>0) {
            if (buildings[j]>buildings[i]) {
                flag = true;
                break;
            }
            else {
                if (b[j]==-1) {
                    break;
                }
                else {
                    j = b[j];
                }
            }
        }
        if (flag) {
            b[i]=j;
        }
        else {
            b[i] = -1;
        }
        flag = false;
    }
    c[N+1]=0;
    c[N]=-1;
    flag = false;
    for (i=N-1; i>0; i--){
        j = i + 1;
        while(j<N+1) {
            if (buildings[j]>buildings[i]) {
                flag = true;
                break;
            }
            else {
                if (c[j]==-1) {
                    break;
                }
                else {
                    j = c[j];
                }
            }
        }
        if (flag) {
            c[i]=j;
        }
        else {
            c[i] = -1;
        }
        flag = false;
    }

    ll costs[N+1];
    for (i=1; i<N+1; i++) {
        costs[i] = buildings[i] + leftcosts(i, 0) + rightcosts(i, 0);
        if (i==1) {
            result = costs[i];
        }
        else {
            if (costs[i] < result) {
                result = costs[i];
            }
        }
    }
    cout << result << endl;


}
