#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <errno.h>

typedef enum { LOG_LEVEL_DBG, LOG_LEVEL_INF, LOG_LEVEL_WRN, LOG_LEVEL_ERR } LogLevel_t;
const char* level_strs[] = { "DBG", "INF", "WRN", "ERR" };
LogLevel_t g_system_log_level = LOG_LEVEL_INF; 


void get_power_status(char* buf, size_t len) {
    FILE *fp = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    if (fp) { // 1단계: 노트북 확인
        int cap = 0; fscanf(fp, "%d", &cap);
        snprintf(buf, len, "Battery low: %d%%", cap);
        fclose(fp); return;
    }
    fp = fopen("/sys/class/power_supply/AC/online", "r");
    if (fp) { // 2단계: 데스크탑 확인
        int on = 0; fscanf(fp, "%d", &on);
        snprintf(buf, len, "Power Source: AC (%s)", on ? "Connected" : "Disconnected");
        fclose(fp);
    } else { // 3단계: 가상환경/서버 확인
        snprintf(buf, len, "Power Source: Stable Fixed AC");
    }
}

void get_active_ip(char* buf, size_t len) {
    struct ifaddrs *ifaddr, *ifa;
    strncpy(buf, "127.0.0.1", len);
    if (getifaddrs(&ifaddr) != -1) {
        for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET && strcmp(ifa->ifa_name, "lo") != 0) {
                inet_ntop(AF_INET, &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr, buf, len);
                break;
            }
        }
        freeifaddrs(ifaddr);
    }
}


void log_print(LogLevel_t level, const char* file, int line, const char* fmt, ...) {
    if (level < g_system_log_level) return;

    clock_t now = clock();
    unsigned long time_ms = (unsigned long)(now * 1000 / CLOCKS_PER_SEC);

    char buffer[256]; 
    const char* filename = strrchr(file, '/') ? strrchr(file, '/') + 1 : file;
    int offset = snprintf(buffer, sizeof(buffer), "[%lu ms][%s] %s:%d - ", 
                          time_ms, level_strs[level], filename, line);

    if (offset < sizeof(buffer)) {
        va_list args;
        va_start(args, fmt);
        vsnprintf(buffer + offset, sizeof(buffer) - offset, fmt, args);
        va_end(args);
    }
    printf("%s\n", buffer);
}

#define LOG_DBG(fmt, ...) log_print(LOG_LEVEL_DBG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INF(fmt, ...) log_print(LOG_LEVEL_INF, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WRN(fmt, ...) log_print(LOG_LEVEL_WRN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERR(fmt, ...) log_print(LOG_LEVEL_ERR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)



int main() {
    char sys_info[64];

    printf("=== Day 30: Professional Log System ===\n\n");

    // [Phase 1]
    printf("[Phase 1] Current Level: INFO\n");
    LOG_INF("System initialized.");
    LOG_DBG("This DBG log is hidden in Phase 1.");  // 출력 안됨
    
    // 전원 및 배터리 시스템 상태
    get_power_status(sys_info, sizeof(sys_info));
    LOG_WRN("%s", sys_info);

    if (access("config.ini", F_OK) == -1) {
        LOG_ERR("Failed to load file: config.ini (Reason: %s)", strerror(errno));
    }

    // clock() 지연
    clock_t goal = clock() + (24 * CLOCKS_PER_SEC / 1000);
    while (clock() < goal); 

    printf("\n>> System Log Level Changed to: DBG (and above)\n\n");
    g_system_log_level = LOG_LEVEL_DBG;

    // [Phase 2]
    printf("[Phase 2] Verbose Mode On\n");
    LOG_DBG("Variable i reached limit."); // 출력 됨
    
    get_active_ip(sys_info, sizeof(sys_info));
    LOG_INF("Network connected IP: %s", sys_info);

    return 0;
}