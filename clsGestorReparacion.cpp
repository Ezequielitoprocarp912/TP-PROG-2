#include "clsGestorReparacion.h"
#include "clsGestorCliente.h"
#include "clsGestorVehiculo.h"
#include "clsGestorEmpleado.h"
#include <cstdio>
#include <limits>
#include <cstring>

/// CONSTRUCTOR
clsGestorReparacion::clsGestorReparacion()
{
    _rutaDireccion = "Reparacion.dat";
}

bool clsGestorReparacion::ev(std::string texto, int minimo, int maximo)
{
    if ((texto.size() >= static_cast<std::string::size_type>(minimo)) &&
        (texto.size() <= static_cast<std::string::size_type>(maximo)))
    {
        return true;
    }
    else
    {
        rlutil::cls();
        std::cout << "Entrada invalida. Ingrese nuevamente" << std::endl;
        return false;
    }
}

int clsGestorReparacion::cantidadDeReparaciones()
{
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL)
    {
        return -1;
    }

    fseek(p, 0, SEEK_END);
    int cantReparaciones = ftell(p) / sizeof(clsReparacion);
    fclose(p);

    return cantReparaciones;
}

bool clsGestorReparacion::cargarUnaReparacion(clsReparacion &reparacion)
{
    int cant = cantidadDeReparaciones();
    int codRep;

    if (cant == -1)
    {
        codRep = 1;
    }
    else
    {
        codRep = cant + 1;
    }

    reparacion.setCodReparacion(codRep);
    reparacion.setEstado(true);

    std::string cuit, numPatente, descripcionFalla, legajo;
    float recaudacion;

    clsCliente cliente;
    clsVehiculo vehiculo;
    clsEmpleado empleado;
    clsGestorCliente gestorCliente;
    clsGestorVehiculo gestorVehiculo;
    clsGestorEmpleado gestorEmpleado;
    clsGestorReparacion gestorReparacion;

    std::cin.ignore();

    /// CUIT
    do {
        std::cout << "CUIT: ";
        std::getline(std::cin, cuit);
    } while (!ev(cuit, 11, 11));

    int posCliente = gestorCliente.buscarClientePorCuit(cuit.c_str());
    if (posCliente == -1) {
        std::cout << "ERROR: CLIENTE NO ENCONTRADO";
        return false;
    }

    cliente = gestorCliente.leerCliente(posCliente);
    reparacion.setCliente(cliente);

    /// PATENTE
    do {
        std::cout << "PATENTE: ";
        std::getline(std::cin, numPatente);
    } while (!ev(numPatente, 6, 7));

    int posVehiculo = gestorVehiculo.buscarVehiculoPorPatente(numPatente.c_str());
    if (posVehiculo == -1) {
        std::cout << "ERROR: VEHICULO NO ENCONTRADO";
        return false;
    }

    vehiculo = gestorVehiculo.leerVehiculo(posVehiculo);
    reparacion.setVehiculo(vehiculo);

    /// DESCRIPCION
    do {
        std::cout << "DESCRIPCION DE LA FALLA: ";
        std::getline(std::cin, descripcionFalla);
    } while (!ev(descripcionFalla, 1, 200));
    reparacion.setDescripcionFalla(descripcionFalla.c_str());

    /// RECAUDACION
    bool recaudacionValida = false;
    while (!recaudacionValida)
    {
        std::cout << "RECAUDACION: ";
        std::string recaudacionStr;
        std::getline(std::cin, recaudacionStr);

        /// Validar que no esté vacía
        if (recaudacionStr.empty())
        {
            std::cout << "ERROR: ENTRADA NO VALIDA";
            continue;
        }

        try
        {
            recaudacion = std::stof(recaudacionStr); /// convertir a float

            if (recaudacion < 0)
            {
                std::cout << "ERROR: RECAUDACION NEGATIVA";
                continue;
            }

            reparacion.setRecaudacion(recaudacion);
            recaudacionValida = true;
        }
        catch (std::exception &)
        {
            std::cout << "ERROR: ENTRADA NO VALIDA";
        }
    }

    /// FECHA Y VALIDACIONES
    clsFecha F_ingreso;
    bool fechaValida = false;
    std::string diaStr, mesStr, anioStr;
    int dia = 0, mes = 0, anio = 0;

    while (!fechaValida)
    {
        rlutil::cls();
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
                rlutil::cls();
                std::cout << "Dia invalido. Ingrese nuevamente." << std::endl;
            }

        } while (!diaOk);

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
                rlutil::cls();
                std::cout << "Mes invalido. Ingrese nuevamente." << std::endl;
            }

        } while (!mesOk);

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
                rlutil::cls();
                std::cout << "Anio invalido. Ingrese nuevamente." << std::endl;
            }

        } while (!anioOk);

        // VALIDACION COMPLETA (31/2, 29/2, etc.)
        fechaValida = F_ingreso.setFecha(dia, mes, anio);

        if (!fechaValida)
        {
            rlutil::cls();
            std::cout << "ERROR: FECHA NO VALIDA" << std::endl;
            rlutil::anykey("Press any key to continue...\n");
        }
    }

    reparacion.setFechaIngreso(F_ingreso);
    std::cout << "\nFecha cargada correctamente: " << F_ingreso.mostrar() << std::endl;

    ///EMPLEADO
    do
    {
        std::cout << "LEGAJO: ";
        std::getline(std::cin, legajo);
    }
    while (!ev(legajo, 5, 5));

    int posEmpleado = gestorEmpleado.buscarEmpleadoPorLegajo(legajo.c_str());
    if (posEmpleado == -1)
    {
        std::cout << "Empleado no encontrado.\n";
        return false;
    }

    empleado = gestorEmpleado.leerEmpleado(posEmpleado);
    reparacion.setEmpleado(empleado);

    return true;
}

