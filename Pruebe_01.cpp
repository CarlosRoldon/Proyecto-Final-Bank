#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string> 
#include <vector>   //para poder crear la lista de personas y guardarlo en un vector
#include <random>   //para sacar el numero aleatorio de la balota
#include <iomanip> // Para setw y left , para imprimir mejor el Banco
#include <ctime>    // Para srand()

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

//Estructura donde podemos guardar los datos de una persona
struct Persona{
    string nombre;
    string apellido;
    int ID;
    int Cantidad_Acciones = 0;
    bool balota = false;
    int dineroTotal = 0;
};

// Función para mostrar la lista de Personas
// Modificado para que se imprima de forma prolija
void mostrarPersonas(vector<Persona>& personas) {
    // Definimos los anchos de columna
    const int anchoID = 5;
    const int anchoNombre = 15;
    const int anchoAcciones = 10;
    const int anchoFondos = 12;
    
    // Encabezado
    cout << left << setw(anchoID) << "ID" << " | "
         << setw(anchoNombre) << "Nombre" << " | "
         << setw(anchoAcciones) << "Acciones" << " | "
         << setw(anchoFondos) << "Fondos" << " | "
         << "Estado" << endl;
    cout << string(50, '-') << endl;
    
    // Mostrar datos
    for (const auto& p : personas) {
        cout << left << setw(anchoID) << p.ID << " | "
             << setw(anchoNombre) << p.nombre << " | "
             << setw(anchoAcciones) << p.Cantidad_Acciones << " | "
             << "$" << setw(anchoFondos - 1) << fixed << setprecision(2) << p.dineroTotal << " | ";
        //Si ganó la balota lo mostramos
        if (p.balota) {
            cout << "Ganador Balota!";
        }
        cout << endl;
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
    //Ciclo para recorrer el vector personas
    for (auto& p : personas) {
        if (p.ID == ID) {
            //Entra al condicional si encontró el ID ingresado
            //Usamos acumuladores para sumar las acciones y el dinero total
            p.Cantidad_Acciones += cantidad;
            p.dineroTotal += p.Cantidad_Acciones*VALOR_ACCION;
            cout << "Se agregaron " << cantidad << " acciones a " << p.nombre << ".\n\n";
            return;
        }
    }
    cout << "Persona no encontrada.\n";
}


// ME RETORNA EL ID DEL GANADOR DE LA BALOTA (ALEATORIO)
int numeroBalotaGanador(vector<Persona>& personas){
    srand(time(nullptr)); // semilla para generar el numero aleatorio
    int ganadorID; // aqui vamos a guardar el ID del ganador
    bool encontrado = false; // boolean para saber si ya encontramos el ganador
    
    while (!encontrado) {
        int indice = (rand() % 23); // Genera un índice aleatorio entre 1 y 23
        if (!personas[indice+1].balota) {
            personas[indice+1].balota = true; // Marcar como ganador (+1 porque inicia desde 0)
            ganadorID = personas[indice].ID;
            encontrado = true;
        }
    }
    return ganadorID;
}

//FUNCION SUMAR BALOTA DE HOY DEVUELVE LA FRASE DONDE DICE CUAL ES EL GANADOR
void MostrarganadorBalotaSumaCuenta(vector<Persona>& personas){
    int posicionGanador = numeroBalotaGanador(personas);
    // Se le da la mitad e la valota en efectivo y la otra mitad va a su cuenta
    personas[posicionGanador].dineroTotal += (VALOR_BALOTA*23)/2;
    string fraseGanador = "El ganador de la Balota de hoy es el N("+ to_string(personas[posicionGanador].ID) +") - "+
    personas[posicionGanador].nombre+" "+personas[posicionGanador].apellido +"\n\n";
    //cout << posicionGanador<<endl;
    fraseGanador = "\033[33m"+fraseGanador+"\033[0m";
    //Imprimimos El ganador 
    cout << fraseGanador << endl;
}

//FUNCION QUE PASA UN STRUNG A BOOL (ES para transformarlo al leer el archivo)
bool stringABool(const string& str) {
    return str == "1";  // Retorna true si es "1", false en otros casos
}


//ESTA FUNCION REESCRIBE LOS ARCHIVOS CON LA NUEVA INFORMACION
void GuardarDatosEnTXT(vector<Persona>& personas){
    //Creamos los strings donde guardamos los textos correspondientes
    string textoAcciones;
    string textoBalota;
    string textoDineroTotal;
    //Ciclo donde vamos guardando los datos del vector de personas
    //lo guardamos en strings con sus saltos de linea
    for (const auto& p : personas) {
        textoAcciones += to_string(p.Cantidad_Acciones)+"\n";
        textoBalota += to_string(p.balota)+"\n";
        textoDineroTotal += to_string(p.dineroTotal)+"\n";
    }

    //aqui el ofstream es para meter informacion en el archivio txt que deseamos 
    ofstream archivoAccionesMOD("documentoAcciones.txt");
    //guardamos el texto con la informacion del programa en el TXT 
    archivoAccionesMOD << textoAcciones;
    // cerramos el archivo para evitar conflictos de entrada y salida
    archivoAccionesMOD.close();
    ofstream archivoBalotaMOD("documentoBalota.txt");
    archivoBalotaMOD << textoBalota;
    archivoBalotaMOD.close();
    ofstream archivoDineroTotalMOD("documentoDineroTotal.txt");
    archivoDineroTotalMOD << textoDineroTotal;
    archivoDineroTotalMOD.close();
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
    int i=0;
    // Este ciclo va a leer los archivos TXT y guardar la informacion en el vector de personas
    // Hasta que lleguemos a la ultima linea
    // personas.puch_back con esta linea llenamos cada
    while (getline(archivoNombres,lineasPersonaVector[0]) && getline(archivoApellido,lineasPersonaVector[1]) && 
        getline(archivoAcciones,lineasPersonaVector[2]) && getline(archivoBalota,lineasPersonaVector[3]) && 
        getline(archivoDineroTotal,lineasPersonaVector[4])){
        // Vamos a agregar a cada persona en el vector personas con la informacion que sacamos de los archivos TXT
        personas.push_back({lineasPersonaVector[0],lineasPersonaVector[1],i+1,atoi(lineasPersonaVector[2].c_str()),
        stringABool(lineasPersonaVector[3]),atoi(lineasPersonaVector[4].c_str())});
        //CICLO PARA CAPTURAR CADA UNO DE LOS TEXTOS 
        //para que Posteriormente se modiquen
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
    //EN ESTE PUNTO YA TENEMOS CARGADOS LOS DATOS DEL TXT
    //INICIO DEL PROGRAMA POR CONSOLA
    cout << "\033[32mBienvenido al Banco de Ahorros!!!\033[0m \n\n";
    int opcion;
    do{
        cout << "Menu de opciones:\n\n";
        cout << "1. Mostrar Banco Completo\n";
        cout << "2. Mostrar cuenta de una Persona\n";
        cout << "3. Jugar la Balota\n";
        cout << "4. Agregar Acciones a una persona\n";
        cout << "5. Guardar Nuevos Datos\n";
        cout << "0. Salir\n\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\nMostrando Banco Completo.\n\n";
                    mostrarPersonas(personas);
                    cout << "\n";
                break;
            case 2:
                cout << "\nMostrando la cuenta.\n\n";
                    mostrarPersonaID(personas,pedirIDPersona());
                    cout << "\n\n";
                break;
            case 3: 
                cout << "\nVMAOS A JUGAR LA BALOTA!!!\n";
                    MostrarganadorBalotaSumaCuenta(personas);
                    cout << "\n";
                break;
            case 4:
                cout << "\nVamos a agregar acciones a una cuenta.\n\n";
                    agregarAcciones(personas,pedirIDPersona(),pedirCantidadAcciones());
                    cout << "Acciones agregadas exitosamente\n\n";
                    cout << "\n";
                break;
            case 5:
                //llamamos a la funcion que hace que los archivos se modifiquen con los nuevos valores
                    GuardarDatosEnTXT(personas);
                cout << "\n\033[33mDATOS GUARDADOS CORRECTAMENTE\033[0m \n\n";
                cout << "\n";
                break;
            case 0:
                cout << "\nSaliendo del programa...\n\n";
                break;
            default:
                cout << "\nOpción no válida. Intente de nuevo.\n\n";
                cout << "\n";
                break;
        }
    }while(!opcion==0);

    return 0;
}