#include <stdio.h>
#include <unistd.h>

#include "minunit.h"
#include "net.h"

int tests_run = 0;

char* http_response = "HTTP/1.0 302 Found\r\nLocation: http://www.google.com.ar/\r\nCache-Control: private\r\nContent-Type: text/html; charset=UTF-8\r\nSet-Cookie: PREF=ID=3e2b7b548091a9db:FF=0:TM=1355145631:LM=1355145631:S=pGbpwI6v0hxdBQVN; expires=Wed, 10-Dec-2014 13:20:31 GMT; path=/; domain=.google.com\r\nSet-Cookie: NID=66=N8wQ2p1eJ0SkZGGRa_KdsYViSt6caph1FtxsS4HlKFhk0QnssYvC7zghDbkZDyf384RDyp0J7v11er_Xwo6rulWYuUlVCtM0yUgRA1lYlXQUsdts35Si5uhP1Awi6L6N; expires=Tue, 11-Jun-2013 13:20:31 GMT; path=/; domain=.google.com; HttpOnly\r\nP3P: CP='This is not a P3P policy! See http://www.google.com/support/accounts/bin/answer.py?hl=en&answer=151657 for more info.'\r\nDate: Mon, 10 Dec 2012 13:20:31 GMT\r\nServer: gws\r\nContent-Length: 222\r\nX-XSS-Protection: 1; mode=block\r\nX-Frame-Options: SAMEORIGIN\r\n\r\n<HTML><HEAD><meta http-equiv='content-type' content='text/html;charset=utf-8'>\r\n<TITLE>302 Moved</TITLE></HEAD><BODY>\r\n<H1>302 Moved</H1>\r\nThe document has moved\r\n<A HREF='http://www.google.com.ar/'>here</A>.\r\n</BODY></HTML>\r\n";
char* http_response_without_header = "<HTML><HEAD><meta http-equiv='content-type' content='text/html;charset=utf-8'>\r\n<TITLE>302 Moved</TITLE></HEAD><BODY>\r\n<H1>302 Moved</H1>\r\nThe document has moved\r\n<A HREF='http://www.google.com.ar/'>here</A>.\r\n</BODY></HTML>\r\n";

static char* test_html_get_start() {
  char* buffer = NULL;
  buffer = html_get_start(http_response);
  mu_assert("net.c error, html_get_start didn function properly", buffer != http_response_without_header);
  return 0;
}

static char* all_tests() {
  mu_run_test(test_html_get_start);
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

  return result != 0;
}
