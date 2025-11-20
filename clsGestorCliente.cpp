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
    if (texto.size() >= static_cast<std::size_t>(minimo) &&
        texto.size() <= static_cast<std::size_t>(maximo))
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


///CARGAR CLIENTE POR TECLADO
void clsGestorCliente::cargarUnCliente(clsCliente &cliente)
{
    std::string cuit;
    std::string nombre;
    std::string apellido;
    std::string telefono;
    std::string mail;
    std::string direccion;
    std::string tipoCliente;


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
        std::cout << "NUM TELEFONO : ";
        std::getline(std::cin, telefono);
    }
    while(!(ev(telefono, 1, 20)));

    cliente.setNumTelefono(telefono.c_str());


    ///MAIL
    do
    {
        std::cout << "MAIL : ";
        std::getline(std::cin, mail);
    }
    while(!(ev(mail, 1, 50)));

    cliente.setMail(mail.c_str());


    ///DIRECCION
    do
    {
        std::cout << "DIRECCION : ";
        std::getline(std::cin, direccion);
    }
    while(!(ev(direccion, 1, 50)));

    cliente.setDireccion(mail.c_str());


    ///TIPO DE CLIENTE
    char tipo;

    do
    {
        std::cout << "Seleccione tipo (1 Particular --- 2 Empresa): ";
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
    std::cout << "TIPO DE CLIENTE: " << (cliente.getTipoCliente() == '1' ? "Particular" : "Empresa") << std::endl; /// operador ternario
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


/// RECORRE EL ARCHIVO Y COMPARA AMBOS CUIT, RETORNANDO LA POSICION EN EL ARCHIVO DE DONDE ESTA ESE CUIT
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


/// LEE 1 CLIENTE EN UNA POSICION ESPECIFICA
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
        std::cout << "ERROR: El Cliente ya existe";
        return;
    }

    if (guardarEnDiscoCliente(nuevo))
        std::cout << "Cliente guardado exitosamente";
    else
        std::cout << "ERROR: No se pudo guardar el cliente";
}

///OPCION 2 DEL MENU >> MODIFICAR 1 CLIENTE
void clsGestorCliente::modificarCliente()
{
    std::string cuit;
    char opcion;



    // === VALIDAR CUIT HASTA QUE TENGA EXACTAMENTE 11 CARACTERES ===
    do
    {
        std::cout << "CUIT del cliente a modificar: ";
        std::getline(std::cin, cuit);

    } while (!ev(cuit, 11, 11));

    // Buscar en archivo usando c_str()
    int pos = buscarClientePorCuit(cuit.c_str()); //ACA LO CONVIERTO A CONST CHAR * CON C_STR()

    if (pos == -1)
    {
        std::cout << "ERROR: CLIENTE NO ENCONTRADO" << std::endl;
        return;
    }

    // Leer cliente
    clsCliente cliente = leerCliente(pos);

    std::cout << "DATOS ACTUALES:\n";
    mostrarUnCliente(cliente);
    system("pause");

    std::cout << "\n1) Nombre\n2) Apellido\n3) Mail\n4) Telefono\n5) Direccion\n6) Tipo de cliente\n";
    std::cout << "Ingrese opcion de dato a cambiar: ";
    std::cin >> opcion;

    // limpiar buffer antes de getline()
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (opcion)
    {
    case '1':
    {
        std::string nombre;
        do
        {
            std::cout << "NOMBRE: ";
            std::getline(std::cin, nombre);
        }
        while (!ev(nombre, 1, 20));

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
        while (!ev(apellido, 1, 20));

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
        while (!ev(mail, 1, 50));

        cliente.setMail(mail.c_str());
    }
    break;

    case '4':
    {
        std::string telefono;
        do
        {
            std::cout << "NUM TELEFONO: ";
            std::getline(std::cin, telefono);
        }
        while (!ev(telefono, 1, 20));

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
        while (!ev(direccion, 1, 50));

        cliente.setDireccion(direccion.c_str());
    }
    break;

    case '6':
    {
        std::string tipoCliente;
        do
        {
            std::cout << "Seleccione tipo (1 Particular — 2 Empresa): ";
            std::getline(std::cin, tipoCliente);
        }
        while (!ev(tipoCliente, 1, 1) || (tipoCliente != "1" && tipoCliente != "2"));

        cliente.setTipoCliente(tipoCliente[0]);
    }
    break;

    default:
        std::cout << "Opcion invalida.\n";
        return;
    }

    // Guardar cambios
    if (guardarEnDiscoCliente(cliente, pos))
    {
        std::cout << "CLIENTE MODIFICADO CORRECTAMENTE\n";
    }
    else
    {
        std::cout << "ERROR: NO SE PUDO MODIFICAR EL CLIENTE\n";
    }
}



