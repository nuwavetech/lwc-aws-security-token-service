# LightWave Client - AWS Security Token Service
This LightWave Client sample application illustrates how to assume an AWS Identity and Access Management (IAM)role using the AWS Security Token Service (STS). The Access Key Id, Secret Access Key, and Session Token of the assumed role can be used in subsequent LightWave Client requests to AWS services.
 
A LightWave Client (LWC) application might use STS in the following scenario:
   
 + A LWC application needs to access files in an AWS S3 bucket.
 + The S3 bucket policy uses IAM roles to contol access.
 + The LWC application must assume an IAM role and use the temporary credentials in order to access the S3 bucket.
  
This sample illustrates how to assume the IAM role. The credentials returned can be used in subsequent requests to other AWS services.

## Prerequisites

+ NonStop C Compiler.
+ An installed instance of [LightWave Client](https://docs.nuwavetech.com/display/LWCLIENT) version 1.1.0 or greater.
+ An AWS account.
+ An IAM role ARN to be assumed.
+ The security credentials (Access key ID and Secret access key) of an IAM user that has permission to assume the IAM Role.

The following values must be configured in the SETUP TACL macro after installation of the sample:

+ lwc-isv - The installation subvolume of your LightWave Client software.
+ role-arn - The ARN of the IAM role to be assumed.

The AWSAUTH file must be updated with the credentials of an IAM user that has permission to assume the role. For more information
on configuring AWS credentials for use with LightWave Client, see [Request Authentication and Signing](https://docs.nuwavetech.com/display/LWCLIENT/Request+Authentication+and+Signing) in the LightWave Client documentation.
  
## Install & Build

The application must be built from source. The source files are present in the repository for convenient viewing. 
In addition, a PAK archive containing all of the source files is available for transfer to your NonStop system.

| Repository File | NonStop File |
| -- | -- |
| macros/build.txt | build |
| macros/loadddl.txt | loadddl |
| macros/logcfg.txt | logcfg |
| macros/setenv.txt | setenv |
| macros/startpw.txt | startpw |
| macros/stoppw.txt | stoppw | 
| macros/unsetenv.txt | unsetenv |
| resources/stsapi.json | stsapi |
| resources/stsddl.txt | stsddl |
| src/sts.c | stsc |
| stspak.bin | stspak |  

#### Transfer the PAK archive to your NonStop System

Download `stspak.bin` from this repository to your local system, then upload to your NonStop server using binary transfer mode.

Note: to download the PAK file, click `stspak.bin` in the file list to display the file details, then click the *Download* button.

Logon to TACL on your NonStop system to peform the installation and build steps.

#### Unpak the PAK archive
```
TACL > UNPAK STSPAK ($*.*.*), VOL $your-volume.your-subvolume.*, LISTALL, MYID
```

#### Build the application 
```
TACL > RUN LOADDDL
TACL > RUN BUILD
```
## Running the application
Customize the SETENV macro for your environment and run it to set the required PARAMs.
```
TACL> T/EDIT SETENV
TACL> RUN SETENV
```
Customize the AWSAUTH file with your IAM user credentials.
```
TACL> T/EDIT AWSAUTH
```
Start the LightWave Client Pathway
```
TACL > RUN STARTPW
```
Run the application
```
TACL > RUN STS

LightWave Client(tm) - AWS Security Token Service (STS) - Test Driver - 31JUL2019

Sending a GetCallerIdentity request ... completed in 0.314983 seconds.

    Request Id: d343945b-b3b3-11e9-a98e-e9d92f7310af
    Account:    7642****3716
    UserId:     AIDA*************SG7U
    Arn:        arn:********************************************user

Sending an AssumeRole request ... completed in 0.128614 seconds.

    Request Id:         d3576aa7-b3b3-11e9-a98e-e9d92f7310af
    Role ARN:           arn:********************************************role
    Access Key Id:      ASIA************IJJS
    Secret Access Key:  Y+MD********************************R1by
    Session Token:      FQoGZXIvYXdzEEIaD ... Zm/Pa3v2vKLWPh+oF
    Expiration:         212431352953000000 2019-07-31T17:09:13.000Z

Sending a GetAccessKeyInfo request ... completed in 0.090779 seconds.

    Request Id:         d367e598-b3b3-11e9-a98e-e9d92f7310af
    Access Key Account: 7642****3716

Done.
```
Assistance is available through the [NuWave Technologies Support Center](http://support.nuwavetech.com).

