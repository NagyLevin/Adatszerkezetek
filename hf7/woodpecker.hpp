/** @file woodpecker.hpp Woodpecker CPP testing API */
#ifndef WOODPECKER_HPP
#define WOODPECKER_HPP
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <span>
#include <sstream>
#include <string_view>
#include <utility>
#include <vector>
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace woodpecker {

inline void usage(const char *name) {
  std::cerr << "Usage:" << std::endl;
  std::cerr << "\t" << name
            << " [-v] [-t test_no] [-f logfile] [-c] [--no-timeout] [-- other "
               "arguments]"
            << std::endl;
  std::cerr
      << "-v           Verbose output: print tests and results to stdout\n"
      << "               Default setting when no logfile is specified\n"
      << "-t test_no   Run only specific testcase\n"
      << "-f logfile   Write test results to file\n"
      << "-c           Configuration mode: print only test numbers and names\n"
      << "--no-timeout Don't check timeouts.\n";
}

struct woodpecker_controller;
struct test_controller;
using TEST_FUNC = std::function<void(test_controller &)>;

struct test_params_t {
  int points = 1;
  long long mem_limit = -1, stack_limit = -1;
};

struct test_case {
  std::string test_name;
  test_params_t test_params;
  woodpecker::TEST_FUNC func;
  void run_test(woodpecker_controller & /*woodpecker_cntr*/);
};

struct scoped_log {
  static inline std::stringstream log_buffer; /* NOLINT */
  std::vector<std::string> &logs;
  template <typename LOGGABLE>
  scoped_log(std::vector<std::string> &logs, const std::string &msg,
             const LOGGABLE &val)
      : logs(logs) {
    log_buffer << val;
    logs.push_back(msg + log_buffer.str());
    log_buffer.str("");
    log_buffer.clear();
  }
  scoped_log(std::vector<std::string> &logs) : logs(logs) {
    logs.push_back(log_buffer.str());
    log_buffer.str("");
    log_buffer.clear();
  }
  ~scoped_log() { logs.pop_back(); }
  scoped_log(const scoped_log &) = delete;
  scoped_log(scoped_log &&) = delete;
  scoped_log &operator=(const scoped_log &) = delete;
  scoped_log &operator=(scoped_log &&) = delete;
};

struct woodpecker_controller {
private:
  static inline std::vector<test_case>
      testcases; /**< descriptors for all testcase */
public:
  int test_no =
      0; /**< id of the test that will be running, 0 to run all tests */
  int counter = 0;            /**< test counter used in macros */
  int total = 0;              /**< total points achieved */
  int maximum = 0;            /**< maximum achievable points */
  std::ofstream test_log;     /**< logfile to write test results */
  bool verbose = false;       /**< print logs to stderr */
  bool config_mode = false;   /**< output test configs instead of running them*/
  bool check_timeouts = true; /**< check timeouts */
  test_params_t default_params{0, -1, -1};
  explicit woodpecker_controller(const std::span<const char *> &argv) noexcept {
    size_t arg_idx = 1;
    while (arg_idx < argv.size()) {
      if (!strcmp(argv[arg_idx], "-v")) {
        verbose = true;
      } else if (!strcmp(argv[arg_idx], "-t")) {
        test_no = std::stoi(argv[++arg_idx]);
      } else if (!strcmp(argv[arg_idx], "-f")) {
        test_log.open(argv[++arg_idx]);
      } else if (!strcmp(argv[arg_idx], "-c")) {
        config_mode = true;
      } else if (!strcmp(argv[arg_idx], "--no-timeout")) {
        check_timeouts = false;
      } else if (!strcmp(argv[arg_idx], "--")) {
        break;
      } else {
        usage(argv[0]);
        exit(2);
      }
      arg_idx++;
    }
    if (!test_log.is_open() && !verbose) {
      verbose = true;
    }
  }

  void run_tests() {
    for (auto &testcase : testcases) {
      testcase.run_test(*this);
    }
  }

  ~woodpecker_controller() {
    if (!config_mode) {
      *this << ">>> TOTAL POINTS: " << total << "\n";
    }
    if (test_log.is_open()) {
      test_log.close();
    }
  }

  woodpecker_controller(const woodpecker_controller &) = delete;
  woodpecker_controller(woodpecker_controller &&) = delete;
  woodpecker_controller &operator=(const woodpecker_controller &) = delete;
  woodpecker_controller &operator=(woodpecker_controller &&) = delete;

  template <typename T> woodpecker_controller &operator<<(const T &printable) {
    if (test_log.is_open())
      test_log << printable;
    if (verbose)
      std::cerr << printable;
    return *this;
  }

  struct AutoReg {
    AutoReg(const std::string &name, const woodpecker::TEST_FUNC &func,
            const test_params_t &params) {
      woodpecker_controller::testcases.push_back({name, params, func});
    }
  };
};

struct test_controller {
  bool enabled, error_free = true;
  std::string label;
  test_params_t test_params;
  bool ok;
  int &out;
  woodpecker_controller &woodpecker_cntr;
  std::vector<std::string> logs{};

  void print_logs() const {
    for (const auto &log : logs) {
      woodpecker_cntr << ">>> " << log << "\n";
    }
  }

  test_controller(bool enabled, std::string &&label,
                  const test_params_t &test_params, int &out,
                  woodpecker_controller &woodpecker_cntr)
      : enabled(enabled), label(std::move(label)), test_params(test_params),
        ok(true), out(out), woodpecker_cntr(woodpecker_cntr) {
    if (woodpecker_cntr.config_mode) {
      this->enabled = false;
      // Output points, memory limit, etc.
      long long mem_limit = this->test_params.mem_limit;
      if (mem_limit < 0) {
        mem_limit = woodpecker_cntr.default_params.mem_limit;
      }
      long long stack_limit = this->test_params.stack_limit;
      if (stack_limit < 0) {
        stack_limit = woodpecker_cntr.default_params.stack_limit;
      }
      woodpecker_cntr << this->test_params.points << ";" << mem_limit << ";"
                      << stack_limit << ";" << this->label << "\n";
    }
    if (this->enabled) {
      woodpecker_cntr.maximum += this->test_params.points;
      woodpecker_cntr << ">>> Test: " << this->label << " ("
                      << test_params.points << ")\n";
    }
  }

  void report_failure(const std::string_view expr,
                      const std::filesystem::path file_path, int line_num,
                      std::string_view operator_str, auto lhs, auto rhs) {
    woodpecker_cntr << ">>> " << expr << " failed at "
                    << file_path.filename().string() << ":" << line_num
                    << ". With expansion: " << lhs << operator_str << rhs
                    << ".\n";
  }

  void report_failure(const std::string_view expr,
                      const std::filesystem::path file_path, int line_num,
                      std::string_view operator_str, auto lhs, auto rhs,
                      auto tolerance) {
    woodpecker_cntr << ">>> " << expr << " failed at "
                    << file_path.filename().string() << ":" << line_num
                    << ". With expansion: " << lhs << operator_str << rhs
                    << " (with tolerance " << tolerance << ").\n";
  }

  test_controller &operator<<(const std::string &msg) {
    if (msg.find("ERROR") != std::string::npos) {
      error_free = false;
      ok = false;
    }
    woodpecker_cntr << msg;
    return *this;
  }

  ~test_controller() {
    if (enabled && error_free) {
      out += ok ? test_params.points : 0;
      woodpecker_cntr << ">>> Result: " << (ok ? "PASS" : "FAIL") << "\n";
    }
  }
  test_controller(const test_controller &) = delete;
  test_controller(test_controller &&) = delete;
  test_controller &operator=(const test_controller &) = delete;
  test_controller &operator=(test_controller &&) = delete;
};

struct timer_controller {
  std::chrono::nanoseconds &out;
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
  bool run;
  explicit timer_controller(std::chrono::nanoseconds &out)
      : out(out), start(std::chrono::high_resolution_clock::now()), run(true) {}
  ~timer_controller() {
    auto stop = std::chrono::high_resolution_clock::now();
    out = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
  }
  timer_controller(const timer_controller &) = delete;
  timer_controller(timer_controller &&) = delete;
  timer_controller &operator=(const timer_controller &) = delete;
  timer_controller &operator=(timer_controller &&) = delete;
};

struct measurement_controller {
  std::string name;
  std::chrono::nanoseconds timeout;
  std::chrono::nanoseconds duration{};
  std::unique_ptr<timer_controller> timer;
  bool run;
  woodpecker_controller &woodpecker_cntr;
  test_controller &test_cntr;
  measurement_controller(std::string &&name, std::chrono::nanoseconds timeout,
                         woodpecker_controller &woodpecker_cntr,
                         test_controller &test_cntr)
      : name(std::move(name)), timeout(timeout),
        timer(std::make_unique<timer_controller>(duration)), run(true),
        woodpecker_cntr(woodpecker_cntr), test_cntr(test_cntr) {}
  ~measurement_controller() {
    if (!woodpecker_cntr.check_timeouts) {
      return;
    }
    timer.reset();
    if (duration > timeout) {
      test_cntr.print_logs();
      woodpecker_cntr << ">>> TIMEOUT: " << name << " " << duration.count()
                      << "ns vs " << timeout.count() << "ns\n";
      test_cntr.ok = false;
    }
  }
  measurement_controller(const measurement_controller &) = delete;
  measurement_controller(measurement_controller &&) = delete;
  measurement_controller &operator=(const measurement_controller &) = delete;
  measurement_controller &operator=(measurement_controller &&) = delete;
};

inline void test_case::run_test(woodpecker_controller &woodpecker_cntr) {
  test_controller cntr(++woodpecker_cntr.counter == woodpecker_cntr.test_no ||
                           woodpecker_cntr.test_no == 0,
                       std::move(test_name), test_params, woodpecker_cntr.total,
                       woodpecker_cntr);
  try {
    if (cntr.enabled) {
      func(cntr);
    }
  } catch (std::bad_alloc &) {
    cntr << ">>> Result: RUNTIME ERROR: MEMORY LIMIT EXCEEDED\n";
  } catch (const std::exception &e) {
    cntr << ">>> Result: RUNTIME ERROR: " << e.what() << "\n";
  } catch (...) {
    cntr << ">>> Result: RUNTIME ERROR\n";
  }
}

} // end namespace woodpecker

