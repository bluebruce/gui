#ifndef __MSGD_H__
#define __MSGD_H__

#define MSGD_IP "127.0.0.1"
#define MSGD_FE_PORT 6850

#define INFOTYPE_RT 0xAD000001
#define INFOTYPE_ST 0xAD000002

struct info_hdr {
    unsigned int type;
    unsigned int data_len;
    unsigned char data[];
};

struct static_info {
    unsigned char IP[16];
    unsigned char FW[16];
};

struct runtime_info {
    unsigned int type;
    unsigned int str_len;
    unsigned char str[];
};



#endif // __MSGD_H__
