#include <cstdio>
#include <limits>
#include <cstring>

#include "clsGestorCliente.h"
#include "clsGestorVehiculo.h"
#include "clsGestorEmpleado.h"
#include "clsGestorReparacion.h"

/// CONSTRUCTOR
clsGestorReparacion::clsGestorReparacion()
{
    _rutaDireccion = "Reparacion.dat";
}


/// METODOS DE MANIPULACION
bool clsGestorReparacion::ev(std::string texto, int minimo, int maximo)
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


    /// CUIT
    do
    {
        std::cout << "CUIT DEL CLIENTE: ";
        std::getline(std::cin, cuit);
    }
    while (!ev(cuit, 11, 11));

    int posCliente = gestorCliente.buscarClientePorCuit(cuit.c_str());
    if (posCliente == -1)
    {
        std::cout << "Cliente no encontrado.\n";
        return false;
    }

    cliente = gestorCliente.leerCliente(posCliente);
    reparacion.setCliente(cliente);

    /// PATENTE
     do
    {
        std::cout << "PATENTE: ";
        std::getline(std::cin, numPatente);

        // Convertir automaticamente a MAYÚSCULAS
        for (char &c : numPatente)
        {
            c = std::toupper(static_cast<unsigned char>(c));
        }
    }
    while(!(ev(numPatente, 6, 7)));

    int posVehiculo = gestorVehiculo.buscarVehiculoPorPatente(numPatente.c_str());
    if (posVehiculo == -1)
    {
        std::cout << "Vehiculo no encontrado.\n";
        return false;
    }

    vehiculo = gestorVehiculo.leerVehiculo(posVehiculo);
    reparacion.setVehiculo(vehiculo);

    /// DESCRIPCION
    do
    {
        std::cout << "DESCRIPCION DE LA FALLA: ";
        std::getline(std::cin, descripcionFalla);
    }
    while (!ev(descripcionFalla, 1, 200));
    reparacion.setDescripcionFalla(descripcionFalla.c_str());


    /// FECHA Y VALIDACION
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

    reparacion.setFechaIngreso(F_ingreso);
    std::cout << "\nFecha cargada correctamente: " << F_ingreso.mostrar() << std::endl;


    ///EMPLEADO
    do
    {
        std::cout << "LEGAJO EMPLEADO ASIGNADO: ";
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


    ///REDAUDACION
    do
    {
        std::cout << "MONTO DE LA REPARACION: $";
        std::cin >> recaudacion;

        if (std::cin.fail() || recaudacion > 9999999 || recaudacion < 0)
        {
            std::cin.clear();
            std::cin.ignore(9999999, '\n');
            std::cout << "Valor invalido." << std::endl;
        }
    }
    while (std::cin.fail() || recaudacion > 9999999 || recaudacion < 0);

    reparacion.setRecaudacion(recaudacion);

    return true;
}


void clsGestorReparacion::mostrarUnaReparacion(clsReparacion reparacion)
{
    std::cout << "CODIGO DE REPARACION: " << reparacion.getCodReparacion() << std::endl;
    std::cout << "DESCRIPCION DE FALLA: " << reparacion.getDescripcionFalla() << std::endl;
    std::cout << "CLIENTE: " << reparacion.getCliente().getCuit() << std::endl;
    std::cout << "VEHICULO: " << reparacion.getVehiculo().getNumeroPatente() << std::endl;
    std::cout << "FECHA DE INGRESO: " << reparacion.getFechaIngreso().mostrar() << std::endl;
    std::cout << "EMPLEADO ASIGNADO: " << reparacion.getEmpleado().getApellido() << " " << "/// ";
    std::cout << "Legajo #" << reparacion.getEmpleado().getLegajo() << std::endl;
    std::cout << "MONTO DE LA REPARACION: $" << reparacion.getRecaudacion() << std::endl;
    std::cout << "-----------------------------------";
    std::cout << std::endl;
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

    system("cls");
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
        std::cout << "No hay reparaciones registradas para ese Anio." << std::endl;
        return;
    }

    ///ARREGLO DE PUNTEROS MESES
    const char* nombresMes[12] =
    {
        "ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO",
        "JULIO", "AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"
    };

    float totalAnual = 0;

    std::cout << "=== RECAUDACION DEL ANIO ======= " << anioBusqueda << " ===" << std::endl;

    for (int i = 0; i < 12; i++)
    {
        std::cout << nombresMes[i] << ": $ " << recaudacionMes[i] << std::endl;
        totalAnual += recaudacionMes[i];
    }

    std::cout << "TOTAL RECAUDACION ANUAL: $ " << totalAnual << std::endl;
}


bool clsGestorReparacion::pedirFecha(int& mes, int& anio)
{
    std::cout << "Ingrese el anio a buscar: ";
    std::cin >> anio;

    if (anio < 1900 || anio > 2025)
    {
        std::cout << "Anio invalido. Debe estar entre 1900 y 2025." << std::endl;
        return false;
    }

    std::cout << "Ingrese el mes: ";
    std::cin >> mes;

    if (mes < 1 || mes > 12)
    {
        std::cout << "Mes invalido. Debe ser un valor entre 1 y 12." << std::endl;
        return false;
    }

    return true;
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

    if (cargarUnaReparacion(reparacionNueva))
    {
        guardarEnDiscoReparacion(reparacionNueva);
        std::cout << "Reparacion guardada correctamente.\n";
    }
    else
    {
        std::cout << "No se guardo la reparacion (faltan datos validos).\n";
    }
}


void clsGestorReparacion::mostrarTodas()
{
    clsReparacion reparacion;

    FILE *file;
    file = fopen(_rutaDireccion.c_str(), "rb");

    if(file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente. " << std::endl;
        return;
    }

    while(fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if(reparacion.getEstado()==true)
        {
            mostrarUnaReparacion(reparacion);
        }
    }

    fclose(file);
}

