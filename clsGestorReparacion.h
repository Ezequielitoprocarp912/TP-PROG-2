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
    bool pedirFecha(int& mes, int& anio);


    /// METODOS DE EJECUCION
    void cargarReparacion();
    void mostrarTodas();
    void buscarReparacion();
    void recaudacionAnual();
    void recaudacionXvehiculo();
    void reparacionesXfecha();
    void reparacionesXempleado();

};

