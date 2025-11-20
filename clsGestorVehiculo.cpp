///GESTOR VEHICULO CPP
#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>
#include "clsVehiculo.h"
#include "clsGestorVehiculo.h"

/// CONSTRUCTOR
clsGestorVehiculo::clsGestorVehiculo()
{
    _rutaDireccion = "Vehiculo.dat";
}


///METODOS DE MANIPULACION
bool clsGestorVehiculo::ev(std::string texto, int minimo, int maximo)
{
    ///std::size() Devuelve 1 valor size t que es 1 entero sin signo (UNSIGNED) que suele ser mas grande en el sistema que el entero que si tiene signo (signed)
    if (static_cast<int>(texto.size()) >= minimo &&
        static_cast<int>(texto.size()) <= maximo)
    {
        return true;
    }
    else
    {
        system("cls");
        std::cout << "Entrada invalida. Ingrese nuevamente" << std::endl;
        return false;
    }
}



void clsGestorVehiculo::cargarUnVehiculo(clsVehiculo &vehiculo)
{
    std::string numPatente;
    std::string marca;
    std::string modelo;
    std::string tipoVehiculo;


    ///PATENTE
///PATENTE
    do
    {
        std::cout << "PATENTE: ";
        std::getline(std::cin, numPatente);

        // Convertir automáticamente a MAYÚSCULAS
        for (char &c : numPatente)
        {
            c = std::toupper(static_cast<unsigned char>(c));
        }
    }while(!(ev(numPatente, 6, 7)));

vehiculo.setNumeroPatente(numPatente.c_str());



    ///MARCA
    do
    {
        std::cout << "MARCA: ";
        std::getline(std::cin, marca);
    }
    while(!(ev(marca, 1, 20)));

    vehiculo.setMarca(marca.c_str());


    ///MODELO
    do
    {
        std::cout << "MODELO: ";
        std::getline(std::cin, modelo);
    }
    while(!(ev(modelo, 1, 20)));

    vehiculo.setModelo(modelo.c_str());


    ///TIPO DE VEHICULO
    char tipo;
    do
    {
        std::cout << "\n 1) Auto\n 2) Camioneta\n 3) Camion\n 4) Transporte\n" << std::endl;
        std::cout << "INGRESE UN NUMERO DE TIPO: ";
        std::getline(std::cin, tipoVehiculo);
    }
    while(!(ev(tipoVehiculo, 1, 1)) || (tipoVehiculo != "1" && tipoVehiculo != "2" && tipoVehiculo != "3" && tipoVehiculo != "4"));

    tipo=tipoVehiculo[0];

    vehiculo.setTipoVehiculo(tipo);
    vehiculo.setEstado(true);
}


void clsGestorVehiculo::mostrarUnVehiculo(clsVehiculo vehiculo)
{
    std::cout << "PATENTE: " << vehiculo.getNumeroPatente() << std::endl;
    std::cout << "MARCA: " << vehiculo.getMarca() << std::endl;
    std::cout << "MODELO: " << vehiculo.getModelo() << std::endl;

    std::cout << "TIPO: ";
    switch(vehiculo.getTipoVehiculo())
    {
    case '1':
        std::cout << "AUTO" << std::endl;
        break;
    case '2':
        std::cout << "CAMIONETA" << std::endl;
        break;
    case '3':
        std::cout << "CAMION" << std::endl;
        break;
    case '4':
        std::cout << "TRANSPORTE" << std::endl;
        break;
    default:
        std::cout << "AUTO" << std::endl;
    }
    std::cout << "-----------------------------------";
    std::cout << std::endl << std::endl;
}


bool clsGestorVehiculo::guardarEnDiscoVehiculo(clsVehiculo vehiculo)
{
    FILE *file;
    file = fopen(_rutaDireccion.c_str(), "ab+");

    if(file==NULL)
    {
        std::cout << "Direccion no encontrada";
        return false;
    }

    bool grabar = fwrite(&vehiculo, sizeof(clsVehiculo), 1, file);
    fclose(file);
    return grabar;
}


