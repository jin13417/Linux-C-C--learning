#include <iostream> /*io库*/
#define N 1

/*有些编译器允许main()的返回类型VOID，但是这种写法已不再是合法的C++程序
 *请不要养成这种习惯。应该让main（）返回int，像下面返回0就可以了。
 * */
int main()
{
#if 0
    std::cout << "hello world\n";/*标准的hello world!程序*/
    /* \n 和 std::endl 都是换行符的意思，但是使用后者会更好
     * 因为在有些系统下可能不能识别\n.
     * endl = end line 的意思*/
    std::cout << "my name is jsh "<<std::endl;
    std::cout << "cumputer 2+3=" << 5 <<std::endl;
#endif


    /*下面是2中方式使用命名空间的方法*/
#if N
    using std::cout;
    using std::endl;
#else
    using namespace std;
#endif
    cout << "my name is jsh "<<endl;
    cout << "cumputer 2+3=" << 5 <<endl;

    return 0;
}
