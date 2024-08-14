#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <iomanip>

const size_t DOS_HEADER_SIZE = 64;
const size_t PE_HEADER_OFFSET = 0x3C;
const size_t PE_HEADER_SIZE = 248;
const size_t SECTION_HEADER_SIZE = 40;
const size_t SECTION_ALIGNMENT = 0x1000;
const size_t ENTRY_POINT_OFFSET = 0x10;
const size_t PE_MAGIC_NUMBER = 0x00004550;
const size_t CODE_SECTION_SIZE = 0x1000;

const char STUB_CODE[] = {
    0xB8, 0x00, 0x00, 0x00, 0x00,
    0xC3
};

void writePEHeader(std::ofstream& file, size_t codeSize) {
    char peHeader[PE_HEADER_SIZE] = { 0 };

    peHeader[0] = 'M';
    peHeader[1] = 'Z';
    std::memcpy(peHeader + PE_HEADER_OFFSET, &PE_HEADER_SIZE, sizeof(PE_HEADER_SIZE));

    std::memcpy(peHeader + PE_HEADER_OFFSET, &PE_MAGIC_NUMBER, sizeof(PE_MAGIC_NUMBER));

    peHeader[0x4] = 0x4C;
    peHeader[0x6] = 0x01;
    peHeader[0x14] = 0x10;
    peHeader[0x16] = 0x10B;

    peHeader[0x18] = 0x10B;
    peHeader[0x1A] = 0x00;
    peHeader[0x1C] = 0x00;
    peHeader[0x1E] = 0x00;
    peHeader[0x20] = (codeSize + sizeof(STUB_CODE) + SECTION_ALIGNMENT - 1) & ~(SECTION_ALIGNMENT - 1);
    peHeader[0x22] = 0x00;
    peHeader[0x24] = 0x00;
    peHeader[0x28] = 0x00;
    peHeader[0x2C] = 0x00;
    peHeader[0x30] = 0x10000000;
    peHeader[0x34] = 0x00;
    peHeader[0x38] = 0x00;
    peHeader[0x3C] = 0x00;
    peHeader[0x40] = 0x00;
    peHeader[0x44] = 0x00;
    peHeader[0x48] = 0x00;
    peHeader[0x4C] = 0x00;
    peHeader[0x50] = 0x00;
    peHeader[0x54] = 0x00;
    peHeader[0x58] = (codeSize + sizeof(STUB_CODE) + SECTION_ALIGNMENT - 1) & ~(SECTION_ALIGNMENT - 1);
    peHeader[0x5C] = (codeSize + sizeof(STUB_CODE) + SECTION_ALIGNMENT - 1) & ~(SECTION_ALIGNMENT - 1);
    peHeader[0x60] = 0x00;
    peHeader[0x62] = 0x00;
    peHeader[0x64] = 0x00;
    peHeader[0x68] = 0x00;
    peHeader[0x6C] = 0x00;
    peHeader[0x70] = 0x00;
    peHeader[0x74] = 0x00;
    peHeader[0x78] = 0x00;
    peHeader[0x7C] = 0x00;

    file.write(peHeader, PE_HEADER_SIZE);
}

void writeSectionHeaders(std::ofstream& file, size_t codeSize) {
    char sectionHeader[SECTION_HEADER_SIZE] = { 0 };

    std::memcpy(sectionHeader, ".text", 6);
    std::memcpy(sectionHeader + 0x08, &codeSize, sizeof(codeSize));
    std::memcpy(sectionHeader + 0x14, &codeSize, sizeof(codeSize));
    std::memcpy(sectionHeader + 0x18, &codeSize, sizeof(codeSize));
    std::memcpy(sectionHeader + 0x1C, &codeSize, sizeof(codeSize));

    file.write(sectionHeader, SECTION_HEADER_SIZE);
}

void writeBytecode(std::ofstream& file, const std::vector<unsigned char>& bytecode) {
    file.write(reinterpret_cast<const char*>(bytecode.data()), bytecode.size());
}

void writeStub(std::ofstream& file) {
    file.write(STUB_CODE, sizeof(STUB_CODE));
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: minibyte_compiler <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::ifstream file(inputFile);
    if (!file) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    std::string hexCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::vector<unsigned char> bytecode;
    for (size_t i = 0; i < hexCode.length(); i += 3) {
        unsigned int byte;
        int result = std::sscanf(hexCode.substr(i, 2).c_str(), "%2x", &byte);
        if (result != 1) {
            std::cerr << "Error parsing hex code." << std::endl;
            return 1;
        }
        bytecode.push_back(static_cast<unsigned char>(byte));
    }

    std::ofstream outputFileStream(outputFile, std::ios::binary);
    if (!outputFileStream) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    size_t codeSize = bytecode.size();
    writePEHeader(outputFileStream, codeSize);
    writeSectionHeaders(outputFileStream, codeSize);
    writeStub(outputFileStream);
    writeBytecode(outputFileStream, bytecode);

    outputFileStream.close();

    std::cout << "Compilation successful. Executable created: " << outputFile << std::endl;
    return 0;
}
