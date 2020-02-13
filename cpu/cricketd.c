/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h> //unlink()
#include <signal.h> //sigaction

#include <cuda_runtime_api.h>
#include <cuda.h>

#include "cd_rpc_prot.h"

#include "cd_common.h"
#include "cricketd_utils.h"


extern void rpc_cd_prog_1(struct svc_req *rqstp, register SVCXPRT *transp);

static size_t kernelnum = 0;
static kernel_info_t *infos = NULL;

void int_handler(int signal) {
    unlink(CD_SOCKET_PATH);
    printf("have a nice day!\n");
    exit(0);
}

bool_t printmessage_1_svc(char *argp, int *result, struct svc_req *rqstp)
{
    printf("string: \"%s\"\n", argp);
    *result = 42;
    return 1;
}

bool_t cuda_malloc_1_svc(size_t argp, ptr_result *result, struct svc_req *rqstp)
{
    printf("cudaMalloc\n");
    result->err = cudaMalloc((void**)&result->ptr_result_u.ptr, argp);
    return 1;
}

bool_t cuda_free_1_svc(uint64_t ptr, int *result, struct svc_req *rqstp)
{
    printf("cudaFree\n");
    *result = cudaFree((void*)ptr);
    return 1;
}

bool_t cuda_memcpy_htod_1_svc(uint64_t ptr, mem_data mem, size_t size, int *result, struct svc_req *rqstp)
{
    printf("cudaMemcpyHtoD\n");
    if (size != mem.mem_data_len) {
        fprintf(stderr, "data size mismatch\n");
        return 0;
    }
    *result = cudaMemcpy((void*)ptr, mem.mem_data_val, size, cudaMemcpyHostToDevice);
    return 1;
}

bool_t cuda_memcpy_dtoh_1_svc(uint64_t ptr, size_t size, mem_result *result, struct svc_req *rqstp)
{
    printf("cudaMemcpyDtoH\n");
    //*result = cudaMemcpy((void*)ptr, mem.mem_data_val, size, cudaMemcpyHostToDevice);
    return 1;
}

bool_t cuda_launch_kernel_1_svc(ptr function, rpc_dim3 gridDim, rpc_dim3 blockDim,
                                mem_data args, size_t sharedMem, ptr stream,
                                int *result, struct svc_req *rqstp)
{
/*    void *elf;
    size_t elf_size;

    if (cricketd_launch_load_elf("/home/eiling/projects/cricket/tests/test_kernel", &elf, &elf_size) != 1) {
        fprintf(stderr, "error while loading elf\n");
    }
*/
  /*  void* cuda_args[] = {};
    CUresult res;
    CUmodule cuModule;
    res = cuModuleLoad(&cuModule, "/home/eiling/projects/cricket/tests/test_kernel");
    printf("%d: res=%d\n", __LINE__, res);
    CUfunction kernel;
    res = cuModuleGetFunction(&kernel, cuModule, "kernel_no_param");
    printf("%d: res=%d\n", __LINE__, res);
    res = cuLaunchKernel(kernel, gridDim.x, gridDim.y, gridDim.z, blockDim.x, blockDim.y, blockDim.z, sharedMem, (void*)stream, cuda_args, NULL);
    printf("%d: res=%d\n", __LINE__, res);
    */
    //*result = cudaMemcpy((void*)ptr, mem.mem_data_val, size, cudaMemcpyHostToDevice);

   // void *kernel_addr = (void*)(function+elf);
    dim3 cuda_gridDim = {gridDim.x, gridDim.y, gridDim.z};
    dim3 cuda_blockDim = {blockDim.x, blockDim.y, blockDim.z};
    void *t_args = NULL;

    printf("cudaLaunchKernel(func=%p, gridDim=[%d,%d,%d], blockDim=[%d,%d,%d], args=%p, sharedMem=%d, stream=%p)\n", function, cuda_gridDim.x, cuda_gridDim.y, cuda_gridDim.z, cuda_blockDim.x, cuda_blockDim.y, cuda_blockDim.z, t_args, sharedMem, (void*)stream);

    //*result = cudaLaunchKernel((void*)function, cuda_gridDim, cuda_blockDim, &t_args, sharedMem, (cudaStream_t)stream);
    *result = cudaLaunchKernel((void*)function, cuda_gridDim, cuda_blockDim, &t_args, 0, NULL);
    printf("cudaLaunchKernel result: %d\n", *result);
    return 1;
}

