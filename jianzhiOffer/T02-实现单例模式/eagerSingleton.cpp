//头文件中
class Singleton  
{
    public:
        static Singleton& Instance()
        {
            return instance;
        }
    private:
        Singleton();
        ~Singleton();
        Singleton(const Singleton&);
        Singleton& operator=(const Singleton&);
    private:
        static Singleton instance;
}
//实现文件中
Singleton Singleton::instance;  
// 这种实现在程序开始(静态属性instance初始化)
// 的时就完成了实例的创建。这正好和上述的Lazy Singleton相反。
// 由于在main函数之前初始化，所以没有线程安全的问题，
// 但是潜在问题在于no-local static对象（函数外的static对象）
// 在不同编译单元（可理解为cpp文件和其包含的头文件）
// 中的初始化顺序是未定义的。
// 如果在初始化完成之前调用 Instance()方法会返回一个未定义的实例。