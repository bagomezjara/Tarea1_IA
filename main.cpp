#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <time.h>
#include <queue>
#include <climits>

using namespace std;

int costo=0;//valor costo camino
map<string,vector<pair<string, int>>> grafo;// mapa de grafo, no inclulle las heuristicas
map<string,int> heuristica;// mapa de las heuristicas


void BusquedaProf(map<string,vector<pair<string, int>>> grafo, string init, string dest){//algoritmo de busqueda en profundidad
    srand(time(NULL));//la seed del rand
    vector<string> camino;//se crea el camino
    map<string,int> expandido;// mapa donde se guardan los datos de expancion
    map<string,int> visitado;// mapa donde se guardan los datos sobre los nodos visitados
    string actual=init;//se pasa el string inicial al string actual
    visitado[actual]=1;// se marca el nodo actual como visitado
    camino.push_back(actual);// se añade el nodo actual al camino

    while(actual!=dest){//ciclo while que itera mientras el nodo actual no sea el final
        expandido[actual]+=1;// se aumenta el numero de expansiones para el nodo actual
        int index=rand()%grafo[actual].size();//se genera un numero aleatorio para escoger un hijo al azar
        string aux=grafo[actual][index].first;// se busca el nodo hijo seleccionado al azar y se guarda en un string

        if(visitado[aux]!=1){//si es que el nodo escogido no a sido visitado, continua
            costo+=grafo[actual][index].second;// se aumenta el costo del camino
            actual=aux;//el string actual toma el valor de nodo escogido
            visitado[aux]=1;// se marca el nodo escogido como visitado
            camino.push_back(actual);// se ingresa el nodo escogido al camino
        }
    }

    //se imprime el output
    for(auto i=camino.begin();i!=camino.end();i++){
        cout<<*i<< "->";
    }
    cout<<endl;
    cout<<"Costo:"<<costo<<endl;
    map<string, int>::iterator it;
    for(it=expandido.begin();it!=expandido.end();it++){
        cout<<it->first<<":"<<it->second<<endl;
    }
    costo=0;// se devuelve el valor de costo a 0
    return;
}

void BusquedaGreedy(map<string,vector<pair<string, int>>>, string init, string dest,map<string,int> heuristica){
    vector<string> camino;//se crea el camino
    map<string,int> expandido;// mapa donde se guardan los datos de expancion
    map<string,int> visitado;// mapa donde se guardan los datos sobre los nodos visitados
    string actual=init;//se pasa el string inicial al string actual
    visitado[actual]=1;// se marca el nodo actual como visitado
    camino.push_back(actual);// se añade el nodo actual al camino
    string aux;

    while(actual!=dest){//ciclo while que itera mientras el nodo actual no sea el final
        int m=INT_MAX;//como tratamos de minimizar, usaremos el int maximo
        int auxi;//se crea un index para iterar en el vector del mapa
        expandido[actual]+=1;// se aumenta el numero de expansiones para el nodo actual
        for(int i=0; i<grafo[actual].size();i++){//recorremos todos los hijos de nodo actual

            if(heuristica[aux]< m){//si la heuristica del nodo es menor que el valor min almacenado actualmente
                m=heuristica[aux];//actualizamos el valor de m con la heuristica del nodo escogido
                aux=grafo[actual][i].first;// se busca a uno de los hijos y se guarda
                auxi=i;// tomamos el index del vector y lo guardamos
            }
        }
        if(visitado[aux]!=1){//si es que el nodo escogido no a sido visitado, continua
            costo+=grafo[actual][auxi].second;//agregamos el costo del camino
            actual=aux;//el string actual toma el valor de nodo escogido
            camino.push_back(actual);// se ingresa el nodo escogido al camino
            visitado[actual]=1;// se marca el nodo actual como visitado
        }
    }


    //se imprime el output
    for(auto i=camino.begin();i!=camino.end();i++){
        cout<<*i<< "->";
    }
    cout<<endl;
    cout<<"Costo:"<<costo<<endl;
    map<string, int>::iterator it;
    for(it=expandido.begin();it!=expandido.end();it++){
        cout<<it->first<<":"<<it->second<<endl;
    }
    costo=0;
    return;
}

