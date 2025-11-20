///MENU PRINCIPAL CPP
#include <iostream>
#include <limits>
#include <conio.h>

#include "clsGestorCliente.h"
#include "clsGestorVehiculo.h"
#include "clsGestorReparacion.h"
#include "clsGestorEmpleado.h"
#include "clsReparacion.h"
#include "clsMenuPrincipal.h"


///CONSTRUCTORES
clsMenuPrincipal::clsMenuPrincipal()
{
    _salir=false;
}

///METODOS MENU PRINCIPAL
void clsMenuPrincipal::mostrar()
{
    system("cls");
    std::cout << "==== TALLER MECANICO PACHECO ====" << std::endl;
    std::cout << "1 - MENU CLIENTES" << std::endl;
    std::cout << "2 - MENU VEHICULOS" << std::endl;
    std::cout << "3 - MENU EMPLEADOS" << std::endl;
    std::cout << "4 - MENU REPARACIONES" << std::endl;
    std::cout << "9 === SALIR DEL MENU ===" << std::endl;
}

void clsMenuPrincipal::elegirOpcion()
{
    std::cout << std::endl;
    std::cout << "INGRESE OPCION: ";
    _opcion = _getch()-'0';
    std::cout << std::endl;

}

void clsMenuPrincipal::opcionesMenu()
{
    switch(_opcion)
    {
    case 1:
        ejecutarMenuClientes();
        break;

    case 2:
        ejecutarMenuVehiculos();
        break;

    case 3:
        ejecutarMenuEmpleados();
        break;

    case 4:
        ejecutarMenuReparaciones();
        break;

    case 9:
        _salir=true;
        break;

    default:
        std::cout << "Error, ingrese una opcion valida" << std::endl;
        system("pause");
    }
}

void clsMenuPrincipal::ejecutarMenuPrincipal()
{
    while(_salir!=true)
    {
        mostrar();
        elegirOpcion();
        opcionesMenu();
    }
}


///METODOS MENU CLIENTES
void clsMenuPrincipal::mostrarMenuClientes()
{
    system("cls");
    std::cout << "=== MENU CLIENTES ===" << std::endl;
    std::cout << "1 - CARGAR CLIENTE" << std::endl;
    std::cout << "2 - MODIFICAR CLIENTE" << std::endl;
    std::cout << "3 - BAJA CLIENTE" << std::endl;
    std::cout << "4 - MOSTRAR TODOS LOS CLIENTES" << std::endl;
    std::cout << "5 - LISTAR CLIENTE POR CUIT" << std::endl;
    std::cout << "6 - MOSTRAR TODOS LOS CLIENTES ORDENADOS POR CUIT" << std::endl;
    std::cout << "7 - ALTA CLIENTE: " << std::endl;
    std::cout << "0 === VOLVER ===" << std::endl;
}

void clsMenuPrincipal::opcionesMenuClientes()
{
    clsGestorCliente gestorClientes;

    switch(_opcion)
    {
    case 1:
        system("cls");
        gestorClientes.cargarCliente();
        std::cout << std::endl;
        system("pause");
        break;

    case 2:
        system("cls");
        gestorClientes.modificarCliente();
        std::cout << std::endl;
        system("pause");
        break;

    case 3:
        system("cls");
        gestorClientes.bajaCliente();
        std::cout << std::endl;
        system("pause");
        break;

    case 4:
        system("cls");
        gestorClientes.mostrarTodos();
        system("pause");
        break;

    case 5:
        system("cls");
        gestorClientes.buscarCliente();
        system("pause");
        break;

    case 6:
        system("cls");
        ejecutarSubMenuCUIT(gestorClientes);
        system("pause");
        break;

    case 7:
        system("cls");
        gestorClientes.altaCliente();
        system("pause");
        break;

    case 0:
        return;
        break;

    default:
        std::cout << "Error, ingrese una opcion valida" << std::endl;
        system("pause");
        break;
    }
}

void clsMenuPrincipal::ejecutarMenuClientes()
{
    mostrarMenuClientes();
    elegirOpcion();
    opcionesMenuClientes();
}

///MENU CLIENTES:: METODOS SUBMENU CUIT
void clsMenuPrincipal::mostrarSubMenuCUIT()
{
    system("cls");
    std::cout << "=== ORDENAMIENTO POR CUIT ===" << std::endl;
    std::cout << "1-Mostrar de manera ascendente" << std::endl;
    std::cout << "2-Mostrar de manera descendente" << std::endl;
}

