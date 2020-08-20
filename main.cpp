#include <iostream>

#include "LogCleaner.h"
#include "compiler/driver.hh"

void raise_usage_error() {
  const char* usage_msg =
      "Usage: pass flags in first order, then path_to_test, then path_to_log";
  std::cerr << usage_msg << std::endl;
  exit(1);
}

int main(int argc, char** argv) {
  Driver driver;
  LogCleaner& log_cleaner = LogCleaner::GetInstance();

  size_t argc_count = 0;
  for (int i = 1; i < argc; ++i) {
    if (argv[i] == std::string("-p")) {
      driver.trace_parsing_ = true;
      ++argc_count;
    } else if (argv[i] == std::string("-s")) {
      driver.trace_scanning_ = true;
      ++argc_count;
    } else if (!driver.Parse(argv[i])) {
      if (argc - argc_count != 3) {
        raise_usage_error();
      }

      std::string logs_path(argv[i + 1]);
      log_cleaner.ClearLastLogs(logs_path);
      driver.SetLogsPath(logs_path);

      driver.PrintTree(logs_path + "tree_output.out");
      log_cleaner.AddLogFilePath(logs_path + "tree_output.out");
      driver.Exec();
      std::cout << "executed_successfully\n";

      log_cleaner.ValidateUsage();
      return 0;
    } else {
      raise_usage_error();
    }
  }

  raise_usage_error();
}
