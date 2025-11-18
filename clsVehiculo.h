#pragma once
#include <cstring>

class clsVehiculo
{
private:
    char _numPatente[8];
    char _marca[20];
    char _modelo[20];
    char _tipoVehiculo;
    bool _estado;

public:
    clsVehiculo();

    bool setNumeroPatente(const char* numPatente);
    bool setMarca(const char* marca);
    bool setModelo(const char* modelo);
    bool setTipoVehiculo(char tipoVehiculo);
    void setEstado(bool estado);

    const char* getNumeroPatente();
    const char* getMarca();
    const char* getModelo();
    char getTipoVehiculo();
    bool getEstado();
};




