#include <cstdio>
#include <limits>
#include <cstring>

#include "clsGestorCliente.h"
#include "clsGestorVehiculo.h"
#include "clsGestorEmpleado.h"
#include "clsGestorReparacion.h"

/// CONSTRUCTOR
clsGestorReparacion::clsGestorReparacion()
{
    _rutaDireccion = "Reparacion.dat";
}


/// METODOS DE MANIPULACION
bool clsGestorReparacion::ev(std::string texto, int minimo, int maximo)
{
    if (texto.size() >= static_cast<std::size_t>(minimo) &&
            texto.size() <= static_cast<std::size_t>(maximo))
    {
        return true;
    }
    else
    {
        system("cls");
        std::cout << "Entrada invalida. Ingrese nuevamente" << std::endl;
        return false;
    }
}


int clsGestorReparacion::cantidadDeReparaciones()
{
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL)
    {
        return -1;
    }

    fseek(p, 0, SEEK_END);
    int cantReparaciones = ftell(p) / sizeof(clsReparacion);
    fclose(p);

    return cantReparaciones;
}


bool clsGestorReparacion::cargarUnaReparacion(clsReparacion &reparacion)
{
    int cant = cantidadDeReparaciones();
    int codRep;

    if (cant == -1)
    {
        codRep = 1;
    }
    else
    {
        codRep = cant + 1;
    }

    reparacion.setCodReparacion(codRep);
    reparacion.setEstado(true);

    std::string cuit, numPatente, descripcionFalla, legajo;
    float recaudacion;

    clsCliente cliente;
    clsVehiculo vehiculo;
    clsEmpleado empleado;
    clsGestorCliente gestorCliente;
    clsGestorVehiculo gestorVehiculo;
    clsGestorEmpleado gestorEmpleado;


    /// CUIT
    do
    {
        std::cout << "CUIT: ";
        std::getline(std::cin, cuit);
    }
    while (!ev(cuit, 11, 11));

    int posCliente = gestorCliente.buscarClientePorCuit(cuit.c_str());
    if (posCliente == -1)
    {
        std::cout << "Cliente no encontrado.\n";
        return false;
    }

    cliente = gestorCliente.leerCliente(posCliente);
    reparacion.setCliente(cliente);

    /// PATENTE
    do
    {
        std::cout << "PATENTE: ";
        std::getline(std::cin, numPatente);
    }
    while (!ev(numPatente, 6, 7));

    int posVehiculo = gestorVehiculo.buscarVehiculoPorPatente(numPatente.c_str());
    if (posVehiculo == -1)
    {
        std::cout << "Vehiculo no encontrado.\n";
        return false;
    }

    vehiculo = gestorVehiculo.leerVehiculo(posVehiculo);
    reparacion.setVehiculo(vehiculo);

    /// DESCRIPCION
    do
    {
        std::cout << "DESCRIPCION DE LA FALLA: ";
        std::getline(std::cin, descripcionFalla);
    }
    while (!ev(descripcionFalla, 1, 200));
    reparacion.setDescripcionFalla(descripcionFalla.c_str());


    /// FECHA Y VALIDACION
    clsFecha F_ingreso;
    bool fechaValida = false;
    std::string diaStr, mesStr, anioStr;
    int dia = 0, mes = 0, anio = 0;

    while (!fechaValida)
    {
        system("cls");
        std::cout << "=== INGRESE LA FECHA DE INGRESO ===" << std::endl;

        // DIA
        bool diaOk = false;
        do
        {
            std::cout << "Dia: ";
            std::getline(std::cin, diaStr);

            if (!ev(diaStr, 1, 2)) continue;

            dia = atoi(diaStr.c_str());
            if (dia >= 1 && dia <= 31)
            {
                diaOk = true;
            }
            else
            {
                system("cls");
                std::cout << "Dia invalido. Ingrese nuevamente." << std::endl;
            }

        }
        while (!diaOk);

        // MES
        bool mesOk = false;
        do
        {
            std::cout << "Mes: ";
            std::getline(std::cin, mesStr);

            if (!ev(mesStr, 1, 2)) continue;

            mes = atoi(mesStr.c_str());
            if (mes >= 1 && mes <= 12)
            {
                mesOk = true;
            }
            else
            {
                system("cls");
                std::cout << "Mes invalido. Ingrese nuevamente." << std::endl;
            }

        }
        while (!mesOk);

        // ANIO
        bool anioOk = false;
        do
        {
            std::cout << "Anio: ";
            std::getline(std::cin, anioStr);

            if (!ev(anioStr, 4, 4)) continue;

            anio = atoi(anioStr.c_str());
            if (anio >= 1900 && anio <= 2025)
            {
                anioOk = true;
            }
            else
            {
                system("cls");
                std::cout << "Anio invalido. Ingrese nuevamente." << std::endl;
            }

        }
        while (!anioOk);

        // VALIDACION COMPLETA (31/2, 29/2, etc.)
        fechaValida = F_ingreso.setFecha(dia, mes, anio);

        if (!fechaValida)
        {
            system("cls");
            std::cout << "La combinacion de fecha es invalida (por ejemplo 31/2 o 29/2 no bisiesto)." << std::endl;
            system("pause");
        }
    }

    reparacion.setFechaIngreso(F_ingreso);
    std::cout << "\nFecha cargada correctamente: " << F_ingreso.mostrar() << std::endl;


    ///EMPLEADO
    do
    {
        std::cout << "LEGAJO EMPLEADO: ";
        std::getline(std::cin, legajo);
    }
    while (!ev(legajo, 5, 5));

    int posEmpleado = gestorEmpleado.buscarEmpleadoPorLegajo(legajo.c_str());
    if (posEmpleado == -1)
    {
        std::cout << "Empleado no encontrado.\n";
        return false;
    }

    empleado = gestorEmpleado.leerEmpleado(posEmpleado);
    reparacion.setEmpleado(empleado);


    ///REDAUDACION


    do
    {
        std::cout << "MONTO DE LA REPARACION: $";
        std::cin >> recaudacion;

        if (std::cin.fail() || recaudacion > 9999999 || recaudacion < 0)
        {
            std::cin.clear();
            std::cin.ignore(9999999, '\n');
            std::cout << "Valor invalido." << std::endl;
        }
    }
    while (std::cin.fail() || recaudacion > 9999999 || recaudacion < 0);

    reparacion.setRecaudacion(recaudacion);

    return true;
}


