R_type_table = {
    "add": {"funct7": "0000000", "funct3": "000", "opcode": "0110011"},
    "sub": {"funct7": "0100000", "funct3": "000", "opcode": "0110011"},
    "sll": {"funct7": "0000000", "funct3": "001", "opcode": "0110011"},
    "slt": {"funct7": "0000000", "funct3": "010", "opcode": "0110011"},
    "sltu": {"funct7": "0000000", "funct3": "011", "opcode": "0110011"},
    "xor": {"funct7": "0000000", "funct3": "100", "opcode": "0110011"},
    "srl": {"funct7": "0000000", "funct3": "101", "opcode": "0110011"},
    "or": {"funct7": "0000000", "funct3": "110", "opcode": "0110011"},
    "and": {"funct7": "0000000", "funct3": "111", "opcode": "0110011"}
}

I_type_table = {
    "addi": {"funct3": "000", "opcode": "0010011"},
    "sltiu": {"funct3": "011", "opcode": "0010011"},
    "lw": {"funct3": "010", "opcode": "0000011"},
    "jalr": {"funct3": "000", "opcode": "1100111"}
}

S_type_table = {"sw": {"funct3": "010", "opcode": "0100011"}}

B_type_table = {
    "beq": {"funct3": "000", "opcode": "1100011"},
    "bne": {"funct3": "001", "opcode": "1100011"},
    "blt": {"funct3": "100", "opcode": "1100011"},
    "bge": {"funct3": "101", "opcode": "1100011"},
    "bltu": {"funct3": "110", "opcode": "1100011"},
    "bgeu": {"funct3": "111", "opcode": "1100011"}
}

U_type_table = {
    "lui": {"opcode": "0110111"},
    "auipc": {"opcode": "0010111"}
}

J_type_table = {"jal": {"opcode": "1101111"}}

registers = {
    "zero": "00000", "ra": "00001", "sp": "00010", "gp": "00011", "tp": "00100",
    "t0": "00101", "t1": "00110", "t2": "00111", "s0": "01000", "fp": "01000",
    "s1": "01001", "a0": "01010", "a1": "01011", "a2": "01100", "a3": "01101",
    "a4": "01110", "a5": "01111", "a6": "10000", "a7": "10001", "s2": "10010",
    "s3": "10011", "s4": "10100", "s5": "10101", "s6": "10110", "s7": "10111",
    "s8": "11000", "s9": "11001", "s10": "11010", "s11": "11011", "t3": "11100",
    "t4": "11101", "t5": "11110", "t6": "11111",
    "x0": "00000", "x1": "00001", "x2": "00010", "x3": "00011", "x4": "00100",
    "x5": "00101", "x6": "00110", "x7": "00111", "x8": "01000",
    "x9": "01001", "x10": "01010", "x11": "01011", "x12": "01100", "x13": "01101",
    "x14": "01110", "x15": "01111", "x16": "10000", "x17": "10001", "x18": "10010",
    "x19": "10011", "x20": "10100", "x21": "10101", "x22": "10110", "x23": "10111",
    "x24": "11000", "x25": "11001", "x26": "11010", "x27": "11011", "x28": "11100",
    "x29": "11101", "x30": "11110", "x31": "11111"
}


def immediate(x, bits):
    if bits <= 0: return "error"
    x = x.strip()
    is_negative = False
    if x.startswith("-"):
        is_negative = True
        x = x[1:]
    if x.startswith("0x"): # Support hex as per prompt 0x00000000
        y = int(x, 16)
    elif not x.isdigit():
        return "error"
    else:
        y = int(x)
    
    binary_int = 0
    place = 1
    if y == 0: binary_int = 0
    else:
        temp_y = y
        while temp_y != 0:
            remainder = temp_y % 2
            binary_int = remainder * place + binary_int
            place = place * 10
            temp_y = temp_y // 2
    binary = str(binary_int)
    if len(binary) > bits: return "error"
    while len(binary) < bits: binary = "0" + binary
    if not is_negative: return binary
    flipped = "".join("1" if b == "0" else "0" for b in binary)
    result = list(flipped)
    carry = 1
    i = bits - 1
    while i >= 0 and carry == 1:
        if result[i] == "0":
            result[i] = "1"
            carry = 0
        else:
            result[i] = "0"
        i -= 1
    return "".join(result)

def encode_R_type(parts):
    instr, rd, rs1, rs2 = parts
    entry = R_type_table[instr]
    return entry["funct7"] + registers[rs2] + registers[rs1] + entry["funct3"] + registers[rd] + entry["opcode"]

