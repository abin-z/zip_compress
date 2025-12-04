#include <fstream>
#include <iostream>
#include <vector>

#include "zip_compress/zip_writer.h"

int main()
{
  const std::string big_file = "big_file.dat";
  const size_t file_size = 100 * 1024 * 1024;  // 100MB

  // 生成测试大文件
  std::ofstream out(big_file, std::ios::binary);
  std::vector<char> buffer(1024 * 1024, 0);  // 1MB buffer
  for (size_t written = 0; written < file_size; written += buffer.size())
  {
    size_t to_write = std::min(buffer.size(), file_size - written);
    out.write(buffer.data(), to_write);
  }
  out.close();
  std::cout << "Generated test file: " << big_file << std::endl;

  // 压缩文件
  try
  {
    zip_compress::ZipWriter writer("test.zip");
    writer.add_file(big_file);  // 只压缩单个大文件
    writer.finish();
    std::cout << "ZIP created successfully" << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