void clsGestorReparacion::mostrarUnaReparacion(clsReparacion reparacion)
{
    std::cout << "CODIGO DE REPARACION: " << reparacion.getCodReparacion() << std::endl;
    std::cout << "DESCRIPCION DE FALLA: " << reparacion.getDescripcionFalla() << std::endl;
    std::cout << "CLIENTE: " << reparacion.getCliente().getCuit() << std::endl;
    std::cout << "VEHICULO: " << reparacion.getVehiculo().getNumeroPatente() << std::endl;
    std::cout << "FECHA DE INGRESO: " << reparacion.getFechaIngreso().mostrar() << std::endl;
    std::cout << "EMPLEADO ASIGNADO: " << reparacion.getEmpleado().getApellido() << " " << "/// ";
    std::cout << "Legajo #" << reparacion.getEmpleado().getLegajo() << std::endl;
    std::cout << "MONTO DE LA REPARACION: " << reparacion.getRecaudacion() << std::endl;
    std::cout << "-----------------------------------";
    std::cout << std::endl;
}


///REC $ VEHICULO
void clsGestorReparacion::recaudacionXvehiculo()
{
    FILE *file = fopen(_rutaDireccion.c_str(), "rb");

    if (file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente." << std::endl;
        return;
    }

    clsReparacion reparacion;
    bool hayDatos = false;

    system("cls");
    std::cout << "======= RECAUDACION POR VEHICULO =======" << std::endl << std::endl;

    while (fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if (reparacion.getEstado() == true)
        {
            hayDatos = true;

            std::cout << "PATENTE: " << reparacion.getVehiculo().getNumeroPatente() << std::endl;
            std::cout << "CUIT CLIENTE: " << reparacion.getCliente().getCuit() << std::endl;
            std::cout << "FECHA DE INGRESO: " << reparacion.getFechaIngreso().mostrar() << std::endl;
            std::cout << "RECAUDACION: $" << reparacion.getRecaudacion() << std::endl;
            std::cout << "----------------------------------------" << std::endl;
        }
    }

    fclose(file);

    if (!hayDatos)
    {
        std::cout << "No hay reparaciones activas registradas." << std::endl;
    }
}