void clsMenuPrincipal::opcionesSubMenuCUIT(clsGestorCliente &gestorClientes)
{
    switch(_opcion)
    {
    case 1:
        system("cls");
        gestorClientes.CUITascendente();
        system("pause");
        break;

    case 2:
        system("cls");
        gestorClientes.CUITdescendente();
        system("pause");
        break;

    default:
        std::cout << "Error, ingrese una opcion valida" << std::endl;
        system("pause");
    }
}

void clsMenuPrincipal::ejecutarSubMenuCUIT(clsGestorCliente &gestorClientes)
{
    mostrarSubMenuCUIT();
    elegirOpcion();
    opcionesSubMenuCUIT(gestorClientes);
}


///METODOS MENU VEHICULOS
void clsMenuPrincipal::mostrarMenuVehiculos()
{
    system("cls");
    std::cout << "=== MENU VEHICULOS ===" << std::endl;
    std::cout << "1 - CARGAR VEHICULO" << std::endl;
    std::cout << "2 - MODIFICAR VEHICULO" << std::endl;
    std::cout << "3 - BAJA VEHICULO" << std::endl;
    std::cout << "4 - MOSTRAR TODOS LOS VEHICULOS" << std::endl;
    std::cout << "5 - BUSCAR VEHICULO POR PATENTE " << std::endl;
    std::cout << "6 - ORDENAR X PATENTE (MENOR A MAYOR)" << std::endl;
    std::cout << "7 - ALTA VEHICULO" << std::endl;
    std::cout << "0 === VOLVER ===" << std::endl;
}

void clsMenuPrincipal::opcionesMenuVehiculos()
{
    clsGestorVehiculo gestorVehiculos;

    switch(_opcion)
    {

    case 1:
        system("cls");
        gestorVehiculos.cargarVehiculo();
        std::cout << std::endl;
        system("pause");
        break;

    case 2://
        system("cls");
        gestorVehiculos.modificarVehiculo();
        std::cout << std::endl;
        system("pause");
        break;

    case 3:
        system("cls");
        gestorVehiculos.bajaVehiculo();
        std::cout << std::endl;
        system("pause");
        break;

    case 4:
        system("cls");
        gestorVehiculos.mostrarTodos();
        system("pause");
        break;

    case 5:
        system("cls");
        gestorVehiculos.buscarVehiculo();
        system("pause");
        break;

    case 6:
        system("cls");
        gestorVehiculos.OrdenarXPatente();
        system("pause");
        break;
     case 7:
        system("cls");
        gestorVehiculos.Alta_Vehiculo();
        system("pause");
        break;


    case 0:
        return;
        break;

    default:
        std::cout << "Error, ingrese una opcion valida" << std::endl;
        system("pause");
    }
}

void clsMenuPrincipal::ejecutarMenuVehiculos()
{
    mostrarMenuVehiculos();
    elegirOpcion();
    opcionesMenuVehiculos();
}


///METODOS MENU EMPLEADOS
void clsMenuPrincipal::mostrarMenuEmpleados()
{
    system("cls");
    std::cout << "=== MENU EMPLEADOS ===" << std::endl;
    std::cout << "1 - CARGAR EMPLEADO" << std::endl;
    std::cout << "2 - MODIFICAR EMPLEADO" << std::endl;
    std::cout << "3 - Baja empleado" << std::endl;
    std::cout << "4 - Mostrar todos los empleados" << std::endl;
    std::cout << "5 - Buscar por legajo" << std::endl;
    std::cout << "6 - ALTA EMPLEADO" << std::endl;
    std::cout << "0 === VOLVER ===" << std::endl;
}

