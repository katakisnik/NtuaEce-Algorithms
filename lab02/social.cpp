#include <iostream>
#include <vector>

using namespace std;

long N;
long credits[500000];
long aleft[50000];
long aright[50000];
vector<long> helper1;
vector<long> helper2;

long binary_search_low (long credit, vector<long> &helper, int length) {
    if (credit < helper[0]) {
        return -1;
    }
    if (credit > helper[length-1]) {
        return length-1;
    }
    long low = 0;
    long high = length-1;
    while (low <= high) {
        long mid = (high+low)/2;
        if (credit < helper[mid]) {
            high = mid-1;
        }
        else if (credit > helper[mid]) {
            low = mid+1;
        }
        else {
            return mid;
        }
    }
    return low - 1;
}

long binary_search_high (long credit, vector<long> &helper, int length) {
    if (credit > helper[0]) {
        return -1;
    }
    if (credit < helper[length-1]) {
        return length-1;
    }
    long low = 0;
    long high = length-1;
    while (low <= high) {
        long mid = (high+low)/2;
        if (credit > helper[mid]) {
            high = mid-1;
        }
        else if (credit < helper[mid]) {
            low = mid+1;
        }
        else {
            return mid;
        }
    }
    return low - 1;
}

int main()
{
    long i;
    cin >> N;
    for (i=0; i<N; i++) {
        cin >> credits[i];
    }
    int length = 0;
    long position;
    for (i=0; i<N; i++) {
        if (i == 0) {
            helper1.push_back(credits[i]);
            length++;
            aleft[i] = length;
        }
        else {
            position = binary_search_low(credits[i], helper1, length);
            //cout << helper1[position] << endl;
            if (position == length - 1)  {
                if (credits[i] > helper1[position]) {
                    length++;
                    helper1.push_back(credits[i]);
                }
                aleft[i] = length;

            }
            else if (position != length - 1) {
                if ((credits[i] < helper1[position+1]) && (credits[i] != helper1[position])) {
                    helper1[position+1] = credits[i];
                }
                aleft[i] = length;
            }
        }
    }
    length = 0;
    for (i=N-1; i>=0; i--) {
        if (i == N-1) {
            helper2.push_back(credits[i]);
            length++;
            aright[i] = length;
        }
        else {
            position = binary_search_high(credits[i], helper2, length);
            if (position == length - 1) {
                if (credits[i] < helper2[position]) {
                    length++;
                    helper2.push_back(credits[i]);
                }
                aright[i] = length;
            }
            else if (position != length - 1) {
                if ((credits[i] > helper2[position+1]) && (credits[i] != helper2[position])) {
                    helper2[position+1] = credits[i];
                }
                aright[i] = length;
            }
        }
    }
    long result, newres;
    for (i=-1; i<N; i++) {
        if (i == -1) {
            result = aright[0];
        }
        else if (i == N-1) {
            newres = aleft[N-1];
            if (newres > result) {
                result = newres;
            }
        }
        else {
            newres = aleft[i] + aright[i+1];
            if (newres > result) {
                result = newres;
            }
        }
        //cout << helper1[i] << endl;
        //cout << aright[i] << endl;

    }
    cout << result << endl;
    return 0;
}
