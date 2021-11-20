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

void sra(uint32_t rt, uint32_t rd, uint32_t sa) {

    NEXT_STATE.REGS[rd] = ((int32_t) CURRENT_STATE.REGS[rt])>>sa;

    // int32_t mask = 0b10000000000000000000000000000000;

    // if (sa>0) mask>>(sa-1);
    
    // NEXT_STATE.REGS[rd] = NEXT_STATE.REGS[rd] | mask;

}


//SLLV (Shift Left Logical Variable)//

void sllv(uint32_t rs, uint32_t rt, uint32_t rd) {

    NEXT_STATE.REGS[rd] = (CURRENT_STATE.REGS[rt])<<CURRENT_STATE.REGS[rs];

}


//SRLV (Shift Right Logical Variable)//

void srlv(uint32_t rs, uint32_t rt, uint32_t rd) {

    NEXT_STATE.REGS[rd] = (CURRENT_STATE.REGS[rt])>>CURRENT_STATE.REGS[rs];

}


//SRAV (Shift Right Arithmetic Variable)//

void srav(uint32_t rs, uint32_t rt, uint32_t rd) {

    NEXT_STATE.REGS[rd] = ((int32_t) CURRENT_STATE.REGS[rt])>>CURRENT_STATE.REGS[rs];

    // int32_t mask = 0b10000000000000000000000000000000;

    // if (CURRENT_STATE.REGS[rs]>0) mask>>(CURRENT_STATE.REGS[rs]-1);
    
    // NEXT_STATE.REGS[rd] = NEXT_STATE.REGS[rd] | mask;

}


//JR (Jump Register)//

void jr(uint32_t rs) {

    NEXT_STATE.PC = CURRENT_STATE.REGS[rs];

}


//JALR (Jump and Link Register)//

void jalr(uint32_t rs, uint32_t rd) {

    NEXT_STATE.REGS[rd] = CURRENT_STATE.PC + 4;

    NEXT_STATE.PC = CURRENT_STATE.REGS[rs];

}


//MFHI (Move from HI)//

void mfhi(uint32_t rd) {

    NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;

}


//MTHI (Move to HI)//

void mthi(uint32_t rs) {

    NEXT_STATE.HI = CURRENT_STATE.REGS[rs];

}
 

//MFLO (Move from LO)//

void mflo(uint32_t rd) {

    NEXT_STATE.REGS[rd] = CURRENT_STATE.LO;

}


//MTLO (Move to LO)//

void mtlo(uint32_t rs) {

    NEXT_STATE.LO = CURRENT_STATE.REGS[rs];

}


//MULT//

void mult(uint32_t rs , uint32_t rt) {

    uint64_t temporary = (int32_t) CURRENT_STATE.REGS[rs] * (int32_t) CURRENT_STATE.REGS[rt];

    CURRENT_STATE.HI = (temporary>>32);

    CURRENT_STATE.LO = ((temporary<<32)>>32);

}


//MULTU//

void multu(uint32_t rs , uint32_t rt) {

    uint64_t temporary = CURRENT_STATE.REGS[rs] * CURRENT_STATE.REGS[rt];

    CURRENT_STATE.HI = (temporary>>32);

    CURRENT_STATE.LO = ((temporary<<32)>>32);

}

//ADD//

void add(uint32_t rs, uint32_t rt, uint32_t rd) {

    int result = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
    if (((CURRENT_STATE.REGS[rs] >> 31) == CURRENT_STATE.REGS[rt] >> 31) && ((CURRENT_STATE.REGS[rt]  >> 31) != (result >> 31))) {
        printf("\nOverflow!\n");
        RUN_BIT = 0;
    } else {
        NEXT_STATE.REGS[rd] = result; 
    }

}


//ADDU//

void addu(uint32_t rs, uint32_t rt, uint32_t rd) {

    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];

}

//SUB//

void sub(uint32_t rs, uint32_t rt, uint32_t rd) {

    int result = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
    if (((CURRENT_STATE.REGS[rs] >> 31) == !(CURRENT_STATE.REGS[rt] >> 31)) && ((CURRENT_STATE.REGS[rt]  >> 31) != (result >> 31))) {
        printf("\nOverflow!\n");
        RUN_BIT = 0;
    } else {
        NEXT_STATE.REGS[rd] = result; 
    }

}


//SUBU//

void subu(uint32_t rs, uint32_t rt, uint32_t rd) {

    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];

}

//AND//

void and(uint32_t rs, uint32_t rt, uint32_t rd) {

    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];

}


//OR//

void or(uint32_t rs, uint32_t rt, uint32_t rd) {

    NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];

}


//XOR//