#define GLUE_HELPER(x, y) x##y
#define GLUE(x, y) GLUE_HELPER(x, y)
#define WOODPECKER_UNIQUE_NAME(name) GLUE(name, __LINE__)

#define OVERLOADIFY(_1, _2, _3, _4, NAME, ...) NAME

#define INTERNAL_WOODPECKER_TEST_CASE(test_func, label, test_params)           \
  static void test_func(woodpecker::test_controller &);                        \
  namespace woodpecker {                                                       \
  const woodpecker_controller::AutoReg                                         \
      WOODPECKER_UNIQUE_NAME(auto_registrar)(label, test_func, test_params);   \
  }                                                                            \
  static void test_func(woodpecker::test_controller &cntr)

#define TEST1(label)                                                           \
  INTERNAL_WOODPECKER_TEST_CASE(WOODPECKER_UNIQUE_NAME(woodpecker_test),       \
                                label, test_params_t{})
#define TEST2(label, t_param1)                                                 \
  INTERNAL_WOODPECKER_TEST_CASE(WOODPECKER_UNIQUE_NAME(woodpecker_test),       \
                                label, (test_params_t{t_param1}))
#define TEST3(label, t_param1, t_param2)                                       \
  INTERNAL_WOODPECKER_TEST_CASE(WOODPECKER_UNIQUE_NAME(woodpecker_test),       \
                                label, (test_params_t{t_param1, t_param2}))
