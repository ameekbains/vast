extern "C" __global__ void blur_kernel(const unsigned char* src, unsigned char* dst, int width, int height)
{
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x >= width || y >= height)
        return;
    // dummy kernel: copy src to dst
    int idx = (y * width + x) * 3;
    dst[idx] = src[idx];
    dst[idx+1] = src[idx+1];
    dst[idx+2] = src[idx+2];
}
