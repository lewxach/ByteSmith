### MiniByte Language Documentation

### Introduction

MiniByte is a low-level programming language designed to provide a bridge between raw binary and assembly language. It allows for more readable and manageable bytecode while still offering the precision of assembly-level programming.

### File Format

MiniByte programs are stored in text files with the .mb extension. Each byte of the program is represented by two hexadecimal digits. Bytes are separated by spaces or newlines.

### Example

Here’s a sample MiniByte file (example.mb):

B8 00 00 00 00 C3

This file represents a simple program that sets the EAX register to 0 and then returns.

### ByteCode Instructions

MiniByte uses the same bytecode instructions as x86 assembly language. Below are a few common instructions:

B8: MOV EAX, imm32 – Moves a 32-bit immediate value into the EAX register.
C3: RET – Returns from the procedure.
90: NOP – No operation (used for padding or delays).
For a full list of instructions, refer to x86 assembly language documentation.

### Compiling MiniByte Programs

To compile MiniByte bytecode into a Windows executable, you need to use the ByteSmith compiler.

Installation

Download ByteSmith: Obtain the ByteSmith executable from the official source or repository.
Ensure Dependencies: Make sure you have any required libraries or dependencies installed.

### Compiling a MiniByte Program

To compile a .mb file into an executable, use the following command:

ByteSmith <input_file.mb> <output_file.exe>

<input_file.mb>: Path to your MiniByte source file.
<output_file.exe>: Path where the compiled executable will be saved.

### Example

Assuming you have a MiniByte file named program.mb:

B8 00 00 00 00 C3

Compile it using:

ByteSmith program.mb program.exe

This will generate an executable named program.exe.

Writing MiniByte Programs

When writing MiniByte programs, follow these guidelines:

Hexadecimal Format: Use two-digit hexadecimal representations for each byte. For example, B8 for the MOV instruction and 00 for the value.
Instruction Sequences: Ensure that instructions are sequenced correctly according to the x86 assembly language.

### Example Program

Here's a MiniByte program that sets the EAX register to 1 and then returns:

B8 01 00 00 00 C3

This program:

Sets the EAX register to 1.
Returns from the procedure.
Commenting

MiniByte does not support comments in the code itself. You should document your code externally or use separate files to describe what each byte or sequence of bytes does.

Error Handling

During compilation, ByteSmith might encounter the following errors:

Invalid Input File: The input file does not exist or cannot be opened.
Parsing Errors: The bytecode is not in the correct format or contains invalid bytes.
File Writing Errors: There are issues writing the output file.

### Building ByteSmith from Source

If you need to build ByteSmith from source:

Setup: Ensure you have a C++ compiler installed (e.g., MSVC, GCC).
Compile: Use the your desired command, Example:

g++ -o ByteSmith ByteSmith.cpp

Run: After building, you can use ByteSmith as described in the compiling section.

License

ByteSmith is licensed under the MIT License. See the LICENSE file for more details.

Thank you for using MiniByte and ByteSmith!
