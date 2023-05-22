#include <iterator>
using namespace std;

template<typename Iterator>
Iterator k_unique(Iterator begin, Iterator end, int k){
    if(begin==end) return end;
    int count = 0;
    Iterator retend = begin;
    while((++begin)!=end){
        if(*begin!=*retend){
            *(++retend) = *begin;
            count = 0;
        }
        else if(++count < k){
            *(++retend) = *begin;
        }
    }
    return ++retend;
}