#define TEST4(label, points, mem_limit, stack_limit)                           \
  INTERNAL_WOODPECKER_TEST_CASE(                                               \
      WOODPECKER_UNIQUE_NAME(woodpecker_test), label,                          \
      (test_params_t{points, mem_limit, stack_limit}))

#define WOODPECKER_INIT                                                        \
  woodpecker::woodpecker_controller woodpecker_cntr(                           \
      {argv, static_cast<std::span<const char *>::size_type>(argc)})

#define WOODPECKER_RUN_TESTS woodpecker_cntr.run_tests()

#define INTERNAL_WOODPECKER_MAIN(is_test, mem_limit_, stack_limit_)            \
  int main(int argc, const char *argv[]) {                                     \
    WOODPECKER_INIT;                                                           \
    woodpecker_cntr.default_params.mem_limit = mem_limit_;                     \
    woodpecker_cntr.default_params.stack_limit = stack_limit_;                 \
    WOODPECKER_RUN_TESTS;                                                      \
    if constexpr (is_test) {                                                   \
      return woodpecker_cntr.maximum == woodpecker_cntr.total ? 0 : 1;         \
    }                                                                          \
    return 0;                                                                  \
  }
#define WOODPECKER_MAIN0(is_test) INTERNAL_WOODPECKER_MAIN(false, -1, -1)
#define WOODPECKER_MAIN1(is_test, param1)                                      \
  static_assert(false, "WOODPECKER_MAIN macros have 0 or 2 parameters, but"    \
                       "used with 1");