///EJERCICIO TOBI GODD




void clsGestorReparacion::recaudacion_X_Empleado()
{
    std::string legajo;
    do
    {
        std::cout << "LEGAJO EMPLEADO: ";
        std::getline(std::cin, legajo);
    }
    while (!ev(legajo, 5, 5));

    //ABRO ARCHIVO
    FILE *file = fopen(_rutaDireccion.c_str(), "rb");

    if (file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente." << std::endl;
        return;
    }

    clsReparacion reparacion;
    bool hayDatos = false;

    system("cls");
    std::cout << "======= RECAUDACION POR EMPLEADO =======" << std::endl << std::endl;


    float acum=0;
    //PROCESO EL ARCHIVO
    while (fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if (reparacion.getEstado() == true)
        {
            hayDatos = true;
            if (strcmp(reparacion.getEmpleado().getLegajo(), legajo.c_str()) ==0 )
            {
                std::cout << "LEGAJO: " << reparacion.getEmpleado().getLegajo() << std::endl;
                //std::cout << "CUIT CLIENTE: " << reparacion.getCliente().getCuit() << std::endl;
                //std::cout << "FECHA DE INGRESO: " << reparacion.getFechaIngreso().mostrar() << std::endl;
                std::cout << "RECAUDACION: $" << reparacion.getRecaudacion() << std::endl;
                std::cout << "----------------------------------------" << std::endl;
                acum += reparacion.getRecaudacion();
            }
        }
    }
    std::cout<< "RECAUDACION TOTAL: $ " << acum << std::endl;
    fclose(file);

    if (!hayDatos)
    {
        std::cout << "No hay reparaciones activas registradas." << std::endl;
    }

}






///METODO 6 EN EL MENU REP

void clsGestorReparacion::reparacion_X_Epleado()
{

    std::string legajo;
    do
    {
        std::cout << "LEGAJO EMPLEADO A BUSCAR: ";
        std::getline(std::cin, legajo);
    }
    while (!ev(legajo, 5, 5));

    //ABRO ARCHIVO
    FILE *file = fopen(_rutaDireccion.c_str(), "rb");

    if (file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente." << std::endl;
        return;
    }


    ///INSTANCIAMOS REP
    clsReparacion reparacion;
    bool hayDatos = false;

    system("cls");
    std::cout << "======= REPARACION! X EMPLEADO =======" << std::endl << std::endl;

    while (fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if (reparacion.getEstado() == true)
        {
            hayDatos = true;
            if (strcmp(reparacion.getEmpleado().getLegajo(), legajo.c_str()) ==0 )
            {
                std::cout<< "CODIGO REPARACION: " << reparacion.getCodReparacion() << std::endl;
                std::cout << "LEGAJO: " << reparacion.getEmpleado().getLegajo() << std::endl;

                std::cout << "CUIT CLIENTE: " << reparacion.getCliente().getCuit() << std::endl;
                std::cout << "NOMBRE + APELLIDO CLIENTE: " << reparacion.getCliente().getNombre() << " " << reparacion.getCliente().getApellido() << std::endl;

                std::cout << "PATENTE  VEHICULO: " << reparacion.getVehiculo().getNumeroPatente() << std::endl;
                std::cout << "MARCA + MODELO: " << reparacion.getVehiculo().getMarca() << " " << reparacion.getVehiculo().getModelo() << std::endl;
                std::cout << "TIPO VEHICULO: ";


                switch(reparacion.getVehiculo().getTipoVehiculo())
                {
                case '1':
                    std::cout << "AUTO" << std::endl;
                    break;
                case '2':
                    std::cout << "CAMIONETA" << std::endl;
                    break;
                case '3':
                    std::cout << "CAMION" << std::endl;
                    break;
                case '4':
                    std::cout << "TRANSPORTE" << std::endl;
                    break;
                default:
                    std::cout << "AUTO" << std::endl;
                }
                std::cout << std::endl;

                std::cout << "FECHA DE INGRESO: " << reparacion.getFechaIngreso().mostrar() << std::endl;
                std::cout << "RECAUDACION: $" << reparacion.getRecaudacion() << std::endl;
                std::cout << "----------------------------------------" << std::endl;

            }
        }
    }

    fclose(file);
    if (hayDatos==false)
    {
        std::cout << "NO HAY NAAA";
    }

}