void BusquedaUniforme(map<string,vector<pair<string, int>>>, string init, string dest){
    vector<string> camino;//se crea el camino
    map<string,int> expandido;// mapa donde se guardan los datos de expancion
    map<string,int> visitado;// mapa donde se guardan los datos sobre los nodos visitados
    priority_queue<pair<string, int>,vector<pair<string, int>>,greater<pair<string, int>>> prio;// se crea una priority queue de menor a mayor
    string actual=init;//se pasa el string inicial al string actual
    int pcosto=0;// se crea una variable entera par guardar el costo acumulado
    prio.push(make_pair(actual,pcosto));// se ingresa el primer nodo a la queue

    while(!prio.empty()){// se itera hasta que la queue este vacia
        string aux=prio.top().first;//actuaizamos el string del nodo
        pcosto=prio.top().second;// actualizamos el costo acumulado
        prio.pop();// se quita el nodo de mayor valor de la queue

        if(aux==dest){// si el nuevo nodo es el final, el algoritmo termina
            camino.push_back(aux);// se ingresa el nodo escogido al camino
            break;
        }else{
            for(int i=0; i<grafo[aux].size();i++){//recorremos todos los hijos de nodo actual
                if(visitado[aux]!=1){//si es que el nodo escogido no a sido visitado, continua
                    costo+=grafo[aux][i].second;//agregamos el costo del camino
                    expandido[aux]+=1;// se aumenta el numero de expansiones para el nodo actual
                    camino.push_back(aux);// se ingresa el nodo escogido al camino
                    visitado[aux]=1;// se marca el nodo actual como visitado
                    prio.push(make_pair(grafo[aux][i].first,pcosto+grafo[aux][i].second));// hacemos push del nuevo nodo con el costo acumulado
                }
            }
        }
    }

    //se imprime el output
    for(auto i=camino.begin();i!=camino.end();i++){
        cout<<*i<< "->";
    }
    cout<<endl;
    cout<<"Costo:"<<costo<<endl;
    map<string, int>::iterator it;
    for(it=expandido.begin();it!=expandido.end();it++){
        cout<<it->first<<":"<<it->second<<endl;
    }
    costo=0;
    return;
}

void BusquedaA(map<string,vector<pair<string, int>>>, string init, string dest,map<string,int> heuristica){
    vector<string> camino;//se crea el camino
    map<string,int> expandido;// mapa donde se guardan los datos de expancion
    map<string,int> visitado;// mapa donde se guardan los datos sobre los nodos visitados
    priority_queue<pair<string, int>,vector<pair<string, int>>,greater<pair<string, int>>> prio;// se crea una priority queue de menor a mayor
    string actual=init;//se pasa el string inicial al string actual
    map<string,int> nodoacumulado;// se crea un mapa para asociarle un valor acumulado a cada nodo
    int pcosto=0;// se crea una variable entera par guardar el costo acumulado
    prio.push(make_pair(actual,pcosto));// se ingresa el primer nodo a la queue

    while(!prio.empty()){// se itera hasta que la queue este vacia
        string aux=prio.top().first;//actuaizamos el string del nodo
        pcosto=nodoacumulado[aux];// actualizamos el costo acumulado
        prio.pop();// se quita el nodo de mayor valor de la queue

        if(aux==dest){// si el nuevo nodo es el final, el algoritmo termina
            camino.push_back(aux);// se ingresa el nodo escogido al camino
            break;
        }else{
            for(int i=0; i<grafo[aux].size();i++){//recorremos todos los hijos de nodo actual
            if(visitado[aux]!=1){//si es que el nodo escogido no a sido visitado, continua
                    costo+=grafo[aux][i].second;//agregamos el costo del camino
                    expandido[aux]+=1;// se aumenta el numero de expansiones para el nodo actual
                    camino.push_back(aux);// se ingresa el nodo escogido al camino
                    visitado[aux]=1;// se marca el nodo actual como visitado
                    nodoacumulado[grafo[aux][i].first]=pcosto+grafo[aux][i].second;// le damos el valor acumulado del costo mas el costo acumulado al nodo
                    prio.push(make_pair(grafo[aux][i].first,heuristica[aux]+nodoacumulado[grafo[aux][i].first]));// hacemos push del nuevo nodo con el valor acumulado mas el valor de su heuristica
                }
            }
        }
    }

    //se imprime el output
    for(auto i=camino.begin();i!=camino.end();i++){
        cout<<*i<< "->";
    }
    cout<<endl;
    cout<<"Costo:"<<costo<<endl;
    map<string, int>::iterator it;
    for(it=expandido.begin();it!=expandido.end();it++){
        cout<<it->first<<":"<<it->second<<endl;
    }
    costo=0;
    return;
}

