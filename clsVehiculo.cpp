/// clsVehiculo.cpp
#include <iostream>
#include <cstring>
#include "clsVehiculo.h"

clsVehiculo::clsVehiculo()
{
    strcpy(_numPatente,"0000000");
    strcpy(_marca,"SIN MARCA");
    strcpy(_modelo,"SIN MODELO");
    _tipoVehiculo = '0';
    _estado = false;
}

bool clsVehiculo::setNumeroPatente(const char* numPatente)
{
    if(strlen(numPatente) >= 6 && strlen(numPatente) <= 7)
    {
        strcpy(_numPatente, numPatente);
        return true;
    }
    std::cout << "Patente no valida.\n";
    system("pause");
    return false;
}

bool clsVehiculo::setMarca(const char* marca)
{
    if(strlen(marca) >= 1 && strlen(marca) <= 20)
    {
        strcpy(_marca, marca);
        return true;
    }
    std::cout << "Marca no valida.\n";
    system("pause");
    return false;
}

bool clsVehiculo::setModelo(const char* modelo)
{
    if(strlen(modelo) >= 1 && strlen(modelo) <= 20)
    {
        strcpy(_modelo, modelo);
        return true;
    }
    std::cout << "Modelo no valido.\n";
    system("pause");
    return false;
}

bool clsVehiculo::setTipoVehiculo(char tipoVehiculo)
{
    if(tipoVehiculo=='1'||tipoVehiculo=='2'||tipoVehiculo=='3'||tipoVehiculo=='4')
    {
        _tipoVehiculo = tipoVehiculo;
        return true;
    }
    std::cout << "Tipo no valido.\n";
    system("pause");
    return false;
}

void clsVehiculo::setEstado(bool estado)
{
    _estado = estado;
}

const char* clsVehiculo::getNumeroPatente()
{
    return _numPatente;
}
const char* clsVehiculo::getMarca()
{
    return _marca;
}
const char* clsVehiculo::getModelo()
{
    return _modelo;
}
char clsVehiculo::getTipoVehiculo()
{
    return _tipoVehiculo;
}
bool clsVehiculo::getEstado()
{
    return _estado;
}

