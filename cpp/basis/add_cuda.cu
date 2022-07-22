// https://developer.nvidia.com/blog/even-easier-introduction-cuda/

#include <iostream>
#include <math.h>
// Kernel function to add the elements of two arrays
__global__
void add(int n, float *x, float *y)
{
  // spread the computation to threads and blocks
  int index = blockIdx.x*blockDim.x + threadIdx.x;
  int stride = blockDim.x*gridDim.x; //threads in the grid; gridDim.x->how many blocks; blockDim.x ->how many threads
  for (int i = index; i < n; i+=stride) // grid-stride loop: thread 0 compute 0, 0+stride, 0+2*stride, ...
    y[i] = x[i] + y[i];
}

int main(void)
{
  int N = 1<<20;
  float *x, *y;

  // Allocate Unified Memory – accessible from CPU or GPU
  cudaMallocManaged(&x, N*sizeof(float));
  cudaMallocManaged(&y, N*sizeof(float));

  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  int blockSize = 256; // threads per block
  int numBlock = (N+blockSize-1)/blockSize; //round up N in case N is not a multiple of blockSize

  int numSMs;
  cudaDeviceGetAttribute(&numSMs, cudaDevAttrMultiProcessorCount, 0);
  numBlock = 32*numSMs;
  std::cout << "Number of blocks: "<< numBlock << std::endl;
  // Run kernel on 1M elements on the GPU
  add<<<numBlock, blockSize>>>(N, x, y);
  // <<blocks, thread>>
  // Wait for GPU to finish before accessing on host
  cudaDeviceSynchronize();

  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for (int i = 0; i < N; i++)
    maxError = fmax(maxError, fabs(y[i]-3.0f));
  std::cout << "Max error: " << maxError << std::endl;

  // Free memory
  cudaFree(x);
  cudaFree(y);
  
  return 0;
}