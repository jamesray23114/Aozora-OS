static inline int sqrt(int number) 
{
    if (number == 0 || number == 1)
    return number;
 
    int i = 1, result = 1;
    while (result <= number)
    {
      i++;
      result = i * i;
    }
    return i - 1;
}

static inline int p2(int number)
{
    return number * number;
}

static inline int p3(int number)
{
    return number * number * number;
}