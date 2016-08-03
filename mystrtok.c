#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*自己实现strtok思路
使用静态变量解决循环分割要保存的字符串
使用指向不为指向第一个字符分割符指针,指向需要分割字符串的首地扯,
使用指向分割符串的指针,依次找每一个分割符
使用一个临时指针用于返回分割后的字符串

第一次传参时,把源字符串赋值给静态变量,(静态变量的特点是,只初始化一次,存在静态区,生命周期为整个程序终止会被释放 )
第二次strtok源字符串是传NULL,此时可以根据静态变量是不是为NULL,决定前源字符串有没有到结尾,

把静态字符串指针赋值给寻找分割符指针,分割符指针循环向后比较,找到分割符且这个分割是首位置时,把静态指针跳这个分割符,
分割符指针不作处理且继续向后查找,依次向后直到第一个字符不是分割符串中的一员,这样静态指针会一直到指向不为分割符的位置
当分割符找到分割符时,且不跟静态指针相等时,相当于找到可以返回的字符串,使用一个flag标记来跳出比较循环.此时把分割符指针减静态指针就可以得到要分割出的字符串了.
当然最后要做是不是为结尾判断,为结尾时直接返回NULL表示结束

*/

char * my_strtok(char * src, char *str)
{

	static char * pSrc     = NULL;      //记录第一次传进来的值
	char		*pStr      = NULL;      //记录传进来的分割符或分割符串
	char	    *tmpSrc    = NULL;      //源字符串的辅助指针,循环因子 依次向后指向分割符
	char        *tmpBuf	   = NULL;      //返回变量
	char	    *tmpStr    = NULL;      //分割符的辅助指针,循环因子

	if (str == NULL)
	{
		printf("传入的地扯无效!\n");
		return  NULL;
	}
	if (src == NULL && pSrc == NULL)
	{
		printf("传入的地扯无效!\n");

		return  NULL;
	}
	else if (src != NULL && pSrc == NULL)
	{
		//第一次执行
		pSrc = src;
	}

	pStr = str;

	//用于找到分割符时,跳出循环语句
	int falg = 0;
          
	//控制源字符串的循环
	for (tmpSrc = pSrc; *tmpSrc != '\0'; tmpSrc++)
	{
		//控制分割符串
		for (tmpStr=pStr; *tmpStr != '\0'; tmpStr++)
		{
			//源字符串中找到分割符
			if (*tmpSrc == *tmpStr)
			{
				//把所有分割符出现在第一个位置时,将静态的字符串去掉第一个,也就是跳过分割符,重新分割
				//因为出现在首位置时,会打印空格 需要是以空格分割,再打印空格不合理,也就是说所有分割符
				//都不可以打印到屏幕tmpSrc == pSrc   判断循环因子指针和静态指针的位置是不是一样,一样证明出现在第一个位置
				if ((tmpSrc == pSrc/*&&*tmpSrc == *tmpStr) || (tmpSrc == pSrc&&*tmpSrc == *(tmpStr+1))
					|| (tmpSrc == pSrc&&*tmpSrc == *(tmpStr + 2)) || (tmpSrc == pSrc&&*tmpSrc == *(tmpStr + 3)*/))
				{
					//当找到分割符且又为第一个字符时,此时没有必要再跟其它分割符进行比较,直接跳出这个分割符循环,找下一个源比较符
					pSrc+=1;
					break;
				}
				else 
				{
					falg = 1;
					break;
				}

			}
		}
		if (falg == 1)
			break;
	}
	//把指向不为分割符的指针赋值给要返回的字符指针
	tmpBuf = pSrc;
	//如果到达最后时,返回NULL
	if (*tmpBuf == '\0')
			return NULL;

	//此时的tmpSrc 指向的是分割符位置,减去不是以分割符开头的源字符位置,得到分割出来的字符串,把最后位置0 防止乱码
	tmpBuf[tmpSrc-pSrc] = '\0';

	//把静态字符跳过分割符的后一个位置
	pSrc =tmpSrc+1;        
	return tmpBuf;
}

int main()
{
	char src[] = "   -   This,       a          sample string.............";
	char * pch;
	char str[] = " ,.-";

	pch = my_strtok(src, str);

	while (pch != NULL)
	{
		printf("%s\n", pch);
		pch = my_strtok(NULL, str);
	}
	return 0;
}