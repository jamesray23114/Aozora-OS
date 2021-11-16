
void kernel_main()
{
    char* vram = (char*) 0xb8000;
    vram[0] = 'c';    

    char* test = (char*) 0x100000;
    test[0] = 'h';

    vram[2] = test[0];

    return;
}

