// SPDX-License-Identifier: MIT
// Copyright (c) 2025 Abin

/**
 * @file zip_reader.h
 * @brief 简单的 ZIP 文件解压类
 * @author abin
 * @date 2025-12-05
 */

#ifndef __GUARD_ZIP_READER_H_INCLUDE_GUARD__
#define __GUARD_ZIP_READER_H_INCLUDE_GUARD__

#include <string>
#include <vector>

#include "miniz.h"

namespace zip_compress
{

class ZipReader
{
 public:
  explicit ZipReader(const std::string& zip_path);
  ~ZipReader();

  // 获取 ZIP 内文件相对路径列表
  std::vector<std::string> file_list() const;

  // 解压整个 ZIP 文件到指定目录（会覆盖已有文件）
  void extract_all(const std::string& output_folder);

  // 解压单个文件到指定路径
  void extract_file(const std::string& file_name_in_zip, const std::string& output_path);

 private:
  mz_zip_archive zip_;
  bool opened_;
};

}  // namespace zip_compress

#endif  // __GUARD_ZIP_READER_H_INCLUDE_GUARD__
