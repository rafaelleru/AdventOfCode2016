#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>     /* atoi */

using namespace std;

struct step{
  string content;
};

void readPath(vector<step>& path){
  ifstream input("input");

  //leemos hasta cada  ","
  char r[32];
  char c;
  step aux;
  while(input.get(c)){ //Leemos de char en char (No se si es lo mejor)
    if(c == ','){
      path.push_back(aux);
    }

    if(c == ' '){ //El espacio indica un nuevo 'step'
      aux.content.clear();
    }else //almacenamos el nuevo char que compone el 'step'
      aux.content.push_back(c);
  }

  if(input.eof()){ //El ultimo tambien hay que almacenarlo
    path.push_back(aux);
  }
}

int taxicabGrometry(pair<int, int> finalPos){
  return abs(0 - finalPos.first) + abs(0 - finalPos.second); //Calculamos la discancia manhattan entre 0,0  y finalPos
};

pair<int, int> getFinalCoordinates(vector<step>& path){
  int orientation = 0;
  pair<int, int> pos;
  pos.first = pos.second = 0;

  for(vector<step>::iterator it = path.begin(); it != path.end(); ++it){
    if((*it).content[0] == 'R'){
      orientation++;
      if(orientation == 4) //Si la orientacion es 4 mira al norte, lo cual es 0
	orientation = 0;
    }else if((*it).content[0] == 'L'){
      orientation--;
      if(orientation < 0) //Orientacion negatica indica que esta al oeste.
	orientation = 3;
    }

    string steps_c;
    steps_c = (*it).content.substr(1, (*it).content.size());

    int nSteps = atoi(steps_c.c_str());
    cout << "Me muevo " << nSteps << " hacia la: " << endl;
    for(int i = 0; i < nSteps; ++i){
      switch (orientation) {
      case 0: {
	cout << "Norte" << endl;
	pos.first++;
	break;
      }

      case 1: {
	cout << "Este" << endl;
	pos.second++;
	break;
      }

      case 2: {
	cout << "Sur" << endl;
	pos.first--;
	break;
      }

      case 3: {
	cout << "Oeste" << endl;
	pos.second--;
	break;
      }
      }
    }
  }

  return pos;
};

int main(){
  //En primer lugar abrimos el archivo que contiene las coordenadas que tenemos que avanzar.
  vector<step> path;
  readPath(path);
  pair<int, int> finalPos = getFinalCoordinates(path);

  cout << "x: " << finalPos.first << " y: " << finalPos.second << endl;
  cout << "taxicabGeometry distance: " << taxicabGrometry(finalPos) << endl;
  
}