void xor(uint32_t rs, uint32_t rt, uint32_t rd) {

    NEXT_STATE.REGS[rd] = (CURRENT_STATE.REGS[rt] ^ CURRENT_STATE.REGS[rs]);

}


//NOR//

void nor(uint32_t rs, uint32_t rt, uint32_t rd) {

    NEXT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rt] | CURRENT_STATE.REGS[rs]);

}


//DIV//

void div(uint32_t rs , uint32_t rt) {

    int32_t first = CURRENT_STATE.REGS[rs];

    int32_t second = CURRENT_STATE.REGS[rt];

    NEXT_STATE.LO = first/second;

    NEXT_STATE.HI = first%second;

    //Do I have to deal with the case of the divisor being 0 or not? If so, how do I assign an Undefined?


}


//DIVU//

void divu(uint32_t rs , uint32_t rt) {

    NEXT_STATE.LO = CURRENT_STATE.REGS[rs]/CURRENT_STATE.REGS[rt];

    NEXT_STATE.HI = CURRENT_STATE.REGS[rs]%CURRENT_STATE.REGS[rt];

    //Do I have to deal with the case of the divisor being 0 or not? If so, how do I assign an Undefined?

}



//SLT//

void slt(uint32_t rs, uint32_t rt, uint32_t rd) {

    int32_t first = CURRENT_STATE.REGS[rs];
    
    int32_t second = CURRENT_STATE.REGS[rt];


    if ( first < second ) CURRENT_STATE.REGS[rd]=1;
    else CURRENT_STATE.REGS[rd]=0;

}


//SLTU//

void sltu(uint32_t rs, uint32_t rt, uint32_t rd) {

    if ( CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt] ) CURRENT_STATE.REGS[rd]=1;
    else CURRENT_STATE.REGS[rd]=0;

}

void jump(uint32_t instruction) {
    int jumpAdrr = (instruction & 0b00000011111111111111111111111111) << 2; 
    NEXT_STATE.PC &= (0b11110000000000000000000000000000); 
    NEXT_STATE.PC |= jumpAdrr;          
}

/////////////////////////////////////////////////////////////////////

//OPERAÇÕES DO TIPO J (JUMPS)//

/////////////////////////

////////////////////////////////////////////
//OPERAÇÕES DO TIPO I (IMEDIATOS)//

//ADDIU//

void addiu(uint32_t instruction, uint32_t rs, uint32_t rt, uint32_t immediate) { 

    // uint32_t rs = (instruction<<6)>>27; //Valor do registrador com o primeiro valor de adição

    // uint32_t rt = (instruction<<11)>>27; //Valor do registrador de recebimento

    // uint32_t immediate = (instruction & 0x0000FFFF); //Valor do imediato

    NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + (((int32_t) immediate << 16) >> 16);


}

/////////////////////////////////////////////////////////////////////

//OPERAÇÕES DO TIPO LOAD//


/////////////////////////////////////////////////////////////////////

//OPERAÇÕES DO TIPO STORE//


/////////////////////////////////////////////////////////////////////

