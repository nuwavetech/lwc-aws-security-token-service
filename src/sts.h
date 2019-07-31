/* SCHEMA PRODUCED DATE - TIME : 7/31/2019 - 11:02:57 */
#pragma section lightwave_rp_code_enum
/* Definition LIGHTWAVE-RP-CODE-ENUM created on 07/31/2019 at 11:02 */
enum
{
   lw_rp_success = 0,
   lw_rp_info = 1,
   lw_rp_error = 2
};
typedef short                           lightwave_rp_code_enum_def;
#pragma section lightwave_info_code_enum
/* Definition LIGHTWAVE-INFO-CODE-ENUM created on 07/31/2019 at 11:02 */
enum
{
   lw_info_field_truncated = 100,
   lw_info_array_truncated = 101
};
typedef short                           lightwave_info_code_enum_def;
#pragma section lightwave_error_src_enum
/* Definition LIGHTWAVE-ERROR-SRC-ENUM created on 07/31/2019 at 11:02 */
enum
{
   lw_error_src_lightwave = 1,
   lw_error_src_http = 2,
   lw_error_src_tcpip = 3,
   lw_error_src_ssl = 4
};
typedef short                           lightwave_error_src_enum_def;
#pragma section lightwave_error_enum
/* Definition LIGHTWAVE-ERROR-ENUM created on 07/31/2019 at 11:02 */
enum
{
   lw_error_invalid_license = 1,
   lw_error_invalid_header = 2,
   lw_error_invalid_rq_code = 3,
   lw_error_invalid_type = 4,
   lw_error_serialization_error = 5,
   lw_error_deserialization_error = 6,
   lw_error_request_timeout = 7,
   lw_error_response_not_defined = 12,
   lw_error_internal_error = 500
};
typedef short                           lightwave_error_enum_def;
#pragma section lightwave_rq_header
/* Definition LIGHTWAVE-RQ-HEADER created on 07/31/2019 at 11:02 */
#include <tnsint.h>
#pragma fieldalign shared2 __lightwave_rq_header
typedef struct __lightwave_rq_header
{
   short                           rq_code;
   unsigned short                  rq_version;
   __uint32_t                      rq_timeout;
   char                            reserved[24];
} lightwave_rq_header_def;
#define lightwave_rq_header_def_Size 32
#pragma section lightwave_rp_header
/* Definition LIGHTWAVE-RP-HEADER created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __lightwave_rp_header
typedef struct __lightwave_rp_header
{
   short                           rp_code;
   short                           http_status;
   short                           info_code;
   short                           info_detail;
   char                            reserved[24];
} lightwave_rp_header_def;
#define lightwave_rp_header_def_Size 32
#pragma section lightwave_error_rp
/* Definition LIGHTWAVE-ERROR-RP created on 07/31/2019 at 11:02 */
#include <tnsint.h>
#pragma fieldalign shared2 __lightwave_error_rp
typedef struct __lightwave_error_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   __int32_t                       error_source;
   __int32_t                       error_code;
   __int32_t                       error_subcode;
   char                            error_message[4096];
} lightwave_error_rp_def;
#define lightwave_error_rp_def_Size 4140
#pragma section aws_security_token_ser_val
/* Definition AWS-SECURITY-TOKEN-SER-VAL created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __aws_security_token_ser_val
typedef struct __aws_security_token_ser_val
{
   short                           rq_assume_role;
   /*value is 1*/
   short                           rq_get_caller_identity;
   /*value is 2*/
   short                           rq_get_access_key_info;
   /*value is 3*/
} aws_security_token_ser_val_def;
#define aws_security_token_ser_val_def_Size 6
#pragma section aws_security_token_ser_enm
/* Definition AWS-SECURITY-TOKEN-SER-ENM created on 07/31/2019 at 11:02 */
enum
{
   rq_assume_role = 1,
   rq_get_caller_identity = 2,
   rq_get_access_key_info = 3
};
typedef short                           aws_security_token_ser_enm_def;
#pragma section credentials_type
/* Definition CREDENTIALS-TYPE created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __credentials_type
typedef struct __credentials_type
{
   char                            session_token[2050];
   char                            secret_access_key[66];
   long long                       expiration;
   char                            access_key_id[66];
} credentials_type_def;
#define credentials_type_def_Size 2190
#pragma section assumed_role_user_type
/* Definition ASSUMED-ROLE-USER-TYPE created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __assumed_role_user_type
typedef struct __assumed_role_user_type
{
   char                            arn[2050];
   char                            assumed_role_id[2050];
} assumed_role_user_type_def;
#define assumed_role_user_type_def_Size 4100
#pragma section assume_role_result_type
/* Definition ASSUME-ROLE-RESULT-TYPE created on 07/31/2019 at 11:02 */
#include <tnsint.h>
#pragma fieldalign shared2 __assume_role_result_type
typedef struct __assume_role_result_type
{
   credentials_type_def            credentials;
   assumed_role_user_type_def      assumed_role_user;
   __int32_t                       packed_policy_size;
} assume_role_result_type_def;
#define assume_role_result_type_def_Size 6294
#pragma section response_metadata_type
/* Definition RESPONSE-METADATA-TYPE created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __response_metadata_type
typedef struct __response_metadata_type
{
   char                            request_id[66];
} response_metadata_type_def;
#define response_metadata_type_def_Size 66
#pragma section assume_role_response
/* Definition ASSUME-ROLE-RESPONSE created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __assume_role_response
typedef struct __assume_role_response
{
   assume_role_result_type_def     assume_role_result;
   response_metadata_type_def      response_metadata;
} assume_role_response_def;
#define assume_role_response_def_Size 6360
#pragma section error_type
/* Definition ERROR-TYPE created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __error_type
typedef struct __error_type
{
   char                            type_rw[66];
   char                            code_rw[66];
   char                            message_rw[1026];
} error_type_def;
#define error_type_def_Size 1158
#pragma section error_response
/* Definition ERROR-RESPONSE created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __error_response
typedef struct __error_response
{
   error_type_def                  error_rw;
   char                            request_id[66];
} error_response_def;
#define error_response_def_Size 1224
#pragma section get_caller_identity_r_type
/* Definition GET-CALLER-IDENTITY-R-TYPE created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __get_caller_identity_r_type
typedef struct __get_caller_identity_r_type
{
   char                            arn[2050];
   char                            user_id[66];
   char                            account[66];
} get_caller_identity_r_type_def;
#define get_caller_identity_r_type_def_Size 2182
#pragma section get_caller_id_response
/* Definition GET-CALLER-ID-RESPONSE created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __get_caller_id_response
typedef struct __get_caller_id_response
{
   get_caller_identity_r_type_def  get_caller_identity_result;
   response_metadata_type_def      response_metadata;
} get_caller_id_response_def;
#define get_caller_id_response_def_Size 2248
#pragma section get_access_key_info_r_type
/* Definition GET-ACCESS-KEY-INFO-R-TYPE created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __get_access_key_info_r_type
typedef struct __get_access_key_info_r_type
{
   char                            account[16];
} get_access_key_info_r_type_def;
#define get_access_key_info_r_type_def_Size 16
#pragma section access_key_info_response
/* Definition ACCESS-KEY-INFO-RESPONSE created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __access_key_info_response
typedef struct __access_key_info_response
{
   get_access_key_info_r_type_def  get_access_key_info_result;
   response_metadata_type_def      response_metadata;
} access_key_info_response_def;
#define access_key_info_response_def_Size 82
#pragma section assume_role_rq
/* Definition ASSUME-ROLE-RQ created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __assume_role_rq
typedef struct __assume_role_rq
{
   lightwave_rq_header_def         lightwave_rq_header;
   char                            role_session_name[66];
   char                            duration_seconds[8];
   char                            external_id[1226];
   char                            policy[2050];
   char                            role_arn[2050];
   char                            serial_number[258];
   char                            token_code[8];
} assume_role_rq_def;
#define assume_role_rq_def_Size 5698
#pragma section assume_role_200_rp
/* Definition ASSUME-ROLE-200-RP created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __assume_role_200_rp
typedef struct __assume_role_200_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   assume_role_response_def        assume_role_response;
} assume_role_200_rp_def;
#define assume_role_200_rp_def_Size 6392
#pragma section assume_role_other_rp
/* Definition ASSUME-ROLE-OTHER-RP created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __assume_role_other_rp
typedef struct __assume_role_other_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   error_response_def              error_response;
} assume_role_other_rp_def;
#define assume_role_other_rp_def_Size 1256
#pragma section get_caller_identity_rq
/* Definition GET-CALLER-IDENTITY-RQ created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __get_caller_identity_rq
typedef struct __get_caller_identity_rq
{
   lightwave_rq_header_def         lightwave_rq_header;
} get_caller_identity_rq_def;
#define get_caller_identity_rq_def_Size 32
#pragma section get_caller_identity_200_rp
/* Definition GET-CALLER-IDENTITY-200-RP created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __get_caller_identity_200_rp
typedef struct __get_caller_identity_200_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   get_caller_id_response_def      get_caller_id_response;
} get_caller_identity_200_rp_def;
#define get_caller_identity_200_rp_def_Size 2280
#pragma section get_caller_identy_other_rp
/* Definition GET-CALLER-IDENTY-OTHER-RP created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __get_caller_identy_other_rp
typedef struct __get_caller_identy_other_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   error_response_def              error_response;
} get_caller_identy_other_rp_def;
#define get_caller_identy_other_rp_def_Size 1256
#pragma section get_access_key_info_rq
/* Definition GET-ACCESS-KEY-INFO-RQ created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __get_access_key_info_rq
typedef struct __get_access_key_info_rq
{
   lightwave_rq_header_def         lightwave_rq_header;
   char                            access_key_id[256];
} get_access_key_info_rq_def;
#define get_access_key_info_rq_def_Size 288
#pragma section get_access_key_info_200_rp
/* Definition GET-ACCESS-KEY-INFO-200-RP created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __get_access_key_info_200_rp
typedef struct __get_access_key_info_200_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   access_key_info_response_def    access_key_info_response;
} get_access_key_info_200_rp_def;
#define get_access_key_info_200_rp_def_Size 114
#pragma section get_access_key_io_other_rp
/* Definition GET-ACCESS-KEY-IO-OTHER-RP created on 07/31/2019 at 11:02 */
#pragma fieldalign shared2 __get_access_key_io_other_rp
typedef struct __get_access_key_io_other_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   error_response_def              error_response;
} get_access_key_io_other_rp_def;
#define get_access_key_io_other_rp_def_Size 1256
