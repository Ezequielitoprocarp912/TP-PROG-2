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
    if((texto.size()>=minimo)&&(texto.size()<=maximo))
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
    empleado.setFechaIngreso(F_ingreso);


    ///LEGAJO


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
        // Archivo inexistente → primer legajo
        strcpy(nuevoLegajo, "00001");
        return true;
    }

    // Ir al último registro del archivo
    fseek(p, -sizeof(clsEmpleado), SEEK_END);

    // Leer último empleado
    if (fread(&empleado, sizeof(clsEmpleado), 1, p) != 1)
    {
        fclose(p);
        strcpy(nuevoLegajo, "00001");
        return true;
    }

    fclose(p);

    // Convertir cadena a número
    int ultimo = atoi(empleado.getLegajo());
    ultimo++;

    // Formatear nuevamente a 5 digitos con ceros a la izquierda
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


/// EJECUCIÓN DE OPCIONES DE MENU
void clsGestorEmpleado::cargarEmpleado()
{
    clsEmpleado nuevo;
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
    char opcion;
    char legajo[6];

    std::cout << "Legajo del empleado a modificar: ";
    std::cin >> legajo;

    int pos;
    pos=buscarEmpleadoPorLegajo(legajo);

    if (pos !=-1)
    {
        clsEmpleado empleado = leerEmpleado(pos);

        std::cout << "DATOS ACTUALES: " << std::endl;
        std::cout << std::endl;

        mostrarUnEmpleado(empleado);

        system("pause");

        std::cout << "\n 1) Nombre\n 2) Apellido\n 3) Mail\n 4) Telefono\n 5) Direccion\n 6) Fecha de ingreso\n " << std::endl;
        std::cout << "Ingrese opcion de dato a cambiar: ";
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

        case '6':
        {
            /// FECHA Y VALIDACIONES
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

            empleado.setFechaIngreso(F_ingreso);
        }
        break;

        }


        ///EDITA EL VEHICULO EN SU POSICION CORRESPONDIENTE
        if (guardarEnDiscoEmpleado(empleado, pos))
        {
            std::cout << "EMPLEADO MODIFICADO CORRECTAMENTE" << std::endl;
        }
        else
        {
            std::cout << "ERROR: NO SE PUDO MODIFICAR EL EMPLEADO" << std::endl;
        }
    }

    else
    {
        std::cout << "ERROR: EMPLEADO NO ENCONTRADO" << std::endl;
        return;
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


