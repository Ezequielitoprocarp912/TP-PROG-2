#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

#include "clsGestorEmpleado.h"
#include "clsEmpleado.h"

/// CONSTRUCTOR
clsGestorEmpleado::clsGestorEmpleado()
{
    _rutaDireccion = "Empleado.dat";
}


/// MÉTODOS DE MANIPULACIÓN
bool clsGestorEmpleado::ev(std::string texto, int minimo, int maximo)
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

void clsGestorEmpleado::cargarUnEmpleado(clsEmpleado &empleado)
{
    std::string cuit;
    std::string nombre;
    std::string apellido;
    std::string telefono;
    std::string mail;
    std::string direccion;
    std::string legajo;


    ///CUIT
    do
    {
        std::cout << "CUIT: ";
        std::getline(std::cin, cuit);
    }
    while(!(ev(cuit, 11, 11)));

    empleado.setCuit(cuit.c_str());

    ///NOMBRE
    do
    {
        std::cout << "NOMBRE: ";
        std::getline(std::cin, nombre);
    }
    while(!(ev(nombre, 1, 20)));

    empleado.setNombre(nombre.c_str());

    ///APELLIDO
    do
    {
        std::cout << "APELLIDO: ";
        std::getline(std::cin, apellido);
    }
    while(!(ev(apellido, 1, 20)));

    empleado.setApellido(apellido.c_str());


    ///TELEFONO
    do
    {
        std::cout << "NUM TELEFONO : ";
        std::getline(std::cin, telefono);
    }
    while(!(ev(telefono, 1, 20)));

    empleado.setNumTelefono(telefono.c_str());


    ///MAIL
    do
    {
        std::cout << "MAIL : ";
        std::getline(std::cin, mail);
    }
    while(!(ev(mail, 1, 50)));

    empleado.setMail(mail.c_str());


    ///DIRECCION
    do
    {
        std::cout << "DIRECCION : ";
        std::getline(std::cin, direccion);
    }
    while(!(ev(direccion, 1, 50)));

    empleado.setDireccion(direccion.c_str());


    ///FECHA DE INGRESO
    clsFecha F_ingreso;
    bool fechaValida = false;
    std::string diaStr, mesStr, anioStr;
    int dia = 0, mes = 0, anio = 0;

    while (!fechaValida)
    {
        system("cls");
        std::cout << "=== INGRESE LA FECHA DE INGRESO ===" << std::endl;

        // DIA
        bool diaOk = false;
        do
        {
            std::cout << "Dia: ";
            std::getline(std::cin, diaStr);

            if (!ev(diaStr, 1, 2)) continue;

            dia = atoi(diaStr.c_str());
            if (dia >= 1 && dia <= 31)
            {
                diaOk = true;
            }
            else
            {
                system("cls");
                std::cout << "Dia invalido. Ingrese nuevamente." << std::endl;
            }

        }
        while (!diaOk);

        // MES
        bool mesOk = false;
        do
        {
            std::cout << "Mes: ";
            std::getline(std::cin, mesStr);

            if (!ev(mesStr, 1, 2)) continue;

            mes = atoi(mesStr.c_str());
            if (mes >= 1 && mes <= 12)
            {
                mesOk = true;
            }
            else
            {
                system("cls");
                std::cout << "Mes invalido. Ingrese nuevamente." << std::endl;
            }

        }
        while (!mesOk);

        // ANIO
        bool anioOk = false;
        do
        {
            std::cout << "Anio: ";
            std::getline(std::cin, anioStr);

            if (!ev(anioStr, 4, 4)) continue;

            anio = atoi(anioStr.c_str());
            if (anio >= 1900 && anio <= 2025)
            {
                anioOk = true;
            }
            else
            {
                system("cls");
                std::cout << "Anio invalido. Ingrese nuevamente." << std::endl;
            }

        }
        while (!anioOk);

        // VALIDACION COMPLETA (31/2, 29/2, etc.)
        fechaValida = F_ingreso.setFecha(dia, mes, anio);

        if (!fechaValida)
        {
            system("cls");
            std::cout << "La combinacion de fecha es invalida (por ejemplo 31/2 o 29/2 no bisiesto)." << std::endl;
            system("pause");
        }
    }

    ///FECHA DE INGRESO
    empleado.setFechaIngreso(F_ingreso);

    /// LEGAJO AUTOMATICO
    char nuevoLegajo[6];
    generarLegajo(nuevoLegajo);
    empleado.setLegajo(nuevoLegajo);

    empleado.setEstado(true);

}

