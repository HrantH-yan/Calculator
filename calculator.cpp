#include <iostream>


int main()
{
    float num1;
    float num2;
    char oprtr;
    std::cout<<"Enter an expression consisting of two positive numbers\n";
    std::cout<<"Only '+' '-' '*' '/' operators allowed\n";
    std::cout<<"Enter -1 to exit\n"; 

    std::cin>>num1;
    while (num1 != -1)
    {    
        std::cin>>oprtr;
        std::cin>>num2;
        if((num1 <= 0) || (num2 <= 0))
        {
            std::cerr<<"Wrong input: Only positive numbers allowed\n";
            return 1;
        }

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
                std::cerr<<"Division by 0\n";
                return 1;
            }
            std::cout<<num1 / num2<<'\n';
            break;
        default:
            std::cerr<<"Wrong input only '+' '-' '*' '/' operators allowed(f.e. '10.5 * 30')\n";
            return 1;
        }

        std::cout<<"Enter -1 to exit\n"; 
        std::cin>>num1;
    }

    std::cout<<"Program successfully finished\n"; 
    return 0;
}
