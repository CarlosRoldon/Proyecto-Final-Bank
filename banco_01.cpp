#include <iostream>
#include <vector>   //para poder crear la lista de personas y guardarlo en un vector
#include <random>   //para sacar el numero aleatorio de la balota
#include <ctime>    // Para srand()

using namespace std;

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
        cout << "ID: "<< p.ID << ", " << p.nombre << ", Acciones Totales: (" << p.Cantidad_Acciones <<
        ") | "<< p.dineroTotal<< endl;
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
    //srand(rd());
    srand(time(nullptr));
    int ganadorID;
    bool encontrado = false;
    
    while (!encontrado) {
        int indice = (rand() % 23) + 1; // Genera un índice aleatorio entre 1 y 23
        if (!personas[indice].balota) {
            personas[indice].balota = true; // Marcar como ganador
            ganadorID = personas[indice].ID;
            encontrado = true;
        }
    }
    return ganadorID;
}

//FUNCION SUMAR BALOTA DE HOY DEVUELVE LA FRASE DONDE DICE CUAL ES EL GANADOR
void MostrarganadorBalotaSumaCuenta(vector<Persona>& personas){
    int posicionGanador = numeroBalotaGanador(personas);
    //PROVISONAL
    string fraseXD;
    fraseXD = "\033[31m"+to_string(posicionGanador)+"\033[0m";
    cout << fraseXD << endl;
    // SE LE VA A DAR 
    personas[posicionGanador].dineroTotal += (VALOR_BALOTA*23)/2;
    string fraseGanador = "El ganador de la Balota de hoy es el N("+ to_string(personas[posicionGanador].ID) +") - "+
    personas[posicionGanador].nombre+" "+personas[posicionGanador].apellido +"\n\n";
    cout << fraseGanador << endl;
}



int main(){
    //BASE DE DATOS PROVISIONAL
    vector<Persona> personas;
    personas.push_back({"Sofia", "Ramirez",1});
    personas.push_back({"Mateo", "Gonzales",2});
    personas.push_back({"Valentina", "Perez",3});
    personas.push_back({"Santiago", "Lopez",4});
    personas.push_back({"Camila", "Rodriguez",5});
    personas.push_back({"David", "Martinez",6});
    personas.push_back({"Laura", "Hernandez",7});
    personas.push_back({"Benjamin", "Garcia",8});
    personas.push_back({"Martina", "Fernandez",9});
    personas.push_back({"Diego", "Sanchez",10});
    personas.push_back({"Emilia", "Moreno",11});
    personas.push_back({"Lucas", "Gomez",12});
    personas.push_back({"Olivia", "Alvarez",13});
    personas.push_back({"Nicolas", "Romero",14});
    personas.push_back({"Victoria", "Muñoz",15});
    personas.push_back({"Alejandro", "Diaz",16});
    personas.push_back({"Isabella", "Castro",17});
    personas.push_back({"Daniel", "Vega",18});
    personas.push_back({"Emma", "Navarro",19});
    personas.push_back({"Pablo", "Guzman",20});
    personas.push_back({"Sara", "Marin",21});
    personas.push_back({"Manuel", "Jimenez",22});
    personas.push_back({"Ana", "Ruiz",23});

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

    return 0;
}



