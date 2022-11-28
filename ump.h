#ifndef SMS_UMP_H
#define SMS_UMP_H

#ifdef __cplusplus
extern "C" {
#endif

int sendCode(const char* phone, const char* code);

const char* showSms(const char* code);

#ifdef __cplusplus
}
#endif

#endif //SMS_UMP_H
