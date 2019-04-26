#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <cstdlib>
#include <cmath>
#include <limits>

using namespace std;
typedef long long ll;


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


struct bullet {
    ll timestart;
    ll velocity;
    ll id;
};

struct collision {
    ll bulleta;
    ll bulletb;
};

ll N;
bullet lbulleta[1000000];
bullet rbulleta[1000000];
//vector<bullet> lbullet;
//vector<bullet> rbullet;
ll sizelbullet=0;
ll sizerbullet=0;
//list<collision> collisions;
ll L;
ll K;
collision col;
//int time = 0;

double getposistionleft(double t, ll u, ll tstart) {
    double position;
    position = (double) u*t - u*tstart;
    return position;
}

double getposistionright(double t, ll u, ll tstart) {
    double position;
    position = (double) -u*t + L + u*tstart;
    return position;
}

int main()
{
    N = readint();
    L = readint();
    K = readint();
    int i;
    for (i=0; i<N; i++){
        bullet b;
        b.timestart = readint();
        b.velocity = readint();
        b.id = i+1;
        lbulleta[i] = b;
    }
    for (i=0; i<N; i++){
        bullet b;
        b.timestart = readint();
        b.velocity = readint();
        b.id = i+1;
        rbulleta[i] = b;
    }
    ll j;
    double start=0.0, finish=L, time=0.0;
    for (j=0; j<K; j++) {
        vector<bullet> lbullet;
        vector<bullet> rbullet;
        ll maxu = 0;
        sizelbullet = 0;
        for (i=0; i<N; i++) {
            bullet b = lbulleta[i];
            if (b.velocity <= maxu) {}
            else {
                maxu = b.velocity;
                lbullet.push_back(b);
                //cout << b.id << endl;
                sizelbullet++;
            }
        }
        maxu = 0;
        sizerbullet = 0;
        for (i=0; i<N; i++) {
            bullet b = rbulleta[i];
            if (b.velocity <= maxu) {}
            else {
                maxu = b.velocity;
                rbullet.push_back(b);
                sizerbullet++;
            }
        }

        start = (double) time;
        finish = (double) L + time;
        while (1) {

            time = (start+finish)/2;
            double posleft, posright, maxl, minr;
            ll u, idl, idr, maxlid, minrid, timestart;
            bullet l,r;
            ll maxsize;
            if (sizelbullet >= sizerbullet) {
                maxsize = sizelbullet;
            }
            else {
                maxsize = sizerbullet;
            }
            //collision col;
            for (ll i=0; i<maxsize; i++) {
                if (i<sizelbullet){
                    l = lbullet[i];
                    u = l.velocity;
                    timestart = l.timestart;
                    idl = l.id;
                    posleft = getposistionleft(time, u, timestart);
                    if (i == 0) {
                        maxl = posleft;
                        maxlid = idl;
                    }
                    else {
                        if(posleft > maxl) {
                            maxl = posleft;
                            maxlid = idl;
                        }
                    }
                }
                if (i<sizerbullet) {
                    r = rbullet[i];
                    u = r.velocity;
                    timestart = r.timestart;
                    idr = r.id;
                    //cout << idr << endl;
                    posright = getposistionright(time, u, timestart);
                    if (i==0) {
                        minr = posright;
                        minrid = idr;
                        //cout << minrid << endl;
                    }
                    else {
                        if (posright < minr) {
                            minr = posright;
                            minrid = idr;
                            //cout << minrid << endl;
                        }
                    }
                }
            }
            if (abs(maxl - minr) < 1)  {
                col.bulleta = maxlid;
                col.bulletb = minrid;
                break;
            }
            if (maxl > minr) {
                finish = time;
            }
            else {
                start = time;
            }
        }

        cout << col.bulleta << " " << col.bulletb << endl;

        lbulleta[col.bulleta-1].velocity = 0;
        rbulleta[col.bulletb-1].velocity = 0;

    }

    return 0;
}
