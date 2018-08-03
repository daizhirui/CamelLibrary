typedef void (*FuncPtr)(void);
void test() {
    int i = 0x10000014;
    FuncPtr funcptr;
    funcptr = (FuncPtr)0x10000014;
    funcptr();
}
