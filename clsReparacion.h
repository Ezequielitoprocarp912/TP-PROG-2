#pragma once

#include "clsCliente.h"
#include "clsVehiculo.h"
#include "clsEmpleado.h"
#include "clsFecha.h"

class clsReparacion
{
    private:
    ///ATRIBUTOS
        int _codReparacion;
        char _descripcionFalla [200];
        clsCliente _cliente;
        clsVehiculo _vehiculo;
        clsEmpleado _empleado;
        clsFecha _ingreso;
        clsFecha _reparado;
        clsFecha _egreso;
        bool _estado;
        float _recaudacion;

    public:
    ///CONSTRUCTORES
        clsReparacion();

    ///SETTERS
        void setCodReparacion (int codReparacion);
        bool setDescripcionFalla (const char* descripcionFalla);
        void setCliente (clsCliente cliente);
        void setVehiculo (clsVehiculo vehiculo);
        void setEmpleado (clsEmpleado empleado);
        void setFechaIngreso(clsFecha ingreso);
        void setFechaReparado(clsFecha reparado);
        void setFechaEgreso(clsFecha egreso);
        void setEstado(bool estado);
        void setRecaudacion (float recaudacion);


    ///GETTERS
        int getCodReparacion();
        const char* getDescripcionFalla();
        clsCliente getCliente();
        clsVehiculo getVehiculo();
        clsEmpleado getEmpleado();
        clsFecha getFechaIngreso();
        clsFecha getFechaReparado();
        clsFecha getFechaEgreso();
        bool getEstado();
        float getRecaudacion();

};
