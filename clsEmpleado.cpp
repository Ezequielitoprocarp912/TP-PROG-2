#include "clsEmpleado.h"
#include <iostream>
#include <cstdio>
#include <cstring>


///CONSTRUCTOR DEFAULT
clsEmpleado::clsEmpleado()
{
    strcpy(_numTelefono, "SIN TELEFONO");
    strcpy(_mail, "SIN MAIL");
    strcpy(_legajo, "SIN TELEFONO");
    _ingreso=clsFecha();
    _estado = false;
}


///SETTERS
bool clsEmpleado::setNumTelefono(const char *telefono)
{
    if(strlen(telefono) >= 1 && strlen(telefono) <= 20)
    {
        strcpy(_numTelefono, telefono);
        return true;
    }
    else
    {
        std::cout << "Telefono no valido. Ingrese nuevamente." << std::endl;
        rlutil::anykey("Press any key to continue...\n");
        return false;
    }
}

bool clsEmpleado::setMail (const char* mail)
{
    if(strlen(mail) >= 1 && strlen(mail) <= 50)
    {
        strcpy(_mail, mail);
        return true;
    }
    else
    {
        std::cout << "Mail no valido. Ingrese nuevamente." << std::endl;
        rlutil::anykey("Press any key to continue...\n");
        return false;
    }
}

bool clsEmpleado::setLegajo(const char *legajo)
{
    if(strlen(legajo) >= 5 && strlen(legajo) <= 5)
    {
        strcpy(_legajo, legajo);
        return true;
    }
    else
    {
        std::cout << "Legajo no valido. Ingrese nuevamente." << std::endl;
        rlutil::anykey("Press any key to continue...\n");
        return false;
    }
}

void clsEmpleado::setFechaIngreso(clsFecha ingreso){
    _ingreso = ingreso;
}

void clsEmpleado::setEstado (bool estado)
{
    _estado = estado;
}


///GETTERS
const char* clsEmpleado::getMail()
{
    return _mail;
}

const char* clsEmpleado::getNumTelefono()
{
    return _numTelefono;
}

const char* clsEmpleado::getLegajo()
{
    return _legajo;
}

clsFecha clsEmpleado::getIngreso()
{
    return _ingreso;
}

bool clsEmpleado::getEstado ()
{
    return _estado;
}
