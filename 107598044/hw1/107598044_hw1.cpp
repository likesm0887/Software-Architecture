#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <iostream>
#include <string.h>
#include <windows.h>

using namespace std;

int check_class_exist = 0;
sqlite3 * pDB = NULL;

//增加課程
void AddClass(const string& sName, const string& sDescription, const string& sTarget, const string& sPrice, const string& sAttention, const string& sNote);
//刪除課程��
void DeleteClass(const string& sName);
//編輯課程��
void ModifyClassName(const string& sName, const string& sNewName);
void ModifyClassDescription(const string& sName, const string& sNewDescription);
void ModifyClassTarget(const string& sName, const string& sNewTarget);
void ModifyClassPrice(const string& sName, const string& sNewPrice);
void ModifyClassAttention(const string& sName, const string& sNewAttention);
void ModifyClassNote(const string& sName, const string& sNewNote);
//尋找課程
void SelectClass();
void SelectClassOne(const string& sName);
void SelectClassName();
void SelectCheckClassName(const string& sName);

int main(){
    system("color F0");
    int input, modify;
    char aa[50], name[100], description[100], target[100], price[100], attention[100], note[100], newname[100], minus_one[5]="-1", empty_class[5]="";
    int nRes = sqlite3_open("./test.db", &pDB);
    if (nRes != SQLITE_OK){
        cout<<"Open database fail: "<<sqlite3_errmsg(pDB);
        return 0;
    }
    //system("color f0");
    while (1){
        printf("1. 列出所有課程\n");
        printf("2. 新增課程\n");
        printf("3. 刪除課程\n");
        printf("4. 編輯課程\n");
        printf("5. 離開\n");
        //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), );
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
        printf("請輸入上面所對應的數字: ");
        scanf("%d", &input);
        gets(aa);
        system("cls");
        printf("請輸入上面所對應的數字: %d\n\n", input);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        switch (input){
            case 1:
                printf("所有課程如下:\n\n");
                SelectClass();
                break;
            case 2:
                printf("-----新增課程-----\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
                printf("輸入課程名稱: ");
                gets(name);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                SelectCheckClassName(name);
                if (check_class_exist == 1){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
                    printf("已存在相同名稱之課程！\n\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                }
                else if (check_class_exist == 0 && strcmp (name, empty_class) == 0){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
                    printf("課程不得留空！\n\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                }
                else {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
                    printf("輸入課程說明: ");
                    gets(description);
                    printf("輸入課程適合的對象: ");
                    gets(target);
                    printf("輸入課程定價: ");
                    gets(price);
                    printf("輸入課程注意事項: ");
                    gets(attention);
                    printf("輸入課程備註: ");
                    gets(note);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    printf("\n[        課程名稱        ][        課程說明        ][        課程對象        ][        課程定價        ][        注意事項        ][        課程備註        ]\n");
                    printf(" ------------------------  ------------------------  ------------------------  ------------------------  ------------------------  ------------------------ \n");
                    printf("%26s%26s%26s%26s%26s%26s\n", name, description, target, price, attention, note);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
                    printf("\n若確定要新增，請再輸入一次課名，否則輸入-1跳出: ");
                    while(1){
                        gets(newname);
                        if (strcmp (name, newname) == 0){
                            system("cls");
                            AddClass(name, description, target, price, attention, note);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            break;
                        }
                        else if (strcmp (minus_one, newname) == 0){
                            system("cls");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            break;
                        }
                        else{
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
                            printf("輸入錯誤！\n");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
                            printf("若確定要新增，請再輸入一次課名，否則輸入-1跳出: ");
                        }
                    }
                }
                break;
            case 3:
                printf("-----刪除課程-----\n\n");
                SelectClassName();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
                printf("請輸入要刪除的課程: ");
                gets(name);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                SelectCheckClassName(name);
                if (check_class_exist == 0){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
                    printf("課程不存在！\n\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                }
                else if (check_class_exist == 1){
                    SelectClassOne(name);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
                    printf("若確定要刪除，請再輸入一次課名，否則輸入-1跳出: ");
                    while (1){
                        gets(newname);
                        if (strcmp (name, newname) == 0){
                            system("cls");
                            DeleteClass(name);
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            break;
                        }
                        else if (strcmp (minus_one, newname) == 0){
                            system("cls");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                            break;
                        }
                        else{
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
                            printf("輸入錯誤！\n");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
                            printf("若確定要刪除，請再輸入一次課名，否則輸入-1跳出: ");
                        }
                    }
                }

                break;
            case 4:
                printf("-----課程編輯-----\n\n");
                SelectClassName();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
                printf("請輸入欲修改之課程: ");
                gets(name);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                SelectCheckClassName(name);
                if (check_class_exist == 0){
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
                    printf("課程不存在！\n\n");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                }
                else {
                    modify = 0;
                    while(modify!=7){
                        SelectClassOne(name);
                        printf("1. 修改《%s》課程名稱\n", name);
                        printf("2. 修改《%s》課程說明\n", name);
                        printf("3. 修改《%s》課程適合的對象\n", name);
                        printf("4. 修改《%s》課程定價\n", name);
                        printf("5. 修改《%s》課程注意事項\n", name);
                        printf("6. 修改《%s》課程備註\n", name);
                        printf("7. 離開編輯模式\n");
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE);
                        printf("請輸入上面所對應的數字: ");
                        scanf("%d", &modify);
                        gets(aa);
                        switch (modify){
                            case 1:
                                printf("請輸入欲修改之課程新名稱: ");
                                gets(newname);
                                if(strcmp (newname, empty_class) == 0){
                                    system("cls");
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
                                    printf("錯誤，課程不得留空！\n");
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                    break;
                                }
                                system("cls");
                                ModifyClassName(name, newname);
                                strcpy(name, newname);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                break;
                            case 2:
                                printf("請輸入欲修改之課程新說明: ");
                                gets(description);
                                system("cls");
                                ModifyClassDescription(name, description);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                break;
                            case 3:
                                printf("請輸入欲修改之課程新適合的對象: ");
                                gets(target);
                                system("cls");
                                ModifyClassTarget(name, target);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                break;
                            case 4:
                                printf("請輸入欲修改之課程新定價: ");
                                gets(price);
                                system("cls");
                                ModifyClassPrice(name, price);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                break;
                            case 5:
                                printf("請輸入欲修改之課程新注意事項: ");
                                gets(attention);
                                system("cls");
                                ModifyClassAttention(name, attention);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                break;
                            case 6:
                                printf("請輸入欲修改之課程新備註: ");
                                gets(note);
                                system("cls");
                                ModifyClassNote(name, note);
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                break;
                            case 7:
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                break;
                            default:
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
                                printf("輸入錯誤，請重新輸入！\n");
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        }
                    }
                    //printf("-----已離開課程編輯模式-----\n\n");
                    system("cls");
                }
                break;
            case 5:
                return 0;
            default:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
                printf("輸入錯誤，請重新輸入\n\n");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        }

    }

//QUIT:
    //sqlite3_close(pDB);

    return 0;
}

void AddClass(const string& sName, const string& sDescription, const string& sTarget, const string& sPrice, const string& sAttention, const string& sNote){
    string strSql = "";

    strSql += "insert into class(name, description, target, price, attention, note)";
    strSql += "values('";
    strSql += sName;
    strSql += "','";
    strSql += sDescription;
    strSql += "','";
    strSql += sTarget;
    strSql += "',";
    strSql += sPrice;
    strSql += ",'";
    strSql += sAttention;
    strSql += "','";
    strSql += sNote;
    strSql += "');";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB , strSql.c_str() ,0 ,0, &cErrMsg);
    if (nRes != SQLITE_OK){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
        printf("新增課程失敗\: %s\n", cErrMsg);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        //return false;
    }
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("新增《%s》課程成功\\n\n", sName.c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }

    //return true;
}

void DeleteClass(const string& sName){
    string strSql = "";
    strSql += "delete from class where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB , strSql.c_str() ,0 ,0, &cErrMsg);
    if (nRes != SQLITE_OK){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
        printf("刪除課程失敗\: %s\n", cErrMsg);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        //return false;
    }
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("刪除《%s》課程成功\\n\n", sName.c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }

    //return true;
}

void ModifyClassName(const string& sName, const string& sNewName){
    string strSql = "";

    strSql += "update class set name ='";
    strSql += sNewName;
    strSql += "' where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB , strSql.c_str() ,0 ,0, &cErrMsg);
    if (nRes != SQLITE_OK){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
        printf("修改課程名稱失敗\: %s\n\n", cErrMsg);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        //return false;
    }
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("修改《%s》課程名稱成功\: %s\n\n", sName.c_str(), sNewName.c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    //return true;
}

void ModifyClassDescription(const string& sName, const string& sNewDescription){
    string strSql = "";

    strSql += "update class set description ='";
    strSql += sNewDescription;
    strSql += "' where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB , strSql.c_str() ,0 ,0, &cErrMsg);
    if (nRes != SQLITE_OK){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
        printf("修改課程說明失敗\: %s\n\n", cErrMsg);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        //return false;
    }
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("修改《%s》課程說明成功\: %s\n\n", sName.c_str(), sNewDescription.c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    //return true;
}

void ModifyClassTarget(const string& sName, const string& sNewTarget){
    string strSql = "";

    strSql += "update class set target ='";
    strSql += sNewTarget;
    strSql += "' where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB , strSql.c_str() ,0 ,0, &cErrMsg);
    if (nRes != SQLITE_OK){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
        printf("修改課程適用對象失敗\: %s\n\n", cErrMsg);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        //return false;
    }
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("修改《%s》課程適用對象成功\: %s\n\n", sName.c_str(), sNewTarget.c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    //return true;
}

void ModifyClassPrice(const string& sName, const string& sNewPrice){
    string strSql = "";

    strSql += "update class set price =";
    strSql += sNewPrice;
    strSql += " where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB , strSql.c_str() ,0 ,0, &cErrMsg);
    if (nRes != SQLITE_OK){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
        printf("修改課程定價失敗\: %s\n\n", cErrMsg);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        //return false;
    }
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("修改《%s》課程定價成功\: %s\n\n", sName.c_str(), sNewPrice.c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    //return true;
}

void ModifyClassAttention(const string& sName, const string& sNewAttention){
    string strSql = "";

    strSql += "update class set attention ='";
    strSql += sNewAttention;
    strSql += "' where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB , strSql.c_str() ,0 ,0, &cErrMsg);
    if (nRes != SQLITE_OK){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
        printf("修改課程注意事項失敗\: %s\n\n", cErrMsg);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        //return false;
    }
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("修改《%s》課程注意事項成功\: %s\n\n", sName.c_str(), sNewAttention.c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    //return true;
}

void ModifyClassNote(const string& sName, const string& sNewNote){
    string strSql = "";

    strSql += "update class set note ='";
    strSql += sNewNote;
    strSql += "' where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB , strSql.c_str() ,0 ,0, &cErrMsg);
    if (nRes != SQLITE_OK){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED);
        printf("修改課程備註失敗\: %s\n\n", cErrMsg);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        //return false;
    }
    else{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN);
        printf("修改《%s》課程備註成功\: %s\n\n", sName.c_str(), sNewNote.c_str());
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    }
    //return true;
}

static int UserResult(void *NotUsed, int argc, char **argv, char **azColName){
    for(int i = 1 ; i < argc ; i++){
        //cout<<azColName[i]<<" = "<<(argv[i] ? argv[i] : "NULL")<<", ";
        printf("%26s", (argv[i] ? argv[i] : "NULL"));
    }

    printf("\n");

    return 0;
}

void SelectClass(){
    char* cErrMsg;

    printf("\n[        課程名稱        ][        課程說明        ][        課程對象        ][        課程定價        ][        注意事項        ][        課程備註        ]\n");
    printf(" ------------------------  ------------------------  ------------------------  ------------------------  ------------------------  ------------------------ \n");


    int res = sqlite3_exec(pDB, "select * from class;", UserResult , 0 , &cErrMsg);

    if (res != SQLITE_OK){
        cout<<"select fail: "<<cErrMsg<<endl;
        //return false;
    }
    printf("\n");
    //return true;
}

void SelectClassOne(const string& sName){
    char* cErrMsg;
    string strSql = "";
    printf("\n[        課程名稱        ][        課程說明        ][        課程對象        ][        課程定價        ][        注意事項        ][        課程備註        ]\n");
    printf(" ------------------------  ------------------------  ------------------------  ------------------------  ------------------------  ------------------------ \n");
    strSql += "select * from class where name ='";
    strSql += sName;
    strSql += "';";

    int res = sqlite3_exec(pDB, strSql.c_str(), UserResult , 0 , &cErrMsg);

    if (res != SQLITE_OK){
        cout<<"select fail: "<<cErrMsg<<endl;
        //return false;
    }
    printf("\n");
    //return true;
}

static int UserResultName(void *NotUsed, int argc, char **argv, char **azColName){
    for(int i = 0 ; i < argc ; i++){
        //cout<<azColName[i]<<" = "<<(argv[i] ? argv[i] : "NULL")<<", ";
        printf("《%s》", (argv[i] ? argv[i] : "NULL"));
    }
    return 0;
}

void SelectClassName(){
    char* cErrMsg;
    printf("目前的課程有: ");
    int res = sqlite3_exec(pDB, "select name from class;", UserResultName , 0 , &cErrMsg);

    if (res != SQLITE_OK){
        cout<<"select fail: "<<cErrMsg<<endl;
        //return false;
    }
    printf("\n");
    //return true;
}

static int UserResultCheckName(void *data, int argc, char **argv, char **azColName){
    //printf("argc = %d\n", argc);
    //printf("data=%s\n", (const char*)data);
    check_class_exist = 1;
    //if (argc == 0){
    //    printf("找無此課程\n");
    //}
    return 0;
}

void SelectCheckClassName(const string& sName){
    check_class_exist = 0;
    const char* data = "Callback function called";
    string strSql = "";

    strSql += "select name from class where name ='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int res = sqlite3_exec(pDB, strSql.c_str(), UserResultCheckName , (void*)data, &cErrMsg);

    if (res != SQLITE_OK){
        cout<<"select fail: "<<cErrMsg<<endl;
        //return false;
    }
}
