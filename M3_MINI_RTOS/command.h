#define MAX_STRING_LENGTH 32  // 변환할 문자열의 최대 길이

// 문자를 소문자로 변환하는 함수
int my_tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

// 문자열 길이를 계산하는 함수
int my_strlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// 문자열을 소문자로 변환하는 함수
void my_tolower_str(const char *str, char *result) {
    int length = my_strlen(str);

    // 문자열의 각 문자를 소문자로 변환하여 결과 문자열에 저장
    int i;
    for (i = 0; i < length; i++) {
        result[i] = my_tolower(str[i]);
    }

    // 문자열 끝에 null 문자 추가
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
