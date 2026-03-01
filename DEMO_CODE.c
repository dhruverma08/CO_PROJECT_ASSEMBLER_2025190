import sys
final = []
#R-type  funct7 | rs2 | rs1 | funct3 | rd | opcode
R_opcode="0110011"
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