void clsGestorReparacion::buscarReparacion()
{
    clsReparacion reparacionBuscada;

    int codReparacion;

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

void clsGestorReparacion::recaudacionXvehiculo()
{
    std::string numPatente;
    float recTotal=0;

     do
    {
        std::cout << "PATENTE: ";
        std::getline(std::cin, numPatente);

        // Convertir automáticamente a MAYÚSCULAS
        for (char &c : numPatente)
        {
            c = std::toupper(static_cast<unsigned char>(c));
        }
    }
    while(!(ev(numPatente, 6, 7)));


    FILE *file = fopen(_rutaDireccion.c_str(), "rb");

    if (file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente." << std::endl;
        return;
    }

    clsReparacion reparacion;
    bool hayDatos = false;

    system("cls");
    std::cout << "======= RECAUDACION POR VEHICULO =======" << std::endl << std::endl;

    while (fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if (reparacion.getEstado() == true)
        {
            hayDatos = true;

            if(reparacion.getVehiculo().getNumeroPatente()==numPatente)

            {
                std::cout << "PATENTE: " << reparacion.getVehiculo().getNumeroPatente() << std::endl;
                std::cout << "CUIT CLIENTE: " << reparacion.getCliente().getCuit() << std::endl;
                std::cout << "FECHA DE INGRESO: " << reparacion.getFechaIngreso().mostrar() << std::endl;
                std::cout << "RECAUDACION: $" << reparacion.getRecaudacion() << std::endl;
                std::cout << "----------------------------------------" << std::endl;
                recTotal+=reparacion.getRecaudacion();
            }
        }
    }

    std::cout << "RECAUDACION TOTAL: $" << recTotal << std::endl;

    fclose(file);

    if (!hayDatos)
    {
        std::cout << "No hay reparaciones activas registradas." << std::endl;
    }
}

void clsGestorReparacion::reparacionesXfecha()
{
    int mes, anio;
    pedirFecha(mes, anio);

    clsReparacion reparacion;
    FILE *file = fopen(_rutaDireccion.c_str(), "rb");

    if (file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente." << std::endl;
        return;
    }

    int contador = 0;
    float acu = 0;

    while (fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if (reparacion.getEstado())
        {
            clsFecha fechaIngreso = reparacion.getFechaIngreso();

            /// Compara con el mes y año que puso el usuario
            if (fechaIngreso.getMes() == mes && fechaIngreso.getAnio() == anio)
            {
                contador++;
                acu+=reparacion.getRecaudacion();
            }
        }
    }

    fclose(file);

    /// Crear solo para obtener el nombre del mes solicitado
    clsFecha fechaBuscada(1, mes, anio);

    /// MOSTRAR RESULTADO CORRECTO
    if (contador > 0)
    {
        system("cls");
        std::cout << "Cantidad de reparaciones en "
                  << fechaBuscada.mesToString() << "/" << anio
                  << ": " << contador << " /// " << "Cantidad recaudado: $" << acu << std::endl;
    }
    else
    {
        system("cls");
        std::cout << "No hay reparaciones en "
                  << fechaBuscada.mesToString() << "/" << anio
                  << "." << std::endl;
    }
}

void clsGestorReparacion::reparacionesXempleado()
{
    int mes, anio;
    clsReparacion reparacion;
    clsGestorEmpleado gestorEmpleados;

    pedirFecha(mes, anio);
    clsFecha fechaBuscada=clsFecha(1, mes, anio); /// SOLO PARA MOSTRAR MES

    int cantEmp = gestorEmpleados.obtenerCantidadReg();
    if (cantEmp == 0)
    {
        std::cout << "No hay empleados activos." << std::endl;
        return;
    }

    clsEmpleado *vecEmpleados = new clsEmpleado[cantEmp];
    gestorEmpleados.cargarEmpleados(vecEmpleados, cantEmp);
    float *recEmp = new float [cantEmp];
    int *repEmp = new int [cantEmp];

    for (int i = 0; i < cantEmp; i++)
    {
        recEmp[i] = 0;
        repEmp[i] = 0;
    }

    FILE *pReparaciones = fopen(_rutaDireccion.c_str(), "rb");
    if (pReparaciones == NULL)
    {
        std::cout << "Error al abrir reparaciones." << std::endl;
        delete[] vecEmpleados;
        delete[] recEmp;
        delete[] repEmp;
        return;
    }

    while (fread(&reparacion, sizeof(clsReparacion), 1, pReparaciones) == 1)
    {
        if(reparacion.getFechaIngreso().getAnio()==anio && reparacion.getFechaIngreso().getMes()==mes)
        {
            for (int i = 0; i < cantEmp; i++)
            {
                if (strcmp(reparacion.getEmpleado().getLegajo(), vecEmpleados[i].getLegajo()) == 0)
                {
                    recEmp[i] += reparacion.getRecaudacion();
                    repEmp[i]++;
                    break;
                }
            }
        }
    }

    fclose(pReparaciones);

    system("cls");
    std::cout << "======== RECAUDACION POR EMPLEADO " << fechaBuscada.mesToString() << "/" << anio << " ========" << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < cantEmp; i++)
    {
        std::cout << "Empleado: " << vecEmpleados[i].getApellido()
                  << " | CUIT: " << vecEmpleados[i].getCuit()
                  << " | Recaudacion Total: $" << recEmp[i]
                  << " | Reparaciones: " << repEmp[i]
                  << std::endl;
        std::cout << std::endl;
    }

    delete[] vecEmpleados;
    delete[] repEmp;
    delete[] recEmp;
}
