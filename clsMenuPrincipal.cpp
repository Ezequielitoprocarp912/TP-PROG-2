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
    std::cout << "1-Menu Clientes" << std::endl;
    std::cout << "2-Menu Vehiculos" << std::endl;
    std::cout << "3-Menu Empleados" << std::endl;
    std::cout << "4-Menu Reparaciones" << std::endl;
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
    std::cout << "1-Cargar cliente" << std::endl;
    std::cout << "2-Modificar cliente" << std::endl;
    std::cout << "3-Baja cliente" << std::endl;
    std::cout << "4-Mostrar todos los clientes" << std::endl;
    std::cout << "5-Buscar por CUIT" << std::endl;
    std::cout << "6-Mostrar todos los clientes ordenados por CUIT" << std::endl;
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
    std::cout << "1-Cargar vehiculo" << std::endl;
    std::cout << "2-Modificar vehiculo" << std::endl;
    std::cout << "3-Baja vehiculo" << std::endl;
    std::cout << "4-Mostrar todos los vehiculos" << std::endl;
    std::cout << "5-Buscar vehiculo por patente" << std::endl;
    std::cout << "6-Ordenar por patente (Menor a mayor)" << std::endl;
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
    std::cout << "1-Cargar empleado" << std::endl;
    std::cout << "2-Modificar empleado" << std::endl;
    std::cout << "3-Baja empleado" << std::endl;
    std::cout << "4-Mostrar todos los empleados" << std::endl;
    std::cout << "5-Buscar por legajo" << std::endl;
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
    std::cout << "4-Recaudacion por vehiculo" << std::endl;
    std::cout << "5-Cantidad de reparaciones por fecha" << std::endl;
    std::cout << "6-Cantidad de reparaciones por empleado" << std::endl;
    std::cout << "7-Recaudacion anual" << std::endl;
    std::cout << "0 === VOLVER ===" << std::endl;
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
        gestorReparacion.recaudacionXvehiculo();
        system("pause");
        break;

    case 5:
        system("cls");
        gestorReparacion.reparacionesXfecha();
        system("pause");
        break;

    case 6:
        system("cls");
        gestorReparacion.reparacionesXempleado();
        system("pause");
        break;

    case 7:
        system("cls");
        gestorReparacion.recaudacionAnual();
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