#define WOODPECKER_MAIN2(is_test, mem_limit, stack_limit)                      \
  INTERNAL_WOODPECKER_MAIN(is_test, mem_limit, stack_limit)

#endif /* DOXYGEN_SHOULD_SKIP_THIS*/

/** @defgroup tests Test case declaration macros
 *  Woodpecker handles each test case as a separate function.
 *  @{
 */

/**
 * @brief Test creation macro. Each test in woodpecker is a function created by
 * this macro. Every test uses a test controller to record the results of the
 * check macros. A test fails if any checking macro fails in the function.
 *
 * The points, mem_limit, stack_limit parameters can be used with the designated
 * initializers syntax (constrains on order of paramters apply).
 * e.g. TEST("Dummy", .mem_limit=100*1024*1024, .stack_limit=1024)
 *
 * @param label The name of the test. The name should describe what the test
 * expects from the user implementation.
 * @param points An estimate of the number of points this test contributes to
 * the maximum. Optional argument, if not present the default value is 1.
 * @param mem_limit Maximum heap memory in bytes. Optional argument to limit the
 * heap memory for the test via the python runner.
 * @param stack_limit Maximum stack size in bytes. Optional argument to limit
 * stack size for the test via the python runner.
 */
#define TEST(...)                                                              \
  /* suppress warning in CLion */                                              \
  /* NOLINTNEXTLINE(cert-err58-cpp): AutoReg shouldn't throw */                \
  OVERLOADIFY(__VA_ARGS__, TEST4, TEST3, TEST2, TEST1, DUMMY)(__VA_ARGS__)

/** @} */ // end of tests
/** @defgroup application_macros Application macros
 * Woodpecker supply the main function as a macro. These macros define the main
 * function, create woodpecker related controllers, parse the command line and
 * run the tests or list all test case.
 * @{
 */

/**
 * @brief This macro generates a main running tests with woodpecker. This macro
 * should be used with the python runner script.
 *
 * @param mem_limit_ maximum allocated heap memory in bytes. This value is used
 * to communicate the python runner script the memory limitations for the
 * application. Optional argument if not present set to -1, which means there is
 * no limit.
 * @param stack_limit_ maximum stack size in bytes. This value is used to
 * communicate the python runner script the memory limitations for the
 * application. Optional argument if not present set to -1, which means there is
 * no limit.
 *
 * @return  always 0
 */
