#include <iostream>

int main()
{
    using namespace std;
    char buffer[80] = {'\0'};
    cout << "Enter the string:" << endl;
    //下面2种方法获取数据
#if 0
    /*没有边界检查，超过可能出现意想不到的后果，不安全*/
    cin  >> buffer;
#else
    /*最多可以获取79个字符，有边界检查，更安全*/
    cin.get(buffer,79);
#endif
    cout << "Here is the Buffer: " << buffer <<endl;
    return 0;
}


