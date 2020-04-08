#include <jni.h>
#include <string>
#include <pthread.h>
#include <android/log.h>


#define TAG "chenzhuJNI"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)

#define Http_Get(RETURNTYPE ,FUNCTIONNAME ,...) JNIEXPORT RETURNTYPE JNICALL \
Java_com_chenzhu_myapplication_NativeMethods_##FUNCTIONNAME\
(JNIEnv* env,  jobject instance /* this */,##__VA_ARGS__)\

#define Http_Post(RETURNTYPE ,FUNCTIONNAME ,...) JNIEXPORT RETURNTYPE JNICALL \
Java_com_chenzhu_myapplication_NativeMethods_##FUNCTIONNAME\
(JNIEnv* env,  jobject instance /* this */,##__VA_ARGS__)\

#define Http_DownLoad(RETURNTYPE ,FUNCTIONNAME ,...) JNIEXPORT RETURNTYPE JNICALL \
Java_com_chenzhu_myapplication_NativeMethods_##FUNCTIONNAME\
(JNIEnv* env,  jobject instance /* this */,##__VA_ARGS__)\

pthread_t pid;
//调用类
jobject jobject_global; // 全局的 再子线程中回调使用 与Java的那个类持有
JavaVM* javaVM; // 子线程中Jnienv 要单独获取

typedef void*  CallBackInThread(int type, const char *result);
typedef struct Message{
    int time;
    int type;
    char* url;
    char* reqJson;
    char* savePath;
    CallBackInThread* callBackInThread;
} Message;

//回调请求信息给java
void* SendMsgToJava(int type, const char *result) ;
//回调下载进度给java
void* SendProToJava(double progress );
//回调再创子建线程的时候
void* callCreateThread( void* args );
