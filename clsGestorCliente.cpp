#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>
#include "clsGestorCliente.h"
#include "clsCliente.h"

/// CONSTRUCTOR
/// Guarda la ruta del archivo donde se guardan los registros
clsGestorCliente::clsGestorCliente()
{
    _rutaDireccion = "Cliente.dat";
}

/// MÉTODOS DE MANIPULACIÓN
bool clsGestorCliente::ev(std::string texto, int minimo, int maximo)
{
    if ((texto.size() >= static_cast<std::string::size_type>(minimo)) &&
        (texto.size() <= static_cast<std::string::size_type>(maximo))){
        return true;
    }else{
        rlutil::cls();
        std::cout << "ERROR: ENTRADA NO VALIDA";
        return false;
    }
}


void clsGestorCliente::cargarUnCliente(clsCliente &cliente)
{
    std::string cuit;
    std::string nombre;
    std::string apellido;
    std::string telefono;
    std::string mail;
    std::string direccion;
    std::string tipoCliente;

    std::cin.ignore();

    ///CUIT
    do
    {
        std::cout << "CUIT: ";
        std::getline(std::cin, cuit);
    }
    while(!(ev(cuit, 11, 11)));

    cliente.setCuit(cuit.c_str());

    ///NOMBRE
    do
    {
        std::cout << "NOMBRE: ";
        std::getline(std::cin, nombre);
    }
    while(!(ev(nombre, 1, 20)));

    cliente.setNombre(nombre.c_str());

    ///APELLIDO
    do
    {
        std::cout << "APELLIDO: ";
        std::getline(std::cin, apellido);
    }
    while(!(ev(apellido, 1, 20)));

    cliente.setApellido(apellido.c_str());


    ///TELEFONO
    do
    {
        std::cout << "TELEFONO: ";
        std::getline(std::cin, telefono);
    }
    while(!(ev(telefono, 1, 20)));

    cliente.setNumTelefono(telefono.c_str());


    ///MAIL
    do
    {
        std::cout << "MAIL: ";
        std::getline(std::cin, mail);
    }
    while(!(ev(mail, 1, 50)));

    cliente.setMail(mail.c_str());


    ///DIRECCION
    do
    {
        std::cout << "DIRECCION: ";
        std::getline(std::cin, direccion);
    }
    while(!(ev(direccion, 1, 50)));

    cliente.setDireccion(mail.c_str());


    ///TIPO DE CLIENTE
    char tipo;

    do
    {
        std::cout << "[1-PARTICULAR / 2-EMPRESA]: ";
        std::getline(std::cin, tipoCliente);
    }
    while(!(ev(tipoCliente, 1, 1)) || (tipoCliente != "1" && tipoCliente != "2"));

    tipo=tipoCliente[0];
    cliente.setTipoCliente(tipo);

    cliente.setEstado(true);
}


/// ESTE METODO MUESTRA LOS DATOS DE LOS CLIENTES
void clsGestorCliente::mostrarUnCliente(clsCliente cliente)
{
    std::cout << "CUIT: " << cliente.getCuit() << std::endl;
    std::cout << "NOMBRE: " << cliente.getNombre() << std::endl;
    std::cout << "APELLIDO: " << cliente.getApellido() << std::endl;
    std::cout << "TELEFONO: " << cliente.getNumTelefono() << std::endl;
    std::cout << "MAIL: " << cliente.getMail() << std::endl;
    std::cout << "DIRECCION: " << cliente.getDireccion() << std::endl;
    std::cout << "TIPO: " << (cliente.getTipoCliente() == '1' ? "PARTICULAR" : "EMPRESA") << std::endl; ///OPERADOR TERNARIO
    std::cout << "-----------------------------------";
    std::cout << std::endl;
}

/// abre el archivo utilizando ab+ escribe registro final
bool clsGestorCliente::guardarEnDiscoCliente(clsCliente cliente)
{
    FILE *p = fopen(_rutaDireccion.c_str(), "ab+");
    if (p == NULL) return false;
    bool ok = fwrite(&cliente, sizeof(clsCliente), 1, p);
    fclose(p);
    return ok;
}
/// sobrescribe un registro existente en una pos especifica seek
bool clsGestorCliente::guardarEnDiscoCliente(clsCliente cliente, int pos)
{
    FILE *p = fopen(_rutaDireccion.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, sizeof(clsCliente) * pos, SEEK_SET);
    bool ok = fwrite(&cliente, sizeof(clsCliente), 1, p);
    fclose(p);
    return ok;
}
/// recorre el archivo buscando un cliente
int clsGestorCliente::buscarClientePorCuit(const char *cuit)
{
    clsCliente cliente;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL) return -1;

    int i = 0;
    while (fread(&cliente, sizeof(clsCliente), 1, p))
    {
        if (strcmp(cliente.getCuit(), cuit) == 0)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}
