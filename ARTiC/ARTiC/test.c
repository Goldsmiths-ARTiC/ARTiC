void do_math(int *x, int *y) {
  *x += 5;
}

int main(int argc, char** argv) {
  int result = -1, val = 4;
  do_math(&val);
  return result;
}
