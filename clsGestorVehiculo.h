#pragma once
#include "clsVehiculo.h"
#include <string>

class clsGestorVehiculo
{
private:
    std::string _rutaDireccion; /// Guarda la ruta del archivo donde se guardan los registros

public:
    clsGestorVehiculo();

    /// Carga y muestra un vehículo
    void cargarUnVehiculo(clsVehiculo &vehiculo); // Cargar datos de un vehículo
    void mostrarUnVehiculo(clsVehiculo vehiculo); // Mostrar los datos de un vehículo

    /// Métodos de manipulación de archivo
    bool ev(std::string texto, int minimo, int maximo); // Validación de longitud
    bool guardarEnDiscoVehiculo(clsVehiculo registro); // Guardar al final
    bool guardarEnDiscoVehiculo(clsVehiculo registro, int posicion); // Guardar en posición específica
    int buscarVehiculoPorPatente(const char* patenteBuscada); // Buscar vehículo por patente
    clsVehiculo leerVehiculo(int posicion); // Leer vehículo en posición del archivo
    int obtenerCantidadReg(std::string pfile, clsVehiculo obj); // Contar registros activos

    /// Ejecución de opciones
    void cargarVehiculo();
    void modificarVehiculo();
    void mostrarTodos();
    void bajaVehiculo();
    void buscarVehiculo();
    void OrdenarXPatente();
    void Alta_Vehiculo();
};

