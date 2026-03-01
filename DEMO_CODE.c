import sys
final = []
    
#R-type funct7 | rs2 | rs1 | funct3 | rd | opcode
    
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


# I-type imm[11:0] | rs1 | funct3 | rd | opcode

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


# S-type imm[11:5] | rs2 | rs1 | funct3 | imm[4:0] | opcode

S_type_table = {
    "sw": {
        "funct3": "010",
        "opcode": "0100011"
    }
}


# B-type imm[12|10:5] | rs2 | rs1 | funct3 | imm[4:1|11] | opcode

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


# U-type imm[31:12] | rd | opcode

U_type_table = {
    "lui": {
        "opcode": "0110111"
    },
    "auipc": {
        "opcode": "0010111"
    }
}


# J-type  imm[20|10:1|11|19:12] | rd | opcode

J_type_table = {
    "jal": {
        "opcode": "1101111"
    }
}

# Register name → register number
REGISTER_TABLE = {
    "zero": 0,
    "ra": 1,
    "sp": 2,
    "gp": 3,
    "tp": 4,
    "t0": 5, "t1": 6, "t2": 7,
    "s0": 8, "fp": 8, "s1": 9,
    "a0": 10, "a1": 11, "a2": 12, "a3": 13,
    "a4": 14, "a5": 15, "a6": 16, "a7": 17,
    "s2": 18, "s3": 19, "s4": 20, "s5": 21,
    "s6": 22, "s7": 23, "s8": 24, "s9": 25,
    "s10": 26, "s11": 27,
    "t3": 28, "t4": 29, "t5": 30, "t6": 31
}


def get_instruction_type(instr):
    
    instr = instr.lower()

    if instr in R_type_table:
        return 0      # R-type

    elif instr in I_type_table:
        return 1      # I-type

    elif instr in S_type_table:
        return 2      # S-type

    elif instr in B_type_table:
        return 3      # B-type

    elif instr in U_type_table:
        return 4      # U-type

    elif instr in J_type_table:
        return 5      # J-type

    else:
        return -1     # invalid instruction

    
def main_encoder(line):

    parts = line.replace(",", " ").split()
    instr = parts[0]
    inst_type = get_instruction_type(instr)
    match inst_type:
        case 0:
            print("R-type encoder called")
        case 1:
            print("I-type encoder called")
        case 2:
            print("S-type encoder called")
        case 3:
            print("B-type encoder called")          
        case 4:
            print("U-type encoder called")
        case 5:
            print("J-type encoder called")
        case _:
            print("Invalid instruction")
