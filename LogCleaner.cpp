#include <fstream>

#include "LogCleaner.h"

LogCleaner& LogCleaner::GetInstance() {
  static LogCleaner instance;
  return instance;
}

LogCleaner::LogCleaner()
    : created_files_log_("created_files.txt"), run_is_valid_(false) {}

LogCleaner::~LogCleaner() {
  if (!run_is_valid_) {
    for (const auto& file_path : logs_) {
      std::remove(file_path.c_str());
    }
  } else {
    WriteLogFile();
  }
}

void LogCleaner::WriteLogFile() {
  std::ofstream log;
  log.open(log_dir_path_ + created_files_log_);

  for (const auto& filename : logs_) {
    log << filename << std::endl;
  }

  log.close();
}

void LogCleaner::AddLogFilePath(const std::string& file_path) {
  logs_.emplace_back(file_path);
}

void LogCleaner::ValidateUsage() { run_is_valid_ = true; }

void LogCleaner::ClearLastLogs(const std::string& log_dir_path) {
  log_dir_path_ = log_dir_path;

  std::ifstream last_log;
  last_log.open(log_dir_path_ + created_files_log_);

  std::string file_path;
  while (getline(last_log, file_path)) {
    std::remove(file_path.c_str());
  }

  last_log.close();
}
