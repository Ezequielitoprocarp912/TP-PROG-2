#pragma once
#include <iostream>
#include "clsReparacion.h"

class clsGestorReparacion
{
private:
    std::string _rutaDireccion;

public:
    /// CONSTRUCTOR
    clsGestorReparacion();

    /// MÉTODOS DE ARCHIVO
    bool guardarEnDiscoReparacion(clsReparacion);
    bool sobreEscribirEnDiscoReparacion(clsReparacion, int);
    int buscarReparacionPorCod(int);
    clsReparacion leerReparacion(int);
    int cantidadDeReparaciones();

    /// MÉTODOS DE MANIPULACIÓN
    bool ev(std::string texto, int minimo, int maximo);
    bool cargarUnaReparacion(clsReparacion &reparacion);
    void mostrarUnaReparacion(clsReparacion reparacion);
    void recaudacionXvehiculo();
    void recaudacion_X_Empleado(); ///
    void reparacion_X_Epleado();
    void recaudacionAnual();
    void empleado_MAS_RECAUDACION ();

    ///OPC 8

    void Listar_Entre_Fechas ();

    ///OPCION 9

    void modificarReparacion();

    /// METODOS DE EJECUCION
    void cargarReparacion();
    void mostrarTodas();
    void buscarReparacion(); // POR CODIGO DE REPARACION
    void cantidadReparacionesPorFecha(int mes, int anio);

};

