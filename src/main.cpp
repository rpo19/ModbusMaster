#include <stdio.h>
#include "ModbusMaster.h"
#include <unistd.h>

ModbusMaster node;

void serialWrite(uint8_t b){
    fwrite(&b, 1, 1, stdout);
}

uint8_t serialRead(){
    uint8_t res;
    fread(&res, 1, 1, stdin);
    printf("0x%02x\n", res);
    return res;
}

int main(){

    static uint32_t i;
    uint8_t j, result;
    uint16_t data[6];

    uint8_t in[256];
    uint8_t out[256];

    node.begin(5, in, out);

    result = node.readHoldingRegisters(3019, 2);

    node.serialWrite(serialWrite);
    node.serialRead(serialRead);


    //printf("%d\n", node.u8ModbusADUoutSize);

    while(1){

        fflush(stdin);
        node.commit();
        fflush(stdout);
        sleep(1);
        result = node.handleResponse(node.ku8MBReadHoldingRegisters);
        if (result == node.ku8MBSuccess)
        {
            printf("yee\n");
        } else {
            printf("bad\n");
        }
        sleep(1);
    }


    

    

}