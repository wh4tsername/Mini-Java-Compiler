#pragma once

#include <vector>
#include <string>

class LogCleaner {
 public:
  void AddLogFilePath(const std::string& file_path);
  void ClearLastLogs(const std::string& log_dir_path);
  void ValidateUsage();

  static LogCleaner& GetInstance();

  LogCleaner(const LogCleaner&) = delete;
  LogCleaner(LogCleaner&&) = delete;
  LogCleaner& operator=(const LogCleaner&) = delete;
  LogCleaner&& operator=(LogCleaner&&) = delete;

 private:
  LogCleaner();
  ~LogCleaner();

  void WriteLogFile();

 private:
  std::vector<std::string> logs_;
  std::string log_dir_path_;
  std::string created_files_log_;
  bool run_is_valid_;
};
