#include "movieStruct.h"
#include <iostream>
#include <vector>
#include <string>

// #include "g_app.cpp"

using namespace std;

class QSort {
private:
  void azza(bool b){

  }
  bool compareTitles(movieNode *a,movieNode *b,bool az){
    if(az){ // if az- input equal true
      return a->name<b->name;
    }
    return a->name>b->name;
  }
  void swap(vector<movieNode *> &vec, int l, int r){
    auto temp = vec[r];
    vec[r]=vec[l];
    vec[l]=temp;
  }

  int partition(vector<movieNode *> &vec, int left, int right,bool az){
    int pivot = (left+right)/2;

    swap(vec,pivot,right);// swapping pivot with the right end of vec

    int i = left;// making counter for left side
    int j = right-1;// making counter for right side excluding the pivot we moved to end
    while(i<=j){
      while(compareTitles(vec[i],vec[right],az)){// moving left counter till we find a number that is greater with our pivot
        i++;
      }
      while(!compareTitles(vec[j],vec[right],az)){// moving right counter till we find a number that is less than our pivot
        j--;
      }
      if(i<j){ // it is possible that both counters have crossed. So we make sure they didnt. If they are less than eachother then we swap positions within vec
      //cout <<"swapped"<<endl;
        swap(vec,i,j);
        i++;// increase left counter
        j--;// decrease right counter
      }
    }
    swap(vec,right,i);// we swap the pivot(was at right end of vec) with our left counter
    cout << endl;
    return i; // we return position of the left counter
  }

  void quickSort(vector<movieNode *> &vec, int l, int r,bool az){
    if(l<r){
      int pivot = partition(vec, l, r,az);
      quickSort(vec, l, pivot-1,az);// we start off with the left side
      quickSort(vec, pivot+1, r,az);// then we move to the right side
    }
  }
  void displayMovies2(vector<movieNode *> movies){
    for(int i = 0; i < movies.size(); i++){
      cout << i+1 << ". title: " << movies[i]->name << endl;
      cout << "      " << "location: " << movies[i]->location << endl;
      cout << "      " << "release date: " << movies[i]->date << endl;
      string type;
      if(movies[i]->kind=="S"){
        type = "Standard";
      } else {
        type = "Blue-ray";
      }
      cout << "      " << "type: " << type << endl;
      cout << endl;
    }
  }
public:
  QSort(){

  }
  void displayMovies(vector<movieNode *> &vec, bool az){
    quickSort(vec,0,vec.size()-1,az);
    displayMovies2(vec);
  }
};
