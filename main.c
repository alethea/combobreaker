#include <stdio.h>
#include <stdlib.h>
#include "loader.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
 
#define MEM_SIZE (128)
 
int main()
{
cl_device_id device_id = NULL;
cl_context context = NULL;
cl_command_queue command_queue = NULL;
cl_mem memobj = NULL;
cl_program program = NULL;
cl_kernel kernel = NULL;
cl_platform_id platform_id = NULL;
cl_uint ret_num_devices;
cl_uint ret_num_platforms;
cl_int ret;
 
char string[MEM_SIZE];
 
char *fileName = "./hello.cl";
char *source_str;
size_t source_size;
 
/* Load the source code containing the kernel*/
load(fileName, &source_str, &source_size);

/* Get Platform and Device Info */
ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
 
/* Create OpenCL context */
context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
 
/* Create Command Queue */
command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
 
/* Create Memory Buffer */
memobj = clCreateBuffer(context, CL_MEM_READ_WRITE,MEM_SIZE * sizeof(char), NULL, &ret);
 
/* Create Kernel Program from the source */
program = clCreateProgramWithSource(context, 1, (const char **)&source_str,
(const size_t *)&source_size, &ret);
 
/* Build Kernel Program */
ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
 
/* Create OpenCL Kernel */
kernel = clCreateKernel(program, "hello", &ret);
 
/* Set OpenCL Kernel Parameters */
/*Our host will be modifying this*/
ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
 
/* Execute OpenCL Kernel */
ret = clEnqueueTask(command_queue, kernel, 0, NULL,NULL);

/* Copy results from the memory buffer */
ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0,
MEM_SIZE * sizeof(char),string, 0, NULL, NULL);

/* Display Result */
puts(string);
 
/* Finalization */
ret = clFlush(command_queue);
ret = clFinish(command_queue);
ret = clReleaseKernel(kernel);
ret = clReleaseProgram(program);
ret = clReleaseMemObject(memobj);
ret = clReleaseCommandQueue(command_queue);
ret = clReleaseContext(context);
 
free(source_str);
 
return 0;
}