#include <stdio.h>
#include <unistd.h>

#include "minunit.h"
#include "file.h"

int tests_run = 0;

char* dir = "new_dir";
char* filename = "/test.txt";

void tear_down() {
  if (unlink("sites/new_dir/test.txt") == -1)
    perror("unlink");
  if (rmdir("sites/new_dir") == -1)
    perror("rmdir");
}

static char* test_file_save() {
  char *content = "This is a test file";
  mu_assert("file.c error, couldn't create and save the file", file_save(content, dir, filename) != -1);
  return 0;
}

static char* all_tests() {
  mu_run_test(test_file_save);
  return 0;
}

int main(int argc, char** argv) {
  char* result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  } else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  tear_down();

  return result != 0;
}
