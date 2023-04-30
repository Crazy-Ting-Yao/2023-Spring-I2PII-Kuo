#include<string>
#include<iostream>
#include<sstream>
#include<cctype>
int main(){
    std::string data;
    while(getline(std::cin,data)){
        std::string head, current;
        std::stringstream ss;
        ss << data;
        ss >> head;
        int id=0;
        int flag=1;
        while(ss>>current){
            if(tolower(head[++id])!=tolower(current[0])){
                flag=0;
                break;
            }
        }
        if(flag&&(id+1)==head.length()) std::cout<<"o'_'o"<<std::endl;
        else std::cout<<"QQ"<<std::endl;
        ss.str("");
        ss.clear();
    }
}