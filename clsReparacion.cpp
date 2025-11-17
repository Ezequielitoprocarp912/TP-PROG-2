#include "clsReparacion.h"

///CONSTRUCTORES
clsReparacion::clsReparacion()
{
    _codReparacion=0;
    strcpy(_descripcionFalla, "");
    _cliente=clsCliente();
    _vehiculo=clsVehiculo();
    _empleado=clsEmpleado();
    _ingreso=clsFecha();
    _reparado=clsFecha();
    _egreso=clsFecha();
    _estado=false;
}

///SETTERS
bool clsReparacion::setDescripcionFalla(const char* descripcionFalla)
{
    if(strlen(descripcionFalla) >= 1 && strlen(descripcionFalla) <= 200)
    {
        strcpy(_descripcionFalla, descripcionFalla);
        return true;
    }
    else
    {
        return false;
    }
}

void clsReparacion::setCodReparacion (int codReparacion)
{
    _codReparacion=codReparacion;
}

void clsReparacion::setCliente(clsCliente cliente)
{
    _cliente=cliente;
}

void clsReparacion::setVehiculo(clsVehiculo vehiculo)
{
    _vehiculo=vehiculo;
}

void clsReparacion::setEmpleado(clsEmpleado empleado)
{
    _empleado=empleado;
}

void clsReparacion::setFechaIngreso(clsFecha ingreso)
{
    _ingreso=ingreso;
}

void clsReparacion::setFechaReparado(clsFecha reparado)
{
    _reparado=reparado;
}

void clsReparacion::setFechaEgreso(clsFecha egreso)
{
    _egreso=egreso;
}

void clsReparacion::setEstado(bool estado)
{
    _estado=estado;
}

///GETTERS
int clsReparacion::getCodReparacion()
{
    return _codReparacion;
}

const char* clsReparacion::getDescripcionFalla()
{
    return _descripcionFalla;
}

clsCliente clsReparacion::getCliente()
{
    return _cliente;
}

clsVehiculo clsReparacion::getVehiculo()
{
    return _vehiculo;
}

clsEmpleado clsReparacion::getEmpleado()
{
    return _empleado;
}

clsFecha clsReparacion::getFechaIngreso()
{
    return _ingreso;
}


clsFecha clsReparacion::getFechaReparado()
{
    return _reparado;
}


clsFecha clsReparacion::getFechaEgreso()
{
    return _egreso;
}

bool clsReparacion::getEstado()
{
    return _estado;
}
