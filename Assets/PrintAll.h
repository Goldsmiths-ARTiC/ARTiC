int foo(int i)
{
    if (i > 0)
    {
        return i + 1;
    }
}


int doo(int i)
{
    for (int j = 0; j < 10; ++j)
    {
        i += 1;
    }
    return i;
};


int main(void) {
    int a, b, c = 0;
    const int d;
    a = foo(b);
    b = doo(a);
    int * e;
    const int* f;
}
