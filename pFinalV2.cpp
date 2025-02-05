#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string> 
#include <vector>   //para poder crear la lista de personas y guardarlo en un vector
#include <random>   //para sacar el numero aleatorio de la balota

using namespace std;

//LINEAS PARA LEER LOS ARCHIVOS TXT
string lineasPersonaVector[5];
/*
    lineaNombre pos=0
    lineaApellido pos=1
    lineaAcciones pos=2
    lineaBalota pos=3
    lineaDineroTotal pos=4
*/
// Vector donde guardamos los datos en el formato de txt (en salto de lineas)
string textoCambioTXT[5];

//variable que se usa como semilla para Generar numeros aleatorios
random_device rd;

int VALOR_ACCION = 10000;
int VALOR_BALOTA = 5000;

struct Persona{
    string nombre;
    string apellido;
    int ID;
    int Cantidad_Acciones = 0;
    bool balota = false;
    int dineroTotal = 0;
};

// Función para mostrar la lista de Personas
void mostrarPersonas(vector<Persona>& personas) {
    for (const auto& p : personas) {
        if(p.balota){
            cout << "ID: "<< p.ID << ", " << p.nombre << ", Acciones: (" << p.Cantidad_Acciones <<
            ") | Fondos: $ "<< p.dineroTotal<< " -- Ganador Balota ✓"<< endl;
        } else {
            cout << "ID: "<< p.ID << ", " << p.nombre << ", Acciones: (" << p.Cantidad_Acciones <<
            ") | Fondos: $ "<< p.dineroTotal<< endl;
        }
        
    }
    cout << endl;
}

// Función para mostrar La persona Por ID
void mostrarPersonaID(vector<Persona>& personas, int ID) {
    for (const auto& p : personas) {
        if (p.ID == ID) {
            cout << "ID: "<< p.ID << ", " << p.nombre << ", Acciones Totales: " << p.Cantidad_Acciones <<
            " | Saldo: "<< p.dineroTotal<< endl;
            return;
        }
    }
        cout << "Persona no encontrada.\n";
}

//PEDIR LOS DATOS PARA MOSTRAR UNA PERSONA POR ID 
// Retorna el Id Valido
int pedirIDPersona(){
    int IDpersona;
    do{
        cout << "Digite el ID de la persona"<< endl;
        cin >> IDpersona;
    }while(IDpersona<0 || IDpersona>23);
    return IDpersona;
}

//PEDIR CANTIDAD DE ACCIONES PARA AGREGAR
// Retorna la cantidad de acciones INT
int pedirCantidadAcciones(){
    int cantidadAcciones;
    do{
        cout << "Digite la cantidad de Acciones a agregar: MAX(5) "<< endl;
        cin >> cantidadAcciones;
    }while(cantidadAcciones<1 || cantidadAcciones>5);
    return cantidadAcciones;
}


// Función para agregar acciones(VALOR) a una persona específica segun su ID
void agregarAcciones(vector<Persona>& personas, const int ID, int cantidad) {
    for (auto& p : personas) {
        if (p.ID == ID) {
            p.Cantidad_Acciones += cantidad;
            p.dineroTotal += p.Cantidad_Acciones*VALOR_ACCION;
            cout << "Se agregaron " << cantidad << " acciones a " << p.nombre << ".\n\n";
            return;
        }
    }
    cout << "Persona no encontrada.\n";
}


// ME RETORNA EL ID DEL GANADOR DE LA BALOTA
int numeroBalotaGanador(vector<Persona>& personas){
    srand(rd());
    if (personas.empty()) return -1; // En caso de que no haya personas

    int ganadorID;
    bool encontrado = false;

    while (!encontrado) {
        int indice = rand() % personas.size(); // Genera un índice aleatorio
        if (!personas[indice].balota) {
            personas[indice+1].balota = 1; // Marcar como ganador
            ganadorID = personas[indice].ID;
            encontrado = true;
        }
    }
    return ganadorID;
}

