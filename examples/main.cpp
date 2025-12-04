// 避免 Windows min/max 宏污染
#ifdef _WIN32
#define NOMINMAX
#endif

#include <fstream>
#include <ghc/filesystem.hpp>  // 或 std::filesystem
#include <iostream>
#include <vector>

#include "zip_compress/zip_writer.h"

namespace fs = ghc::filesystem;

// 测试压缩大文件
void test_zip_compression()
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
}

// 测试递归压缩文件夹
void test_compress_folder(const std::string& folder_path, const std::string& zip_path)
{
  // 创建测试文件夹及文件
  fs::create_directory(folder_path);
  for (int i = 0; i < 5; ++i)
  {
    std::ofstream out(fs::path(folder_path) / ("file" + std::to_string(i) + ".dat"), std::ios::binary);
    std::vector<char> buffer(1024 * 1024, i);  // 1MB 数据
    out.write(buffer.data(), buffer.size());
  }

  try
  {
    zip_compress::ZipWriter writer(zip_path);

    // 遍历文件夹，跳过目标 ZIP 文件
    for (auto& entry : fs::recursive_directory_iterator(folder_path))
    {
      if (fs::is_regular_file(entry))
      {
        if (entry.path().string() == zip_path) continue;
        writer.add_file(entry.path().string(), folder_path);
      }
    }

    writer.finish();
    std::cout << "Folder ZIP created successfully: " << zip_path << std::endl;
  }
  catch (const std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}

int main()
{
  test_zip_compression();
  test_compress_folder("test_folder", "folder_test.zip");
  return 0;
}
