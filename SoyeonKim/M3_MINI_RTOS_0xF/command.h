#define MAX_STRING_LENGTH 32  // ��ȯ�� ���ڿ��� �ִ� ����

// ���ڸ� �ҹ��ڷ� ��ȯ�ϴ� �Լ�
int my_tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

// ���ڿ� ���̸� ����ϴ� �Լ�
int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// ���ڿ��� �ҹ��ڷ� ��ȯ�ϴ� �Լ�
void my_tolower_str(const char *str, char *result) {
    int length = my_strlen(str);

    // ���ڿ��� �� ���ڸ� �ҹ��ڷ� ��ȯ�Ͽ� ��� ���ڿ��� ����
    int i;
    for (i = 0; i < length; i++) {
        result[i] = my_tolower(str[i]);
    }

    // ���ڿ� ���� null ���� �߰�
    result[length] = '\0';
}

int my_strcasecmp(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        char c1 = my_tolower((unsigned char)*str1);
        char c2 = my_tolower((unsigned char)*str2);

        if (c1 != c2) {
            return c1 - c2;
        }

        str1++;
        str2++;
    }

    return 0;
}
