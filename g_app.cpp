#include "movieStruct.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "quickSortMovies.cpp"

using namespace std;


// each movie node will save name, location, date, and kind
movieNode* makeMovieNode(string line){
  string name;
  string location;
  int date;
  string kind;
  string dateTemp;
  int dashCounter=0;
  for(int i = 0; i < line.length();i++){
    if(line[i]=='-'){
      dashCounter++;
      continue;
    } else if(dashCounter==0){// saving name
      name+=line[i];
    } else if(dashCounter==1){// saving location
      location+=line[i];
    } else if(dashCounter==2){// saving date
      dateTemp+=line[i];
      date = stoi(dateTemp);
    } else if(dashCounter==3){// saving kind
      kind+=line[i];
    }
  }

  return new movieNode(name,location,date,kind);
}

string toLower(string movie){
  for(int i = 0;i<movie.length();i++){
    if(movie[i] >='A'&&movie[i]<='Z'){
      movie[i] = static_cast<char>(movie[i]+32);
    }
  }
  return movie;
}

void findMovie(vector<movieNode *>movies,string movie){
  bool movieFound = false;
  int movieCount = 0;
  string moviecopy;
  cout << endl;

  cout << "===========================================================" << endl;
  cout << "=                       Movie Search                      =" << endl;
  cout << "===========================================================" << endl;
  for(int i=0; i < movies.size();i++){
    moviecopy=movies[i]->name;
    if(toLower(moviecopy)==toLower(movie)){
      movieCount++;
      cout << movieCount << ". " << movies[i]->name << endl;
      cout << "   " << "location: " << movies[i]->location << endl;
      cout << "   " << "release date: " << movies[i]->date << endl;
      string type;
      if(movies[i]->kind=="S"){
        type = "Standard";
      } else {
        type = "Blue-ray";
      }
      cout << "   " << "type: " << type << endl;
      movieFound = true;
    }
  }
  if(!movieFound){
    cout<<"=                      Movie not found                    ="<<endl;
  }
  cout << "===========================================================" << endl;
}

void displayMenu(){
  cout << endl;
  cout << "===========================================================" << endl;
  cout << "=                    Grandpa's Movies                     =" << endl;
  cout << "===========================================================" << endl;
  cout << "=                (1)  search for a movie                  =\n";
  cout << "=                (2)  sort movies                         =\n";
  cout << "=                (-1) end program                         =\n";
  cout << "===========================================================\n";
}

void displayEndProgram(){
  cout << "===========================================================\n";
  cout << "=                       Program Ended                     =\n";
  cout << "===========================================================\n";
}

void displaySortMenu(){
  cout << "===========================================================\n";
  cout << "=                      Sort Movies                        =\n";
  cout << "===========================================================\n";
  cout << "=           (1)  Sort alphabetically A-Z                  =\n";
  cout << "=           (2)  Sort alphabetically Z-A                  =\n";
  //cout << "=        (3)  Sort by release date (least to greatest)  =\n";
  //cout << "=        (4)  Sort by release date (greatest to least)  =\n";
  cout << "=           (0)  Return to main menu                       =\n";
  cout << "===========================================================\n";
}

void displaySearchMovie(){
  cout << "===========================================================\n";
  cout << "= Enter a movie to search for (enter 0 to return to menu) =\n";
  cout << "===========================================================\n";
}

int main(){
  fstream moviesTxt;
  vector<movieNode *> movies;
  string line;

  moviesTxt.open("g_movies.txt");// opening file and gettig each line
  if(moviesTxt.is_open()){
    while ( getline (moviesTxt,line) ){
      movieNode* newMovie = makeMovieNode(line);
      movies.push_back(newMovie);
    }
    moviesTxt.close();
  } else {
    cout << " Unable to open file\n";
  }

  QSort qsort;
  string input;
  while(input!="-1"){
    displayMenu();
    cout << ">";
    getline(cin,input);

    if(input == "-1"){
      displayEndProgram();
      break;
    } else if(input == "1"){
      displaySearchMovie();
      cout << ">";
      getline(cin,input);
      if(input == "0"){
        continue;
      } else {
        findMovie(movies,input);
        cout << "Press enter to continue: ";
        cin.ignore();
      }
    } else if(input == "2"){
      displaySortMenu();
      cout << ">";

      getline(cin,input);
      if(input == "1"){
        qsort.displayMovies(movies,1);
      } else if (input == "2"){
        qsort.displayMovies(movies,0);
      } else if (input == "0"){
        continue;
      } else {
        cout << "Incorrect input" << endl;
        cout << "Press enter to continue: ";
        cin.ignore();
      }
    }
    cout << endl;
  }

  for(auto n:movies){
    delete n;
  }
  movies.clear();
  return 0;
}
