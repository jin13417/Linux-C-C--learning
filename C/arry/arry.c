#include <stdio.h>
int main()
{
    int j,i;
    char a[3][3] = {1,2,3,4,5,6,7,8,9};
    for(i = 0; i < 3; i ++)
    {
        for(j = 0; j < 3; j ++)
            printf("%p\t",&a[i][j]);
        puts("");
    }

    printf("a[0] = %#x\na[1] = %#x\na[2] = %#x\n",&a[0][0],&a[1][0],&a[2][0]);
    getchar();
    printf("a = %#x\n",a);
    printf("&a = %#x\n",&a);
    printf("&a  + 1= %#x\n",&a + 1);
    printf("a+1 = %#x\n",a + 1);
    printf("*(a+1) = %#x\n",*(a + 1));
    printf("a[1] + 1 = %#x\n",a[1] + 1);
    printf("&a[1] = %#x\n",&a[1]);
    printf("&a[1][0] = %#x\n",&a[1][0]);
    printf("a[1] = %#x\n",a[1]);
    printf("(a[1] + 1) + 1 = %#x\n",(a[1] + 1) + 1);
    printf("a[1][0] = %#x\n",a[1][0]);
    printf("*(&a[1][0]) = %#x\n",*&a[1][0]);
    printf("new = %#x\n",);
    return 0;

}
