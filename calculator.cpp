#include <iostream>

struct Word
{
    int length = 0;
    char *arr = new char[0];
};

Word append(Word input, char sym);
float chars_to_num(Word input,int idx_point); // converts a number from expression to float


int main()
{
    char oprtr;
    char sym;
    Word w_num1;
    Word w_num2;
    int idx_point1;
    int idx_point2;
    int idx;     
    std::cout<<"Enter an expression consisting of two non negative numbers, add '=' at the end\n";
    std::cout<<"Only '+' '-' '*' '/' operators allowed\n";
    while (true)
    {
        std::cout<<"Enter '-1' to end\n"; 
        delete[] w_num1.arr;
        delete[] w_num2.arr;
        w_num1.arr = new char[0];
        w_num2.arr = new char[0];
        w_num1.length = 0;
        w_num2.length = 0;
        idx = 1;
        idx_point1 = -1;
        idx_point2= -1;
        bool end_cond = true;
        while (true)
        {
            std::cin>>sym;
            if (sym == '.' && idx == 1)
            {
                idx_point1 = w_num1.length;
                ++idx;
            }
            else if (!isdigit(sym))
            {
                oprtr = sym;
                break;
            }
            w_num1 = append(w_num1, sym);
            end_cond = false;
        }

        while (true)
        {
            std::cin>>sym;

            if (end_cond && sym == '1')     // end condition
            {
                std::cout<<"\nProgram finished\n";
                return 0;
            }

            if (sym == '.' && idx < 3)
            {
                idx_point2 = w_num2.length;
                idx= idx + 10;  //no more points
            }
            else if (sym == '=')
            {
                break;
            }
            else if (!isdigit(sym))
            {
                std::cout<<"\nWrong input only '+' '-' '*' '/' operators allowed(f.e. '10.5 * 30'):\n";
                return 0;
            }
            w_num2 = append(w_num2, sym);
            end_cond = false;
        }

        float num1;
        float num2;
        num1 = chars_to_num(w_num1, idx_point1);
        num2 = chars_to_num(w_num2, idx_point2);
        switch (oprtr)
        {
        case '+':
            std::cout<<num1 + num2<<'\n';
            break;
        case  '-':
            std::cout<< num1 - num2<<'\n';
            break;
        case '*':
            std::cout<< num1 * num2<<'\n';
            break;
        case '/':
            if (num2 == 0)
            {
                std::cout<<"Division by 0 not allowed: Try again\n";
                break;
            }
            std::cout<<num1 / num2<<'\n';
            break;
        default:
            std::cout<<"\nWrong input only '+' '-' '*' '/' operators allowed(f.e. '10.5 * 30'):\n";
            break;
        }
    }
    return 0;
}

float chars_to_num(Word input, int idx_point)
{
    if (idx_point == -1) //if num is integer(no '.' input in num) setting idx_point at the end of num
    {
        idx_point = input.length;
    }
    float num = 0;
    float digit_mul = 1;
    for (int k = idx_point -1; k >= 0 ;--k)  // before '.'
{
        num = num + (input.arr[k] ^ 48)*digit_mul;
        digit_mul = digit_mul * 10;
    }
    digit_mul = 0.1;
    for (int k =idx_point +1; k < input.length ;++k) //after '.'
    {
        num = num + (input.arr[k] ^ 48)*digit_mul;
        digit_mul = digit_mul / 10;
    }
    return num;
}

Word append(Word input, char sym)
{
    Word word;
    delete[] word.arr;
    word.arr = new char[input.length+1];
    for (int k = 0; k < input.length; ++k)
    {
        word.arr[k] = input.arr[k];
    }
    word.arr[input.length] = sym;
    word.length = input.length + 1;
    return word;
}