#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
using namespace std;

int hourToMinute(string times){
  std::stringstream conversion(times);
  int hour, minute;
  char holder;
  conversion >> hour >> holder >> minute;
  int new_time = hour*60 + minute;
  return new_time;
}

string minuteToString(int times){
  string new_time;
  int hour = times/60;
  int minute = times%60;
  string hour1 = to_string(hour);
  string minute1 = to_string(minute);
  if(minute < 10){
      minute1 = "0" + minute1;
  }
  new_time = hour1 + ":" + minute1;
  return new_time;
}

vector<string> stringToVector(string schedule){
    vector<string> v;
    istringstream iss(schedule);
    string temp;
    while (std::getline(iss, temp, ',')) {
        v.push_back(temp);
    }
    return v;
}

string remove_character(string schedule){
    int i = 0;
    while(i < schedule.size()) {
        if(schedule[i] == '[' || schedule[i] == ']' || schedule[i] == '\'') {
            schedule.erase(i,1);
        } else{
            i++;
        }
    }
    return schedule;
}

int main() {
  ifstream file("input.txt");
  ofstream output("output.txt");
  string person1_busy_Schedule, person1_work_hours, person2_busy_Schedule, person2_work_hours;
  int duration_of_meeting;
  while(!file.eof()) {
    file >> person1_busy_Schedule >> person1_work_hours >> person2_busy_Schedule >> person2_work_hours >> duration_of_meeting;
    person1_busy_Schedule = remove_character(person1_busy_Schedule);
    person1_work_hours = remove_character(person1_work_hours);
    person2_busy_Schedule = remove_character(person2_busy_Schedule);
    person2_work_hours = remove_character(person2_work_hours);

    vector<string> person1 = stringToVector(person1_busy_Schedule);
    vector<string> person2 = stringToVector(person2_busy_Schedule);
    vector<string> hour1 = stringToVector(person1_work_hours);
    vector<string> hour2 = stringToVector(person2_work_hours);
      
    int sizes = person1.size() + person2.size();
    for(int i = 0; i < person1.size(); i++){
      person2.push_back(person1[i]);
    }

    vector<int> minutes;
    for(int i = 0; i<person2.size(); i++){
      minutes.push_back(hourToMinute(person2[i]));
    }
    
    int colum = minutes.size()/2;
    vector<vector<int>> combined(colum, vector<int>(2));
    int index1 = 0;
    for(int row = 0; row < combined.size(); ++row){
      for(int col = 0; col < combined[row].size(); ++col){
        if(index1 < minutes.size()){
          combined[row][col]= minutes[index1];
          index1++;
        }
      }
    }
    sort(combined.begin(), combined.end());
    vector<int> new_hour; //holds least and most time free
    if(hour1[0] > hour2[0]){
        new_hour.push_back(hourToMinute(hour1[0]));
    } else{
        new_hour.push_back(hourToMinute(hour2[0]));
    }
    if(hour1[1] < hour2[1]){
      new_hour.push_back(hourToMinute(hour1[1]));
    } else{
      new_hour.push_back(hourToMinute(hour2[1]));
    }
    int start = new_hour[0];
    int end = new_hour[1];

    std::vector<std::pair<string, string>> free_time;
    
    for (const auto& a : combined) {
        while((start + duration_of_meeting) <= a[0]){
          free_time.push_back({minuteToString(start), minuteToString(start+duration_of_meeting)});
          start = start + duration_of_meeting;
        } 
        start = a[1];
    }
    
    while((start + duration_of_meeting) <= end){
        free_time.push_back({minuteToString(start), minuteToString(start+duration_of_meeting)});
        start = start + duration_of_meeting;
    } 

    
    output <<"[";
    for(int i = 0; i < free_time.size(); i++){
        output << "[" <<free_time[i].first<<","<<free_time[i].second<<"], ";
    }
    output <<"]" << endl;
  }
  return 0;
}