void process_instruction()
{
    /* execute one instruction here. You should use CURRENT_STATE and modify
     * values in NEXT_STATE. You can call mem_read_32() and mem_write_32() to
     * access memory. */

     uint32_t instruction = mem_read_32(CURRENT_STATE.PC);

     uint32_t opcode = instruction>>26;
     printf("opcode: %d\n", opcode);

     NEXT_STATE.PC = CURRENT_STATE.PC + 4; // To colocando isso aqui pra gente omitir nos outros campos
     //Aí quando a gente tiver tratando de Jumps e tal, é só levar isso em consideração
     //Se for jump relativo, a gente sempre tem que contar com o +4, então tudo normal
     //Se for jump absoluto, tudo bem também porque a gente só tá transferindo o valor e esse primeiro comando vai ser "inútil" mas ele vai facilitar muito o entendimento e evita DEMAIS repetição no código

    uint32_t rs = (instruction<<6)>>27; //Valor do registrador com o primeiro valor da operação dos tipos R e I

    uint32_t rt = (instruction<<11)>>27; //Valor do registrador com o segundo valor da operação dos tipos R e I

    uint32_t immediate = (instruction & 0x0000FFFF); ////Valor do imediato da operação do tipo I

     switch(opcode) {

/////////////////////////////////////////////////////////////////////

        //REGISTRADORES//

        case (0):; 
 
       
            uint32_t functcode = instruction & 0b00000000000000000000000000111111; //Grabbing the funct code at the end of the instruction

            uint32_t rdR = (instruction<<16)>>27; //Valor do registrador destino da operação

            uint32_t saR = (instruction<<21)>>27; //Shifts

            printf("functcode: %d", functcode);

            switch (functcode) { 

                //SLL (Shift Left Logical)//

                case (0):

                sll(rt,rdR,saR);
                
                break;


                //SRL (Shift Right Logical)//

                case (0x02):

                srl(rt,rdR,saR);

                break;


                //SRA (Shift Right Arithmetic)//

                case (0x03):

                sra(rt,rdR,saR);

                break;


                //SLLV (Shift Left Logical Variable)//

                case (0x04):

                sllv(rs,rt,rdR);
                
                break;


                //SRLV (Shift Right Logical Variable)//

                case (0x06):

                srlv(rs,rt,rdR);

                break;


                //SRAV (Shift Right Arithmetic Variable)//

                case (0x07):

                srav(rs,rt,rdR);

                break;


                //JR (Jump Register)//

                case (0x08):

                jr(rs);

                break;


                //JALR (Jump and Link Register)// Do I have to take care of the case if RD is ommited and I have to assume it goes to the $ra?

                case (0x09):

                jalr(rs,rdR);

                break;


                //MFHI (Move from HI)//

                case (0x10):

                mfhi(rdR);

                break;


                //MTHI (Move to HI)//

                case (0x11):

                mthi(rs);

                break;


                //MFLO (Move from LO)//

                case (0x12):

                mflo(rdR);

                break;


                //MTLO (Move to LO)//

                case (0x13):

                mtlo(rs);

                break;


                //MULT//

                case (0x18):

                mult(rs, rt);

                break;


                //MULTU//

                case (0x19):

                multu(rs, rt);

                break;


                //ADD//

                case (0x20): //add //Causes an exception upon overflow 

                add(rs,rt,rdR);

                break;


                //ADDU//

                case (0x21): //addu //Does NOT cause an exception upon overflow 

                addu(rs,rt,rdR);

                break;


                //SUB//

                case (0x22):

                sub(rs,rt,rdR);

                break;


                //SUBU//

                case (0x23):

                subu(rs,rt,rdR);

                break;


                //AND//

                case (0x24):

                and(rs,rt,rdR);

                break;


                //OR//

                case (0x25):

                or(rs,rt,rdR);

                break;


                //XOR//

                case (0x26):

                xor(rs,rt,rdR);

                break;


                //NOR//

                case (0x27):

                nor(rs,rt,rdR);

                break;


                //DIV// Should I worry if the divisor is 0? If so, how do I return undefined?

                case (0x1a):

                div(rs,rt);

                break;


                //DIVU//

                case (0x1b):

                divu(rs,rt);

                break;


                //SLT (Set Less Than)//

                case (0x2a):

                slt(rs,rt,rdR);

                break;


                //SLTU (Set Less Than Unsigned)//

                case (0x2b):

                sltu(rs,rt,rdR);

                break;


                //SYSCALL (Syscall)//

                case (0xc):

                if (CURRENT_STATE.REGS[2]==10) RUN_BIT=0;


                break;


            }

        break;

/////////////////////////////////////////////////////////////////////


        //JUMPs//

        //J//

        case (0x2):

          jump(instruction);

        break;


        //JAL (Jump and Link)//

        case (0x3):

          NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
          jump(instruction);
         

        break;



/////////////////////////////////////////////////////////////////////


        //IMEDIATOS//

        //BEQ (Branch Equal To)//

        case (0x4):
          if (CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]) NEXT_STATE.PC += (((int32_t) immediate << 16) >> 16) * 4;
        break;


        //BNE (Branch NOT Equal To)//

        case (0x5):
         if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]) NEXT_STATE.PC += (((int32_t) immediate << 16) >> 16) * 4;
        break;


        //SOME ODD BRANCH COMMANDS THAT REQUIRE MORE MANIPULATION (CHECK THE MIPS INSTRUCTIONS BY THEIR NAMES)//

        case (0x1):;

            switch (rt) {

                //BLTZ (Branch on Less Than Zero)//

                case (0x0):
                   if ((int32_t) CURRENT_STATE.REGS[rs] < 0) NEXT_STATE.PC += (((int32_t) immediate << 16) >> 16) * 4;
                break;


                //BGEZ (Branch on Greater Than or Equal to Zero)//

                case (0x1):
                   if ((int32_t) CURRENT_STATE.REGS[rs] >= 0) NEXT_STATE.PC += (((int32_t) immediate << 16) >> 16) * 4;
                break;


                //BLTZAL (Branch on Less Than Zero and Link)///

                case (0x10):
                   NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
                   if ((int32_t) CURRENT_STATE.REGS[rs] < 0) NEXT_STATE.PC += (((int32_t) immediate << 16) >> 16) * 4;
                break; 


                //BGEZAL (Branch On Greater Than Or Equal To Zero And Link)///

                case (0x11):
                   NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
                   if ((int32_t) CURRENT_STATE.REGS[rs] >= 0) NEXT_STATE.PC += (((int32_t) immediate << 16) >> 16) * 4;
                break; 

            
            }
