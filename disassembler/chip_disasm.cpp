#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "../constants.h"
#include "../memory.h"
using namespace std;

// Handles hexadecimal output formatting
#define HEX(width) std::setw(width) << std::setfill('0') << uppercase << std::hex

// Handles outputting various common values
#define OPCODE (((instruction) >> 12) & 0xF)

#define ADDRESS "0x" << HEX(3) << (instruction & 0xFFF)
#define VX "V" << HEX(1) << ((instruction >> 8) & 0xF)
#define VY "V" << HEX(1) << ((instruction >> 4) & 0xF)
#define N (instruction & 0xF)
#define NN "0x" << HEX(2) << (instruction & 0xFF)
#define INSTR HEX(4) << instruction

// Function: print_usage
//
// Prints the usage message for this application.
void print_usage() {
	cout << "chip_disasm - A disassembler for the CHIP-8 virtual machine." << endl;
	cout << endl;
	cout << "Usage: chip_disasm CHIPROM OUTFILE" << endl;
	cout << "\tCHIPROM - The path to the CHIP-8 ROM file to be disassembled." << endl;
	cout << "\tOUTFILE - The file where the disassembled rom will be output." << endl;
}

// Function: get_disassembled
// 
// Parameters:
//    instruction - The instruction to be disassembled
//
// Returns a string containing the disassembled form of this instruction
std::string get_disassembled(const unsigned short& instruction) {
	ostringstream disasm;
	
	switch (OPCODE) {
		case 0x0:
		{
			switch (instruction & 0xFF) {
				case 0xE0:
					disasm << "clear screen";
					break;
				case 0xEE:
					disasm << "return from subroutine";
					break;
				case 0x00:
					disasm << "exit";
					break;
				default:
					disasm << "unknown instruction " << INSTR;
					break;
			}
		}
		break;
		case 0x1:
		{
			disasm << "jump to " << ADDRESS; 
		}
		break;
		case 0x2:
		{
			disasm << "call subroutine at " << ADDRESS;
		}
		break;
		case 0x3:
		{
			disasm << "skip next if " << VX << " == " << NN;
		}
		break;
		case 0x4:
		{
			disasm << "skip next if " << VX << " != " << NN;
		}
		break;
		case 0x5:
		{
			disasm << "skip next if " << VX << " == " << VY;
		}
		break;
		case 0x6:
		{
			disasm << VX << " = " << NN;
		}
		break;
		case 0x7:
		{
			disasm << VX << " = " << VX << " + " << NN;
		}
		break;
		case 0x8:
		{
			switch (instruction & 0xF) {
				case 0x0:
				{
					disasm << VX << " = " << VY;
				}
				break;
				case 0x1:
				{
					disasm << VX << " = " << VX << " | " << VY;
				}
				break;
				case 0x2:
				{
					disasm << VX << " = " << VX << " & " << VY;
				}
				break;
				case 0x3:
				{
					disasm << VX << " = " << VX << " ^ " << VY;
				}
				break;
				case 0x4:
				{
					disasm << VX << " = " << VX << " + " << VY;
				}
				break;
				case 0x5:
				{
					disasm << VX << " = " << VX << " - " << VY;
				}
				break;
				case 0x6:
				{
					disasm << VX << " = " << VX << " >> 1";
				}
				break;
				case 0x7:
				{
					disasm << VX << " = " << VY << " - " << VX;
				}
				break;
				case 0xE:
				{
					disasm << VX << " = " << VX <<  " << 1";
				}
				break;
				default:
				{
					disasm << "unknown instruction " << INSTR;
				}
				break;
			}
		}
		break;
		case 0x9:
		{
			disasm << "skip next if " << VX << " != " << VY;
		}
		break;
		case 0xA:
		{
			disasm << "I = " << ADDRESS;
		}
		break;
		case 0xB:
		{
			disasm << "jump to " << ADDRESS << " + V0";
		}
		break;
		case 0xC:
		{
			disasm << VX << " = rand() & " << NN;
		}
		break;
		default:
		{
			disasm << "unknown instruction " << INSTR;
		}
		break;
	}
	
	return disasm.str();
}

int main (int argc, char const *argv[]) {
	// If we have less than two parameters
	if (argc < 3) {
		// Print the usage message and abort
		print_usage();
		return EXIT_FAILURE;
	}
	
	// Otherwise load the given ROM file into memory
	unsigned char memory[CHIP_OCHO_MEMORY_SIZE];
	ifstream rom(argv[1]);
	
	// If the ROM file could not be opened
	if(!rom.good() || rom.eof() || !rom.is_open()) {
		// indicate that a failure occurred
		cout << "Error, could not load CHIP-8 ROM '" << argv[1] << "'" << endl;
		return EXIT_FAILURE;
	}
	
	// Determine the size of the file
	rom.seekg(0, ios_base::beg);
	ifstream::pos_type begin = rom.tellg();
	rom.seekg(0, ios_base::end);
	unsigned int rom_size = static_cast<unsigned int>(rom.tellg() - begin);
	
	// Use this to compute the number of bytes to be read
	streamsize amount_to_read = min(MAX_CHIP_PROGRAM_SIZE, rom_size);
	
	// Go to beginning of file and read the ROM data into the memory at CHIP_LOAD_OFFSET
	rom.seekg(0, ios_base::beg);
	rom.read((char*)memory, amount_to_read);
	rom.close();
	
	// Output the result of running the ROM to the file
	ofstream out(argv[2]);
	unsigned short opcode;
	
	for (streamsize pc = 0; pc < amount_to_read; pc += 2) {
		opcode = *((unsigned short*)&memory[pc]);
		opcode = (opcode >> 8) | (opcode << 8);
		out << setw(3) << setfill('0') << hex << uppercase << pc << ": ";
		out << "[" << HEX(4) << opcode << "] ";
		out << get_disassembled(opcode) << endl;
	}
	
	return EXIT_SUCCESS;
}