#define WOODPECKER_MAIN(...)                                                   \
  OVERLOADIFY(0, 1, __VA_ARGS__ __VA_OPT__(, ) WOODPECKER_MAIN2,               \
              WOODPECKER_MAIN1, WOODPECKER_MAIN0, DUMMY)                       \
  (false __VA_OPT__(, ) __VA_ARGS__)

/**
 * @brief This macro generates a main running tests with woodpecker. This macro
 * should not be used with the runner script since test failures would be
 * treated as runtime errors.
 *
 * @param mem_limit_ maximum allocated heap memory in bytes. This value is used
 * to communicate the python runner script the memory limitations for the
 * application. Optional argument if not present set to -1, which means there is
 * no limit.
 * @param stack_limit_ maximum stack size in bytes. This value is used to
 * communicate the python runner script the memory limitations for the
 * application. Optional argument if not present set to -1, which means there is
 * no limit.
 *
 * @return  0 all tests passed, 1 otherwise
 */
#define WOODPECKER_TEST_MAIN(...)                                              \
  OVERLOADIFY(0, 1, __VA_ARGS__ __VA_OPT__(, ) WOODPECKER_MAIN2,               \
              WOODPECKER_MAIN1, WOODPECKER_MAIN0, DUMMY)                       \
  (true __VA_OPT__(, ) __VA_ARGS__)

/** @} */ // end of application_macros
/** @defgroup assertions Assertion macros
 *  Woodpecker handles assertions through macros, trying to handle all major
 * cases.
 *  @{
 */

/**
 * @brief Equality checking, passes if lhs == rhs is true. Only evaluates lhs
 * == rhs if no checks failed in the test so far.
 *
 * @param lhs Left hand side of the comparison. Can be any expression.
 * @param rhs Right hand side of the comparison. Can be any expression.
 */
#define CHECK_EQ(lhs, rhs)                                                     \
  do {                                                                         \
    if (cntr.ok) {                                                             \
      auto lhs_v = (lhs);                                                      \
      auto rhs_v = (rhs);                                                      \
      cntr.ok = lhs_v == rhs_v;                                                \
      if (!cntr.ok) {                                                          \
        cntr.print_logs();                                                     \
        cntr.report_failure(#lhs " == " #rhs, __FILE__, __LINE__,              \
                            " == ", lhs_v, rhs_v);                             \
      }                                                                        \
    }                                                                          \
  } while (false)

/**
 * @brief Equality checking with tolerance for floating point computations.
 * Similar to CHECK_EQ but enables error arising from floating point
 * computations. Check fails if val - expr > abs_tolerance  + relative_tolerance
 * * val. Only evaluates the check if no checks failed in the test so far.
 *
 * @param val Expected result
 * @param expr Expression to produce val.
 * @param relative_tolerance Relative tolerance to hide small errors from
 * floating point operations.
 */
#define CHECK_CLOSE_TO(val, expr, relative_tolerance)                          \
  do {                                                                         \
    if (cntr.ok) {                                                             \
      auto value = (val);                                                      \
      auto actual = (expr);                                                    \
      const double error = std::abs(value - actual);                           \
      constexpr double ABSOLUTE_TOLERANCE =                                    \
          std::numeric_limits<decltype(actual)>::epsilon() * 100;              \
      /* Similarly to Numpy's `allclose` */                                    \
      cntr.ok =                                                                \
          error <= ABSOLUTE_TOLERANCE + (relative_tolerance)*std::abs(value);  \
      if (!cntr.ok) {                                                          \
        cntr.print_logs();                                                     \
        cntr.report_failure(#val " == " #expr, __FILE__, __LINE__,             \
                            " == ", value, actual, (relative_tolerance));      \
      }                                                                        \
    }                                                                          \
  } while (false)