bool clsGestorVehiculo::guardarEnDiscoVehiculo(clsVehiculo vehiculo, int posicion)
{
    bool grabar;
    FILE *file;
    file = fopen(_rutaDireccion.c_str(), "rb+");

    if(file==NULL)
    {
        exit(1);
    }

    fseek(file, sizeof(clsVehiculo)*posicion, SEEK_SET);
    grabar = fwrite(&vehiculo, sizeof(clsVehiculo), 1, file);
    fclose(file);
    return grabar;
}





clsVehiculo clsGestorVehiculo::leerVehiculo(int posicion)
{
    clsVehiculo vehiculo;
    FILE *file = fopen(_rutaDireccion.c_str(),"rb");

    if(file == NULL)
    {
        vehiculo.setEstado(false);
        return vehiculo;
    }

    // verificar posición válida
    if (fseek(file, sizeof(clsVehiculo)*posicion, SEEK_SET) != 0)
    {
        vehiculo.setEstado(false);
        fclose(file);
        return vehiculo;
    }

    // intentar leer
    if (fread(&vehiculo, sizeof(clsVehiculo), 1, file) != 1)
    {
        vehiculo.setEstado(false);
    }

    fclose(file);
    return vehiculo;
}



///EJECUCION DE OPCIONES
void clsGestorVehiculo::cargarVehiculo()
{
    clsVehiculo vehiculoNuevo;
    bool check;

    cargarUnVehiculo(vehiculoNuevo);

    if((buscarVehiculoPorPatente(vehiculoNuevo.getNumeroPatente()))!=-1)
    {
        system("cls");
        std::cout << "Error. Vehiculo ya existente." << std::endl;
        return;
    }


    check=guardarEnDiscoVehiculo(vehiculoNuevo);
    if(check==true)
    {
        std::cout << "Vehiculo guardado exitosamente" << std::endl;
    }
    else
    {
        std::cout << "El vehiculo no ha podido ser guardado" << std::endl;
    }
}








void clsGestorVehiculo::modificarVehiculo()
{
        std::string numPatente;

    int pos = -1;

    /// BUCLE HASTA QUE PATENTE SEA EXISTENTE Y VALIDA EN EL RANGO DE 6 y 7 CARACTERES
    do
    {
        do
        {
            std::cout << "INGRESAR PATENTE DE AUTO A MODIFICAR: ";
            std::getline(std::cin, numPatente);

            // CONVERTIR A MAYUSCULA
            for (char &c : numPatente)
            {
                c = std::toupper(static_cast<unsigned char>(c));
            }

        } while (!ev(numPatente, 6, 7));  // valida largo

        // BUSCAR EN ARCHIVO
        pos = buscarVehiculoPorPatente(numPatente.c_str());

        /// SI NO EXISTE >>> VUELVO A PEDIR
        if (pos == -1)
        {
            std::cout << "ERROR: VEHICULO NO ENCONTRADO. Intente nuevamente.\n\n";
            system("pause");
            system("cls");
        }

    } while (pos == -1);


    clsVehiculo vehiculo = leerVehiculo(pos);

    char opcion;
    do
    {
        system("cls");
        std::cout << "=== MODIFICAR VEHICULO ===\n";
        mostrarUnVehiculo(vehiculo);

        std::cout << "\nSeleccione un dato a cambiar:\n";
        std::cout << "1) Marca\n";
        std::cout << "2) Modelo\n";
        std::cout << "3) Tipo\n";
        std::cout << "4) Guardar y salir\n";
        std::cout << "Opcion: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(opcion)
        {
        case '1':
        {
            std::string marca;
            do
            {
                std::cout << "NUEVA MARCA: ";
                std::getline(std::cin, marca);
            }
            while(!(ev(marca, 1, 20)));

            vehiculo.setMarca(marca.c_str());
            break;
        }

        case '2':
        {
            std::string modelo;
            do
            {
                std::cout << "NUEVO MODELO: ";
                std::getline(std::cin, modelo);
            }
            while(!(ev(modelo, 1, 20)));

            vehiculo.setModelo(modelo.c_str());
            break;
        }

        case '3':
        {
            std::string tipoVehiculo;
            char tipo;

            do
            {
                std::cout << "\n 1) Auto\n 2) Camioneta\n 3) Camion\n 4) Transporte\n";
                std::cout << "Ingrese nuevo tipo: ";
                std::getline(std::cin, tipoVehiculo);
            }
            while(!(ev(tipoVehiculo, 1, 1)) ||
                  (tipoVehiculo != "1" && tipoVehiculo != "2" &&
                   tipoVehiculo != "3" && tipoVehiculo != "4"));

            tipo = tipoVehiculo[0];
            vehiculo.setTipoVehiculo(tipo);
            break;
        }

        case '4':
            break;

        default:
            std::cout << "Opcion no valida." << std::endl;
            system("pause");
        }

    } while(opcion != '4');


    if (guardarEnDiscoVehiculo(vehiculo, pos))
        std::cout << "VEHICULO MODIFICADO CORRECTAMENTE\n";
    else
        std::cout << "ERROR: NO SE PUDO MODIFICAR VEHICULO\n";


}







