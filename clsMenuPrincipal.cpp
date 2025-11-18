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
    rlutil::hidecursor();
    std::cout << "====TALLER MECANICO PACHECO====" << std::endl;
    std::cout << "1-CLIENTES" << std::endl;
    std::cout << "2-VEHICULOS" << std::endl;
    std::cout << "3-EMPLEADOS" << std::endl;
    std::cout << "4-REPARACIONES" << std::endl;
    std::cout << "0-===SALIR===" << std::endl;
}

void clsMenuPrincipal::elegirOpcion()
{
    rlutil::locate(2,10); std::cout << "OPCION [ ]";
    rlutil::locate(10, 10); std::cin >> _opcion;
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

    case 0:
        _salir=true;
        break;

    default:
        std::cout << "ERROR: OPCION INVALIDA" << std::endl;
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
    std::cout << "====CLIENTES====" << std::endl;
    std::cout << "1-CARGAR" << std::endl;
    std::cout << "2-MODIFICAR" << std::endl;
    std::cout << "3-BAJAR" << std::endl;
    std::cout << "4-LISTAR TODOS" << std::endl;
    std::cout << "5-BUSCAR" << std::endl;
    std::cout << "6-LISTAR ORDENADOS" << std::endl;
    std::cout << "0-===VOLVER===" << std::endl;
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
        gestorClientes.CUITascendente();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 0:
        return;
        break;

    default:
        std::cout << "ERROR: OPCION INVALIDA" << std::endl;
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

/////MENU CLIENTES:: METODOS SUBMENU CUIT
//void clsMenuPrincipal::mostrarSubMenuCUIT()
//{
//    rlutil::cls();
//    std::cout << "=== ORDENAMIENTO POR CUIT ===" << std::endl;
//    std::cout << "1-Mostrar de manera ascendente" << std::endl;
//    std::cout << "2-Mostrar de manera descendente" << std::endl;
//}
//
//void clsMenuPrincipal::opcionesSubMenuCUIT(clsGestorCliente &gestorClientes)
//{
//    switch(_opcion)
//    {
//    case 1:
//        rlutil::cls();
//        gestorClientes.CUITascendente();
//        rlutil::anykey("Press any key to continue...\n");
//        break;
//
//    case 2:
//        rlutil::cls();
//        gestorClientes.CUITdescendente();
//        rlutil::anykey("Press any key to continue...\n");
//        break;
//
//    default:
//        std::cout << "Error, ingrese una opcion valida" << std::endl;
//        rlutil::anykey("Press any key to continue...\n");
//    }
//}
//
//void clsMenuPrincipal::ejecutarSubMenuCUIT(clsGestorCliente &gestorClientes)
//{
//    mostrarSubMenuCUIT();
//    elegirOpcion();
//    opcionesSubMenuCUIT(gestorClientes);
//}


///METODOS MENU VEHICULOS
void clsMenuPrincipal::mostrarMenuVehiculos()
{
    rlutil::cls();
    std::cout << "====VEHICULOS====" << std::endl;
    std::cout << "1-CARGAR" << std::endl;
    std::cout << "2-MODIFICAR" << std::endl;
    std::cout << "3-BAJAR" << std::endl;
    std::cout << "4-LISTAR TODOS" << std::endl;
    std::cout << "5-BUSCAR" << std::endl;
    std::cout << "6-LISTAR ORDENADOS" << std::endl;
    std::cout << "0-===VOLVER===" << std::endl;
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
        std::cout << "ERROR: OPCION INVALIDA" << std::endl;
        rlutil::anykey("Press any key to continue...\n");
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
    rlutil::cls();
    std::cout << "====EMPLEADOS====" << std::endl;
    std::cout << "1-CARGAR" << std::endl;
    std::cout << "2-MODIFICAR" << std::endl;
    std::cout << "3-BAJAR" << std::endl;
    std::cout << "4-LISTAR TODOS" << std::endl;
    std::cout << "5-BUSCAR" << std::endl;
    std::cout << "0-===VOLVER===" << std::endl;
}

void clsMenuPrincipal::opcionesMenuEmpleados()
{
    clsGestorEmpleado gestorEmpleados;

    switch(_opcion)
    {
    case 1:
        rlutil::cls();
        gestorEmpleados.cargarEmpleado();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 2:
        rlutil::cls();
        gestorEmpleados.modificarEmpleado();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 3:
        rlutil::cls();
        gestorEmpleados.bajaEmpleado();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 4:
        rlutil::cls();
        gestorEmpleados.mostrarTodos();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 5:
        rlutil::cls();
        gestorEmpleados.buscarEmpleado();
        rlutil::anykey("Press any key to continue...\n");
        break;

    case 0:
        return;
        break;

    default:
        std::cout << "ERROR: OPCION INVALIDA" << std::endl;
        rlutil::anykey("Press any key to continue...\n");
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
    rlutil::cls();
    std::cout << "====REPARACIONES====" << std::endl;
    std::cout << "1-CARGAR" << std::endl;
    std::cout << "2-BUSCAR" << std::endl;
    std::cout << "3-LISTAR TODAS" << std::endl;
    std::cout << "4-CANTIDAD EN FECHA" << std::endl;
    std::cout << "5-RECAUDACION X VEHICULO" << std::endl;
    std::cout << "6-RECAUDACION ANUAL X MES" << std::endl;
    std::cout << "0-===VOLVER===" << std::endl;
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
        std::cout << "ERROR: OPCION INVALIDA" << std::endl;
        rlutil::anykey("Press any key to continue...\n");
    }
}

void clsMenuPrincipal::ejecutarMenuReparaciones()
{
    mostrarMenuReparaciones();
    elegirOpcion();
    opcionesMenuReparaciones();
}
