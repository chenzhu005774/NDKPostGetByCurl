/*
 *  CommonTools.h
 *  Created on: 2020年4月6日
 *  Author: chenzhu
 */

#ifndef MY_APPLICATION_COMMONTOOLS_H
#define MY_APPLICATION_COMMONTOOLS_H

#include <android/log.h>
#include "zlib.h"
#include <vector>
#include <unistd.h>
#include <memory.h>
#include <curl.h>
#include <unistd.h>
#include <string>
using namespace std;

#define LOG_TAG ("chenzhu")
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO   , LOG_TAG, __VA_ARGS__))
typedef void*  CallProgress(double progress );

//静态变量是属于类的，所以可以通过class::variable访问，
// 非静态变量是属于对象的，需要new，new就需要实现析构函数和构造函数

class CommonTools{
public:
    CommonTools();
    ~CommonTools();
public:
    static CallProgress*  callProgress  ;//这里只是声明，并没有定义,需要再cpp文件中定义分配

    static size_t receive_data(void *contents, size_t size, size_t nmemb, void *stream);
    // HTTP 下载文件的回掉函数
    static size_t writedata2file(void *ptr, size_t size, size_t nmemb, FILE *stream);
    // 文件下载接口
     int download_file(const char* url, const char outfilename[FILENAME_MAX],CallProgress* callprogress);
    // http get 请求
    static CURLcode HttpGet(const std::string & strUrl, std::string & strResponse,int nTimeout);
    // htpp post 请求
    static CURLcode HttpPost(const std::string & strUrl, std::string szJson,std::string & strResponse,int nTimeout);

    static int my_progress_func(char *progress_data, double t, /* dltotal */  double d, /* dlnow */ double ultotal, double ulnow);


};


#endif //MY_APPLICATION_COMMONTOOLS_H
