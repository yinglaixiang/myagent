#ifndef __VSIM_H__
#define __VSIM_H__

#include <stdint.h>

/*
return codes:
    0       Successful
    1       The profile is running, do nothing
    others  Failed
SLOT:
    Only support slot=0x01 currently
*/
int32_t vsim_enable(uint8_t slot, uint32_t profile_id);


/*
Return codes:
    0       Successful
    others  Failed
*/
int32_t vsim_insert_profile(uint8_t* profile, uint32_t profile_size);
int32_t vsim_update_profile(uint32_t profile_id, uint8_t *profile, uint32_t profile_size);
int32_t vsim_delete_profile(uint32_t profile_id);

int32_t vsim_get_cid(uint8_t *id, uint32_t *id_len);
int32_t vsim_get_cert(uint8_t *cert, uint32_t *cert_len);
int32_t vsim_get_exported_pk(uint8_t *pk, uint32_t *pk_len);

#endif // __VSIM_H__