def encode_I_type(parts):
    instr = parts[0]
    entry = I_type_table[instr]
    if instr == "lw":
        rd = parts[1]
        offset, rs1 = parts[2].split("(")
        rs1 = rs1.replace(")", "")
    else:
        rd, rs1, offset = parts[1], parts[2], parts[3]
    imm_bin = immediate(offset, 12)
    if imm_bin == "error": raise ValueError("Illegal Immediate")
    return imm_bin + registers[rs1] + entry["funct3"] + registers[rd] + entry["opcode"]

def encode_S_type(parts):
    instr = parts[0]
    rs2 = parts[1]
    offset, rs1 = parts[2].split("(")
    rs1 = rs1.replace(")", "")
    imm_bin = immediate(offset, 12)
    if imm_bin == "error": raise ValueError("Illegal Immediate")
    return imm_bin[:7] + registers[rs2] + registers[rs1] + S_type_table[instr]["funct3"] + imm_bin[7:] + S_type_table[instr]["opcode"]

def encode_B_type(parts):
    instr, rs1, rs2, imm = parts
    if imm in label: offset = label[imm] - pc
    else: offset = int(imm, 0)
    imm_bin = immediate(str(offset), 13)
    if imm_bin == "error": raise ValueError("Illegal Immediate")
    return imm_bin[0] + imm_bin[2:8] + registers[rs2] + registers[rs1] + B_type_table[instr]["funct3"] + imm_bin[8:12] + imm_bin[1] + B_type_table[instr]["opcode"]

def encode_U_type(parts):
    instr, rd, imm = parts
    imm_bin = immediate(imm, 20)
    if imm_bin == "error": raise ValueError("Illegal Immediate")
    return imm_bin + registers[rd] + U_type_table[instr]["opcode"]

def encode_J_type(parts):
    instr, rd, imm = parts
    if imm in label: offset = label[imm] - pc
    else: offset = int(imm, 0)
    imm_bin = immediate(str(offset), 21)
    if imm_bin == "error": raise ValueError("Illegal Immediate")
    return imm_bin[0] + imm_bin[10:20] + imm_bin[9] + imm_bin[1:9] + registers[rd] + J_type_table[instr]["opcode"]

def get_instruction_type(instr):
    instr = instr.lower()
    if instr in R_type_table: return 0
    if instr in I_type_table: return 1
    if instr in S_type_table: return 2
    if instr in B_type_table: return 3
    if instr in U_type_table: return 4
    if instr in J_type_table: return 5
    return -1

def main_encoder(line):
    parts = line.replace(",", " ").split()
    # Typo check for registers
    for p in parts[1:]:
        if "(" in p: 
            r = p.split("(")[1].replace(")", "")
            if r not in registers: raise ValueError(f"Invalid register {r}")
        elif not p.strip("-").isdigit() and not p.startswith("0x") and p not in label:
            if p not in registers: raise ValueError(f"Invalid register {p}")
            
    inst_type = get_instruction_type(parts[0])
    match inst_type:
        case 0: return encode_R_type(parts)
        case 1: return encode_I_type(parts)
        case 2: return encode_S_type(parts)
        case 3: return encode_B_type(parts)
        case 4: return encode_U_type(parts)
        case 5: return encode_J_type(parts)
        case _: raise ValueError(f"Invalid instruction mnemonic: {parts[0]}")


pc = 0
label = {}
all_instrs = []

try:
    with open("input_file.txt", "r") as fin:
        lines = [l.strip() for l in fin.readlines() if l.strip()]

    # First Pass: Labels and Virtual Halt Check
    temp_pc = 0
    for line in lines:
        instr_body = line
        if ":" in line:
            lbl_name = line[:line.index(":")].strip()
            # Constraint: Label must start with a character
            if not lbl_name[0].isalpha():
                raise ValueError(f"Syntax Error: Label '{lbl_name}' must start with a letter")
            label[lbl_name] = temp_pc
            instr_body = line[line.index(":")+1:].strip()
        
        if instr_body:
            all_instrs.append(instr_body)
            temp_pc += 4

    # Constraint: Missing/Last Virtual Halt Check
    if not all_instrs:
        raise ValueError("Syntax Error: File is empty")
    
    last = all_instrs[-1].replace(",", " ").split()
    # Check if last is: beq zero, zero, 0
    is_halt = (last[0] == "beq" and last[1] == "zero" and last[2] == "zero" and 
              (last[3] == "0" or last[3] == "0x00000000" or (last[3] in label and label[last[3]] == (temp_pc-4))))
    
    if not is_halt:
        raise ValueError("Syntax Error: Virtual Halt (beq zero,zero,0) must be the last instruction")

    # Second Pass: Encoding
    with open("output_file.txt", "w") as fout:
        pc = 0
        for instr in all_instrs:
            binary = main_encoder(instr)
            fout.write(binary + "\n")
            pc += 4

except Exception as e:
    print(f"Error at line {pc//4 + 1}: {e}")