/**
 * @brief Comparison assertion, passes if lhs < rhs is true. Only evaluates lhs
 * < rhs if no checks failed in the test so far.
 *
 * @param lhs Left hand side of the comparison. Can be any expression.
 * @param rhs Right hand side of the comparison. Can be any expression.
 */
#define CHECK_LT(lhs, rhs)                                                     \
  do {                                                                         \
    if (cntr.ok) {                                                             \
      auto lhs_v = (lhs);                                                      \
      auto rhs_v = (rhs);                                                      \
      cntr.ok = lhs_v < rhs_v;                                                 \
      if (!cntr.ok) {                                                          \
        cntr.print_logs();                                                     \
        cntr.report_failure(#lhs " < " #rhs, __FILE__, __LINE__, " < ", lhs_v, \
                            rhs_v);                                            \
      }                                                                        \
    }                                                                          \
  } while (false)

/**
 * @brief Comparison assertion, passes if lhs <= rhs is true. Only evaluates lhs
 * <= rhs if no checks failed in the test so far.
 *
 * @param lhs Left hand side of the comparison. Can be any expression.
 * @param rhs Right hand side of the comparison. Can be any expression.
 */
#define CHECK_LE(lhs, rhs)                                                     \
  do {                                                                         \
    if (cntr.ok) {                                                             \
      auto lhs_v = (lhs);                                                      \
      auto rhs_v = (rhs);                                                      \
      cntr.ok = lhs_v <= rhs_v;                                                \
      if (!cntr.ok) {                                                          \
        cntr.print_logs();                                                     \
        cntr.report_failure(#lhs " <= " #rhs, __FILE__, __LINE__,              \
                            " <= ", lhs_v, rhs_v);                             \
      }                                                                        \
    }                                                                          \
  } while (false)

/**
 * @brief Comparison assertion, passes if lhs > rhs is true. Only evaluates lhs
 * > rhs if no checks failed in the test so far.
 *
 * @param lhs Left hand side of the comparison. Can be any expression.
 * @param rhs Right hand side of the comparison. Can be any expression.
 */
#define CHECK_GT(lhs, rhs)                                                     \
  do {                                                                         \
    if (cntr.ok) {                                                             \
      auto lhs_v = (lhs);                                                      \
      auto rhs_v = (rhs);                                                      \
      cntr.ok = lhs_v > rhs_v;                                                 \
      if (!cntr.ok) {                                                          \
        cntr.print_logs();                                                     \
        cntr.report_failure(#lhs " > " #rhs, __FILE__, __LINE__, " > ", lhs_v, \
                            rhs_v);                                            \
      }                                                                        \
    }                                                                          \
  } while (false)

/**
 * @brief Comparison assertion, passes if lhs >= rhs is true. Only evaluates lhs
 * <= rhs if no checks failed in the test so far.
 *
 * @param lhs Left hand side of the comparison. Can be any expression.
 * @param rhs Right hand side of the comparison. Can be any expression.
 */
#define CHECK_GE(lhs, rhs)                                                     \
  do {                                                                         \
    if (cntr.ok) {                                                             \
      auto lhs_v = (lhs);                                                      \
      auto rhs_v = (rhs);                                                      \
      cntr.ok = lhs_v >= rhs_v;                                                \
      if (!cntr.ok) {                                                          \
        cntr.print_logs();                                                     \
        cntr.report_failure(#lhs " >= " #rhs, __FILE__, __LINE__,              \
                            " >= ", lhs_v, rhs_v);                             \
      }                                                                        \
    }                                                                          \
  } while (false)

/**
 * @brief Check if `code` throws an exception of type `exc` fails otherwise.
 * Only evaluates the check if no checks failed in the test so far.
 *
 * @param exc type of the exception that `code` should throw.
 */
