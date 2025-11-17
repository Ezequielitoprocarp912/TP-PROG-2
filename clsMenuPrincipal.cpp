#include "clsMenuPrincipal.h"
#include <iostream>
#include <limits>

///CONSTRUCTORES
clsMenuPrincipal::clsMenuPrincipal()
{
    _salir=false;
}

///METODOS MENU PRINCIPAL
void clsMenuPrincipal::mostrar()
{
    rlutil::cls();
    std::cout << "==== TALLER MECANICO PACHECO ====" << std::endl;
    std::cout << "1-Menu Clientes" << std::endl;
    std::cout << "2-Menu Vehiculos" << std::endl;
    std::cout << "3-Menu Reparaciones" << std::endl;
    std::cout << "9 === SALIR DEL MENU ===" << std::endl;
}

void clsMenuPrincipal::elegirOpcion()
{
    std::cout << std::endl;
    std::cout << "INGRESE OPCION: ";
    std::cin >> _opcion;
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
        ejecutarMenuReparaciones();
        break;

    case 9:
        _salir=true;
        break;

    default:
        std::cout << "Error, ingrese una opcion valida" << std::endl;
        rlutil::anykey("Press any key to continue...\n");
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
    rlutil::cls();
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
        rlutil::cls();
        gestorClientes.cargarCliente();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 2:
        rlutil::cls();
        gestorClientes.modificarCliente();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 3:
        rlutil::cls();
        gestorClientes.bajaCliente();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 4:
        rlutil::cls();
        gestorClientes.mostrarTodos();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 5:
        rlutil::cls();
        gestorClientes.buscarCliente();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 6:
        rlutil::cls();
        ejecutarSubMenuCUIT(gestorClientes);
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 0:
        return;
        break;

    default:
        std::cout << "Error, ingrese una opcion valida" << std::endl;
        rlutil::anykey("Press any key to continue...\n");
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
    rlutil::cls();
    std::cout << "=== ORDENAMIENTO POR CUIT ===" << std::endl;
    std::cout << "1-Mostrar de manera ascendente" << std::endl;
    std::cout << "2-Mostrar de manera descendente" << std::endl;
}

void clsMenuPrincipal::opcionesSubMenuCUIT(clsGestorCliente &gestorClientes)
{
    switch(_opcion)
    {
    case 1:
        rlutil::cls();
        gestorClientes.CUITascendente();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 2:
        rlutil::cls();
        gestorClientes.CUITdescendente();
        rlutil::anykey("Press any key to continue...\n");
        break;

    default:
        std::cout << "Error, ingrese una opcion valida" << std::endl;
        rlutil::anykey("Press any key to continue...\n");
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
    rlutil::cls();
    std::cout << "=== MENU VEHICULOS ===" << std::endl;
    std::cout << "1-Cargar vehiculo" << std::endl;
    std::cout << "2-Modificar vehiculo" << std::endl;
    std::cout << "3-Baja vehiculo" << std::endl;
    std::cout << "4-Mostrar todos los vehiculos" << std::endl;
    std::cout << "5-Buscar por PATENTE" << std::endl;
    std::cout << "6-ORDENAR POR PATENTE (MENOR A MAYOR)" << std::endl;
    std::cout << "0 === VOLVER ===" << std::endl;
}

void clsMenuPrincipal::opcionesMenuVehiculos()
{
    clsGestorVehiculo gestorVehiculos;

    switch(_opcion)
    {

    case 1:
        rlutil::cls();
        gestorVehiculos.cargarVehiculo();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 2://
        rlutil::cls();
        gestorVehiculos.modificarVehiculo();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 3:
        rlutil::cls();
        gestorVehiculos.bajaVehiculo();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 4:
        rlutil::cls();
        gestorVehiculos.mostrarTodos();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 5:
        rlutil::cls();
        gestorVehiculos.buscarVehiculo();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 6:
        rlutil::cls();
        gestorVehiculos.OrdenarXPatente();
        rlutil::anykey("Press any key to continue...\n");
        break;


    case 0:
        return;
        break;

    default:
        std::cout << "Error, ingrese una opcion valida" << std::endl;
        rlutil::anykey("Press any key to continue...\n");
    }
}

void clsMenuPrincipal::ejecutarMenuVehiculos()
{
    mostrarMenuVehiculos();
    elegirOpcion();
    opcionesMenuVehiculos();
}

///METODOS MENU REPARACIONES
void clsMenuPrincipal::mostrarMenuReparaciones()
{
    rlutil::cls();
    std::cout << "=== MENU REPARACIONES ===" << std::endl;
    std::cout << "1-Cargar reparacion" << std::endl;
    std::cout << "2-Mostrar reparacion por codigo de reparacion" << std::endl;
    std::cout << "3-Mostrar todas las reparaciones activas" << std::endl;
    std::cout << "4-CANTIDAD REPARACIONES X FECHA" << std::endl;
    std::cout << "5-RECAUDACION X VEHICULO " << std::endl;
    std::cout << "6-RECAUDACION ANUAL X MES" << std::endl;
    std::cout << "0 === VOLVER ===" << std::endl;
}

///MENU REPARACIONES Y METODOS
void clsMenuPrincipal::opcionesMenuReparaciones()
{
    clsGestorReparacion gestorReparacion;

    switch(_opcion)
    {
    case 1:
        rlutil::cls();
        gestorReparacion.cargarReparacion();
        rlutil::anykey("Press any key to continue...\n");
        break;
    case 2:
        rlutil::cls();
        gestorReparacion.buscarReparacion();
        rlutil::anykey("Press any key to continue...\n");
        break;
    case 3:
        rlutil::cls();
        gestorReparacion.mostrarTodas();
        rlutil::anykey("Press any key to continue...\n");
        break;
    case 4:
        rlutil::cls();
        gestorReparacion.cantidadReparacionesPorFecha();
        rlutil::anykey("Press any key to continue...\n");
        break;
    case 5:
        rlutil::cls();
        gestorReparacion.recaudacionXvehiculo();
        rlutil::anykey("Press any key to continue...\n");
        break;
    case 6:
        rlutil::cls();
        gestorReparacion.recaudacionAnual();
        rlutil::anykey("Press any key to continue...\n");
        break;
    case 0:
        return;
        break;
    default:
        std::cout << "Error, ingrese una opcion valida" << std::endl;
        rlutil::anykey("Press any key to continue...\n");
    }
}

void clsMenuPrincipal::ejecutarMenuReparaciones()
{
    mostrarMenuReparaciones();
    elegirOpcion();
    opcionesMenuReparaciones();
}