int main(){
    string nombre;
    int optimo=18;

    cout<<"Ingrese el nombre del archivo que desea ingresar:"<<endl;
    cin>>nombre;

    ifstream file(nombre);
    string contenido;
    int cont=0;
    string init,dest;

    while(file>>contenido){

        if(cont==1){
            init=contenido;
        }else if(cont==3){
            dest=contenido;
        }

        int coma=0;

        for(int i=0;i<contenido.size();i++){
            if(contenido[i]==',')
                coma=1;
        }
        /*if(coma==1){
            contenido[1]=='\n';
            a==contenido[0];
        }*/
        cont++;
    }
    cout <<"init:"<< init << endl;
    cout <<"dest:"<< dest << endl;

    heuristica.insert({"A",10});
    heuristica.insert({"B",7});
    heuristica.insert({"C",10});
    heuristica.insert({"D",3});
    heuristica.insert({"E",1});
    heuristica.insert({"F",2});
    heuristica.insert({"G",2});
    heuristica.insert({"H",0});

    vector<pair<string, int>> a,b,c,d,e,f,g,h;
    pair<string, int> a1,a2,b1,b2,c1,c2,d1,e1,f1,g1;
    a1=make_pair("B",11);
    a2=make_pair("C",6);
    b1=make_pair("D",4);
    b2=make_pair("E",3);
    c1=make_pair("F",3);
    c2=make_pair("E",10);
    d1=make_pair("H",3);
    e1=make_pair("H",5);
    f1=make_pair("G",1);
    g1=make_pair("E",4);

    a.push_back(a1);
    a.push_back(a2);
    b.push_back(b1);
    b.push_back(b2);
    c.push_back(c1);
    c.push_back(c2);
    d.push_back(d1);
    e.push_back(e1);
    f.push_back(f1);
    g.push_back(g1);

    grafo.insert({"A",a});
    grafo.insert({"B",b});
    grafo.insert({"C",c});
    grafo.insert({"D",d});
    grafo.insert({"E",e});
    grafo.insert({"F",f});
    grafo.insert({"G",g});
    grafo.insert({"H",h});

    cout<<"Busqueda en Profundidad:"<<endl;
    BusquedaProf(grafo, init, dest);
    cout<<"Busqueda Greedy:"<<endl;
    BusquedaGreedy(grafo, init, dest, heuristica);
    cout<<"Busqueda con Costo Uniforme:"<<endl;
    BusquedaUniforme(grafo, init, dest);
    cout<<"Busqueda A*:"<<endl;
    BusquedaA(grafo, init, dest, heuristica);
/*
    ifstream file(nombre);
    string line;

    getline(file, line);

    stringstream ss(line);

    string aux;

    ss >> aux;
    ss >> aux;

    getline(file, line);
    stringstream ss2(line);

    string aux2;

    ss2 >> aux2;
    ss2 >> aux2;

*/

    return 0;
}
