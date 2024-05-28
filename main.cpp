#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "binary_operations_lib.h"
#include "leer_equipos.h"

int main(){
    FILE *f= fopen("C:\\Users\\lauta\\Desktop\\SEGOVIA LAUTARO\\Parciales\\Info2\\Parcial1\\network_structure.dat","rb");
    if(f==NULL){
        printf("error al abrir el archivo\n");
        return 0;
    }
    int cant_disp= countDevices(f);
    rewind(f);
    int c=0;
    uint64_t h;
    uint16_t ids;
    Registro *v= new Registro[cant_disp];
    while(fread(&h, sizeof(uint64_t), 1, f)!=0)
    {
        //extraigo los IDs de los equipos (el actual y el que esta en el nivel superior)
        v[c].IDs.ID= exxtract_ID(h, 48, 63);
        v[c].IDs.ID_sup= exxtract_ID(h, 0, 15);
        //extraigo el tipo de equipo
        v[c].type= exxtract_segment_64bits(h, 24, 25);
        //segun el tipo extraigo la informacion que se requiera de cada uno
        if(v[c].type == 0){ //es un cpu
            v[c].eq_nivel_inf= exxtract_segment_64bits(h, 32, 47); 
            v[c].id_inf= new uint16_t[(v[c].eq_nivel_inf)]; //la cantidad de equipos conectados al cpu es dinamica, depende de cada cpu
            //guardo los IDs de los equipos conectados despues del actual
            for(int i=0; i<(v[c].eq_nivel_inf); i++){
                fread(&ids, sizeof(uint16_t), 1, f);
                v[c].id_inf[i]= ids;
            }
        }
        if(v[c].type == 1) //es un sensor
            v[c].info= exxtract_segment_64bits(h, 20, 21);
            v[c].eq_nivel_inf=1;
        if(v[c].type == 2) //es un actuador
            v[c].info= exxtract_segment_64bits(h, 23, 23);
            v[c].eq_nivel_inf=1;
        if(v[c].type == 3){ //es un conector
            v[c].eq_nivel_inf= exxtract_segment_64bits(h, 32, 47); 
            v[c].id_inf= new uint16_t[(v[c].eq_nivel_inf)]; //la cantidad de equipos conectados al conector tambien es dinamica
            //guardo los IDs de los equipos conectados despues del actual
            for(int i=0; i<(v[c].eq_nivel_inf); i++){
                fread(&ids, sizeof(uint16_t), 1, f);
                v[c].id_inf[i]= ids;
            }
        }
        c++;
    }
    showIDs(v, cant_disp);
    for(int i=0; i<v[i].eq_nivel_inf; i++){
        if(v[c].eq_nivel_inf>0){
            delete []v[i].id_inf;
        } else{
            delete []v[i].id_inf;
        }
    }
    delete []v;

    fclose(f);
}