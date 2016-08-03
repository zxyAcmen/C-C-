#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*�Լ�ʵ��strtok˼·
ʹ�þ�̬�������ѭ���ָ�Ҫ������ַ���
ʹ��ָ��Ϊָ���һ���ַ��ָ��ָ��,ָ����Ҫ�ָ��ַ������׵س�,
ʹ��ָ��ָ������ָ��,������ÿһ���ָ��
ʹ��һ����ʱָ�����ڷ��طָ����ַ���

��һ�δ���ʱ,��Դ�ַ�����ֵ����̬����,(��̬�������ص���,ֻ��ʼ��һ��,���ھ�̬��,��������Ϊ����������ֹ�ᱻ�ͷ� )
�ڶ���strtokԴ�ַ����Ǵ�NULL,��ʱ���Ը��ݾ�̬�����ǲ���ΪNULL,����ǰԴ�ַ�����û�е���β,

�Ѿ�̬�ַ���ָ�븳ֵ��Ѱ�ҷָ��ָ��,�ָ��ָ��ѭ�����Ƚ�,�ҵ��ָ��������ָ�����λ��ʱ,�Ѿ�ָ̬��������ָ��,
�ָ��ָ�벻�������Ҽ���������,�������ֱ����һ���ַ����Ƿָ�����е�һԱ,������ָ̬���һֱ��ָ��Ϊ�ָ����λ��
���ָ���ҵ��ָ��ʱ,�Ҳ�����ָ̬�����ʱ,�൱���ҵ����Է��ص��ַ���,ʹ��һ��flag����������Ƚ�ѭ��.��ʱ�ѷָ��ָ�����ָ̬��Ϳ��Եõ�Ҫ�ָ�����ַ�����.
��Ȼ���Ҫ���ǲ���Ϊ��β�ж�,Ϊ��βʱֱ�ӷ���NULL��ʾ����

*/

char * my_strtok(char * src, char *str)
{

	static char * pSrc     = NULL;      //��¼��һ�δ�������ֵ
	char		*pStr      = NULL;      //��¼�������ķָ����ָ����
	char	    *tmpSrc    = NULL;      //Դ�ַ����ĸ���ָ��,ѭ������ �������ָ��ָ��
	char        *tmpBuf	   = NULL;      //���ر���
	char	    *tmpStr    = NULL;      //�ָ���ĸ���ָ��,ѭ������

	if (str == NULL)
	{
		printf("����ĵس���Ч!\n");
		return  NULL;
	}
	if (src == NULL && pSrc == NULL)
	{
		printf("����ĵس���Ч!\n");

		return  NULL;
	}
	else if (src != NULL && pSrc == NULL)
	{
		//��һ��ִ��
		pSrc = src;
	}

	pStr = str;

	//�����ҵ��ָ��ʱ,����ѭ�����
	int falg = 0;
          
	//����Դ�ַ�����ѭ��
	for (tmpSrc = pSrc; *tmpSrc != '\0'; tmpSrc++)
	{
		//���Ʒָ����
		for (tmpStr=pStr; *tmpStr != '\0'; tmpStr++)
		{
			//Դ�ַ������ҵ��ָ��
			if (*tmpSrc == *tmpStr)
			{
				//�����зָ�������ڵ�һ��λ��ʱ,����̬���ַ���ȥ����һ��,Ҳ���������ָ��,���·ָ�
				//��Ϊ��������λ��ʱ,���ӡ�ո� ��Ҫ���Կո�ָ�,�ٴ�ӡ�ո񲻺���,Ҳ����˵���зָ��
				//�������Դ�ӡ����ĻtmpSrc == pSrc   �ж�ѭ������ָ��;�ָ̬���λ���ǲ���һ��,һ��֤�������ڵ�һ��λ��
				if ((tmpSrc == pSrc/*&&*tmpSrc == *tmpStr) || (tmpSrc == pSrc&&*tmpSrc == *(tmpStr+1))
					|| (tmpSrc == pSrc&&*tmpSrc == *(tmpStr + 2)) || (tmpSrc == pSrc&&*tmpSrc == *(tmpStr + 3)*/))
				{
					//���ҵ��ָ������Ϊ��һ���ַ�ʱ,��ʱû�б�Ҫ�ٸ������ָ�����бȽ�,ֱ����������ָ��ѭ��,����һ��Դ�ȽϷ�
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
	//��ָ��Ϊ�ָ����ָ�븳ֵ��Ҫ���ص��ַ�ָ��
	tmpBuf = pSrc;
	//����������ʱ,����NULL
	if (*tmpBuf == '\0')
			return NULL;

	//��ʱ��tmpSrc ָ����Ƿָ��λ��,��ȥ�����Էָ����ͷ��Դ�ַ�λ��,�õ��ָ�������ַ���,�����λ��0 ��ֹ����
	tmpBuf[tmpSrc-pSrc] = '\0';

	//�Ѿ�̬�ַ������ָ���ĺ�һ��λ��
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