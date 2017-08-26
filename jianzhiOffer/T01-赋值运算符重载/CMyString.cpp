class CMyString
{
private:
	char* m_pData;
public:
	CMyString(char *pData);
	CMyString(const Cstring &str);
	CMyString & operator=(const CMyString &str);
	~CMyString();
};

// default constructor
CMyString::CMyString(char *pData = NULL)
{
    if(pData == NULL)
    {
        m_pData = new char[1];
        m_pData[0] = '\0';
    }
    else
    {
        int length = strlen(pData);
        m_pData = new char[length + 1];
        strcpy(m_pData, pData);
    }
}

// copy constructor
CMyString::CMyString(const Cstring &str){
	// 分配内存
    int length = strlen(str.m_pData);
    m_pData = new char[length + 1];
    // 拷贝字符串,包括结尾字符'\0'
    strcpy(m_pData, str.m_pData);
}

//  copy assignment operator

// 解法一：不考虑异常安全的做法
// CMyString & CMyString::operator=(const CMyString &str){
// 	// 判断是否是同一个对象
// 	if(this == &str)
// 		return *this;
// 	// 释放指针成员原有指向的内存
// 	delete [] m_pData;
// 	m_pData = NULL;

// 	// 为指针成员分配新的内存并把str拷贝过去
// 	m_pData = new char[strlen(str.m_pData)+1];// 如果new抛出bad_alloc异常，则原来实例失效
// 	strcpy(m_pData, str,m_pData);

// 	return *this;
// }

// 解法二：考虑异常安全的做法: copy and swap
CMyString & CMyString::operator=(const CMyString &str){
	if(this != &str){
		CMyString strTemp(str);// 深拷贝

		// 交换strTemp.m_pData和m_pData指针
		char *pTemp = strTemp.m_pData;
		strTemp.m_pData = m_pData;
		m_pData = pTemp;
	}// 超出strTemp作用范围，调用析构函数
	 // 由于strTemp.m_pData指向原来的实例,所以析构原来的字符串
	return *this;
}

// destructor
CMyString::~CMyString()
{
    delete[] m_pData; // 与new []匹配
}