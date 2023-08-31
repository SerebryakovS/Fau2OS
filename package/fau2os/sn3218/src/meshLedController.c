
#include    <time.h>
#include <ncurses.h>
#include  <string.h>
#include   <stdio.h>
#include  <stdint.h>
#include  <stdlib.h>
#include  "sn3218.h"

#define FACTOR  (RAND_MAX / SN3218_NLEDS)

int main(int argc, char **argv){
    uint8_t Idx;
    if (!sn3218_OpenDev()){
        fprintf(stderr, "Could not open SN3218 over I2C\n");
        return -EXIT_FAILURE;
    };
    if (strcmp(argv[1], "gamma") == 0) {
        for (uint8_t Jdx = 0; Jdx < 3; Jdx++){
            for (Idx = 0; Idx < SN3218_GAMMA; Idx++){
                sn3218_SetAllLeds(sn3218_GammaIntencities[Idx]);
                msleep(50);
            };
            msleep(50);
            for (Idx = SN3218_GAMMA-1; Idx > 0; Idx--){
                sn3218_SetAllLeds(sn3218_GammaIntencities[Idx]);
                msleep(50);
            };
        };
    } else if (strcmp(argv[1], "all") == 0) {
        for (Idx = 0; Idx < 5; Idx++){
            sn3218_SetAllLeds(1);
            msleep(200);
            sn3218_SetAllLeds(0);
            msleep(200);
        };
    } else if (strcmp(argv[1], "loop") == 0) {
        for (Idx = 1; Idx <= SN3218_NLEDS; Idx++){
            sn3218_SetOneLed(Idx, 1);
            msleep(100);
        };
        msleep(100);
        for (Idx = 1; Idx <= SN3218_NLEDS; Idx++){
            sn3218_SetOneLed(Idx, 0);
            msleep(100);
        };
    }else if (strcmp(argv[1], "random") == 0) {
        time_t Timer;
        srand(time(&Timer));
        for (Idx = 0; Idx < 1000; Idx++){
            uint8_t LedNumber = rand() / FACTOR + 1;
            sn3218_SetOneLed(LedNumber, 10);
            msleep(20);
            sn3218_SetOneLed(LedNumber, 0);
            msleep(20);
        };
    }else{
        fprintf(stderr, "Use one of the following modes as first argument: [gamma, all, loop, random]\n");
        return -EXIT_FAILURE;
    };
    sn3218_CloseDev();
    return EXIT_SUCCESS;
};