void clsGestorReparacion::recaudacionAnual()
{
    FILE *file = fopen(_rutaDireccion.c_str(), "rb");

    if (file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente." << std::endl;
        return;
    }

    clsReparacion reparacion;
    bool hayDatos = false;
    float recaudacionMes[12] = {0};

    system("cls");
    std::cout << "======= RECAUDACION ANUAL POR MES =======" << std::endl << std::endl;

    int anioBusqueda;
    std::cout << "Ingrese el anio a consultar: ";
    std::cin >> anioBusqueda;

    while (fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if (reparacion.getEstado())
        {
            clsFecha f = reparacion.getFechaIngreso();
            int mes = f.getMes();
            int anio = f.getAnio();

            if (mes >= 1 && mes <= 12 && anio == anioBusqueda)
            {
                recaudacionMes[mes - 1] += reparacion.getRecaudacion();
                hayDatos = true;
            }
        }
    }

    fclose(file);

    if (!hayDatos)
    {
        std::cout << "No hay reparaciones registradas para ese Anio." << std::endl;
        return;
    }

    ///ARREGLO DE PUNTEROS MESES
    const char* nombresMes[12] =
    {
        "ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO",
        "JULIO", "AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"
    };

    float totalAnual = 0;

    std::cout << "=== RECAUDACION DEL ANIO ======= " << anioBusqueda << " ===" << std::endl;

    for (int i = 0; i < 12; i++)
    {
        std::cout << nombresMes[i] << ": $ " << recaudacionMes[i] << std::endl;
        totalAnual += recaudacionMes[i];
    }

    std::cout << "TOTAL RECAUDACION ANUAL: $ " << totalAnual << std::endl;
}



///METODOS DE ARCHIVO
bool clsGestorReparacion::guardarEnDiscoReparacion(clsReparacion reparacion)
{
    FILE *p = fopen(_rutaDireccion.c_str(), "ab+");
    if (p == NULL)
    {
        std::cout << "Direccion no encontrada";
        return false;
    }

    bool grabar = fwrite(&reparacion, sizeof(clsReparacion), 1, p);
    fclose(p);
    return grabar;
}


bool clsGestorReparacion::sobreEscribirEnDiscoReparacion(clsReparacion reparacion, int pos)
{
    FILE *p = fopen(_rutaDireccion.c_str(), "rb+");
    if (p == NULL)
    {
        std::cout << "Direccion no encontrada";
        return false;
    }
    fseek(p, sizeof(clsReparacion)*pos, SEEK_SET);
    bool grabar = fwrite(&reparacion, sizeof(clsReparacion), 1, p);
    fclose(p);
    return grabar;
}


