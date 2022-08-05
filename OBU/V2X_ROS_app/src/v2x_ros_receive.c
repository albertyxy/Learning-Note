#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <math.h>
#include <cJSON.h>
#include "v2x_includes.h"


#define MY_RECV_PORT 6801 // port 8866 is used to receive  messages
#define BUFF_LEN 1024
#define WMS_PORT 7201 // WMS listening port 7201
char *SERVERIP = "127.0.0.1"; // local IP
static v2x_bsm_struct s_host_bsm;       
static v2x_bsm_struct s_remote_bsm;     

void send_to_wms(char* tx_buf, int tx_length)
{
    struct sockaddr_in servaddr;
    static int tx_count = 0;
    int cli_sock = -1;
    cli_sock = socket(PF_INET, SOCK_DGRAM, 0);
    // if((cli_sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    // {
    //     ERR_EXIT("socket");
    // }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(WMS_PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVERIP);

    printf("send data to wms:[tx_count: %d length:%d] %s\n",tx_count, tx_length, tx_buf);
    sendto(cli_sock, tx_buf, tx_length, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    tx_count += 1;
    close(cli_sock);

}

int main()
{
    int ret;
    int server_sock = -1;
    struct sockaddr_in server_addr;
    // IPV4 and UDP protocol
    server_sock = socket(AF_INET, SOCK_DGRAM, 0);    
    if(server_sock < 0){
        printf("create socket failed \n");
        return -1;
    }
    memset(&server_addr, 0 ,sizeof server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(MY_RECV_PORT);
    // start listening MY_RECV_PORT
    ret = bind(server_sock, (struct sockaddr*)&server_addr, sizeof server_addr ); 
    if(ret < 0)
    {
        printf("socket bind failed \n");
        return -1;
    }

    //monitor the socket status per 100ms
    fd_set readfds;
    struct timeval timeout = {0,0};
    int rx_count=0;
    int wait_count=0;
    while(1)
    {       
        // select timeout 100ms
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;

        // start monitoring sockets' status
        FD_ZERO(&readfds);
        FD_SET(server_sock, &readfds);
        int maxfd = server_sock + 1;
        ret = select(maxfd, &readfds, NULL, NULL, &timeout);

        if(FD_ISSET(server_sock, &readfds) > 0)
        {
            // server_sock is readable
            socklen_t len;
            int count = -1;
            struct sockaddr_in client_addr; 
            len = sizeof client_addr;
            char receive_buf[BUFF_LEN];
            memset(receive_buf, 0, BUFF_LEN); 
            // receive message
            count = recvfrom(server_sock, receive_buf, BUFF_LEN, 0, (struct sockaddr*)&client_addr, &len);// receive udp data
            if(count == -1)
            {
                printf("receive data failed!\n");
                return -1;	
            }
            rx_count++;
            printf("[rx_count: %d length:%d] %s\n", rx_count, count, receive_buf);
            cJSON* root;
            cJSON* format;
            root = cJSON_Parse(receive_buf);
            int value_int;
            double value_double;
            char* value_string;
            value_int = cJSON_GetObjectItem(root, "host_flag")->valueint;
            if (value_int == 1)
            {
                s_host_bsm.host_flag = VEH_FLAG_HOST;
            }
            else if (value_int == 2)
            {
                s_host_bsm.host_flag = VEH_FLAG_REMOTE;
            }
            else
            {
                s_host_bsm.host_flag = VEH_FLAG_NONE;
            }
            format = cJSON_GetObjectItem(root, "pos");
            value_double = cJSON_GetObjectItem(format, "latitude")->valuedouble;
            s_host_bsm.pos.latitude = value_double;
            value_double = cJSON_GetObjectItem(format, "longitude")->valuedouble;
            s_host_bsm.pos.longitude = value_double;
            value_int = cJSON_GetObjectItem(root, "trans")->valueint;
            s_host_bsm.trans = value_int;
            value_double = cJSON_GetObjectItem(root, "speed")->valuedouble;
            s_host_bsm.speed = value_double;
            value_double = cJSON_GetObjectItem(root, "heading")->valuedouble;
            s_host_bsm.heading = value_double;
            format = cJSON_GetObjectItem(root, "accel_set");
            value_double = cJSON_GetObjectItem(format, "acc_lng")->valuedouble;
            s_host_bsm.accel_set.acc_lng = value_double;
            value_double = cJSON_GetObjectItem(format, "acc_lat")->valuedouble;
            s_host_bsm.accel_set.acc_lat = value_double;
            value_int = cJSON_GetObjectItem(root, "vehicle_classification")->valueint;
            s_host_bsm.vehicle_classification.classification = value_int;
            value_int = cJSON_GetObjectItem(root, "events")->valueint;
            s_host_bsm.events = value_int;
            format = cJSON_GetObjectItem(root, "veh_emergency_ext");
            value_int = cJSON_GetObjectItem(format, "response_type")->valueint;
            s_host_bsm.veh_emergency_ext.response_type = value_int;
            value_int = cJSON_GetObjectItem(format, "lights_use")->valueint;
            s_host_bsm.veh_emergency_ext.lights_use = value_int;
         
            //V2X_PR(LOG_LEVEL_DEBUG,LOG_ID,"[rx_count: %d length:%d] %s", rx_count, count, receive_buf);
            // send message to wms
            send_to_wms(receive_buf,count);
            //V2X_PR(LOG_LEVEL_DEBUG,LOG_ID,"Sending to WMS");
        }
        else if(FD_ISSET(server_sock, &readfds)==0)
        {
            // server sock is unreadable
            wait_count++;
            if(wait_count == 10){
                printf(" waiting\n");
                wait_count = 0;
            }
            
        }
        else
        {
            // error
            printf(" socket error\n");
            return -1;
        }
    }
}