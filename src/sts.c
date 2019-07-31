/**
 *
 *  Copyright (c) 2019 NuWave Technologies, Inc. All rights reserved. (www.nuwavetech.com)
 *
 */
  
#pragma nolist
#include <cextdecs>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tal.h>
#include <time.h>
#pragma list

#include "sts.h"

static const char* compactToken(const char* token);
static const char* formatTimestamp(const long long timestamp);
static const char* getEnvValue(const char* name, int required);
static const char* maskString(const char* src);
static void printErrorResponse(const lightwave_rp_header_def* header,
                               const error_response_def* error);
static void printSendError(void);

int main(int argc, char** argv, char** env) {
  int rc;
  const char* pathmon_name;
  const char* server_class;
  const char* role_arn;
  long long start_time;
  long long end_time;
  int reply_len;

  get_caller_identity_rq_def get_caller_identity_rq;
  assume_role_rq_def assume_role_rq;
  get_access_key_info_rq_def get_access_key_info_rq;

  union {
    lightwave_rp_header_def header;
    get_caller_identity_200_rp_def rp_200;
    get_caller_identy_other_rp_def rp_other;
  } get_caller_identity_rp;

  union {
    lightwave_rp_header_def header;
    assume_role_200_rp_def rp_200;
    assume_role_other_rp_def rp_other;
  } assume_role_rp;

  union {
    lightwave_rp_header_def header;
    get_access_key_info_200_rp_def rp_200;
    get_access_key_io_other_rp_def rp_other;
  } get_access_key_info_rp;

  printf("\nLightWave Client(tm) - AWS Security Token Service (STS) "
         "- Test Driver - 31JUL2019\n");

  /* Get variables from the environment. These are set by the SETENV macro. */
  if ((pathmon_name = getEnvValue("PATHMON-NAME", 1)) == NULL) {
    return 0;
  }

  if ((server_class = getEnvValue("SERVER-CLASS", 1)) == NULL) {
    return 0;
  }

  if ((role_arn = getEnvValue("ROLE-ARN", 1)) == NULL) {
    return 0;
  }

  /* Initialize and send a get caller identity. */
  printf("\nSending a GetCallerIdentity request ... ");

  memset(&get_caller_identity_rq, 0, sizeof(get_caller_identity_rq));
  get_caller_identity_rq.lightwave_rq_header.rq_code = rq_get_caller_identity;

  start_time = JULIANTIMESTAMP();

  rc = SERVERCLASS_SENDL_(
      (char*)pathmon_name, (short)strlen(pathmon_name), (char*)server_class,
      (short)strlen(server_class), (char*)&get_caller_identity_rq,
      (char*)&get_caller_identity_rp, sizeof(get_caller_identity_rq),
      sizeof(get_caller_identity_rp), &reply_len);

  end_time = JULIANTIMESTAMP();

  if (rc != 0) {
    printSendError();
    return 0;
  }

  if (get_caller_identity_rp.header.http_status != 200) {
    printErrorResponse(&get_caller_identity_rp.header,
                       &get_caller_identity_rp.rp_other.error_response);
    return 0;
  }

  printf("completed in %g seconds.\n\n",
         (double)(end_time - start_time) / 1000000.0);

  printf("    Request Id: %s\n",
         get_caller_identity_rp.rp_200.get_caller_id_response.response_metadata
             .request_id);
  printf("    Account:    %s\n",
         maskString(
             (const char*)get_caller_identity_rp.rp_200.get_caller_id_response
                 .get_caller_identity_result.account));
  printf("    UserId:     %s\n",
         maskString(
             (const char*)get_caller_identity_rp.rp_200.get_caller_id_response
                 .get_caller_identity_result.user_id));
  printf(
      "    Arn:        %s\n",
      maskString((const char*)get_caller_identity_rp.rp_200
                     .get_caller_id_response.get_caller_identity_result.arn));

  /* Initialize and send an assume role request. */
  printf("\nSending an AssumeRole request ... ");

  memset(&assume_role_rq, 0, sizeof(assume_role_rq));
  assume_role_rq.lightwave_rq_header.rq_code = rq_assume_role;
  strcpy(assume_role_rq.role_session_name, "lwc-sts-sample");
  strncpy(assume_role_rq.role_arn, role_arn, sizeof(assume_role_rq.role_arn));
  strcpy(assume_role_rq.duration_seconds, "900");

  start_time = JULIANTIMESTAMP();

  rc = SERVERCLASS_SENDL_((char*)pathmon_name, (short)strlen(pathmon_name),
                          (char*)server_class, (short)strlen(server_class),
                          (char*)&assume_role_rq, (char*)&assume_role_rp,
                          sizeof(assume_role_rq), sizeof(assume_role_rp),
                          &reply_len);

  end_time = JULIANTIMESTAMP();

  if (rc != 0) {
    printSendError();
    return 0;
  }

  if (assume_role_rp.header.http_status != 200) {
    printErrorResponse(&assume_role_rp.header,
                       &assume_role_rp.rp_other.error_response);
    return 0;
  }

  printf("completed in %g seconds.\n\n",
         (double)(end_time - start_time) / 1000000.0);

  printf(
      "    Request Id:         %s\n",
      assume_role_rp.rp_200.assume_role_response.response_metadata.request_id);
  printf("    Role ARN:           %s\n",
         maskString((const char*)assume_role_rq.role_arn));
  printf("    Access Key Id:      %s\n",
         maskString((const char*)assume_role_rp.rp_200.assume_role_response
                        .assume_role_result.credentials.access_key_id));
  printf("    Secret Access Key:  %s\n",
         maskString((const char*)assume_role_rp.rp_200.assume_role_response
                        .assume_role_result.credentials.secret_access_key));
  printf("    Session Token:      %s\n",
         compactToken(assume_role_rp.rp_200.assume_role_response
                          .assume_role_result.credentials.session_token));
  printf("    Expiration:         %lld %s\n",
         assume_role_rp.rp_200.assume_role_response.assume_role_result
             .credentials.expiration,
         formatTimestamp(assume_role_rp.rp_200.assume_role_response
                             .assume_role_result.credentials.expiration));

  /* Initialize and send a get access key info request. */
  printf("\nSending a GetAccessKeyInfo request ... ");

  memset(&get_access_key_info_rq, 0, sizeof(get_access_key_info_rq));
  get_access_key_info_rq.lightwave_rq_header.rq_code = rq_get_access_key_info;
  strcpy(get_access_key_info_rq.access_key_id,
         assume_role_rp.rp_200.assume_role_response.assume_role_result
             .credentials.access_key_id);

  start_time = JULIANTIMESTAMP();

  rc = SERVERCLASS_SENDL_(
      (char*)pathmon_name, (short)strlen(pathmon_name), (char*)server_class,
      (short)strlen(server_class), (char*)&get_access_key_info_rq,
      (char*)&get_access_key_info_rp, sizeof(get_access_key_info_rq),
      sizeof(get_access_key_info_rp), &reply_len);

  end_time = JULIANTIMESTAMP();

  if (rc != 0) {
    printSendError();
    return 0;
  }

  if (get_access_key_info_rp.header.http_status != 200) {
    printErrorResponse(&get_access_key_info_rp.header,
                       &get_access_key_info_rp.rp_other.error_response);
    return 0;
  }

  printf("completed in %g seconds.\n\n",
         (double)(end_time - start_time) / 1000000.0);

  printf("    Request Id:         %s\n",
         get_access_key_info_rp.rp_200.access_key_info_response
             .response_metadata.request_id);

  printf("    Access Key Account: %s\n",
         maskString(
             (const char*)get_access_key_info_rp.rp_200.access_key_info_response
                 .get_access_key_info_result.account));

  printf("\nDone.\n");

  return 0;
}

