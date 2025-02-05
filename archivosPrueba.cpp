#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector> 
#include <string> 

using namespace std;

string texto;

string lineasPersonaVector[5];
/*
    lineaNombre pos=0
    lineaApellido pos=1
    lineaAcciones pos=2
    lineaBalota pos=3
    lineaDineroTotal pos=4
*/
string textoCambioTXT[5];


struct Persona{
    string nombre;
    string apellido;
    int ID;
    int Cantidad_Acciones = 0;
    bool balota = false;
    int dineroTotal = 0;
};

void mostrarPersonas(vector<Persona>& personas) {
    for (const auto& p : personas) {
        cout << p.ID << ". "<< p.nombre<<" "<< p.apellido<<", A="<< p.Cantidad_Acciones<<
        "Balota: "<< p.balota<< "$ "<< p.dineroTotal<< endl;
    }
    cout << endl;
}

bool stringABool(const string& str) {
    return str == "true";  // Retorna true si es "true", false en otros casos
}

int main(){
    vector<Persona> personas;
    //sirve pora meter informacion en elarchivo de texto
    ifstream archivoNombres ("documentoprueba.txt");
    ifstream archivoApellido ("documentoApellido.txt");
    ifstream archivoAcciones ("documentoAcciones.txt");
    ifstream archivoBalota ("documentoBalota.txt");
    ifstream archivoDineroTotal ("documentoDineroTotal.txt");
    // el ciclo es para que lea todas las lineas escritas en el archivo una debajo de otra
    int i=0;
    while (getline(archivoNombres,lineasPersonaVector[0]) && getline(archivoApellido,lineasPersonaVector[1]) && 
    getline(archivoAcciones,lineasPersonaVector[2]) && getline(archivoBalota,lineasPersonaVector[3]) && 
    getline(archivoDineroTotal,lineasPersonaVector[4])){
    personas.push_back({lineasPersonaVector[0],lineasPersonaVector[1],i+1,atoi(lineasPersonaVector[2].c_str()),
    stringABool(lineasPersonaVector[3]),atoi(lineasPersonaVector[4].c_str())});
    //CICLO PARA CAPTURAR CADA UNO DE LOS TEXTOS (prueba)
    //para que Posteriormente se modiquen (prueba)
    for (int j = 0; j < 5; j++){
        textoCambioTXT[j]=textoCambioTXT[j]+lineasPersonaVector[j]+"\n";
    }
    i++;
    //cout << personas[i].nombre<< endl; 
    }

//cout << texto << endl;
// sirve para eliminar cache del archivo
archivoNombres.close();
//cout << texto << endl;
//mostrarPersonas(personas);
/*
cout << textoCambioTXT[0];
cout << textoCambioTXT[1];
cout << textoCambioTXT[2];
cout << textoCambioTXT[3];
cout << textoCambioTXT[4];
*/
textoCambioTXT[0]

//aqui el ofstream es para meter informacion en el archivio txt que deseamos 
ofstream archivo2("documentoprueba.txt");
archivo2 << "Texto a ingresar en el archivo nuevo";

    system("pause");
}