void clsGestorEmpleado::mostrarUnEmpleado(clsEmpleado empleado)
{
    std::cout << "CUIT: " << empleado.getCuit() << std::endl;
    std::cout << "NOMBRE: " << empleado.getNombre() << std::endl;
    std::cout << "APELLIDO: " << empleado.getApellido() << std::endl;
    std::cout << "TELEFONO: " << empleado.getNumTelefono() << std::endl;
    std::cout << "MAIL: " << empleado.getMail() << std::endl;
    std::cout << "DIRECCION: " << empleado.getDireccion() << std::endl;
    std::cout << "FECHA DE INGRESO: " << empleado.getIngreso().mostrar() << std::endl;
    std::cout << "LEGAJO: " << empleado.getLegajo() << std::endl;

    std::cout << "-----------------------------------";
    std::cout << std::endl;
}


///METODOS DE ARCHIVO
bool clsGestorEmpleado::generarLegajo(char *nuevoLegajo)
{
    clsEmpleado empleado;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");

    if (p == NULL)
    {
        strcpy(nuevoLegajo, "00001");
        return true;
    }

    // Verificar tamaño del archivo
    fseek(p, 0, SEEK_END);
    long size = ftell(p);

    if (size < (long)sizeof(clsEmpleado))
    {
        fclose(p);
        strcpy(nuevoLegajo, "00001");
        return true;
    }

    // Ir al ultimo empleado
    fseek(p, -(long)sizeof(clsEmpleado), SEEK_END);

    if (fread(&empleado, sizeof(clsEmpleado), 1, p) != 1) //-1 ES, SI NO SE PUDO LEER EL ULTIMO EMPLEADO, PONER 00001
    {
        fclose(p);
        strcpy(nuevoLegajo, "00001");
        return true;
    }

    fclose(p);

    int ultimo = atoi(empleado.getLegajo());
    ultimo++;

    sprintf(nuevoLegajo, "%05d", ultimo);

    return true;
}


bool clsGestorEmpleado::guardarEnDiscoEmpleado(clsEmpleado empleado)
{
    FILE *p = fopen(_rutaDireccion.c_str(), "ab+");
    if (p == NULL) return false;
    bool ok = fwrite(&empleado, sizeof(clsEmpleado), 1, p);
    fclose(p);
    return ok;
}

bool clsGestorEmpleado::guardarEnDiscoEmpleado(clsEmpleado empleado, int pos)
{
    FILE *p = fopen(_rutaDireccion.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, sizeof(clsEmpleado) * pos, SEEK_SET);
    bool ok = fwrite(&empleado, sizeof(clsEmpleado), 1, p);
    fclose(p);
    return ok;
}

int clsGestorEmpleado::buscarEmpleadoPorCUIT(const char *cuit)
{
    clsEmpleado empleado;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL) return -1;

    int i = 0;
    while (fread(&empleado, sizeof(clsEmpleado), 1, p))
    {
        if (strcmp(empleado.getCuit(), cuit) == 0)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

int clsGestorEmpleado::buscarEmpleadoPorLegajo(const char *legajo)
{
    clsEmpleado empleado;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL) return -1;

    int i = 0;
    while (fread(&empleado, sizeof(clsEmpleado), 1, p))
    {
        if (strcmp(empleado.getLegajo(), legajo) == 0)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}


///PREGUNTAR DESPUES
clsEmpleado clsGestorEmpleado::leerEmpleado(int pos)
{
    clsEmpleado empleado;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL) exit(1);
    fseek(p, sizeof(clsEmpleado) * pos, SEEK_SET);
    fread(&empleado, sizeof(clsEmpleado), 1, p);
    fclose(p);
    return empleado;
}







/// **************** EJECUCIÓN DE OPCIONES DE MENU ****************
void clsGestorEmpleado::cargarEmpleado()
{
    clsEmpleado nuevo;   /// SE LLAMA 1RO AL COSNTRUCTOR DE PERSONA () LUEGO AL DE EMPLEADO
    cargarUnEmpleado(nuevo);

    if (buscarEmpleadoPorCUIT(nuevo.getCuit()) != -1)
    {
        std::cout << "ERROR: El empleado ya existe";
        return;
    }

    if (guardarEnDiscoEmpleado(nuevo))
        std::cout << "Empleado guardado exitosamente";
    else
        std::cout << "ERROR: No se pudo guardar el empleado";
}