void clsGestorVehiculo::mostrarTodos()
{
    clsVehiculo vehiculo;

    FILE *file;
    file = fopen(_rutaDireccion.c_str(), "rb");

    if(file == NULL)
    {
        std::cout << "No hay vehiculos cargados actualmente " << std::endl;
        return;
    }

    while(fread(&vehiculo, sizeof(clsVehiculo), 1, file))
    {
        if(vehiculo.getEstado()==true)
        {
            mostrarUnVehiculo(vehiculo);
        }
    }

    fclose(file);
}


/// 364


void clsGestorVehiculo::bajaVehiculo()
{
    clsVehiculo vehiculoEliminado;
    char patente[8];

    //  NO limpiar buffer acá
    std::cout << "Patente de vehiculo a eliminar: ";
    std::cin.getline(patente, 8);

    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Demasiados caracteres, intente nuevamente." << std::endl;
        return;
    }

    // Convertir a mayúsculas
    for (int i = 0; patente[i] != '\0'; i++)
    {
        patente[i] = std::toupper(static_cast<unsigned char>(patente[i]));
    }

    int pos = buscarVehiculoPorPatente(patente);

    if (pos == -1)
    {
        std::cout << "ERROR: VEHICULO NO ENCONTRADO" << std::endl;
        return;
    }

    vehiculoEliminado = leerVehiculo(pos);
    vehiculoEliminado.setEstado(false);

    if (guardarEnDiscoVehiculo(vehiculoEliminado, pos))
    {
        std::cout << "Vehiculo eliminado correctamente." << std::endl;
    }
    else
    {
        std::cout << "ERROR: No se pudo eliminar el vehiculo." << std::endl;
    }
}

/// ++++++++++++++++++++++ ALTA VEHICULO SIN RETURN +++++++++++++++++++++++++

void clsGestorVehiculo::Alta_Vehiculo()
{
    std::string numPatente;

    int pos = -1;

    /// BUCLE HASTA QUE PATENTE SEA EXISTENTE Y VALIDA EN EL RANGO DE 6 y 7 CARACTERES
    do
    {
        do
        {
            std::cout << "PATENTE: ";
            std::getline(std::cin, numPatente);

            // CONVERTIR A MAYUSCULA
            for (char &c : numPatente)
            {
                c = std::toupper(static_cast<unsigned char>(c));
            }

        } while (!ev(numPatente, 6, 7));  // valida largo

        // BUSCAR EN ARCHIVO
        pos = buscarVehiculoPorPatente(numPatente.c_str());

        /// SI NO EXISTE >>> VUELVO A PEDIR
        if (pos == -1)
        {
            std::cout << "ERROR: VEHICULO NO ENCONTRADO. Intente nuevamente.\n\n";
        }

    } while (pos == -1);

    /// SI EXSITE, DAMOS DE ALTA
    clsVehiculo vehiculo = leerVehiculo(pos);
    vehiculo.setEstado(true);

    if (guardarEnDiscoVehiculo(vehiculo, pos))
    {
        std::cout << "Vehiculo dado de ALTA correctamente.\n";
    }
    else
    {
        std::cout << "ERROR: No se pudo dar de alta el vehiculo.\n";
    }
}