/* Format the token into 40 chars or less. */
static const char* compactToken(const char* token) {
  static char compact[64];

  if (strlen(token) < 40) {
    strcpy(compact, token);
    return compact;
  }

  sprintf(compact, "%-.17s ... %-.17s", token, &token[strlen(token) - 17]);
  return compact;
}

static const char* formatTimestamp(const long long timestamp) {
  static char string[64];
  short dt[8];

  if (INTERPRETTIMESTAMP(timestamp, dt) == -1) {
    strcpy(string, "invalid");
    return string;
  }

  sprintf(string, "%04hd-%02hd-%02hdT%02hd:%02hd:%02hd.%03hdZ", dt[0], dt[1],
          dt[2], dt[3], dt[4], dt[5], dt[6]);

  return string;
}

static const char* getEnvValue(const char* name, int required) {
  const char* v = getenv(name);
  if (v == NULL && required != 0) {
    printf("PARAM \"%s\" not set. Did you run SETENV?\n", name);
  }
  return v;
}

static const char* maskString(const char* src) {
  static char string[2050];
  size_t len;

  *string = 0;
  strncat(string, src, sizeof(string) - 1);
  len = strlen(string);

  if (len <= 8) {
    memset(string, '*', len);
  } else {
    len -= 8;
    memset(&string[4], '*', len);
  }

  return string;
}

static void printErrorResponse(const lightwave_rp_header_def* header,
                               const error_response_def* error) {

  printf("\n\nThe service returned HTTP status %d, error:\n",
         header->http_status);
  printf("  Type:     %s\n", error->error_rw.type_rw);
  printf("  Code:     %s\n", error->error_rw.code_rw);
  printf("  Message:  %s\n", error->error_rw.message_rw);
  printf("\n");
}

static void printSendError(void) {
  short prc;
  short frc;

  SERVERCLASS_SEND_INFO_(&prc, &frc);

  printf("\n\nSERVERCLASS_SEND_ error %hd:%hd occurred.\n\n", prc, frc);
  switch (frc) {
  case 14:
    printf("Did you start the pathway by running STARTPW?\n\n");
    break;
  default:
    break;
  }

  return;
}

/* End of file. */