#define CHECK_EXC(exc, code)                                                   \
  do {                                                                         \
    if (cntr.ok) {                                                             \
      try {                                                                    \
        (void)(code);                                                          \
        cntr.ok = false;                                                       \
        cntr.woodpecker_cntr << ">>> expected exception\n";                    \
      } catch (exc &) { /* NOLINT(bugprone-macro-parentheses) */               \
      }                                                                        \
      if (!cntr.ok) {                                                          \
        cntr.print_logs();                                                     \
        cntr.woodpecker_cntr << #code << " failed at" << __LINE__ << "\n";     \
      }                                                                        \
    }                                                                          \
  } while (false)

/**
 * @brief Checks if `code` does not throw any exception.
 * Only evaluates the check if no checks failed in the test so far.
 */
#define CHECK_NOEXC(code)                                                      \
  do {                                                                         \
    if (cntr.ok) {                                                             \
      try {                                                                    \
        (void)(code);                                                          \
        cntr.ok = true;                                                        \
      } catch (std::exception & e) {                                           \
        cntr.print_logs();                                                     \
        cntr.woodpecker_cntr << ">>> " << #code                                \
                             << " throws unexpected exception at " << __LINE__ \
                             << " unexpected exception: " << e.what() << "\n"; \
        cntr.ok = false;                                                       \
      }                                                                        \
      if (!cntr.ok) {                                                          \
        cntr.woodpecker_cntr << #code << " failed at" << __LINE__ << "\n";     \
      }                                                                        \
    }                                                                          \
  } while (false)

/**
 * @brief Named timing macro. Checks if the code in the following block takes at
 * most `timeout` time, fails otherwise. Uses std::chrono::literals, and spills
 * it to the rest of the test.
 *
 * @param label A name for the measurement.
 * @param timeout Time limit for the code in the block. Should be convertible to
 * std::chrono::nanoseconds.
 */
#define MEASURE(label, timeout)                                                \
  using namespace std::chrono_literals;                                        \
  if (woodpecker::measurement_controller mcntr(                                \
          label,                                                               \
          std::chrono::duration_cast<std::chrono::nanoseconds>(timeout),       \
          cntr.woodpecker_cntr, cntr);                                         \
      mcntr.run)

/** @} */ // end of assertions
/** @defgroup logging Logging macros
 *  Additional log information can be saved to print if an assertion fails.
 *  @{
 */
/**
 * @brief Save the value of a variable to print as additional info. The message
 * is scoped and will be printed for each assertion fail in the current scope
 * after the CAPTURE macro.
 *
 * @param var A variable which value is saved.
 */
#define CAPTURE(var)                                                           \
  woodpecker::scoped_log WOODPECKER_UNIQUE_NAME(log)(cntr.logs,                \
                                                     #var " := ", (var))
/**
 * @brief Log additional infos for woodpecker testcases. The message is scoped
 * and will be printed for each assertion fail in the current scope after the
 * INFO macro.
 *
 * @param var A variable which value is saved.
 */
#define INFO(msg)                                                              \
  woodpecker::scoped_log::log_buffer << (msg); /* NOLINT */                    \
  woodpecker::scoped_log WOODPECKER_UNIQUE_NAME(log)(cntr.logs)
/** @} */ // end of assertions

/** @defgroup utility_macros Utility macros
 *  Woodpecker helper macros to be used with the assertion macros, but not
 * enforce any behaviour themselves.
 *  @{
 */
/**
 * @brief Time measure macro. Defines a new variable with name `varname` and
 * type std::chrono::nanoseconds. Set the value of `varname` to the measured
 * time of the next block.
 *
 * @param varname An unique identifier that will be used to declare a variable
 * with type std::chrono::nanoseconds by this macro.
 */
#define TIMER(varname)                                                         \
  std::chrono::nanoseconds varname;                                            \
  if (woodpecker::timer_controller tcntr(varname); tcntr.run)

/** @} */ // end of utility_macros
#endif    /* ifndef WOODPECKER_HPP */
