#include <iostream>
using namespace std;

int main() {
    int distance = 0,
        arraySt[] = {-1, 5},
        arrayNd[] = {26, 6};

    for(int tempSt : arraySt) {
        for(int iNd : arrayNd) {
            int tempNd = iNd, tempDistance;
            if(tempSt >= tempNd) {
                tempDistance = tempSt - tempNd;
            } else {
                tempDistance = tempNd - tempSt;
            }
            if(distance == 0 || distance > tempDistance) {
                distance = tempDistance;
            }
        }
    }
    cout << distance << endl;
    return 0;
}
