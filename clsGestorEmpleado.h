#pragma once
#include <iostream>
#include "clsEmpleado.h"

class clsGestorEmpleado
{
private:
    std::string _rutaDireccion;

public:
    /// CONSTRUCTOR
    clsGestorEmpleado();

    /// MÉTODOS DE MANIPULACIÓN
    bool ev(std::string texto, int minimo, int maximo);
    void cargarUnEmpleado(clsEmpleado &);
    void mostrarUnEmpleado(clsEmpleado);
    int obtenerCantidadReg (std::string pfile, clsEmpleado obj);
    ///**
    int obtenerCantidadReg ();
    //void CUITascendente();
    //void CUITdescendente();

    /// MÉTODOS DE ARCHIVO
    bool generarLegajo(char *nuevoLegajo);
    bool guardarEnDiscoEmpleado(clsEmpleado);
    bool guardarEnDiscoEmpleado(clsEmpleado, int);
    int buscarEmpleadoPorCUIT(const char *);
    int buscarEmpleadoPorLegajo(const char *);
    clsEmpleado leerEmpleado(int);

    /// EJECUCIÓN DE OPCIONES
    void cargarEmpleado();
    void modificarEmpleado();
    void mostrarTodos();
    void bajaEmpleado();
    ///HACER DESPUES ALTA EMPLEADO
    void altaEmpleado();
    void buscarEmpleado();
};