int clsGestorReparacion::buscarReparacionPorCod(int codigo)
{
    clsReparacion reparacion;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL) return -1;

    int i = 0;
    while (fread(&reparacion, sizeof(clsReparacion), 1, p))
    {
        if (reparacion.getCodReparacion() == codigo)
        {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}


clsReparacion clsGestorReparacion::leerReparacion(int pos)
{
    clsReparacion reparacion;
    FILE *p = fopen(_rutaDireccion.c_str(), "rb");
    if (p == NULL) exit(1);
    fseek(p, sizeof(clsReparacion)*pos, SEEK_SET);
    fread(&reparacion, sizeof(clsReparacion), 1, p);
    fclose(p);
    return reparacion;
}


///METODOS DE EJECUCION
void clsGestorReparacion::cargarReparacion()
{
    clsReparacion reparacionNueva;

    if (cargarUnaReparacion(reparacionNueva))
    {
        guardarEnDiscoReparacion(reparacionNueva);
        std::cout << "Reparacion guardada correctamente.\n";
    }
    else
    {
        std::cout << "No se guardo la reparacion (faltan datos validos).\n";
    }
}


void clsGestorReparacion::mostrarTodas()
{
    clsReparacion reparacion;

    FILE *file;
    file = fopen(_rutaDireccion.c_str(), "rb");

    if(file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente " << std::endl;
        return;
    }

    while(fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if(reparacion.getEstado()==true)
        {
            mostrarUnaReparacion(reparacion);
        }
    }

    fclose(file);
}

///BUSCAR REPARACION POR CODIGO DE REP
void clsGestorReparacion::buscarReparacion()
{
    clsReparacion reparacionBuscada;

    int codReparacion;

    std::cout << "Codigo de reparacion a buscar: ";
    std::cin >> codReparacion;

    int pos;
    pos=buscarReparacionPorCod(codReparacion);

    reparacionBuscada = leerReparacion(pos);

    if ((pos!=-1) && (reparacionBuscada.getEstado() == true))
    {
        mostrarUnaReparacion(reparacionBuscada);
    }
    else
    {
        std::cout << "Error. Reparacion inexistente" << std::endl;
    }
}

void clsGestorReparacion::cantidadReparacionesPorFecha(int mes, int anio)
{
    clsReparacion reparacion;
    FILE *file = fopen(_rutaDireccion.c_str(), "rb");

    if (file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente." << std::endl;
        return;
    }

    int contador = 0;

    // RECORRER ARCHIVO
    while (fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if (reparacion.getEstado())   // Solo reparaciones activas
        {
            clsFecha fechaIngreso = reparacion.getFechaIngreso();

            // Compara con el mes y año que puso el usuario
            if (fechaIngreso.getMes() == mes &&
                    fechaIngreso.getAnio() == anio)
            {
                contador++;
            }
        }
    }

    fclose(file);

    // Crear solo para obtener el nombre del mes solicitado
    clsFecha fechaBuscada(1, mes, anio);

    // MOSTRAR RESULTADO CORRECTO
    if (contador > 0)
    {
        std::cout << "Cantidad de reparaciones en "
                  << fechaBuscada.mesToString() << "/" << anio
                  << ": " << contador << std::endl;
    }
    else
    {
        std::cout << "No hay reparaciones en "
                  << fechaBuscada.mesToString() << "/" << anio
                  << "." << std::endl;
    }
}


void clsGestorReparacion::empleado_MAS_RECAUDACION()
{

    //ABRO ARCHIVO
    FILE *file = fopen(_rutaDireccion.c_str(), "rb");

    if (file == NULL)
    {
        std::cout << "No hay reparaciones cargadas actualmente." << std::endl;
        return;
    }

    clsReparacion reparacion; // TODOS LOS DATOS DE REPARACION


    system("cls");
    std::cout << "======= RECAUDACION POR EMPLEADO =======" << std::endl << std::endl;


    float acum; ///NO PONGO ACA EN CERO
    //PROCESO EL ARCHIVO
    clsGestorEmpleado empleado_GEST;
    clsEmpleado empleado; //TODOS LOS DATOS ESTAN ACA


    int cantEmpleados = empleado_GEST.obtenerCantidadReg(); /// SE LA CANTIDAD DE REGISTROS
    int cantidad_REPARACIONES = cantidadDeReparaciones();
    float Recaudacion_MAX = 0;
    char legajo_MAX[6];

    for (int i=0; i<cantEmpleados; i++)
    {
        empleado = empleado_GEST.leerEmpleado(i); //RECCORIENDO TODOS LOS ESPACIOS SE CARGA TODO LOS DATOS DEL EMPLEADO EN ESA POS
        /// POR CADA EMPLEADO RECORRO TODAS LAS REPARACIONES PARA CUANTAS HIZO ESE EMPLEADO QUE ESTOY LEYENDO
        acum = 0; // POR CADA EMPLEADO LO REINICIAMOS A CERO
        for (int x=0 ; x<cantidad_REPARACIONES; x++)
        {
            reparacion = leerReparacion(x);
            if ( strcmp(reparacion.getEmpleado().getLegajo() , empleado.getLegajo()) == 0 && reparacion.getEstado()==true)
            {
                acum += reparacion.getRecaudacion(); // SUMO CADA VEZ QUE COINCIDE EL LEGAJO EMPLEADO
            }
        }
        ///ACA SE CUANTO ACUMULO EL EMPLEADO QUE ESTA VINIENDO EJ: EMPLEADO n 1
        if (acum > Recaudacion_MAX)
        {
            Recaudacion_MAX = acum;
            strcpy(legajo_MAX, empleado.getLegajo());
        }

    }
    /// MOSTRAR ACA
    std::cout<< "RECAUDACION TOTAL: $ " << acum << std::endl;
    std::cout<< "LEGAJO: " << legajo_MAX << std::endl;

    fclose(file);
}



void clsGestorReparacion::Listar_Entre_Fechas()
{

      int dia, mes, anio;
      clsFecha Fecha_1;

bool FechaOk=false;
do{
      std::cout<<"FECHA 1 "<< std::endl;
      std::cout<<"INGRESAR DIA: ";
      std::cin>> dia;
      std::cout<<"INGRESAR MES: ";
      std::cin>> mes;
      std::cout<<"INGRESAR ANIO: ";
      std::cin>> anio;
      std::cout<<std::endl;

      Fecha_1.setFecha(dia, mes, anio);
      FechaOk = Fecha_1.validarFecha();
       if (FechaOk==false){
            std::cout<< "FECHA 1 INVALIDA: " <<std::endl;
            system("pause");
            system("cls");
      }

}while (!FechaOk);



     FechaOk=false;
     clsFecha Fecha_2;
do{
      std::cout<<"FECHA 2 "<< std::endl;
      std::cout<<"INGRESAR DIA: ";
      std::cin>> dia;
      std::cout<<"INGRESAR MES: ";
      std::cin>> mes;
      std::cout<<"INGRESAR ANIO: ";
      std::cin>> anio;
      std::cout<<std::endl;

      Fecha_2.setFecha(dia, mes, anio);
      FechaOk = Fecha_2.validarFecha();
      if (FechaOk==false){
            std::cout<< "FECHA 2 INVALIDA: " <<std::endl;
            system("pause");
            system("cls");
      }

}while (!FechaOk);



    clsReparacion reparacion;

    FILE *file;
    file = fopen(_rutaDireccion.c_str(), "rb");

    if(file == NULL)
    {
        std::cout << "No hay REPARACIONES cargadas actualmente " << std::endl;
        return;
    }

    while(fread(&reparacion, sizeof(clsReparacion), 1, file))
    {
        if( (reparacion.getEstado()==true) && (reparacion.getFechaIngreso() > Fecha_1) && (reparacion.getFechaIngreso() < Fecha_2) )
        {
            //std::cout<< "FECHA 1: " << Fecha_1.mostrar();
            //std::cout<< "FECHA 2: "<< Fecha_2.mostrar();
            //std::cout<< "FECHA EN REPARACION: " << reparacion.getFechaIngreso().mostrar();
            mostrarUnaReparacion(reparacion);
        }
    }

    fclose(file);




}



/// OPCION 9 MENU > MODIFICAR REPARACION

void clsGestorReparacion::modificarReparacion()
{
    int codigoREP;
    std::cout<< "INGRESAR CODIGO REPARACION: ";
    std::cin>> codigoREP;
    int pos = -1;
    do
    {

        /// BUSCAR EN ARCHIVO
        pos = buscarReparacionPorCod(codigoREP);

        /// SI NO EXISTE >>> VUELVO A PEDIR
        if (pos == -1)
        {
            std::cout << "ERROR: REPARACION INEXISTENTE. Intente nuevamente.\n\n";
            system("pause");
            system("cls");
        }

    } while (pos == -1); ///MIENTRAS LA LONGITUD NO COINCIDA Y EL LEGAJO SEA INEXISTENTE, SIGUE EL BUCLE


        clsReparacion reparacion = leerReparacion(pos);
        std::cout << "DATOS ACTUALES: " << std::endl;
        std::cout << std::endl;

        mostrarUnaReparacion(reparacion);

        system("pause");

        char opcion;

        do {
        system("cls");
        mostrarUnaReparacion(reparacion);

        std::cout<<std::endl;
        std::cout << "\n 1) Nombre\n 2) Apellido\n 3) Mail\n 4) Telefono\n 5) Direccion\n 6) Fecha de ingreso\n 7) GUARDAR Y SALIR\n" << std::endl;
        std::cout << "Ingrese opcion de dato a cambiar: ";
        std::cin >> opcion;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch(opcion)
        {
            /*
        case '1':
        {
            std::string nombre;
            do
            {
                std::cout << "NOMBRE: ";
                std::getline(std::cin, nombre);
            }
            while(!(ev(nombre, 1, 20)));

            empleado.setNombre(nombre.c_str());
        }
        break;

        case '2':
        {
            std::string apellido;
            do
            {
                std::cout << "APELLIDO: ";
                std::getline(std::cin, apellido);
            }
            while(!(ev(apellido, 1, 20)));

            empleado.setApellido(apellido.c_str());
        }
        break;

        case '3':
        {
            std::string mail;
            do
            {
                std::cout << "MAIL: ";
                std::getline(std::cin, mail);
            }
            while(!(ev(mail, 1, 50)));

            empleado.setMail(mail.c_str());
        }
        break;

        case '4':
        {
            std::string telefono;
            do
            {
                std::cout << "NUM TELEFONO: ";
                std::getline(std::cin, telefono);
            }
            while(!(ev(telefono, 1, 20)));

            empleado.setNumTelefono(telefono.c_str());
        }
        break;


        case '5':
        {
            std::string direccion;
            do
            {
                std::cout << "DIRECCION: ";
                std::getline(std::cin, direccion);
            }
            while(!(ev(direccion, 1, 50)));

            empleado.setDireccion(direccion.c_str());
        }
        break;


*/
/// +++++++++++++++++++++ FECHA Y VALIDACIONES +++++++++++++++++++++
        case '6':
        {
            clsFecha F_ingreso;
            bool fechaValida = false;
            std::string diaStr, mesStr, anioStr;
            int dia = 0, mes = 0, anio = 0;

            while (!fechaValida)
            {
                system("cls");
                std::cout << "=== INGRESE LA FECHA DE INGRESO ===" << std::endl;

                // DIA
                bool diaOk = false;
                do
                {
                    std::cout << "Dia: ";
                    std::getline(std::cin, diaStr);

                    if (!ev(diaStr, 1, 2)) continue;

                    ///ATOI
                    dia = atoi(diaStr.c_str()); // 12 > 12/0 ESTILO CADENA CARACTERES GRACIAS A STR LUEGO ATOI LO CONVIERTE A ENTERO > RESULTADO FINAL = 12 AHORA ES UN NUMERO USABLE
                    if (dia >= 1 && dia <= 31)
                    {
                        diaOk = true;
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Dia invalido. Ingrese nuevamente." << std::endl;
                    }

                }
                while (!diaOk);

                // MES
                bool mesOk = false;
                do
                {
                    std::cout << "Mes: ";
                    std::getline(std::cin, mesStr);

                    if (!ev(mesStr, 1, 2)) continue;

                    mes = atoi(mesStr.c_str());
                    if (mes >= 1 && mes <= 12)
                    {
                        mesOk = true;
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Mes invalido. Ingrese nuevamente." << std::endl;
                    }

                }
                while (!mesOk);

                // ANIO
                bool anioOk = false;
                do
                {
                    std::cout << "Anio: ";
                    std::getline(std::cin, anioStr);

                    if (!ev(anioStr, 4, 4)) continue;

                    anio = atoi(anioStr.c_str());
                    if (anio >= 1900 && anio <= 2025)
                    {
                        anioOk = true;
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Anio invalido. Ingrese nuevamente." << std::endl;
                    }

                }
                while (!anioOk);

                /// VALIDACION COMPLETA (31/2, 29/2, etc.)
                //SETFECHA 1. CARGA LOS VALORES _DIA = DIA ETC 2. LLAMA A ValidarFecha()
                fechaValida = F_ingreso.setFecha(dia, mes, anio);

                if (!fechaValida)
                {
                    system("cls");
                    std::cout << "La combinacion de fecha es invalida (por ejemplo 31/2 o 29/2 no bisiesto)." << std::endl;
                    system("pause");
                }
            }

            reparacion.setFechaIngreso(F_ingreso);
        }
        break;

            case '7':
            break;
            default:
            std::cout << "Opcion no valida." << std::endl;
            system("pause");

        }
} while(opcion != '7');


        ///EDITA EL EMPLEADO EN SU POSICION CORRESPONDIENTE
        if (sobreEscribirEnDiscoReparacion(reparacion, pos))
        {
            std::cout << "REPARACION MODIFICADA CORRECTAMENTE" << std::endl;
        }
        else
        {
            std::cout << "ERROR: NO SE PUDO MODIFICAR LA REPARACION" << std::endl;
        }

}
