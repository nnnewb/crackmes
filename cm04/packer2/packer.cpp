#include <LIEF/LIEF.hpp>
#include <Windows.h>
#include <vector>
#include <string>

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

  auto program_content = read_file(program_path);
  auto packed_section = LIEF::PE::Section(".packed");
  packed_section.content(program_content);
  loader_binary->add_section(packed_section, LIEF::PE::PE_SECTION_TYPES::DATA);

  auto builder = LIEF::PE::Builder::Builder(loader_binary.get());
  builder.build();
  builder.write("packed.exe");

  return 0;
}
