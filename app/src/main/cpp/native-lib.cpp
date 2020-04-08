#include "native-lib.h"
#include "CommonTools.h"


#ifdef __cplusplus
extern "C"
#endif
Http_Get(jstring ,NativeHttpGet,jstring url_) {
    string hello = "";
    const char * url = env->GetStringUTFChars(url_,0);
    jstring params =env->NewStringUTF(hello.c_str());
    jobject_global = env->NewGlobalRef(instance);
    Message *message = new Message();
    message->time= 10;
    message->type=1;
    message->url= const_cast<char *>(url);
    message->callBackInThread=&SendMsgToJava;
    //param1 子线程 param2 基本没有标识 3params 回调方法void* method（void* args）  4参数 void*
    pthread_create(&pid, 0, callCreateThread, message);
    return params;
}

#ifdef __cplusplus
extern "C"
#endif
Http_Post(jstring ,NativeHttpPost,jstring url_,jstring reqJson_) {
    string hello = "";
    const char * url = env->GetStringUTFChars(url_,0);
    const char * reqJson = env->GetStringUTFChars(reqJson_,0);
    jstring back =env->NewStringUTF(hello.c_str());
    jobject_global = env->NewGlobalRef(instance);
    Message *message = new Message();
    message->time= 10;
    message->type=2;
    message->url= const_cast<char *>(url);
    message->reqJson = const_cast<char*>(reqJson);
    message->callBackInThread=&SendMsgToJava;
    //param1 子线程 param2 基本没有标识 3params 回调方法void* method（void* args）  4参数 void*
    pthread_create(&pid, 0, callCreateThread, message);
    return back;
}

#ifdef __cplusplus
extern "C"
#endif
Http_DownLoad(jstring ,NativeHttpDownLoad,jstring url_,jstring savePath_) {
    string hello = "";
    const char * url = env->GetStringUTFChars(url_,0);
    const char * savePath = env->GetStringUTFChars(savePath_,0);
    jstring params =env->NewStringUTF(hello.c_str());
    jobject_global = env->NewGlobalRef(instance);
    Message *message = new Message();
    message->time= 10;
    message->type=3;
    message->url= const_cast<char *>(url);
    message->savePath=const_cast<char *>(savePath);
    message->callBackInThread=&SendMsgToJava;
//    param1 子线程 param2 基本没有标识 3params 回调方法void* method（void* args）  4参数 void*
    pthread_create(&pid, 0, callCreateThread, message);

    return params;
}

/***************与Java层对应**************/
//当调用System.loadLibrary时，会回调这个方法 ，此时获取全局的Javavm
jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    javaVM = vm;
    return JNI_VERSION_1_6;
}


//回调信息给java
void* SendMsgToJava(int type, const char *result) {
    JNIEnv *env;
    javaVM->AttachCurrentThread(&env, NULL);
    jclass classCallback = env->GetObjectClass(jobject_global);
    jmethodID methodErr = env->GetMethodID(classCallback, "callBackFromNDK", "(ILjava/lang/String;)V");
    env->CallVoidMethod(jobject_global, methodErr, type,env->NewStringUTF(result));
    javaVM->DetachCurrentThread();
    return 0;
}

//回调下载进度给Java
void* SendProToJava(double progress ) {
    JNIEnv *env;
    javaVM->AttachCurrentThread(&env, NULL);
    jclass classCallback = env->GetObjectClass(jobject_global);
    jmethodID methodErr = env->GetMethodID(classCallback, "callProgressFromNDK", "(D)V");
    env->CallVoidMethod(jobject_global, methodErr, progress);
    javaVM->DetachCurrentThread();
    return 0;
}

void* callCreateThread( void* args ){
    CommonTools * commonTools ;
    Message* message =(Message*)args;

    LOGI("超时时间：%d",message->time);
    LOGI("请求地址：%s",message->url);
    LOGI("请求类型：%d",message->type);
    LOGI("请求参数：%s",message->reqJson);
    LOGI("保存路径：%s",message->savePath);
    string strResponse ;
    int ret;
    switch (message->type){
        case 1:
            ret=  commonTools->HttpGet( message->url, strResponse, message->time);
            LOGI("GET请求结果：%s,返回的值是：%d",strResponse.c_str(),ret);
            message->callBackInThread(message->type,strResponse.c_str());
            break;
        case 2:
            ret= commonTools->HttpPost( message->url, message->reqJson,strResponse, message->time);
            LOGI("POST请求结果：%s,返回的值是：%d",strResponse.c_str(),ret);
            message->callBackInThread(message->type,strResponse.c_str());
            break;
        case 3:
            ret= commonTools->download_file(message->url, message->savePath,SendProToJava);
            LOGI("DOWN请求结果：%s,返回的值是：%d",strResponse.c_str(),ret);
            message->callBackInThread(message->type,"ret:"+ret);
            break;
    }



    int a = 10;
    int i = 0;
    for (i;i<a;i++){
        LOGI("this is %d",i);
        sleep(1);
    }
    return 0;
}