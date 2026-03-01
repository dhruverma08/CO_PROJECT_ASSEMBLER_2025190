import sys
final = []
# OPCODES
R_type = {'add': '0110011', 'sub': '0110011', 'sll': '0110011','slt': '0110011', 'sltu': '0110011', 'xor': '0110011','srl': '0110011', 'or': '0110011', 'and': '0110011'}
I_type = {'lw': '0000011', 'addi': '0010011', 'sltiu': '0010011','jalr': '1100111'}
S_type = {'sw': '0100011'}
B_type = {'beq': '1100011','bne': '1100011', 'blt': '1100011', 'bge': '1100011','bltu': '1100011', 'bgeu': '1100011'}
U_type = {'lui': '0110111','auipc': '0010111'}
J_type = {'jal': '1101111'}

# Function-3
R_type_func3 = {'add': '000', 'sub': '000', 'sll': '001','slt': '010', 'sltu': '011', 'xor': '100','srl': '101', 'or': '110', 'and': '111'}
I_type_func3 = {'lw': '010', 'addi': '000', 'sltiu': '011','jalr': '000'}
S_type_func3 = {'sw': '010'}
B_type_func3 = {'beq': '000','bne': '001', 'blt': '100', 'bge': '101','bltu': '110', 'bgeu': '111'}