void clsGestorReparacion::mostrarUnaReparacion(clsReparacion reparacion)
{
    std::cout << "CODIGO DE REPARACION: " << reparacion.getCodReparacion() << std::endl;
    std::cout << "DESCRIPCION DE FALLA: " << reparacion.getDescripcionFalla() << std::endl;
    std::cout << "CLIENTE: " << reparacion.getCliente().getCuit() << std::endl;
    std::cout << "VEHICULO: " << reparacion.getVehiculo().getNumeroPatente() << std::endl;
    std::cout << "EMPLEADO: " << reparacion.getEmpleado().getApellido() << " - ";
    std::cout << "LEGAJO: #" << reparacion.getEmpleado().getLegajo() << std::endl;
    std::cout << "FECHA DE INGRESO: " << reparacion.getFechaIngreso().mostrar() << std::endl;
    std::cout << "RECAUDACION: $" << reparacion.getRecaudacion() << std::endl;
    std::cout << "-----------------------------------";
    std::cout << std::endl;
}

///METODOS DE ARCHIVO
bool clsGestorReparacion::guardarEnDiscoReparacion(clsReparacion reparacion)
{
    FILE *p = fopen(_rutaDireccion.c_str(), "ab+");
    if (p == NULL)
    {
        std::cout << "Direccion no encontrada";
        return false;
    }

    bool grabar = fwrite(&reparacion, sizeof(clsReparacion), 1, p);
    fclose(p);
    return grabar;
}

bool clsGestorReparacion::sobreEscribirEnDiscoReparacion(clsReparacion reparacion, int pos)
{
    FILE *p = fopen(_rutaDireccion.c_str(), "rb+");
    if (p == NULL)
    {
        std::cout << "Direccion no encontrada";
        return false;
    }
    fseek(p, sizeof(clsReparacion)*pos, SEEK_SET);
    bool grabar = fwrite(&reparacion, sizeof(clsReparacion), 1, p);
    fclose(p);
    return grabar;
}

int clsGestorReparacion::buscarReparacionPorCod(int codigo)
{
    clsReparacion reparacion;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL) return -1;

    int i = 0;
    while (fread(&reparacion, sizeof(clsReparacion), 1, p))
    {
        if (reparacion.getCodReparacion() == codigo)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

clsReparacion clsGestorReparacion::leerReparacion(int pos)
{
    clsReparacion reparacion;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL) exit(1);
    fseek(p, sizeof(clsReparacion)*pos, SEEK_SET);
    fread(&reparacion, sizeof(clsReparacion), 1, p);
    fclose(p);
    return reparacion;
}

///METODOS DE EJECUCION
void clsGestorReparacion::cargarReparacion()
{
    clsReparacion reparacionNueva;

    if (cargarUnaReparacion(reparacionNueva)) {
        guardarEnDiscoReparacion(reparacionNueva);
        std::cout << "Reparacion guardada correctamente.\n";
    } else {
        std::cout << "No se guardó la reparación (faltan datos válidos).\n";
    }
}

void clsGestorReparacion::mostrarTodas()
{
    clsReparacion reparacion;

    FILE *file;
    file = fopen(_rutaDireccion.c_str(), "rb");

    if(file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente " << std::endl;
        return;
    }

    while(fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if(reparacion.getEstado()==true)
        {
            mostrarUnaReparacion(reparacion);
        }
    }

    rlutil::anykey("Press any key to continue...\n");

    fclose(file);
}