/*extern void** __cudaRegisterFatBinary(
  void *fatCubin
);
extern void __cudaRegisterFunction(
  void **fatCubinHandle, const char *hostFun, char *deviceFun,
  const char *deviceName, int thread_limit, void *tid,
  void *bid, void *bDim, void *gDim, int *wSize
);
extern void __cudaRegisterFatBinaryEnd(
  void **fatCubinHandle
);

bool_t cuda_register_fat_binary_1_svc(rpc_fatCubin cubin, ptr_result *result, struct svc_req *rqstp)
{
    struct __fatCubin fat = {.magic = cubin.magic,
                             .seq   = cubin.seq,
                             .text  = cubin.text,
                             .data  = cubin.data,
                             .ptr   = cubin.ptr,
                             .ptr2  = cubin.ptr2,
                             .zero  = cubin.zero};
    printf("__cudaRegisterFatBinary(magic: %x, seq: %x, text: %lx, data: %lx, ptr: %lx, ptr2: %lx, zero: %lx\n",
           fat.magic, fat.seq, fat.text, fat.data, fat.ptr, fat.ptr2, fat.zero);
    //result->ptr_result_u.ptr = (uint64_t)__cudaRegisterFatBinary(&fat);
    result->err = 0;
    return 1;
}

bool_t cuda_register_function_1_svc(ptr cubinHandle, ptr hostFun, char *deviceFun, char *deviceName, int *result, struct svc_req * rqstp)
{
    printf("__cudaRegisterFunction(fatCubinHandle=%p, hostFun=%p, devFunc=%s, deviceName=%s)\n", (void*)cubinHandle, (void*)hostFun, deviceFun, deviceName);
   // __cudaRegisterFunction((void*)cubinHandle, (void*)hostFun, deviceFun, deviceName,                            -1, NULL, NULL, NULL, NULL, NULL);
    *result = 0;
    return 1;
}

bool_t cuda_register_fat_binary_end_1_svc(ptr cubinHandle, int *result, struct svc_req * rqstp)
{
    printf("__cudaRegisterFatBinaryEnd(fatCubinHandle=%p)\n", (void*)cubinHandle);
    //__cudaRegisterFatBinaryEnd((void*)cubinHandle);
    *result = 0;
    return 1;
}*/

int rpc_cd_prog_1_freeresult (SVCXPRT * a, xdrproc_t b , caddr_t c)
{
    if (b == (xdrproc_t) xdr_str_result) {
        free( ((str_result*)c)->str_result_u.str);
    }
}

/* shared object constructor; executes before main and thus hijacks main program */
void __attribute__ ((constructor)) cricketd_main(void)
{
    register SVCXPRT *transp;

    struct sigaction act;
    act.sa_handler = int_handler;
    sigaction(SIGINT, &act, NULL);

    transp = svcunix_create(RPC_ANYSOCK, 0, 0, CD_SOCKET_PATH);
    if (transp == NULL) {
        fprintf (stderr, "%s", "cannot create unix service.");
        exit(1);
    }
    if (!svc_register(transp, RPC_CD_PROG, RPC_CD_VERS, rpc_cd_prog_1, 0)) {
        fprintf (stderr, "%s", "unable to register (RPC_PROG_PROG, RPC_PROG_VERS, ).");
        exit(1);
    }

    /* Call CUDA initialization function (usually called by __libc_init_main())
     * Address of "_ZL24__sti____cudaRegisterAllv" in static symbol table is 0x4016c8
     */
    void (*cudaRegisterAllv)(void) =
        (void(*)(void)) cricketd_utils_symbol_address("_ZL24__sti____cudaRegisterAllv");
    printf("found CUDA initialization function at %p\n", cudaRegisterAllv);
    if (cudaRegisterAllv == NULL) {
        fprintf(stderr, "cricketd: error: could not find cudaRegisterAllv initialization function in cubin. I cannot operate without it.\n");
        exit(1);
    }
    cudaRegisterAllv();

    if (!cricketd_utils_parameter_size(&infos, &kernelnum)) {
        fprintf(stderr, "error while getting parameter sizes\n");
        exit(0);
    }
    printf("waiting for RPC requests...\n");

    svc_run ();
    fprintf (stderr, "%s", "svc_run returned");
    unlink(CD_SOCKET_PATH);
    exit(0);
}

