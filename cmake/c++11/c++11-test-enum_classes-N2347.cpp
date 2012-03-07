enum class A
{
    b = 42
};

int main()
{
    return !(static_cast<int>(A::b) == 42);
}
