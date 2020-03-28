#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
//las dimensiones de la matriz están hardcoded pq son variables globales

using namespace std;
unsigned t0, t1;
int m1[101][101];
string m2[402][402], m3[402][402];
string row[402], column[101];//los 1 son caminos posibles y los 0 barrera   
int checks[101][101];// en 0 signfica que no se ha visitado
int hilos,indexFila=-1, indexColumna=-1, ybuscado=-1,xbuscado=-1;
int contador=0;
bool fin =false;
//bool solver(int &, int &);

void solver(int y,int x){//255 es camino libre
  checks[y][x]=1;
  bool flag = false;
  if(y==100 && x>97 ){
    ybuscado=y;
    xbuscado=x;
  }else{
    if(x+1<=100 && !fin){//verificar que no se salga de los limites de la matriz
      if(checks[y][x+1]==0 && m3[y][x+1].compare("255")==0){//verificar que no se haya visitado la casilla. Mover una casilla a la derecha eje x
      if(contador<hilos){// si el número de hilos en uso es mejor que x, entonces se puede crear un hilo nuevo, si no se sigue el proceso por medio del mismo hilo
        contador++;
        thread t1(solver,y,x+1);
        t1.join();
        if(y==ybuscado && x+1==xbuscado){
          cout << y << " " << x << "\n";
          ybuscado=y;
          xbuscado=x;
        }
      }else{
        solver(y,x+1);
        if(y==ybuscado && x+1==xbuscado){
          cout << y << " " << x << "\n";
          ybuscado=y;
          xbuscado=x;
        }
      } 
         flag=true;
      }
    }
    if(x-1>=0 && !fin){//verificar que no se salga de los limites de la matriz
     if(checks[y][x-1]==0 && m3[y][x-1].compare("255")==0){//verificar que no se haya visitado la casilla. Mover una casilla a la izquierda eje x
     if(contador<hilos){
       contador++;
         thread t1(solver,y,x-1);
        
         t1.join();
          if(y==ybuscado && x-1==xbuscado){
            cout << y << " " << x << "\n";
            ybuscado=y;
            xbuscado=x;
          }
      }else{
        solver(y,x-1);
        if(y==ybuscado && x-1==xbuscado){
            cout << y << " " << x << "\n";
            ybuscado=y;
            xbuscado=x;
          }
      }
       flag=true;
      }
    }
    if(y+1<=100 && !fin){//verificar que no se salga de los limites de la matriz
     if(checks[y+1][x]==0 && m3[y+1][x].compare("255")==0){//verificar que no se haya visitado la casilla. Mover una casilla arriba eje y
     if(contador<hilos){
       contador++;
        thread t1(solver,y+1,x);
        t1.join();
         if(y+1==ybuscado && x==xbuscado){
            cout << y << " " << x << "\n";
            ybuscado=y;
            xbuscado=x;
        }
      }else{
        solver(y+1,x);
        if(y+1==ybuscado && x==xbuscado){
            cout << y << " " << x << "\n";
            ybuscado=y;
            xbuscado=x;
        }
      }
       flag=true;
     }
    }

    if(y-1>=0 && !fin){ //verificar que no se salga de los limites de la matriz
      if(checks[y-1][x]==0 && m3[y-1][x].compare("255")==0){//verificar que no se haya visitado la casilla. Mover una casilla abajo eje y
      if(contador<hilos){
        contador++;
        thread t1(solver,y-1,x);
        
        t1.join();
        if(y-1==ybuscado && x==xbuscado){
            cout << y << " " << x << "\n";
            ybuscado=y;
            xbuscado=x;
        }
      }else{
         solver(y-1,x);
         if(y-1==ybuscado && x==xbuscado){
            cout << y << " " << x << "\n";
            ybuscado=y;
            xbuscado=x;
          }
      }
       flag=true;
      }
    }
    if(!flag && !fin){//cuando se "muere un hilo"
      contador--;
    }
}

}

bool comparador(){
  if(indexFila==-1){
      indexFila++;
      return false;
  }else{
    int ii=0;
      while(ii<402){
        if(!(row[ii].compare(m2[indexFila][ii])==0)){
            indexFila++;
            return false;
        }
        ii++;
      }
      return true;
  }
}
bool comparadorColumna(){
if(indexColumna==-1){
      indexColumna++;
      return false;
  }else{
    int ii=0;
      while(ii<101){
        if(!(column[ii].compare(m3[ii][indexColumna])==0)){
            indexColumna++;
            return false;
        }
        ii++;
      }
      return true;
  }
}

void insertar(){
  int ii=0;
  while(ii<402){
    m2[indexFila][ii]=row[ii];
    ii++;    
  }
}
void insertarm3(){
  int ii=0;
  while(ii<101){
    m3[ii][indexColumna]=column[ii];
    ii++;
  }
}

void recorteHorizontal(){
  int ii=0,jj;
  while(ii<402){
    jj=0;
    while(jj<101){
      column[jj]=m2[jj][ii];
      jj++;
    }
    if(!comparadorColumna()){
        insertarm3();
      }
    ii++;
  }
}
void recorteVertical(){
  ifstream myinfile;
  myinfile.open("mapadeprueba.txt",ios::in);
  string line;
  int i=0;
  //loop through myinfile while line exist
  while(getline(myinfile,line))
  {
      row[i]=line;
      i++;
      if(i==402){
        if(!comparador()){
          insertar();
        }
        i=0;
      }
  };
  myinfile.close();
  recorteHorizontal(); 
}


int main() 
{
  recorteVertical();
  /*int i=0;
  int j;
  string hc ="0";
  ofstream myoutfile("resultado.txt");
  while(i<101){
    j=0;
    while(j<101){
      if(j==0){
         myoutfile << hc << "\n";
      }else{
        myoutfile << m3[i][j-1] << "\n";
      }
      j++;
    }
    i++;
  }
  i=0;
  myoutfile.close();*/
  int i,j;
  cout << "Inserta el número de hilos: ";
  cin >> hilos;
  i=0;
  cout <<"----------------------------------------------------------------------------------------------" <<"\n";
  t0=clock();
  solver(0,1);
  t1=clock();
  /*i=0,j=0;
  while(i<101){
    j=0;
    while(j<101){
      if(checks[i][j]==1){
        cout << "o";
      }else{
        cout << "x";
      }
      j++;
    }
    cout << "\n";
    i++;
  }*/
  double time = (double(t1-t0)/CLOCKS_PER_SEC);
cout << "Execution Time: " << time << endl;
  cout <<"----------------------------------------------------------------------------------------------" <<"\n";
}
