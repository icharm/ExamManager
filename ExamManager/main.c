//
//  main.c
//  ExamManager
//
//  Created by ICHARM on 16/9/2.
//  Copyright © 2016年 ICHARM. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cJSON.h"
//考生信息
#define STU_FILE "/Users/ZH96/Desktop/ExamManager-master/ExamManager/students.bin"
//试题信息
#define QUE_FILE "/Users/ZH96/Desktop/ExamManager-master/ExamManager/questions.bin"
//考试成绩信息
#define EXAM_FILE "/Users/ZH96/Desktop/ExamManager-master/ExamManager/examinfo.bin"

//void addStudent();




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

    f=fopen(filename,"wb");
    if(!f){
        printf("打开文件错误！\n\n");
        exit(0);
    }
    len=strlen(json);
    fwrite(json,len,1,f);
    
    fclose(f);
    //free(filename);
    free(json);
}

//读取文件
cJSON *readfile(char *filename)
{
    FILE *f;long len;char *data;
    cJSON *json;
    
    f=fopen(filename,"rb");
    fseek(f,0,SEEK_END);
    len=ftell(f);
    fseek(f,0,SEEK_SET);
    data=(char*)malloc(len+1);fread(data,1,len,f);fclose(f);
    //doit(data);
    //printf("%s\n",data);
    json = cJSON_Parse(data);
    free(data);
    return json;
    
}

/*******************考生管理****************/
//添加考生
void addStudent(){
    char *name;
    char *stu_arr[100];
    name = (char *)malloc(100);
    cJSON * root, *stu_json;
    char *out;

    printf("请输入考生姓名:\n");
    scanf("%s",name);
    
    //读取考生信息
    stu_json = readfile(STU_FILE);
    cJSON *stu_child;
    if(stu_json->child){
        stu_child = stu_json->child;
    }
    int stu_count = -1;
    do{
        stu_count++;
        stu_arr[stu_count] = stu_child->valuestring;
        stu_child = stu_child->next;
    }while(stu_child);
    stu_count++;
    stu_arr[stu_count] = name;
    root = cJSON_CreateArray();
    for(int j=0; j<=stu_count; j++){
        cJSON_AddItemToArray(root, cJSON_CreateString(stu_arr[j]));
    }
    out = cJSON_Print(root);
    writefile(STU_FILE, out);
    cJSON_Delete(root);
    cJSON_Delete(stu_child);
    cJSON_Delete(stu_json);
    printf("添加成功！\n");
    free(name);
    
}

//修改考生
void modifyStudent()
{
    char *name;
    name = (char *)malloc(100);
    printf("请输入需要修改的考生名：\n");
    scanf("%s", name);
    
    cJSON * stu_json;
    cJSON * stu_child;
    cJSON * root;
    char * out;
    char * stu_arr[100];
    //读取考生信息
    stu_json = readfile(STU_FILE);
    if(stu_json->child){
        stu_child = stu_json->child;
    }
    int stu_count = -1;
    do{
        stu_count++;
        stu_arr[stu_count] = stu_child->valuestring;
        stu_child = stu_child->next;
    }while(stu_child);
    int flag = 1;
    int j;
    for(j =0; j<=stu_count; j++){
         flag = strcmp(stu_arr[j], name);
        if(flag == 0){
            break;
        }
    }
    if(flag != 0){
        printf("未找到该用户!\n");
        cJSON_Delete(stu_child);
        cJSON_Delete(stu_json);
        free(name);
        exit(0);
    }else{
        char * name_new;
        name_new = (char *)malloc(100);
        printf("请输入修改后的用户名:\n");
        scanf("%s", name_new);
        
        stu_arr[j] = name_new;
        root = cJSON_CreateArray();
        for(int j=0; j<=stu_count; j++){
            cJSON_AddItemToArray(root, cJSON_CreateString(stu_arr[j]));
        }
        out = cJSON_Print(root);
        writefile(STU_FILE, out);
        free(name_new);
        printf("修改成功！");
    }
    
    cJSON_Delete(root);
    cJSON_Delete(stu_child);
    cJSON_Delete(stu_json);
    free(name);
}

