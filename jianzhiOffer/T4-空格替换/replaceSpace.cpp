// T4-Replace Space
// 题目描述 
// 请实现一个函数，将一个字符串中的空格替换成“%20”。
// 例如，当字符串为We Are Happy.
// 则经过替换之后的字符串为We%20Are%20Happy。

// 借助辅助空间，使用队列保存临时字符串，然后再拷贝到原址
// 时间复杂度O(n), 空间复杂度O(n)
class Solution {
public:
    void replaceSpace(char *str,int length) {
        char *str_temp = str;
        if(str_temp==NULL) return;
         
        deque<char> ch;
        while(*str_temp != '\0'){
            if(*str_temp==' '){
                ch.push_back('%');
                ch.push_back('2');
                ch.push_back('0');
            }
            else
                ch.push_back(*str_temp);
             
            str_temp++;
        }
        if(length < ch.size())
            return;
        for(deque<char>::iterator it = ch.begin();it != ch.end();it++){
            *str = *it;
            str++;
        }
        *str = '\0'; // 涉及到C风格字符串，一定不能忘记结尾字符
    }
};

// 双指针，原址操作
// 时间复杂度O(n)，空间复杂度O(1)
class Solution {
public:
	void replaceSpace(char *str,int length) {
		// 输入检查
		if(str == NULL) return;
        
        // 针对字符指针的副本进行操作
        char *str0 = str;

        // 遍历字符串，统计空格数和字符串长度
        int blankCnt = 0;
        int len = 0;
        while(*str0 != '\0')
        {
            len++; // count for string length
            if (*str0 == ' ')
                blankCnt++; // count for blank
            str0++;
        }

        if(len+1 + 2*blankCnt > length) return;

 		// 使用双指针, 初始化指针p1指向当前字符串的末尾，指针p2指向最终字符串的末尾
        char *p1 = str + len+1;
        char *p2 = str + len+1 + 2*blankCnt;
 		
 		// 若p1 != p2 则迭代进行如下操作
 			// 若p1未指向空格，则将p1处字符挪到p2处，然后p1,p2递减1
 			// 若p1指向正常字符，则将p2处及前面两个字节赋值为'0' '2' '%'，p2每次赋值完递减1
 		// 若p1 = p2 则说明从后向前遍历到了第一个字符，
        while(p1 != p2)
        {
            int charCnt = 0;
            while(*p1 != ' ')
            {
                *p2 = *p1;
                p1--;
                p2--;
                charCnt++;
            }
            *p2-- = '0';
            *p2-- = '2';
            *p2-- = '%';
            p1--;
        }
	}
};