int clsGestorVehiculo::buscarVehiculoPorPatente(const char* patenteBuscada)
{
    FILE *file = fopen(_rutaDireccion.c_str(), "rb");
    if (file == NULL)
        return -1;  /// archivo vacio

    clsVehiculo vehiculo;
    int pos = 0;

    while (fread(&vehiculo, sizeof(clsVehiculo), 1, file) == 1)
    {
        if (!vehiculo.getEstado())
        {
            pos++;
            continue;   /// saltar vehículos eliminados PERO seguir leyendo
        }

        char patenteArchivo[8];
        std::strcpy(patenteArchivo, vehiculo.getNumeroPatente());

        // pasar a mayúsculas
        for (int i = 0; patenteArchivo[i] != '\0'; i++)
            patenteArchivo[i] = std::toupper(static_cast<unsigned char>(patenteArchivo[i]));

        char patenteTmp[8];
        std::strcpy(patenteTmp, patenteBuscada);
        for (int i = 0; patenteTmp[i] != '\0'; i++)
            patenteTmp[i] = std::toupper(static_cast<unsigned char>(patenteTmp[i]));

        if (std::strcmp(patenteArchivo, patenteTmp) == 0)
        {
            fclose(file);
            return pos;
        }

        pos++;
    }

    fclose(file);
    return -1;   /// no encontrado
}





///METODO ORIGINAL SIN MAYUSUCULAS
void clsGestorVehiculo::buscarVehiculo()
{
    char patente[8];

    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // limpiar buffer
    std::cout << "Patente de vehiculo a buscar: ";
    std::cin.getline(patente, 8);

    int pos = buscarVehiculoPorPatente(patente);

    if (pos != -1)
    {
        clsVehiculo vehiculo = leerVehiculo(pos);
        mostrarUnVehiculo(vehiculo);
    }
    else
    {
        std::cout << "Error. El vehiculo es inexistente" << std::endl;
    }
}





int clsGestorVehiculo::obtenerCantidadReg (std::string pfile, clsVehiculo obj)
{
    FILE *p = fopen(pfile.c_str(), "rb");
    if (p == NULL)
    {
        std::cout << "No hay datos cargados actualmente.";
        return 0;
    }

    int cont = 0;
    while (fread(&obj, sizeof(clsVehiculo), 1, p))
    {
        if (obj.getEstado())
        {
            cont++;
        }
    }

    fclose(p);

    return cont;
}


///MEMORIA DINAMICA
void clsGestorVehiculo::OrdenarXPatente()
{
    clsVehiculo vehiculo;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");

    if (p == NULL)
    {
        std::cout << "No hay vehículos cargados actualmente." << std::endl;
        system("pause");
        return;
    }

    int cantidad = obtenerCantidadReg(_rutaDireccion.c_str(), vehiculo);
    if (cantidad <= 0)
    {
        std::cout << "No hay vehículos cargados actualmente." << std::endl;
        fclose(p);
        system("pause");
        return;
    }

    clsVehiculo *vecVehiculos = new clsVehiculo[cantidad];
    rewind(p);

    int i = 0;
    while (fread(&vehiculo, sizeof(clsVehiculo), 1, p))
    {
        if (vehiculo.getEstado() == true)
        {
            vecVehiculos[i] = vehiculo;
            i++;
        }
    }
    fclose(p);

    if (i == 0)
    {
        std::cout << "No hay vehículos activos para mostrar." << std::endl;
        delete[] vecVehiculos;
        system("pause");
        return;
    }

    /// ORDENAR POR NUMERO DE PATENTE (alfabeticamente)
    for (int a = 0; a < i - 1; a++)
    {
        for (int b = a + 1; b < i; b++)
        {
            if (strcmp(vecVehiculos[a].getNumeroPatente(), vecVehiculos[b].getNumeroPatente()) > 0)
            {
                clsVehiculo aux = vecVehiculos[a];
                vecVehiculos[a] = vecVehiculos[b];
                vecVehiculos[b] = aux;
            }
        }
    }

    std::cout << "\n=== VEHICULOS ORDENADOS POR PATENTE (A-Z) ===" << std::endl;
    for (int j = 0; j < i; j++)
    {
        mostrarUnVehiculo(vecVehiculos[j]);
        std::cout << std::endl;
    }

    delete[] vecVehiculos;

    std::cout << "\n=== Fin del listado ===" << std::endl;
    system("pause");
}
