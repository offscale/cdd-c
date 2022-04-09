#ifndef C_CDD_TESTS_TEST_STRUCT_H
#define C_CDD_TESTS_TEST_STRUCT_H

#include <greatest.h>

#include "cst.h"

static const char one_structs_src[] = "struct Haz {\n"
                                      "  const char *bzr;\n"
                                      "};\n";

static const char two_structs_src[] = "struct Haz {\n"
                                      "  const char *bzr;\n"
                                      "};\n"
                                      "\n"
                                      "struct Foo {\n"
                                      "  const char *bar;\n"
                                      "  int can;\n"
                                      "  struct Haz *haz;\n"
                                      "};\n";

TEST x_test_one_structs_scanned(void) {
  struct str_elem *scanned = (struct str_elem *)scanner(one_structs_src);
  struct str_elem *iter;
  enum { n = 5 };
  size_t i = 0;
  static const char *scanned_str_l[n] = {
      "struct Haz ", "{", "\012  const char *bzr;", "\012}", ";"};

  for (iter = scanned; iter != NULL; iter = iter->next)
    ASSERT_STR_EQ(iter->s, scanned_str_l[i++]);
  PASS();
}

TEST x_test_two_structs_scanned(void) {
  struct str_elem *scanned = (struct str_elem *)scanner(two_structs_src);
  struct str_elem *iter;
  enum { n = 12 };
  size_t i = 0;
  static const char *scanned_str_l[n] = {"struct Haz ",
                                         "{",
                                         "\012  const char *bzr;",
                                         "\012}",
                                         ";",
                                         "\012\012struct Foo ",
                                         "{",
                                         "\012  const char *bar;",
                                         "\012  int can;",
                                         "\012  struct Haz *haz;",
                                         "\012}",
                                         ";"};

  for (iter = scanned; iter != NULL; iter = iter->next)
    ASSERT_STR_EQ(iter->s, scanned_str_l[i++]);
  PASS();
}

SUITE(struct_suite) {
  RUN_TEST(x_test_one_structs_scanned);
  RUN_TEST(x_test_two_structs_scanned);
}

#endif /* !C_CDD_TESTS_TEST_STRUCT_H */