void clsMenuPrincipal::opcionesMenuEmpleados()
{
    clsGestorEmpleado gestorEmpleados;

    switch(_opcion)
    {
    case 1:
        system("cls");
        gestorEmpleados.cargarEmpleado();
        std::cout << std::endl;
        system("pause");
        break;

    case 2:
        system("cls");
        gestorEmpleados.modificarEmpleado();
        std::cout << std::endl;
        system("pause");
        break;

    case 3:
        system("cls");
        gestorEmpleados.bajaEmpleado();
        std::cout << std::endl;
        system("pause");
        break;

    case 4:
        system("cls");
        gestorEmpleados.mostrarTodos();
        system("pause");
        break;

    case 5:
        system("cls");
        gestorEmpleados.buscarEmpleado();
        system("pause");
        break;


    case 6:
        system("cls");
        gestorEmpleados.altaEmpleado();
        system("pause");
        break;

    case 0:
        return;
        break;

    default:
        std::cout << "Error, ingrese una opcion valida" << std::endl;
        system("pause");
        break;
    }
}

void clsMenuPrincipal::ejecutarMenuEmpleados()
{
    mostrarMenuEmpleados();
    elegirOpcion();
    opcionesMenuEmpleados();
}


///METODOS MENU REPARACIONES
void clsMenuPrincipal::mostrarMenuReparaciones()
{
    system("cls");
    std::cout << "=== MENU REPARACIONES ===" << std::endl;
    std::cout << "1-Cargar reparacion" << std::endl;
    std::cout << "2-Mostrar reparacion por codigo de reparacion" << std::endl;
    std::cout << "3-Mostrar todas las reparaciones activas" << std::endl;
    std::cout << "4 - Cantidad de reparaciones por fecha" << std::endl;
    std::cout << "5 - RECAUDACION X EMPLEADO" << std::endl;
    std::cout << "6 - REPARACIONES X EMPLEADO" << std::endl; //MUESTRO LAS REPARACIONES DADO 1 LEGAJO ESPECIFICO
    std::cout << "7 - EMPLEADO CON MAYOR RECAUDACION $" << std::endl;
    std::cout << "8 - LISTAR DESDE X FECHA HASTA X2 FECHA " << std::endl;
    std::cout << "9 - MODIFICAR UNA REPARACION " << std::endl;
    std::cout << "0 === VOLVER ===" << std::endl;
}


///MENU REPARACIONES Y METODOS
// Función para pedir el mes y el año, y validar que estén en el rango correcto
bool pedirFecha(int& mes, int& anio)
{
    // Pedir el mes
    std::cout << "Ingrese el mes (1-12): ";
    std::cin >> mes;

    if (mes < 1 || mes > 12)
    {
        std::cout << "Mes invalido. Debe ser un valor entre 1 y 12." << std::endl;
        return false;
    }

    // Pedir el año
    std::cout << "Ingrese el año (ej. 2025): ";
    std::cin >> anio;

    if (anio < 1900 || anio > 2025)
    {
        std::cout << "Anio invalido. Debe estar entre 1900 y 2025." << std::endl;
        return false;
    }

    return true;
}


void clsMenuPrincipal::opcionesMenuReparaciones()
{
    clsGestorReparacion gestorReparacion;

    switch(_opcion)
    {
    case 1:
        system("cls");
        gestorReparacion.cargarReparacion();
        system("pause");
        break;

    case 2:
        system("cls");
        gestorReparacion.buscarReparacion();
        system("pause");
        break;

    case 3:
        system("cls");
        gestorReparacion.mostrarTodas();
        system("pause");
        break;

    case 4:
        system("cls");

        int mes, anio;

        // Llamar a la función para pedir y validar el mes y año
        if (pedirFecha(mes, anio))
        {
            // Si la entrada es válida, llamar al método con los parámetros
            gestorReparacion.cantidadReparacionesPorFecha(mes, anio);
        }

        system("pause");
        break;


    case 5:
        system("cls");
        gestorReparacion.recaudacion_X_Empleado();
        system("pause");
        break;

    case 6:
        system("cls");
        gestorReparacion.reparacion_X_Epleado();
        system("pause");
        break;

    case 7:
        system("cls");
        gestorReparacion.empleado_MAS_RECAUDACION();
        system("pause");
        break;


     case 8:
        system("cls");
        gestorReparacion.Listar_Entre_Fechas();
        system("pause");
        break;


    case 9:
        system("cls");
        gestorReparacion.modificarReparacion();
        system("pause");
        break;


    case 0:
        return;
        break;

    default:
        std::cout << "Error, ingrese una opcion valida" << std::endl;
        system("pause");
    }
}

void clsMenuPrincipal::ejecutarMenuReparaciones()
{
    mostrarMenuReparaciones();
    elegirOpcion();
    opcionesMenuReparaciones();
}
