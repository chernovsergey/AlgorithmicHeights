#ifndef BOYERMOORE_H
#define BOYERMOORE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using std::string;
using std::vector;
const int ASIZE = 256;
const int XSIZE = 6;

bool isPrefix(string X, int lenX, int p){
    /*
     * Проверяет является ли строка префиксом
    */

    int j = 0;
    for(int i = p; i < lenX; ++i){
        if(X[i] != X[j])
            return false;
        ++j;

     return true;
    }
}

int suffixLength(string X, int lenX, int p){
    /*
     * Возвращает длину наибольшей подстроки, которая является
     * суффиксом шаблона Х
    */

    int len = 0;
    int i = p;
    int j = lenX - 1;
    while(i >= 0 && X[i] == X[j]){
        len += 1;
        --i;
        --j;
    }

    return len;
}

vector<int> prefixBadChar(string X, int lenX){
    /*
     * Вычисление префикс функции "плохого символа"
    */

    vector<int> table(ASIZE);

    // Заполняем значением по умолчанию, равным длине шаблона
    for(int i = 0; i < ASIZE; ++i)
        table[i] = lenX;

    // Вычисление функции по определению
    for(int i = 0; i < lenX - 1; ++i)
        table[(char)X[i]] = lenX - 1 - i;

    return table;

}

vector<int> prefixGoodSuffix(string X, int lenX){
    /*
     * Вычисление префикс функции "хорошего суффикса"
    */

    vector<int> table(lenX);
    int lastPrefixPosition = lenX;

    for(int i = lenX - 1; i >= 0; i--){
        if(isPrefix(X, lenX, i+1))
            lastPrefixPosition = i + 1;

        table[lenX - 1 - i] = lastPrefixPosition - i + lenX - 1;
    }

    // Вычисление функции по определению
    for(int i = 0; i < lenX - 2; ++i){
        int slen = suffixLength(X, lenX, i);
        table[slen] = lenX - 1 - i + slen;
    }

    return table;
}

int BMSearch(string T, string P){
    int len_T = T.size();
    int len_P = P.size();

    if(len_P > len_T || len_P == 0 || len_T == 0){
        return -1;
    }

    auto bad_char = prefixBadChar(P, len_P);
    auto good_suff = prefixGoodSuffix(P, len_P);

    //Поиск подстроки
    for(int i = len_P - 1; i <= len_T - 1; ++i)
    {
        int j = len_P - 1;
        while(P[j] == T[i])
        {
            if(j == 0)
            {
                return i;
            }
            --i;
            --j;
        }
        i += std::max(good_suff[len_P - 1 - j], bad_char[(char)T[i]]);
    }

    return -1;

}



int boyer_moore(char* sstr, char* pattern)
{
    char* inits = sstr;
    char* initp = pattern;

    int spatt = strlen(pattern);
    while(*pattern != '\0') pattern++;

    // this algorithm tested for printable ASCII characters
    // from ASCII, 65-90 and 97-122
    int* jump_table=(int*) calloc(128, sizeof(int));
    int count=0;

    while(pattern != initp) {
        pattern--;
        jump_table[*pattern]=count;
        count++;
    }

    char* stmp=0;
    char* iter=0;
    int shift=0;
    int bad_count=0;
    int bcount=0;
    while(*sstr != '\0')
    {
        bcount=0;
        bad_count=spatt;
        stmp = sstr+ (spatt-1);
        iter = pattern + (spatt-1);
        while(*stmp == *iter) {
            bad_count--;
            bcount++;
            stmp--;
            iter--;
            if(bcount==spatt)
                return sstr-inits;
        }

        //jump table
        if(jump_table[*stmp] == 0) {
            // the character not found in pattern
            shift=bad_count;
        } else {
            shift=jump_table[*stmp];
            (shift - bcount < 1)?shift = 1: shift = shift-bcount;
        }
        sstr += shift;
    }
    //not found
    return -1;
}
#endif // BOYERMOORE_H

