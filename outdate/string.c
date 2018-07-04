
char* cm_strcat(char* des, char* source)
{
    int index;
    index = DATA_SIZE -1;
    char * tmp = des;
    while (*tmp) {
        index--;
        tmp++;
        if (index == 0)
            return des;
    }
    while (*source) {
        *tmp++ = *source++;
        index--;
        if (index == 0)
            return des;
    }
    *tmp = '\0';
    return des;
}

char* charcat(char * des, char source)
{
    int index;
    char * tmp = des;
    index = DATA_SIZE - 2;
    while (*tmp) {
        tmp++;
        index--;
        if (index == 0)
            return des;
    }
    *tmp++ = source;
    *tmp = '\0';
    return des;
}