//删除考生
void deleteStudent(){
    
    char *name;
    name = (char *)malloc(100);
    printf("请输入需要删除的考生名：\n");
    scanf("%s", name);
    
    cJSON * stu_json;
    cJSON * stu_child;
    cJSON * root;
    char * out;
    char * stu_arr[100];
    //读取考生信息
    stu_json = readfile(STU_FILE);
    if(stu_json->child){
        stu_child = stu_json->child;
    }
    int stu_count = -1;
    do{
        stu_count++;
        stu_arr[stu_count] = stu_child->valuestring;
        stu_child = stu_child->next;
    }while(stu_child);
    int flag = 1;
    int j;
    for(j =0; j<=stu_count; j++){
        flag = strcmp(stu_arr[j], name);
        if(flag == 0){
            break;
        }
    }
    if(flag != 0){
        printf("未找到该用户!\n");
        cJSON_Delete(stu_child);
        cJSON_Delete(stu_json);
        free(name);
        exit(0);
    }else{
        for(;j<stu_count;j++){
            stu_arr[j] = stu_arr[j+1];
        }
        root = cJSON_CreateArray();
        for(int j=0; j<stu_count; j++){
            cJSON_AddItemToArray(root, cJSON_CreateString(stu_arr[j]));
        }
        out = cJSON_Print(root);
        writefile(STU_FILE, out);
        printf("删除成功！\n");
    }
    
    cJSON_Delete(root);
    cJSON_Delete(stu_child);
    cJSON_Delete(stu_json);
    free(name);

}
/***************试题管理********************/
//增加试题
void addQuestion(){
    char *question_h;
    question_h = (char *)malloc(500);
    char *question_b;
    question_b = (char *)malloc(500);
    char *right;
    right = (char *)malloc(10);
    
    cJSON * root;
    char *out;
    fflush(stdin);
    getchar();
    printf("请输入题干:\n");
    gets(question_h);
    printf("请输入选项:\n");
    gets(question_b);
    printf("请输入正确答案:\n");
    gets(right);
    
    cJSON * ques, * ques_child;
    char *ques_arr[300][3];
    //读取试题信息
    ques = readfile(QUE_FILE);
    
    if(ques->child){
       ques_child = ques->child;
    }
    int ques_count = -1;
    do{
        ques_count++;
        cJSON * ques_child_c;
        //if(!ques_child->next){
            ques_child_c = ques_child->child;
        //}
        int q_count = -1;
        do{
            q_count++;
            ques_arr[ques_count][q_count] = ques_child_c->valuestring;
            ques_child_c = ques_child_c->next;
        }while(ques_child_c);
        cJSON_Delete(ques_child_c);
        ques_child = ques_child->next;
    }while(ques_child);
    
    ques_count++;
    ques_arr[ques_count][0] = question_h;
    ques_arr[ques_count][1] = question_b;
    ques_arr[ques_count][2] = right;
    
    
    root = cJSON_CreateArray();
    cJSON *que[ques_count];
    for(int i=0; i<=ques_count; i++){
        que[i] = cJSON_CreateArray();
        cJSON_AddItemToArray(que[i], cJSON_CreateString(ques_arr[i][0]));
        cJSON_AddItemToArray(que[i], cJSON_CreateString(ques_arr[i][1]));
        cJSON_AddItemToArray(que[i], cJSON_CreateString(ques_arr[i][2]));
        cJSON_AddItemToArray(root, que[i]);
    }
    
    out = cJSON_Print(root);
    writefile(QUE_FILE, out);
    
    printf("添加成功！\n");
    cJSON_Delete(ques_child);
    cJSON_Delete(ques);
    cJSON_Delete(root);
    free(question_b);
    free(question_h);
    free(right);
    main();
}

