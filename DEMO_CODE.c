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

registers = {
    "zero": "00000", "ra": "00001", "sp": "00010", "gp": "00011", "tp": "00100",
    "t0": "00101", "t1": "00110", "t2": "00111", "s0": "01000", "fp": "01000",
    "s1": "01001", "a0": "01010", "a1": "01011", "a2": "01100", "a3": "01101",
    "a4": "01110", "a5": "01111", "a6": "10000", "a7": "10001", "s2": "10010",
    "s3": "10011", "s4": "10100", "s5": "10101", "s6": "10110", "s7": "10111",
    "s8": "11000", "s9": "11001", "s10": "11010", "s11": "11011", "t3": "11100",
    "t4": "11101", "t5": "11110", "t6": "11111"
}

def encode_R_type(parts):
    instr, rd, rs1, rs2 = parts
    entry = R_type_table[instr]

    funct7 = entry["funct7"]
    funct3 = entry["funct3"]
    opcode = entry["opcode"]

    return funct7 + registers[rs2] + registers[rs1] + funct3 + registers[rd] + opcode

def encode_I_type(parts):
    instr = parts[0]
    entry = I_type_table[instr]

    funct3 = entry["funct3"]
    opcode = entry["opcode"]

    if instr == "lw":
        rd = parts[1]
        offset, rs1 = parts[2].split("(")
        rs1 = rs1.replace(")", "")
    else:
        rd, rs1, imm = parts[1], parts[2], parts[3]
        offset = imm

    imm_bin = imm_to_bin(offset, 12)

    return imm_bin + registers[rs1] + funct3 + registers[rd] + opcode

def encode_S_type(parts):
    instr = parts[0]
    entry = S_type_table[instr]

    funct3 = entry["funct3"]
    opcode = entry["opcode"]

    rs2 = parts[1]
    offset, rs1 = parts[2].split("(")
    rs1 = rs1.replace(")", "")

    imm_bin = imm_to_bin(offset, 12)

    imm_11_5 = imm_bin[:7]
    imm_4_0 = imm_bin[7:]

    return imm_11_5 + registers[rs2] + registers[rs1] + funct3 + imm_4_0 + opcode

def encode_B_type(parts):
    instr, rs1, rs2, imm = parts
    entry = B_type_table[instr]

    funct3 = entry["funct3"]
    opcode = entry["opcode"]

    imm_bin = imm_to_bin(imm, 13)

    return imm_bin[0] + imm_bin[2:8] + registers[rs2] + registers[rs1] + funct3 + imm_bin[8:12] + imm_bin[1] + opcode 

def encode_U_type(parts):
    instr, rd, imm = parts
    entry = U_type_table[instr]

    opcode = entry["opcode"]

    imm_bin = imm_to_bin(imm, 20)

    return imm_bin + registers[rd] + opcode

def encode_J_type(parts):
    instr, rd, imm = parts
    entry = J_type_table[instr]

    opcode = entry["opcode"]

    imm_bin = imm_to_bin(imm, 21)

    return imm_bin[0] + imm_bin[10:20] + imm_bin[9] + imm_bin[1:9] + registers[rd] + opcode 

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
            return encode_R_type(parts)
        case 1:
            return encode_I_type(parts)
        case 2:
            return encode_S_type(parts)
        case 3:
            return encode_B_type(parts)
        case 4:
            return encode_U_type(parts)
        case 5:
            return encode_J_type(parts)
        case _:
            raise ValueError("Invalid instruction")
