#include <LIEF/LIEF.hpp>
#include <Windows.h>
#include <compressapi.h>
#include <vector>

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

std::vector<uint8_t> compress(const std::vector<uint8_t> &raw) {
  std::vector<uint8_t> compressed_buffer;
  COMPRESSOR_HANDLE compressor = 0;
  auto success = CreateCompressor(COMPRESS_ALGORITHM_XPRESS_HUFF, nullptr, &compressor);
  if (!success) {
    MessageBoxA(0, "create compressor fail", "compress fail", MB_OK);
    ExitProcess(255);
  }

  DWORD compressed_size = 0;
  success = Compress(compressor, raw.data(), raw.size(), nullptr, 0, &compressed_size);
  if (!success) {
    DWORD error_code = GetLastError();

    if (error_code != ERROR_INSUFFICIENT_BUFFER) {
      MessageBoxA(0, "unexpected compress error", "compress fail", MB_OK);
      ExitProcess(255);
    }

    compressed_buffer.resize(compressed_size, 0);
  }

  success = Compress(compressor, raw.data(), raw.size(), compressed_buffer.data(), compressed_buffer.size(),
                     &compressed_size);
  if (!success) {
    MessageBoxA(0, "unexpected compress error", "compress fail", MB_OK);
    ExitProcess(255);
  }
  compressed_buffer.resize(compressed_size, 0);

  // save before/after compress size for decompression
  compressed_buffer.insert(compressed_buffer.begin(), {
                                                          (uint8_t)((raw.size() >> 24) & 0xff),
                                                          (uint8_t)((raw.size() >> 16) & 0xff),
                                                          (uint8_t)((raw.size() >> 8) & 0xff),
                                                          (uint8_t)(raw.size() & 0xff),
                                                          (uint8_t)((compressed_size >> 24) & 0xff),
                                                          (uint8_t)((compressed_size >> 16) & 0xff),
                                                          (uint8_t)((compressed_size >> 8) & 0xff),
                                                          (uint8_t)(compressed_size & 0xff),
                                                      });
  return compressed_buffer;
}

int main(int argc, const char *argv[]) {
  if (argc < 3) {
    printf("loader and program path are required");
    return -1;
  }
  auto loader_path = argv[1];
  auto program_path = argv[2];
  auto loader_binary = LIEF::PE::Parser::parse(loader_path);

  auto raw_content = read_file(program_path);
  auto compressed = compress(raw_content);

  auto packed_section = LIEF::PE::Section(".packed");
  packed_section.content(compressed);
  loader_binary->add_section(packed_section, LIEF::PE::PE_SECTION_TYPES::DATA);

  auto builder = LIEF::PE::Builder::Builder(loader_binary.get());
  builder.build();
  builder.write("compress-packed.exe");

  return 0;
}
