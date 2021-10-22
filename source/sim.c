#include <stdio.h>
#include "shell.h"

void process_instruction()
{
    printf("Aqui na funcao process_instruction\n");
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */

     uint32_t instruction = mem_read_32(CURRENT_STATE.PC);

     uint32_t opcode = instruction>>26;

     switch(opcode) {

        //Registradores//

        case (0):
       
            uint32_t functcode = instruction & 0b00000000000000000000000000011111;

            switch (functcode) { 

                case (0x20): //add


                break;

            }

        break;


        //Imediatos//

        case (0x9): //addiu
        
            

        break;


     }



}