//FUNCION SUMAR BALOTA DE HOY DEVUELVE LA FRASE DONDE DICE CUAL ES EL GANADOR
void MostrarganadorBalotaSumaCuenta(vector<Persona>& personas){
    int posicionGanador = numeroBalotaGanador(personas);
    // SE LE VA A DAR 
    personas[posicionGanador].dineroTotal += (VALOR_BALOTA*23)/2;
    string fraseGanador = "El ganador de la Balota de hoy es el N("+ to_string(personas[posicionGanador].ID) +") - "+
    personas[posicionGanador].nombre+" "+personas[posicionGanador].apellido +"\n\n";
    cout << posicionGanador<<endl;
    cout << fraseGanador << endl;
}

//FUNCION QUE PASA UN STRUNG A BOOL (ES para transformarlo al leer el archivo)
bool stringABool(const string& str) {
    return str == "1";  // Retorna true si es "1", false en otros casos
}

int main(){
    //BASE DE DATOS PROVISIONAL
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
        // Vamos a agregar a cada persona en el vector personas con la informacion que sacamos de los archivos TXT
        personas.push_back({lineasPersonaVector[0],lineasPersonaVector[1],i+1,atoi(lineasPersonaVector[2].c_str()),
        stringABool(lineasPersonaVector[3]),atoi(lineasPersonaVector[4].c_str())});
        //CICLO PARA CAPTURAR CADA UNO DE LOS TEXTOS (prueba)
        //para que Posteriormente se modiquen (prueba)
        for (int j = 0; j < 5; j++){
            textoCambioTXT[j]=textoCambioTXT[j]+lineasPersonaVector[j]+"\n";
        }
        i++;
    }
    //Cerramos los archivos para evitar errores
    archivoNombres.close();
    archivoApellido.close();
    archivoBalota.close();
    archivoAcciones.close();
    archivoDineroTotal.close();

    int opcion;
    do{
        cout << "Menú de opciones:\n";
        cout << "1. Mostrar Banco Completo\n";
        cout << "2. Mostrar cuenta de una Persona\n";
        cout << "3. Jugar la Balota\n";
        cout << "4. Agregar Acciones a una persona\n";
        cout << "0. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\nMostrando Banco Completo.\n\n";
                    mostrarPersonas(personas);
                break;
            case 2:
                cout << "\nMostrando la cuenta.\n\n";
                    mostrarPersonaID(personas,pedirIDPersona());
                break;
            case 3: 
                cout << "\nVMAOS A JUGAR LA BALOTA!!!\n";
                    MostrarganadorBalotaSumaCuenta(personas);
                break;
            case 4:
                cout << "\nVamos a agregar acciones a una cuenta.\n\n";
                    agregarAcciones(personas,pedirIDPersona(),pedirCantidadAcciones());
                    cout << "Acciones agregadas exitosamente\n\n";
                break;
            case 0:
                cout << "\nSaliendo del programa...\n\n";
                break;
            default:
                cout << "\nOpción no válida. Intente de nuevo.\n\n";
                break;
        }
    }while(!opcion==0);

    string textoAcciones;
    string textoBalota;
    string textoDineroTotal;
    for (const auto& p : personas) {
        textoAcciones += to_string(p.Cantidad_Acciones)+"\n";
        textoBalota += to_string(p.balota)+"\n";
        textoDineroTotal += to_string(p.dineroTotal)+"\n";
    }

    //aqui el ofstream es para meter informacion en el archivio txt que deseamos 
    ofstream archivoAccionesMOD("documentoAcciones.txt");
    archivoAccionesMOD << textoAcciones;
    archivoAccionesMOD.close();
    ofstream archivoBalotaMOD("documentoBalota.txt");
    archivoBalotaMOD << textoBalota;
    archivoBalotaMOD.close();
    ofstream archivoDineroTotalMOD("documentoDineroTotal.txt");
    archivoDineroTotalMOD << textoDineroTotal;
    archivoDineroTotalMOD.close();

    return 0;
}