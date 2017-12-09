#include <stdio.h>

const char* getOpcodeName(unsigned int OpCode) {
  switch (OpCode) {
    // Terminators
    case 1:
      return "ret";
    case 2:
      return "br";
    case 3:
      return "switch";
    case 4:
      return "indirectbr";
    case 5:
      return "invoke";
    case 6:
      return "resume";
    case 7:
      return "unreachable";
    case 8:
      return "cleanupret";
    case 9:
      return "catchret";
    case 10:
      return "catchpad";
    case 11:
      return "catchswitch";
    // Standard binary operators...
    case 12:
      return "add";
    case 13:
      return "fadd";
    case 14:
      return "sub";
    case 15:
      return "fsub";
    case 16:
      return "mul";
    case 17:
      return "fmul";
    case 18:
      return "udiv";
    case 19:
      return "sdiv";
    case 20:
      return "fdiv";
    case 21:
      return "urem";
    case 22:
      return "srem";
    case 23:
      return "frem";
    // Logical operators...
    case 24:
      return "and";
    case 25:
      return "or";
    case 26:
      return "xor";
    // Memory instructions...
    case 27:
      return "alloca";
    case 28:
      return "load";
    case 29:
      return "store";
    case 30:
      return "cmpxchg";
    case 31:
      return "atomicrmw";
    case 32:
      return "fence";
    case 33:
      return "getelementptr";
    // Convert instructions...
    case 34:
      return "trunc";
    case 35:
      return "zext";
    case 36:
      return "sext";
    case 37:
      return "fptrunc";
    case 38:
      return "fpext";
    case 39:
      return "fptoui";
    case 40:
      return "fptosi";
    case 41:
      return "uitofp";
    case 42:
      return "sitofp";
    case 43:
      return "inttoptr";
    case 44:
      return "ptrtoint";
    case 45:
      return "bitcast";
    case 46:
      return "addrspacecast";
    // Other instructions...
    case 47:
      return "icmp";
    case 48:
      return "fcmp";
    case 49:
      return "phi";
    case 50:
      return "select";
    case 51:
      return "call";
    case 52:
      return "shl";
    case 53:
      return "lshr";
    case 54:
      return "ashr";
    case 55:
      return "va_arg";
    case 56:
      return "extractelement";
    case 57:
      return "insertelement";
    case 58:
      return "shufflevector";
    case 59:
      return "extractvalue";
    case 60:
      return "insertvalue";
    case 61:
      return "landingpad";
    case 62:
      return "cleanuppad";
    default:
      return "<Invalid operator> ";
  }
}

int counts[100] = {0};

void logCounts(int opcode) {
  counts[opcode]++;
  // printf("Incremented opcode: %i\n", counts[opcode]);
}

void printCounts(int opcode) {
  counts[opcode]++;
  int total = 0;
  for (int i = 0; i < 100; ++i) {
    if (counts[i] > 0) {
      total += counts[i];
      // printf("Opcode: %i, Instruction: %s, Count: %i \n", i,
      // getOpcodeName(i),
      //        counts[i]);
      printf("%s %i\n", getOpcodeName(i), counts[i]);
    }
  }
  printf("TOTAL %i\n", total);
}