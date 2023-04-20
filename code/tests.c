#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "counts.h"

void runFileTest(char * filename, char * target, int expected) {
  int actual = countWord(filename, target);
  cr_assert_eq(expected,actual);
}

Test(lex20, test_01) { runFileTest("../data/file01", "therefore", 2); }
Test(lex20, test_02) { runFileTest("../data/file01", "the", 0); }
Test(lex20, test_03) { runFileTest("../data/file02", "therefore", 1); }
Test(lex20, test_04) { runFileTest("../data/file02", "the", 2); }
Test(lex20, test_05) { runFileTest("../data/file03", "the", 13); }
Test(lex20, test_06) { runFileTest("../data/file03", "are", 2); }
Test(lex20, test_07) { runFileTest("../data/file03", "grippe", 1); }
Test(lex20, test_08) { runFileTest("../data/file03", "as", 3); }
Test(lex20, test_09) { runFileTest("../data/file03", "was", 3); }
