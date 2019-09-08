#include <cstdio>
#include <cmath>
#include <string>

using namespace std;

bool isNumber(const string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}

int main(int argc, char **args){

    FILE *first = fopen(args[1], "r");
    FILE *second = fopen(args[2], "r");

    int flag1, flag2;
    char cstr1[100], cstr2[100];
    double precision = 1e-5;
    const double eps = 1e-16;
    string str1, str2;

    while(true){
        flag1 = fscanf(first, "%s", cstr1);
        flag2 = fscanf(second, "%s", cstr2);
        str1 = cstr1;
        str2 = cstr2;

        // check for equal amount of number
        if(flag1==EOF && flag2==EOF){
            printf("100\n");
            return 0;
        }
        else if(flag1==EOF || flag2==EOF){
            printf("0\n");
            printf("Number of words are does not match. i.e. number of written values does not match.\n");
            return 0;
        }

        // check for stringls
        flag1 = isNumber(str1);
        flag2 = isNumber(str2);
        if(flag1!=flag2 || (!flag1 && !flag2 && str1!=str2)){
            printf("0\n");
            printf("Headers are different.\n");
            return 0;
        }

        if(flag1 && flag2)
        {
            double val1 = stod(cstr1);
            double val2 = stod(cstr2);
            if(fabs(val1)<precision && fabs(val2)<precision)
                continue;
                
            if(fabs(val1-val2)/(fabs(val1)+fabs(val2)+eps) > precision){
                printf("0\n");
                printf("Written values are different. values = %lf and %lf", val1, val2);
                return 0;
            }
        }

    }

    return 0;
}
