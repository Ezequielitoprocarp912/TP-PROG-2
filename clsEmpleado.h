#pragma once
#include "clsPersona.h"
#include "clsFecha.h"

class clsEmpleado: public clsPersona
{
    private:
    ///ATRIBUTOS
        char _numTelefono[21];
        char _mail[51];
        char _legajo[6];
        clsFecha _ingreso;
        bool _estado;

    public:
    ///CONSTRUCTORES
        clsEmpleado();

    ///SETTERS
        bool setNumTelefono(const char* telefono);
        bool setMail(const char* mail);
        bool setLegajo(const char* legajo);
        void setFechaIngreso(clsFecha ingreso);
        void setEstado(bool estado);

    ///GETTERS
        const char* getMail();
        const char* getNumTelefono();
        const char* getLegajo();
        clsFecha getIngreso();
        bool getEstado();
};