void clsGestorEmpleado::modificarEmpleado()
{
    std::string legajo;

    int pos = -1;

    /// BUCLE HASTA QUE PATENTE SEA EXISTENTE Y VALIDA EN EL RANGO DE 6 y 7 CARACTERES
    do
    {
        do
        {
            std::cout << "INGRESAR LEGAJO DE EMPLEADO A MODIFICAR: ";
            std::getline(std::cin, legajo);
        } while (!ev(legajo, 5, 5)); //VALIDAR LONGITUD 00001

        /// BUSCAR EN ARCHIVO
        pos = buscarEmpleadoPorLegajo(legajo.c_str());

        /// SI NO EXISTE >>> VUELVO A PEDIR
        if (pos == -1)
        {
            std::cout << "ERROR: EMPLEADO INEXISTENTE. Intente nuevamente.\n\n";
            system("pause");
            system("cls");
        }

    } while (pos == -1); ///MIENTRAS LA LONGITUD NO COINCIDA Y EL LEGAJO SEA INEXISTENTE, SIGUE EL BUCLE


        clsEmpleado empleado = leerEmpleado(pos);
        std::cout << "DATOS ACTUALES: " << std::endl;
        std::cout << std::endl;

        mostrarUnEmpleado(empleado);

        system("pause");

        char opcion;

        do {
        system("cls");
        mostrarUnEmpleado(empleado);

        std::cout<<std::endl;
        std::cout << "\n 1) Nombre\n 2) Apellido\n 3) Mail\n 4) Telefono\n 5) Direccion\n 6) Fecha de ingreso\n 7) GUARDAR Y SALIR\n" << std::endl;
        std::cout << "Ingrese opcion de dato a cambiar: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

            empleado.setNombre(nombre.c_str());
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

            empleado.setApellido(apellido.c_str());
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

            empleado.setMail(mail.c_str());
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
            while(!(ev(telefono, 1, 20)));

            empleado.setNumTelefono(telefono.c_str());
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

            empleado.setDireccion(direccion.c_str());
        }
        break;



/// +++++++++++++++++++++ FECHA Y VALIDACIONES +++++++++++++++++++++
        case '6':
        {
            clsFecha F_ingreso;
            bool fechaValida = false;
            std::string diaStr, mesStr, anioStr;
            int dia = 0, mes = 0, anio = 0;

            while (!fechaValida)
            {
                system("cls");
                std::cout << "=== INGRESE LA FECHA DE INGRESO ===" << std::endl;

                // DIA
                bool diaOk = false;
                do
                {
                    std::cout << "Dia: ";
                    std::getline(std::cin, diaStr);

                    if (!ev(diaStr, 1, 2)) continue;

                    ///ATOI
                    dia = atoi(diaStr.c_str()); // 12 > 12/0 ESTILO CADENA CARACTERES GRACIAS A STR LUEGO ATOI LO CONVIERTE A ENTERO > RESULTADO FINAL = 12 AHORA ES UN NUMERO USABLE
                    if (dia >= 1 && dia <= 31)
                    {
                        diaOk = true;
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Dia invalido. Ingrese nuevamente." << std::endl;
                    }

                }
                while (!diaOk);

                // MES
                bool mesOk = false;
                do
                {
                    std::cout << "Mes: ";
                    std::getline(std::cin, mesStr);

                    if (!ev(mesStr, 1, 2)) continue;

                    mes = atoi(mesStr.c_str());
                    if (mes >= 1 && mes <= 12)
                    {
                        mesOk = true;
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Mes invalido. Ingrese nuevamente." << std::endl;
                    }

                }
                while (!mesOk);

                // ANIO
                bool anioOk = false;
                do
                {
                    std::cout << "Anio: ";
                    std::getline(std::cin, anioStr);

                    if (!ev(anioStr, 4, 4)) continue;

                    anio = atoi(anioStr.c_str());
                    if (anio >= 1900 && anio <= 2025)
                    {
                        anioOk = true;
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Anio invalido. Ingrese nuevamente." << std::endl;
                    }

                }
                while (!anioOk);

                /// VALIDACION COMPLETA (31/2, 29/2, etc.)
                //SETFECHA 1. CARGA LOS VALORES _DIA = DIA ETC 2. LLAMA A ValidarFecha()
                fechaValida = F_ingreso.setFecha(dia, mes, anio);

                if (!fechaValida)
                {
                    system("cls");
                    std::cout << "La combinacion de fecha es invalida (por ejemplo 31/2 o 29/2 no bisiesto)." << std::endl;
                    system("pause");
                }
            }

            empleado.setFechaIngreso(F_ingreso);
        }
        break;

            case '7':
            break;
            default:
            std::cout << "Opcion no valida." << std::endl;
            system("pause");

        }
} while(opcion != '7');


        ///EDITA EL EMPLEADO EN SU POSICION CORRESPONDIENTE
        if (guardarEnDiscoEmpleado(empleado, pos))
        {
            std::cout << "EMPLEADO MODIFICADO CORRECTAMENTE" << std::endl;
        }
        else
        {
            std::cout << "ERROR: NO SE PUDO MODIFICAR EL EMPLEADO" << std::endl;
        }

}