/// lee un cliente en una pos especifica
clsCliente clsGestorCliente::leerCliente(int pos)
{
    clsCliente cliente;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL) exit(1);
    fseek(p, sizeof(clsCliente) * pos, SEEK_SET);
    fread(&cliente, sizeof(clsCliente), 1, p);
    fclose(p);
    return cliente;
}

/// EJECUCIÓN DE OPCIONES DE MENU
void clsGestorCliente::cargarCliente()
{
    clsCliente nuevo;
    cargarUnCliente(nuevo);

    if (buscarClientePorCuit(nuevo.getCuit()) != -1)
    {
        std::cout << "ERROR: CLIENTE EXISTENTE";
        return;
    }

    std::cout << (guardarEnDiscoCliente(nuevo) ? "CLIENTE GUARDADO CORRECTAMENTE" : "ERROR: NO SE PUDO GUARDAR") << std::endl;
}

void clsGestorCliente::modificarCliente()
{
    char opcion;
    char cuit[20];

    std::cout << "CUIT: ";
    std::cin >> cuit;

    int pos;
    pos=buscarClientePorCuit(cuit);

    if (pos !=-1)
    {
        clsCliente cliente = leerCliente(pos);

        std::cout << "DATOS ACTUALES: " << std::endl;
        std::cout << std::endl;

        mostrarUnCliente(cliente);

        rlutil::anykey("Press any key to continue...\n");

        std::cout << "\n1-NOMBRE\n2-APELLIDO\n3-MAIL\n4-TELEFONO\n5-DIRECCION\n6-TIPO\n" << std::endl;
        std::cout << "OPCION: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion)
        {
            case '1':
            {
                std::string nombre;
                do
                {
                    std::cout << "NOMBRE: ";
                    std::getline(std::cin, nombre);
                }
                while(!(ev(nombre, 1, 20)));

                cliente.setNombre(nombre.c_str());
            }
            break;

            case '2':
            {
                std::string apellido;
                do
                {
                    std::cout << "APELLIDO: ";
                    std::getline(std::cin, apellido);
                }
                while(!(ev(apellido, 1, 20)));

                cliente.setApellido(apellido.c_str());
            }
            break;

            case '3':
            {
                std::string mail;
                do
                {
                    std::cout << "MAIL: ";
                    std::getline(std::cin, mail);
                }
                while(!(ev(mail, 1, 50)));

                cliente.setMail(mail.c_str());
            }
            break;

            case '4':
            {
                std::string telefono;
                do
                {
                    std::cout << "TELEFONO: ";
                    std::getline(std::cin, telefono);
                }
                while(!(ev(telefono, 1, 20)));

                cliente.setNumTelefono(telefono.c_str());
            }
            break;


            case '5':
            {
                std::string direccion;
                do
                {
                    std::cout << "DIRECCION: ";
                    std::getline(std::cin, direccion);
                }
                while(!(ev(direccion, 1, 50)));

                cliente.setDireccion(direccion.c_str());
            }
            break;

            case '6':
            {
                char tipo;
                std::string tipoCliente;
                do
                {
                    std::cout << "[1-PARTICULAR / 2-EMPRESA]: ";
                    std::getline(std::cin, tipoCliente);
                }
                while(!(ev(tipoCliente, 1, 1)) || (tipoCliente != "1" && tipoCliente != "2"));

                tipo=tipoCliente[0];
                cliente.setTipoCliente(tipo);
            }
            break;
        }

        std::cout << (guardarEnDiscoCliente(cliente, pos) ? "CLIENTE GUARDADO CORRECTAMENTE" : "ERROR: NO SE PUDO GUARDAR") << std::endl;
    }
}


void clsGestorCliente::mostrarTodos()
{
    clsCliente cliente;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL)
    {
        std::cout << "ERROR: ARCHIVO NO ENCONTRADO";
        return;
    }

    while (fread(&cliente, sizeof(clsCliente), 1, p))
    {
        if (cliente.getEstado())
            mostrarUnCliente(cliente);
    }

    rlutil::anykey("Press any key to continue...\n");

    fclose(p);
}

