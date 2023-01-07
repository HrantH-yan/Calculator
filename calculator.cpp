#include <iostream>

struct Expression
{
    int idx_point1 = -1;
    int idx_point2 = -1;
    int idx_op;
    char op;
    int length;
    char *arr = new char[0];
};

bool num_check(char *expression, int start, int end, int idx_point); // checks if the number from expression is correct
float chars_to_num(char *expression, int start, int end, int idx_point); // converts a number from expression to float
Expression input_char_arr(char end); // inputting and storing chars in array(till end symbol), and collecting parameters


int main()
{
    while (true)
    {
        Expression expr;
        std::cout<<"Enter an expression consisting of two non negative numbers, add '=' at the end\n";
        std::cout<<"Enter '-1 =' to end\n"; 
        expr = input_char_arr('=');
        if((expr.arr[0] == '-') && expr.arr[1] == '1')  // end condition
        {
            std::cout<<"\nProgram finished\n";
            return 0;
        }
        if (!num_check(expr.arr, 0, expr.idx_op, expr.idx_point1))  //checking num1 ( if there are other symbols exept point1)
        {
            std::cout<<"Wrong input(example of allowed expression '10.5 * 30'): Try again\n";
            return 0;
        }
        if (!num_check(expr.arr, expr.idx_op+1, expr.length, expr.idx_point2)) //checking num2
        {
            std::cout<<"Wrong input(example of allowed expression '10.5 * 30'): Try again\n";
            return 0;
        }

        float num1 = 0;
        float num2 = 0;        
        num1 = chars_to_num(expr.arr, 0 , expr.idx_op, expr.idx_point1);
        num2 = chars_to_num(expr.arr, expr.idx_op + 1, expr.length, expr.idx_point2);
       
        switch (expr.op)
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
            std::cout<<"Wrong input: Try again\n";
            break;
        }
    }
    return 0;
}



bool num_check(char *expression, int start, int end, int idx_point)
{
    if (isdigit(expression[start]))
    {
        for (int k = start; k < end;++k)
        {
            if (k == idx_point)
            {
                continue;
            }
            else if(!isdigit(expression[k]))
            { 
                return false;
                break;
            }
        } 
    }
    else
    {
        return false;
    }
    return true;
}

float chars_to_num(char *expression, int start, int end, int idx_point)
{
    if (idx_point == -1) //if num is integer(no '.' input in num) setting idx_point at the end of num
    {
        idx_point = end;
    }
    float num = 0;
    float digit_mul = 1;
    for (int k = idx_point -1; k >= start ;--k)  // before '.'
{
        num = num + (expression[k] ^ 48)*digit_mul;
        digit_mul = digit_mul * 10;
    }
    digit_mul = 0.1;
    for (int k =idx_point +1; k < end ;++k) //after '.'
    {
        num = num + (expression[k] ^ 48)*digit_mul;
        digit_mul = digit_mul / 10;
    }
    return num;
}

Expression input_char_arr(char end)
{
    int i = 0;
    int idx = 1;
    char sym;
    char *temp = new char[0];
    Expression expr;
    while(true)
    {
        
        std::cin>>sym;
        if (sym == end)
        {
            break;
        }
        if (sym == '.' && idx == 1)
        {
            expr.idx_point1 = i;
            ++idx;
        }        
        else if (sym == '.' && idx == 2)
        {
            expr.idx_point2 = i;
            ++idx;
        }
        else if (!isdigit(sym) && sym != '.')
        {
            expr.idx_op = i;
            expr.op = sym; 
        }

        if (i % 2 == 0)                        // deleting space in heap allocated to expression 
        {                                      // and allocating new one bigger by one char
        delete[]  expr.arr;                    // copy all elements from temp to expression
        expr.arr = new char[i+1];              // and adding new sym
        for (int k = 0; k < i; ++k)
        {
            expr.arr[k] = temp[k];
        }
        expr.arr[i] = sym;
        }
        else if (i % 2 == 1)                 
        {
            delete[]  temp;
            temp = new char[i+1];
            for (int k = 0; k < i; ++k)
            {
                temp[k] = expr.arr[k];
            }
            temp[i] = sym;
        }
        ++i;
    }             
    if (i % 2 == 0)
    {    
        expr.arr[i-1] = temp[i-1];
        delete[] temp;
    }        //at the end of loop i is also the length of expression 
    expr.length = i;
    return expr;    

}