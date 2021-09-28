#include <LIEF/LIEF.hpp>
#include <fstream>
#include <iostream>
#include <memory>

size_t align(size_t n, size_t alignment) {
  if (n % alignment == 0) {
    return n;
  }
  return n - (n % alignment) + alignment;
}

void padding(std::vector<uint8_t> &data, size_t alignment) {
  auto pad = align(data.size(), alignment);
  if (pad != 0) {
    data.resize(data.size() + pad, 0);
  }
}

std::vector<uint8_t> read_file(const std::string &path) {
  auto h = CreateFile(path.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
  DWORD readbyte = 0;
  auto filesize = GetFileSize(h, nullptr);
  auto content = std::vector<uint8_t>();
  content.resize(filesize, 0);
  if (!ReadFile(h, content.data(), filesize, &readbyte, nullptr)) {
    abort();
  }
  if (readbyte != filesize) {
    abort();
  }

  CloseHandle(h);
  return content;
}

int main(int argc, const char *argv[]) {
  if (argc < 3) {
    printf("loader and program path are required");
    return -1;
  }
  auto loader_path = argv[1];
  auto program_path = argv[2];
  auto loader_binary = LIEF::PE::Parser::parse(loader_path);

  auto file_alignment = loader_binary->optional_header().file_alignment();
  auto section_alignment = loader_binary->optional_header().section_alignment();

  auto program_content = read_file(program_path);
  padding(program_content, file_alignment);
  auto packed_section = LIEF::PE::Section(".packed");
  packed_section.content(program_content);
  packed_section.characteristics(static_cast<uint32_t>(
      LIEF::PE::SECTION_CHARACTERISTICS::IMAGE_SCN_MEM_READ | LIEF::PE::SECTION_CHARACTERISTICS::IMAGE_SCN_MEM_WRITE |
      LIEF::PE::SECTION_CHARACTERISTICS::IMAGE_SCN_CNT_INITIALIZED_DATA));
  loader_binary->add_section(packed_section);

  auto builder = LIEF::PE::Builder::Builder(loader_binary.get());
  builder.build();
  builder.write("packed.exe");

  return 0;
}
