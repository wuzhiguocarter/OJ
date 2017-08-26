class Singleton  
{
public:
    static Singleton& Instance()
    {
        static Singleton instance；
        return instance；
    }
private:
        Singleton()；
        ~Singleton()；
        Singleton(const Singleton&);
        Singleton& operator=(const Singleton&);
};

// C++0x之后是该实现线程安全的，
// 有兴趣可以读相关的标准草案（section 6.7）编译器支持程度不一定,
// 但是G++4.0及以上是支持的。