void clsGestorEmpleado::mostrarTodos()
{
    clsEmpleado empleado;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL)
    {
        std::cout << "No hay empleados cargados actualmente.";
        return;
    }

    while (fread(&empleado, sizeof(clsEmpleado), 1, p))
    {
        if (empleado.getEstado())
            mostrarUnEmpleado(empleado);
    }
    fclose(p);
}

void clsGestorEmpleado::bajaEmpleado()
{
    char legajo[6];
    std::cout << "Ingrese el legajo del empleado a eliminar: ";
    std::cin >> legajo;

    int pos = buscarEmpleadoPorLegajo(legajo);
    if (pos == -1)
    {
        std::cout << "ERROR: Empleado no encontrado.";
        return;
    }

    clsEmpleado empleado = leerEmpleado(pos);
    empleado.setEstado(false);
    guardarEnDiscoEmpleado(empleado, pos);

    std::cout << "Empleado dado de baja correctamente.";
}

void clsGestorEmpleado::buscarEmpleado()
{
    char legajo[6];
    std::cout << "Ingrese el legajo del empleado a buscar: ";
    std::cin >> legajo;

    int pos = buscarEmpleadoPorLegajo(legajo);
    if (pos == -1)
    {
        std::cout << "Empleado inexistente.";
        return;
    }

    clsEmpleado empleado = leerEmpleado(pos);
    if (empleado.getEstado())
        mostrarUnEmpleado(empleado);
    else
        std::cout << "El empleado esta dado de baja o inactivo";
}


int clsGestorEmpleado::obtenerCantidadReg (std::string pfile, clsEmpleado obj)
{
    FILE *p = fopen(pfile.c_str(), "rb");
    if (p == NULL)
    {
        std::cout << "No hay datos cargados actualmente.";
        return 0;
    }

    int cont = 0;
    while (fread(&obj, sizeof(clsEmpleado), 1, p))
    {
        if (obj.getEstado()==true)
        {
            cont++;
        }
    }

    fclose(p);

    return cont;
}


/// ALTAA EMPLEADOO +++

void clsGestorEmpleado::altaEmpleado()
{
    std::string legajo;

    int pos = -1;

    /// BUCLE HASTA QUE PATENTE SEA EXISTENTE Y VALIDA EN EL RANGO DE 6 y 7 CARACTERES
    do
    {
        do
        {
            std::cout << "LEGAJO A BUSCAR: ";
            std::getline(std::cin, legajo);



        } while (!ev(legajo, 5, 5));  // VALIDAR LONGITUD DEL LEGAJO

        // BUSCAR EN ARCHIVO
        pos = buscarEmpleadoPorLegajo(legajo.c_str()); ///CONVIERTO EL STRING DE LEGAJO A CONST CHAR*

        /// SI NO EXISTE >>> VUELVO A PEDIR
        if (pos == -1)
        {
            std::cout << "ERROR: EMPLEADOU NO ENCONTRADO. Intente nuevamente.\n\n";
            system("pause");
            system("cls");
        }

    } while (pos == -1);

    /// SI EXSITE, DAMOS DE ALTA
    clsEmpleado empleado = leerEmpleado(pos);
    empleado.setEstado(true);

    if (guardarEnDiscoEmpleado(empleado, pos))
    {
        std::cout << "EMPLEADO dado de ALTA correctamente.\n";
    }
    else
    {
        std::cout << "ERROR: No se pudo dar de ALTA al EMPLEADO.\n";
    }
}


int clsGestorEmpleado::obtenerCantidadReg()
{
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL)
    {
        std::cout << "No hay datos cargados actualmente.";
        return 0;
    }

    fseek(p, 0, SEEK_END);
    int cant = ftell(p)/sizeof (clsEmpleado);
    fclose(p);

    return cant;
}
