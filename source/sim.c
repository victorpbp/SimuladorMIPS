#include <stdio.h>
#include "shell.h"


//OPERAÇÕES DO TIPO R (REGISTRADORES)//

//SLL (Shift Left Logical)//

void sll(uint32_t rt, uint32_t rd, uint32_t sa) {

    NEXT_STATE.REGS[rd] = (CURRENT_STATE.REGS[rt])<<sa;

}

//SRL (Shift Right Logical)//

void srl(uint32_t rt, uint32_t rd, uint32_t sa) {

    NEXT_STATE.REGS[rd] = (CURRENT_STATE.REGS[rt])>>sa;

}

//SRA (Shift Right Arithmetic)//

void srl(uint32_t rt, uint32_t rd, uint32_t sa) {

    NEXT_STATE.REGS[rd] = (CURRENT_STATE.REGS[rt])>>sa;

    int32_t mask = 0b10000000000000000000000000000000;

    if (sa>0) mask>>(sa-1);
    
    NEXT_STATE.REGS[rd] = NEXT_STATE.REGS[rd] | mask;

}

//ADD//

void add(uint32_t rs, uint32_t rt, uint32_t rd) {

    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];

}


//ADDU//

void addu(uint32_t rs, uint32_t rt, uint32_t rd) {

    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];

}

/////////////////////////////////////////////////////////////////////

//OPERAÇÕES DO TIPO J (JUMPS)//


/////////////////////////////////////////////////////////////////////

//OPERAÇÕES DO TIPO I (IMEDIATOS)//

//ADDIU//

void addiu(uint32_t instruction) { 

    uint32_t rs = (instruction<<6)>>27; //Valor do registrador com o primeiro valor de adição

    uint32_t rt = (instruction<<11)>>27; //Valor do registrador de recebimento

    uint32_t imme = (instruction & 0x0000FFFF); //Valor do imediato

    NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + imme;

    printf("valor do registrador: %d\n",NEXT_STATE.REGS[2]); //Caso de teste pra saber o valor do V0
    printf("valor do registrador: %d\n",NEXT_STATE.REGS[8]); //Caso de teste pra saber o valor do t0
    printf("valor do registrador: %d\n",NEXT_STATE.REGS[9]); //Caso de testa pra saber o valor do t1

}

/////////////////////////////////////////////////////////////////////

//OPERAÇÕES DO TIPO LOAD//


/////////////////////////////////////////////////////////////////////

//OPERAÇÕES DO TIPO STORE//


/////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////

        //REGISTRADORES//

        case (0):; 
       
            uint32_t functcode = instruction & 0b00000000000000000000000000011111; //Grabbing the funct code at the end of the instruction

            uint32_t rsR = (instruction<<6)>>27; //Valor do registrador com o primeiro valor de adição

            uint32_t rtR = (instruction<<11)>>27; //Valor do registrador com o segundo valor de adição

            uint32_t rdR = (instruction<<16)>>27; //Valor do registrador destino da operação

            uint32_t saR = (instruction<<21)>>27; //Shifts

            switch (functcode) { 


                //SLL (Shift Left Logical)//

                case (0):;

                sll(rtR,rdR,saR);
                
                break;


                //SRL (Shift Right Logical)//

                case (0x02):;

                srl(rtR,rdR,saR);

                break;


                //SRA (Shift Right Arithmetic)//

                case (0x03):;

                sra(rtR,rdR,saR);

                break;


                //SLL (Shift Left Logical Variable)//

                case (0x04):;
                
                break;


                //SRLV (Shift Right Logical Variable)//

                case (0x06):;

                break;


                //SRAV (Shift Right Arithmetic Variable)//

                case (0x07):;

                break;


                //JR (Jump Registry)//

                case (0x08):;

                break;


                //JALR (Jump and Link Register)//

                case (0x09):;

                break;


                //MFHI (Move from HI)//

                case (0x10):;

                break;


                //MTHI (Move from HI)//

                case (0x11):;

                break;


                //MFLO (Move from LO)//

                case (0x12):;

                break;


                //MTLO (Move from LO)//

                case (0x13):;

                break;


                //MULT//

                case (0x18):;

                break;


                //MULTU//

                case (0x19):;

                break;


                //ADD//

                case (0x20):; //add //Causes an exception upon overflow (How do I do that?)

                add(rsR,rtR,rdR);

                break;


                //ADDU//

                case (0x21):; //addu //Does NOT cause an exception upon overflow (How do I do that?)

                addu(rsR,rtR,rdR);

                break;


                //SUB//

                case (0x22):;

                break;


                //SUBU//

                case (0x23):;

                break;


                //AND//

                case (0x24):;

                break;


                //OR//

                case (0x25):;

                break;


                //XOR//

                case (0x26):;

                break;


                //NOR//

                case (0x27):;

                break;


                //DIV//

                case (0x1a):;

                break;


                //DIVU//

                case (0x1b):;

                break;


                //SLT (Set Less Than)//

                case (0x2a):;

                break;


                //SLTU (Set Less Than Unsigned)//

                case (0x2b):;

                break;


                //SYSCALL (Syscall)//

                case (0xc):;

                if (CURRENT_STATE.REGS[2]==10) RUN_BIT=0;

                break;


            }

        break;

