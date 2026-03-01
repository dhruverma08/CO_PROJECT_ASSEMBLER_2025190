import sys
final = []
    
#R-type funct7 | rs2 | rs1 | funct3 | rd | opcode
R_opcode = "0110011"
    
R_type_table = {
    "add": {
        "funct7": "0000000",
        "funct3": "000",
        "opcode": "0110011"
    },
    "sub": {
        "funct7": "0100000",
        "funct3": "000",
        "opcode": "0110011"
    },
    "sll": {
        "funct7": "0000000",
        "funct3": "001",
        "opcode": "0110011"
    },
    "slt": {
        "funct7": "0000000",
        "funct3": "010",
        "opcode": "0110011"
    },
    "sltu": {
        "funct7": "0000000",
        "funct3": "011",
        "opcode": "0110011"
    },
    "xor": {
        "funct7": "0000000",
        "funct3": "100",
        "opcode": "0110011"
    },
    "srl": {
        "funct7": "0000000",
        "funct3": "101",
        "opcode": "0110011"
    },
    "or": {
        "funct7": "0000000",
        "funct3": "110",
        "opcode": "0110011"
    },
    "and": {
        "funct7": "0000000",
        "funct3": "111",
        "opcode": "0110011"
    }
}

# I type imm[11:0] | rs1 | funct3 | rd | opcode

I_type_table = {
    "addi": {
        "funct3": "000",
        "opcode": "0010011"
    },
    "sltiu": {
        "funct3": "011",
        "opcode": "0010011"
    },
    "lw": {
        "funct3": "010",
        "opcode": "0000011"
    },
    "jalr": {
        "funct3": "000",
        "opcode": "1100111"
    }
}

# s type imm[11:5] | rs2 | rs1 | funct3 | imm[4:0] | opcode
S_type_table = {
    "sw": {
        "funct3": "010",
        "opcode": "0100011"
    }
}
# b type imm[12|10:5] | rs2 | rs1 | funct3 | imm[4:1|11] | opcode
B_type_table = {

    "beq": {
        "funct3": "000",
        "opcode": "1100011"
    },

    "bne": {
        "funct3": "001",
        "opcode": "1100011"
    },

    "blt": {
        "funct3": "100",
        "opcode": "1100011"
    },

    "bge": {
        "funct3": "101",
        "opcode": "1100011"
    },

    "bltu": {
        "funct3": "110",
        "opcode": "1100011"
    },

    "bgeu": {
        "funct3": "111",
        "opcode": "1100011"
    }
}

#u-type imm[31:12] | rd | opcode
U_type_table = {

    "lui": {
        "opcode": "0110111"
    },

    "auipc": {
        "opcode": "0010111"
    }
}
#J_type  imm[20|10:1|11|19:12] | rd | opcode
J_type_table = {

    "jal": {
        "opcode": "1101111"
    }
}
