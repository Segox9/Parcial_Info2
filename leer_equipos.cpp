#include "leer_equipos.h"
#include "binary_operations_lib.h"
void showIDs(Registro *r, int n)
{
    printf("\nIDs:\n");
    for(int i=0; i<n; i++){
        printf("\nID del equipo actual: %d", r[i].IDs.ID);
        printf("\nID del equipo anterior: %d", r[i].IDs.ID_sup);
        
    } 

}
int countDevices(FILE *f){
    uint64_t h;
    uint64_t tp;
    uint64_t cant_eqp_inf;
    int cant=0;
    while(fread(&h, sizeof(uint64_t), 1, f) != 0){
        tp= exxtract_segment_64bits(h, 24, 25);
        if(tp == 0 || tp==3 ){
            cant_eqp_inf= exxtract_segment_64bits(h, 32, 47);
        }
        if (tp == 1 || tp== 2){
            cant_eqp_inf=1;
        }
        fseek(f, cant_eqp_inf*(sizeof(uint16_t)), SEEK_CUR);
        cant++;
    }
    return cant;
}
Registro getRegister(uint16_t Id, Registro *r, int n){

    for(int i=0; i<n; i++){
        if(r[i].IDs.ID == Id){
            return r[i];
        }
    }
    
}

