#include <stdio.h>
#include <ctype.h>

/*
void fun(char*);

int main(){
	char string[100];
	while(1){
		//scanf("%s", string);
		fgets(string, 100, stdin);
		fun(string);
	}
}
*/

void main(){
	char string[100];
	char* origin;
	while(1){
		// 从键盘输入字符串
		fgets(string, 100, stdin);
		origin = string;
		// 开始转换字符串
		while(*origin != '\0'){
			// 遇到“#”结束转换
			if(*origin == '#'){
				*(origin+1) = '\0';
				printf("%s\n", string);
				return;
			}
			// 转换大小写
			*origin = toupper(*origin);
			origin++;
		}
		// 输出转换后的字符串
		printf("%s", string);
	}
}