void clsGestorCliente::bajaCliente()
{
    char cuit[20];
    std::cout << "Ingrese el CUIT del cliente a eliminar: ";
    std::cin >> cuit;

    int pos = buscarClientePorCuit(cuit);
    if (pos == -1)
    {
        std::cout << "ERROR: CLIENTE NO ENCONTRADO";
        return;
    }

    clsCliente cliente = leerCliente(pos);
    cliente.setEstado(false);
    guardarEnDiscoCliente(cliente, pos);

    std::cout << "CLIENTE DADO DE BAJA CORRECTAMENTE";
}

void clsGestorCliente::buscarCliente()
{
    char cuit[20];
    std::cout << "CUIT: ";
    std::cin >> cuit;

    int pos = buscarClientePorCuit(cuit);
    if (pos == -1)
    {
        std::cout << "ERROR: CLIENTE NO ENCONTRADO";
        return;
    }

    clsCliente cliente = leerCliente(pos);
    if (cliente.getEstado())
        mostrarUnCliente(cliente);
    else
        std::cout << "ERROR: CLIENTE INACTIVO";
}

int clsGestorCliente::obtenerCantidadReg (std::string pfile, clsCliente obj)
{
    FILE *p = fopen(pfile.c_str(), "rb");
    if (p == NULL)
    {
        std::cout << "ERROR: ARCHIVO VACIO";
        return 0;
    }

    int cont = 0;
    while (fread(&obj, sizeof(clsCliente), 1, p))
    {
        if (obj.getEstado()==true)
        {
            cont++;
        }
    }

    fclose(p);

    return cont;
}


void clsGestorCliente::CUITascendente()
{
    clsCliente cliente;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");

    if (p == NULL)
    {
        std::cout << "ERROR: ARCHIVO VACIO";
        return;
    }

    int cont = obtenerCantidadReg(_rutaDireccion.c_str(), cliente);

    if (cont <= 0)
    {
        std::cout << "ERROR: ARCHIVO VACIO";
        fclose(p);
        return;
    }


    clsCliente *vecClientes = new clsCliente[cont];


    rewind(p);


    int i = 0;
    while (fread(&cliente, sizeof(clsCliente), 1, p))
    {
        if (cliente.getEstado()==true)
        {
            vecClientes[i] = cliente;
            i++;
        }
    }
    fclose(p);


    ///ORDENAR
    for (int a = 0; a < i - 1; a++)
    {
        for (int b = a + 1; b < i; b++)
        {
            if (vecClientes[a].getCuit() > vecClientes[b].getCuit())
            {
                clsCliente aux = vecClientes[a];
                vecClientes[a] = vecClientes[b];
                vecClientes[b] = aux;
            }
        }
    }

    ///MOSTRAR
    std::cout << "=== CLIENTES ORDENADOS POR CUIT (MENOR A MAYOR) ===" << std::endl;
    for (int j = 0; j < i; j++)
    {
        mostrarUnCliente(vecClientes[j]);
        std::cout << std::endl;
    }

    delete[] vecClientes;
}

//void clsGestorCliente::CUITdescendente()
//{
//    clsCliente cliente;
//    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
//
//    if (p == NULL)
//    {
//        std::cout << "No hay clientes cargados actualmente." << std::endl;
//        return;
//    }
//
//    int cont = obtenerCantidadReg(_rutaDireccion.c_str(), cliente);
//
//    if (cont <= 0)
//    {
//        std::cout << "No hay clientes cargados actualmente." << std::endl;
//        fclose(p);
//        return;
//    }
//
//
//    clsCliente *vecClientes = new clsCliente[cont];
//
//
//    rewind(p);
//
//
//    int i = 0;
//    while (fread(&cliente, sizeof(clsCliente), 1, p))
//    {
//        if (cliente.getEstado()==true)
//        {
//            vecClientes[i] = cliente;
//            i++;
//        }
//    }
//    fclose(p);
//
//
//    ///ORDENAR
//    for (int a = 0; a < i - 1; a++)
//    {
//        for (int b = a + 1; b < i; b++)
//        {
//            if (vecClientes[a].getCuit() < vecClientes[b].getCuit())
//            {
//                clsCliente aux = vecClientes[a];
//                vecClientes[a] = vecClientes[b];
//                vecClientes[b] = aux;
//            }
//        }
//    }
//
//    ///MOSTRAR
//    std::cout << "=== CLIENTES ORDENADOS POR CUIT (MENOR A MAYOR) ===" << std::endl;
//    for (int j = 0; j < i; j++)
//    {
//        mostrarUnCliente(vecClientes[j]);
//        std::cout << std::endl;
//    }
//
//    delete[] vecClientes;
//}
