#ifndef STATUS_H
#define STATUS_H

typedef enum ds_status {
    DS_OK = 0,
    DS_ERR_INVALID_ARGUMENT,
    DS_ERR_OUT_OF_MEMORY,
    DS_ERR_EMPTY,
    DS_ERR_OUT_OF_RANGE,
    DS_ERR_ALREADY_EXISTS
} ds_status;

#endif /* STATUS_H */
