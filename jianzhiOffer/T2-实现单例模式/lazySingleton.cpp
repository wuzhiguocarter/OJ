//头文件中
class Singleton  
{
    public:
        static Singleton& Instance()
        {
            if (instance_ == NULL)
            {
                instance_ = new Singleton;
            }
            return *instance_;
         }
    private:
        Singleton()；
        ~Singleton()；
        Singleton(const Singleton&);
        Singleton& operator=(const Singleton&);
    private:
        static Singleton* instance_;
};
//test.cpp 使用单例
Singleton* Singleton::instance_ = NULL;  
Singleton *p = Singleton::Instance();
// ...
// 
// 注意，这里Instance()返回的实例的引用而不是指针，如果返回的是指针
// 可能会有被外部调用者delete掉的隐患，所以这里返回引用会更加保险一些。
// 并且直到Instance()被访问，才会生成实例，
// 这种特性被称为延迟初始化（Lazy initialization），
// 这在一些初始化时消耗较大的情况有很大优势。

// Lazy Singleton不是线程安全的，比如现在有线程A和线程B，
// 都通过instance_ == NULL的判断，那么线程A和B都会创建新实例。
// 单例模式保证生成唯一实例的规则被打破了。