#include <stdio.h>
int main() 
{
	//char 主要用于处理字符数据，既可以表示单个字符，也可以通过字符数组表示字符串。
    char input[9];      // 存储输入的8个字符 + 结束符
    char birthday[] = "19820928";  // 生日字符串
    char encoded[9];    // 存储编码结果
    char decoded[9];    // 存储解码结果
    
    printf("请输入8位字符: ");
    scanf("%8s", input);  // 读取8个字符
    
    
    // 编码过程：按位异或
    printf("\n编码过程:\n");
    for(int i = 0; i < 8; i++) {
        encoded[i] = input[i] ^ birthday[i];
        printf("%c XOR %c = %d\n", input[i], birthday[i], (unsigned char)encoded[i]);
    }
	//%c 是 C 语言中用于输出 字符类型（char） 的格式说明符。
    encoded[8] = '\0';  // 字符串结束符
    
    printf("\n编码结果(十进制): ");
    for(int i = 0; i < 8; i++) {
        printf("%d ", encoded[i]);
    }
    printf("\n");
    
    // 解码过程：再次按位异或
    printf("\n解码过程:\n");
    for(int i = 0; i < 8; i++) {
        decoded[i] = encoded[i] ^ birthday[i];
        printf("%d XOR %c = %c\n", encoded[i], birthday[i], decoded[i]);
    }
    decoded[8] = '\0';  // 字符串结束符
    
    printf("\n解码结果: %s\n", decoded);
    
    // 验证是否相同
    printf("\n验证结果: ");
    int same = 1;
    for(int i = 0; i < 8; i++) {
        if(input[i] != decoded[i]) {
            same = 0;
            break;
        }
    }
    
    if(same) {
        printf("? 解码结果与原始输入相同！\n");
    } else {
        printf("? 解码结果与原始输入不同！\n");
    }
    
    return 0;
}