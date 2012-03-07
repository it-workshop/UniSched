int main(void)
{
    long long lv;
    unsigned long long ul;

    return ((sizeof(lv) >= 8) && (sizeof(ul) >= 8)) ? 0 : 1;
}