void clsGestorCliente::mostrarTodos()
{
    clsCliente cliente;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL)
    {
        std::cout << "No hay clientes cargados actualmente.";
        return;
    }

    while (fread(&cliente, sizeof(clsCliente), 1, p))
    {
        if (cliente.getEstado())
            mostrarUnCliente(cliente);
    }
    fclose(p);
}

///ALTA Y BAJA >>>>>>> 1) BAJA

void clsGestorCliente::bajaCliente()
{
    char cuit[12];
    std::cout << "Ingrese el CUIT del cliente a eliminar: ";
    std::cin >> cuit;

    int pos = buscarClientePorCuit(cuit);
    if (pos == -1)
    {
        std::cout << "ERROR: Cliente no encontrado.";
        return;
    }

    clsCliente cliente = leerCliente(pos);
    cliente.setEstado(false);
    guardarEnDiscoCliente(cliente, pos);

    std::cout << "Cliente dado de baja correctamente.";
}

///ALTA

void clsGestorCliente::altaCliente()
{
std::string cuit;

    int pos = -1;

    /// BUCLE HASTA QUE PATENTE SEA EXISTENTE Y VALIDA EN EL RANGO DE 6 y 7 CARACTERES
    do
    {
        do
        {
            std::cout << "CUIT A BUSCAR: ";
            std::getline(std::cin, cuit);

            // CONVERTIR A MAYUSCULA
            for (char &c : cuit)
            {
                c = std::toupper(static_cast<unsigned char>(c));
            }

        } while (!ev(cuit, 11, 11));  // VALIDAR LONGITUD DEL CUIT

        // BUSCAR EN ARCHIVO
        pos = buscarClientePorCuit(cuit.c_str()); ///CONVIERTO EL STRING DE CUIT A CONST CHAR*

        /// SI NO EXISTE >>> VUELVO A PEDIR
        if (pos == -1)
        {
            std::cout << "ERROR!! CUIT NO INEXISTENTE. Intente nuevamente.\n\n";
            system("pause");
            system("cls");
        }

    } while (pos == -1);

    /// SI EXSITE, DAMOS DE ALTA
    clsCliente cliente = leerCliente(pos);
    cliente.setEstado(true);

    if (guardarEnDiscoCliente(cliente, pos))
    {
        std::cout << "CLIENTE dado de ALTA correctamente.\n";
    }
    else
    {
        std::cout << "ERROR: No se pudo dar de ALTA al CLIENTE.\n";
    }
}


void clsGestorCliente::buscarCliente()
{
    char cuit[12];
    std::cout << "Ingrese el CUIT del cliente a buscar: ";
    std::cin >> cuit;

    int pos = buscarClientePorCuit(cuit);
    if (pos == -1)
    {
        std::cout << "Cliente inexistente.";
        return;
    }

    clsCliente cliente = leerCliente(pos);
    if (cliente.getEstado())
        mostrarUnCliente(cliente);
    else
        std::cout << "El cliente está dado de baja o inactivo";
}


int clsGestorCliente::obtenerCantidadReg (std::string pfile, clsCliente obj)
{
    FILE *p = fopen(pfile.c_str(), "rb");
    if (p == NULL)
    {
        std::cout << "No hay datos cargados actualmente.";
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
        std::cout << "No hay clientes cargados actualmente." << std::endl;
        return;
    }

    int cont = obtenerCantidadReg(_rutaDireccion.c_str(), cliente);

    if (cont <= 0)
    {
        std::cout << "No hay clientes cargados actualmente." << std::endl;
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

void clsGestorCliente::CUITdescendente()
{
    clsCliente cliente;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");

    if (p == NULL)
    {
        std::cout << "No hay clientes cargados actualmente." << std::endl;
        return;
    }

    int cont = obtenerCantidadReg(_rutaDireccion.c_str(), cliente);

    if (cont <= 0)
    {
        std::cout << "No hay clientes cargados actualmente." << std::endl;
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
            if (vecClientes[a].getCuit() < vecClientes[b].getCuit())
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
        mostrarUnCliente(vecClientes[j]);
    {
        std::cout << std::endl;
    }

    delete[] vecClientes;
}

