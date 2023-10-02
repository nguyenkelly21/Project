#include <iostream>
#include <fstream>
#include <vector>

int main() {

}

// merges busySchedule1 and busySchedule2: sorted by start time and replaces if there is any overlap
vector<string> mergedSchedule(vector<string> schedule1, vector<string> schedule2) {
    vector<string> merged;
    int i = 0;
    int j = 0;

    while (i < schedule1.size() && j < schedule2.size()) {
        if (schedule1[i] <= schedule2[j]) {
            merged.push_back(schedule1[i]);
            i++;
        } else {
            merged.push_back(schedule2[j]);
            j++;
        }
    }

    while (i < schedule1.size()) {
        merged.push_back(schedule1[i]);
        i++;
    }

    while (j < schedule2.size()) {
        merged.push_back(schedule2[j]);
        j++;
    }

    return merged;
}
