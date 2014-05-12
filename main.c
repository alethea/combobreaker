#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <error.h>
#include "hash.h"
#include "alphabet.h"
#include "loader.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define SHA256_KERNEL "sha256.cl"

void or_fail(cl_int err, char * fmt) {
    if (err) {
        error(-2, 0, fmt, err);
    }
}
 
int main() {
    cl_device_id device_id = NULL;
    cl_context context = NULL;
    cl_command_queue command_queue = NULL;
    cl_mem hash = NULL;
    cl_mem message = NULL;
    cl_mem length = NULL;
    cl_program program = NULL;
    cl_kernel kernel = NULL;
    cl_platform_id platform_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int err;
     
    char resulthash[32];

    char *source_str;
    size_t source_size;
    /* Load the source code containing the kernel*/
    load(SHA256_KERNEL, &source_str, &source_size);

    /* Get Platform and Device Info */
    or_fail(clGetPlatformIDs(1, &platform_id, &ret_num_platforms),
            "Could not get platform ID: %d\n");

    or_fail(clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, 
        &device_id, &ret_num_devices),"Could not get device ID: %d\n");

    /* Create OpenCL context */
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &err);
    or_fail(err, "Could not initialize OpenCL context: %d");
     
    /* Create Command Queue */
    command_queue = clCreateCommandQueue(context, device_id, 0, &err);
    or_fail(err, "Count not create command queue: %d");
     
    /* Create Memory Buffer */
    message = clCreateBuffer(context, CL_MEM_READ_WRITE, 8 * sizeof(char), NULL, &err);
    or_fail(err, "Could not create message buffer: %d\n");
    hash = clCreateBuffer(context, CL_MEM_READ_WRITE, 8 * sizeof(cl_uint), NULL, &err);
    or_fail(err, "Could not create hash buffer: %d\n");
    length= clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_int), NULL, &err);
    or_fail(err, "Could not create length buffer: %d\n");

    /* Create Kernel Program from the source */
    program = clCreateProgramWithSource(context, 1, (const char **)&source_str,
        (const size_t *)&source_size, &err);
    or_fail(err, "Could not create program object: %d\n");
     
    /* Build Kernel Program */
    or_fail(clBuildProgram(program, 1, &device_id, NULL, NULL, NULL),
            "Could not build program: %d\n");

    /* Create OpenCL Kernel */
    kernel = clCreateKernel(program, "sha256", &err);
    or_fail(err, "Could not create kernel: %d\n");
     
    /* Set OpenCL Kernel Parameters */
    or_fail(clSetKernelArg(kernel, 0, sizeof(cl_mem), &message),
            "Could not set arg 1: %d\n");
    or_fail(clSetKernelArg(kernel, 1, sizeof(cl_mem), &length),
            "Could not set arg 2: %d\n");
    or_fail(clSetKernelArg(kernel, 2, sizeof(cl_mem), &hash),
            "Could not set arg 3: %d\n");

    /* Execute OpenCL Kernel */
    or_fail(clEnqueueTask(command_queue, kernel, 0, NULL,NULL),
            "Could not execute kernel: %d\n");
     
    /* Copy results from the memory buffer */
    or_fail(clEnqueueReadBuffer(command_queue, hash, CL_TRUE, 0,
        8 * sizeof(cl_int), resulthash, 0, NULL, NULL),
        "Could not execute kernel: %d\n");

    /* Display Result */
    print_hash(resulthash, 32);

    /* Finalization */
    or_fail(clFinish(command_queue),
            "Could not finish command queue: %d\n");
    or_fail(clFlush(command_queue),
            "Could not flush command queue: %d\n");
    or_fail(clReleaseKernel(kernel),
            "Could not release kernel: %d\n");
    or_fail(clReleaseProgram(program),
            "Could not release program: %d\n");
    or_fail(clReleaseMemObject(message),
            "Could not release memobject message: %d\n");
    or_fail(clReleaseMemObject(hash),
            "Could not release memobject hash: %d\n");
    or_fail(clReleaseMemObject(length),
            "Could not release memobject length: %d\n");
    or_fail(clReleaseCommandQueue(command_queue),
            "Could not release command queue: %d\n");
    or_fail(clReleaseContext(context),
            "Could not release context: %d\n");
    free(source_str);
     
    return 0;
}