/////////////////////////////////////////////////////////////////////


        //JUMPs//

        //J//

        case (0x2):;

        break;


        //JAL (Jump and Link)//

        case (0x3):;

        break;


        //BEQ (Branch Equal To)//

        case (0x4):;

        break;


        //BNE (Branch NOT Equal To)//

        case (0x5):;

        break;



/////////////////////////////////////////////////////////////////////


        //IMEDIATOS//


        //SOME ODD BRANCH COMMANDS THAT REQUIRE MORE MANIPULATION (CHECK THE MIPS INSTRUCTIONS BY THEIR NAMES)//

        case (0x1):;

            uint32_t whichOne = (instruction<<11)>>27;

            switch (whichOne) {

                //BLTZ (Branch on Less Than Zero)//

                case (0x0):;

                break;


                //BGEZ (Branch on Greater Than or Equal to Zero)//

                case (0x1):;

                break;


                //BLTZAL (Branch on Less Than Zero and Link)///

                case (0x10):;

                break; 


                //BLTZAL (Branch on Less Than Zero and Link)///

                case (0x11):;

                break; 

            
            }
/////////////////////////////////////////////////////////////////////


        break;



        //BLEZ (Branch on Less Than or Equal to Zero)//

        case (0x6):;

        break;


        //BGTZ (Branch on Greater Than Zero)//

        case (0x7):;

        break;


        //ADDI//

        case (0x8):;

        break;


        //ADDIU//        

        case (0x9):;
        
            addiu(instruction);

        break;


        //SLTI (Set Less Than Immediate)//

        case (0xa):;

        break;


        //SLTIU (Set Less Than Immediate Unsigned)//

        case (0xb):;

        break;


        //ANDI//

        case (0xc):;

        break;


        //ORI//

        case (0xd):;

        break;


        //XORI//

        case (0xe):;

        break;



/////////////////////////////////////////////////////////////////////

        //LOAD (AINDA SÃO IMEDIATOS)//


        //LUI (Load Upper Immediate)//

        case (0xf):;

        break;


        //LB (Load Byte)//

        case (0x20):;

        break;


        //LH (Load Halfword)//

        case (0x21):;

        break;


        //LW (Load Word)//

        case (0x23):;

        break;


        //LBU (Load Byte Unsigned)//

        case (0x24):;

        break;


        //LHU (Load Halfword Unsigned)//

        case (0x25):;

        break;


/////////////////////////////////////////////////////////////////////

        //STORE//


        //SB (Store Byte)//

        case (0x28):;

        break;


        //SH (Store Halfword)//

        case (0x29):;

        break;

        
        //SW (Store Word)//

        case (0x2b):;

        break;


     }


}