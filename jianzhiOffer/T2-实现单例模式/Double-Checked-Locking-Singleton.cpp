static Singleton& Instance()  
{
    if (instance_ == NULL) 
    {
        Lock lock; //基于作用域的加锁，超出作用域，自动调用析构函数解锁
        if (instance_ == NULL)
        {
              instance_ = new Singleton;
        }
    }
    return *instance_;
}