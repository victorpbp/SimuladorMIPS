#include <stdio.h>
#include "shell.h"

void add(uint32_t instruction) {

    uint32_t rs = (instruction<<6)>>27; //Valor do registrador com o primeiro valor de adição

    uint32_t rt = (instruction<<11)>>27; //Valor do registrador com o segundo valor de adição

    uint32_t rd = (instruction<<16)>>27; //Valor do registrador destino da operação

    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];

}

void process_instruction()
{
    printf("Aqui na funcao process_instruction\n");
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */

     uint32_t instruction = mem_read_32(CURRENT_STATE.PC);

     uint32_t opcode = instruction>>26;

     NEXT_STATE.PC = CURRENT_STATE.PC + 4; // To colocando isso aqui pra gente omitir nos outros campos
     //Aí quando a gente tiver tratando de Jumps e tal, é só levar isso em consideração
     //Se for jump relativo, a gente sempre tem que contar com o +4, então tudo normal
     //Se for jump absoluto, tudo bem também porque a gente só tá transferindo o valor e esse primeiro comando vai ser "inútil" mas ele vai facilitar muito o entendimento e evita DEMAIS repetição no código

     switch(opcode) {

        //Registradores//

        case (0):;
       
            uint32_t functcode = instruction & 0b00000000000000000000000000011111;

            switch (functcode) { 

                //ADD//

                case (0x20):; //add //Causes an exception upon overflow (How do I do that?)

                add(instruction);


                break;

                //ADDU//

                case (0x21):; //addu //Does NOT cause an exception upon overflow (How do I do that?)

                uint32_t rs = (instruction<<6)>>27; //Valor do registrador com o primeiro valor de adição

                uint32_t rt = (instruction<<11)>>27; //Valor do registrador com o segundo valor de adição

                uint32_t rd = (instruction<<16)>>27; //Valor do registrador destino da operação

                NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];


                break;

            }

        break;


        //Imediatos//
        

        case (0x9):; //addiu
        
            uint32_t rs = (instruction<<6)>>27; //Valor do registrador com o primeiro valor de adição

            uint32_t rt = (instruction<<11)>>27; //Valor do registrador de recebimento

            uint32_t imme = (instruction & 0x0000FFFF); //Valor do imediato

            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + imme;

            //printf("valor do registrador: %d\n",NEXT_STATE.REGS[2]); //Caso de teste pra saber o valor do V0
            //printf("valor do registrador: %d\n",NEXT_STATE.REGS[8]); //Caso de teste pra saber o valor do t0
            //printf("valor do registrador: %d\n",NEXT_STATE.REGS[9]); //Caso de testa pra saber o valor do t1

        break;


     }


}