/////////////////////////////////////////////////////////////////////


        break;



        //BLEZ (Branch on Less Than or Equal to Zero)//

        case (0x6):
            if ((int32_t) CURRENT_STATE.REGS[rs] <= 0) NEXT_STATE.PC += (((int32_t) immediate << 16) >> 16) * 4;
        break;


        //BGTZ (Branch on Greater Than Zero)//

        case (0x7):
            if ((int32_t) CURRENT_STATE.REGS[rs] > 0) NEXT_STATE.PC += (((int32_t) immediate << 16) >> 16) * 4;
        break;


        //ADDI//

        case (0x8):
            addiu(instruction, rs, rt, immediate);
            if (NEXT_STATE.REGS[rt] < CURRENT_STATE.REGS[rt]) {
                printf("Overflow! ");
                RUN_BIT = 0;
            }
        break;


        //ADDIU (Add Immediate)//        

        case (0x9):
            addiu(instruction, rs, rt, immediate);
        break;


        //SLTI (Set Less Than Immediate)//

        case (0xa):
            if (CURRENT_STATE.REGS[(int32_t)rs] < (int32_t)immediate) NEXT_STATE.REGS[rt] = 1; 
            else NEXT_STATE.REGS[rt] = 0;  
        break;


        //SLTIU (Set Less Than Immediate Unsigned)//

        case (0xb):
            if (CURRENT_STATE.REGS[rs] < immediate) NEXT_STATE.REGS[rt] = 1; 
            else NEXT_STATE.REGS[rt] = 0; 
        break;


        //ANDI (And Immediate)//

        case (0xc):
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] & immediate;  
        break;


        //ORI//

        case (0xd):
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] | immediate;  
        break;


        //XORI//

        case (0xe):
            NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] ^ immediate; 
        break;



/////////////////////////////////////////////////////////////////////

        //LOAD (AINDA SÃO IMEDIATOS)//


        //LUI (Load Upper Immediate)//

        case (0xf):
           NEXT_STATE.REGS[rt] = (immediate << 16);
        break;


        //LB (Load Byte)//

        case (0x20):
           NEXT_STATE.REGS[rt] = ((int32_t)( mem_read_32(CURRENT_STATE.REGS[rs] + (((int32_t) immediate << 16) >> 16)) & (0x000000FF)) << 24) >> 24;
        break;


        //LH (Load Halfword)//

        case (0x21):
           NEXT_STATE.REGS[rt] = ((int32_t)(mem_read_32(CURRENT_STATE.REGS[rs] + (((int32_t) immediate << 16) >> 16)) & (0x0000FFFF)) << 16) >> 16;
        break;


        //LW (Load Word)//

        case (0x23):
           NEXT_STATE.REGS[rt] = mem_read_32(CURRENT_STATE.REGS[rs] + (((int32_t) immediate << 16) >> 16));
        break;


        //LBU (Load Byte Unsigned)//

        case (0x24):
           NEXT_STATE.REGS[rt] = mem_read_32(CURRENT_STATE.REGS[rs] + (((int32_t) immediate << 16) >> 16)) & (0x000000FF); 
        break;


        //LHU (Load Halfword Unsigned)//

        case (0x25):
            NEXT_STATE.REGS[rt] = mem_read_32(CURRENT_STATE.REGS[rs] + (((int32_t) immediate << 16) >> 16)) & (0x0000FFFF);
        break;


/////////////////////////////////////////////////////////////////////

        //STORE//

        //SB (Store Byte)//

        case (0x28):
           mem_write_32(CURRENT_STATE.REGS[rs] + immediate, (mem_read_32(CURRENT_STATE.REGS[rs] + immediate) & 0xFFFFFF00) | (CURRENT_STATE.REGS[rt] & 0x000000FF));
        break;


        //SH (Store Halfword)//

        case (0x29):
           mem_write_32(CURRENT_STATE.REGS[rs] + immediate, (mem_read_32(CURRENT_STATE.REGS[rs] + immediate) & 0xFFFF0000) | (CURRENT_STATE.REGS[rt] & 0x0000FFFF));
        break;

        
        //SW (Store Word)//

        case (0x2b):
           mem_write_32(CURRENT_STATE.REGS[rs] + immediate, CURRENT_STATE.REGS[rt]);
        break;


     }
     printf("\n"); //linebreak to keep things aligned, even if functcode is absent
     for (int x = 0; x < 32; x++) {
       printf("%02d: 0x%08x\n", x, NEXT_STATE.REGS[x]); //print register values
     }
     printf("PC: 0x%08x\n\n", NEXT_STATE.PC); //print PC value


}