///BUSCAR REPARACION POR CODIGO DE REP
void clsGestorReparacion::buscarReparacion()
{
    clsReparacion reparacionBuscada;

    int codReparacion;

    std::cin.ignore();
    std::cout << "Codigo de reparacion a buscar: ";
    std::cin >> codReparacion;


    int pos;
    pos=buscarReparacionPorCod(codReparacion);

    reparacionBuscada = leerReparacion(pos);

    if ((pos!=-1) && (reparacionBuscada.getEstado() == true))
    {
        mostrarUnaReparacion(reparacionBuscada);
    }
    else
    {
        std::cout << "Error. Reparacion inexistente" << std::endl;
    }
}

void clsGestorReparacion::cantidadReparacionesPorFecha()
{
    int anio, mes;

    std::cout << "ANIO: ";
    std::cin >> anio;

    std::cout << "MES: ";
    std::cin >> mes;

    clsReparacion reparacion;

    FILE *file = fopen(_rutaDireccion.c_str(), "rb");

    if (file == NULL) {
        std::cout << "ERROR: ARCHIVO INEXISTENTE..." << std::endl;
        return;
    }

    int contador = 0;

    clsFecha fechaIngreso;

    while (fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if (reparacion.getEstado() == true)///Asegurarse de que la reparación esté activa
        {
            fechaIngreso = reparacion.getFechaIngreso();///Obtener la fecha de ingreso

            if (fechaIngreso.getMes() == mes && fechaIngreso.getAnio() == anio) {contador++;}///AUMENTAR EL CONTADOR SI LAS FECHAS COINCIDEN
        }
    }

    fclose(file);

    ///Mostrar resultado
    if (contador > 0) {
        std::cout << "CANTIDAD DE REPARACIONES EN " << fechaIngreso.mesToString() << "/" << anio << ": " << contador << std::endl;
    } else {
        std::cout << "NO SE ENCONTRARON REPARACIONES EN " << fechaIngreso.mesToString() << "/" << anio << std::endl;
    }
}

void clsGestorReparacion::recaudacionXvehiculo()
{
    FILE *file = fopen(_rutaDireccion.c_str(), "rb");

    if (file == NULL)
    {
        std::cout << "ERROR: ARCHIVO VACIO" << std::endl;
        return;
    }

    clsReparacion reparacion;
    bool hayDatos = false;

    rlutil::cls();
    std::cout << "======= RECAUDACION POR VEHICULO =======" << std::endl << std::endl;

    while (fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if (reparacion.getEstado() == true)
        {
            hayDatos = true;

            std::cout << "PATENTE: " << reparacion.getVehiculo().getNumeroPatente() << std::endl;
            std::cout << "CUIT CLIENTE: " << reparacion.getCliente().getCuit() << std::endl;
            std::cout << "FECHA DE INGRESO: " << reparacion.getFechaIngreso().mostrar() << std::endl;
            std::cout << "RECAUDACION: $" << reparacion.getRecaudacion() << std::endl;
            std::cout << "----------------------------------------" << std::endl;
        }
    }

    fclose(file);

    if (!hayDatos)
    {
        std::cout << "No hay reparaciones activas registradas." << std::endl;
    }
}

void clsGestorReparacion::recaudacionAnual()
{
    FILE *file = fopen(_rutaDireccion.c_str(), "rb");

    if (file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente." << std::endl;
        return;
    }

    clsReparacion reparacion;
    bool hayDatos = false;
    float recaudacionMes[12] = {0};

    rlutil::cls();
    std::cout << "======= RECAUDACION ANUAL POR MES =======" << std::endl << std::endl;

    int anioBusqueda;
    std::cout << "Ingrese el anio a consultar: ";
    std::cin >> anioBusqueda;

    while (fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if (reparacion.getEstado())
        {
            clsFecha f = reparacion.getFechaIngreso();
            int mes = f.getMes();
            int anio = f.getAnio();

            if (mes >= 1 && mes <= 12 && anio == anioBusqueda)
            {
                recaudacionMes[mes - 1] += reparacion.getRecaudacion();
                hayDatos = true;
            }
        }
    }

    fclose(file);

    if (!hayDatos)
    {
        std::cout << "No hay reparaciones registradas para ese año." << std::endl;
        return;
    }

    ///ARREGLO DE PUNTEROS MESES
    const char* nombresMes[12] = {
        "ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO",
        "JULIO", "AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"
    };

    float totalAnual = 0;

    std::cout << "=== RECAUDACION DEL AÑO ======= " << anioBusqueda << " ===" << std::endl;

    for (int i = 0; i < 12; i++)
    {
        std::cout << nombresMes[i] << ": $ " << recaudacionMes[i] << std::endl;
        totalAnual += recaudacionMes[i];
    }

    std::cout << "TOTAL RECAUDACION ANUAL: $ " << totalAnual << std::endl;
}
