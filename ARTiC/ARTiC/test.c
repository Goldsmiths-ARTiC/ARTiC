void do_math(int *x) {
  *x += 5;
}

void do_math2(int *x) {
  *x += 5;
}

int main(void) {
  int result = -1, val = 4;
  do_math(&val);
  do_math2(&val);
  return result;
}