//修改试题
void modifyQuestion(){
    int id;
    char *question_h;
    question_h = (char *)malloc(500);
    char *question_b;
    question_b = (char *)malloc(500);
    char *right;
    right = (char *)malloc(10);
    
    printf("请输入想要修改的试题序号:\n");
    scanf("%d",&id);
    fflush(stdin);
    getchar();
    printf("请输入题干:\n");
    gets(question_h);
    printf("请输入选项:\n");
    gets(question_b);
    printf("请输入正确答案:\n");
    gets(right);
    
    
    cJSON * ques;
    cJSON * ques_child;
    char *ques_arr[300][3];
    //读取试题信息
    ques = readfile(QUE_FILE);
    
    if(ques->child){
        ques_child = ques->child;
    }
    int ques_count = -1;
    do{
        ques_count++;
        cJSON * ques_child_c;
        //if(!ques_child->next){
        ques_child_c = ques_child->child;
        //}
        int q_count = -1;
        do{
            q_count++;
            ques_arr[ques_count][q_count] = ques_child_c->valuestring;
            ques_child_c = ques_child_c->next;
        }while(ques_child_c);
        cJSON_Delete(ques_child_c);
        ques_child = ques_child->next;
    }while(ques_child);
    
    
        ques_arr[id][0] = question_h;
        ques_arr[id][1] = question_b;
        ques_arr[id][2] = right;
   
    cJSON *root;
    char *out;
    root = cJSON_CreateArray();
    cJSON *que[ques_count];
    for(int i=0; i<=ques_count; i++){
        que[i] = cJSON_CreateArray();
        cJSON_AddItemToArray(que[i], cJSON_CreateString(ques_arr[i][0]));
        cJSON_AddItemToArray(que[i], cJSON_CreateString(ques_arr[i][1]));
        cJSON_AddItemToArray(que[i], cJSON_CreateString(ques_arr[i][2]));
        cJSON_AddItemToArray(root, que[i]);
    }
    
    out = cJSON_Print(root);
    writefile(QUE_FILE, out);
    
    printf("修改成功！\n");
    
    cJSON_Delete(ques);
    cJSON_Delete(ques_child);
    cJSON_Delete(root);
    main();
}

//删除试题
void deleteQuestion(){
    int id;
    printf("请输入想要删除的试题序号:\n");
    scanf("%d",&id);
    
    cJSON * ques;
    cJSON * ques_child;
    char *ques_arr[300][3];
    //读取试题信息
    ques = readfile(QUE_FILE);
    
    if(ques->child){
        ques_child = ques->child;
    }
    int ques_count = -1;
    do{
        ques_count++;
        cJSON * ques_child_c;
        //if(!ques_child->next){
        ques_child_c = ques_child->child;
        //}
        int q_count = -1;
        do{
            q_count++;
            ques_arr[ques_count][q_count] = ques_child_c->valuestring;
            ques_child_c = ques_child_c->next;
        }while(ques_child_c);
        cJSON_Delete(ques_child_c);
        ques_child = ques_child->next;
    }while(ques_child);
    
    for(int i=id; i<=ques_count;i++){
        ques_arr[i][0] = ques_arr[i+1][0];
        ques_arr[i][1] = ques_arr[i+1][1];
        ques_arr[i][2] = ques_arr[i+1][2];
    }
    cJSON *root;
    char *out;
    root = cJSON_CreateArray();
    cJSON *que[ques_count-1];
    for(int i=0; i<=ques_count-1; i++){
        que[i] = cJSON_CreateArray();
        cJSON_AddItemToArray(que[i], cJSON_CreateString(ques_arr[i][0]));
        cJSON_AddItemToArray(que[i], cJSON_CreateString(ques_arr[i][1]));
        cJSON_AddItemToArray(que[i], cJSON_CreateString(ques_arr[i][2]));
        cJSON_AddItemToArray(root, que[i]);
    }
    
    out = cJSON_Print(root);
    writefile(QUE_FILE, out);
    
    printf("删除成功！\n");

    cJSON_Delete(ques);
    cJSON_Delete(ques_child);
    cJSON_Delete(root);
    main();

}


