#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <netinet/ip.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <sstream>

//android:networkSecurityConfig="@xml/network_security_config"

extern "C" JNIEXPORT jstring JNICALL
Java_com_tango_jnitest2_MainActivity_stringFromJNI2(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello2  ~~~~~ native-lib.cpp";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_tango_jnitest2_MainActivity_addValue
        (JNIEnv *env, jobject thiz, jint a,jint b)
{
    return a+b;
}



char net_device_name[128]={"wlan0"};//这个要根据手机的实际网络设备名修改掉
char rx_socket_buff[2048];
int timeout = 100;


static void sleepMs(unsigned int micro_second)
{
    struct timeval  t_timeval;
    
    t_timeval.tv_sec = 0;
    t_timeval.tv_usec = 1000*micro_second;
    
    select( 0, NULL, NULL, NULL, &t_timeval );
}


static int send_cnt = 0;
static int send_len = 0;
int sent_socket()
{
    int u_sockfd, len;
    struct sockaddr_ll s_sockaddr;
    struct ifreq ifstruct;
    int tx_cnt = 0;

    unsigned char tx_buff[]={0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x0b,0x0a,0x0c,0x0d,0x08,0x00,0x45,0x00,0x00,0x28,0x73,0x97,0x40,0x00,0x80,0x06,0x00,0x00,0xc0,0xa8,0x01,0x55,0xC0,0xA8,0x01,0x11,0x07,0xd0,0x03,0xe8,0x0e,0xf8,0xee,0xf2,0xc7,0xfb,0x4a,0xdf,0x50,0x10,0x00,0x20,0xfe,0x1c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0x11,0x22,0x33,0x44,0x55,0x66,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
    
    u_sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    memset(&s_sockaddr,0,sizeof(s_sockaddr));
    strcpy(ifstruct.ifr_name, net_device_name);
    s_sockaddr.sll_ifindex=ifstruct.ifr_ifindex;
    ioctl(u_sockfd, SIOCGIFINDEX, &ifstruct);
    strcpy(ifstruct.ifr_name, net_device_name);
    s_sockaddr.sll_ifindex=ifstruct.ifr_ifindex;

    ioctl(u_sockfd, SIOCGIFINDEX, &ifstruct);
    
    int recv_len = 0;
    
    while(tx_cnt < 100)
    {
        tx_buff[0x38] = tx_cnt&0xff;
        tx_buff[0x39] = (tx_cnt>>8)&0xff;
        tx_buff[0x3A] = (tx_cnt>>16)&0xff;
        tx_buff[0x3B] = (tx_cnt>>24)&0xff;
        
        send_cnt++;
        
        len = sendto(u_sockfd, &tx_buff, sizeof(tx_buff), 0, (struct sockaddr*)&s_sockaddr, sizeof(s_sockaddr));
        
        send_len = send_len + len;
        
        //printf("Tx Len=%d \r",len);
        int curr_recv_len = recv(u_sockfd, &rx_socket_buff, sizeof(rx_socket_buff), 0);
        
        if (curr_recv_len > 0)
        recv_len = recv_len + curr_recv_len;
        
        if(-1 == len)
        {
            perror("sendto");
        }
        
        if (tx_cnt%100 == 0)
        {
            printf("Tx Len=%d \n\n",len);
        }
        
        tx_cnt++;
        sleepMs(10);
    }
    
    return recv_len;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_tango_jnitest2_MainActivity_socketSend
        (JNIEnv *env, jobject thiz)
{
		sent_socket();
    return 0;
}

int add_fun(int a,int b)
{
    return a+b;
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_tango_jnitest2_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
static int cnt =0;
		cnt++;    
    int ret = sent_socket();
    std::string hello = "Hello3  from C++  TxCnt:"+ std::to_string(send_cnt)+ "\n RxLen:" +std::to_string(ret)+"\n TxLen:" +std::to_string(send_len);
    int a = rand()%1000;
    int b = rand()%1000;
    hello = hello + "\n add_fun  "+std::to_string(a) + " + "+ std::to_string(b) + " = "  +std::to_string(add_fun(a,b));
    return env->NewStringUTF(hello.c_str());
}

