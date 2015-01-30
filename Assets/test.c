void test_do_math(int *x) {
  *x += 5;
}

int main(void) {
  int result = -1, val = 4;
  test_do_math(&val);
  return result;
}