void studentManager(){
    int flag = 0;
    printf("^v^v^v^v^v^v^考生信息如下^v^v^v^v^v^v^\n");
    
    cJSON * stu_json;
    cJSON * stu_child;
    //读取考生信息
    stu_json = readfile(STU_FILE);
    if(stu_json->child){
        stu_child = stu_json->child;
    }
    do{
        printf("%s\n", stu_child->valuestring);
        stu_child = stu_child->next;
    }while(stu_child);
    cJSON_Delete(stu_json);
    cJSON_Delete(stu_child);
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
            main();
            break;
        default:
            printf("错误序号重新输入\n");
            goto input_s;
            break;
    }
    
}

void ExamManager(){
    
    
    int flag = 0;
    printf("^v^v^v^v^v^v^试题信息如下^v^v^v^v^v^v^\n");
    
    cJSON * ques;
    cJSON * ques_child;
    char *ques_arr[300][3];
    //读取试题信息
    ques = readfile(QUE_FILE);
    
    if(ques->child){
        ques_child = ques->child;
    }
    int ques_count = -1;
    do{
        ques_count++;
        cJSON * ques_child_c;
        //if(!ques_child->next){
        ques_child_c = ques_child->child;
        //}
        int q_count = -1;
        do{
            q_count++;
            ques_arr[ques_count][q_count] = ques_child_c->valuestring;
            ques_child_c = ques_child_c->next;
        }while(ques_child_c);
        cJSON_Delete(ques_child_c);
        ques_child = ques_child->next;
    }while(ques_child);
    
    for(int i=0; i<=ques_count;i++){
        printf("%d. %s\n",i,ques_arr[i][0]);
        printf("\t%s\t正确答案:%s\n",ques_arr[i][1],ques_arr[i][2]);
    }
    cJSON_Delete(ques);
    cJSON_Delete(ques_child);
    printf("^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^\n");
    
    printf("请输入序号：\n");
    printf("1. 增加考题\n");
    printf("2. 修改考题\n");
    printf("3. 删除考题\n\n");
    printf("4. 返回上一层菜单\n");
    
    
input_s:scanf("%d",&flag);
    
    switch (flag) {
        case 1:
            addQuestion();
            break;
        case 2:
            modifyQuestion();
            break;
        case 3:
            deleteQuestion();
            break;
        case 4:
            main();
            break;
        default:
            printf("错误序号重新输入\n");
            goto input_s;
            break;
    }

}
//参加考试
void joinExam(){
    char name[100];
    printf("请输入考生名:\n");
    scanf("%s",name);
    cJSON *stu_json, *stu_child;
    
    char *stu_arr[100];
    //读取考生信息
    stu_json = readfile(STU_FILE);
    if(stu_json->child){
        stu_child = stu_json->child;
    }
    int stu_count = -1;
    do{
        stu_count++;
        stu_arr[stu_count] = stu_child->valuestring;
        stu_child = stu_child->next;
    }while(stu_child);
    int flag = 1;
    int j;
    for(j =0; j<=stu_count; j++){
        flag = strcmp(stu_arr[j], name);
        if(flag == 0){
            break;
        }
    }
    if(flag != 0){
        printf("未找到该考生!\n");
        cJSON_Delete(stu_child);
        cJSON_Delete(stu_json);
        free(name);
        exit(0);
    }else{
        printf("现在开始答题\n");
        cJSON * ques;
        cJSON * ques_child;
        char *ques_arr[300][3];
        //读取试题信息
        ques = readfile(QUE_FILE);
        
        if(ques->child){
            ques_child = ques->child;
        }
        int ques_count = -1;
        do{
            ques_count++;
            cJSON * ques_child_c;
            //if(!ques_child->next){
            ques_child_c = ques_child->child;
            //}
            int q_count = -1;
            do{
                q_count++;
                ques_arr[ques_count][q_count] = ques_child_c->valuestring;
                ques_child_c = ques_child_c->next;
            }while(ques_child_c);
            cJSON_Delete(ques_child_c);
            ques_child = ques_child->next;
        }while(ques_child);
        
        //生成随机数
        int count = 0; //计数，共5题
        int base[5];
        srand((unsigned)time(NULL)); //用当前系统时间设置种子
        for(; count<5; count++){
            base[count] = rand()%13;
            int tmp = base[count];
            printf("%d. %s\n",count,ques_arr[tmp][0]);
            printf("%s\n\n", ques_arr[tmp][1]);
        }
        
        char answer[100];
        printf("请依次输入答案，空格隔开\n");
        getchar();
        gets(answer);
        char *token = strtok(answer, " ");
        char *answer_arr[10];
        int i = 0;
        while(token){
            answer_arr[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        //验证答案
        int score = 0;
        for(int i=0; i<5; i++){
            int j = base[i];
            if(!strcmp(answer_arr[i],ques_arr[j][2])){
                score += 20;
            }
            //puts(answer_arr[i]);
        }
        
        printf("考试结束，正确率：%d\n",score);
        
        //读取考试成绩数据
        cJSON *scoreData;
        char * sc_arr[500][2];
        scoreData = readfile(EXAM_FILE);
        if(scoreData->child){
            scoreData = scoreData->child;
        }
        int sc_count = -1;
        do{
            sc_count++;
            cJSON * sc_child_c;
            //if(!ques_child->next){
            sc_child_c = scoreData->child;
            //}
            int q_count = -1;
            do{
                q_count++;
                sc_arr[sc_count][q_count] = sc_child_c->valuestring;
                sc_child_c = sc_child_c->next;
            }while(sc_child_c);
            cJSON_Delete(sc_child_c);
            scoreData = scoreData->next;
        }while(scoreData);
        
        char score_s[5];
        sprintf(score_s, "%d", score);
        sc_count++;
        sc_arr[sc_count][0] = name;
        sc_arr[sc_count][1] = score_s;
        
        
        cJSON *root, *info[500];
        char * out;
        root = cJSON_CreateArray();
        for(int i=0; i<=sc_count; i++){
            info[i] = cJSON_CreateArray();
            cJSON_AddItemToArray(info[i], cJSON_CreateString(sc_arr[i][0]));
            cJSON_AddItemToArray(info[i], cJSON_CreateString(sc_arr[i][1]));
            cJSON_AddItemToArray(root, info[i]);
        }
        
        out = cJSON_Print(root);
        writefile(EXAM_FILE, out);
        cJSON_Delete(scoreData);
        cJSON_Delete(root);
        cJSON_Delete(ques);
        cJSON_Delete(ques_child);
        
    }
    
    
}

void fetchScore(){
    char name[100];
    printf("请输入考生姓名:\n");
    scanf("%s", name);
    //读取考试成绩数据
    cJSON *scoreData;
    char * sc_arr[500][2];
    scoreData = readfile(EXAM_FILE);
    if(scoreData->child){
        scoreData = scoreData->child;
    }
    int sc_count = -1;
    do{
        sc_count++;
        cJSON * sc_child_c;
        //if(!ques_child->next){
        sc_child_c = scoreData->child;
        //}
        int q_count = -1;
        do{
            q_count++;
            sc_arr[sc_count][q_count] = sc_child_c->valuestring;
            sc_child_c = sc_child_c->next;
        }while(sc_child_c);
        cJSON_Delete(sc_child_c);
        scoreData = scoreData->next;
    }while(scoreData);
    
    int flag=1;
    printf("\n");
    for(int i=0;i<=sc_count;i++){
        if(!strcmp(sc_arr[i][0],name)){
            flag = 0;
            printf("%s %s\n",sc_arr[i][0],sc_arr[i][1]);
        }
    }
    if(flag == 1){
        printf("未找到考生数据！\n");
    }
    
}

int main() {
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
