//
//  main.c
//  ExamManager
//
//  Created by ICHARM on 16/9/2.
//  Copyright © 2016年 ICHARM. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
//void addStudent();

//考生信息结构体
struct student {
    const char *name;
    int number;
};


//字符串转json
void doit(char *text)
{
    char *out;cJSON *json;
    
    json=cJSON_Parse(text);
    if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
    else
    {
        out=cJSON_Print(json);
        cJSON_Delete(json);
        printf("%s\n",out);
        free(out);
    }
}


//写入文件
void writefile(char *filename, char * json)
{
    FILE *f;long len;;

    f=fopen(filename,"rb");
    if(!f){
        printf("打开文件错误！\n\n");
        exit(0);
    }
    len=strlen(json);
    fwrite(json,1,len+1,f);
    fclose(f);
    free(json);
    free(filename);
}

//读取文件
void readfile(char *filename)
{
    FILE *f;long len;char *data;
    
    f=fopen(filename,"wb");fseek(f,0,SEEK_END);len=ftell(f);fseek(f,0,SEEK_SET);
    data=(char*)malloc(len+1);fread(data,1,len,f);fclose(f);
    doit(data);
    free(data);
}



void addStudent(){
    char *name;
    name = (char *)malloc(100);
    int number;
    cJSON * root, *info;
    char *out;
    printf("请输入考生编号:\n");
    scanf("%d",&number);
    printf("请输入考生姓名:\n");
    scanf("%s",name);
    
    struct student tmp[0];
    tmp[0].name=name;
    tmp[0].number=number;
    
    root = cJSON_CreateObject();
    info=cJSON_CreateObject();

        cJSON_AddItemToObject(root, tmp[0].name, info);
        cJSON_AddStringToObject(info, "姓名", tmp[0].name);
        cJSON_AddNumberToObject(info, "编号", number);

    out = cJSON_Print(root);
    writefile("/Users/icharm/git/ExamManager/ExamManager/students.strings", out);
    
    
    cJSON_Delete(root);
    printf("%s\n",out);
    free(name);
}

void modifyStudent()
{
    
}

void deleteStudent(){


}


void studentManager(){
    int flag = 0;
    printf("^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^\n");
    printf("请输入序号：\n");
    printf("1. 增加考生信息\n");
    printf("2. 修改考生信息\n");
    printf("3. 删除考生信息\n\n");
    printf("4. 返回上一层菜单\n");
    
    
input_s:scanf("%d",&flag);
    
    switch (flag) {
        case 1:
            addStudent();
            break;
        case 2:
            modifyStudent();
            break;
        case 3:
            deleteStudent();
            break;
        case 4:
            main(NULL,NULL);
            break;
        default:
            printf("错误序号重新输入\n");
            goto input_s;
            break;
    }
    
}

void ExamManager(){

}

void joinExam(){

}

int fetchScore(){

    return 0;
}

int main(int argc, const char * argv[]) {
    int flag = 0;
    printf("^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^\n");
    printf("欢迎使用考生管理系统V1.0\n");
    printf("^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^\n");
    printf("请输入序号：\n");
    printf("1. 考生管理\n");
    printf("2. 试题库管理\n");
    printf("3. 参加考试\n");
    printf("4. 成绩查询\n");

    input:scanf("%d", &flag);
    
    switch (flag) {
        case 1:
            studentManager();
            break;
        case 2:
            ExamManager();
            break;
        case 3:
            joinExam();
            break;
        case 4:
            fetchScore();
            break;
        default:
            printf("错误序号重新输入\n");
            goto input;
            break;
    }
    return 1;
}
